QT += core
QT -= gui

CONFIG += c++11

TARGET = BlueZ_API_Test
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

INCLUDEPATH +=  "/usr/include/" \
                "/usr/include/gstreamer-1.0/" \
                "/usr/include/glib-2.0/" \
                "/usr/include/glib-2.0/glib/" \
                "/usr/lib/x86_64-linux-gnu/glib-2.0/include/" \
                "/usr/lib/x86_64-linux-gnu/gstreamer-1.0/include/"

LIBS += -lbluetooth \
        -lgstreamer-1.0 \
        -lgobject-2.0 \
        -lglib-2.0

SOURCES += main.cpp \
    bluetoothscanner.cpp \
    logger.cpp \
    bluetoothdevice.cpp \
    mutex.cpp \
    audioplayer.cpp

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
    bluetoothscanner.h \
    logger.h \
    bluetoothdevice.h \
    mutex.h \
    audioplayer.h
