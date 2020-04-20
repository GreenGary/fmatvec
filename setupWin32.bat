@echo off
set FMATVECT_SRC=%~dp0
set FMATVECT_BUILD=%FMATVECT_SRC%..\build

if not exist "%FMATVECT_BUILD%"       mkdir "%FMATVECT_BUILD%"
if not exist "%FMATVECT_BUILD%\ninja" mkdir "%FMATVECT_BUILD%\ninja32"

REM Visual Studio 2017 
REM CALL "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvars64.bat"
CALL "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvars32.bat"

set LIB=%LIB%;d:\ArbeitUndAusbildung\2020 Stengel\dev\LAPACKE_examples\lib;

REM bug in find_package to find version 1.72
REM set BOOST_INCLUDEDIR=c:\local\boost_1_72_0

cd "%FMATVECT_BUILD%\ninja32"
cmd
