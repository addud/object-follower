//
// SonarDriver.cpp
//

#include "SonarDriver.h"
using namespace ecrobot;

//=============================================================================
// get command for obstacle avoidance
VectorT<S16> SonarDriver::getCommand(void)
{
	VectorT<S16> cmd = VectorT<S16>(0, 0);
	if (mObstacle)
	{
		cmd = VectorT<S16>(-100, 0);
	}
	return cmd;
}

//=============================================================================
// A drive request
Driver::eDriverRequest SonarDriver::getRequest(void)
{
	Driver::eDriverRequest req = Driver::NO_REQ;
	if (mObstacle)
	{
		req = Driver::DRIVE;
	}
	return req;
}

//=============================================================================
// Check obstacles using a Sonar Sensor
void SonarDriver::checkObstacles(SonarSensor& sonar)
{
	mObstacle = false;
	if (sonar.getDistance() <= 30)
	{
		mObstacle = true;
	}
}
