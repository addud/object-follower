// SpritePC.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "..\App.h"
#include "..\Stub.h"

int _tmain(int argc, _TCHAR* argv[])
{
	App app;
	display_gui();

	app.init();
	while(1)
		app.update();
	return 0;
}

