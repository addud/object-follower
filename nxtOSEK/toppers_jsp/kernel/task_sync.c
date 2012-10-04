/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
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
 *  @(#) $Id: task_sync.c,v 1.7 2003/12/20 08:12:24 hiro Exp $
 */

/*
 *	��������°Ʊ����ǽ
 */

#include "jsp_kernel.h"
#include "check.h"
#include "task.h"
#include "wait.h"

/*
 *  �����Ԥ�
 */
#ifdef __slp_tsk

SYSCALL ER
slp_tsk()
{
	WINFO	winfo;
	ER	ercd;

	LOG_SLP_TSK_ENTER();
	CHECK_DISPATCH();

	t_lock_cpu();
	if (runtsk->wupcnt) {
		runtsk->wupcnt = FALSE;
		ercd = E_OK;
	}
	else {
		runtsk->tstat = (TS_WAITING | TS_WAIT_SLEEP);
		make_wait(&winfo);
		LOG_TSKSTAT(runtsk);
		dispatch();
		ercd = winfo.wercd;
	}
	t_unlock_cpu();

    exit:
	LOG_SLP_TSK_LEAVE(ercd);
	return(ercd);
}

#endif /* __slp_tsk */

/*
 *  �����Ԥ��ʥ����ॢ���Ȥ����
 */
#ifdef __tslp_tsk

SYSCALL ER
tslp_tsk(TMO tmout)
{
	WINFO	winfo;
	TMEVTB	tmevtb;
	ER	ercd;

	LOG_TSLP_TSK_ENTER(tmout);
	CHECK_DISPATCH();
	CHECK_TMOUT(tmout);

	t_lock_cpu();
	if (runtsk->wupcnt) {
		runtsk->wupcnt = FALSE;
		ercd = E_OK;
	}
	else if (tmout == TMO_POL) {
		ercd = E_TMOUT;
	}
	else {
		runtsk->tstat = (TS_WAITING | TS_WAIT_SLEEP);
		make_wait_tmout(&winfo, &tmevtb, tmout);
		LOG_TSKSTAT(runtsk);
		dispatch();
		ercd = winfo.wercd;
	}
	t_unlock_cpu();

    exit:
	LOG_TSLP_TSK_LEAVE(ercd);
	return(ercd);
}

#endif /* __tslp_tsk */

/*
 *  �������ε���
 */
#ifdef __wup_tsk

SYSCALL ER
wup_tsk(ID tskid)
{
	TCB	*tcb;
	UINT	tstat;
	ER	ercd;

	LOG_WUP_TSK_ENTER(tskid);
	CHECK_TSKCTX_UNL();
	CHECK_TSKID_SELF(tskid);
	tcb = get_tcb_self(tskid);

	t_lock_cpu();
	if (TSTAT_DORMANT(tstat = tcb->tstat)) {
		ercd = E_OBJ;
	}
	else if ((tstat & TS_WAIT_SLEEP) != 0) {
		if (wait_complete(tcb)) {
			dispatch();
		}
		ercd = E_OK;
	}
	else if (!(tcb->wupcnt)) {
		tcb->wupcnt = TRUE;
		ercd = E_OK;
	}
	else {
		ercd = E_QOVR;
	}
	t_unlock_cpu();

    exit:
	LOG_WUP_TSK_LEAVE(ercd);
	return(ercd);
}

#endif /* __wup_tsk */

/*
 *  �������ε������󥿥�������ƥ������ѡ�
 */
#ifdef __iwup_tsk

SYSCALL ER
iwup_tsk(ID tskid)
{
	TCB	*tcb;
	UINT	tstat;
	ER	ercd;

	LOG_IWUP_TSK_ENTER(tskid);
	CHECK_INTCTX_UNL();
	CHECK_TSKID(tskid);
	tcb = get_tcb(tskid);

	i_lock_cpu();
	if (TSTAT_DORMANT(tstat = tcb->tstat)) {
		ercd = E_OBJ;
	}
	else if ((tstat & TS_WAIT_SLEEP) != 0) {
		if (wait_complete(tcb)) {
			reqflg = TRUE;
		}
		ercd = E_OK;
	}
	else if (!(tcb->wupcnt)) {
		tcb->wupcnt = TRUE;
		ercd = E_OK;
	}
	else {
		ercd = E_QOVR;
	}
	i_unlock_cpu();

    exit:
	LOG_IWUP_TSK_LEAVE(ercd);
	return(ercd);
}

#endif /* __iwup_tsk */

/*
 *  �����������׵�Υ���󥻥�
 */
#ifdef __can_wup

SYSCALL ER_UINT
can_wup(ID tskid)
{
	TCB	*tcb;
	ER_UINT	ercd;

	LOG_CAN_WUP_ENTER(tskid);
	CHECK_TSKCTX_UNL();
	CHECK_TSKID_SELF(tskid);
	tcb = get_tcb_self(tskid);

	t_lock_cpu();
	if (TSTAT_DORMANT(tcb->tstat)) {
		ercd = E_OBJ;
	}
	else {
		ercd = tcb->wupcnt ? 1 : 0;
		tcb->wupcnt = FALSE;
	}
	t_unlock_cpu();

    exit:
	LOG_CAN_WUP_LEAVE(ercd);
	return(ercd);
}

#endif /* __can_wup */

/*
 *  �Ԥ����֤ζ������
 */
#ifdef __rel_wai

SYSCALL ER
rel_wai(ID tskid)
{
	TCB	*tcb;
	ER	ercd;

	LOG_REL_WAI_ENTER(tskid);
	CHECK_TSKCTX_UNL();
	CHECK_TSKID(tskid);
	tcb = get_tcb(tskid);

	t_lock_cpu();
	if (!(TSTAT_WAITING(tcb->tstat))) {
		ercd = E_OBJ;
	}
	else {
		if (wait_release(tcb)) {
			dispatch();
		}
		ercd = E_OK;
	}
	t_unlock_cpu();

    exit:
	LOG_REL_WAI_LEAVE(ercd);
	return(ercd);
}

#endif /* __rel_wai */

/*
 *  �Ԥ����֤ζ���������󥿥�������ƥ������ѡ�
 */
#ifdef __irel_wai

SYSCALL ER
irel_wai(ID tskid)
{
	TCB	*tcb;
	ER	ercd;

	LOG_IREL_WAI_ENTER(tskid);
	CHECK_INTCTX_UNL();
	CHECK_TSKID(tskid);
	tcb = get_tcb(tskid);

	i_lock_cpu();
	if (!(TSTAT_WAITING(tcb->tstat))) {
		ercd = E_OBJ;
	}
	else {
		if (wait_release(tcb)) {
			reqflg = TRUE;
		}
		ercd = E_OK;
	}
	i_unlock_cpu();

    exit:
	LOG_IREL_WAI_LEAVE(ercd);
	return(ercd);
}

#endif /* __irel_wai */

/*
 *  �����Ԥ����֤ؤΰܹ�
 */
#ifdef __sus_tsk

SYSCALL ER
sus_tsk(ID tskid)
{
	TCB	*tcb;
	UINT	tstat;
	ER	ercd;

	LOG_SUS_TSK_ENTER(tskid);
	CHECK_TSKCTX_UNL();
	CHECK_TSKID_SELF(tskid);
	tcb = get_tcb_self(tskid);

	t_lock_cpu();
	if (tcb == runtsk && !(enadsp)) {
		ercd = E_CTX;
	}
	else if (TSTAT_DORMANT(tstat = tcb->tstat)) {
		ercd = E_OBJ;
	}
	else if (TSTAT_RUNNABLE(tstat)) {
		/*
		 *  �¹ԤǤ�����֤��鶯���Ԥ����֤ؤ�����
		 */
		tcb->tstat = TS_SUSPENDED;
		LOG_TSKSTAT(tcb);
		if (make_non_runnable(tcb)) {
			dispatch();
		}
		ercd = E_OK;
	}
	else if (TSTAT_SUSPENDED(tstat)) {
		ercd = E_QOVR;
	}
	else {
		/*
		 *  �Ԥ����֤�������Ԥ����֤ؤ�����
		 */
		tcb->tstat |= TS_SUSPENDED;
		LOG_TSKSTAT(tcb);
		ercd = E_OK;
	}
	t_unlock_cpu();

    exit:
	LOG_SUS_TSK_LEAVE(ercd);
	return(ercd);
}

#endif /* __sus_tsk */

/*
 *  �����Ԥ����֤���κƳ�
 */
#ifdef __rsm_tsk

SYSCALL ER
rsm_tsk(ID tskid)
{
	TCB	*tcb;
	UINT	tstat;
	ER	ercd;

	LOG_RSM_TSK_ENTER(tskid);
	CHECK_TSKCTX_UNL();
	CHECK_TSKID(tskid);
	tcb = get_tcb(tskid);

	t_lock_cpu();
	if (!(TSTAT_SUSPENDED(tstat = tcb->tstat))) {
		ercd = E_OBJ;
	}
	else if (!(TSTAT_WAITING(tstat))) {
		/*
		 *  �����Ԥ����֤���¹ԤǤ�����֤ؤ�����
		 */
		if (make_runnable(tcb)) {
			dispatch();
		}
		ercd = E_OK;
	}
	else {
		/*
		 *  ����Ԥ����֤����Ԥ����֤ؤ�����
		 */
		tcb->tstat &= ~TS_SUSPENDED;
		LOG_TSKSTAT(tcb);
		ercd = E_OK;
	}
	t_unlock_cpu();

    exit:
	LOG_RSM_TSK_LEAVE(ercd);
	return(ercd);
}

#endif /* __rsm_tsk */

/*
 *  �����Ԥ����֤���ζ����Ƴ�
 *
 *  JSP�����ͥ�Ǥϡ�frsm_tsk �� rsm_tsk ��Ʊ��ν����Ȥʤ롥frsm_tsk 
 *  ���ƤФ��ȡ�frsm_tsk �� rsm_tsk ��ξ���Υ����ӥ�������Υȥ졼��
 *  �������Ϥ���롥��������� rsm_tsk �Υȥ졼�����������뤳
 *  �Ȥ�ɬ�פǤ��롥rsm_tsk �Υȥ졼������������������뤿��ˤϡ���
 *  �����ǥ����ѥå��Υ��ȡ��������㳰�����Υ���������뤳�Ȥ�ɬ��
 *  �Ȥʤ�Τǡ���դ�ɬ�פǤ��롥
 */
#ifdef __frsm_tsk

SYSCALL ER
frsm_tsk(ID tskid)
{
	ER	ercd;

	LOG_FRSM_TSK_ENTER(tskid);
	ercd = rsm_tsk(tskid);
	LOG_FRSM_TSK_LEAVE(ercd);
	return(ercd);
}

#endif /* __frsm_tsk */

/*
 *  �����������ٱ�
 */
#ifdef __dly_tsk

SYSCALL ER
dly_tsk(RELTIM dlytim)
{
	WINFO	winfo;
	TMEVTB	tmevtb;
	ER	ercd;

	LOG_DLY_TSK_ENTER(dlytim);
	CHECK_DISPATCH();
	CHECK_PAR(dlytim <= TMAX_RELTIM);

	t_lock_cpu();
	runtsk->tstat = TS_WAITING;
	make_non_runnable(runtsk);
	runtsk->winfo = &winfo;
	winfo.tmevtb = &tmevtb;
	tmevtb_enqueue(&tmevtb, dlytim, (CBACK) wait_tmout_ok, (VP) runtsk);
	LOG_TSKSTAT(runtsk);
	dispatch();
	ercd = winfo.wercd;
	t_unlock_cpu();

    exit:
	LOG_DLY_TSK_LEAVE(ercd);
	return(ercd);
}

#endif /* __dly_tsk */
