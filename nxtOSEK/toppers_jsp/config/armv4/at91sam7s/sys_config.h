/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *                2003      by Advanced Data Controls, Corp
 *  Copyright (C) 2006 by GJ Business Division RICOH COMPANY,LTD. JAPAN
 *  Copyright (C) 2007-     by Monami Software Limited Partnership, JAPAN
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
 *  @(#) $Id: sys_config.h,v 1.2 2006/06/11 11:38:40 roi Exp $
 */


/*
 *  �������åȥ����ƥ��¸�⥸�塼���At91sam7s�ѡ�
 *
 *  ���Υ��󥯥롼�ɥե�����ϡ�t_config.h �Τߤ��饤�󥯥롼�ɤ���롥
 *  ¾�Υե����뤫��ľ�ܥ��󥯥롼�ɤ��ƤϤʤ�ʤ���
 */


#ifndef _SYS_CONFIG_H_
#define _SYS_CONFIG_H_

/*
 *  �����ͥ����������̾�Υ�͡���
 */
#include <sys_rename.h>

/*
 * ����ߥϥ�ɥ�κ����
 */
#define MAX_INT_NUM 32

/*
 *  vxget_tim �򥵥ݡ��Ȥ��뤫�ɤ��������
 */
#if 0
#define  SUPPORT_VXGET_TIM
#else /* patch */
#endif


/*
 *  ���ꥢ��ݡ����ֹ�˴ؤ������
 */
#define TNUM_PORT   2   /* ���ݡ��Ȥ��륷�ꥢ��ݡ��Ȥο� */
#define TNUM_SIOP   2   /* ���ݡ��Ȥ��륷�ꥢ��I/O�ݡ��Ȥο� */

/*
 *  ���ꥢ��ݡ����ֹ�˴ؤ������
 */
#define	CONSOLE_PORTID  1	/* ���󥽡�����Ѥ��륷�ꥢ��ݡ����ֹ�   */
#define LOGTASK_PORTID  1   /* �����ƥ�����Ѥ��륷�ꥢ��ݡ����ֹ� */

/*
 *  ������Ԥ����֤Ǥμ¹ԥ롼����
 */
#ifdef ARM920T_CORE
#define WAIT_INTERRUPT  mcr p15, 0, r3, c7, c0, 4
#else
#define WAIT_INTERRUPT  nop
#endif

/*
 *  �ץ��å��Υ���ǥ�����
 */
#define SIL_ENDIAN  SIL_ENDIAN_LITTLE  /* ��ȥ륨��ǥ����� */

#ifndef _MACRO_ONLY

/*
 *  �������åȥ����ƥ��¸�ν����
 */
extern void    sys_initialize(void);

/*
 *  �������åȥ����ƥ�ν�λ
 *
 *  �����ƥ��λ������˻Ȥ���ROM��˥��ƽФ��Ǽ¸����뤳�Ȥ����ꤷ
 *  �Ƥ��롥
 */
extern void    sys_exit(void);

/*
 *  �������åȥ����ƥ��ʸ������
 *
 *  �����ƥ�����٥��ʸ�����ϥ롼����ROM��˥��ƽФ��Ǽ¸����뤳
 *  �Ȥ����ꤷ�Ƥ��롥
 */
extern void    sys_putc(char c);


/*
 *  ������ѤΥơ��֥�
 */
extern FP   int_table[MAX_INT_NUM];


/*
 *  IRQ�ϥ�ɥ�(sys_support.S)
 */
extern void IRQ_Handler(void);
extern void FIQ_Handler(void);

/*
 *  ����ߥϥ�ɥ�ν����������������ޥ���
 *
 */
#define INTHDR_ENTRY(inthdr)  extern void inthdr(void)

#define INT_ENTRY(inthdr) inthdr

/*
 *  ����ߥϥ�ɥ������
 *
 *  ������ֹ� inhno �γ���ߥϥ�ɥ�ε�ư���Ϥ� inthdr �����ꤹ�롥
 */
extern void define_inh(INHNO inhno, FP inthdr);




#endif /* _MACRO_ONLY */
#if 0
#else /* patch */
#include "../../windows/api.h"
#define NONTASK_STACK_SIZE 1024
#endif
#endif /* _SYS_CONFIG_H_ */
