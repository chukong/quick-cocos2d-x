@echo off
set DIR=%~dp0
cd "%DIR%\..\"
php %DIR%\lib\compile_scripts.php -zip -x framework.server -p framework framework lib\framework_precompiled\framework_precompiled

copy lib\framework_precompiled\framework_precompiled.zip template\PROJECT_TEMPLATE_01\res\
