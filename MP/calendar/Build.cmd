@echo off
C:\Keil\ARM\BIN\AA calendar.asm PL (999) EP
if errorlevel 2 goto comp_err
C:\Keil\ARM\BIN\LA calendar.obj TO calendar NOPRINT CASE 
if errorlevel 2 goto link_err
C:\Keil\ARM\BIN\OHA calendar
..\hex2bin.exe -s 10000 -e dis calendar.hex
del calendar.elf
echo !!! SUCCESS !!!
goto end

:comp_err
echo !!! COMPILE ERRORS !!!
goto end

:link_err
echo !!! LINK ERRORS !!!
goto end

:end
pause
