/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *                2003      by  Advanced Data Controls, Corp
 *  Copyright (C) 2006 by GJ Business Division RICOH COMPANY,LTD. JAPAN
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
 *  @(#) $Id: hw_timer.h,v 1.3 2006/06/18 09:14:24 roi Exp $
 */

/*
 *  CPU��¸�����ޥ⥸�塼���At91sam7s�ѡ�
 *  TIMER1(24Mhz����)�����
 */

#ifndef _HW_TIMER_H_
#define _HW_TIMER_H_

#include <s_services.h>
#include <at91sam7s.h>

/*
 *  �����޳���ߤγ�����ֹ�
 */
#define INHNO_TIMER    IRQ_TC0_PID

#ifndef _MACRO_ONLY

/*
 *  �������ͤ�����ɽ���η�
 */
typedef UW    CLOCK;

/*
 *  �������ͤ�����ɽ���ȥߥ��á�����ñ�̤Ȥ��Ѵ�
 *  TIMER_CLOCK �ϥ������åȥܡ����������
 */
#define TO_CLOCK(nume, deno) (TIMER_CLOCK * (nume) / (deno))
#define TO_USEC(clock)       ((clock) * 1000 / TIMER_CLOCK)

/*
 *  ����Ǥ������Υ����޼�����ñ�̤�����ɽ����
 */
#define MAX_CLOCK    ((CLOCK) 0xffffffff)
/*
 *  �����ޤθ����ͤ�����ȯ�������ͤȤߤʤ�����Ƚ��
 */
#define GET_TOLERANCE    100
#define BEFORE_IREQ(clock) \
        ((clock) >= TO_CLOCK(TIC_NUME, TIC_DENO) - GET_TOLERANCE)

/*
 *  �����ޤε�ư����
 *
 *  �����ޤ�������������Ū�ʥ����޳�����׵��ȯ�������롥
 */
Inline void
hw_timer_initialize()
{
    CLOCK    cyc = TO_CLOCK(TIC_NUME, TIC_DENO);

    /*
     *  �����޴�Ϣ������
     */
	/* ����å����͡��֥� */
    sil_wrw_mem((VP)(TADR_PMC_BASE+TOFF_PMC_PCER), (1<<IRQ_TC0_PID));
    /* ��������� */
    sil_wrw_mem((VP)(TADR_TC_BASE+TOFF_TC_CCR), TC_CLKDIS);
    sil_wrw_mem((VP)(TADR_TC_BASE+TOFF_TC_IDR), 0xFFFFFFFF);
    /* �����޾���ͤΥ����å� */
    assert(cyc <= MAX_CLOCK);
    /* ��������ͤ򥻥å� */
	sil_wrw_mem((VP)(TADR_TC_BASE+TOFF_TC_CMR), TC_CLKS_MCK8);	/* 47,923,200Hz/8=5,990,400Hz */
	sil_wrw_mem((VP)(TADR_TC_BASE+TOFF_TC_CMR), sil_rew_mem((VP)(TADR_TC_BASE+TOFF_TC_CMR)) | TC_WAVESEL10);
    sil_wrw_mem((VP)(TADR_TC_BASE+TOFF_TC_RC), cyc);
    /* ����ߤΥ��ꥢ  */
    sil_wrw_mem((VP)(TADR_TC_BASE+TOFF_TC_IER), TC_CPCS);
    /* ������ȥ�������   */
    sil_wrw_mem((VP)(TADR_TC_BASE+TOFF_TC_CCR), (TC_CLKEN|TC_SWTRG));
}

/*
 *  �����޳�����׵�Υ��ꥢ
 */
Inline void
hw_timer_int_clear()
{
    sil_rew_mem((VP)(TADR_TC_BASE+TOFF_TC_SR));
}

/*
 *  �����ޤ���߽���
 */
Inline void
hw_timer_terminate()
{
    /* �ڥ�ǥ��󥰥ӥåȤ򥯥ꥢ */
	sil_rew_mem((VP)(TADR_TC_BASE+TOFF_TC_SR));
	sil_wrw_mem((VP)(TADR_AIC_BASE+TOFF_AIC_EOICR), 0);
    /* ��������� */
	sil_wrw_mem((VP)(TADR_TC_BASE+TOFF_TC_CCR), TC_CLKDIS);
    /* ������Ե���*/
    sil_wrw_mem((VP)(TADR_TC_BASE+TOFF_TC_IDR), TC_CPCS);
}

/*
 *  �����ޤθ����ͤ��ɤߤ���
 *
 *  ����߶ػ߶����ǸƤӽФ����ȡ�
 */
Inline CLOCK
hw_timer_get_current(void)
{
    return(TO_CLOCK(TIC_NUME, TIC_DENO) - sil_rew_mem((VP)TADR_TC_BASE+TOFF_TC_CV));
}

Inline BOOL
hw_timer_fetch_interrupt(void)
{
    return(sil_rew_mem((VP)(TADR_AIC_BASE+TOFF_AIC_IPR)) & (1<<IRQ_TC0_PID));
}

#endif /* _MACRO_ONLY */
#endif /* _HW_TIMER_H_ */



