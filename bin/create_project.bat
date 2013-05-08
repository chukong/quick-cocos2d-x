@echo off
set DIR=%~dp0
set TEMPLATE_ROOT=%DIR%..\template
php "%DIR%lib\create_project.php" -t "%TEMPLATE_ROOT%\PROJECT_TEMPLATE_01" %*
