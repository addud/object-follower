/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2005 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
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
 *  @(#) $Id: mempfix.c,v 1.12 2005/11/12 14:55:23 hiro Exp $
 */

/*
 *	����Ĺ����ס��뵡ǽ
 */

#include "jsp_kernel.h"
#include "check.h"
#include "task.h"
#include "wait.h"
#include "mempfix.h"

/*
 *  ����Ĺ����ס���ID�κ����͡�kernel_cfg.c��
 */
extern const ID	tmax_mpfid;

/*
 *  ����Ĺ����ס��������֥�å��Υ��ꥢ��kernel_cfg.c��
 */
extern const MPFINIB	mpfinib_table[];

/*
 *  ����Ĺ����ס�������֥�å��Υ��ꥢ��kernel_cfg.c��
 */
extern MPFCB	mpfcb_table[];

/*
 *  ����Ĺ����ס���ο�
 */
#define TNUM_MPF	((UINT)(tmax_mpfid - TMIN_MPFID + 1))

/*
 *  ����Ĺ����ס���ID�������Ĺ����ס�������֥�å�����Ф���
 *  ��Υޥ���
 */
#define INDEX_MPF(mpfid)	((UINT)((mpfid) - TMIN_MPFID))
#define get_mpfcb(mpfid)	(&(mpfcb_table[INDEX_MPF(mpfid)]))

/*
 *  ����Ĺ����ס����Ԥ�����֥�å������
 */
typedef struct fixed_memorypool_waiting_information {
	WINFO	winfo;		/* ɸ����Ԥ�����֥�å� */
	WOBJCB	*wobjcb;	/* �Ԥ����֥������Ȥδ����֥�å� */
	VP	blk;		/* ������������֥�å� */
} WINFO_MPF;

/* 
 *  ����Ĺ����ס��뵡ǽ�ν����
 */
#ifdef __mpfini

void
mempfix_initialize()
{
	UINT	i;
	MPFCB	*mpfcb;

	for (mpfcb = mpfcb_table, i = 0; i < TNUM_MPF; mpfcb++, i++) {
		queue_initialize(&(mpfcb->wait_queue));
		mpfcb->mpfinib = &(mpfinib_table[i]);
		mpfcb->unused = mpfcb->mpfinib->mpf;
		mpfcb->freelist = NULL;
	}
}

#endif /* __mpfini */

/*
 *  ����Ĺ����ס��뤫��֥�å������
 */
#ifdef __mpfget

BOOL
mempfix_get_block(MPFCB *mpfcb, VP *p_blk)
{
	FREEL	*free;

	if (mpfcb->freelist != NULL) {
		free = mpfcb->freelist;
		mpfcb->freelist = free->next;
		*p_blk = (VP) free;
		return(TRUE);
	}
	else if (mpfcb->unused < mpfcb->mpfinib->limit) {
		*p_blk = mpfcb->unused;
		mpfcb->unused = (VP)((char *)(mpfcb->unused)
						+ mpfcb->mpfinib->blksz);
		return(TRUE);
	}
	return(FALSE);
}

#endif /* __mpfget */

/*
 *  ����Ĺ����֥�å��γ���
 */
#ifdef __get_mpf

SYSCALL ER
get_mpf(ID mpfid, VP *p_blk)
{
	MPFCB	*mpfcb;
	WINFO_MPF winfo;
	ER	ercd;

	LOG_GET_MPF_ENTER(mpfid, p_blk);
	CHECK_DISPATCH();
	CHECK_MPFID(mpfid);
	mpfcb = get_mpfcb(mpfid);

	t_lock_cpu();
	if (mempfix_get_block(mpfcb, p_blk)) {
		ercd = E_OK;
	}
	else {
		wobj_make_wait((WOBJCB *) mpfcb, (WINFO_WOBJ *) &winfo);
		dispatch();
		ercd = winfo.winfo.wercd;
		if (ercd == E_OK) {
			*p_blk = winfo.blk;
		}
	}
	t_unlock_cpu();

    exit:
	LOG_GET_MPF_LEAVE(ercd, *p_blk);
	return(ercd);
}

#endif /* __get_mpf */

/*
 *  ����Ĺ����֥�å��γ����ʥݡ���󥰡�
 */
#ifdef __pget_mpf

SYSCALL ER
pget_mpf(ID mpfid, VP *p_blk)
{
	MPFCB	*mpfcb;
	ER	ercd;

	LOG_PGET_MPF_ENTER(mpfid, p_blk);
	CHECK_TSKCTX_UNL();
	CHECK_MPFID(mpfid);
	mpfcb = get_mpfcb(mpfid);

	t_lock_cpu();
	if (mempfix_get_block(mpfcb, p_blk)) {
		ercd = E_OK;
	}
	else {
		ercd = E_TMOUT;
	}
	t_unlock_cpu();

    exit:
	LOG_PGET_MPF_LEAVE(ercd, *p_blk);
	return(ercd);
}

#endif /* __pget_mpf */

/*
 *  ����Ĺ����֥�å��γ����ʥ����ॢ���Ȥ����
 */
#ifdef __tget_mpf

SYSCALL ER
tget_mpf(ID mpfid, VP *p_blk, TMO tmout)
{
	MPFCB	*mpfcb;
	WINFO_MPF winfo;
	TMEVTB	tmevtb;
	ER	ercd;

	LOG_TGET_MPF_ENTER(mpfid, p_blk, tmout);
	CHECK_DISPATCH();
	CHECK_MPFID(mpfid);
	CHECK_TMOUT(tmout);
	mpfcb = get_mpfcb(mpfid);

	t_lock_cpu();
	if (mempfix_get_block(mpfcb, p_blk)) {
		ercd = E_OK;
	}
	else if (tmout == TMO_POL) {
		ercd = E_TMOUT;
	}
	else {
		wobj_make_wait_tmout((WOBJCB *) mpfcb, (WINFO_WOBJ *) &winfo,
						&tmevtb, tmout);
		dispatch();
		ercd = winfo.winfo.wercd;
		if (ercd == E_OK) {
			*p_blk = winfo.blk;
		}
	}
	t_unlock_cpu();

    exit:
	LOG_TGET_MPF_LEAVE(ercd, *p_blk);
	return(ercd);
}

#endif /* __tget_mpf */

/*
 *  ����Ĺ����֥�å����ֵ�
 */
#ifdef __rel_mpf

SYSCALL ER
rel_mpf(ID mpfid, VP blk)
{
	MPFCB	*mpfcb;
	TCB	*tcb;
	FREEL	*free;
	ER	ercd;
    
	LOG_REL_MPF_ENTER(mpfid, blk);
	CHECK_TSKCTX_UNL();
	CHECK_MPFID(mpfid);
	mpfcb = get_mpfcb(mpfid);
	CHECK_PAR(mpfcb->mpfinib->mpf <= blk
			&& blk < mpfcb->mpfinib->limit
			&& ((char *)(blk) - (char *)(mpfcb->mpfinib->mpf))
					% mpfcb->mpfinib->blksz == 0);

	t_lock_cpu();
	if (!(queue_empty(&(mpfcb->wait_queue)))) {
		tcb = (TCB *) queue_delete_next(&(mpfcb->wait_queue));
		((WINFO_MPF *)(tcb->winfo))->blk = blk;
		if (wait_complete(tcb)) {
			dispatch();
		}
		ercd = E_OK;
	}
	else {
		free = (FREEL *) blk;
		free->next = mpfcb->freelist;
		mpfcb->freelist = free;
		ercd = E_OK;
	}
	t_unlock_cpu();

    exit:
	LOG_REL_MPF_LEAVE(ercd);
	return(ercd);
}

#endif /* __rel_mpf */
