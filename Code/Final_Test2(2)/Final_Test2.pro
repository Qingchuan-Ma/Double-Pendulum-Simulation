#-------------------------------------------------
#
# Project created by QtCreator 2016-12-13T17:30:52
#
#-------------------------------------------------

QT       += core gui
QT       += gui
QT       += opengl
QT       += multimedia
CONFIG += c++11

LIBS += -lglut32
LIBS += -LC:\glut

QT += core gui opengl
LIBS += -lopengl32 -lglu32

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Final_Test2
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp \
    graph1.cpp \
    double_pendulum_culculate.cpp \
    triple_pendulum_culculate.cpp \
    graph2.cpp \
    graph3.cpp \
    graph4.cpp \
    graph1_1.cpp \
    graph1_2.cpp \
    graph1_3.cpp \
    titlebar.cpp \
    help.cpp \
    calculatewidget.cpp \
    connect.cpp \
    graph3_1.cpp \
    graph3_2.cpp \
    graph3_3.cpp \
    fun.cpp

HEADERS  += dialog.h \
    graph1.h \
    double_pendulum_culculate.h \
    triple_pendulum_culculate.h \
    graph2.h \
    graph3.h \
    graph4.h \
    graph1_1.h \
    graph1_2.h \
    graph1_3.h \
    titlebar.h \
    help.h \
    calculatewidget.h \
    connect.h \
    graph3_1.h \
    graph3_2.h \
    graph3_3.h \
    fun.h

FORMS    += dialog.ui \
    help.ui \
    connect.ui \
    fun.ui

RESOURCES += \
    testresourse2.qrc

OTHER_FILES +=
