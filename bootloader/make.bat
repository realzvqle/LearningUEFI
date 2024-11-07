@echo off


if exist ..\image\image.vhd del ..\image\image.vhd
cl /c /Zl /I"C:\build\efi\includes" /I"C:\build\efi\includes\efi\em64t" main.c
link /entry:EfiEntry /dll /IGNORE:4086 main.obj
fwimage app main.dll ..\root\EFI\BOOT\bootx64.efi
cd ..
exit
