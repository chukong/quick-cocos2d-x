@echo off

if "%WindowsSdkDir%" == "" (
    echo Start this batch script from Visual Studio Command Prompt
    goto :EOF
)

set DIR=%~dp0
set SRCDIR=%DIR%LuaJit-2.0.2
set DESTDIR=%DIR%win32

del %DESTDIR%\*.lib
del %DESTDIR%\*.dll

cd /d %SRCDIR%\src
call msvcbuild.bat static

if exist %SRCDIR%\src\lua51.lib (
    copy %SRCDIR%\src\lua51.lib %DESTDIR%
)

cd /d %DIR%
