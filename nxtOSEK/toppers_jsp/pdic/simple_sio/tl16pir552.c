/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2000-2003 by Industrial Technology Institute,
 *                              Miyagi Prefectural Government, JAPAN
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
 */

#include <tl16pir552.h>

/*
 *	TL16PIR552(TI)�� �ʰ�SIO�ɥ饤��
 */

/*
 *  ���ꥢ��I/O�ݡ��Ƚ�����֥�å������
 */
typedef struct sio_port_initialization_block {
	VP	channel_addr;	/* ���ꥢ��ݡ��Ȥγ������� */

	UB	lcr_def;	/* LCR������ b0-b6;
				(�������ӥåȿ������ȥåץӥåȡ��ѥ�ƥ�) */
	UB	scr_def;	/* SCR�����͡ʥץꥹ�����顨��*/
	UB	boud_hi_def;	/* DLM�����͡ʥܡ��졼�Ⱦ�̤������͡� */
	UB	boud_lo_def;	/* DLL�����͡ʥܡ��졼�Ȳ��̤������͡� */
} SIOPINIB;

/*
 *  ���ꥢ��I/O�ݡ��ȴ����֥�å������
 */
struct sio_port_control_block {
	const SIOPINIB	*siopinib;	/* ���ꥢ��I/O�ݡ��Ƚ�����֥�å� */
	VP_INT		exinf;		/* ��ĥ���� */
	BOOL		openflag;	/* �����ץ�Ѥߥե饰 */
	BOOL		getready;	/* ʸ��������������� */
	BOOL		putready;	/* ʸ���������Ǥ������ */
};

/*
 *  ���ꥢ��I/O�ݡ��Ƚ�����֥�å�
 *    ID = 1 ��ݡ���1��ID = 2 ��ݡ���2���б������Ƥ��롥
 */
const SIOPINIB siopinib_table[TNUM_SIOP] = {
	{ (VP)  UART_CH01,
	  (UB)	WORD_LENGTH_8 | STOP_BITS_1 | PARITY_NON,
	  (UB)	PRE_DIVISOR,
	  (UB)	HI8(DIVISOR),
	  (UB)	LO8(DIVISOR) },
#if TNUM_SIOP >= 2
	{ (VP)  UART_CH02,
	  (UB)	WORD_LENGTH_8 | STOP_BITS_1 | PARITY_NON,
	  (UB)	PRE_DIVISOR,
	  (UB)	HI8(DIVISOR),
	  (UB)	LO8(DIVISOR) },
#endif /* TNUM_SIOP >= 2 */
};

/*
 *  ���ꥢ��I/O�ݡ��Ƚ�����֥�å��μ�Ф�
 */
#define INDEX_SIOPINIB(siopid)	((UINT)((siopid) - 1))
#define get_siopinib(siopid)	(&(siopinib_table[INDEX_SIOPINIB(siopid)]))


/*
 *  ���ꥢ��I/O�ݡ��ȴ����֥�å��Υ��ꥢ
 */
SIOPCB	siopcb_table[TNUM_SIOP];

/*
 *  ���ꥢ��I/O�ݡ���ID��������֥�å�����Ф�����Υޥ���
 */
#define INDEX_SIOP(siopid)	((UINT)((siopid) - 1))
#define get_siopcb(siopid)	(&(siopcb_table[INDEX_SIOP(siopid)]))

/*
 *  SIO�ѥ쥸�������ؿ�
 */
Inline void
tl16pir552_orb( VP addr, UW reg, UB val )
{
	tl16pir552_wrb( addr, reg, tl16pir552_reb( addr, reg ) | val );
}

Inline void
tl16pir552_andb( VP addr, UW reg, UB val )
{
	tl16pir552_wrb( addr, reg, tl16pir552_reb( addr, reg ) & val );
}


/*
 *  ���֤��ɽФ���IIR���ɽФ���
 */
static void
tl16pir552_get_stat(SIOPCB *siopcb)
{
	UB	iir;

	iir = tl16pir552_reb( siopcb->siopinib->channel_addr, IIR) & INT_MASK;

	switch( iir ) {
		case INT_TRANS_EMPTY :
			siopcb->putready = TRUE;
			break;
		case INT_RECEIVE_DATA :
		case INT_CHAR_TIME_OUT :
			siopcb->getready = TRUE;
			break;
		default :
			break;
	}

}

/*
 *  ʸ��������Ǥ��뤫��
 */
Inline BOOL
tl16pir552_getready(SIOPCB *siopcb)
{
	return(siopcb->getready);
}

