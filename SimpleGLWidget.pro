#-------------------------------------------------
#
# Project created by QtCreator 2015-11-17T16:20:05
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SimpleGLWidget
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cxx\
        mainwindow.cxx \
    glwidget.cxx

HEADERS  += mainwindow.hxx \
    glwidget.hxx

FORMS    += mainwindow.ui

DISTFILES += \
    setup.bat
