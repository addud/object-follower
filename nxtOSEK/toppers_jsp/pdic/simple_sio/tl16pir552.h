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

#ifndef _TL16PIR552_H_
#define _TL16PIR552_H_

#include <s_services.h>		/* �ǥХ����ɥ饤����ɸ�।�󥯥롼�ɥե����� */

/*
 *  ���ꥢ�롿�ѥ��� I/O TL16PIR552(TI) ��Ϣ�����
 */
/* TL16PIR552�Υ쥸�����Υ��ɥ쥹 */
#define RBR	0x00	/* Receiver Buffer (�ɤ߽Ф�) */
#define THR	0x00	/* Transmitter Holding Register (�񤭽Ф�) */
#define DLL	0x00	/* Divisor Latch (LSB) */
#define IER	0x10	/* Interrupt-Enable Register */
#define DLM	0x10	/* Divisor Latch (MSB) */
#define	IIR	0x20	/* Interrupt-Ident Register (�ɤ߽Ф�) */
#define	FCR	0x20	/* FIFO Control Register (�񤭽Ф�) */
#define	LCR	0x30	/* Line-Control Register */
#define	MCR	0x40	/* Modem-Control Register */
#define	LSR	0x50	/* Line-Status Register */
#define	MSR	0x60	/* Modem-Status Register */
#define	SCR	0x70	/* Scratch Register */

/* for LCR */
#define	WORD_LENGTH_8		(BIT1 | BIT0)
#define	STOP_BITS_1		0u		/* BIT2 */
#define	PARITY_NON		0u		/* BIT3, 4 */
/* BIT5,6 ��ά */
#define	DIVISOR_LATCH_ACC	BIT7

/* for IER */
#define	DIS_INT			0u
#define	RECEIVE_DATA_AVAILABLE	BIT0
#define	TRANS_REG_EMPTY		BIT1
#define RECEIVE_LINE_STATUS	BIT2
#define MODEM_STATUS		BIT3

/* for MCR */
#define	DTR			BIT0
#define	RTS			BIT1
#define	ENABLE_EXT_INT		BIT3
#define	AUTOFLOW_CONTROL	BIT5

/* for FCR */
#define	FIFO_ENABLE		BIT0
#define	RECEIVE_FIFO_RESET	BIT1
#define	TRANS_FIFO_RESET	BIT2
#define RECEIVE_TRIG_1_BYTE	0u		/* BIT6, 7 */
#define RECEIVE_TRIG_4_BYTE	BIT6
#define	RECEIVE_TRIG_8_BYTE	BIT7
#define	RECEIVE_TRIG_14_BYTE	(BIT6 | BIT7)

/* for IIR */
#define	INT_MASK		0x0f
#define	INT_RECEIVE_DATA	BIT2
#define INT_CHAR_TIME_OUT	(BIT3 | BIT2)
#define	INT_TRANS_EMPTY		BIT1

/* for LSR */
#define	THRE			BIT5
#define TEMT			BIT6

/* �ܡ��졼������ط� */
#define	PRE_DIVISOR	4
#define	DIVISOR		XIN_CLOCK / (8 * DEVIDE_RATIO * PRE_DIVISOR)

#ifndef _MACRO_ONLY

/*
 *  ���ꥢ��I/O�ݡ��ȴ����֥�å������
 */
typedef struct sio_port_control_block	SIOPCB;

#endif /* _MACRO_ONLY */

/*
 *  SIO�ѥ����ƥ।�󥿥ե������쥤�䡼
 */
/* x : �ݡ��ȤΥ١������ɥ쥹��y : �쥸�������ե��åȡ�z : �쥸������ */
#define tl16pir552_wrb( x, y, z )	sil_wrb_mem( (VP)(x + y), z )
#define tl16pir552_reb( x, y )		sil_reb_mem( (VP)(x + y) )

/*
 *  ������Хå��롼����μ����ֹ�
 */
#define SIO_ERDY_SND	1u		/* ������ǽ������Хå� */
#define SIO_ERDY_RCV	2u		/* �������Υ�����Хå� */

#ifndef _MACRO_ONLY

/*
 *  SIO�ɥ饤�Фν�����롼����
 */
extern void	tl16pir552_initialize(void);

/*
 *  �����ץ󤷤Ƥ���ݡ��Ȥ����뤫��
 */
extern BOOL	tl16pir552_openflag(void);

/*
 *  ���ꥢ��I/O�ݡ��ȤΥ����ץ�
 */
extern SIOPCB	*tl16pir552_opn_por(ID siopid, VP_INT exinf);

/*
 *  ���ꥢ��I/O�ݡ��ȤΥ�����
 */
extern void	tl16pir552_cls_por(SIOPCB *siopcb);

/*
 *  ���ꥢ��I/O�ݡ��Ȥؤ�ʸ������
 */
extern BOOL	tl16pir552_snd_chr(SIOPCB *siopcb, char c);

/*
 *  ���ꥢ��I/O�ݡ��Ȥ����ʸ������
 */
extern INT	tl16pir552_rcv_chr(SIOPCB *siopcb);

/*
 *  ���ꥢ��I/O�ݡ��Ȥ���Υ�����Хå��ε���
 */
extern void	tl16pir552_ena_cbr(SIOPCB *siopcb, UINT cbrtn);

/*
 *  ���ꥢ��I/O�ݡ��Ȥ���Υ�����Хå��ζػ�
 */
extern void	tl16pir552_dis_cbr(SIOPCB *siopcb, UINT cbrtn);

/*
 *  SIO�γ���ߥ����ӥ��롼����
 */
extern void	tl16pir552_uart0_isr(void);
extern void	tl16pir552_uart1_isr(void);

/*
 *  ���ꥢ��I/O�ݡ��Ȥ����������ǽ������Хå�
 */
extern void	tl16pir552_ierdy_snd(VP_INT exinf);

/*
 *  ���ꥢ��I/O�ݡ��Ȥ���μ������Υ�����Хå�
 */
extern void	tl16pir552_ierdy_rcv(VP_INT exinf);

/*
 *  �����ͥ뵯ư���Ѥν���� (sys_putc������)
 */
extern void	tl16pir552_init(void);

/*
 *  ���ꥢ��I/O�ݡ��Ȥؤ�ʸ�������ʥݡ���󥰡�
 */
extern void	tl16pir552_putchar_pol(char c);

#endif /* _MACRO_ONLY */
#endif /* _TL16PIR552_H_ */
