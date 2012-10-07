//
// GamePadDriver.cpp
//

#include "GamePadDriver.h"
using namespace ecrobot;

//=============================================================================
// Get robot drive command
VectorT<S16> GamePadDriver::getCommand(void)
{
	VectorT<S16> cmd = VectorT<S16>(0,0);
	if (mrGamePad.isConnected())
	{
		VectorT<S8> gpCmd = mrGamePad.get();
		cmd.mX = static_cast<S16>(-gpCmd.mX); // reverse the direction of forward command
		cmd.mY = static_cast<S16>(gpCmd.mY);
	}
	return cmd;
}

//=============================================================================
// Driver's status
Driver::eDriverRequest GamePadDriver::getRequest(void)
{
	Driver::eDriverRequest req = Driver::NO_REQ;
	if (mrGamePad.isConnected())
	{
		req = Driver::DRIVE;
	}
	return req;
}

