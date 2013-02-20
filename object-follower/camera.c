/* ---------------------------------------------------------------------------
 ** camera.c
 **
 ** Mindsensors NxtCam driver for NxtOsek.
 **
 ** Author: Adrian Dudau
 ** Acknowledgments: based on code from Takashi Chikamasa for the i2C communication.
 ** -------------------------------------------------------------------------*/

//#include "mymath.h"
//#include "kernel.h"
//#include "kernel_id.h"
#include "ecrobot_interface.h"
#include "camera.h"

#define MYABS(x)	(((x) >= 0)? (x):-(x));

#define ADDRESS 0x01


/* Data received from the camera is stored in a static array.
 * TODO: Might be better to do it in a reentrant way so as to allow several
 * cameras. Better: do it all in C++...
 *
 */
static U8 nxtcamdata[41];


/*
 * Initialize the specified port to be used for I2C communication
 * NOTE: user defined I2C sensor initialize function should be implemented
 *       in user defined an OSEK initialization Task (not in LEJOS OSEK device init hook).
 *       because device init hook is invoked in a loop while the button instruction screen is appeared.
 */
void init_nxtcam(U8 port_id)
{
	nxt_avr_set_input_power(port_id, 2);
	i2c_enable(port_id);

	int i;
	for (i = 0; i < 41; i++)
		nxtcamdata[i] = 0;
}


static U8 nxtcambuffer[8];
SINT send_nxtcam_command(U8 port_id, U8 command)
{
	while (i2c_busy(port_id) != 0)
		;
	nxtcambuffer[0] = command;
	/* write Single shot command */
	SINT ret = i2c_start_transaction(port_id, ADDRESS, 0x41, 1, nxtcambuffer,
			1, 1);
	return ret;
}

/*
 *
 * This API implementation for I2C communication might be different from
 * I2C sensor communication examples in other NXT programming languages.
 * Others use a wait until data transaction is finished after sending a request.
 * However, it might not be acceptable for real-time control application. So we
 * introduce one sampling delay to avoid waiting for the completion of the data acqusition.
 */

// For debugging, usefull to check if communication with the NxtCam is actually happening.
static int nxtcamtransaccounter = 0;

int request(U8 port_id)
{
	if (i2c_busy(port_id) == 0) /* check the status of I2C comm. */
	{
		/* i2c_start_transaction just triggers an I2C transaction,
		 * actual data transaction between ARM7 and an NxtCam is done
		 * by an ISR after this, so there is one execution cycle
		 * delay for consistent data acquistion
		 */
		SINT ret = i2c_start_transaction(port_id, ADDRESS, 0x42, 1, nxtcamdata,
				41, 0);
		if (ret == 0)
			nxtcamtransaccounter++;
	}
	return nxtcamtransaccounter;
}

U8* getdata()
{
	return nxtcamdata;
}

/*
 * Returns the index of the biggest rectangle of color id pcolorid
 * Returns -1 if no rectangle of color id pcolorid is found, or all
 * rectangle are strictly smaller than pminarea.
 */
int getbiggestrect(U8 pcolorid, int pminarea)
{
	int rectindex = -1;
	int i;
	int maxarea = pminarea;
	for (i = 0; i < nxtcamdata[0]; i++)
	{
		int colorid = (int) nxtcamdata[1 + 5 * i + 0];

		if (colorid == pcolorid)
		{

			int area = getArea(i);

			if (area >= maxarea)
			{
				maxarea = area;
				rectindex = i;
			}
		}
	}

	return rectindex;
}

/*
 * Returns the X coordinate of the center for rectangle of index rectindex.
 */
int getX(U8 rectindex)
{
	int xul = (int) nxtcamdata[5 * rectindex + 1 + 1];
	int xlr = (int) nxtcamdata[5 * rectindex + 1 + 3];
	return (xlr + xul) / 2;
}

/*
 * Returns the Y coordinate of the center for rectangle of index rectindex.
 */
int getY(U8 rectindex)
{
	int yul = (int) nxtcamdata[5 * rectindex + 1 + 2];
	int ylr = (int) nxtcamdata[5 * rectindex + 1 + 4];
	return (yul + ylr) / 2;
}

/*
 * Returns the width of the rectangle of index rectindex.
 */
int getWidth(U8 rectindex) {
	int xul = (int) nxtcamdata[5 * rectindex + 1 + 1];
	int xlr = (int) nxtcamdata[5 * rectindex + 1 + 3];

	return MYABS(xlr - xul);
}

/*
 * Returns the height of the rectangle of index rectindex.
 */
int getHeight(U8 rectindex) {
	int yul = (int) nxtcamdata[5 * rectindex + 1 + 2];
	int ylr = (int) nxtcamdata[5 * rectindex + 1 + 4];

	return MYABS(ylr - yul);
}

/*
 * Returns the area of the rectangle of index rectindex.
 */
int getArea(U8 rectindex) {
	return getWidth(rectindex)*getHeight(rectindex);
}

/*
 * Terminate I2C communication on the specified port
 */
void term_nxtcam(U8 port_id)
{
	i2c_disable(port_id);
}
