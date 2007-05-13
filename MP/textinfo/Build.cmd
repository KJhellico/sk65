@echo off
C:\Keil\ARM\BIN\AA textinfo.asm PL (999) EP
if errorlevel 2 goto comp_err
C:\Keil\ARM\BIN\LA textinfo.obj TO textinfo NOPRINT CASE 
if errorlevel 2 goto link_err
C:\Keil\ARM\BIN\OHA textinfo
..\hex2bin.exe -s 10000 -e dis textinfo.hex
del textinfo.elf
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
