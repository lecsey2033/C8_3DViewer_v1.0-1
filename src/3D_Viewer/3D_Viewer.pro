QT       += core gui openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../obj_parcer.c \
    main.cpp \
    mainwindow.cpp \
    openglwidget.cpp

HEADERS += \
    ../obj_parcer.h \
    mainwindow.h \
    openglwidget.h

FORMS += \
    mainwindow.ui

include(3rdparty/src/gifimage/qtgifimage.pri)


