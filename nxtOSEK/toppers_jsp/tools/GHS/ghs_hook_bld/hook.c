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
 *  @(#) $Id: hook.c,v 1.2 2003/12/19 11:48:37 honda Exp $
 */

#ifdef GHS_HOOK
#include "jsp_kernel.h"
#include "kernel.h"
#include "task.h"
#include "ghs_hook.h"

void sys_hook0(int grp, int code)
{
    ID tskid=TSKID(runtsk);
#if(GHS_HOOK != 1)
    if (!(Ros_buf.hook.trc_grp & THG_SYS) || !(Ros_buf.hook.sys_grp & grp))
        return;
    if (tskid > TRACE_TNUM_TSKID || !(Ros_buf.hook.task_id[tskid]))
        return;
#endif
    t_lock_cpu();
    ghs_hook4(THG_SYS, tskid, code);
    t_unlock_cpu();
}

void sys_hook0_i(int grp, int code)
{
#if(GHS_HOOK != 1)
    if (!(Ros_buf.hook.trc_grp & THG_SYS) || !(Ros_buf.hook.sys_grp & grp))
        return;
    if (!(Ros_buf.hook.task_id[0]))
        return;
#endif
    t_lock_cpu();
    ghs_hook4(THG_SYS, 0, code);
    t_unlock_cpu();
}

void sys_hook1(int grp, int code, int p1)
{
    ID tskid = TSKID(runtsk);
#if(GHS_HOOK != 1)
    if (!(Ros_buf.hook.trc_grp & THG_SYS) || !(Ros_buf.hook.sys_grp & grp))
        return;
    if (tskid > TRACE_TNUM_TSKID || !(Ros_buf.hook.task_id[tskid]))
	return;
#endif
    t_lock_cpu();
    ghs_hook5(THG_SYS, tskid, code, p1);
    t_unlock_cpu();
}

void sys_hook1_i(int grp, int code, int p1)
{
#if(GHS_HOOK != 1)
    if (!(Ros_buf.hook.trc_grp & THG_SYS) || !(Ros_buf.hook.sys_grp & grp))
        return;
    if (!(Ros_buf.hook.task_id[0]))
        return;
#endif
    t_lock_cpu();
    ghs_hook5(THG_SYS, 0, code, p1);
    t_unlock_cpu();
}

void sys_hook2(int grp, int code, int p1, int p2)
{
    ID tskid = TSKID(runtsk);
#if(GHS_HOOK != 1)
    if (!(Ros_buf.hook.trc_grp & THG_SYS) || !(Ros_buf.hook.sys_grp & grp))
        return;
    if (tskid > TRACE_TNUM_TSKID || !(Ros_buf.hook.task_id[tskid]))
        return;
#endif
    t_lock_cpu();
    ghs_hook6(THG_SYS, tskid, code, p1, p2);
    t_unlock_cpu();
}

void sys_hook2_i(int grp, int code, int p1, int p2)
{
#if(GHS_HOOK != 1)
    if (!(Ros_buf.hook.trc_grp & THG_SYS) || !(Ros_buf.hook.sys_grp & grp))
        return;
    if (!(Ros_buf.hook.task_id[0]))
        return;
#endif
    t_lock_cpu();
    ghs_hook6(THG_SYS, 0, code, p1, p2);
    t_unlock_cpu();
}

void sys_hook3(int grp, int code, int p1, int p2, int p3)
{
    ID tskid = TSKID(runtsk);
#if(GHS_HOOK != 1)
    if (!(Ros_buf.hook.trc_grp & THG_SYS) || !(Ros_buf.hook.sys_grp & grp))
        return;
    if (!(Ros_buf.hook.task_id[tskid & (TRACE_TNUM_TSKID-1)]))
        return;
#endif
    t_lock_cpu();
    ghs_hook7(THG_SYS, tskid, code, p1, p2, p3);
    t_unlock_cpu();
}

void sys_hook4(int grp, int code, int p1, int p2, int p3, int p4)
{
    ID tskid = TSKID(runtsk);
#if(GHS_HOOK != 1)
    if (!(Ros_buf.hook.trc_grp & THG_SYS) || !(Ros_buf.hook.sys_grp & grp))
        return;
    if (tskid > TRACE_TNUM_TSKID || !(Ros_buf.hook.task_id[tskid]))
        return;
#endif
    t_lock_cpu();
    ghs_hook8(THG_SYS, tskid, code, p1, p2, p3, p4);
    t_unlock_cpu();
}


void trc_rtn_hook(int grp, int code, int ercd)
{
    ID	tskid = TSKID(runtsk);
#if(GHS_HOOK != 1)
    if (!(Ros_buf.hook.trc_grp & THG_RET))
        return;
    if (!(Ros_buf.hook.trc_grp & THG_SYS) || !(Ros_buf.hook.sys_grp & grp))
        return;
    if (tskid > TRACE_TNUM_TSKID || !(Ros_buf.hook.task_id[tskid]))
	return;
#endif
    t_lock_cpu();
    ghs_hook5(THG_RET, tskid, code, ercd);
    t_unlock_cpu();
}

/*CPU��å����֤ǸƤФ�뤿�ᡢCPU���å�����ɬ�פϤʤ�*/
void sts_hook(ID tskid)
{
	TCB	*tcb;
	int tstat;
#if(GHS_HOOK != 1)
    if (!(Ros_buf.hook.trc_grp & THG_STS))
        return;
    if (tskid > TRACE_TNUM_TSKID || !(Ros_buf.hook.task_id[tskid]))
        return;
#endif
    tcb = get_tcb(tskid);
	tstat = (int)(tcb->tstat);
	if(TSTAT_DORMANT(tstat)) tstat = 0x1;	/* 0x1:Dormant */
	else if(TSTAT_RUNNABLE(tstat)) tstat = 0x0;	/* 0x0:Ready */
	else if(TSTAT_WAITING(tstat)) {
		if((tstat & (TS_WAIT_SLEEP | TS_WAIT_WOBJ)) == 0) tstat = 0x09;  /* 0x9:Delay */
		else {
			if((tstat & TS_WAIT_SLEEP) != 0) tstat = 0x08;  /* 0x8:Sleep */
			else tstat = 0x0a;  /* 0xa:Waiting */
		}
	if(TSTAT_SUSPENDED(tstat)) tstat |= 0x10;
	}
	else if(TSTAT_SUSPENDED(tstat)) tstat = 0x10;
	ghs_hook4(THG_STS, tskid, tstat);
}

void dispatch_hook(TCB	*tcb)
{
    ID tskid;

#if(GHS_HOOK != 1)
    if (!(Ros_buf.hook.trc_grp & THG_DSP))
        return;
#endif
    tskid = runtsk == NULL ? 0 : TSKID(runtsk);
    t_lock_cpu();
    ghs_hook4(THG_DSP, tskid, TSKID(tcb));
}

void exception_hook(int code, int addr)
{
    int i;
    ID tskid;

#if(GHS_HOOK != 1)
    if (!(Ros_buf.hook.trc_grp & THG_INT))
        return;
#endif
    for(i = 0; i < TRACE_TNUM_EVT; i++){
        if(Ros_buf.hook.evtcode[i] == 0) return;
        if(Ros_buf.hook.evtcode[i] == code){
            tskid = runtsk == NULL ? 0 : TSKID(runtsk);
            ghs_hook5(THG_INT, tskid, code, addr);
            return;
        }
    }
}
#endif

