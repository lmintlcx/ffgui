
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

TRANSLATIONS += ffgui_zh_CN.ts

RESOURCES += ffgui.qrc

RC_ICONS = logo.ico
