#-------------------------------------------------
#
# Project created by QtCreator 2012-10-20T15:00:03
#
#-------------------------------------------------

QT       += core network

TARGET = CamControl
TEMPLATE = app
LIBS = -lgphoto2
QMAKE_CXXFLAGS += -Werror -std=c++0x


SOURCES += main.cpp\
    mcamera.cpp \
    timelapse.cpp \
    server.cpp

HEADERS  += mcamera.h \
    timelapse.h \
    server.h
