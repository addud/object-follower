set FANTOM=C:\cygwin\fantom
set NXTCOMMFANTOM=C:\cygwin\nxtosek\ecrobot\nxtcommfantom

cl /I . /I .. /I %NXTCOMMFANTOM% /I %FANTOM%\includes %FANTOM%\targets\win32U\i386\msvc71\release\fantom.lib main_usbhost.cpp %NXTCOMMFANTOM%\nxtcommfantom.cpp /o usbhost.exe

@echo off
rm *.obj
