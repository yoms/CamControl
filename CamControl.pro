#-------------------------------------------------
#
# Project created by QtCreator 2012-10-20T15:00:03
#
#-------------------------------------------------

QT       += core network

arm6{
    target.path = ./
}

TARGET = CamControl
INSTALLS += target

TEMPLATE = app
LIBS = -lgphoto2
QMAKE_CXXFLAGS += -Werror -std=c++0x


SOURCES += main.cpp\
    mcamera.cpp \
    server.cpp \
    message.cpp \
    command.cpp \
    timelapsecommand.cpp \
    capturecommand.cpp

HEADERS  += mcamera.h \
    server.h \
    message.h \
    command.h \
    timelapsecommand.h \
    capturecommand.h
