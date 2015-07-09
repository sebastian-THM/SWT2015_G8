#-------------------------------------------------
#
# Project created by QtCreator 2015-06-20T21:05:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SWT2015_G8
TEMPLATE = app


SOURCES += main.cpp\
        view_qt.cpp \
    cutting_area.cpp \
    renderarea.cpp \
    parser.cpp

HEADERS  += view_qt.h \
    cutting_area.h \
    renderarea.h \
    parser.h

FORMS    += view_qt.ui

#
# Use the ISO C++ 2011 standard
#
CONFIG += c++11
