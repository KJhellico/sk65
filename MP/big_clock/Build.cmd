@echo off
C:\Keil\ARM\BIN\AA big_clock.asm PL (999) EP
if errorlevel 2 goto comp_err
C:\Keil\ARM\BIN\LA big_clock.obj TO big_clock NOPRINT CASE 
if errorlevel 2 goto link_err
C:\Keil\ARM\BIN\OHA big_clock
..\hex2bin.exe -s 10000 -e dis big_clock.hex
del big_clock.elf
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
