@echo off
C:\Keil\ARM\BIN\AA accutemp.asm PL (999) EP
if errorlevel 2 goto comp_err
C:\Keil\ARM\BIN\LA accutemp.obj TO accutemp NOPRINT CASE 
if errorlevel 2 goto link_err
C:\Keil\ARM\BIN\OHA accutemp
..\hex2bin.exe -s 10000 -e dis accutemp.hex
del accutemp.elf
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
