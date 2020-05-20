@echo off
title qmake and nmake build shell

set "VSCMD_START_DIR=D:\tmp\ffgui_build"

if not exist D:\tmp\ffgui_build md D:\tmp\ffgui_build
D: && cd D:\tmp\ffgui_build

call "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvarsall.bat" x86 10.0.10240.0

REM set PATH=C:\Program Files (x86)\Microsoft SDKs\Windows\v7.1A\Bin;%PATH%
REM set INCLUDE=C:\Program Files (x86)\Microsoft SDKs\Windows\v7.1A\Include;%INCLUDE%
REM set LIB=C:\Program Files (x86)\Microsoft SDKs\Windows\v7.1A\Lib;%LIB%

C:\Qt\Qt_5.14.2\msvc2017_x86\static\bin\qmake.exe D:\work\ffgui\ffgui.pro -spec win32-msvc

REM C:\Qt\Qt_5.14.2\msvc2017_x86\static\bin\lupdate.exe D:\work\ffgui\ffgui.pro
REM C:\Qt\Qt_5.14.2\msvc2017_x86\static\bin\lrelease.exe D:\work\ffgui\ffgui.pro

del D:\tmp\ffgui_build\debug\ffgui.exe
del D:\tmp\ffgui_build\release\ffgui.exe
nmake Debug
REM nmake Release
REM nmake clean
