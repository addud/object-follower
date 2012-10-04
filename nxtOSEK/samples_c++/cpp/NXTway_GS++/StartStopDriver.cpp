//
// StartStopDriver.cpp
//

#include "StartStopDriver.h"
using namespace ecrobot;

Driver::eDriverRequest StartStopDriver::getRequest(void)
{
	bool offToOn = false;
	// As the result of an experiment with a NXT. This bouncer seems to be needed to
	// detect the status of Touch Sensor in stable way.
	if (mStateIndex == N_TOUCH_STATES)
	{
		mStateIndex = 0;
	}
	mTouchStates[mStateIndex++] = mrTouch.isPressed();
	for (int i = 1; i < N_TOUCH_STATES; i++)
	{
		if (mTouchStates[i-1] != mTouchStates[i]) break; // bounce occurred

		if (i == N_TOUCH_STATES-1) // all states becomes the same
		{
			if (!mTouchState && mTouchStates[i])
			{
				offToOn = true; // Touch Sensor: OFF->ON
			}
			mTouchState = mTouchStates[i];
		}
	}

	// driver state machine
	switch(mDriverRequest)
	{
		case Driver::STOP:
			if (offToOn)
			{
				mDriverRequest = Driver::START;
			}
			break;
		case Driver::NO_REQ:
			if (offToOn)
			{
				mDriverRequest = Driver::STOP;
			}
			break;
		case Driver::START:
		default:
			mDriverRequest = Driver::NO_REQ;
			break;
	}
	return mDriverRequest;
}


