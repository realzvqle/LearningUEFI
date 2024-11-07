@echo off

rd root /s /q
cd bootloader
start clean.bat
cd ..
cd image
start clean.bat
cd ..