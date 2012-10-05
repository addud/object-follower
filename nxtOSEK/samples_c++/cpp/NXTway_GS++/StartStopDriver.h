//
// StartStopDriver.h
//

#ifndef STARTSTOPDRIVER_H_
#define STARTSTOPDRIVER_H_

#include "TouchSensor.h"
using namespace ecrobot;

#include "Driver.h"

extern "C"
{
	#include <string.h>
	#include "ecrobot_interface.h"
};

class StartStopDriver: public Driver
{
public:
	StartStopDriver(const TouchSensor& touch):
		mrTouch(touch), mDriverRequest(Driver::STOP), mTouchState(false),
		mStateIndex(0) { memset(mTouchStates, mTouchState, N_TOUCH_STATES); }

	// Get driver request
	virtual Driver::eDriverRequest getRequest(void);

private:
	static const int N_TOUCH_STATES = 10; // used for Touch Sensor bouncer
	const TouchSensor& mrTouch;
	Driver::eDriverRequest mDriverRequest;
	bool mTouchState;
	bool mTouchStates[N_TOUCH_STATES];
	int mStateIndex;
};

#endif /* STARTSTOPDRIVER_H_ */
