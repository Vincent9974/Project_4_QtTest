@echo off
title qmake and nmake build prompt
set MINGW_PATH=d:\Qt\Qt5.14.2\Tools\mingw730_32
set QT_DIR=d:\Qt\Qt5.14.2\5.14.2\mingw73_32
set BUILD_DIR=%cd%\build
set PRO_DIR=%cd%
set PATH=%MINGW_PATH%\bin;%QT_DIR%\bin;%PATH%


if not exist %BUILD_DIR% (
    md %BUILD_DIR%
)

cd build
qmake.exe %PRO_DIR%\HelloWorld.pro -spec win32-g++ "CONFIG+=debug" "CONFIG+=console"
if exist %BUILD_DIR%\debug\HelloWorld.exe del %BUILD_DIR%\debug\HelloWorld.exe
@REM d:\Qt\Qt5.14.2\Tools\QtCreator\bin\jom.exe -j4
%MINGW_PATH%\bin\mingw32-make -f Makefile.Debug
cd debug
if not exist %BUILD_DIR%\debug\Qt5Core.dll (
    windeployqt HelloWorld.exe
)