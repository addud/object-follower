//
// LineTraceDriver.cpp
//

#include "LineTraceDriver.h"

VectorT<S16> LineTraceDriver::getCommand()
{
	VectorT<S16> cmd;
	if (mrLight.get() <= (WHITE + BLACK)/2)
	{
		cmd = VectorT<S16>(50, 50); // Turn right
	}
	else
	{
		cmd = VectorT<S16>(50,-50); // Turn left
	}
	return cmd;
}
