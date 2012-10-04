echo Executing NeXTTool to upload tetrix.rxe...
wineconsole ~/LEGO/nxtOSEK/NeXTTool.exe /COM=usb -download=tetrix.rxe
wineconsole ~/LEGO/nxtOSEK/NeXTTool.exe /COM=usb -listfiles=tetrix.rxe
echo NeXTTool is terminated.
