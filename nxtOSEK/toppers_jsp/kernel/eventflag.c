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
 *  @(#) $Id: eventflag.c,v 1.8 2003/06/04 01:46:16 hiro Exp $
 */

/*
 *	���٥�ȥե饰��ǽ
 */

#include "jsp_kernel.h"
#include "check.h"
#include "task.h"
#include "wait.h"
#include "eventflag.h"

/*
 *  ���٥�ȥե饰ID�κ����͡�kernel_cfg.c��
 */
extern const ID	tmax_flgid;

/*
 *  ���٥�ȥե饰������֥�å��Υ��ꥢ��kernel_cfg.c��
 */
extern const FLGINIB	flginib_table[];

/*
 *  ���٥�ȥե饰�����֥�å��Υ��ꥢ��kernel_cfg.c��
 */
extern FLGCB	flgcb_table[];

/*
 *  ���٥�ȥե饰�ο�
 */
#define TNUM_FLG	((UINT)(tmax_flgid - TMIN_FLGID + 1))

/*
 *  ���٥�ȥե饰ID���饤�٥�ȥե饰�����֥�å�����Ф�����Υޥ���
 */
#define INDEX_FLG(flgid)	((UINT)((flgid) - TMIN_FLGID))
#define get_flgcb(flgid)	(&(flgcb_table[INDEX_FLG(flgid)]))

/*
 *  ���٥�ȥե饰�Ԥ�����֥�å������
 *
 *  flgptn �ϡ�waiptn ����� wfmode ��Ʊ���˻Ȥ����ȤϤʤ����ᡤunion 
 *  ��Ȥ��Х�������󤹤뤳�Ȥ���ǽ�Ǥ��롥
 */
typedef struct eventflag_waiting_information {
	WINFO	winfo;		/* ɸ����Ԥ�����֥�å� */
	WOBJCB	*wobjcb;	/* �Ԥ����֥������Ȥδ����֥�å� */
	FLGPTN	waiptn;		/* �Ԥ��ѥ����� */
	MODE	wfmode;		/* �Ԥ��⡼�� */
	FLGPTN	flgptn;		/* �Ԥ�������Υѥ����� */
} WINFO_FLG;

/*
 *  ���٥�ȥե饰��ǽ�ν����
 */
#ifdef __flgini

void
eventflag_initialize(void)
{
	UINT	i;
	FLGCB	*flgcb;

	for (flgcb = flgcb_table, i = 0; i < TNUM_FLG; flgcb++, i++) {
		queue_initialize(&(flgcb->wait_queue));
		flgcb->flginib = &(flginib_table[i]);
		flgcb->flgptn = flgcb->flginib->iflgptn;
	}
}

#endif /* __flgini */

/*
 *  ���٥�ȥե饰�Ԥ�������Υ����å�
 */
#ifdef __flgcnd

BOOL
eventflag_cond(FLGCB *flgcb, FLGPTN waiptn, MODE wfmode, FLGPTN *p_flgptn)
{
	if ((wfmode & TWF_ORW) != 0 ? (flgcb->flgptn & waiptn) != 0
				: (flgcb->flgptn & waiptn) == waiptn) {
		*p_flgptn = flgcb->flgptn;
		if ((flgcb->flginib->flgatr & TA_CLR) != 0) {
			flgcb->flgptn = 0;
		}
		return(TRUE);
	}
	return(FALSE);
}

#endif /* __flgcnd */

/*
 *  ���٥�ȥե饰�Υ��å�
 */
#ifdef __set_flg

SYSCALL ER
set_flg(ID flgid, FLGPTN setptn)
{
	FLGCB	*flgcb;
	TCB	*tcb;
	WINFO_FLG *winfo;
	ER	ercd;

	LOG_SET_FLG_ENTER(flgid, setptn);
	CHECK_TSKCTX_UNL();
	CHECK_FLGID(flgid);
	flgcb = get_flgcb(flgid);

	t_lock_cpu();
	flgcb->flgptn |= setptn;
	if (!(queue_empty(&(flgcb->wait_queue)))) {
		tcb = (TCB *)(flgcb->wait_queue.next);
		winfo = (WINFO_FLG *)(tcb->winfo);
		if (eventflag_cond(flgcb, winfo->waiptn,
					winfo->wfmode, &(winfo->flgptn))) {
			queue_delete(&(tcb->task_queue));
			if (wait_complete(tcb)) {
				dispatch();
			}
		}
	}
	ercd = E_OK;
	t_unlock_cpu();

    exit:
	LOG_SET_FLG_LEAVE(ercd);
	return(ercd);
}

#endif /* __set_flg */

/*
 *  ���٥�ȥե饰�Υ��åȡ��󥿥�������ƥ������ѡ�
 */
#ifdef __iset_flg

SYSCALL ER
iset_flg(ID flgid, FLGPTN setptn)
{
	FLGCB	*flgcb;
	TCB	*tcb;
	WINFO_FLG *winfo;
	ER	ercd;

	LOG_ISET_FLG_ENTER(flgid, setptn);
	CHECK_INTCTX_UNL();
	CHECK_FLGID(flgid);
	flgcb = get_flgcb(flgid);

	i_lock_cpu();
	flgcb->flgptn |= setptn;
	if (!(queue_empty(&(flgcb->wait_queue)))) {
		tcb = (TCB *)(flgcb->wait_queue.next);
		winfo = (WINFO_FLG *)(tcb->winfo);
		if (eventflag_cond(flgcb, winfo->waiptn,
					winfo->wfmode, &(winfo->flgptn))) {
			queue_delete(&(tcb->task_queue));
			if (wait_complete(tcb)) {
				reqflg = TRUE;
			}
		}
	}
	ercd = E_OK;
	i_unlock_cpu();

    exit:
	LOG_ISET_FLG_LEAVE(ercd);
	return(ercd);
}

#endif /* __iset_flg */

/*
 *  ���٥�ȥե饰�Υ��ꥢ
 */
#ifdef __clr_flg

SYSCALL ER
clr_flg(ID flgid, FLGPTN clrptn)
{
	FLGCB	*flgcb;
	ER	ercd;

	LOG_CLR_FLG_ENTER(flgid, clrptn);
	CHECK_TSKCTX_UNL();
	CHECK_FLGID(flgid);
	flgcb = get_flgcb(flgid);

	t_lock_cpu();
	flgcb->flgptn &= clrptn; 
	ercd = E_OK;
	t_unlock_cpu();

    exit:
	LOG_CLR_FLG_LEAVE(ercd);
	return(ercd);
}

#endif /* __clr_flg */

/*
 *  ���٥�ȥե饰�Ԥ�
 */
#ifdef __wai_flg

SYSCALL ER
wai_flg(ID flgid, FLGPTN waiptn, MODE wfmode, FLGPTN *p_flgptn)
{
	FLGCB	*flgcb;
	WINFO_FLG winfo;
	ER	ercd;

	LOG_WAI_FLG_ENTER(flgid, waiptn, wfmode, p_flgptn);
	CHECK_DISPATCH();
	CHECK_FLGID(flgid);
	CHECK_PAR(waiptn != 0);
	CHECK_PAR((wfmode & ~TWF_ORW) == 0);
	flgcb = get_flgcb(flgid);

	t_lock_cpu();
	if (!(queue_empty(&(flgcb->wait_queue)))) {
		ercd = E_ILUSE;
	}
	else if (eventflag_cond(flgcb, waiptn, wfmode, p_flgptn)) {
		ercd = E_OK;
	}
	else {
		winfo.waiptn = waiptn;
		winfo.wfmode = wfmode;
		wobj_make_wait((WOBJCB *) flgcb, (WINFO_WOBJ *) &winfo);
		dispatch();
		ercd = winfo.winfo.wercd;
		if (ercd == E_OK) {
			*p_flgptn = winfo.flgptn;
		}
	}
	t_unlock_cpu();

    exit:
	LOG_WAI_FLG_LEAVE(ercd, *p_flgptn);
	return(ercd);
}

#endif /* __wai_flg */

/*
 *  ���٥�ȥե饰�Ԥ��ʥݡ���󥰡�
 */
#ifdef __pol_flg

SYSCALL ER
pol_flg(ID flgid, FLGPTN waiptn, MODE wfmode, FLGPTN *p_flgptn)
{
	FLGCB	*flgcb;
	ER	ercd;

	LOG_POL_FLG_ENTER(flgid, waiptn, wfmode, p_flgptn);
	CHECK_TSKCTX_UNL();
	CHECK_FLGID(flgid);
	CHECK_PAR(waiptn != 0);
	CHECK_PAR((wfmode & ~TWF_ORW) == 0);
	flgcb = get_flgcb(flgid);

	t_lock_cpu();
	if (!(queue_empty(&(flgcb->wait_queue)))) {
		ercd = E_ILUSE;
	}
	else if (eventflag_cond(flgcb, waiptn, wfmode, p_flgptn)) {
		ercd = E_OK;
	}
	else {
		ercd = E_TMOUT;
	}
	t_unlock_cpu();

    exit:
	LOG_POL_FLG_LEAVE(ercd, *p_flgptn);
	return(ercd);
}

#endif /* __pol_flg */

/*
 *  ���٥�ȥե饰�Ԥ��ʥ����ॢ���Ȥ����
 */
#ifdef __twai_flg

SYSCALL ER
twai_flg(ID flgid, FLGPTN waiptn, MODE wfmode, FLGPTN *p_flgptn, TMO tmout)
{
	FLGCB	*flgcb;
	WINFO_FLG winfo;
	TMEVTB	tmevtb;
	ER	ercd;

	LOG_TWAI_FLG_ENTER(flgid, waiptn, wfmode, p_flgptn, tmout);
	CHECK_DISPATCH();
	CHECK_FLGID(flgid);
	CHECK_PAR(waiptn != 0);
	CHECK_PAR((wfmode & ~TWF_ORW) == 0);
	CHECK_TMOUT(tmout);
	flgcb = get_flgcb(flgid);

	t_lock_cpu();
	if (!(queue_empty(&(flgcb->wait_queue)))) {
		ercd = E_ILUSE;
	}
	else if (eventflag_cond(flgcb, waiptn, wfmode, p_flgptn)) {
		ercd = E_OK;
	}
	else if (tmout == TMO_POL) {
		ercd = E_TMOUT;
	}
	else {
		winfo.waiptn = waiptn;
		winfo.wfmode = wfmode;
		wobj_make_wait_tmout((WOBJCB *) flgcb, (WINFO_WOBJ *) &winfo,
						&tmevtb, tmout);
		dispatch();
		ercd = winfo.winfo.wercd;
		if (ercd == E_OK) {
			*p_flgptn = winfo.flgptn;
		}
	}
	t_unlock_cpu();

    exit:
	LOG_TWAI_FLG_LEAVE(ercd, *p_flgptn);
	return(ercd);
}

#endif /* __twai_flg */
