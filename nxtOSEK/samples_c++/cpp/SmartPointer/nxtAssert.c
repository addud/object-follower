#include "nxtAssert.h"
#include "ecrobot_interface.h"

void __nxtAssert(const char *file, int line, const char *exp)
{
	display_clear(0);
	display_goto_xy(0, 0);
	display_string("assert");
	display_goto_xy(0, 1);
	display_string("File: ");
	display_string(file);
	display_goto_xy(0, 2);
	display_string("Line: ");
	display_int(line,0);
	display_goto_xy(0, 3);
	display_string(exp);
	display_update();

#ifdef NXT_WARN_ASSERT
	display_goto_xy(0, 3);
	display_string("Press ENTER");
#endif
	while(true)
	{
#ifdef NXT_WARN_ASSERT
		if(ecrobot_is_ENTER_button_pressed())
		{
			display_clear(0);
			display_goto_xy(0, 0);
			return;
		}
#endif
	}
}

