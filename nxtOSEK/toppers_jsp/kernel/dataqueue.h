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
 *  @(#) $Id: dataqueue.h,v 1.5 2003/06/04 01:46:16 hiro Exp $
 */

/*
 *	�ǡ������塼��ǽ
 */

#ifndef _DATAQUEUE_H_
#define _DATAQUEUE_H_

#include "queue.h"

/*
 *  �ǡ������塼������֥�å�
 */
typedef struct dataqueue_initialization_block {
	ATR	dtqatr;		/* �ǡ������塼°�� */
	UINT	dtqcnt;		/* �ǡ������塼�ΰ������ */
	VP	dtq;		/* �ǡ������塼�ΰ����Ƭ���� */
} DTQINIB;

/*
 *  �ǡ������塼�����֥�å�
 */
typedef struct dataqueue_control_block {
	QUEUE	swait_queue;	/* �ǡ������塼�����Ԥ����塼 */
	const DTQINIB *dtqinib;	/* �ǡ������塼������֥�å��ؤΥݥ��� */
	QUEUE	rwait_queue;	/* �ǡ������塼�����Ԥ����塼 */
	UINT	count;		/* �ǡ������塼��Υǡ����ο� */
	UINT	head;		/* �ǽ�Υǡ����γ�Ǽ��� */
	UINT	tail;		/* �Ǹ�Υǡ����γ�Ǽ���μ� */
} DTQCB;

/*
 *  �ǡ������塼��ǽ�ν����
 */
extern void	dataqueue_initialize(void);

/*
 *  �ǡ������塼�ΰ�˥ǡ������Ǽ
 */
extern BOOL	enqueue_data(DTQCB *dtqcb, VP_INT data);

/*
 *  �ǡ������塼�ΰ�˥ǡ���������Ǽ
 */
extern void	force_enqueue_data(DTQCB *dtqcb, VP_INT data);

/*
 *  �ǡ������塼�ΰ褫��ǡ������Ф�
 */
extern BOOL	dequeue_data(DTQCB *dtqcb, VP_INT *p_data);

/*
 *  �����Ԥ����塼����Ƭ�������ؤΥǡ�������
 */
extern TCB	*send_data_rwait(DTQCB *dtqcb, VP_INT data);

/*
 *  �����Ԥ����塼����Ƭ����������Υǡ�������
 */
extern TCB	*receive_data_swait(DTQCB *dtqcb, VP_INT *p_data);

#endif /* _DATAQUEUE_H_ */
