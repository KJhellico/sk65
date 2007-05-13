@echo off
C:\Keil\ARM\BIN\AA progress.asm PL (999) EP
if errorlevel 2 goto comp_err
C:\Keil\ARM\BIN\LA progress.obj TO progress NOPRINT CASE 
if errorlevel 2 goto link_err
C:\Keil\ARM\BIN\OHA progress
..\hex2vkp -Fc:\temp\sk_full.bin progress.hex
del progress.elf
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
