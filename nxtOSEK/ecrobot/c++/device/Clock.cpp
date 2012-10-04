//
// Clock.cpp
//
// Copyright 2009 by Takashi Chikamasa, Jon C. Martin and Robert W. Kramer
//

#include "Clock.h"
using namespace ecrobot;


//=============================================================================
// Constructor
Clock::Clock(void)
:
mStartClock(systick_get_ms())
{}

//=============================================================================
// reset system tick to 0
void Clock::reset(void)
{
	mStartClock = systick_get_ms();
}

//=============================================================================
// get tick after app began
U32 Clock::now(void) const
{
	return (systick_get_ms() - mStartClock);
}

//=============================================================================
// wait in a loop for duration in msec
void Clock::wait(U32 duration)
{
	if (duration > 0)
	{
		systick_wait_ms(duration);
	}
}

//=============================================================================
// sleep running Task for duration in msec
void Clock::sleep(U32 duration)
{
	if (duration > 0)
	{
		Sleep(duration);
	}
}

