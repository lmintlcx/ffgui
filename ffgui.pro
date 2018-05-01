
QT += core gui widgets
CONFIG += qt console

TEMPLATE = app
TARGET = "ffgui"

QMAKE_CXXFLAGS += /MP

HEADERS += \
        ffgui.h

SOURCES += \
        main.cpp \
        ffgui.cpp

TRANSLATIONS += zh_CN.ts

RC_ICONS = logo.ico
