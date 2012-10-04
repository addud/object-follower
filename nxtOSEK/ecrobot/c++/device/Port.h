//
// Port.h
//
// Copyright 2009 by Takashi Chikamasa, Jon C. Martin and Robert W. Kramer
//

#ifndef PORT_H_
#define PORT_H_

/**
 * @file Port.h
 * @brief Motor/Sensor port related enums and defines.
 */

/**
 * @enum ePortS Enum for NXT sensor ports.
 */
enum ePortS
{
	PORT_1 = 0, /**< Enum value for NXT sensor port 1 */
	PORT_2,     /**< Enum value for NXT sensor port 2 */
	PORT_3,     /**< Enum value for NXT sensor port 3 */
	PORT_4      /**< Enum value for NXT sensor port 4 */
};

/**
 * @enum ePortM Enum for NXT motor ports
 */
enum ePortM
{
	PORT_A = 0, /**< Enum value for NXT motor port A */
	PORT_B,     /**< Enum value for NXT motor port B */
	PORT_C      /**< Enum value for NXT motor port C */
};

/**
 * @enum ePower Enum for power supply to NXT sensor port.
 */
enum ePower
{
	POWER_OFF = 0,          /**< Enum value for no power supply */
	POWER_LOWSPEED_9V = 1,  /**< Enum value to supply 9V to sensor */
	POWER_LOWSPEED = 2      /**< Enum value for I2C device */
};

/** Number of sensor ports */
#define NUM_PORT_S (4) // number of sensor ports

/** Number of motor ports */
#define NUM_PORT_M (3) // number of motor ports

#endif
