#-------------------------------------------------
#
# Project created by QtCreator 2012-08-22T12:01:36
#
#-------------------------------------------------

QT       += core gui

TARGET = rectanglePacker
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    SP/SPPackingStrategy.cpp \
    SP/SPPackingCommand.cpp \
    SP/Rect.cpp \
    SP/PackingCommand.cpp \
    SP/Layout.cpp \
    SP/GraphPacking.cpp \
    stage.cpp \
    saparamsdialog.cpp \
    addrectdialog.cpp

HEADERS  += mainwindow.h \
    SP/SPPackingStrategy.h \
    SP/SPPackingCommand.h \
    SP/Rect.h \
    SP/Point.h \
    SP/PackingStrategy.h \
    SP/PackingCommand.h \
    SP/Layout.h \
    SP/GraphPacking.h \
    stage.h \
    saparamsdialog.h \
    addrectdialog.h

FORMS    += mainwindow.ui \
    stage.ui \
    saparamsdialog.ui \
    addrectdialog.ui
