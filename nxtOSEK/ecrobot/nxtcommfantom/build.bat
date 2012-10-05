set FANTOM=C:\cygwin\fantom

cl /I . /I %FANTOM%\includes /I ..\bios /I ..\..\lejos_nxj\src\nxtvm\platform\nxt %FANTOM%\targets\win32U\i386\msvc71\release\fantom.lib main_appflash.cpp nxtcommfantom.cpp /o ..\..\bin\appflash.exe

@echo off
rm *.obj
