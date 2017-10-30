#-------------------------------------------------
#
# Project created by QtCreator 2015-05-11T10:05:40
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = test
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

INCLUDEPATH += /usr/lib/jvm/jdk1.7.0_80/include\
        /usr/lib/jvm/jdk1.7.0_80/include/linux

HEADERS  += mainwindow.h \
    stringtohex.h

FORMS    += mainwindow.ui

DISTFILES += java/ddmlib.jar \
    java/com/android/screenshot/Screenshot.class \
    java/com/android/screenshot/Screenshot$1.class

unix|win32: LIBS += -L/usr/lib/jvm/jdk1.7.0_80/jre/lib/amd64/server -ljvm
