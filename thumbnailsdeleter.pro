QT       += core sql
QT+=websockets
QT       += gui

QT+=widgets

TARGET = thumbnailsdeleter
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    ApplicationNameManager.cpp \
    mapReduceFunctions.cpp \
    FileTimeComparator.cpp \
    MainLogic.cpp \
    ManageWindow.cpp \
    GeneralCleaner.cpp

HEADERS += \
    ApplicationNameManager.h \
    DataType.h \
    CommonHeader.h \
    TdPreCompile.h \
    mapReduceFunctions.h \
    FileTimeComparator.h \
    MainLogic.h \
    ManageWindow.h \
    GeneralCleaner.h

CONFIG+=precompile_header

PRECOMPILED_HEADER += TdPreCompile.h

#QT+=network

FORMS += \
    ManageWindow.ui \
    GeneralCleaner.ui


TRANSLATIONS+=PublicServer.ts

QT+=concurrent

unix:!macx: LIBS += -lParallizedAlgorithms

#安装
target.path=/usr/bin

INSTALLS += target
CONFIG +=c++11

unix:!macx: LIBS += -lRotatingActiveUserQt

unix:!macx: LIBS += -llowmemoryqt
