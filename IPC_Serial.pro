#-------------------------------------------------
#
# Project created by QtCreator 2017-10-23T15:39:48
#
#-------------------------------------------------
DEFINES += GDBUS
if(contains(DEFINES, GDBUS)){
message(build with gdbus)
QT       -= gui
TARGET = IPC_Serial
CONFIG   += console
CONFIG   -= app_bundle
CONFIG   +=0x11
TEMPLATE = app

INCLUDEPATH+= /usr/include \
                /usr/include/glib-2.0 \
                /usr/include/glib-2.0/gio \
                /usr/include/gio-unix-2.0 \
                /usr/include/gio-unix-2.0/gio \
                /usr/include/gio-unix-2.0/gio \
                /usr/include/giomm-2.4 \
                /usr/lib/i386-linux-gnu/glib-2.0/include

LIBS += -L/usr/lib/i386-linux-gnu -lgio-2.0   -lgobject-2.0 -lglib-2.0  -lpthread


SOURCES += \
    src/demo.cpp \
    src/taskManager.cpp \
    src/TLVtools.cpp \
    src/DataLinkLayer.cpp \
    src/TransportLayer.cpp \
    src/COBSTool.cpp \
    src/MsgQueue.cpp \
    src/common.cpp \
    src/serial.cpp \
    src/timeout.cpp \
    src/Msg2MCUhandler.cpp \
    src/SerialServer.cpp \
    src/gdbus/ServiceOfSerial.c

HEADERS += \
    src/common.h \
    src/taskManager.h \
    src/TLVtools.h \
    src/DataLinkLayer.h \
    src/TransportLayer.h \
    src/COBSTool.h \
    src/MsgQueue.h \
    src/serial.h \
    src/timeout.h \
    src/Msg2MCUhandler.h \
    src/SerialServer.h \
    src/gdbus/ServiceOfSerial.h
}
else{
message(build with qdbus)
QT       += core dbus

QT       -= gui

TARGET = IPC_Serial
CONFIG   += console
CONFIG   -= app_bundle
CONFIG   +=0x11
TEMPLATE = app


SOURCES += \
    src/demo.cpp \
    src/taskManager.cpp \
    src/TLVtools.cpp \
    src/DataLinkLayer.cpp \
    src/TransportLayer.cpp \
    src/COBSTool.cpp \
    src/MsgQueue.cpp \
    src/common.cpp \
    src/serial.cpp \
    src/timeout.cpp \
    src/Msg2MCUhandler.cpp \
    src/SerialServer.cpp

HEADERS += \
    src/common.h \
    src/taskManager.h \
    src/TLVtools.h \
    src/DataLinkLayer.h \
    src/TransportLayer.h \
    src/COBSTool.h \
    src/MsgQueue.h \
    src/serial.h \
    src/timeout.h \
    src/Msg2MCUhandler.h \
    src/SerialServer.h
}
