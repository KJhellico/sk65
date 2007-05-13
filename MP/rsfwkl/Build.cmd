@echo off
C:\Keil\ARM\BIN\AA rsfwkl.asm PL (999) EP
if errorlevel 2 goto comp_err
C:\Keil\ARM\BIN\LA rsfwkl.obj TO rsfwkl NOPRINT CASE 
if errorlevel 2 goto link_err
C:\Keil\ARM\BIN\OHA rsfwkl
..\hex2vkp -Fc:\temp\sk_full.bin rsfwkl.hex
del rsfwkl.elf
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
