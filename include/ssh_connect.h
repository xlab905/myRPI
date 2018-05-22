#ifndef SSHCLIENT_H
#define SSHCLIENT_H

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <string>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <libssh/libssh.h>
#include <unistd.h>
#include <netdb.h>

using namespace std;

class SSHCLIENT
{
public:
    SSHCLIENT();
    ~SSHCLIENT();

public:
    bool _connectServer();
    bool _connect();
    bool _disconnect();
    int _verifyKnownHost(ssh_session session);
    int _showRemoteProcess();

private:
    int client, server;
    int portNum = 1500;
    bool isExit = false;
    static const int bufSize = 1024;
    char buffer[bufSize];


    ssh_session m_ssh_session;
    int port = 22;
    char *m_ip = "140.113.150.59";
    char *m_password = "XlaB@B36";
    int rc;

    struct sockaddr_in server_addr;
};

#endif // SSHCLIENT_H
