#-------------------------------------------------
#
# Project created by QtCreator 2015-05-29T16:42:50
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtLcd
TEMPLATE = app


SOURCES += main.cpp\
        lcd.cpp \
    LcdAPI.cpp \
    Menu.cpp \
    MenuAPP.cpp \
    key.cpp \
    mcu.cpp

HEADERS  += lcd.h \
    basetype.h \
    LcdAPI.h \
    Menu.h \
    MenuAPP.h \
    ascii.h \
    key.h \
    mcu.h

FORMS    += lcd.ui \
    key.ui
