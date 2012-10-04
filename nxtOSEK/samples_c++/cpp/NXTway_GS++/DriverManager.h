//
// DriverManager.h
//

#ifndef DRIVERMANAGER_H_
#define DRIVERMANAGER_H_

#include "Driver.h"

extern "C"
{
	#include "ecrobot_interface.h"
};

class DriverManager
{
/*
 * Robot drivers manager class.
 */
public:
	/**
	 * Constructor.
	 */
	DriverManager();

	/**
	 * Destructor.
	 */
	~DriverManager();

	/**
	 * Create the driver registration table.
	 * @param numOfDrivers Number of drivers to be registered.
	 * @return true:succeeded/false:failed
	 */
	bool createDriverTable(UINT numOfDrivers);

	/**
	 * Delete the driver registration table.
	 */
	void deleteDriverTable(void);

	/**
	 * Add a driver to the driver registration table.
	 * Note that the order of the driver registrations is equal to the priority of the drivers.
	 * (e.g. The first registered driver is the highest priority)
	 * @param driver Driver to be registered in the table.
	 * @return true:succeeded/false:failed
	 */
	bool add(Driver* driver);

	/**
	 * Update the drivers in the table.
	 * Note that this function updates all drivers status, so it should be called before getting the latest status
	 * of the drivers.
	 * @return true:driver has a request/false:no driver has a request
	 */
	bool update(void);

	/**
	 * Get the request sent from the driver which has higher priority.
	 * @return Driver request.
	 */
	Driver::eDriverRequest getRequest(void) const;

	/**
	 * Get the command sent from the driver which has higher priority.
	 * @return Driver command vector(mX,mY).
	 */
	VectorT<S16> getCommand(void) const;

	/**
	 * Get the driver table index id of the driver which has a request.
	 * @return Driver table index id (-1 means that no driver had a request)
	 */
	SINT getById(void) const;

	/**
	 * Get the driver which has a request.
	 * @return Driver which has a request.
	 */
	Driver* get(void) const;

private:
	SINT mSizeOfTable;
	SINT mNumOfDrivers;
	Driver** mDriverAddressTable;
	SINT mDriverId;
	Driver::eDriverRequest mDriverReq;
	VectorT<S16> mDriverCmd;
};

#endif /* DRIVERMANAGER_H_ */
