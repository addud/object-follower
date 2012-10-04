//
// LineTraceDriver.h
//

#ifndef LINETRACEDRIVER_H_
#define LINETRACEDRIVER_H_

#include "Vector.h"
#include "LightSensor.h"
using namespace ecrobot;

#include "Driver.h"

class LineTraceDriver: public Driver
{
public:
	LineTraceDriver(LightSensor& light): mrLight(light) {}

	VectorT<S16> getCommand(void);

private:
	static const S16 WHITE = 500; // Light Sensor value for white
	static const S16 BLACK = 700; // Light Sensor value for black
	LightSensor& mrLight;
};

#endif
