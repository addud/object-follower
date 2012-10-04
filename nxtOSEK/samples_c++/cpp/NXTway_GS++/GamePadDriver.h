//
// GamePadDriver.h
//

#ifndef GAMEPADDRIVER_H_
#define GAMEPADDRIVER_H_

#include "GamePad.h"
#include "Vector.h"
using namespace ecrobot;

#include "Driver.h"

extern "C"
{
	#include "ecrobot_interface.h"
};

class GamePadDriver: public Driver
{
public:
	GamePadDriver(GamePad& gamePad): mrGamePad(gamePad) {}

	// Get driver request
	virtual Driver::eDriverRequest getRequest(void);

	// Get command for remote control
	virtual VectorT<S16> getCommand(void);

private:
	GamePad& mrGamePad;
};

#endif /*REMOTE_H_*/
