QT       += core sql

QT       += gui

QT+=widgets

TARGET = thumbnailsdeleter
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    ThumbnailsDeleter.cpp \
    mapReduceFunctions.cpp \
    FileTimeComparator.cpp \
    TrashCleaner.cpp \
    RpmbuildCleaner.cpp \
    MainLogic.cpp \
    ManageWindow.cpp \
    GeneralCleaner.cpp

HEADERS += \
    DataType.h \
    CommonHeader.h \
    TdPreCompile.h \
    ThumbnailsDeleter.h \
    mapReduceFunctions.h \
    FileTimeComparator.h \
    TrashCleaner.h \
    RpmbuildCleaner.h \
    MainLogic.h \
    ManageWindow.h \
    GeneralCleaner.h

CONFIG+=precompile_header

PRECOMPILED_HEADER+=TdPreCompile.h

QT+=network

FORMS += \
    ThumbnailsDeleter.ui \
    TrashCleaner.ui \
    RpmbuildCleaner.ui \
    ManageWindow.ui \
    GeneralCleaner.ui


TRANSLATIONS+=PublicServer.ts

QT+=concurrent

unix:!macx: LIBS += -lParallizedAlgorithms

#安装
target.path=/usr/bin

INSTALLS += target
CONFIG +=c++11
