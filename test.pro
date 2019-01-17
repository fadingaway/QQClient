#-------------------------------------------------
#
# Project created by QtCreator 2018-10-11T11:04:48
#
#-------------------------------------------------

QT       += core gui
QT += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = test
TEMPLATE = app


SOURCES += main.cpp \
    widget.cpp \
    mylabel.cpp \
    networkwindow.cpp \
    filetransferthread.cpp

HEADERS  += \
    widget.h \
    mylabel.h \
    networkwindow.h \
    filetransferthread.h

FORMS    +=

RESOURCES += \
    image.qrc
