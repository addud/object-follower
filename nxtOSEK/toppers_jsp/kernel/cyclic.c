/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2006 by Embedded and Real-Time Systems Laboratory
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
 *  @(#) $Id: cyclic.c,v 1.11 2006/02/12 05:29:32 hiro Exp $
 */

/*
 *	�����ϥ�ɥ鵡ǽ
 */

#include "jsp_kernel.h"
#include "check.h"
#include "cyclic.h"

/*
 *  �����ϥ�ɥ�ID�κ����͡�kernel_cfg.c��
 */
extern const ID	tmax_cycid;

/*
 *  �����ϥ�ɥ������֥�å��Υ��ꥢ��kernel_cfg.c��
 */
extern const CYCINIB	cycinib_table[];

/*
 *  �����ϥ�ɥ�����֥�å��Υ��ꥢ��kernel_cfg.c��
 */
extern CYCCB	cyccb_table[];

/*
 *  �����ϥ�ɥ�ο�
 */
#define TNUM_CYC	((UINT)(tmax_cycid - TMIN_CYCID + 1))

/*
 *  �����ϥ�ɥ�ID��������ϥ�ɥ�����֥�å�����Ф�����Υޥ���
 */
#define INDEX_CYC(cycid)	((UINT)((cycid) - TMIN_CYCID))
#define get_cyccb(cycid)	(&(cyccb_table[INDEX_CYC(cycid)]))

/*
 *  �����ޤ�������������ϥ�ɥ�η�
 */
typedef void	(*CYCHDR)(VP_INT exinf);

/*
 *  �����ϥ�ɥ鵡ǽ�ν����
 */
#ifdef __cycini

void
cyclic_initialize()
{
	UINT	i;
	CYCCB	*cyccb;

	for (cyccb = cyccb_table, i = 0; i < TNUM_CYC; cyccb++, i++) {
		cyccb->cycinib = &(cycinib_table[i]);
		if ((cyccb->cycinib->cycatr & TA_STA) != 0) {
			cyccb->cycsta = TRUE;
			tmevtb_enqueue_cyc(cyccb,
					(EVTTIM)(cyccb->cycinib->cycphs));
		}
		else {
			cyccb->cycsta = FALSE;
		}
	}
}

#endif /* __cycini */

/*
 *  �����ϥ�ɥ鵯ư�Τ���Υ����।�٥�ȥ֥�å�����Ͽ
 */
#ifdef __cycenq

void
tmevtb_enqueue_cyc(CYCCB *cyccb, EVTTIM evttim)
{
	tmevtb_enqueue_evttim(&(cyccb->tmevtb), evttim,
				(CBACK) call_cychdr, (VP) cyccb);
	cyccb->evttim = evttim;
}

#endif /* __cycenq */

/*
 *  �����ϥ�ɥ��ư���
 */
#ifdef __sta_cyc

SYSCALL ER
sta_cyc(ID cycid)
{
	CYCCB	*cyccb;
	ER	ercd;

	LOG_STA_CYC_ENTER(cycid);
	CHECK_TSKCTX_UNL();
	CHECK_CYCID(cycid);
	cyccb = get_cyccb(cycid);

	t_lock_cpu();
	if (cyccb->cycsta) {
		tmevtb_dequeue(&(cyccb->tmevtb));
	}
	else {
		cyccb->cycsta = TRUE;
	}
	tmevtb_enqueue_cyc(cyccb, base_time + cyccb->cycinib->cyctim);
	ercd = E_OK;
	t_unlock_cpu();

    exit:
	LOG_STA_CYC_LEAVE(ercd);
	return(ercd);
}

#endif /* __sta_cyc */

/*
 *  �����ϥ�ɥ��ư�����
 */
#ifdef __stp_cyc

SYSCALL ER
stp_cyc(ID cycid)
{
	CYCCB	*cyccb;
	ER	ercd;

	LOG_STP_CYC_ENTER(cycid);
	CHECK_TSKCTX_UNL();
	CHECK_CYCID(cycid);
	cyccb = get_cyccb(cycid);

	t_lock_cpu();
	if (cyccb->cycsta) {
		cyccb->cycsta = FALSE;
		tmevtb_dequeue(&(cyccb->tmevtb));
	}
	ercd = E_OK;
	t_unlock_cpu();

    exit:
	LOG_STP_CYC_LEAVE(ercd);
	return(ercd);
}

#endif /* __stp_cyc */

/*
 *  �����ϥ�ɥ鵯ư�롼����
 */
#ifdef __cyccal

void
call_cychdr(CYCCB *cyccb)
{
	/*
	 *  ����ε�ư�Τ���Υ����।�٥�ȥ֥�å�����Ͽ���롥
	 *
	 *  Ʊ��������ƥ��å��Ǽ����ϥ�ɥ����ٵ�ư���٤����ˤϡ�
	 *  ���δؿ����� isig_tim ����ä���ˡ����٤��δؿ����ƤФ��
	 *  ���Ȥˤʤ롥
	 */
	tmevtb_enqueue_cyc(cyccb, cyccb->evttim + cyccb->cycinib->cyctim);

	/*
	 *  �����ϥ�ɥ��CPU��å�������֤ǸƤӽФ���
	 */
	i_unlock_cpu();
	LOG_CYC_ENTER(cyccb);
	(*((CYCHDR)(cyccb->cycinib->cychdr)))(cyccb->cycinib->exinf);
	LOG_CYC_LEAVE(cyccb);
	i_lock_cpu();
}

#endif /* __cyccal */
