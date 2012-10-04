//
// New.cpp
//
// Simple new/delete overload to reduce the memory consumption.
// Note that there is NO exception handling and NOT thread safe.
//
// Copyright 2009 by Takashi Chikamasa, Jon C. Martin and Robert W. Kramer
//

#include <stdlib.h>

//=============================================================================
// new operators overload
//

// normal single new
void* operator new(size_t size) throw()
{
	if (size < 1)
	{
		size = 1; // size 0 is set as size 1
	}
	return malloc(size);
}

// normal array new
void* operator new [](size_t size) throw()
{
	if (size < 1)
	{
		size = 1; // size 0 is set as size 1
	}
	return malloc(size);
}

// default placement version of single new
void* operator new(size_t, void* ptr) throw() { return ptr; }

// default placement version of array new
void* operator new [](size_t, void* ptr) throw() { return ptr; }


//=============================================================================
// delete operators overload
//

// normal single delete
void operator delete(void* ptr) throw() { free(ptr); }

// normal array delete
void operator delete [](void* ptr) throw() { free(ptr); }

// default placement version of single delete
void operator delete(void*, void*) throw() { /* do nothing */ }

// default placement version of array delete
void operator delete [](void*, void*) throw() { /* do nothing */ }

