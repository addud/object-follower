//
// Driver.h
//

#ifndef DRIVER_H_
#define DRIVER_H_

#include "Vector.h"
using namespace ecrobot;

extern "C"
{
	#include "ecrobot_interface.h"
};

class Driver
{
/*
 * Robot driver base class for the robot controlled by forward and turn commands. (e.g. NXTway-GS, Tribot)
 */
public:
	/**
	 * Robot driver request enum.
	 */
	enum eDriverRequest
	{
		NO_REQ, /**< No request */
		STOP,	/**< Request to stop the robot */
		START,	/**< Request to start controlling the robot */
		DRIVE	/**< Request to drive the robot according to the command to be acquired by using getCommand API */
	};

	/**
	 * Constructor.
	 */
	Driver(){}

	/**
	 * Destructor.
	 */
	virtual ~Driver(){}

	/**
	 * Reset the driver to re-start it.
	 */
	virtual void reset(void){} // By default, do nothing

	/**
	 * Get the driver request. The Driver base class always returns DRIVE request.
	 * @return Robot driver request enum
	 */
	virtual eDriverRequest getRequest(void) { return Driver::DRIVE; } // By default, always return DRIVER request

	/**
	 * Driver request command. The Driver base class just returns (0,0) command.
	 * @return forward and turn command
	 */
	virtual VectorT<S16> getCommand(void){ return VectorT<S16>(0,0); } // By default, always return zero forward/turn
};

#endif /*DRIVER_H_*/
