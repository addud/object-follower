#ifndef _NXTCOMMFANTOM_H_
#define _NXTCOMMFANTOM_H_

#include "fantom/iNXT.h"


#define MAX_DEV_ID		65
#define MAX_DEV_NAME    16
#define MAX_DATA_LEN	64

extern  int NXTCommFantom_find(ViChar* nxt_id);
extern nFANTOM100_iNXT NXTCommFantom_open(ViChar* nxt_id);
extern  int NXTCommFantom_getName(nFANTOM100_iNXT nxt, ViChar* name);
extern  int NXTCommFantom_connect(nFANTOM100_iNXT nxt);
extern  int NXTCommFantom_send(nFANTOM100_iNXT nxt, char* data, int offset, int len);
extern  int NXTCommFantom_receive(nFANTOM100_iNXT nxt, char* data, int offset, int len);
extern void NXTCommFantom_close(nFANTOM100_iNXT nxt);

#endif
