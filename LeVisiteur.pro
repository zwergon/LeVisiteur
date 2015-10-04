#-------------------------------------------------
#
# Project created by QtCreator 2015-07-28T22:10:04
#
#-------------------------------------------------

QT       += core gui network xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LeVisiteur
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    visiteursettings.cpp \
    scene.cpp \
    hostdialog.cpp

HEADERS  += mainwindow.h \
    visiteursettings.h \
    scene.h \
    hostdialog.h

FORMS    += mainwindow.ui \
    hostdialog.ui
