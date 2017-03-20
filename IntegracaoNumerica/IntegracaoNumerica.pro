#-------------------------------------------------
#
# Project created by QtCreator 2017-03-13T14:33:26
#
#-------------------------------------------------

QT       += core gui script

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = IntegracaoNumerica
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    plotwidget.cpp \
    integrationmethod.cpp \
    metodos/trapezoidalrule.cpp

HEADERS  += mainwindow.h \
    plotwidget.h \
    integrationmethod.h \
    metodos/trapezoidalrule.h

FORMS    += mainwindow.ui
