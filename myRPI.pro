#-------------------------------------------------
#
# Project created by QtCreator 2018-05-20T16:45:46
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = myRPI
TEMPLATE = app

# This include and lib paths are for my mac (libssh)
INCLUDEPATH += /usr/local/Cellar/libssh/0.7.5/include
LIBS += -L/usr/local/Cellar/libssh/0.7.5/lib -lssh
#LIBS += /usr/local/lib

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    src/io.cpp \
    src/main.cpp \
    src/ssh_connect.cpp

HEADERS  += \
    include/io.h \
    include/ssh_connect.h

#FORMS    += mainwindow.ui

CONFIG += c++11

FORMS +=

DISTFILES += \
    README.md
