#ifndef IO_H
#define IO_H

#include <QWidget>
#include <QMap>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <time.h>
#include "../include/ssh_connect.h"


class QPushButton;
class QTextEdit;
class QLabel;
class QSlider;
class QSpinBox;
class QCheckBox;


class IO: public QWidget
{
    Q_OBJECT

public:
    IO(QWidget *parent = 0);

public slots:
    void _connectPushButton();
    void _disconnectPushButton();
    void _runPushButton();
    void _openCameraPushButton();
    void _exitPushButton();

private:
    SSHCLIENT m_ssh_client;

    QPushButton *connectButton;
    QPushButton *disconnectButton;
    QPushButton *runButton;
    QPushButton *openCameraButton;
    QPushButton *exitButton;


    QLabel *cameraImage;

};

#endif // IO_H
