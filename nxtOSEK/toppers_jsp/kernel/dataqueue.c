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
 *  @(#) $Id: dataqueue.c,v 1.9 2003/06/04 01:46:16 hiro Exp $
 */

/*
 *	�ǡ������塼��ǽ
 */

#include "jsp_kernel.h"
#include "check.h"
#include "task.h"
#include "wait.h"
#include "dataqueue.h"

/*
 *  �ǡ������塼ID�κ����͡�kernel_cfg.c��
 */
extern const ID	tmax_dtqid;

/*
 *  �ǡ������塼������֥�å��Υ��ꥢ��kernel_cfg.c��
 */
extern const DTQINIB	dtqinib_table[];

/*
 *  �ǡ������塼�ο�
 */
#define TNUM_DTQ	((UINT)(tmax_dtqid - TMIN_DTQID + 1))

/*
 *  �ǡ������塼�����֥�å��Υ��ꥢ��kernel_cfg.c��
 */
extern DTQCB	dtqcb_table[];

/*
 *  �ǡ������塼ID����ǡ������塼�����֥�å�����Ф�����Υޥ���
 */
#define INDEX_DTQ(dtqid)	((UINT)((dtqid) - TMIN_DTQID))
#define get_dtqcb(dtqid)	(&(dtqcb_table[INDEX_DTQ(dtqid)]))

/*
 *  �ǡ������塼�Ԥ�����֥�å������
 *
 *  �ǡ������塼�ؤ������Ԥ��ȥǡ������塼����μ����Ԥ��ǡ�Ʊ���Ԥ���
 *  ��֥�å���Ȥ���
 */
typedef struct dataqueue_waiting_information {
	WINFO	winfo;		/* ɸ����Ԥ�����֥�å� */
	WOBJCB	*wobjcb;	/* �Ԥ����֥������Ȥδ����֥�å� */
	VP_INT	data;		/* �������ǡ���  */
} WINFO_DTQ;

/*
 *  �ǡ������塼��ǽ�ν����
 */
#ifdef __dtqini

void
dataqueue_initialize(void)
{
	UINT	i;
	DTQCB	*dtqcb;

	for (dtqcb = dtqcb_table, i = 0; i < TNUM_DTQ; dtqcb++, i++) {
		queue_initialize(&(dtqcb->swait_queue));
		dtqcb->dtqinib = &(dtqinib_table[i]);
		queue_initialize(&(dtqcb->rwait_queue));
		dtqcb->count = 0;
		dtqcb->head = 0;
		dtqcb->tail = 0;
	}
}

#endif /* __dtqini */

/*
 *  �ǡ������塼�ΰ�˥ǡ������Ǽ
 */
#ifdef __dtqenq

BOOL
enqueue_data(DTQCB *dtqcb, VP_INT data)
{
	if (dtqcb->count < dtqcb->dtqinib->dtqcnt) {
		*((VP_INT *)(dtqcb->dtqinib->dtq) + dtqcb->tail) = data;
		dtqcb->count++;
		dtqcb->tail++;
		if (dtqcb->tail >= dtqcb->dtqinib->dtqcnt) {
			dtqcb->tail = 0;
		}
		return(TRUE);
	}
	return(FALSE);
}

#endif /* __dtqenq */

/*
 *  �ǡ������塼�ΰ�˥ǡ���������Ǽ
 */
#ifdef __dtqfenq

void
force_enqueue_data(DTQCB *dtqcb, VP_INT data)
{
	*((VP_INT *)(dtqcb->dtqinib->dtq) + dtqcb->tail) = data;
	dtqcb->tail++;
	if (dtqcb->tail >= dtqcb->dtqinib->dtqcnt) {
		dtqcb->tail = 0;
	}
	if (dtqcb->count < dtqcb->dtqinib->dtqcnt) {
		dtqcb->count++;
	}
	else {
		dtqcb->head = dtqcb->tail;
	}
}

#endif /* __dtqfenq */

/*
 *  �ǡ������塼�ΰ褫��ǡ������Ф�
 */
#ifdef __dtqdeq

BOOL
dequeue_data(DTQCB *dtqcb, VP_INT *p_data)
{
	if (dtqcb->count > 0) {
		*p_data = *((VP_INT *)(dtqcb->dtqinib->dtq) + dtqcb->head);
		dtqcb->count--;
		dtqcb->head++;
		if (dtqcb->head >= dtqcb->dtqinib->dtqcnt) {
			dtqcb->head = 0;
		}
		return(TRUE);
	}
	return(FALSE);
}

#endif /* __dtqdeq */

/*
 *  �����Ԥ����塼����Ƭ�������ؤΥǡ�������
 */
#ifdef __dtqsnd

TCB *
send_data_rwait(DTQCB *dtqcb, VP_INT data)
{
	TCB	*tcb;

	if (!(queue_empty(&(dtqcb->rwait_queue)))) {
		tcb = (TCB *) queue_delete_next(&(dtqcb->rwait_queue));
		((WINFO_DTQ *)(tcb->winfo))->data = data;
		return(tcb);
	}
	return(NULL);
}

#endif /* __dtqsnd */

/*
 *  �����Ԥ����塼����Ƭ����������Υǡ�������
 */
#ifdef __dtqrcv

TCB *
receive_data_swait(DTQCB *dtqcb, VP_INT *p_data)
{
	TCB	*tcb;

	if (!(queue_empty(&(dtqcb->swait_queue)))) {
		tcb = (TCB *) queue_delete_next(&(dtqcb->swait_queue));
		*p_data = ((WINFO_DTQ *)(tcb->winfo))->data;
		return(tcb);
	}
	return(NULL);
}

#endif /* __dtqrcv */

/*
 *  �ǡ������塼�ؤ�����
 */
#ifdef __snd_dtq

SYSCALL ER
snd_dtq(ID dtqid, VP_INT data)
{
	DTQCB	*dtqcb;
	WINFO_DTQ winfo;
	TCB	*tcb;
	ER	ercd;

	LOG_SND_DTQ_ENTER(dtqid, data);
	CHECK_DISPATCH();
	CHECK_DTQID(dtqid);
	dtqcb = get_dtqcb(dtqid);

	t_lock_cpu();
	if ((tcb = send_data_rwait(dtqcb, data)) != NULL) {
		if (wait_complete(tcb)) {
			dispatch();
		}
		ercd = E_OK;
	}
	else if (enqueue_data(dtqcb, data)) {
		ercd = E_OK;
	}
	else {
		winfo.data = data;
		wobj_make_wait((WOBJCB *) dtqcb, (WINFO_WOBJ *) &winfo);
		dispatch();
		ercd = winfo.winfo.wercd;
	}
	t_unlock_cpu();

    exit:
	LOG_SND_DTQ_LEAVE(ercd);
	return(ercd);
}

#endif /* __snd_dtq */

/*
 *  �ǡ������塼�ؤ������ʥݡ���󥰡�
 */
#ifdef __psnd_dtq

SYSCALL ER
psnd_dtq(ID dtqid, VP_INT data)
{
	DTQCB	*dtqcb;
	TCB	*tcb;
	ER	ercd;

	LOG_PSND_DTQ_ENTER(dtqid, data);
	CHECK_TSKCTX_UNL();
	CHECK_DTQID(dtqid);
	dtqcb = get_dtqcb(dtqid);

	t_lock_cpu();
	if ((tcb = send_data_rwait(dtqcb, data)) != NULL) {
		if (wait_complete(tcb)) {
			dispatch();
		}
		ercd = E_OK;
	}
	else if (enqueue_data(dtqcb, data)) {
		ercd = E_OK;
	}
	else {
		ercd = E_TMOUT;
	}
	t_unlock_cpu();

    exit:
	LOG_PSND_DTQ_LEAVE(ercd);
	return(ercd);
}

#endif /* __psnd_dtq */

/*
 *  �ǡ������塼�ؤ������ʥݡ���󥰡��󥿥�������ƥ������ѡ�
 */
#ifdef __ipsnd_dtq

SYSCALL ER
ipsnd_dtq(ID dtqid, VP_INT data)
{
	DTQCB	*dtqcb;
	TCB	*tcb;
	ER	ercd;

	LOG_IPSND_DTQ_ENTER(dtqid, data);
	CHECK_INTCTX_UNL();
	CHECK_DTQID(dtqid);
	dtqcb = get_dtqcb(dtqid);

	i_lock_cpu();
	if ((tcb = send_data_rwait(dtqcb, data)) != NULL) {
		if (wait_complete(tcb)) {
			reqflg = TRUE;
		}
		ercd = E_OK;
	}
	else if (enqueue_data(dtqcb, data)) {
		ercd = E_OK;
	}
	else {
		ercd = E_TMOUT;
	}
	i_unlock_cpu();

    exit:
	LOG_IPSND_DTQ_LEAVE(ercd);
	return(ercd);
}

#endif /* __ipsnd_dtq */

/*
 *  �ǡ������塼�ؤ������ʥ����ॢ���Ȥ����
 */
#ifdef __tsnd_dtq

SYSCALL ER
tsnd_dtq(ID dtqid, VP_INT data, TMO tmout)
{
	DTQCB	*dtqcb;
	WINFO_DTQ winfo;
	TMEVTB	tmevtb;
	TCB	*tcb;
	ER	ercd;

	LOG_TSND_DTQ_ENTER(dtqid, data, tmout);
	CHECK_DISPATCH();
	CHECK_DTQID(dtqid);
	CHECK_TMOUT(tmout);
	dtqcb = get_dtqcb(dtqid);

	t_lock_cpu();
	if ((tcb = send_data_rwait(dtqcb, data)) != NULL) {
		if (wait_complete(tcb)) {
			dispatch();
		}
		ercd = E_OK;
	}
	else if (enqueue_data(dtqcb, data)) {
		ercd = E_OK;
	}
	else if (tmout == TMO_POL) {
		ercd = E_TMOUT;
	}
	else {
		winfo.data = data;
		wobj_make_wait_tmout((WOBJCB *) dtqcb, (WINFO_WOBJ *) &winfo,
						&tmevtb, tmout);
		dispatch();
		ercd = winfo.winfo.wercd;
	}
	t_unlock_cpu();

    exit:
	LOG_TSND_DTQ_LEAVE(ercd);
	return(ercd);
}

#endif /* __tsnd_dtq */

/*
 *  �ǡ������塼�ؤζ�������
 */
#ifdef __fsnd_dtq

SYSCALL ER
fsnd_dtq(ID dtqid, VP_INT data)
{
	DTQCB	*dtqcb;	
	TCB	*tcb;
	ER	ercd;

	LOG_FSND_DTQ_ENTER(dtqid, data);
	CHECK_TSKCTX_UNL();
	CHECK_DTQID(dtqid);
	dtqcb = get_dtqcb(dtqid);
	CHECK_ILUSE(dtqcb->dtqinib->dtqcnt > 0);

	t_lock_cpu();
	if ((tcb = send_data_rwait(dtqcb, data)) != NULL) {
		if (wait_complete(tcb)) {
			dispatch();
		}
	}
	else {
		force_enqueue_data(dtqcb, data);
	}
	ercd = E_OK;
	t_unlock_cpu();

    exit:
	LOG_FSND_DTQ_LEAVE(ercd);
	return(ercd);
}

#endif /* __fsnd_dtq */

/*
 *  �ǡ������塼�ؤζ����������󥿥�������ƥ������ѡ�
 */
#ifdef __ifsnd_dtq

SYSCALL ER
ifsnd_dtq(ID dtqid, VP_INT data)
{
	DTQCB	*dtqcb;
	TCB	*tcb;
	ER	ercd;

	LOG_IFSND_DTQ_ENTER(dtqid, data);
	CHECK_INTCTX_UNL();
	CHECK_DTQID(dtqid);
	dtqcb = get_dtqcb(dtqid);
	CHECK_ILUSE(dtqcb->dtqinib->dtqcnt > 0);

	i_lock_cpu();
	if ((tcb = send_data_rwait(dtqcb, data)) != NULL) {
		if (wait_complete(tcb)) {
			reqflg = TRUE;
		}
	}
	else {
		force_enqueue_data(dtqcb, data);
	}
	ercd = E_OK;
	i_unlock_cpu();

    exit:
	LOG_IFSND_DTQ_LEAVE(ercd);
	return(ercd);
}

#endif /* __ifsnd_dtq */

/*
 *  �ǡ������塼����μ���
 */
#ifdef __rcv_dtq

SYSCALL ER
rcv_dtq(ID dtqid, VP_INT *p_data)
{
	DTQCB	*dtqcb;
	WINFO_DTQ winfo;
	TCB	*tcb;
	VP_INT	data;
	ER	ercd;

	LOG_RCV_DTQ_ENTER(dtqid, p_data);
	CHECK_DISPATCH();
	CHECK_DTQID(dtqid);
	dtqcb = get_dtqcb(dtqid);

	t_lock_cpu();
	if (dequeue_data(dtqcb, p_data)) {
		if ((tcb = receive_data_swait(dtqcb, &data)) != NULL) {
			enqueue_data(dtqcb, data);
			if (wait_complete(tcb)) {
				dispatch();
			}
		}
		ercd = E_OK;
	}
	else if ((tcb = receive_data_swait(dtqcb, p_data)) != NULL) {
		if (wait_complete(tcb)) {
			dispatch();
		}
		ercd = E_OK;
	}
	else {
		runtsk->tstat = (TS_WAITING | TS_WAIT_WOBJ);
		make_wait(&(winfo.winfo));
		queue_insert_prev(&(dtqcb->rwait_queue),
					&(runtsk->task_queue));
		winfo.wobjcb = (WOBJCB *) dtqcb;
		LOG_TSKSTAT(runtsk);
		dispatch();
		ercd = winfo.winfo.wercd;
		if (ercd == E_OK) {
			*p_data = winfo.data;
		}
	}
	t_unlock_cpu();

    exit:
	LOG_RCV_DTQ_LEAVE(ercd, *p_data);
	return(ercd);
}

#endif /* __rcv_dtq */

/*
 *  �ǡ������塼����μ����ʥݡ���󥰡�
 */
#ifdef __prcv_dtq

SYSCALL ER
prcv_dtq(ID dtqid, VP_INT *p_data)
{
	DTQCB	*dtqcb;
	TCB	*tcb;
	VP_INT	data;
	ER	ercd;

	LOG_PRCV_DTQ_ENTER(dtqid, p_data);
	CHECK_TSKCTX_UNL();
	CHECK_DTQID(dtqid);
	dtqcb = get_dtqcb(dtqid);

	t_lock_cpu();
	if (dequeue_data(dtqcb, p_data)) {
		if ((tcb = receive_data_swait(dtqcb, &data)) != NULL) {
			enqueue_data(dtqcb, data);
			if (wait_complete(tcb)) {
				dispatch();
			}
		}
		ercd = E_OK;
	}
	else if ((tcb = receive_data_swait(dtqcb, p_data)) != NULL) {
		if (wait_complete(tcb)) {
			dispatch();
		}
		ercd = E_OK;
	}
	else {
		ercd = E_TMOUT;
	}
	t_unlock_cpu();

    exit:
	LOG_PRCV_DTQ_LEAVE(ercd, *p_data);
	return(ercd);
}

#endif /* __prcv_dtq */

/*
 *  �ǡ������塼����μ����ʥ����ॢ���Ȥ����
 */
#ifdef __trcv_dtq

SYSCALL ER
trcv_dtq(ID dtqid, VP_INT *p_data, TMO tmout)
{
	DTQCB	*dtqcb;
	WINFO_DTQ winfo;
	TMEVTB	tmevtb;
	TCB	*tcb;
	VP_INT	data;
	ER	ercd;

	LOG_TRCV_DTQ_ENTER(dtqid, p_data, tmout);
	CHECK_DISPATCH();
	CHECK_DTQID(dtqid);
	CHECK_TMOUT(tmout);
	dtqcb = get_dtqcb(dtqid);

	t_lock_cpu();
	if (dequeue_data(dtqcb, p_data)) {
		if ((tcb = receive_data_swait(dtqcb, &data)) != NULL) {
			enqueue_data(dtqcb, data);
			if (wait_complete(tcb)) {
				dispatch();
			}
		}
		ercd = E_OK;
	}
	else if ((tcb = receive_data_swait(dtqcb, p_data)) != NULL) {
		if (wait_complete(tcb)) {
			dispatch();
		}
		ercd = E_OK;
	}
	else if (tmout == TMO_POL) {
		ercd = E_TMOUT;
	}
	else {
		runtsk->tstat = (TS_WAITING | TS_WAIT_WOBJ);
		make_wait_tmout(&(winfo.winfo), &tmevtb, tmout);
		queue_insert_prev(&(dtqcb->rwait_queue),
					&(runtsk->task_queue));
		winfo.wobjcb = (WOBJCB *) dtqcb;
		LOG_TSKSTAT(runtsk);
		dispatch();
		ercd = winfo.winfo.wercd;
		if (ercd == E_OK) {
			*p_data = winfo.data;
		}
	}
	t_unlock_cpu();

    exit:
	LOG_TRCV_DTQ_LEAVE(ercd, *p_data);
	return(ercd);
}

#endif /* __trcv_dtq */
