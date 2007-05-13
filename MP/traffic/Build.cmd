@echo off
C:\Keil\ARM\BIN\AA traffic.asm PL (999) EP
if errorlevel 2 goto comp_err
C:\Keil\ARM\BIN\LA traffic.obj TO traffic NOPRINT CASE 
if errorlevel 2 goto link_err
C:\Keil\ARM\BIN\OHA traffic
..\hex2vkp -Fc:\temp\sk_full.bin traffic.hex
del traffic.elf
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
