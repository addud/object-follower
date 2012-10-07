#include "app.h"

extern "C" {

#include "ecrobot_interface.h"
#include "kernel.h"
#include "string.h"
}


extern "C" 
{
/* OSEK declarations */
DeclareTask(Task1);

/* LEJOS OSEK hook to be invoked from an ISR in category 2 */
void user_1ms_isr_type2(void){}

	TASK(Task1)
	{
		App app;

		app.init();
		while(1)
			app.update();

		TerminateTask();
	}
}

