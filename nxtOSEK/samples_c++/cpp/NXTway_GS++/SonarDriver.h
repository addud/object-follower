//
// SonarDriver.h
//

#ifndef SONARDRIVER_H_
#define SONARDRIVER_H_

#include "SonarSensor.h"
#include "Vector.h"
using namespace ecrobot;

#include "Driver.h"

extern "C"
{
	#include "ecrobot_interface.h"
};

class SonarDriver: public Driver
{
public:
	SonarDriver(void): mObstacle(false) {}

	// Get driver request
	virtual Driver::eDriverRequest getRequest(void);

	// Get command for obstacle avoidance
	virtual VectorT<S16> getCommand(void);

	// Check obstacles by using a Sonar Sensor
	void checkObstacles(SonarSensor& sonar);

private:
	bool mObstacle;
};

#endif /*OBSTACLEAVOIDANCE_H_*/
