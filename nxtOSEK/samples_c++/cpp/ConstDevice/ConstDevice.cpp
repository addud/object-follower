//
// ConstDevice.cpp
//

#include "ConstDevice.h"

// File scoped device objects
static LightSensor  light(PORT_1, false); // lamp off
static SonarSensor  sonar(PORT_2);
static SoundSensor    mic(PORT_3);
static TouchSensor  touch(PORT_4);
static Motor motorA(PORT_A, false); // float

// Constant(read-only) devices reference
const LightSensor& crLight  = light;  // Lamp on/off is restricted
const SonarSensor& crSonar  = sonar;  // no difference
const SoundSensor&   crMic  = mic;    // DBA on/off is restricted
const TouchSensor& crTouch  = touch;  // no difference
const       Motor& crMotorA = motorA; // only getCount

