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
 *  @(#) $Id: time_event.c,v 1.9 2006/02/12 05:28:07 hiro Exp $
 */

/*
 *	�����।�٥�ȴ����⥸�塼��
 */

#include "jsp_kernel.h"
#include "check.h"
#include "time_event.h"

/*
 *  �����।�٥�ȥҡ������ޥ���
 */
#define	PARENT(index)	((index) >> 1)		/* �ƥΡ��ɤ���� */
#define	LCHILD(index)	((index) << 1)		/* ���λҥΡ��ɤ���� */
#define	TMEVT_NODE(index)	(tmevt_heap[(index) - 1])

/*
 *  ���٥��ȯ��������ӥޥ���
 *
 *  ���٥��ȯ������ϡ�current_time ����������ͤ���Ӥ��롥���ʤ����
 *  current_time ��Ǿ��͡ʺǤ�ᤤ����ˡ�current_time - 1 ��������
 *  �ʺǤ�󤤻���ˤȤߤʤ�����Ӥ��롥
 */
#define	EVTTIM_LT(t1, t2) (((t1) - current_time) < ((t2) - current_time))
#define	EVTTIM_LE(t1, t2) (((t1) - current_time) <= ((t2) - current_time))

#ifdef __tmeini

/*
 *  �����ƥ����Υ��ե��å�
 */
SYSTIM	systim_offset;

/*
 *  ���ߤΥ����ƥ�����ñ��: �ߥ��á�
 *
 *  ��̩�ˤϡ����Υ�����ƥ��å��Υ����ƥ���
 */
SYSTIM	current_time;

/*
 *  ���Υ�����ƥ��å��Υ����ƥ�����ñ��: 1�ߥ��á�
 */
SYSTIM	next_time;

/*
 *  �����ƥ�����ѻ����ѿ���ñ��: 1/TIM_DENO�ߥ��á�
 */
#if TIC_DENO != 1
UINT	next_subtime;
#endif /* TIC_DENO != 1 */

/*
 *  �����।�٥�ȥҡ��פκǸ�λ����ΰ�Υ���ǥå���
 */
UINT	last_index;

/*
 *  �����ޥ⥸�塼��ν����
 */
void
tmevt_initialize(void)
{
	systim_offset = 0;
	current_time = 0;
#if TIC_DENO == 1
	next_time = current_time + TIC_NUME;
#else /* TIC_DENO == 1 */
	next_subtime += TIC_NUME;
	next_time = current_time + next_subtime / TIC_DENO;
	next_subtime %= TIC_DENO;
#endif /* TIC_DENO == 1 */
	last_index = 0;
}

#endif /* __tmeini */

/*
 *  �����।�٥�Ȥ��������֤�������õ��
 *
 *  ���� time ��ȯ�����륿���।�٥�Ȥ���������Ρ��ɤ�����뤿��ˡ�
 *  �ҡ��פξ�˸����äƶ��Ρ��ɤ��ư�����롥��ư���ζ��Ρ��ɤΰ��֤� 
 *  index ���Ϥ��ȡ���ư��ζ��Ρ��ɤΰ��֡ʤ��ʤ���������֡ˤ��֤���
 */
#ifdef __tmeup

UINT
tmevt_up(UINT index, EVTTIM time)
{
	UINT	parent;

	while (index > 1) {
		/*
		 *  �ƥΡ��ɤΥ��٥��ȯ������������ᤤ�ʤޤ���Ʊ����
		 *  �ʤ�С�index ���������֤ʤΤǥ롼�פ�ȴ���롥
		 */
		parent = PARENT(index);
		if (EVTTIM_LE(TMEVT_NODE(parent).time, time)) {
			break;
		}

		/*
		 *  �ƥΡ��ɤ� index �ΰ��֤˰�ư�����롥
		 */
		TMEVT_NODE(index) = TMEVT_NODE(parent);
		TMEVT_NODE(index).tmevtb->index = index;

		/*
		 *  index ��ƥΡ��ɤΰ��֤˹�����
		 */
		index = parent;
	}
	return(index);
}

#endif /* __tmeup */

/*
 *  �����।�٥�Ȥ��������֤򲼸�����õ��
 *
 *  ���� time ��ȯ�����륿���।�٥�Ȥ���������Ρ��ɤ�����뤿��ˡ�
 *  �ҡ��פβ��˸����äƶ��Ρ��ɤ��ư�����롥��ư���ζ��Ρ��ɤΰ��֤� 
 *  index ���Ϥ��ȡ���ư��ζ��Ρ��ɤΰ��֡ʤ��ʤ���������֡ˤ��֤���
 */
#ifdef __tmedown

UINT
tmevt_down(UINT index, EVTTIM time)
{
	UINT	child;

	while ((child = LCHILD(index)) <= last_index) {
		/*
		 *  �����λҥΡ��ɤΥ��٥��ȯ���������Ӥ����ᤤ����
		 *  �ҥΡ��ɤΰ��֤� child �����ꤹ�롥�ʲ��λҥΡ���
		 *  �ϡ����������Ф줿���λҥΡ��ɤΤ��ȡ�
		 */
		if (child + 1 <= last_index
			&& EVTTIM_LT(TMEVT_NODE(child + 1).time,
				  TMEVT_NODE(child).time)) {
			child = child + 1;
		}

		/*
		 *  �ҥΡ��ɤΥ��٥��ȯ������������٤��ʤޤ���Ʊ����
		 *  �ʤ�С�index ���������֤ʤΤǥ롼�פ�ȴ���롥
		 */
		if (EVTTIM_LE(time, TMEVT_NODE(child).time)) {
			break;
		}

		/*
		 *  �ҥΡ��ɤ� index �ΰ��֤˰�ư�����롥
		 */
		TMEVT_NODE(index) = TMEVT_NODE(child);
		TMEVT_NODE(index).tmevtb->index = index;

		/*
		 *  index ��ҥΡ��ɤΰ��֤˹�����
		 */
		index = child;
	}
	return(index);
}

#endif /* __tmedown */

/*
 * �����।�٥�ȥҡ��פؤ���Ͽ
 *
 *  �����।�٥�ȥ֥�å� tmevtb ��time �ǻ��ꤷ�����֤��в��˥�
 *  �٥�Ȥ�ȯ������褦�ˡ������।�٥�ȥҡ��פ���Ͽ���롥
 */
#ifdef __tmeins

void
tmevtb_insert(TMEVTB *tmevtb, EVTTIM time)
{
	UINT	index;

	/*
	 *  last_index �򥤥󥯥���Ȥ��������������������֤�õ����
	 */
	index = tmevt_up(++last_index, time);

	/*
	 *  �����।�٥�Ȥ� index �ΰ��֤��������롥
	 */ 
	TMEVT_NODE(index).time = time;
	TMEVT_NODE(index).tmevtb = tmevtb;
	tmevtb->index = index;
}

#endif /* __tmeins */

/*
 *  �����।�٥�ȥҡ��פ���κ��
 */
#ifdef __tmedel

void
tmevtb_delete(TMEVTB *tmevtb)
{
	UINT	index = tmevtb->index;
	UINT	parent;
	EVTTIM	event_time = TMEVT_NODE(last_index).time;

	/*
	 *  ����ˤ�꥿���।�٥�ȥҡ��פ����ˤʤ���ϲ��⤷�ʤ���
	 */
	if (--last_index == 0) {
		return;
	}

	/*
	 *  ��������Ρ��ɤΰ��֤˺Ǹ�ΥΡ��ɡ�last_index + 1 �ΰ���
	 *  �ΥΡ��ɡˤ��������������Ŭ�ڤʰ��֤ذ�ư�����롥�ºݤˤϡ�
	 *  �Ǹ�ΥΡ��ɤ�ºݤ���������ΤǤϤʤ�����������Ρ��ɤΰ�
	 *  �֤����Ρ��ɤˤʤ�Τǡ��Ǹ�ΥΡ��ɤ��������٤����֤ظ���
	 *  �ƶ��Ρ��ɤ��ư�����롥
	 *  �Ǹ�ΥΡ��ɤΥ��٥��ȯ�����郎����������Ρ��ɤοƥΡ���
	 *  �Υ��٥��ȯ�����������ξ��ˤϡ���˸����ä��������֤�
	 *  õ���������Ǥʤ����ˤϡ����˸����ä�õ����
	 */
	if (index > 1 && EVTTIM_LT(event_time,
				TMEVT_NODE(parent = PARENT(index)).time)) {
		/*
		 *  �ƥΡ��ɤ� index �ΰ��֤˰�ư�����롥
		 */
		TMEVT_NODE(index) = TMEVT_NODE(parent);
		TMEVT_NODE(index).tmevtb->index = index;

		/*
		 *  ��������Ρ��ɤοƥΡ��ɤ����˸����ä��������֤�
		 *  õ����
		 */
		index = tmevt_up(parent, event_time);
	}
	else {
		/*
		 *  ��������Ρ��ɤ��鲼�˸����ä��������֤�õ����
		 */
		index = tmevt_down(index, event_time);
	}

	/*
	 *  �Ǹ�ΥΡ��ɤ� index �ΰ��֤��������롥
	 */ 
	TMEVT_NODE(index) = TMEVT_NODE(last_index + 1);
	TMEVT_NODE(index).tmevtb->index = index;
}

#endif /* __tmedel */

/*
 *  �����।�٥�ȥҡ��פ���Ƭ�ΥΡ��ɤκ��
 */
Inline void
tmevtb_delete_top(void)
{
	UINT	index;
	EVTTIM	event_time = TMEVT_NODE(last_index).time;

	/*
	 *  ����ˤ�꥿���।�٥�ȥҡ��פ����ˤʤ���ϲ��⤷�ʤ���
	 */
	if (--last_index == 0) {
		return;
	}

	/*
	 *  �롼�ȥΡ��ɤ˺Ǹ�ΥΡ��ɡ�last_index + 1 �ΰ��֤ΥΡ��ɡ�
	 *  ���������������Ŭ�ڤʰ��֤ذ�ư�����롥�ºݤˤϡ��Ǹ�ΥΡ�
	 *  �ɤ�ºݤ���������ΤǤϤʤ����롼�ȥΡ��ɤ����Ρ��ɤˤʤ�
	 *  �Τǡ��Ǹ�ΥΡ��ɤ��������٤����֤ظ����ƶ��Ρ��ɤ��ư��
	 *  ���롥
	 */
	index = tmevt_down(1, event_time);

	/*
	 *  �Ǹ�ΥΡ��ɤ� index �ΰ��֤��������롥
	 */ 
	TMEVT_NODE(index) = TMEVT_NODE(last_index + 1);
	TMEVT_NODE(index).tmevtb->index = index;
}

/*
 *  ������ƥ��å��ζ���
 *
 *  TIC_NUME < TIC_DENO �λ��ϡ�������Ȥ鷺�˻���ι������Ǥ��뤬������
 *  �������ɤ��ɤߤ䤹���ˤ��뤿��� #if ��¿�Ѥ��򤱤Ƥ��롥
 */
#ifdef __isig_tim

SYSCALL ER
isig_tim(void)
{
	TMEVTB	*tmevtb;
	ER	ercd;

	LOG_ISIG_TIM_ENTER();
	CHECK_INTCTX_UNL();
	i_lock_cpu();

	/*
	 *  next_time ��ꥤ�٥��ȯ��������ᤤ�ʤޤ���Ʊ���˥����।
	 *  �٥�Ȥ򡤥����।�٥�ȥҡ��פ���������������Хå��ؿ�
	 *  ��ƤӽФ���
	 */
	while (last_index > 0 && EVTTIM_LE(TMEVT_NODE(1).time, next_time)) {
		tmevtb = TMEVT_NODE(1).tmevtb;
		tmevtb_delete_top();
		(*(tmevtb->callback))(tmevtb->arg);

		/*
		 *  ������ͥ���٤ι⤤����ߤ�����դ��롥
		 */
		i_unlock_cpu();
		i_lock_cpu();
	}

	/*
	 *  current_time �򹹿����롥
	 */
	current_time = next_time;

	/*
	 *  next_time��next_subtime �򹹿����롥
	 */
#if TIC_DENO == 1
	next_time = current_time + TIC_NUME;
#else /* TIC_DENO == 1 */
	next_subtime += TIC_NUME % TIC_DENO;
	next_time = current_time + TIC_NUME / TIC_DENO;
	if (next_subtime >= TIC_DENO) {
		next_subtime -= TIC_DENO;
		next_time += 1u;
	}
#endif /* TIC_DENO == 1 */

	ercd = E_OK;
	i_unlock_cpu();

    exit:
	LOG_ISIG_TIM_LEAVE(ercd);
	return(ercd);
}

#endif /* __isig_tim */
