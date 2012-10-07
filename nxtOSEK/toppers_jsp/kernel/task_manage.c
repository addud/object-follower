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
 *  @(#) $Id: task_manage.c,v 1.9 2007/04/22 18:04:06 hiro Exp $
 */

/*
 *	������������ǽ
 */

#include "jsp_kernel.h"
#include "check.h"
#include "task.h"
#include "wait.h"

/*
 *  �������ε�ư
 */
#ifdef __act_tsk

SYSCALL ER
act_tsk(ID tskid)
{
	TCB	*tcb;
	ER	ercd;

	LOG_ACT_TSK_ENTER(tskid);
	CHECK_TSKCTX_UNL();
	CHECK_TSKID_SELF(tskid);
	tcb = get_tcb_self(tskid);

	t_lock_cpu();
	if (TSTAT_DORMANT(tcb->tstat)) {
		if (make_active(tcb)) {
			dispatch();
		}
		ercd = E_OK;
	}
	else if (!(tcb->actcnt)) {
		tcb->actcnt = TRUE;
		ercd = E_OK;
	}
	else {
		ercd = E_QOVR;
	}
	t_unlock_cpu();

    exit:
	LOG_ACT_TSK_LEAVE(ercd);
	return(ercd);
}

#endif /* __act_tsk */

/*
 *  �������ε�ư���󥿥�������ƥ������ѡ�
 */
#ifdef __iact_tsk

SYSCALL ER
iact_tsk(ID tskid)
{
	TCB	*tcb;
	ER	ercd;

	LOG_IACT_TSK_ENTER(tskid);
	CHECK_INTCTX_UNL();
	CHECK_TSKID(tskid);
	tcb = get_tcb(tskid);

	i_lock_cpu();
	if (TSTAT_DORMANT(tcb->tstat)) {
		if (make_active(tcb)) {
			reqflg = TRUE;
		}
		ercd = E_OK;
	}
	else if (!(tcb->actcnt)) {
		tcb->actcnt = TRUE;
		ercd = E_OK;
	}
	else {
		ercd = E_QOVR;
	}
	i_unlock_cpu();

    exit:
	LOG_IACT_TSK_LEAVE(ercd);
	return(ercd);
}

#endif /* __iact_tsk */

/*
 *  ��������ư�׵�Υ���󥻥�
 */
#ifdef __can_act

SYSCALL ER_UINT
can_act(ID tskid)
{
	TCB	*tcb;
	ER_UINT	ercd;

	LOG_CAN_ACT_ENTER(tskid);
	CHECK_TSKCTX_UNL();
	CHECK_TSKID_SELF(tskid);
	tcb = get_tcb_self(tskid);

	t_lock_cpu();
	ercd = tcb->actcnt ? 1 : 0;
	tcb->actcnt = FALSE;
	t_unlock_cpu();

    exit:
	LOG_CAN_ACT_LEAVE(ercd);
	return(ercd);
}

#endif /* __can_act */

/*
 *  ���������ν�λ
 */
#ifdef __ext_tsk

SYSCALL void
ext_tsk(void)
{
	LOG_EXT_TSK_ENTER();

#ifdef ACTIVATED_STACK_SIZE
	/*
	 *  create_context �� activate_context �ǡ�������Υ����å���
	 *  ����˲����ʤ��褦�ˡ������å���˥��ߡ��ΰ����ݤ��롥
	 */
	(void) alloca(ACTIVATED_STACK_SIZE);
#endif /* ACTIVATED_STACK_SIZE */

	if (sense_context()) {
		/*
		 *  �󥿥�������ƥ����Ȥ��� ext_tsk ���ƤФ줿��硤
		 *  �����ƥ���˥��顼��Ͽ�������Τޤ޼¹Ԥ�³����
		 *  ��, ư����ݾڤ���ʤ���
		 */
		syslog_0(LOG_EMERG,
			"ext_tsk is called from non-task contexts.");
	}
	if (sense_lock()) {
		/*
		 *  CPU��å����֤� ext_tsk ���ƤФ줿���ϡ�CPU��å�
		 *  �������Ƥ��饿������λ���롥������ϡ������ӥ�
		 *  ��������Ǥ�CPU��å����ά����Ф褤������
		 */
		syslog_0(LOG_WARNING,
			"ext_tsk is called from CPU locked state.");
	}
	else {
		if (sense_context()) {
			i_lock_cpu();
		}
		else  {
			t_lock_cpu();
		}
	}
	if (!(enadsp)) {
		/*
		 *  �ǥ����ѥå��ػ߾��֤� ext_tsk ���ƤФ줿���ϡ�
		 *  �ǥ����ѥå����ľ��֤ˤ��Ƥ��饿������λ���롥
		 */
		syslog_0(LOG_WARNING,
			"ext_tsk is called from dispatch disabled state.");
		enadsp = TRUE;
	}
	exit_task();
}

#endif /* __ext_tsk */

/*
 *  �������ζ�����λ
 */
#ifdef __ter_tsk

SYSCALL ER
ter_tsk(ID tskid)
{
	TCB	*tcb;
	UINT	tstat;
	ER	ercd;

	LOG_TER_TSK_ENTER(tskid);
	CHECK_TSKCTX_UNL();
	CHECK_TSKID(tskid);
	tcb = get_tcb(tskid);
	CHECK_NONSELF(tcb);

	t_lock_cpu();
	if (TSTAT_DORMANT(tstat = tcb->tstat)) {
		ercd = E_OBJ;
	}
	else {
		if (TSTAT_RUNNABLE(tstat)) {
			make_non_runnable(tcb);
		}
		else if (TSTAT_WAITING(tstat)) {
			wait_cancel(tcb);
		}
		make_dormant(tcb);
		if (tcb->actcnt) {
			tcb->actcnt = FALSE;
			if (make_active(tcb)) {
				dispatch();
			}
		}
		ercd = E_OK;
	}
	t_unlock_cpu();

    exit:
	LOG_TER_TSK_LEAVE(ercd);
	return(ercd);
}

#endif /* __ter_tsk */

/*
 *  ������ͥ���٤��ѹ�
 */
#ifdef __chg_pri

SYSCALL ER
chg_pri(ID tskid, PRI tskpri)
{
	TCB	*tcb;
	UINT	newpri;
	UINT	tstat;
	ER	ercd;

	LOG_CHG_PRI_ENTER(tskid, tskpri);
	CHECK_TSKCTX_UNL();
	CHECK_TSKID_SELF(tskid);
	CHECK_TPRI_INI(tskpri);
	tcb = get_tcb_self(tskid);
	newpri = (tskpri == TPRI_INI) ? tcb->tinib->ipriority
					: INT_PRIORITY(tskpri);

	t_lock_cpu();
	if (TSTAT_DORMANT(tstat = tcb->tstat)) {
		ercd = E_OBJ;
	}
	else if (TSTAT_RUNNABLE(tstat)) {
		if (change_priority(tcb, newpri)) {
			dispatch();
		}
		ercd = E_OK;
	}
	else {
		tcb->priority = newpri;
		if ((tstat & TS_WAIT_WOBJCB) != 0) {
			wobj_change_priority(((WINFO_WOBJ *)(tcb->winfo))
							->wobjcb, tcb);
		}
		ercd = E_OK;
	}
	t_unlock_cpu();

    exit:
	LOG_CHG_PRI_LEAVE(ercd);
	return(ercd);
}

#endif /* __chg_pri */

/*
 *  ������ͥ���٤λ���
 */
#ifdef __get_pri

SYSCALL ER
get_pri(ID tskid, PRI *p_tskpri)
{
	TCB	*tcb;
	ER	ercd;

	LOG_GET_PRI_ENTER(tskid, p_tskpri);
	CHECK_TSKCTX_UNL();
	CHECK_TSKID_SELF(tskid);
	tcb = get_tcb_self(tskid);

	t_lock_cpu();
	if (TSTAT_DORMANT(tcb->tstat)) {
		ercd = E_OBJ;
	}
	else {
		*p_tskpri = EXT_TSKPRI(tcb->priority);
		ercd = E_OK;
	}
	t_unlock_cpu();

    exit:
	LOG_GET_PRI_LEAVE(ercd, *p_tskpri);
	return(ercd);
}

#endif /* __get_pri */
