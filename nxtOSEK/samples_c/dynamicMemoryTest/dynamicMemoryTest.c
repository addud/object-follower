/* dynamicMemoryTest.c */ 
#include <stdlib.h>
#include <string.h>

#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

/* nxtOSEK hook to be invoked from an ISR in category 2 */
void user_1ms_isr_type2(void){ /* do nothing */ }

const CHAR *str[2] = {"HEAP MEMORY: 1st", "HEAP MEMORY: 2nd"};

TASK(OSEK_Task_Background)
{
	SINT i;
	CHAR *mem[2];
	
	while(1){
		/* heap memory for strings */
		for (i = 0; i < 2; i++) {
			mem[i] = (CHAR *)malloc(strlen(str[i]));
			if(mem[i] == NULL) {
				display_clear(0);
				display_goto_xy(0, 0);
				display_string("HEAP MEMORY: Err");
				display_update();
			}
			else {
				memcpy(mem[i], str[i], strlen(str[i])); 
				display_clear(0);
				display_goto_xy(0, 0);
				display_string(mem[i]);
				display_goto_xy(0, 1);
				display_hex((U32)mem[i], 0);
				display_update();
			}
			systick_wait_ms(1000); /* wait for 1000msec */
		}

		/* release heaped memory for the strings */
		for (i = 0; i < 2; i++) {
			if(mem[i] != NULL) {
				free(mem[i]);
			}
		}
	}
}
