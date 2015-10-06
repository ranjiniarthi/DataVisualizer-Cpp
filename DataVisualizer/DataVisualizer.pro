#-------------------------------------------------
#
# Project created by QtCreator 2015-09-01T16:10:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DataVisualizer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    bheap.cpp \
    queue.cpp \
    stack.cpp

HEADERS  += mainwindow.h \
    bheap.h \
    queue.h \
    stack.h

FORMS    += mainwindow.ui \
    bheap.ui \
    queue.ui \
    stack.ui
