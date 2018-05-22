/*
 * Created by Kevin Lai
 * Date: 2018.05.20
 *
 * This file defines the input output relations of the form
 *
*/



#include "../include/ssh_connect.h"


SSHCLIENT::SSHCLIENT()
{

}

SSHCLIENT::~SSHCLIENT()
{

}


bool SSHCLIENT::_connectServer()
{
    // connecting to the server
    cout << "trying to connect to server" << endl;

    if(connect(client, (struct sockaddr*)&server_addr, sizeof(server_addr)) == 0) {
        cout << "Connecting to server" << endl;
    }

    recv(client, buffer, bufSize, 0);
    cout << "Connection confirmed" << endl;
    cout << "Enter # to end the connection" << endl;

    do {
        cout << "\nClient: ";
        do {
            cin >> buffer;
            send(server, buffer, bufSize, 0);
            if(*buffer == '#') {
                send(server, buffer, bufSize, 0);
                *buffer = '*';
                isExit = true;
            }
        } while(*buffer != 42);

        cout << "\nServer: ";
        do {
            recv(server, buffer, bufSize, 0);
            cout << "buffer" << " ";
            if(*buffer == '#') {
                *buffer = '*';
                isExit = true;
            }
        } while(*buffer != 42);


        cout << endl;

    } while(!isExit);


    cout << "Connection terminated..." << endl;
    cout << "Goodbye!" << endl;

    close(client);
    return 0;
}

bool SSHCLIENT::_connect() {
    m_ssh_session = ssh_new();
    if(m_ssh_session == NULL) exit(-1);
    ssh_options_set(m_ssh_session, SSH_OPTIONS_HOST, m_ip);

    rc = ssh_connect(m_ssh_session);
    if(rc != SSH_OK) {
        cout << "Error connecting to remote host" << endl;
        ssh_free(m_ssh_session);
        exit(-1);
    }
    cout << "Porting successful!" << endl;

    // verify session
    if (_verifyKnownHost(m_ssh_session) < 0)
    {
        ssh_disconnect(m_ssh_session);
        ssh_free(m_ssh_session);
        exit(-1);
    }
    cout << "Verify success!" << endl;


    // authenticate
    rc = ssh_userauth_password(m_ssh_session, NULL, m_password);
    if(rc != SSH_AUTH_SUCCESS) {
        cout << "Error authentication" << endl;
        ssh_disconnect(m_ssh_session);
        ssh_free(m_ssh_session);
        exit(-1);
    }
    cout << "Server authentication success!" << endl;
}

bool SSHCLIENT::_disconnect()
{
    cout << "Disconnecting..." << endl;
    ssh_disconnect(m_ssh_session);
    ssh_free(m_ssh_session);
    return 0;
}

int SSHCLIENT::_verifyKnownHost(ssh_session session)
{
    int state, hlen;
    unsigned char *hash = NULL;
    char *hexa;
    char buf[10];

    state = ssh_is_server_known(session);
    hlen = ssh_get_pubkey_hash(session, &hash);

    if (hlen < 0) return -1;

    switch (state) {
        case SSH_SERVER_KNOWN_OK:
            break; /* ok */
        case SSH_SERVER_KNOWN_CHANGED:
            fprintf(stderr, "Host key for server changed: it is now:\n");
            ssh_print_hexa("Public key hash", hash, hlen);
            fprintf(stderr, "For security reasons, connection will be stopped\n");
            free(hash);
            return -1;
        case SSH_SERVER_FOUND_OTHER:
            fprintf(stderr, "The host key for this server was not found but an other"
            "type of key exists.\n");
            fprintf(stderr, "An attacker might change the default server key to"
            "confuse your client into thinking the key does not exist\n");
            free(hash);
            return -1;
        case SSH_SERVER_FILE_NOT_FOUND:
            fprintf(stderr, "Could not find known host file.\n");
            fprintf(stderr, "If you accept the host key here, the file will be"
            "automatically created.\n");
            /* fallback to SSH_SERVER_NOT_KNOWN behavior */
        case SSH_SERVER_NOT_KNOWN:
            hexa = ssh_get_hexa(hash, hlen);
            fprintf(stderr,"The server is unknown. Do you trust the host key?\n");
            fprintf(stderr, "Public key hash: %s\n", hexa);
            free(hexa);
            if (fgets(buf, sizeof(buf), stdin) == NULL)
            {
                free(hash);
                return -1;
            }
            if (strncasecmp(buf, "yes", 3) != 0)
            {
                free(hash);
                return -1;
            }
            if (ssh_write_knownhost(session) < 0)
            {
                fprintf(stderr, "Error %s\n", strerror(errno));
                free(hash);
                return -1;
            }
            break;
        case SSH_SERVER_ERROR:
            fprintf(stderr, "Error %s", ssh_get_error(session));
            free(hash);
            return -1;
    }
    free(hash);
    return 0;
}

int SSHCLIENT::_showRemoteProcess()
{
    ssh_channel channel;
    int         rc;
    char        buffer[256];
    int         nbytes;

    // allocate a new channel
    channel = ssh_channel_new(m_ssh_session);
    if (channel == NULL) {
        return SSH_ERROR;
    }

    // open session channel
    rc = ssh_channel_open_session(channel);
    if (rc != SSH_OK) {
        ssh_channel_free(channel);
        return rc;
    }
    cout << "Open ssh channel success!" << endl;

    // run a shell command without an interactive shell
    rc = ssh_channel_request_exec(channel, "cd ~/research/texture && pwd");
    if (rc != SSH_OK) {
        ssh_channel_close(channel);
        ssh_channel_free(channel);
        return rc;
    }


    // reads data from a channel
    nbytes = ssh_channel_read(channel, buffer, sizeof(buffer), 0);
    while (nbytes > 0) {
        if (write(1, buffer, nbytes) != (unsigned int)nbytes) {
            ssh_channel_close(channel);
            ssh_channel_free(channel);
            return SSH_ERROR;
        }
        nbytes = ssh_channel_read(channel, buffer, sizeof(buffer), 0);
    }


    if (nbytes < 0) {
        ssh_channel_close(channel);
        ssh_channel_free(channel);
        return SSH_ERROR;
    }

    /* Send an end of file on the channel */
    ssh_channel_send_eof(channel);
    /* Close a channel */
    ssh_channel_close(channel);
    /* Close and free a channel */
    ssh_channel_free(channel);

    return SSH_OK;
}
