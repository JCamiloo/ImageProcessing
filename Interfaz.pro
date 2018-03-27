#-------------------------------------------------
#
# Project created by QtCreator 2018-03-01T17:41:13
#
#-------------------------------------------------

QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets charts

TARGET = Interfaz
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    colortransformation.cpp \
    noise.cpp \
    histogram.cpp \
    morphological.cpp

HEADERS  += mainwindow.h \
    colortransformation.h \
    noise.h \
    histogram.h \
    morphological.h

FORMS    += mainwindow.ui
