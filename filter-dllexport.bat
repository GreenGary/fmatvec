@echo off
set _TMP=%1.tmp
copy /Y %1 %_TMP%
echo EXPORTS  > %1
type %_TMP% | findstr /R fmatvec >> %1
