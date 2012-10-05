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
 *  @(#) $Id: armv4.h,v 1.2 2003/12/01 06:47:05 honda Exp $
 */

/*
 *    ARMv4�����
 */

#ifndef _ARMV4_H_
#define _ARMV4_H_

/*
 *  ARM Exception Vector
 */
#define SVC_Vector    0x00
#define UND_Vector    0x04
#define SWI_Vector    0x08
#define PRFA_Vector   0x0C
#define DATAA_Vector  0x10
#define IRQ_Vector    0x18
#define FIQ_Vector    0x1C


/*
 * ARM Exception Vector Number
 */
#define SVC_Number    0
#define UND_Number    1
#define SWI_Number    2
#define PRFA_Number   3
#define DATAA_Number  4
#define UNNOWN_Number 5
#define IRQ_Number    6
#define FIQ_Number    7

/*
 *  CPSR ����߶ػߥӥå�
 */
#define CPSR_INT_MASK 0xC0
#define CPSR_IRQ_BIT  0x80
#define CPSR_FIQ_BIT  0x40

/*
 *  CPSR �Υ⡼�ɥӥå�
 */
#define CPSR_MODE_MASK   0x1f
#define CPSR_USER        0x10
#define CPSR_FIQ         0x11
#define CPSR_IRQ         0x12
#define CPSR_SVC         0x13
#define CPSR_ABT         0x17
#define CPSR_SYS         0x1F


/*
 * Stub Call
 */
#ifndef _MACRO_ONLY
Inline void
stub_exit(void){
    Asm("swi 0xff");
}

Inline void
stub_putc(char c)
{
    Asm("mov r0,#0x0; mov r4,%0; swi 0x123456"
        :: "r"(c):"r0","r4");
}

Inline void
stub_write(const char *string)
{
    int pos = 0;
    
    while(string[pos] !=0)
        stub_putc(string[pos++]);
}

Inline void
stub_set_inh(INHNO inhno, FP inthdr)
{
    Asm("mov r0,#0x1; mov r4,%0; mov r5,%1; swi 0x123456"
        : /* no output */
        : "r"(inhno),"r"(inthdr)
        : "r0", "r4", "r5");
    
}

#endif /* _MACRO_ONLY */

#endif /* _ARMV4_H_ */
