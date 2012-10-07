/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2003      by Advanced Data Controls, Corp
 *  Copyright (C) 2004 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
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
 *  @(#) $Id: sys_config.c,v 1.1 2006/06/11 11:18:56 roi Exp $
 */

/*
 *    �������åȥ����ƥ��¸�⥸�塼���At91sam7s�ѡ�
 */

#include "jsp_kernel.h"
#include <at91sam7s.h>


/*interrupt mask*/
UW int_mode_table[MAX_INT_NUM]={
    0,
    0,
    0,
    0,
    0,
    0,
    SMR_US0,
    SMR_US1,
    0,
    0,
    0,
    0,
    SMR_TC0,
    SMR_TC1,
    SMR_TC2,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0
};

/*
 *  �������åȥ����ƥ��¸�ν����
 */
void
sys_initialize()
{
#if 0
    unsigned int  baud = ((MCK * 10) / (115200 * 16));
    unsigned long brgr;

    /*
     *  sys_putc ����ǽ�ˤʤ�褦��UART������
     */
    brgr = baud / 10;
    if((baud % 10) >= 5)
        brgr = (baud / 10) + 1;
    sil_wrw_mem((VP)(TADR_PIO_BASE+TOFF_PIO_PDR), (1<<9)|(1<<10));
    sil_wrw_mem((VP)(TADR_DBGU_BASE+TOFF_US_IDR), 0xFFFFFFFF);
    sil_wrw_mem((VP)(TADR_DBGU_BASE+TOFF_US_CR), US_RSTRX|US_RSTTX|US_RXDIS|US_TXDIS);
    sil_wrw_mem((VP)(TADR_DBGU_BASE+TOFF_US_BRGR), brgr);
    sil_wrw_mem((VP)(TADR_DBGU_BASE+TOFF_US_MR), 4<<9);
    sil_wrw_mem((VP)(TADR_DBGU_BASE+TOFF_US_CR), US_TXEN|US_RXEN);
#else /* patch */
#endif
}


/*
 *  �������åȥ����ƥ�ν�λ
 */
void
sys_exit(void)
{
    syslog(LOG_EMERG, "End Kernel.....!");
    while(1);
}


/*
 *  �������åȥ����ƥ��ʸ������
 */

void
sys_putc(char c)
{
#if 0
    if (c == '\n') {
        uart_putc('\r');
    }
    uart_putc(c);
#else /* patch */
#endif
}


/*
 *  ����ߥϥ�ɥ������
 *
 *  ������ֹ� inhno �γ���ߥϥ�ɥ�ε�ư���Ϥ� inthdr �����ꤹ�롥
 */
void
define_inh(INHNO inhno, FP inthdr)
{
    assert(inhno < MAX_INT_NUM);
#if 0
	sil_wrw_mem((VP)(TADR_AIC_BASE+TOFF_AIC_IDCR), 1<<inhno);
	sil_wrw_mem((VP)(TADR_AIC_BASE+TOFF_AIC_SVR+inhno*4), (UW)inthdr);
	sil_wrw_mem((VP)(TADR_AIC_BASE+TOFF_AIC_SMR+inhno*4), int_mode_table[inhno]);
	sil_wrw_mem((VP)(TADR_AIC_BASE+TOFF_AIC_ICCR), 1<<inhno);
	sil_wrw_mem((VP)(TADR_AIC_BASE+TOFF_AIC_IECR), 1<<inhno);
#else /* patch */
	int_table[inhno] = inthdr;
#endif
}

/*
 *  ̤����γ���ߤ����ä����ν���
 */
void
undef_interrupt(){
    syslog(LOG_EMERG, "Unregistered Interrupt occurs.");
    while(1);
}

#if 0
#else /* patch */
FP int_table[MAX_INT_NUM];
UW nontask_stack[NONTASK_STACK_SIZE / sizeof(UW)];
#endif
