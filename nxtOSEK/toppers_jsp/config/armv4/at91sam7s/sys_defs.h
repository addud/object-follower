/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *                2003      by Advanced Data Controls, Corp
 *  Copyright (C) 2005 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
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
 *  @(#) $Id: sys_defs.h,v 1.2 2006/06/18 08:06:36 roi Exp $
 */


/*
 *  �������åȥ����ƥ�˰�¸���������At91sam7s�ѡ�
 *
 *  ���Υ��󥯥롼�ɥե�����ϡ�kernel.h �� sil.h �ǥ��󥯥롼�ɤ���롥
 *  ¾�Υե����뤫��ľ�ܥ��󥯥롼�ɤ��뤳�ȤϤʤ������Υե�����򥤥�
 *  ���롼�ɤ������ˡ�t_stddef.h �� itron.h �����󥯥롼�ɤ����Τǡ�
 *  �����˰�¸���Ƥ�褤��
 */

#ifndef _SYS_DEFS_H_
#define _SYS_DEFS_H_

/*
 *  ��ư��å������Υ������åȥ����ƥ�̾
 */
#define TARGET_NAME "ARM - AT91SAM7S"
#define AT91SAM7S

/* �����ͥ뵯ư���Υ�å�����   */
#define COPYRIGHT_SYS \
"Copyright (C) 2006 by GJ Business Division RICOH COMPANY,LTD. JAPAN\n"

#define RAM_START       0x00200000
#ifndef RAM_SIZE
#define RAM_SIZE        (32*1024)
#endif

#define FIQ_DATA_SIZE   256
#define STACKTOP        (RAM_START+RAM_SIZE-FIQ_DATA_SIZE)  /* �󥿥�������ƥ������ѤΥ����å��ν���� */

/*
 *  �������ͤ�����ɽ���ȥߥ���ñ�̤Ȥ��Ѵ�
 */
#define TIMER_CLOCK     5990

/*
 *  VECTOR MODE
 */
#define VECTOR_IN_ROM

/*
 *  �������åȥ����ƥ��¸�Υ����ӥ�������
 */
#ifndef _MACRO_ONLY


/*
 *  INTNO���ȳ���ߤζػ�/����
 */
typedef    UINT        INTNO;        /* ������ֹ� */
typedef    UINT        INHNO;        /* ����ߥϥ�ɥ��ֹ� */


typedef    UD  SYSUTIM;    /* ��ǽɾ���ѥ����ƥ���� */
extern ER   vxget_tim(SYSUTIM *pk_sysutim) throw();

#endif /* _MACRO_ONLY */


/*
 *  ������ƥ��å������
 */
#define    TIC_NUME    1        /* ������ƥ��å��μ�����ʬ�� */
#define    TIC_DENO    1        /* ������ƥ��å��μ�����ʬ�� */

/*
 *  ���������Ԥ��Τ�������
 */
#define    SIL_DLY_TIM1     20
#define    SIL_DLY_TIM2     10

/*
 *  �ץ��å��Υ���ǥ�����
 */
#define    SIL_ENDIAN    SIL_ENDIAN_LITTLE    /* ��ȥ륨��ǥ����� */

#ifndef _MACRO_ONLY
/*
 * �����ƥ�����ǽ���
 */

Inline void
kernel_abort()
{
   while(1);
}

#endif /* _MACRO_ONLY */

#endif /* _SYS_DEFS_H_ */
