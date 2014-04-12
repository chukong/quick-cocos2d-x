@echo off
set DIR=%~dp0
set TOLUA=%QUICK_COCOS2DX_ROOT%\bin\win32\tolua++.exe

set DOS2UNIX=%QUICK_COCOS2DX_ROOT%\bin\win32\iconv\dos2unix.exe
set CPP_FILE=%QUICK_COCOS2DX_ROOT%\lib\cocos2d-x\scripting\lua\cocos2dx_support\LuaCocos2d.cpp

cd /d "%DIR%"
%TOLUA% -L "%DIR%basic.lua" -o "%CPP_FILE%" Cocos2d.tolua
%DOS2UNIX% "%CPP_FILE%"
pause
