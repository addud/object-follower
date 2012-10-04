// Slightly modified Boost C++ library
#include "scoped_ptr.hpp"
#include "scoped_array.hpp"

#include <memory>	//auto_ptr
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ECRobot++ API
#include "Lcd.h"
#include "Clock.h"
using namespace ecrobot; 

Lcd lcd;

extern "C"
{
#include "ecrobot_interface.h"
#include "kernel.h"

// nxtOSEK hook to be invoked from an ISR in category 2
void user_1ms_isr_type2(void)
{
	SleeperMonitor(); // needed for I2C device and Clock classes
}

// test class
class Foo
{
public:
	Foo(){	lcd.putf("sn", "Foo::Foo()"); }
	~Foo(){ lcd.putf("sn", "Foo::~Foo()"); }
	void doNothing(){}
};

void updateWaitReset(Clock& c)
{
	lcd.disp();
	c.wait(5000);
	lcd.clear();
}

TASK(TaskMain)
{
	Clock nxtClock;

	lcd.clear();
	lcd.putf("sn", "new/delete");	
	Foo *foo = new Foo();
	lcd.cursor(0, 7);
	lcd.putf("x", (U32)foo,8);
	lcd.cursor(0, 2);
	delete foo;

	updateWaitReset(nxtClock);

	//std::auto_ptr
	{
		lcd.putf("sn", "auto_ptr");
		std::auto_ptr<Foo> autoPtr(new Foo());
		lcd.cursor(0, 7);
		lcd.putf("x", (U32)autoPtr.get(),8);
		lcd.cursor(0, 2);

		//autoPtr deleted automatically when the current scope ends
	}

	updateWaitReset(nxtClock);

	//transfer from std::auto_ptr to boost::scoped_ptr
	{
		lcd.putf("sn", "auto->scoped");
		std::auto_ptr<Foo> autoPtr(new Foo());

		lcd.cursor(0, 6);
		//show that the raw pointer address is the same with get()
		lcd.putf("sxn", "autoPtr ", (U32)autoPtr.get(),8);
		boost::scoped_ptr<Foo> scopedPtr(autoPtr);
		lcd.putf("sx",  "scpdPtr ", (U32)scopedPtr.get(),8);

		lcd.cursor(0, 2);

		//scoped_ptr deleted automatically when the current scope ends
	}

	updateWaitReset(nxtClock);
	
	//boost::scoped_array
	{
		lcd.putf("sn", "scoped_array");
		boost::scoped_array<Foo> scopedArray(new Foo[2]);
		lcd.cursor(0, 3);

		//scoped_array deleted automatically when the current scope ends
	}

	updateWaitReset(nxtClock);

	lcd.putf("s", "Assert test");
	lcd.disp();
	nxtClock.wait(2000);

	//should produce an assert for null deref
	boost::scoped_ptr<Foo> scopedPtr;
	scopedPtr->doNothing();
	lcd.disp();

	while(true){}
}
}


