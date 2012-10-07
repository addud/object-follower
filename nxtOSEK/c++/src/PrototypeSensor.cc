//
// PrototypeSensor.cc
//
// HiTechnic prototype sensor class
//
// Written 23-feb-2008 by rwk
//
// Copyright 2007, 2008 by Robert W. Kramer and Takashi Chikamasa
//

#include "PrototypeSensor.h"

//=============================================================================
// PrototypeSensor::PrototypeSensor(unsigned char _port,unsigned int _sample)
//   constructor for sensor object
//
// Parm
//   _port - port number sensor is connected to
//   _sample - sample rate (default 10ms)
//

PrototypeSensor::PrototypeSensor(unsigned char _port,unsigned int _sample) {

  //
  // remember the port number for data transfers
  //

  port = _port;

  //
  // turn on the power
  //

  nxt_avr_set_input_power(port,POWER_ON);
  i2c_enable(port);

  //
  // remember the sample rate
  //

  setSampleRate(_sample);

}



//=============================================================================
// PrototypeSensor::~PrototypeSensor(void)
//   class destructor
//

PrototypeSensor::~PrototypeSensor(void) {

  //
  // turn off power. Not sure if this is needed here.
  //

  nxt_avr_set_input_power(port,POWER_OFF);

  //
  // disable the port. This is necessary.
  //

  i2c_disable(port);
}

//=============================================================================
// void setSampleRate(unsigned int rate)
//   set sample rate, forcing it into the range of 4 - 100ms
//

void PrototypeSensor::setSampleRate(unsigned int rate) {
  unsigned char buf;

  sampleRate = rate;

  //
  // make sure it's in the valid range
  //

  if (sampleRate < 4)
    sampleRate = 4;

  if (sampleRate > 100)
    sampleRate = 100;

  //
  // wait for port to become available
  //

  if (i2c_busy(port))
    sensorSleep(port);

  //
  // initiate data transfer
  //

  buf = (unsigned char)(rate & 0xff);

  i2c_start_transaction(port,1,0x4f,1,&buf,1,1);

  //
  // wait for port to complete the transfer
  //

  if (i2c_busy(port))
    sensorSleep(port);

}

//=============================================================================
// void setDigitalPorts(unsigned char dir)
//   set the direction of the six digital I/O ports
//
// a 1 bit in position i (0 <= i <= 5) indicates that port i is configured for
// output; a 0 bit indicates the port is configured for input.
//

void PrototypeSensor::setDigitalPorts(unsigned char dir) {

  digitalDir = dir;

  //
  // wait for port to become available
  //

  if (i2c_busy(port))
    sensorSleep(port);

  //
  // initiate data transfer
  //

  i2c_start_transaction(port,1,0x4e,1,&dir,1,1);

  //
  // wait for port to complete the transfer
  //

  if (i2c_busy(port))
    sensorSleep(port);

}

//=============================================================================
// void writeDigitalData(unsigned char data)
//   send output to digital I/O ports that are configured for output
//

void PrototypeSensor::writeDigitalData(unsigned char data) {

  data &= digitalDir; // mask off input bits

  //
  // wait for port to become available
  //

  if (i2c_busy(port))
    sensorSleep(port);

  //
  // initiate data transfer
  //

  i2c_start_transaction(port,1,0x4d,1,&data,1,1);

  //
  // wait for port to complete the transfer
  //

  if (i2c_busy(port))
    sensorSleep(port);
}

//=============================================================================
// unsigned char readDigitalData(void)
//   read digital I/O ports that are configured for input
//

unsigned char PrototypeSensor::readDigitalData(void) {
  unsigned char data;

  //
  // wait for port to become available
  //

  if (i2c_busy(port))
    sensorSleep(port);

  //
  // initiate data transfer
  //

  i2c_start_transaction(port,1,0x4c,1,&data,1,0);

  //
  // wait for port to complete the transfer
  //

  if (i2c_busy(port))
    sensorSleep(port);

  data = (data & ~digitalDir) & 0xff;

  return data;
}

//=============================================================================
// void readAnalogData(unsigned int analogPorts[5])
//   read all ADC ports
//
// values are 0 - 1023, 1023 == 3.3v
//

void PrototypeSensor::readAnalogData(unsigned int analogPorts[5]) {
  unsigned char buf[10];
  int i;

  //
  // wait for port to become available
  //

  if (i2c_busy(port))
    sensorSleep(port);

  //
  // initiate data transfer
  //

  i2c_start_transaction(port,1,0x42,1,buf,10,0);

  //
  // wait for port to complete the transfer
  //

  if (i2c_busy(port))
    sensorSleep(port);

  for (i=0;i<5;i++)
    analogPorts[i] = ((unsigned int)buf[2*i] << 2) |
      ((unsigned int)buf[2*i+1] & 0x03);
}

//=============================================================================
// unsigned int readAnalogData(int analogPort)
//   read one ADC port
//

unsigned int PrototypeSensor::readAnalogData(int analogPort) {
  unsigned char buf[10];
  unsigned int data;

  //
  // wait for port to become available
  //

  if (i2c_busy(port))
    sensorSleep(port);

  //
  // initiate data transfer
  //

  i2c_start_transaction(port,1,0x42,1,buf,10,0);

  //
  // wait for port to complete the transfer
  //

  if (i2c_busy(port))
    sensorSleep(port);

  data = ((unsigned int)buf[2*analogPort] << 2) |
    ((unsigned int)buf[2*analogPort+1] & 0x03);

  return data;
}
