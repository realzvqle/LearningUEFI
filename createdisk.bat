@echo off



if exist image\image.vhd del del image\image.vhd
echo Partition the drive now
diskpart /s c:\build\scripts\partition.txt
mkdir Z:\EFI\BOOT
robocopy root Z:\ /s
diskpart /s c:\build\scripts\detach.txt
