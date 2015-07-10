#-------------------------------------------------
#
# Project created by QtCreator 2015-06-20T21:05:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SWT2015_G8
TEMPLATE = app

SOURCES +=  main.cpp\
            view_qt.cpp \
            controller.cpp \
            states/state_base.cpp \
            states/state_cut.cpp \
            states/state_move.cpp \
            states/state_off.cpp \
            states/state_on.cpp \
            renderarea.cpp \
            parser.cpp \
            dispatchtable.cpp

HEADERS  += view_qt.h \
            controller.h \
            states/state_base.h \
            states/state_cut.h \
            states/state_move.h \
            states/state_off.h \
            states/state_on.h \
            renderarea.h \
            parser.h \
            dispatchtable.h

FORMS    += view_qt.ui

#
# Use the ISO C++ 2011 standard
#
CONFIG += c++11
