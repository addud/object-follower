//#include "kernel.h"
//#include "kernel_id.h"
#include "ecrobot_interface.h"

#define ENABLE_TRACKING 0x45
#define DISABLE_TRACKING 0x44
#define SORT_BY_SIZE 0x41
#define TRACK_OBJECTS 0x42

/* Prototypes */
void init_nxtcam(U8 port_id);
int send_nxtcam_command(U8 port_id, U8 command);
int request(U8 port_id);
U8* getdata();
void term_nxtcam(U8 port_id);

int getbiggestrect(U8 pcolorid, int minarea);
int getX(U8 rectindex);
int getY(U8 rectindex);
int getWidth(U8 rectindex);
int getHeight(U8 rectindex);
int getArea(U8 rectindex);
