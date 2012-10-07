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
 *  @(#) $Id: fdc37c935a.c,v 1.3 2005/11/12 15:00:43 honda Exp $
 */

/*
 * ������I/O FDC37C935A �ѥɥ饤��
 */

#include <s_services.h>
#include <fdc37c935a.h>

/*
 *  �����
 */
void
smsc_init(void)
{
    /*
     * Enter Config mode 
     */
    sil_wrh_mem((VP)SMSC_CONFIG_PORT, (0x55 << 8));
    sil_wrh_mem((VP)SMSC_CONFIG_PORT, (0x55 << 8));

    /*
     * Init SCI0
     */
    /* Power on */
    smsc_config_write(0x22, (smsc_config_read(0x22) | 0x10));
    /* Select SCI0 */
    smsc_config_write(0x07, 0x04);
    /* Enable SCI0 */
    smsc_config_write(0x30, 0x01);
    /* Set SCI0 Base Address */
    smsc_config_write(0x60, (SMSC_SCI0_BASE_ADDR & 0xff00) >> 8);
    smsc_config_write(0x61, (SMSC_SCI0_BASE_ADDR & 0xff));    
    /* IRQ4 */
    smsc_config_write(0x70, 0x04);
    

    /*
     *  Exit Config mode
     */
    sil_wrh_mem((VP)SMSC_CONFIG_PORT, (0xAA << 8));
}


/*
 *  �����ѡ�I/O(FDC37C935A)�� �ʰ�SIO�ɥ饤��
 */

/*
 *  ���ꥢ��I/O�ݡ��Ƚ�����֥�å�
 */
typedef struct sio_port_initialization_block {

} SIOPINIB;

/*
 *  ���ꥢ��I/O�ݡ��ȴ����֥�å�
 */
struct sio_port_control_block {
    const SIOPINIB  *siopinib;  /* ���ꥢ��I/O�ݡ��Ƚ�����֥�å� */
    VP_INT          exinf;      /* ��ĥ���� */
    BOOL    openflag;           /* �����ץ�Ѥߥե饰 */
    BOOL    sendflag;           /* ��������ߥ��͡��֥�ե饰 */
    BOOL    getready;           /* ʸ��������������� */
    BOOL    putready;           /* ʸ���������Ǥ������ */
};

/*
 * ���ꥢ��I/O�ݡ��Ƚ�����֥�å�
 */
const SIOPINIB siopinib_table[TNUM_SIOP] = {{}};

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
smsc_sci0_getready(SIOPCB *siopcb)
{
    return(((sil_reh_mem((VP)SMSC_SCI0_LSR) >> 8) & 0x01) != 0);
}

/*
 * ʸ���������Ǥ��뤫?
 */
Inline BOOL
smsc_sci0_putready(SIOPCB *siopcb)
{
	return(((sil_reh_mem((VP)SMSC_SCI0_LSR) >> 8) & 0x60) != 0);
}

/*
 *  ��������ʸ���μ��Ф�
 */
Inline char
smsc_sci0_getchar(SIOPCB *siopcb)
{
    return (sil_reh_mem((VP)SMSC_SCI0_RBR) >> 8);
}

/*
 *  ��������ʸ���ν񤭹���
 */
Inline void
smsc_sci0_putchar(SIOPCB *siopcb, char c)
{
    sil_wrh_mem((VP)SMSC_SCI0_THR, c << 8);
}

/*
 *  ��������ߵ���
 */
Inline void
smsc_sci0_enable_send(SIOPCB *siopcb)
{

    sil_wrh_mem((VP)SMSC_SCI0_IER,
                (((sil_reh_mem((VP)SMSC_SCI0_IER) >> 8) | 0x02) << 8));   
}

/*
 *  ��������߶ػ�
 */
Inline void
smsc_sci0_disable_send(SIOPCB *siopcb)
{
    sil_wrh_mem((VP)SMSC_SCI0_IER,
                (((sil_reh_mem((VP)SMSC_SCI0_IER) >> 8) & ~0x02) << 8));   
}

/*
 *  ��������ߵ���
 */
Inline void
smsc_sci0_enable_rcv(SIOPCB *siopcb)
{

    sil_wrh_mem((VP)SMSC_SCI0_IER,
                (((sil_reh_mem((VP)SMSC_SCI0_IER) >> 8) | 0x01) << 8));   
}

/*
 *  ��������߶ػ�
 */
Inline void
smsc_sci0_disable_rcv(SIOPCB *siopcb)
{
    sil_wrh_mem((VP)SMSC_SCI0_IER,
                (((sil_reh_mem((VP)SMSC_SCI0_IER) >> 8) & ~0x01) << 8));   
}





/*
 *  SIO�ɥ饤�Фν�����롼����
 *  1�ݡ��Ȥ����ʤ����ᡤ���ޤ��̣�Ϥʤ�
 */
void
smsc_sci0_initialize()
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
 *  ����߰ʳ��ν����
 */
void
fdc37c935a_init(void)
{
    volatile UH dummy;
    
    /* BIT7 = 1 */
    sil_wrh_mem((VP)SMSC_SCI0_LCR, 0x83 << 8);

    /* Set BPS */
    sil_wrh_mem((VP)SMSC_SCI0_DLL, ((SMSC_SCI0_BPS & 0x00ff) << 8));   
    sil_wrh_mem((VP)SMSC_SCI0_DLM, ((SMSC_SCI0_BPS >> 8) << 8));

    /* BIT7 = 0 Divisor Latch BIT6 = 0 No Break : BIT3 = 0 NoParity
       : BIT2 = 0 1Stopbit : BIT1,0 = {1.1} 8bitData */    
    sil_wrh_mem((VP)SMSC_SCI0_LCR, 0x03 << 8);

    /* Do not use FIFO */
    sil_wrh_mem((VP)SMSC_SCI0_FCR, 0x0000);

    /* Clear Status */
    dummy = sil_reh_mem((VP)SMSC_SCI0_RBR);
    dummy = sil_reh_mem((VP)SMSC_SCI0_LSR);    
}

/*
 * �����ץ󤷤Ƥ���ݡ��Ȥ����뤫
 */
BOOL
smsc_sci0_openflag(void)
{
    return(siopcb_table[0].openflag);
}

/*
 * ���ꥢ��I/O�ݡ��ȤΥ����ץ�
 */
SIOPCB *
smsc_sci0_opn_por(ID siopid, VP_INT exinf)
{
    SIOPCB      *siopcb;
    const SIOPINIB  *siopinib;


    siopcb = get_siopcb(siopid);
    siopinib = siopcb->siopinib;

    fdc37c935a_init();
        
    /* Enable Receive Data Interrupt */
    sil_wrh_mem((VP)SMSC_SCI0_IER, (0x01 << 8));
    sil_wrh_mem((VP)SMSC_SCI0_MCR, 0x08 << 8);

    /*
     * MS7729RSE01�Ǥϡ�������������ߤ�ȯ�������Ƥ����ʤ��ȳ����
     * ��٥�16�γ���ߤ�ȯ�����Ƥ��ޤ�������ư��ʤ���
     */
    /* �����������׵����� */
    sil_wrh_mem((VP)SMSC_SCI0_IER,
                (((sil_reh_mem((VP)SMSC_SCI0_IER) >> 8) | 0x02) << 8));   
    /* �����������׵��ػ� */        
    sil_wrh_mem((VP)SMSC_SCI0_IER,
                (((sil_reh_mem((VP)SMSC_SCI0_IER) >> 8) & ~0x02) << 8));   

    siopcb->exinf = exinf;
    siopcb->getready = siopcb->putready = FALSE;
    siopcb->openflag = TRUE;

    return(siopcb);
}

/*
 *  ���ꥢ��I/O�ݡ��ȤΥ�����
 */
void
smsc_sci0_cls_por(SIOPCB *siopcb)
{
    sil_wrh_mem((VP)SMSC_SCI0_IER, 0x00);      /* ����ߤζػ� */
    siopcb->openflag = FALSE;
}

/*
 * ���ꥢ��I/O�ݡ��ȤؤΥݡ���󥰤Ǥν���
 */
void
fdc37c935a_pol_putc(char c)
{
    while(((sil_reh_mem((VP)SMSC_SCI0_LSR) >> 8) & 0x60) == 0)
        ;

    sil_wrh_mem((VP)SMSC_SCI0_THR, c << 8);
}

/*
 *  ���ꥢ��I/O�ݡ��Ȥؤ�ʸ������
 */
BOOL
smsc_sci0_snd_chr(SIOPCB *siopcb, char c)
{
    if (smsc_sci0_putready(siopcb)){
        smsc_sci0_putchar(siopcb, c);
        return(TRUE);
    }
    return(FALSE);
}

/*
 *  ���ꥢ��I/O�ݡ��Ȥ����ʸ������
 */
INT
smsc_sci0_rcv_chr(SIOPCB *siopcb)
{
    if (smsc_sci0_getready(siopcb)) {
        return((INT)(UB) smsc_sci0_getchar(siopcb));
    }
    return(-1);
}


/*
 *  ���ꥢ��I/O�ݡ��Ȥ���Υ�����Хå��ε���
 */
void
smsc_sci0_ena_cbr(SIOPCB *siopcb, UINT cbrtn)
{

    switch (cbrtn) {
        case SIO_ERDY_SND:
            smsc_sci0_enable_send(siopcb);
            break;
        case SIO_ERDY_RCV:
            smsc_sci0_enable_rcv(siopcb);
            break;
    }
}

/*
 *  ���ꥢ��I/O�ݡ��Ȥ���Υ�����Хå��ζػ�
 */
void
smsc_sci0_dis_cbr(SIOPCB *siopcb, UINT cbrtn)
{
    switch (cbrtn) {
        case SIO_ERDY_SND:
            smsc_sci0_disable_send(siopcb);
            break;
        case SIO_ERDY_RCV:
            smsc_sci0_disable_rcv(siopcb);
            break;
    }
}

/*
 *  ���ꥢ��I/O�ݡ��Ȥ��Ф������߽���
 */
static void
smsc_sci0_isr_siop(SIOPCB *siopcb)
{
    if (smsc_sci0_getready(siopcb)) {
        /*
         *  �������Υ�����Хå��롼�����ƤӽФ���
         */
        smsc_sci0_ierdy_rcv(siopcb->exinf);
    }
    if (smsc_sci0_putready(siopcb)) {
        /*
         *  ������ǽ������Хå��롼�����ƤӽФ���
         */
        smsc_sci0_ierdy_snd(siopcb->exinf);
    }
}

/*
 *  SIO�γ���ߥ����ӥ��롼����
 */
void
smsc_sci0_isr()
{
    smsc_sci0_isr_siop(&(siopcb_table[0]));
}
