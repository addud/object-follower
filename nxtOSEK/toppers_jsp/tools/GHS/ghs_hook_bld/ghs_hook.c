/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *                2003      by Advanced Data Controls, Corp
 * 
 *  �嵭����Ԥϡ��ʲ��� (1)��(4) �ξ�狼��Free Software Foundation 
 *  �ˤ�äƸ�ɽ����Ƥ��� GNU General Public License �� Version 2 �˵�
 *  �Ҥ���Ƥ���������������˸¤ꡤ�ܥ��եȥ��������ܥ��եȥ�����
 *  ����Ѥ�����Τ�ޤࡥ�ʲ�Ʊ���ˤ���ѡ�ʣ�������ѡ������ۡʰʲ���
 *  ���ѤȸƤ֡ˤ��뤳�Ȥ�̵���ǵ������롥
 *  (1) �ܥ��եȥ������򥽡��������ɤη������Ѥ�����ˤϡ��嵭������
 *      ��ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ��꤬�����Τޤޤη��ǥ���
 *      ����������˴ޤޤ�Ƥ��뤳�ȡ�
 *  (2) �ܥ��եȥ������򡤥饤�֥������ʤɡ�¾�Υ��եȥ�������ȯ�˻�
 *      �ѤǤ�����Ǻ����ۤ�����ˤϡ������ۤ�ȼ���ɥ�����ȡ�����
 *      �ԥޥ˥奢��ʤɡˤˡ��嵭�����ɽ�����������Ѿ�浪��Ӳ���
 *      ��̵�ݾڵ����Ǻܤ��뤳�ȡ�
 *  (3) �ܥ��եȥ������򡤵�����Ȥ߹���ʤɡ�¾�Υ��եȥ�������ȯ�˻�
 *      �ѤǤ��ʤ����Ǻ����ۤ�����ˤϡ����Τ����줫�ξ�����������
 *      �ȡ�
 *    (a) �����ۤ�ȼ���ɥ�����ȡ����Ѽԥޥ˥奢��ʤɡˤˡ��嵭����
 *        �ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ����Ǻܤ��뤳�ȡ�
 *    (b) �����ۤη��֤��̤�������ˡ�ˤ�äơ�TOPPERS�ץ������Ȥ�
 *        ��𤹤뤳�ȡ�
 *  (4) �ܥ��եȥ����������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������뤤���ʤ�»
 *      ������⡤�嵭����Ԥ����TOPPERS�ץ������Ȥ����դ��뤳�ȡ�
 * 
 *  �ܥ��եȥ������ϡ�̵�ݾڤ��󶡤���Ƥ����ΤǤ��롥�嵭����Ԥ�
 *  ���TOPPERS�ץ������Ȥϡ��ܥ��եȥ������˴ؤ��ơ�����Ŭ�Ѳ�ǽ����
 *  �ޤ�ơ������ʤ��ݾڤ�Ԥ�ʤ����ޤ����ܥ��եȥ����������Ѥˤ��ľ
 *  ��Ū�ޤ��ϴ���Ū�������������ʤ�»���˴ؤ��Ƥ⡤������Ǥ�����ʤ���
 * 
 *  @(#) $Id: ghs_hook.c,v 1.2 2003/12/19 11:48:37 honda Exp $
 */
#ifdef GHS_HOOK
#include "jsp_kernel.h"
#include "kernel.h"
#include "time_event.h"
#include "task.h"
#include "ghs_hook.h"


#define	THG_ALL	THG_SYS|THG_RET|THG_DSP|THG_STS|THG_INT
#define	THF_ALL	THF_TSK|THF_TSKS|THF_TEX|THF_SEM|THF_FLG|THF_DTQ|THF_MBX|THF_MPF|THF_TIM
#ifndef GRP
#define	GRP	THG_ALL
#endif
#ifndef SEV
#define	SEV	THF_ALL  
#endif
#ifndef TSK
#define	TSK	TRACE_TNUM_TSKID
#endif


#define MAX_TSK  256

T_ROS Ros_buf;

struct GHS_TASKS {
	B	sts;			
	B	pri;			
} ghs_tasks[MAX_TSK];

ghs_tasks_initialize()
{
	INT	i;
	TCB	*tcb;

	for (tcb = tcb_table, i = 0; i < tmax_tskid; tcb++, i++) {
		if(i > sizeof(ghs_tasks) / sizeof(ghs_tasks[0]))
			return;
		if(TSTAT_RUNNABLE(tcb->tstat)) ghs_tasks[i].sts = TTS_RDY;
		else ghs_tasks[i].sts = TTS_DMT;
		ghs_tasks[i].pri = EXT_TSKPRI(tcb->priority);
	}
}

int SetEndian()
{
    union testme {
        char    a[2];
        short   b;
    	} testme;

    testme.b    = 0;
    testme.a[0] = 1;
    if (testme.b== 1)
        return(0);
    else
        return(1);
}

void vinit_hook(void)
{
    int i;

    Ros_buf.trace.bigendian = SetEndian();
    Ros_buf.trace.dummy = 0;
    Ros_buf.trace.size = BUFF_SIZE-1;
    Ros_buf.trace.putp = 0;
    Ros_buf.trace.getp = 0;
    for(i = 0; i < TRACE_TNUM_TSKID-1; i++)
        Ros_buf.hook.task_id[i] = 0;
    for(i = 0; i < TRACE_TNUM_EVT-1; i++)
        Ros_buf.hook.evtcode[i] = 0;
    Ros_buf.hook.max_tid = tmax_tskid;
    Ros_buf.hook.tnum_tskid = TRACE_TNUM_TSKID;
    Ros_buf.hook.tnum_evt = TRACE_TNUM_EVT;

    Ros_buf.hook.trc_grp = GRP;
    Ros_buf.hook.sys_grp = SEV;
    for(i = 0; i < TSK; i++)
        Ros_buf.hook.task_id[i] = 1;    
    
}

void ghs_hook4(int sts, int p1, int p2)
{
    int putp;

        while(BUFF_SIZE-(Ros_buf.trace.putp-Ros_buf.trace.getp) < 4)
        {
	    Ros_buf.trace.getp += Ros_buf.syscall[Ros_buf.trace.getp & Ros_buf.trace.size] & 0x0F;
        }
        putp = Ros_buf.trace.putp;
        Ros_buf.syscall[putp++ & Ros_buf.trace.size] = (sts << 4) | 4;
        Ros_buf.syscall[putp++ & Ros_buf.trace.size] = current_time;
        Ros_buf.syscall[putp++ & Ros_buf.trace.size] = p1;
        Ros_buf.syscall[putp++ & Ros_buf.trace.size] = p2;
        Ros_buf.trace.putp = putp;
}

void ghs_hook5(int sts, int p1, int p2, int p3)
{
    int putp;

        while(BUFF_SIZE-(Ros_buf.trace.putp-Ros_buf.trace.getp) < 5)
        {   Ros_buf.trace.getp += Ros_buf.syscall[Ros_buf.trace.getp & Ros_buf.trace.size] & 0x0F;
        }
	putp = Ros_buf.trace.putp;
        Ros_buf.syscall[putp++ & Ros_buf.trace.size] = (sts << 4) | 5;
        Ros_buf.syscall[putp++ & Ros_buf.trace.size] = current_time;
        Ros_buf.syscall[putp++ & Ros_buf.trace.size] = p1;
        Ros_buf.syscall[putp++ & Ros_buf.trace.size] = p2;
        Ros_buf.syscall[putp++ & Ros_buf.trace.size] = p3;
        Ros_buf.trace.putp = putp;
}

void ghs_hook6(int sts, int p1, int p2, int p3, int p4)
{
    int putp;

        while(BUFF_SIZE-(Ros_buf.trace.putp-Ros_buf.trace.getp) < 6)
        {   Ros_buf.trace.getp += Ros_buf.syscall[Ros_buf.trace.getp & Ros_buf.trace.size] & 0x0F;
        }

        putp = Ros_buf.trace.putp;
        Ros_buf.syscall[putp++ & Ros_buf.trace.size] = (sts << 4) | 6;
        Ros_buf.syscall[putp++ & Ros_buf.trace.size] = current_time;
        Ros_buf.syscall[putp++ & Ros_buf.trace.size] = p1;
        Ros_buf.syscall[putp++ & Ros_buf.trace.size] = p2;
        Ros_buf.syscall[putp++ & Ros_buf.trace.size] = p3;
        Ros_buf.syscall[putp++ & Ros_buf.trace.size] = p4;
        Ros_buf.trace.putp = putp;
}

void ghs_hook7(int sts, int p1, int p2, int p3, int p4, int p5)
{
    int putp;

        while(BUFF_SIZE-(Ros_buf.trace.putp-Ros_buf.trace.getp) < 7)
        {   Ros_buf.trace.getp += Ros_buf.syscall[Ros_buf.trace.getp & Ros_buf.trace.size] & 0x0F;
        }

        putp = Ros_buf.trace.putp;
        Ros_buf.syscall[putp++ & Ros_buf.trace.size] = (sts << 4) | 7;
        Ros_buf.syscall[putp++ & Ros_buf.trace.size] = current_time;
        Ros_buf.syscall[putp++ & Ros_buf.trace.size] = p1;
        Ros_buf.syscall[putp++ & Ros_buf.trace.size] = p2;
        Ros_buf.syscall[putp++ & Ros_buf.trace.size] = p3;
        Ros_buf.syscall[putp++ & Ros_buf.trace.size] = p4;
        Ros_buf.syscall[putp++ & Ros_buf.trace.size] = p5;
        Ros_buf.trace.putp = putp;
}

void ghs_hook8(int sts, int p1, int p2, int p3, int p4, int p5, int p6)
{
    int putp;

        while(BUFF_SIZE-(Ros_buf.trace.putp-Ros_buf.trace.getp) < 8)
        {   Ros_buf.trace.getp += Ros_buf.syscall[Ros_buf.trace.getp & Ros_buf.trace.size] & 0x0F;
        }
        putp = Ros_buf.trace.putp;
        Ros_buf.syscall[putp++ & Ros_buf.trace.size] = (sts << 4) | 8;
        Ros_buf.syscall[putp++ & Ros_buf.trace.size] = current_time;
        Ros_buf.syscall[putp++ & Ros_buf.trace.size] = p1;
        Ros_buf.syscall[putp++ & Ros_buf.trace.size] = p2;
        Ros_buf.syscall[putp++ & Ros_buf.trace.size] = p3;
        Ros_buf.syscall[putp++ & Ros_buf.trace.size] = p4;
        Ros_buf.syscall[putp++ & Ros_buf.trace.size] = p5;
        Ros_buf.syscall[putp++ & Ros_buf.trace.size] = p6;
        Ros_buf.trace.putp = putp;
}

void ghs_hook9(int sts, int p1, int p2, int p3, int p4, int p5, int p6, int p7)
{
    int putp;

        while(BUFF_SIZE-(Ros_buf.trace.putp-Ros_buf.trace.getp) < 9)
        {   Ros_buf.trace.getp += Ros_buf.syscall[Ros_buf.trace.getp & Ros_buf.trace.size] & 0x0F;
        }

        putp = Ros_buf.trace.putp;
        Ros_buf.syscall[putp++ & Ros_buf.trace.size] = (sts << 4) | 9;
        Ros_buf.syscall[putp++ & Ros_buf.trace.size] = current_time;
        Ros_buf.syscall[putp++ & Ros_buf.trace.size] = p1;
        Ros_buf.syscall[putp++ & Ros_buf.trace.size] = p2;
        Ros_buf.syscall[putp++ & Ros_buf.trace.size] = p3;
        Ros_buf.syscall[putp++ & Ros_buf.trace.size] = p4;
        Ros_buf.syscall[putp++ & Ros_buf.trace.size] = p5;
        Ros_buf.syscall[putp++ & Ros_buf.trace.size] = p6;
        Ros_buf.syscall[putp++ & Ros_buf.trace.size] = p7;
        Ros_buf.trace.putp = putp;
}

#endif

