@echo off

START /B %~dp0..\..\simulator\bin\win32\LuaHostWin32.exe -workdir %~dp0 -file scripts/main.lua -size 640x960