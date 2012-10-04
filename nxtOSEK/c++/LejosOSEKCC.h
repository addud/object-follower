#ifndef _LEJOSOSEKCC_H
#define _LEJOSOSEKCC_H

#include "kernel.h"

enum {
  POWER_OFF,
  POWER_STROBE,
  POWER_ON
};

enum {
  S1,
  S2,
  S3,
  S4
};

enum {
  MOTOR_A,
  MOTOR_B,
  MOTOR_C
};

#ifndef N_SENSORS
const int N_SENSORS = 4;
#endif

const int N_SLEEPERS = 8;

extern TaskType sensorWaitID[N_SENSORS];
extern bool sensorWaiting[N_SENSORS];
extern TaskType sleeperID[N_SLEEPERS];
extern unsigned int sleepCounter[N_SLEEPERS];
extern bool isSleeping[N_SLEEPERS];

extern "C++" {
  void sensorSleep(unsigned char port);
  void sleep(unsigned int duration);
}

#endif
