@echo off
set DIR=%~dp0
set OUTPUT_DIR=%DIR%
set MAKE_LUABINDING="%QUICK_COCOS2DX_ROOT%\bin\compile_luabinding.bat"
call %MAKE_LUABINDING% -E CCOBJECTS=CCPhysicsWorld,CCPhysicsBody,CCPhysicsShape,CCPhysicsDebugNode,CCPhysicsCollisionEvent,CCPhysicsVector -d %OUTPUT_DIR% CCPhysicsWorld_luabinding.tolua
