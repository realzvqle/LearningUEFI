@echo off



cl /c /GS- /Gd /Zl /Oi /Os /Oy /TC kernel.c
link kernel.obj /BASE:0x100000 /ENTRY:KiEntry /SUBSYSTEM:NATIVE /OUT:../root/kernel.exe
cd ..
exit