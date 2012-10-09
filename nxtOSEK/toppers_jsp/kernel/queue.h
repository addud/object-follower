/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2000 by Embedded and Real-Time Systems Laboratory
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
 *  @(#) $Id: queue.h,v 1.5 2003/06/04 01:46:16 hiro Exp $
 */

/*
 *	���塼���饤�֥��
 *
 *  ���Υ��塼���饤�֥��Ǥϡ����塼�إå���ޤ��󥰹�¤�Υ��֥�
 *  ��󥯥��塼�򰷤�������Ū�ˤϡ����塼�إå��μ�����ȥ�ϥ��塼��
 *  ��Ƭ�Υ���ȥꡤ������ȥ�ϥ��塼�������Υ���ȥ�Ȥ��롥�ޤ�����
 *  �塼����Ƭ�Υ���ȥ��������ȥ�ȡ����塼�������Υ���ȥ�μ�����
 *  �ȥ�ϡ����塼�إå��Ȥ��롥���Υ��塼�ϡ�������ȥꡤ������ȥ��
 *  �⼫ʬ���Ȥ�ؤ����塼�إå��Ǥ���魯��
 */

#ifndef	_QUEUE_H_
#define	_QUEUE_H_

/*
 *  ���塼�Υǡ�����¤�����
 */
typedef struct queue {
	struct queue *next;		/* ������ȥ�ؤΥݥ��� */
	struct queue *prev;		/* ������ȥ�ؤΥݥ��� */
} QUEUE;

/*
 *  ���塼�ν����
 *
 *  queue �ˤϥ��塼�إå�����ꤹ�롥
 */
Inline void
queue_initialize(QUEUE *queue)
{
	queue->prev = queue->next = queue;
}

/*
 *  ���塼��������ȥ�ؤ�����
 *
 *  queue ������ entry ���������롥queue �˥��塼�إå�����ꤷ�����
 *  �ˤϡ����塼�������� entry ���������뤳�Ȥˤʤ롥
 */
Inline void
queue_insert_prev(QUEUE *queue, QUEUE *entry)
{
	entry->prev = queue->prev;
	entry->next = queue;
	queue->prev->next = entry;
	queue->prev = entry;
}

/*
 *  ����ȥ�κ��
 *
 *  entry �򥭥塼���������롥
 */
Inline void
queue_delete(QUEUE *entry)
{
	entry->prev->next = entry->next;
	entry->next->prev = entry->prev;
}

/*
 *  ���塼�μ�����ȥ�μ�Ф�
 *
 *  queue �μ�����ȥ�򥭥塼���������������������ȥ���֤���queue
 *  �˥��塼�إå�����ꤷ�����ˤϡ����塼����Ƭ�Υ���ȥ����Ф�
 *  ���Ȥˤʤ롥queue �˶��Υ��塼����ꤷ�ƸƤӽФ��ƤϤʤ�ʤ���
 */
Inline QUEUE *
queue_delete_next(QUEUE *queue)
{
	QUEUE	*entry;

	assert(queue->next != queue);
	entry = queue->next;
	queue->next = entry->next;
	entry->next->prev = queue;
	return(entry);
}

/*
 *  ���塼�������ɤ����Υ����å�
 *
 *  queue �ˤϥ��塼�إå�����ꤹ�롥
 */
Inline BOOL
queue_empty(QUEUE *queue)
{
	if (queue->next == queue) {
		assert(queue->prev == queue);
		return(TRUE);
	}
	return(FALSE);
}

#endif /* _QUEUE_H_ */
