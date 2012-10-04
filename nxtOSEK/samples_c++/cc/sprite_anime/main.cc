#include "app.h"

extern "C"
{
#include "kernel.h"
#include "ecrobot_interface.h"

void user_1ms_isr_type2(void){/* do nothing */}

TASK(Task1)
{
	App app;

	app.init();
	while(1)
	{
		app.update();
	}
}

}

