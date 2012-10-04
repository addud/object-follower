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
 *  @(#) $Id: mailbox.c,v 1.8 2003/07/01 13:31:08 hiro Exp $
 */

/*
 *	�᡼��ܥå�����ǽ
 */

#include "jsp_kernel.h"
#include "check.h"
#include "task.h"
#include "wait.h"
#include "mailbox.h"

/*
 *  �᡼��ܥå���ID�κ����͡�kernel_cfg.c��
 */
extern const ID	tmax_mbxid;

/*
 *  �᡼��ܥå���������֥�å��Υ��ꥢ��kernel_cfg.c��
 */
extern const MBXINIB	mbxinib_table[];

/*
 *  �᡼��ܥå��������֥�å��Υ��ꥢ��kernel_cfg.c��
 */
extern MBXCB	mbxcb_table[];

/*
 *  �᡼��ܥå����ο�
 */
#define TNUM_MBX	((UINT)(tmax_mbxid - TMIN_MBXID + 1))

/*
 *  �᡼��ܥå���ID����᡼��ܥå��������֥�å�����Ф�����Υޥ���
 */
#define INDEX_MBX(mbxid)	((UINT)((mbxid) - TMIN_MBXID))
#define get_mbxcb(mbxid)	(&(mbxcb_table[INDEX_MBX(mbxid)]))

/*
 *  �᡼��ܥå����Ԥ�����֥�å������
 */
typedef struct mailbox_waiting_information {
	WINFO	winfo;		/* ɸ����Ԥ�����֥�å� */
	WOBJCB	*wobjcb;	/* �Ԥ����֥������Ȥδ����֥�å� */
	T_MSG	*pk_msg;	/* ����������å����� */
} WINFO_MBX;

/* 
 *  �᡼��ܥå�����ǽ�ν����
 */
#ifdef __mbxini

void
mailbox_initialize()
{
	UINT	i;
	MBXCB	*mbxcb;

	for (mbxcb = mbxcb_table, i = 0; i < TNUM_MBX; mbxcb++, i++) {
		queue_initialize(&(mbxcb->wait_queue));
		mbxcb->mbxinib = &(mbxinib_table[i]);
		mbxcb->head = NULL;
	}
}

#endif /* __mbxini */

/*
 *  ��å�����ͥ���٤μ�Ф�
 */
#define	MSGPRI(pk_msg)	(((T_MSG_PRI *) pk_msg)->msgpri)

/*
 *  ͥ���ٽ��å��������塼�ؤ�����
 */
Inline void
enqueue_msg_pri(T_MSG **p_prevmsg_next, T_MSG *pk_msg)
{
	T_MSG	*pk_nextmsg;

	while ((pk_nextmsg = *p_prevmsg_next) != NULL) {
		if (MSGPRI(pk_nextmsg) > MSGPRI(pk_msg)) {
			break;
		}
		p_prevmsg_next = &(pk_nextmsg->next);
	}
	pk_msg->next = pk_nextmsg;
	*p_prevmsg_next = pk_msg;
}

/*
 *  �᡼��ܥå����ؤ�����
 */
#ifdef __snd_mbx

SYSCALL ER
snd_mbx(ID mbxid, T_MSG *pk_msg)
{
	MBXCB	*mbxcb;
	TCB	*tcb;
	ER	ercd;
    
	LOG_SND_MBX_ENTER(mbxid, pk_msg);
	CHECK_TSKCTX_UNL();
	CHECK_MBXID(mbxid);
	mbxcb = get_mbxcb(mbxid);
	CHECK_PAR((mbxcb->mbxinib->mbxatr & TA_MPRI) == 0
		|| (TMIN_MPRI <= MSGPRI(pk_msg)
			&& MSGPRI(pk_msg) <= mbxcb->mbxinib->maxmpri));

	t_lock_cpu();
	if (!(queue_empty(&(mbxcb->wait_queue)))) {
		tcb = (TCB *) queue_delete_next(&(mbxcb->wait_queue));
		((WINFO_MBX *)(tcb->winfo))->pk_msg = pk_msg;
		if (wait_complete(tcb)) {
			dispatch();
		}
		ercd = E_OK;
	}
	else if ((mbxcb->mbxinib->mbxatr & TA_MPRI) != 0) {
		enqueue_msg_pri(&(mbxcb->head), pk_msg);
		ercd = E_OK;
	}
	else {
		pk_msg->next = NULL;
		if (mbxcb->head != NULL) {
			mbxcb->last->next = pk_msg;
		}
		else {
			mbxcb->head = pk_msg;
		}
		mbxcb->last = pk_msg;
		ercd = E_OK;
	}
	t_unlock_cpu();

    exit:
	LOG_SND_MBX_LEAVE(ercd);
	return(ercd);
}

#endif /* __snd_mbx */

/*
 *  �᡼��ܥå�������μ���
 */
#ifdef __rcv_mbx

SYSCALL ER
rcv_mbx(ID mbxid, T_MSG **ppk_msg)
{
	MBXCB	*mbxcb;
	WINFO_MBX winfo;
	ER	ercd;
    
	LOG_RCV_MBX_ENTER(mbxid, ppk_msg);
	CHECK_DISPATCH();
	CHECK_MBXID(mbxid);
	mbxcb = get_mbxcb(mbxid);
    
	t_lock_cpu();
	if (mbxcb->head != NULL) {
		*ppk_msg = mbxcb->head;
		mbxcb->head = (*ppk_msg)->next;
		ercd = E_OK;
	}
	else {
		wobj_make_wait((WOBJCB *) mbxcb, (WINFO_WOBJ *) &winfo);
		dispatch();
		ercd = winfo.winfo.wercd;
		if (ercd == E_OK) {
			*ppk_msg = winfo.pk_msg;
		}
	}
	t_unlock_cpu();

    exit:
	LOG_RCV_MBX_LEAVE(ercd, *ppk_msg);
	return(ercd);
}

#endif /* __rcv_mbx */

/*
 *  �᡼��ܥå�������μ����ʥݡ���󥰡�
 */
#ifdef __prcv_mbx

SYSCALL ER
prcv_mbx(ID mbxid, T_MSG **ppk_msg)
{
	MBXCB	*mbxcb;
	ER	ercd;
    
	LOG_PRCV_MBX_ENTER(mbxid, ppk_msg);
	CHECK_TSKCTX_UNL();
	CHECK_MBXID(mbxid);
	mbxcb = get_mbxcb(mbxid);
    
	t_lock_cpu();
	if (mbxcb->head != NULL) {
		*ppk_msg = mbxcb->head;
		mbxcb->head = (*ppk_msg)->next;
		ercd = E_OK;
	}
	else {
		ercd = E_TMOUT;
	}
	t_unlock_cpu();

    exit:
	LOG_PRCV_MBX_LEAVE(ercd, *ppk_msg);
	return(ercd);
}

#endif /* __prcv_mbx */

/*
 *  �᡼��ܥå�������μ����ʥ����ॢ���Ȥ����
 */
#ifdef __trcv_mbx

SYSCALL ER
trcv_mbx(ID mbxid, T_MSG **ppk_msg, TMO tmout)
{
	MBXCB	*mbxcb;
	WINFO_MBX winfo;
	TMEVTB	tmevtb;
	ER	ercd;
    
	LOG_TRCV_MBX_ENTER(mbxid, ppk_msg, tmout);
	CHECK_DISPATCH();
	CHECK_MBXID(mbxid);
	CHECK_TMOUT(tmout);
	mbxcb = get_mbxcb(mbxid);
    
	t_lock_cpu();
	if (mbxcb->head != NULL) {
		*ppk_msg = mbxcb->head;
		mbxcb->head = (*ppk_msg)->next;
		ercd = E_OK;
	}
	else if (tmout == TMO_POL) {
		ercd = E_TMOUT;
	}
	else {
		wobj_make_wait_tmout((WOBJCB *) mbxcb, (WINFO_WOBJ *) &winfo,
						&tmevtb, tmout);
		dispatch();
		ercd = winfo.winfo.wercd;
		if (ercd == E_OK) {
			*ppk_msg = winfo.pk_msg;
		}
	}
	t_unlock_cpu();

    exit:
	LOG_TRCV_MBX_LEAVE(ercd, *ppk_msg);
	return(ercd);
}

#endif /* __trcv_mbx */
