@echo off
set DIR=%~dp0
cd "%DIR%\..\"
%DIR%win32\php.exe %DIR%\lib\compile_scripts.php -i framework -o lib\framework_precompiled\framework_precompiled.zip -p framework -m zip

copy lib\framework_precompiled\framework_precompiled.zip template\PROJECT_TEMPLATE_01\res\
