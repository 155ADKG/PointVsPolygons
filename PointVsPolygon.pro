#-------------------------------------------------
#
# Project created by QtCreator 2016-11-10T10:55:27
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PointVsPolygon
TEMPLATE = app


SOURCES += main.cpp\
        mainform.cpp \
    algorithms.cpp \
    draw.cpp

HEADERS  += mainform.h \
    algorithms.h \
    draw.h

FORMS    += mainform.ui