/*
 *  ʸ���������Ǥ��뤫��
 */
Inline BOOL
tl16pir552_putready(SIOPCB *siopcb)
{
	return(siopcb->putready);
}

/*
 *  ��������ʸ���μ�Ф�
 */
Inline char
tl16pir552_getchar(SIOPCB *siopcb)
{
	siopcb->getready = FALSE;
	return((char) tl16pir552_reb( siopcb->siopinib->channel_addr, RBR ));
	/* 1byte ñ�̤Ǥ�ʸ���μ��Ф���Ԥä����뤿�ᡢtl16pir552_opn_por���
	   �����Хåե���������䤷���Ȥ��Ƥ���ǽ�θ���ϸ����ʤ���
	   ��ǽ�θ���ˤϡ��Хåե����ΤΥ֥�å�ž����Ԥ��ʤɤν�����ɬ�ס�*/
}

/*
 *  ��������ʸ���ν����
 */
Inline void
tl16pir552_putchar(SIOPCB *siopcb, char c)
{
	siopcb->putready = FALSE;
	tl16pir552_wrb( siopcb->siopinib->channel_addr, THR, c );
}

/*
 *  SIO�ɥ饤�Фν�����롼����
 */
void
tl16pir552_initialize()
{
	SIOPCB	*siopcb;
	UINT	i;

	/*
	 *  ���ꥢ��I/O�ݡ��ȴ����֥�å��ν����
	 */
	for (siopcb = siopcb_table, i = 0; i < TNUM_SIOP; siopcb++, i++) {
		siopcb->siopinib = &(siopinib_table[i]);
		siopcb->openflag = FALSE;
	}
}

/*
 *  SIO�쥸����������롼����
 */
void
tl16pir552_init_siopinib( const SIOPINIB  *siopinib )
{
	/*
	 * SIO�쥸�����ν����
	 */
	/* ������� */
	tl16pir552_wrb( siopinib->channel_addr, IER, DIS_INT );

	tl16pir552_wrb( siopinib->channel_addr, MCR, ENABLE_EXT_INT );

	/* �ܡ��졼�Ȥ����� */
	tl16pir552_wrb( siopinib->channel_addr, LCR, siopinib->lcr_def | DIVISOR_LATCH_ACC );

	tl16pir552_wrb( siopinib->channel_addr, SCR, siopinib->scr_def );

	tl16pir552_wrb( siopinib->channel_addr, DLL, siopinib->boud_lo_def );
	tl16pir552_wrb( siopinib->channel_addr, DLM, siopinib->boud_hi_def );

	/* �⡼�ɤ����� */
	tl16pir552_wrb( siopinib->channel_addr, LCR, siopinib->lcr_def );

	/* FIFO������ */
	tl16pir552_wrb( siopinib->channel_addr, FCR, FIFO_ENABLE );
	tl16pir552_wrb( siopinib->channel_addr, FCR, FIFO_ENABLE | RECEIVE_FIFO_RESET | TRANS_FIFO_RESET | RECEIVE_TRIG_1_BYTE );
	tl16pir552_wrb( siopinib->channel_addr, FCR, FIFO_ENABLE | RECEIVE_TRIG_1_BYTE );

	/* ��λ���� */
	tl16pir552_wrb( siopinib->channel_addr, MCR, DTR | RTS | ENABLE_EXT_INT );

	tl16pir552_wrb( siopinib->channel_addr, IER, RECEIVE_DATA_AVAILABLE);
}

/*
 *  �����ͥ뵯ư���ΥС��ʡ������Ѥν����
 */
void
tl16pir552_init(void)
{
	tl16pir552_init_siopinib( get_siopinib(1) );
#if TNUM_SIOP >= 2
	tl16pir552_init_siopinib( get_siopinib(2) );
#endif /* TNUM_SIOP >= 2 */
}

/*
 *  �����ץ󤷤Ƥ���ݡ��Ȥ����뤫��
 */
BOOL
tl16pir552_openflag(void)
{
#if TNUM_SIOP < 2
	return(siopcb_table[0].openflag);
#else /* TNUM_SIOP < 2 */
	return(siopcb_table[0].openflag || siopcb_table[1].openflag);
#endif /* TNUM_SIOP < 2 */
}

/*
 *  ���ꥢ��I/O�ݡ��ȤΥ����ץ�
 */
