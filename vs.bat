@echo off
set FMATVECT_SRC=%~dp0
set FMATVECT_BUILD=%FMATVECT_SRC%..\build

if not exist "%FMATVECT_BUILD%"       mkdir "%FMATVECT_BUILD%"
if not exist "%FMATVECT_BUILD%\msvc"  mkdir "%FMATVECT_BUILD%\msvc64"

REM Visual Studio 2017 
CALL "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvars64.bat"
REM CALL "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvars32.bat"

set LIB=%LIB%;d:\ArbeitUndAusbildung\2020 Stengel\dev\cbia.lib.lapack.dyn.dbg.x64.12;

REM bug in find_package to find version 1.72
REM set BOOST_INCLUDEDIR=c:\local\boost_1_72_0

cd "%FMATVECT_BUILD%\msvc64"
cmake -G "Visual Studio 15 2017 Win64" ..\..\fmatvec-cmake
devenv fmatvec.sln

