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
 *  Copyright (C) 2006-2007 by GJ Business Division RICOH COMPANY,LTD. JAPAN
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
 *  @(#) $Id: at91sam7s.c,v 1.4 2007/05/12 19:32:22 roi Exp $
 *  
 */

/*
 * At91sam7s ������ǽ�ѥɥ饤��
 */
#include <s_services.h>
#include <at91sam7s.h>

#define BAUDRATE   115200

/*
 * ���ꥢ��I/O�ݡ��Ƚ�����֥�å�
 */
const SIOPINIB siopinib_table[TNUM_SIOP] = {
    {(VP)(TADR_DBGU_BASE),         (VP)(TADR_PIO_BASE+TOFF_PIO_PDR),
     (VP)0,
     (VW)((1<<9)|(1<<10)),         0
    }
#if TNUM_SIOP >= 2
    ,
    {(VP)(TADR_US_BASE+US_WINDOW), (VP)(TADR_PIO_BASE+TOFF_PIO_PDR),
     (VP)(TADR_PMC_BASE+TOFF_PMC_PCER),
     (VW)((1<<21)|(1<<22)),        1<<IRQ_US1_PID
    }

#endif /* TNUM_SIOP >= 2 */
};


/*
 *  ���ꥢ��I/O�ݡ��ȴ����֥�å��Υ��ꥢ
 */
SIOPCB  siopcb_table[TNUM_SIOP];


/*
 *  ���ꥢ��I/O�ݡ���ID��������֥�å�����Ф�����Υޥ���
 */
#define INDEX_SIOP(siopid)  ((UINT)((siopid) - 1))
#define get_siopcb(siopid)  (&(siopcb_table[INDEX_SIOP(siopid)]))


/*
 * ʸ�������������?
 */ 
Inline BOOL
uart_getready(SIOPCB *siopcb)
{
    return(((sil_rew_mem((VP)(siopcb->siopinib->uart_base+TOFF_US_CSR)) & US_RXRDY)!=0));
}

/*
 * ʸ���������Ǥ��뤫?
 */
Inline BOOL
uart_putready(SIOPCB *siopcb)
{
    return((sil_rew_mem((VP)(siopcb->siopinib->uart_base+TOFF_US_CSR)) & US_TXEMPTY)!=0);
}

/*
 *  ��������ʸ���μ��Ф�
 */
Inline UB
uart_getchar(SIOPCB *siopcb)
{
    return(sil_rew_mem((VP)(siopcb->siopinib->uart_base+TOFF_US_RHR)));
}

/*
 *  ��������ʸ���ν񤭹���
 */
Inline void
uart_putchar(SIOPCB *siopcb, UB c)
{
    sil_wrw_mem((VP)(siopcb->siopinib->uart_base+TOFF_US_THR),c);
}

/*
 *  ��������ߵ���
 */
Inline void
uart_enable_send(SIOPCB *siopcb)
{
    sil_wrw_mem((VP)(siopcb->siopinib->uart_base+TOFF_US_IER), 1<<1);
}

/*
 *  ��������߶ػ�
 */
Inline void
uart_disable_send(SIOPCB *siopcb)
{
    sil_wrw_mem((VP)(siopcb->siopinib->uart_base+TOFF_US_IDR), 1<<1);
}


/*
 *  ��������ߵ���
 */
Inline void
uart_enable_rcv(SIOPCB *siopcb)
{
    sil_wrw_mem((VP)(siopcb->siopinib->uart_base+TOFF_US_IER), 1<<0);
}

/*
 *  ��������߶ػ�
 */
Inline void
uart_disable_rcv(SIOPCB *siopcb)
{
    sil_wrw_mem((VP)(siopcb->siopinib->uart_base+TOFF_US_IDR), 1<<0);
}

/*
 *  SIO�ɥ饤�Фν�����롼����
 *  1�ݡ��Ȥ����ʤ����ᡤ���ޤ��̣�Ϥʤ�
 */
void
uart_initialize()
{
    SIOPCB  *siopcb;
    UINT    i;

    /*
     *  ���ꥢ��I/O�ݡ��ȴ����֥�å��ν����
     */
    for (siopcb = siopcb_table, i = 0; i < TNUM_SIOP; siopcb++, i++) {
        siopcb->siopinib = &(siopinib_table[i]);
        siopcb->openflag = FALSE;
        siopcb->sendflag = FALSE;
    }
}

/*
 * �����ץ󤷤Ƥ���ݡ��Ȥ����뤫
 */
BOOL
uart_openflag(void)
{
    return(siopcb_table[0].openflag);
}

/*
 * ���ꥢ��I/O�ݡ��ȤΥ����ץ�
 */
SIOPCB *
uart_opn_por(ID siopid, VP_INT exinf)
{
    unsigned int baud = ((MCK * 10) / (BAUDRATE * 16));

    SIOPCB      *siopcb;
    const SIOPINIB  *siopinib;

    siopcb = get_siopcb(siopid);
    siopinib = siopcb->siopinib;

    /*
     * Wait ������롥
     */
    sil_dly_nse(5000);

    if(siopinib->pmc_pcer)
        sil_wrw_mem((VP)siopinib->pmc_pcer, siopinib->irq_bit);
    /* Disable Interrupt */
    sil_wrw_mem((VP)(siopinib->uart_base+TOFF_US_IDR), 0xFFFFFFFF);
    sil_wrw_mem((VP)(siopinib->uart_base+TOFF_US_CR), (US_RSTRX|US_RSTTX|US_RXDIS|US_TXDIS));
    sil_wrw_mem((VP)(siopinib->uart_base+TOFF_PDC_RCR), 0);
    sil_wrw_mem((VP)(siopinib->uart_base+TOFF_PDC_TCR), 0);
    sil_wrw_mem((VP)siopinib->linectrl_pdr, siopinib->pdr_bit);
    /* 8Data, 1Stop, No Parity */
    sil_wrw_mem((VP)(siopinib->uart_base+TOFF_US_MR), (US_CLKS_MCK|US_CHRL_8|US_PAR_NO|US_NBSTOP_1|US_CHMODE_NORMAL));
    /* 115200bps */
    if((baud % 10) >= 5)
        sil_wrw_mem((VP)(siopinib->uart_base+TOFF_US_BRGR), (baud/10)+1);
    else
        sil_wrw_mem((VP)(siopinib->uart_base+TOFF_US_BRGR), (baud/10));

    /*
     * ����ߴ�Ϣ������
     */
    if(siopinib->pmc_pcer){
        sil_wrw_mem((VP)(siopinib->uart_base+TOFF_US_TTGR), 0);
        sil_wrw_mem((VP)(siopinib->uart_base+TOFF_US_CR), US_TXEN|US_RXEN);
        sil_wrw_mem((VP)(siopinib->uart_base+TOFF_US_IER), 1<<0);
    }
	else{
        /* ����å����͡��֥� */
        sil_wrw_mem((VP)(TADR_PMC_BASE+TOFF_PMC_PCER), (1<<IRQ_TC2_PID));
        /* ��������� */
        sil_wrw_mem((VP)(TADR_TC_BASE+TC_WINDOW*2+TOFF_TC_CCR), TC_CLKDIS);
        sil_wrw_mem((VP)(TADR_TC_BASE+TC_WINDOW*2+TOFF_TC_IDR), 0xFFFFFFFF);
        /* ��������ͤ򥻥å� */
        sil_wrw_mem((VP)(TADR_TC_BASE+TC_WINDOW*2+TOFF_TC_CMR), TC_CLKS_MCK8);	/* 47,923,200Hz/8=5,990,400Hz */
        sil_wrw_mem((VP)(TADR_TC_BASE+TC_WINDOW*2+TOFF_TC_CMR), sil_rew_mem((VP)(TADR_TC_BASE+TC_WINDOW*2+TOFF_TC_CMR)) | TC_WAVESEL10);
        sil_wrw_mem((VP)(TADR_TC_BASE+TC_WINDOW*2+TOFF_TC_RC), 59900);			/* 10ms */
        /* ����ߤΥ��ꥢ  */
        sil_wrw_mem((VP)(TADR_TC_BASE+TC_WINDOW*2+TOFF_TC_IER), TC_CPCS);
        /* ������ȥ�������   */
        sil_wrw_mem((VP)(TADR_TC_BASE+TC_WINDOW*2+TOFF_TC_CCR), (TC_CLKEN|TC_SWTRG));

        sil_wrw_mem((VP)(siopinib->uart_base+TOFF_US_CR), US_TXEN|US_RXEN);
    }
    sil_rew_mem((VP)(siopinib->uart_base+TOFF_US_RHR));

    siopcb->exinf = exinf;
    siopcb->getready = siopcb->putready = FALSE;
    siopcb->openflag = TRUE;

    return(siopcb);
}



/*
 *  ���ꥢ��I/O�ݡ��ȤΥ�����
 */
void
uart_cls_por(SIOPCB *siopcb)
{
    const SIOPINIB  *siopinib;

    siopinib = siopcb->siopinib;
	sil_wrw_mem((VP)(siopinib->uart_base+TOFF_US_CR), US_RSTRX|US_RSTTX|US_RXDIS|US_TXDIS);
    siopcb->openflag = FALSE;
}

/*
 *  ���ꥢ��I/O�ݡ��Ȥؤ�ʸ������
 */
BOOL
uart_snd_chr(SIOPCB *siopcb, char c)
{
    if(siopcb->siopinib->pmc_pcer == 0){
        while(!uart_putready(siopcb));
        uart_putchar(siopcb, c);
        return(TRUE);
    }
    else if (uart_putready(siopcb)){
        uart_putchar(siopcb, c);
        return(TRUE);
    }
    return(FALSE);
}

/*
 *  ���ꥢ��I/O�ݡ��Ȥ����ʸ������
 */
INT
uart_rcv_chr(SIOPCB *siopcb)
{
    if (uart_getready(siopcb)) {
        return((INT)(UB) uart_getchar(siopcb));
    }
    return(-1);
}

/*
 *  ���ꥢ��I/O�ݡ��Ȥ���Υ�����Хå��ε���
 */
void
uart_ena_cbr(SIOPCB *siopcb, UINT cbrtn)
{
    switch (cbrtn) {
        case SIO_ERDY_SND:
            uart_enable_send(siopcb);
            break;
        case SIO_ERDY_RCV:
            uart_enable_rcv(siopcb);
            break;
    }
}


/*
 *  ���ꥢ��I/O�ݡ��Ȥ���Υ�����Хå��ζػ�
 */
void
uart_dis_cbr(SIOPCB *siopcb, UINT cbrtn)
{
    switch (cbrtn) {
        case SIO_ERDY_SND:
            uart_disable_send(siopcb);
            break;
        case SIO_ERDY_RCV:
            uart_disable_rcv(siopcb);
            break;
    }
}



/*
 *  ���ꥢ��I/O�ݡ��Ȥ��Ф������߽���
 */
static void
uart_isr_siop(SIOPCB *siopcb)
{
    if (uart_getready(siopcb)) {
        /*
         *  �������Υ�����Хå��롼�����ƤӽФ���
         */
        uart_ierdy_rcv(siopcb->exinf);
    }
    if (uart_putready(siopcb)) {
        /*
         *  ������ǽ������Хå��롼�����ƤӽФ���
         */
        uart_ierdy_snd(siopcb->exinf);
    }
}


/*
 *  SIO�γ���ߥ����ӥ��롼����
 */
void
int_timer2()
{
    SIOPCB *siopcb = &(siopcb_table[0]);

    sil_rew_mem((VP)(TADR_TC_BASE+TC_WINDOW*2+TOFF_TC_SR));
    if (uart_getready(siopcb)) {
        /*
         *  �������Υ�����Хå��롼�����ƤӽФ���
         */
        uart_ierdy_rcv(siopcb->exinf);
    }
}

#if TNUM_SIOP >= 2
void
uart_isr1()
{
    uart_isr_siop(&(siopcb_table[1]));
}
#endif