SIOPCB *
tl16pir552_opn_por(ID siopid, VP_INT exinf)
{
	SIOPCB		*siopcb = get_siopcb(siopid);
	const SIOPINIB	*siopinib = siopcb->siopinib;

	/* ���ꥢ�륳��ȥ���ν���� */
	tl16pir552_init_siopinib( siopinib );

	/* ����ߥ�٥����ꡢ������׵᥯�ꥢ�ϡ�sio_opn_por(hw_serial.h)�ǹԤ��� */

	siopcb->exinf = exinf;
	siopcb->getready = siopcb->putready = FALSE;
	siopcb->openflag = TRUE;

	return(siopcb);
}

/*
 *  ���ꥢ��I/O�ݡ��ȤΥ�����
 */
void
tl16pir552_cls_por(SIOPCB *siopcb)
{
	tl16pir552_wrb( siopcb->siopinib->channel_addr, IER, DIS_INT );

	siopcb->openflag = FALSE;
}

/*
 *  ���ꥢ��I/O�ݡ��Ȥؤ�ʸ������
 */
BOOL
tl16pir552_snd_chr(SIOPCB *siopcb, char c)
{
	if (tl16pir552_putready(siopcb)) {
		tl16pir552_putchar(siopcb, c);
		return(TRUE);
	}
	return(FALSE);
}

/*
 *  ���ꥢ��I/O�ݡ��Ȥ����ʸ������
 */
INT
tl16pir552_rcv_chr(SIOPCB *siopcb)
{
	if (tl16pir552_getready(siopcb)) {
		return((INT)(UB) tl16pir552_getchar(siopcb));
	}
	return(-1);
}

/*
 *  ���ꥢ��I/O�ݡ��Ȥ���Υ�����Хå��ε���
 */
void
tl16pir552_ena_cbr(SIOPCB *siopcb, UINT cbrtn)
{
	UB	ier_bit = 0;

	switch (cbrtn) {
	case SIO_ERDY_SND:
		ier_bit = TRANS_REG_EMPTY;
		break;
	case SIO_ERDY_RCV:
		ier_bit = (RECEIVE_DATA_AVAILABLE | RECEIVE_LINE_STATUS);
		break;
	}

	tl16pir552_orb( siopcb->siopinib->channel_addr, IER, ier_bit );
}

/*
 *  ���ꥢ��I/O�ݡ��Ȥ���Υ�����Хå��ζػ�
 */
void
tl16pir552_dis_cbr(SIOPCB *siopcb, UINT cbrtn)
{
	UB	ier_bit = 0;

	switch (cbrtn) {
	case SIO_ERDY_SND:
		ier_bit = TRANS_REG_EMPTY;
		break;
	case SIO_ERDY_RCV:
		ier_bit = (RECEIVE_DATA_AVAILABLE | RECEIVE_LINE_STATUS);
		break;
	}

	tl16pir552_andb( siopcb->siopinib->channel_addr, IER, ~ier_bit );
}

/*
 *  ���ꥢ��I/O�ݡ��Ȥ��Ф������߽���
 */
static void
tl16pir552_isr_siop(SIOPCB *siopcb)
{
	tl16pir552_get_stat(siopcb);

	if ( tl16pir552_getready(siopcb) ) {
		/*
		 *  �������Υ�����Хå��롼�����ƤӽФ���
		 */
		tl16pir552_ierdy_rcv(siopcb->exinf);
	} else if ( tl16pir552_putready(siopcb) ) {
		/*
		 *  ������ǽ������Хå��롼�����ƤӽФ���
		 */
		tl16pir552_ierdy_snd(siopcb->exinf);
	}
}

/*
 *  SIO�γ���ߥ����ӥ��롼����
 */
void
tl16pir552_uart0_isr()
{
	if (siopcb_table[0].openflag) {
		tl16pir552_isr_siop(&(siopcb_table[0]));
	}
}

#if TNUM_SIOP >= 2
void
tl16pir552_uart1_isr()
{
	if (siopcb_table[1].openflag) {
		tl16pir552_isr_siop(&(siopcb_table[1]));
	}
}
#endif /* TNUM_SIOP >= 2 */

/*
 *  ���ꥢ��I/O�ݡ��ȤؤΥݡ���󥰤Ǥν���
 */
void
tl16pir552_putchar_pol( char val ) {

	const SIOPINIB  *siopinib = get_siopinib( LOGTASK_PORTID );

	/* ����������ץƥ��ˤʤ�ޤ��Ԥġ� */
	while( (tl16pir552_reb( siopinib->channel_addr, LSR ) & (TEMT) ) == 0 );

	tl16pir552_wrb( siopinib->channel_addr, THR, val );
}
