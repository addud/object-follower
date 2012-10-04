echo Executing NeXTTool to upload helloworld_OSEK.rxe...
wineconsole ~/LEGO/nxtOSEK/NeXTTool.exe /COM=usb -download=helloworld_OSEK.rxe
wineconsole ~/LEGO/nxtOSEK/NeXTTool.exe /COM=usb -listfiles=helloworld_OSEK.rxe
echo NeXTTool is terminated.
