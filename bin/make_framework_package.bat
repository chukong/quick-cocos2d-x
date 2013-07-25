@echo off
set DIR=%~dp0
cd "%DIR%\..\"
%DIR%win32\php.exe %DIR%\lib\compile_scripts.php -zip -p framework framework lib\framework_precompiled\framework_precompiled

copy lib\framework_precompiled\framework_precompiled.zip template\PROJECT_TEMPLATE_01\res\
