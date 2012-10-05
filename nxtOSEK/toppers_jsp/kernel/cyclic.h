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
 *  @(#) $Id: cyclic.h,v 1.5 2003/06/04 01:46:16 hiro Exp $
 */

/*
 *	�����ϥ�ɥ鵡ǽ
 */

#ifndef _CYCLIC_H_
#define _CYCLIC_H_

#include "queue.h"
#include "time_event.h"

/*
 *  �����ϥ�ɥ������֥�å�
 */
typedef struct cyclic_handler_initialization_block {
	ATR	cycatr;		/* �����ϥ�ɥ�°�� */
	VP_INT	exinf;		/* �����ϥ�ɥ�γ�ĥ���� */
	FP	cychdr;		/* �����ϥ�ɥ�ε�ư���� */
	RELTIM	cyctim;		/* �����ϥ�ɥ�ε�ư���� */
	RELTIM	cycphs;		/* �����ϥ�ɥ�ε�ư���� */
} CYCINIB;

/*
 *  �����ϥ�ɥ�����֥�å�
 */
typedef struct cyclic_handler_control_block {
	const CYCINIB *cycinib;	/* �����ϥ�ɥ������֥�å��ؤΥݥ��� */
	BOOL	cycsta;		/* �����ϥ�ɥ��ư����� */
	EVTTIM	evttim;		/* ���˼����ϥ�ɥ��ư������� */
	TMEVTB	tmevtb;		/* �����।�٥�ȥ֥�å� */
} CYCCB;

/*
 *  �����ϥ�ɥ鵡ǽ�ν����
 */
extern void	cyclic_initialize(void);

/*
 *  �����ϥ�ɥ鵯ư�Τ���Υ����।�٥�ȥ֥�å�����Ͽ
 */
extern void	tmevtb_enqueue_cyc(CYCCB *cyccb, EVTTIM evttim);

/*
 *  �����ϥ�ɥ鵯ư�롼����
 */
extern void	call_cychdr(CYCCB *cyccb);

#endif /* _CYCLIC_H_ */
