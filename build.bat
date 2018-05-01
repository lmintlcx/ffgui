@echo off
title qmake and nmake build shell

set "VSCMD_START_DIR=D:\tmp\ffgui_build"

if not exist D:\tmp\ffgui_build md D:\tmp\ffgui_build
D: && cd D:\tmp\ffgui_build

call "C:\Program Files (x86)\Microsoft Visual Studio\2017\Enterprise\VC\Auxiliary\Build\vcvarsall.bat" x86

C:\Qt\v5.9.5\msvc2017\x86\shared\bin\qmake.exe D:\work\ffgui\ffgui.pro -spec win32-msvc
REM C:\Qt\v5.9.5\msvc2017\x86\shared\bin\lupdate.exe D:\work\ffgui\ffgui.pro
REM C:\Qt\v5.9.5\msvc2017\x86\shared\bin\lrelease.exe D:\work\ffgui\ffgui.pro
del D:\tmp\ffgui_build\debug\ffgui.exe
del D:\tmp\ffgui_build\release\ffgui.exe
nmake Debug
REM nmake Release
REM nmake clean

cd D:\tmp\ffgui_build\debug
if not exist Qt5Cored.dll C:\Qt\v5.9.5\msvc2017\x86\shared\bin\windeployqt.exe ffgui.exe
REM cd D:\tmp\ffgui_build\release
REM if not exist Qt5Core.dll C:\Qt\v5.9.5\msvc2017\x86\shared\bin\windeployqt.exe ffgui.exe
cd D:\tmp\ffgui_build

exit
