@echo off
set DIR=%~dp0
set OUTPUT_DIR=%DIR%..\extra\luabinding
set MAKE_LUABINDING=%QUICK_COCOS2DX_ROOT%\bin\win32\php.exe %QUICK_COCOS2DX_ROOT%\bin\lib\compile_luabinding.php
pushd
cd "%DIR%"
%MAKE_LUABINDING% -E CCOBJECTS=CCHTTPRequest -d %OUTPUT_DIR% cocos2dx_extra_luabinding.tolua
echo.
echo ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
echo.
%MAKE_LUABINDING% -d %OUTPUT_DIR% cocos2dx_extra_ios_iap_luabinding.tolua
popd
