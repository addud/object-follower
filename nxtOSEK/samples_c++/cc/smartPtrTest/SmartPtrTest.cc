#include "scoped_ptr.hpp"
#include "scoped_array.hpp"

#include <memory>	//auto_ptr
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

extern "C" {

#include "ecrobot_interface.h"
#include "kernel.h"

//test class
class Foo
{
public:
	Foo(){	display_string("Foo::Foo()"); }
	~Foo(){ display_string("Foo::~Foo()"); }
	void doNothing(){}
};

void updateWaitReset()
{
	display_update();
	systick_wait_ms(5000);
	display_clear(0);
	display_goto_xy(0, 0);
}

DeclareTask(MainTask);
 
TASK(MainTask)
{
	display_clear(0);
	display_goto_xy(0, 0);

	display_string("new/delete");

	display_goto_xy(0, 1);
	Foo *foo = new Foo();
	display_goto_xy(0, 7);
	display_hex((U32)foo, 8);
	display_goto_xy(0, 2);
	delete foo;

	updateWaitReset();

	//std::auto_ptr
	{
		display_string("auto_ptr");
		display_goto_xy(0, 1);
		std::auto_ptr<Foo> autoPtr(new Foo());
		display_goto_xy(0, 7);
		display_hex((U32)autoPtr.get(), 8);
		display_goto_xy(0, 2);

		//autoPtr deleted automatically when the current scope ends
	}

	updateWaitReset();

	//transfer from std::auto_ptr to boost::scoped_ptr
	{
		display_string("auto->scoped");
		display_goto_xy(0, 1);
		std::auto_ptr<Foo> autoPtr(new Foo());
		display_goto_xy(0, 7);

		//show that the raw pointer address is the same with get()
		display_hex((U32)autoPtr.get(), 8);
		boost::scoped_ptr<Foo> scopedPtr(autoPtr);
		
		display_hex((U32)scopedPtr.get(), 8);
		display_goto_xy(0, 2);

		//scoped_ptr deleted automatically when the current scope ends
	}

	updateWaitReset();
	
	//boost::scoped_array
	{
		display_string("scoped_array");
		display_goto_xy(0, 1);
		boost::scoped_array<Foo> scopedArray(new Foo[2]);
		display_goto_xy(0, 2);

		//scoped_array deleted automatically when the current scope ends
	}

	//should produce an assert for null deref
	boost::scoped_ptr<Foo> scopedPtr;
	scopedPtr->doNothing();

	display_update();

	while(true){}
}
}


