@echo off


if exist image.vhd del image.vhd
cl /c /Zl /I"C:\efitoolkit\EFI_Toolkit_2.0\include" /I"/efitoolkit/EFI_Toolkit_2.0/include\efi\em64t" main.c
link /entry:EfiEntry /LIBPATH:"C:\efitoolkit\EFI_Toolkit_2.0\lib" /dll /IGNORE:4086 main.obj
fwimage app main.dll main.efi
echo Partition the drive now
diskpart /s c:\projects\uefit\partition.txt
mkdir Z:\EFI\BOOT
xcopy main.efi Z:\efi\boot\bootx64.efi
diskpart /s c:\projects\uefit\detach.txt
qemu-system-x86_64 -drive file=image.vhd,format=vpc -bios ovmf\ovmf.fd

