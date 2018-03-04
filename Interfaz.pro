#-------------------------------------------------
#
# Project created by QtCreator 2018-03-01T17:41:13
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Interfaz
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    colortransformation.cpp \
    noise.cpp

HEADERS  += mainwindow.h \
    colortransformation.h \
    noise.h \
    kernel.h

FORMS    += mainwindow.ui
