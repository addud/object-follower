//
// DriverManager.cpp
//

#include "DriverManager.h"

DriverManager::DriverManager():
mSizeOfTable(0),
mNumOfDrivers(0),
mDriverAddressTable(0),
mDriverId(-1),
mDriverReq(Driver::NO_REQ),
mDriverCmd(VectorT<S16>(0,0))
{}

DriverManager::~DriverManager(void)
{
	this->deleteDriverTable();
}

bool DriverManager::createDriverTable(UINT numOfDrivers)
{
	bool ret = false;
	if (mSizeOfTable == 0)
	{
		mDriverAddressTable = new Driver*[numOfDrivers];
		if (mDriverAddressTable != 0)
		{
			mSizeOfTable = numOfDrivers;
			mNumOfDrivers = 0;
			ret = true;
		}
	}
	return ret;
}

void DriverManager::deleteDriverTable(void)
{
	mSizeOfTable = 0;
	mDriverAddressTable = 0;
	mDriverId = -1;
	mDriverReq = Driver::NO_REQ;
	mDriverCmd = VectorT<S16>(0,0);
	if (mDriverAddressTable != 0)
	{
		delete [] mDriverAddressTable;
	}
}

bool DriverManager::add(Driver* driver)
{
	bool ret = false;
	if (mNumOfDrivers < mSizeOfTable)
	{
		mDriverAddressTable[mNumOfDrivers++] = driver;
		ret = true;
	}
	return ret;
}

bool DriverManager::update(void)
{
	mDriverReq = Driver::NO_REQ;
	mDriverCmd = VectorT<S16>(0,0);
	for (mDriverId=0; mDriverId<mNumOfDrivers; mDriverId++)
	{
		mDriverReq = mDriverAddressTable[mDriverId]->getRequest();
		if (mDriverReq != Driver::NO_REQ)
		{
			mDriverCmd = mDriverAddressTable[mDriverId]->getCommand();
			return true;
		}
	}
	mDriverId = -1;
	return false;
}

VectorT<S16> DriverManager::getCommand(void) const
{
	return mDriverCmd;
}

Driver::eDriverRequest DriverManager::getRequest(void) const
{
	return mDriverReq;
}

SINT DriverManager::getById(void) const
{
	return mDriverId;
}

Driver* DriverManager::get(void) const
{
	if (mDriverId >= 0 && mDriverId < mNumOfDrivers)
	{
		return mDriverAddressTable[mDriverId];
	}
	return 0;
}


