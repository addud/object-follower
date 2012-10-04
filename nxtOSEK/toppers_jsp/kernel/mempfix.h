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
 *  @(#) $Id: mempfix.h,v 1.5 2003/06/04 01:46:16 hiro Exp $
 */

/*
 *	����Ĺ����ס��뵡ǽ
 */

#ifndef _MEMPFIX_H_
#define _MEMPFIX_H_

#include "queue.h"

/*
 *  ����Ĺ����ס��������֥�å�
 */
typedef struct fixed_memorypool_initialization_block {
	ATR	mpfatr;		/* ����Ĺ����ס���°�� */
	UINT	blksz;		/* ����֥�å��Υ������ʴݤ᤿�͡� */
	VP	mpf;		/* ����Ĺ����ס����ΰ����Ƭ���� */
	VP	limit;		/* ����Ĺ����ס����ΰ�ξ������ */
} MPFINIB;

/*
 *  ���֥�å��ꥹ�Ȥ����
 */
typedef struct free_list {
	struct free_list *next;
} FREEL;

/*
 *  ����Ĺ����ס�������֥�å�
 */
typedef struct fixed_memorypool_control_block {
	QUEUE	wait_queue;	/* ����Ĺ����ס����Ԥ����塼 */
	const MPFINIB *mpfinib;	/* ����Ĺ����ס��������֥�å� */
	VP	unused;		/* ̤�����ΰ����Ƭ���� */
	FREEL	*freelist;	/* �����֥�å��Υꥹ�� */
} MPFCB;

/*
 *  ����Ĺ����ס��뵡ǽ�ν����
 */
extern void	mempfix_initialize(void);

/*
 *  ����Ĺ����ס��뤫��֥�å������
 */
extern BOOL	mempfix_get_block(MPFCB *mpfcb, VP *p_blk);

#endif /* _MEMPFIX_H_ */
