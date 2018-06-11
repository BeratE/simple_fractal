#-------------------------------------------------
#
# Project created by QtCreator 2018-05-25T17:58:52
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Fractals
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    myglwidget.cpp

HEADERS  += mainwindow.h \
    myglwidget.h

FORMS    += mainwindow.ui

RESOURCES += \
    shaders.qrc

DISTFILES +=
