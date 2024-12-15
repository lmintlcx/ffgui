
TEMPLATE = app
TARGET = "ffgui"

CONFIG += qt console
QT += core gui widgets

CONFIG -= import_plugins
QTPLUGIN += qwindows qwindowsvistastyle qjpeg qico

QMAKE_CXXFLAGS += /MP /utf-8 /std:c++17

HEADERS += \
        ffgui.h

SOURCES += \
        main.cpp \
        ffgui.cpp

TRANSLATIONS += ffgui_zh_CN.ts

RESOURCES += ffgui.qrc

RC_ICONS = logo.ico
VERSION = 2.0.0
