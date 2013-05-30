@echo off
set DIR=%~dp0
set OUTPUT_DIR=%DIR%
set MAKE_LUABINDING="%QUICK_COCOS2DX_ROOT%\bin\compile_luabinding.bat"
call %MAKE_LUABINDING% -E CCOBJECTS=ArmatureDataManager,Armature -d %OUTPUT_DIR% SPArmature_luabinding.tolua
