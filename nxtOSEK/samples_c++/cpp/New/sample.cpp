/* sample.cpp for TOPPERS/ATK(OSEK) */ 

// ECRobot++ API
#include "Lcd.h"
#include "Clock.h"
using namespace ecrobot;

extern "C"
{
#include <string.h>

#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

Lcd lcd;

// test classes
class Hoge
{
private:
	U8 buf[256]; // certain size of memory to be heaped
public:
	Hoge() { lcd.putf("sn", "new Hoge"); }

	virtual ~Hoge(){ lcd.putf("ns", "delete Hoge"); }

	void func(void) { lcd.putf("s", "func "); }
};

class Hoge1: public Hoge
{
public:
	Hoge1() { lcd.putf("sn", "new Hoge1"); }
	
	~Hoge1() { lcd.putf("ns", "delete Hoge1");}
};

// nxtOSEK hook to be invoked from an ISR in category 2
void user_1ms_isr_type2(void)
{
	SleeperMonitor(); // needed for I2C device and Clock classes
}

TASK(TaskMain)
{
	Clock clock;

	U32 cnt = 0;
	while(1)
	{
		lcd.clear();
		lcd.putf("dn", cnt,0);
		if ((cnt++ << 31) == 0)
		{
			// single new/delete
			Hoge1* hoge1 = new Hoge1;

			hoge1->func();

			delete hoge1;
		}
		else
		{
			// array new/delete
			Hoge* hoges = new Hoge[3];

			hoges[0].func();
			hoges[1].func();
			hoges[2].func();

			delete [] hoges;
		}
		lcd.disp();
		clock.wait(2000);
	}
}
}
