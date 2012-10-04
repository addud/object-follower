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
 *  @(#) $Id: sample1.h,v 1.6 2003/12/20 09:13:29 takayuki Exp $
 */

/*
 *  ����ץ�ץ����(1)�Υإå��ե�����
 */

#include "cpu_defs.h"
#include "sys_defs.h"

/*
 *  �ƥ�������ͥ���٤����
 */

#define MAIN_PRIORITY	5		/* �ᥤ�󥿥�����ͥ���� */
					/* HIGH_PRIORITY ���⤯���뤳�� */

#define HIGH_PRIORITY	9		/* ����˼¹Ԥ���륿������ͥ���� */
#define MID_PRIORITY	10
#define LOW_PRIORITY	11

/*
 *  �������åȰ�¸�������CPU�㳰�ϥ�ɥ�ε�ư��ˡ�ʤɡ�
 */

#ifdef M68K

#define CPUEXC1		5		/* ��������㳰 */
#define RAISE_CPU_EXCEPTION	syslog(LOG_NOTICE, "zerodiv = %d", 10 / 0)

#elif defined(SH3)

#define CPUEXC1		224		/* ���ɥ��顼�㳰 */
#define RAISE_CPU_EXCEPTION	(*((volatile int *) 0xFFFFFEC1))

#elif defined(SH1)

#define CPUEXC1		9		/* CPU���ɥ쥹���顼�㳰 */
#define RAISE_CPU_EXCEPTION	(*((volatile int *) 0xFFFFFEC1))
#ifdef TOKIWA_SH1
#define	STACK_SIZE	512		/* �������Υ����å������� */
#endif /* TOKIWA_SH1 */

#elif defined(ARM7TDMI)

#define CPUEXC1		4		/* ���ɥ��顼�㳰 */
#define RAISE_CPU_EXCEPTION	(*((volatile int *) 0xFFFFFEC1))

#elif defined(V850)

#elif defined(H8)

#undef CPUEXC1				/* CPU�㳰�ϥ�ɥ�򥵥ݡ��Ȥ��ʤ� */

#elif defined(H8S)

#undef CPUEXC1				/* CPU�㳰�ϥ�ɥ�򥵥ݡ��Ȥ��ʤ� */
#define LOOP_REF	4000L		/* ®�ٷ�¬�ѤΥ롼�ײ�� */

#elif defined(MICROBLAZE)

#undef CPUEXC1				/* CPU�㳰�ϥ�ɥ�򥵥ݡ��Ȥ��ʤ� */
#define STACK_SIZE	2048		/* �������Υ����å������� */

#elif defined(I386)

#define CPUEXC1		0		/* ��������㳰 */
#define RAISE_CPU_EXCEPTION   syslog(LOG_NOTICE, "zerodiv = %d", 10 / 0)
#define OMIT_VGET_TIM

#elif defined(TMS320C54X)

#undef CPUEXC1				/* CPU�㳰�ϥ�ɥ�򥵥ݡ��Ȥ��ʤ� */
#define STACK_SIZE	320		/* �������Υ����å������� */
#define LOOP_REF	500000L		/* ®�ٷ�¬�ѤΥ롼�ײ�� */

#elif defined(LINUX)

#undef CPUEXC1				/* CPU�㳰�ϥ�ɥ�򥵥ݡ��Ȥ��ʤ� */
#define OMIT_VGET_TIM
#define LOOP_REF	4000000		/* ®�ٷ�¬�ѤΥ롼�ײ�� */

#elif defined(WINDOWS)

#define LOOP_REF	5000000		/* ®�ٷ�¬�ѤΥ롼�ײ�� */

#endif

/*
 *  �������åȤ˰�¸�����ǽ���Τ�����������
 */

#ifndef TASK_PORTID
#define	TASK_PORTID	1		/* ʸ�����Ϥ��륷�ꥢ��ݡ���ID */
#endif /* TASK_PORTID */

#ifndef STACK_SIZE
#define	STACK_SIZE	8192		/* �������Υ����å������� */
#endif /* STACK_SIZE */

#ifndef LOOP_REF
#define LOOP_REF	1000000		/* ®�ٷ�¬�ѤΥ롼�ײ�� */
#endif /* LOOP_REF */

/*
 *  �ؿ��Υץ�ȥ��������
 */
#ifndef _MACRO_ONLY

extern void	task(VP_INT tskno);
extern void	main_task(VP_INT exinf);
extern void	tex_routine(TEXPTN texptn, VP_INT tskno);
extern void	cyclic_handler(VP_INT exinf);
extern void	cpuexc_handler(VP p_excinf);

#endif /* _MACRO_ONLY */
