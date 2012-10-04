//
// ConstDevice.h
//

#ifndef CONSTDEVICE_H_
#define CONSTDEVICE_H_

// ECRobot++ API
#include "LightSensor.h"
#include "SonarSensor.h"
#include "SoundSensor.h"
#include "TouchSensor.h"
#include "Motor.h"
using namespace ecrobot;

// Constant(read-only) devices
extern const LightSensor& crLight;  // Lamp on/off is restricted
extern const SonarSensor& crSonar;  // no difference
extern const SoundSensor& crMic;    // DBA on/off is restricted
extern const TouchSensor& crTouch;  // no difference
extern const       Motor& crMotorA; // only getCount

#endif
