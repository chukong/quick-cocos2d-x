@ECHO OFF
SET SRCDIR=%~p0
ECHO RMDIR /s/q "%SRCDIR%out\"
ECHO RMDIR /s/q "%SRCDIR%bin\"

pause

RMDIR /s/q "%SRCDIR%out\"
RMDIR /s/q "%SRCDIR%bin\"

