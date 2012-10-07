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
 *  @(#) $Id: st16c2550.c,v 1.4 2005/11/12 15:00:43 honda Exp $
 */

/*
 *     ST16C2550 �� �ʰ�SIO�ɥ饤��
 */
#include <s_services.h>
#include <st16c2550.h>
 
/*
 * �ƥ쥸�����Υ��ե��å�
 */
#define ST16C_RHR   0x00   /* H  LCR bit7=0 Read  */
#define ST16C_THR   0x00   /* H  LCR bit7=0 Write */
#define ST16C_DLL   0x00   /* H  LCR bit7=1       */
#define ST16C_IER   0x02   /* H  LCR bit7=0       */
#define ST16C_DLM   0x02   /* H  LCR bit7=1       */
#define ST16C_ISR   0x04   /* H  Read  */
#define ST16C_FCR   0x04   /* H  Write */
#define ST16C_LCR   0x06   /* H  */
#define ST16C_MCR   0x08   /* H  */
#define ST16C_LSR   0x0a   /* H  Read */
#define ST16C_MSR   0x0c   /* H  Read */
#define ST16C_SPR   0x0e   /* H  */

#define ISR_TX            0x02       /* ����������ȯ�� */
#define IER_TX            0x02       /* ���������ߵ��� */
#define ISR_RX            0x01       /* ����������ȯ�� */
#define IER_RX            0x01       /* ���������ߵ��� */

#define LCR_DL_MODE       0x80       /* Divisor Enable */
#define LCR_VAL           0x03       /* 8bit,1stop,Noparity,No break */
#define FCR_FIFO_DISABLE  0x00

#define LSR_RX_DATA_READY 0x01
#define LSR_TX_EMPTY      0x20

#define MCR_INT_ENABLE    0x08

/*
 *  115200bps������
 *  4 = (7372800Hz)/(115200*16)
 */
#define DLM_VAL  0x00
#define DLL_VAL  0x04




/*
 * ���ꥢ��I/O�ݡ��Ƚ�����֥�å�
 */
const SIOPINIB siopinib_table[TNUM_SIOP] = {
    {ST16C_CHB, LCR_VAL, DLM_VAL, DLL_VAL, PINTER_PINT7E},
#if TNUM_SIOP > 2
    {ST16C_CHA, LCR_VAL, DLM_VAL, DLL_VAL, PINTER_PINT6E},
#endif /* TNUM_SIOP > 2 */    
};

/*
 *  ���ꥢ��I/O�ݡ��Ƚ�����֥�å��μ�Ф�
 */
#define INDEX_SIOPINIB(siopid)  ((UINT)((siopid) - 1))
#define get_siopinib(siopid)  (&(siopinib_table[INDEX_SIOPINIB(siopid)]))


/*
 *  ���ꥢ��I/O�ݡ��ȴ����֥�å��Υ��ꥢ
 */
SIOPCB  siopcb_table[TNUM_SIOP];

/*
 *  ���ꥢ��I/O�ݡ���ID��������֥�å�����Ф�����Υޥ���
 */
#define INDEX_SIOP(siopid)  ((UINT)((siopid) - 1))
#define get_siopcb(siopid)  (&(siopcb_table[INDEX_SIOP(siopid)]))

Inline void
st16c_write(UW addr, UW offset, UB val)
{
    sil_wrh_mem((VP)(addr + offset),val);
}

Inline UB
st16c_read(UW addr, UW offset)
{
    return(sil_reh_mem((VP)(addr + offset)));
}


/*
 * ʸ�������������?
 */ 
Inline BOOL
st16c_getready(SIOPCB *siopcb)
{
    UH status;

    status = st16c_read(siopcb->siopinib->reg_base, ST16C_LSR);
    
    return((status & LSR_RX_DATA_READY));
}

/*
 * ʸ���������Ǥ��뤫?
 */
Inline BOOL
st16c_putready(SIOPCB *siopcb)
{
    UH status;

    status = st16c_read(siopcb->siopinib->reg_base, ST16C_LSR);
    
    return (status & LSR_TX_EMPTY);
}

/*
 *  ��������ʸ���μ��Ф�
 */
Inline UB
st16c_getchar(SIOPCB *siopcb)
{
    return(st16c_read(siopcb->siopinib->reg_base,ST16C_RHR));
}

/*
 *  ��������ʸ���ν񤭹���
 */
Inline void
st16c_putchar(SIOPCB *siopcb, UB c)
{
    st16c_write(siopcb->siopinib->reg_base, ST16C_THR, c);
}

/*
 *  ��������ߵ���
 */
Inline void
st16c_enable_send(SIOPCB *siopcb)
{
    st16c_write(siopcb->siopinib->reg_base, ST16C_IER,
                (st16c_read(siopcb->siopinib->reg_base,ST16C_IER) | IER_TX));
}

/*
 *  ��������߶ػ�
 */
Inline void
st16c_disable_send(SIOPCB *siopcb)
{
    st16c_write(siopcb->siopinib->reg_base, ST16C_IER,
                (st16c_read(siopcb->siopinib->reg_base, ST16C_IER) & ~IER_TX));
                
}

/*
 *  ��������ߵ���
 */
Inline void
st16c_enable_rcv(SIOPCB *siopcb)
{
    st16c_write(siopcb->siopinib->reg_base, ST16C_IER,
                (st16c_read(siopcb->siopinib->reg_base,ST16C_IER) | IER_RX));
}

/*
 *  ��������߶ػ�
 */
Inline void
st16c_disable_rcv(SIOPCB *siopcb)
{
    st16c_write(siopcb->siopinib->reg_base, ST16C_IER,
                (st16c_read(siopcb->siopinib->reg_base, ST16C_IER) & ~IER_RX));
                
}


/*
 *  SIO�ɥ饤�Фν�����롼����
 */
void
st16c2550_initialize()
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
 *
 */
void
st16c2550_init_siopinib(const SIOPINIB *siopinib)
{
    /*
     *  ʬ���������
     */
    /* Divisor Enable */
    st16c_write(siopinib->reg_base, ST16C_LCR,
                (st16c_read(siopinib->reg_base, ST16C_LCR) | LCR_DL_MODE));
    st16c_write(siopinib->reg_base, ST16C_DLL, siopinib->dll_val);
    st16c_write(siopinib->reg_base, ST16C_DLM, siopinib->dlm_val);
    /* Divisor Disable */
    st16c_write(siopinib->reg_base, ST16C_LCR,
                (st16c_read(siopinib->reg_base, ST16C_LCR) & ~LCR_DL_MODE));

    /* �⡼������ */
    st16c_write(siopinib->reg_base, ST16C_LCR, siopinib->lcr_val);

    /* FIFO Disable */
    st16c_write(siopinib->reg_base, ST16C_FCR, FCR_FIFO_DISABLE);

    /* ����߶ػ� */
    st16c_write(siopinib->reg_base, ST16C_IER, 0x00);
}


/*
 *  �����ͥ뵯ư���ΥС��ʡ������Ѥν����
 */
void
st16c2550_init(void)
{
    
    st16c2550_init_siopinib(get_siopinib(1));
#if TNUM_SIOP > 2
    st16c2550_init_siopinib(get_siopinib(2));    
#endif /* TNUM_SIOP > 2 */        
    
}

/*
 * �����ץ󤷤Ƥ���ݡ��Ȥ����뤫
 */
BOOL
st16c2550_openflag(void)
{
#if TNUM_SIOP < 2
    return(siopcb_table[0].openflag);
#else /* TNUM_SIOP < 2 */
    return(siopcb_table[0].openflag || siopcb_table[1].openflag);
#endif /* TNUM_SIOP < 2 */
}


/*
 * ���ꥢ��I/O�ݡ��ȤΥ����ץ�
 */
SIOPCB *
st16c2550_opn_por(ID siopid, VP_INT exinf)
{
    SIOPCB      *siopcb;
    const SIOPINIB  *siopinib;

    siopcb = get_siopcb(siopid);
    siopinib = siopcb->siopinib;
    
    /*
     * �����
     */
    st16c2550_init_siopinib(siopcb->siopinib);
    
    /* ��������ߵ��� */
    st16c_write(siopcb->siopinib->reg_base, ST16C_IER, IER_RX);
    
    /* ��������򥤥͡��֥� */
    st16c_write(siopcb->siopinib->reg_base, ST16C_MCR, MCR_INT_ENABLE);

    siopcb->exinf = exinf;
    siopcb->getready = siopcb->putready = FALSE;
    siopcb->openflag = TRUE;

    return(siopcb);
}

/*
 *  ���ꥢ��I/O�ݡ��ȤΥ�����
 */
void
st16c2550_cls_por(SIOPCB *siopcb)
{
    /* ����߶ػ� */
    st16c_write(siopcb->siopinib->reg_base, ST16C_IER, 0x00);   
    siopcb->openflag = FALSE;
}


/*
 *  ���ꥢ��I/O�ݡ��ȤؤΥݡ���󥰤Ǥν���
 */
void
st16c2550_pol_putc(char c, ID siopid)
{
    const SIOPINIB *siopinib;
    
    siopinib = get_siopinib(siopid);
    
    while((st16c_read(siopinib->reg_base, ST16C_LSR) & LSR_TX_EMPTY)
          != LSR_TX_EMPTY)
        ;
    st16c_write(siopinib->reg_base, ST16C_THR, c);
}


/*
 *  ���ꥢ��I/O�ݡ��Ȥؤ�ʸ������
 */
BOOL
st16c2550_snd_chr(SIOPCB *siopcb, char c)
{
    if (st16c_putready(siopcb)){
        st16c_putchar(siopcb, c);
        return(TRUE);
    }
    return(FALSE);
}

/*
 *  ���ꥢ��I/O�ݡ��Ȥ����ʸ������
 */
INT
st16c2550_rcv_chr(SIOPCB *siopcb)
{
    if (st16c_getready(siopcb)) {
        return((INT)(UB) st16c_getchar(siopcb));
    }
    return(-1);
}





/*
 *  ���ꥢ��I/O�ݡ��Ȥ���Υ�����Хå��ε���
 */
void
st16c2550_ena_cbr(SIOPCB *siopcb, UINT cbrtn)
{

    switch (cbrtn) {
        case SIO_ERDY_SND:
            st16c_enable_send(siopcb);
            break;
        case SIO_ERDY_RCV:
            st16c_enable_rcv(siopcb);
            break;
    }
}

/*
 *  ���ꥢ��I/O�ݡ��Ȥ���Υ�����Хå��ζػ�
 */
void
st16c2550_dis_cbr(SIOPCB *siopcb, UINT cbrtn)
{
    switch (cbrtn) {
        case SIO_ERDY_SND:
            st16c_disable_send(siopcb);
            break;
        case SIO_ERDY_RCV:
            st16c_disable_rcv(siopcb);
            break;
    }
}

/*
 *  ���ꥢ��I/O�ݡ��Ȥ��Ф������߽���
 */
static void
st16c2550_isr_siop(SIOPCB *siopcb)
{
    if (st16c_getready(siopcb)) {
        /*
         *  �������Υ�����Хå��롼�����ƤӽФ���
         */
        st16c2550_ierdy_rcv(siopcb->exinf);
    }
    if (st16c_putready(siopcb)) {
        /*
         *  ������ǽ������Хå��롼�����ƤӽФ���
         */
        st16c2550_ierdy_snd(siopcb->exinf);
    }
}

/*
 *  SIO�γ���ߥ����ӥ��롼����
 */
void
st16c2550_isr()
{
    st16c2550_isr_siop(&(siopcb_table[0]));
}
