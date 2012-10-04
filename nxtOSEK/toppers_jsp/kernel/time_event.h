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
 *  @(#) $Id: time_event.h,v 1.8 2003/06/18 12:48:24 hiro Exp $
 */

/*
 *	�����।�٥�ȴ����⥸�塼��
 */

#ifndef _TIME_EVENT_H_
#define _TIME_EVENT_H_

/*
 *  ���٥��ȯ������Υǡ����������
 *
 *  EVTTIM �ϡ�RELTIM �Ȥ��ƻ���Ǥ����ϰϤ��⹭���ϰϤ�ɽ���Ǥ���ɬ
 *  �פ����롥����������ɥץ�ե�����Ǥϡ�RELTIM �� 16bit �ʾ�Ǥʤ�
 *  ��Фʤ�ʤ����ᡤEVTTIM �� 17bit �ʾ�Ǥ��뤳�Ȥ�ɬ�פǤ��롥����
 *  ���ᡤ16bit �ξ�礬���� UINT �ǤϤʤ���UW ��������Ƥ��롥
 */
typedef UW	EVTTIM;

/*
 *  ���л��֡�RELTIM�ˤ˻���Ǥ��������
 */
#define	TMAX_RELTIM	((((EVTTIM) 1) << (sizeof(EVTTIM) * CHAR_BIT - 1)) - 1)

/* 
 *  �����।�٥�ȥ֥�å��Υǡ����������
 */
typedef void	(*CBACK)(VP);	/* ������Хå��ؿ��η� */

typedef struct time_event_block {
	UINT	index;		/* �����।�٥�ȥҡ�����Ǥΰ��� */
	CBACK	callback;	/* ������Хå��ؿ� */
	VP	arg;		/* ������Хå��ؿ����Ϥ����� */
} TMEVTB;

/*
 *  �����।�٥�ȥҡ�����ΥΡ��ɤΥǡ����������
 */
typedef struct time_event_node {
	EVTTIM	time;		/* ���٥��ȯ������ */
	TMEVTB	*tmevtb;	/* �б����륿���।�٥�ȥ֥�å� */
} TMEVTN;

/*
 *  �����।�٥�ȥҡ��ס�kernel_cfg.c��
 */
extern TMEVTN	tmevt_heap[];

/*
 *  �����ƥ����Υ��ե��å�
 */
extern SYSTIM	systim_offset;

/*
 *  ���ߤΥ����ƥ�����ñ��: �ߥ��á�
 *
 *  �����ƥ൯ư���� 0 �˽�������졤�ʹߡ�isig_tim ���ƤФ���٤�ñĴ
 *  �����ä��롥set_tim �ˤ�ä��ѹ�����ʤ���
 */
extern SYSTIM	current_time;

/*
 *  ���Υ�����ƥ��å��Υ����ƥ�����ñ��: 1�ߥ��á�
 */
extern SYSTIM	next_time;

/*
 *  �����ƥ�����ѻ����ѿ���ñ��: 1/TIM_DENO�ߥ��á�
 *
 *  ���Υ�����ƥ��å��Υ����ƥ����β��̷�򼨤��ʾ�̷�� next_time�ˡ�
 *  TIC_DENO �� 1 �λ��ϡ����̷�Ͼ�� 0 �Ǥ��뤿�ᡤ�����ѿ���ɬ�פʤ���
 */
#if TIC_DENO != 1
extern UINT	next_subtime;
#endif /* TIC_DENO != 1 */

/*
 *  ���л��֤Υ١��������ñ��: 1�ߥ��á�
 *
 *  ���Υ�����ƥ��å��Υ����ƥ������ڤ�夲�����TIC_DENO �� 1 ��
 *  ���ϡ�next_time �� EVTTIM ���Ѵ�������Τ˰��פ��롥
 */
#if TIC_DENO == 1
#define	base_time	((EVTTIM) next_time)
#else /* TIC_DENO == 1 */
#define	base_time	((EVTTIM)(next_time + (next_subtime > 0 ? 1 : 0)))
#endif /* TIC_DENO == 1 */

/*
 *  �����।�٥�ȥҡ��פκǸ�λ����ΰ�Υ���ǥå���
 *
 *  �����।�٥�ȥҡ��פ���Ͽ����Ƥ��륿���।�٥�Ȥο��˰��פ��롥
 */
extern UINT	last_index;

/*
 *  �����।�٥�ȴ����⥸�塼��ν����
 */
extern void	tmevt_initialize(void);

/*
 *  �����।�٥�Ȥ��������֤�õ��
 */
extern UINT	tmevt_up(UINT index, EVTTIM time);
extern UINT	tmevt_down(UINT index, EVTTIM time);

/*
 *  �����।�٥�ȥҡ��פؤ���Ͽ�Ⱥ��
 */
extern void	tmevtb_insert(TMEVTB *tmevtb, EVTTIM time);
extern void	tmevtb_delete(TMEVTB *tmevtb);

/*
 *  �����।�٥�ȥ֥�å�����Ͽ�����л��ֻ����
 *
 *  time �ǻ��ꤷ�����л��֤��в��ˡ�arg ������Ȥ��� callback ����
 *  �ӽФ����褦�ˡ������।�٥�ȥ֥�å� tmevtb ����Ͽ���롥
 */
Inline void
tmevtb_enqueue(TMEVTB *tmevtb, RELTIM time, CBACK callback, VP arg)
{
	assert(time <= TMAX_RELTIM);

	tmevtb->callback = callback;
	tmevtb->arg = arg;
	tmevtb_insert(tmevtb, base_time + time);
}

/*
 *  �����।�٥�ȥ֥�å�����Ͽ�ʥ��٥��ȯ����������
 *
 *  time �ǻ��ꤷ�����٥��ȯ������ˡ�arg ������Ȥ��� callback ����
 *  �ӽФ����褦�ˡ������।�٥�ȥ֥�å� tmevtb ����Ͽ���롥
 */
Inline void
tmevtb_enqueue_evttim(TMEVTB *tmevtb, EVTTIM time, CBACK callback, VP arg)
{
	tmevtb->callback = callback;
	tmevtb->arg = arg;
	tmevtb_insert(tmevtb, time);
}

/*
 *  �����।�٥�ȥ֥�å�����Ͽ���
 */
Inline void
tmevtb_dequeue(TMEVTB *tmevtb)
{
	tmevtb_delete(tmevtb);
}

#endif /* _TIME_EVENT_H_ */
