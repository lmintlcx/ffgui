@echo off
title qmake and nmake build shell

set "VSCMD_START_DIR=D:\tmp\ffgui_build"

if not exist D:\tmp\ffgui_build md D:\tmp\ffgui_build
cd /d D:\tmp\ffgui_build

call "C:\VisualStudio\2017\BuildTools\VC\Auxiliary\Build\vcvarsall.bat" x86

C:\Dev\Qt_5.15.14\msvc2017_x86\static\bin\qmake.exe D:\repo\ffgui\ffgui.pro -spec win32-msvc

REM C:\Dev\Qt_5.15.14\msvc2017_x86\static\bin\lupdate.exe D:\repo\ffgui\ffgui.pro
REM C:\Dev\Qt_5.15.14\msvc2017_x86\static\bin\lrelease.exe D:\repo\ffgui\ffgui.pro

del D:\tmp\ffgui_build\debug\ffgui.exe
del D:\tmp\ffgui_build\release\ffgui.exe
nmake Debug
REM nmake Release
REM nmake clean
