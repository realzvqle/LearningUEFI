@echo off

if exist ..\root rd ..\root /s /q
mkdir ..\root\EFI\BOOT
echo Building Bootloader!
cd bootloader
cmd /c make.bat
cd ..
echo Building Kernel!
cd kernel
cmd /c make.bat
cd ..
