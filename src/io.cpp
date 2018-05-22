/*
 * Created by Kevin Lai
 * Date: 2018.05.20
 *
 * This file defines the input output relations of the form
 *
*/

#include <QtWidgets>
#include "../include/io.h"

IO::IO(QWidget *parent): QWidget(parent)
{
    // define button objects
    connectButton = new QPushButton(tr("&connect"));
    connectButton->setFixedSize(120,40);
    disconnectButton = new QPushButton(tr("&disconnect"));
    disconnectButton->setFixedSize(120,40);
    disconnectButton->setEnabled(false);
    runButton = new QPushButton(tr("&run"));
    runButton->setFixedSize(120,40);
    runButton->setEnabled(false);
    openCameraButton = new QPushButton(tr("&open camera"));
    openCameraButton->setFixedSize(120,40);
    openCameraButton->setEnabled(false);
    exitButton = new QPushButton(tr("&exit"));
    exitButton->setFixedSize(120,40);

    // camera image show up here
    cameraImage = new QLabel(tr("camera image"));
    cameraImage->setAlignment(Qt::AlignCenter);
    cameraImage->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    cameraImage->setFixedSize(500, 400);
    cameraImage->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    // connect the click to the events
    connect(connectButton, SIGNAL(clicked()), this, SLOT(_connectPushButton()));
    connect(disconnectButton, SIGNAL(clicked()), this, SLOT(_disconnectPushButton()));
    connect(runButton, SIGNAL(clicked()), this, SLOT(_runPushButton()));
    connect(openCameraButton, SIGNAL(clicked()), this, SLOT(_openCameraPushButton()));
    connect(exitButton, SIGNAL(clicked()), this, SLOT(_exitPushButton()));

    // layout
    QVBoxLayout *buttonLayout = new QVBoxLayout;
    buttonLayout->addWidget(connectButton);
    buttonLayout->addWidget(disconnectButton);
    buttonLayout->addWidget(runButton);
    buttonLayout->addWidget(openCameraButton);
    buttonLayout->addWidget(exitButton);
    buttonLayout->setSpacing(15);


    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addLayout(buttonLayout, 0, 0, Qt::AlignCenter);
    mainLayout->addWidget(cameraImage, 0, 1, Qt::AlignCenter);
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    setLayout(mainLayout);
    setWindowTitle("Raspberry Pi");

}

void IO::_connectPushButton()
{
    //m_socket._connectServer();
    m_ssh_client._connect();
    connectButton->setEnabled(false);
    disconnectButton->setEnabled(true);
    runButton->setEnabled(true);
    openCameraButton->setEnabled(true);
}

void IO::_disconnectPushButton()
{
    connectButton->setEnabled(true);
    disconnectButton->setEnabled(false);
    runButton->setEnabled(false);
    m_ssh_client._disconnect();
}

void IO::_runPushButton()
{
    m_ssh_client._showRemoteProcess();
}

void IO::_openCameraPushButton()
{
	openCameraButton->setEnabled(false);
    std::cout << "press openCameraPushButton" << std::endl;
}

void IO::_exitPushButton()
{
    exit(-1);
}
