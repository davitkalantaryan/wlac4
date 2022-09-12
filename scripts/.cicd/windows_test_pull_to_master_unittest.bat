

@echo off
setlocal EnableDelayedExpansion

rem some definations
set "Platform=x64"
set "Configuration=Debug"
rem set "ActionConfirm=build"

set scriptDirectory=%~dp0
cd /D %scriptDirectory%..\..
set "repositoryRoot=%cd%\"


echo "Windows test merge with master unittest will be implemented"
exit /b 0

cd "%repositoryRoot%sys\win_%Platform%\%Configuration%\test"
.\unittest.exe

exit /b !ERRORLEVEL!

endlocal
