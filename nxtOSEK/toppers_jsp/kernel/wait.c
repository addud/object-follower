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
 *  @(#) $Id: wait.c,v 1.6 2003/06/04 01:46:16 hiro Exp $
 */

/*
 *	�Ԥ����ִ����⥸�塼��
 */

#include "jsp_kernel.h"
#include "wait.h"

/*
 *  �Ԥ����֤ؤΰܹԡʥ����ॢ���Ȼ����
 *
 */
#ifdef __waimake

void
make_wait_tmout(WINFO *winfo, TMEVTB *tmevtb, TMO tmout)
{
	make_non_runnable(runtsk);
	runtsk->winfo = winfo;
	if (tmout > 0) {
		winfo->tmevtb = tmevtb;
		tmevtb_enqueue(tmevtb, (RELTIM) tmout,
					(CBACK) wait_tmout, (VP) runtsk);
	}
	else {
		assert(tmout == TMO_FEVR);
		winfo->tmevtb = NULL;
	}
}

#endif /* __waimake */

/*
 *  �Ԥ�����Τ���Υ��������֤ι���
 *
 *  tcb �ǻ��ꤵ��륿�������Ԥ��������褦���������֤򹹿����롥��
 *  ��������륿�������¹ԤǤ�����֤ˤʤ���ϡ���ǥ����塼�ˤĤʤ���
 *  �ޤ����ǥ����ѥå���ɬ�פʾ��ˤ� TRUE ���֤���
 */
Inline BOOL
make_non_wait(TCB *tcb)
{
	assert(TSTAT_WAITING(tcb->tstat));

	if (!(TSTAT_SUSPENDED(tcb->tstat))) {
		/*
		 *  �Ԥ����֤���¹ԤǤ�����֤ؤ�����
		 */
		return(make_runnable(tcb));
	}
	else {
		/*
		 *  ����Ԥ����֤��鶯���Ԥ����֤ؤ�����
		 */
		tcb->tstat = TS_SUSPENDED;
		LOG_TSKSTAT(tcb);
		return(FALSE);
	}
}

/*
 *  �Ԥ����
 */
#ifdef __waicmp

BOOL
wait_complete(TCB *tcb)
{
	if (tcb->winfo->tmevtb != NULL) {
		tmevtb_dequeue(tcb->winfo->tmevtb);
	}
	tcb->winfo->wercd = E_OK;
	return(make_non_wait(tcb));
}

#endif /* __waicmp */

/*
 *  �����ॢ���Ȥ�ȼ���Ԥ����
 */
#ifdef __waitmo

void
wait_tmout(TCB *tcb)
{
	if ((tcb->tstat & TS_WAIT_WOBJ) != 0) {
		queue_delete(&(tcb->task_queue));
	}
	tcb->winfo->wercd = E_TMOUT;
	if (make_non_wait(tcb)) {
		reqflg = TRUE;
	}
}

#endif /* __waitmo */
#ifdef __waitmook

void
wait_tmout_ok(TCB *tcb)
{
	tcb->winfo->wercd = E_OK;
	if (make_non_wait(tcb)) {
		reqflg = TRUE;
	}
}

#endif /* __waitmook */

/*
 *  �Ԥ����֤ζ������
 */
#ifdef __waican

void
wait_cancel(TCB *tcb)
{
	if (tcb->winfo->tmevtb != NULL) {
		tmevtb_dequeue(tcb->winfo->tmevtb);
	}
	if ((tcb->tstat & TS_WAIT_WOBJ) != 0) {
		queue_delete(&(tcb->task_queue));
	}
}

#endif /* __waican */
#ifdef __wairel

BOOL
wait_release(TCB *tcb)
{
	wait_cancel(tcb);
	tcb->winfo->wercd = E_RLWAI;
	return(make_non_wait(tcb));
}

#endif /* __wairel */

/*
 *  ��������ͥ���ٽ���Ԥ����塼�ؤ�����
 */
Inline void
queue_insert_tpri(TCB *tcb, QUEUE *queue)
{
	QUEUE	*entry;
	UINT	priority = tcb->priority;

	for (entry = queue->next; entry != queue; entry = entry->next) {
		if (priority < ((TCB *) entry)->priority) {
			break;
		}
	}
	queue_insert_prev(entry, &(tcb->task_queue));
}

/*
 *  �¹���Υ�������Ʊ�����̿����֥������Ȥ��Ԥ����塼�ؤ�����
 */
Inline void
wobj_queue_insert(WOBJCB *wobjcb)
{
	if ((wobjcb->wobjinib->wobjatr & TA_TPRI) != 0) {
		queue_insert_tpri(runtsk, &(wobjcb->wait_queue));
	}
	else {
		queue_insert_prev(&(wobjcb->wait_queue),
					&(runtsk->task_queue));
	}
}

/*
 *  Ʊ�����̿����֥������Ȥ��Ф����Ԥ����֤ؤΰܹ�
 */
#ifdef __wobjwai

void
wobj_make_wait(WOBJCB *wobjcb, WINFO_WOBJ *winfo)
{
	runtsk->tstat = (TS_WAITING | TS_WAIT_WOBJ | TS_WAIT_WOBJCB);
	make_wait(&(winfo->winfo));
	wobj_queue_insert(wobjcb);
	winfo->wobjcb = wobjcb;
	LOG_TSKSTAT(runtsk);
}

#endif /* __wobjwai */
#ifdef __wobjwaitmo

void
wobj_make_wait_tmout(WOBJCB *wobjcb, WINFO_WOBJ *winfo,
					TMEVTB *tmevtb, TMO tmout)
{
	runtsk->tstat = (TS_WAITING | TS_WAIT_WOBJ | TS_WAIT_WOBJCB);
	make_wait_tmout(&(winfo->winfo), tmevtb, tmout);
	wobj_queue_insert(wobjcb);
	winfo->wobjcb = wobjcb;
	LOG_TSKSTAT(runtsk);
}

#endif /* __wobjwaitmo */
/*
 *  ��������ͥ�����ѹ����ν���
 */
#ifdef __wobjpri

void
wobj_change_priority(WOBJCB *wobjcb, TCB *tcb)
{
	if ((wobjcb->wobjinib->wobjatr & TA_TPRI) != 0) {
		queue_delete(&(tcb->task_queue));
		queue_insert_tpri(tcb, &(wobjcb->wait_queue));
	}
}

#endif /* __wobjpri */
