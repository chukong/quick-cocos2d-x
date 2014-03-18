@echo off
set QUICK=%QUICK_COCOS2DX_ROOT%\player\bin\win32\quick-x-player.exe
set PROJECT=%cd%
set SIZE=960x640
start "Quick X Player " "%QUICK%" -workdir %PROJECT% -file %PROJECT%\scripts\main.lua -size %SIZE%
