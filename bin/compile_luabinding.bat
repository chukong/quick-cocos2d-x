@echo off
set DIR=%~dp0
php "%DIR%lib\compile_luabinding.php" %*
