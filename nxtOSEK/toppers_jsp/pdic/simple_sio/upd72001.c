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
 *  @(#) $Id: upd72001.c,v 1.4 2003/12/13 06:21:49 hiro Exp $
 */

/*
 *	��PD72001�� �ʰ�SIO�ɥ饤��
 */

#include <s_services.h>
#include <upd72001.h>

/*
 *  �ǥХ����쥸�����Υ��������ֳֻ��֡�nsecñ�̡�
 *
 *  200�Ȥ����ͤˤ��ޤ꺬��Ϥʤ���
 */
#define	UPD72001_DELAY	200

/*
 *  ��PD72001�Υ쥸�������ֹ�
 */
#define	UPD72001_CR0	0x00u		/* ����ȥ���쥸���� */
#define	UPD72001_CR1	0x01u
#define	UPD72001_CR2	0x02u
#define	UPD72001_CR3	0x03u
#define	UPD72001_CR4	0x04u
#define	UPD72001_CR5	0x05u
#define	UPD72001_CR10	0x0au
#define	UPD72001_CR12	0x0cu
#define	UPD72001_CR14	0x0eu
#define	UPD72001_CR15	0x0fu

#define	UPD72001_SR0	0x00u		/* ���ơ������쥸���� */

/*
 *  ����ȥ���쥸������������
 */
#define CR_RESET	0x18u		/* �ݡ��ȥꥻ�åȥ��ޥ�� */

#define CR0_EOI		0x38u		/* EOI��End of Interrupt��*/

#define CR1_DOWN	0x00u		/* ������ߤ�ػ� */
#define CR1_RECV	0x10u		/* ��������ߵ��ĥӥå� */
#define CR1_SEND	0x02u		/* ��������ߵ��ĥӥå� */

#define CR3_DEF		0xc1u		/* �ǡ��� 8bit���������͡��֥� */
#define CR4_DEF		0x44u		/* ���ȥåץӥå� 1bit���ѥ�ƥ��ʤ� */
#define CR5_DEF		0xeau		/* �ǡ��� 8bit���������͡��֥� */

#define CR10_DEF	0x00u		/* NRZ */
#define CR14_DEF	0x07u		/* �ܡ��졼�ȥ����ͥ졼�����͡��֥� */
#define CR15_DEF	0x56u		/* �ܡ��졼�ȥ����ͥ졼������ */

#define SR0_RECV	0x01u		/* �������Υӥå� */
#define SR0_SEND	0x04u		/* ������ǽ�ӥå� */

/*
 *  ���ꥢ��I/O�ݡ��Ƚ�����֥�å������
 */
typedef struct sio_port_initialization_block {
	VP	data;		/* �ǡ����쥸���������� */
	VP	ctrl;		/* ����ȥ���쥸���������� */

	UB	cr3_def;	/* CR3�������͡ʼ����ӥåȿ���*/
	UB	cr4_def;	/* CR4�������͡ʥ��ȥåץӥåȡ��ѥ�ƥ���*/
	UB	cr5_def;	/* CR5�������͡������ӥåȿ���*/
	UB	brg1_def;	/* �ܡ��졼�Ⱦ�̤������� */
	UB	brg2_def;	/* �ܡ��졼�Ȳ��̤������� */
} SIOPINIB;

/*
 *  ���ꥢ��I/O�ݡ��ȴ����֥�å������
 */
struct sio_port_control_block {
	const SIOPINIB	*siopinib;	/* ���ꥢ��I/O�ݡ��Ƚ�����֥�å� */
	VP_INT		exinf;		/* ��ĥ���� */
	BOOL		openflag;	/* �����ץ�Ѥߥե饰 */
	UB		cr1;		/* CR1�������͡ʳ���ߵ��ġ�*/
	BOOL		getready;	/* ʸ��������������� */
	BOOL		putready;	/* ʸ���������Ǥ������ */
};

/*
 *  ���ꥢ��I/O�ݡ��Ƚ�����֥�å�
 *
 *  ID = 1 ��ݡ���B��ID = 2 ��ݡ���A���б������Ƥ��롥
 */
const SIOPINIB siopinib_table[TNUM_SIOP] = {
	{ (VP) TADR_UPD72001_DATAB, (VP) TADR_UPD72001_CTRLB,
		CR3_DEF, CR4_DEF, CR5_DEF, BRG1_DEF, BRG2_DEF },
#if TNUM_SIOP >= 2
	{ (VP) TADR_UPD72001_DATAA, (VP) TADR_UPD72001_CTRLA,
		CR3_DEF, CR4_DEF, CR5_DEF, BRG1_DEF, BRG2_DEF },
#endif /* TNUM_SIOP >= 2 */
};

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
 *  �ǥХ����쥸�����ؤΥ��������ؿ�
 */
Inline UB
upd72001_read_reg(VP addr)
{
	UB	val;

	val = (UB) upd72001_reb_reg(addr);
	sil_dly_nse(UPD72001_DELAY);
	return(val);
}

Inline void
upd72001_write_reg(VP addr, UB val)
{
	upd72001_wrb_reg(addr, (VB) val);
	sil_dly_nse(UPD72001_DELAY);
}

Inline UB
upd72001_read_ctrl(VP addr, UB reg)
{
	upd72001_write_reg(addr, reg);
	return(upd72001_read_reg(addr));
}

Inline void
upd72001_write_ctrl(VP addr, UB reg, UB val)
{
	upd72001_write_reg(addr, reg);
	upd72001_write_reg(addr, val);
}

Inline void
upd72001_write_brg(VP addr, UB reg, UB val, UB brg2, UB brg1)
{
	upd72001_write_reg(addr, reg);
	upd72001_write_reg(addr, val);
	upd72001_write_reg(addr, brg2);
	upd72001_write_reg(addr, brg1);
	(void) upd72001_read_reg(addr);		/* ���ߡ��꡼�� */
}

/*
 *  ���֤��ɽФ���SR0���ɽФ���
 *
 *  ��PD72001�ϡ����֡�SR0�ˤ�����ɤ�ȼ������ΥӥåȤ�����Ƥ��ޤ���
 *  �ᡤ���֤��ɤ߽Ф��ؿ����ߤ������ꥢ��I/O�ݡ��ȴ����֥�å����
 *  getready �˼������ξ��֡�putready ��������ǽ���֤���¸���Ƥ������
 *  ����ǽ���֤���¸�����פ��⤷��ʤ��ˡ�
 *  ���֥쥸�������ɤ�Ǥ�������ΥӥåȤ�����ʤ��ǥХ����ʤ����餬��
 *  �̤Ȼפ���ˤǤϡ����δؿ���ɬ�פʤ���
 */
static void
upd72001_get_stat(SIOPCB *siopcb)
{
	UB	sr0;

	sr0 = upd72001_read_ctrl(siopcb->siopinib->ctrl, UPD72001_SR0);
	if ((sr0 & SR0_RECV) != 0) {
		siopcb->getready = TRUE;
	}
	if ((sr0 & SR0_SEND) != 0) {
		siopcb->putready = TRUE;
	}
}

/*
 *  ʸ��������Ǥ��뤫��
 */
Inline BOOL
upd72001_getready(SIOPCB *siopcb)
{
	upd72001_get_stat(siopcb);
	return(siopcb->getready);
}

/*
 *  ʸ���������Ǥ��뤫��
 */
Inline BOOL
upd72001_putready(SIOPCB *siopcb)
{
	upd72001_get_stat(siopcb);
	return(siopcb->putready);
}

/*
 *  ��������ʸ���μ�Ф�
 */
Inline char
upd72001_getchar(SIOPCB *siopcb)
{
	siopcb->getready = FALSE;
	return((char) upd72001_read_reg(siopcb->siopinib->data));
}

/*
 *  ��������ʸ���ν����
 */
Inline void
upd72001_putchar(SIOPCB *siopcb, char c)
{
	siopcb->putready = FALSE;
	upd72001_write_reg(siopcb->siopinib->data, (UB) c);
}

/*
 *  EOI��End Of Interrupt��ȯ��
 */
Inline void
upd72001_eoi()
{
	upd72001_write_ctrl((VP) TADR_UPD72001_CTRLA, UPD72001_CR0, CR0_EOI);
}

/*
 *  SIO�ɥ饤�Фν�����롼����
 */
void
upd72001_initialize()
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
 *  �����ץ󤷤Ƥ���ݡ��Ȥ����뤫��
 */
BOOL
upd72001_openflag(void)
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
upd72001_opn_por(ID siopid, VP_INT exinf)
{
	SIOPCB		*siopcb;
	const SIOPINIB	*siopinib;

	siopcb = get_siopcb(siopid);
	siopinib = siopcb->siopinib;

	upd72001_write_reg(siopinib->ctrl, CR_RESET);
	if (!upd72001_openflag()) {
		upd72001_write_ctrl((VP) TADR_UPD72001_CTRLA,
						UPD72001_CR2, 0x18);
		upd72001_write_ctrl((VP) TADR_UPD72001_CTRLB,
						UPD72001_CR2, 0x00);
	}
	siopcb->cr1 = CR1_DOWN;
	upd72001_write_ctrl(siopinib->ctrl, UPD72001_CR1, siopcb->cr1);
	upd72001_write_ctrl(siopinib->ctrl, UPD72001_CR4, siopinib->cr4_def);
	upd72001_write_brg(siopinib->ctrl, UPD72001_CR12, 
				0x01, siopinib->brg2_def, siopinib->brg1_def);
	upd72001_write_brg(siopinib->ctrl, UPD72001_CR12,
				0x02, siopinib->brg2_def, siopinib->brg1_def);
	upd72001_write_ctrl(siopinib->ctrl, UPD72001_CR15, CR15_DEF);
	upd72001_write_ctrl(siopinib->ctrl, UPD72001_CR14, CR14_DEF);
	upd72001_write_ctrl(siopinib->ctrl, UPD72001_CR10, CR10_DEF);
	upd72001_write_ctrl(siopinib->ctrl, UPD72001_CR3, siopinib->cr3_def);
	upd72001_write_ctrl(siopinib->ctrl, UPD72001_CR5, siopinib->cr5_def);
	siopcb->exinf = exinf;
	siopcb->getready = siopcb->putready = FALSE;
	siopcb->openflag = TRUE;
	return(siopcb);
}

/*
 *  ���ꥢ��I/O�ݡ��ȤΥ�����
 */
void
upd72001_cls_por(SIOPCB *siopcb)
{
	upd72001_write_ctrl(siopcb->siopinib->ctrl, UPD72001_CR1, CR1_DOWN);
	siopcb->openflag = FALSE;
}

/*
 *  ���ꥢ��I/O�ݡ��Ȥؤ�ʸ������
 */
BOOL
upd72001_snd_chr(SIOPCB *siopcb, char c)
{
	if (upd72001_putready(siopcb)) {
		upd72001_putchar(siopcb, c);
		return(TRUE);
	}
	return(FALSE);
}

/*
 *  ���ꥢ��I/O�ݡ��Ȥ����ʸ������
 */
INT
upd72001_rcv_chr(SIOPCB *siopcb)
{
	if (upd72001_getready(siopcb)) {
		return((INT)(UB) upd72001_getchar(siopcb));
	}
	return(-1);
}

/*
 *  ���ꥢ��I/O�ݡ��Ȥ���Υ�����Хå��ε���
 */
void
upd72001_ena_cbr(SIOPCB *siopcb, UINT cbrtn)
{
	UB	cr1_bit = 0;

	switch (cbrtn) {
	case SIO_ERDY_SND:
		cr1_bit = CR1_SEND;
		break;
	case SIO_ERDY_RCV:
		cr1_bit = CR1_RECV;
		break;
	}
	siopcb->cr1 |= cr1_bit;
	upd72001_write_ctrl(siopcb->siopinib->ctrl, UPD72001_CR1, siopcb->cr1);
}

/*
 *  ���ꥢ��I/O�ݡ��Ȥ���Υ�����Хå��ζػ�
 */
void
upd72001_dis_cbr(SIOPCB *siopcb, UINT cbrtn)
{
	UB	cr1_bit = 0;

	switch (cbrtn) {
	case SIO_ERDY_SND:
		cr1_bit = CR1_SEND;
		break;
	case SIO_ERDY_RCV:
		cr1_bit = CR1_RECV;
		break;
	}
	siopcb->cr1 &= ~cr1_bit;
	upd72001_write_ctrl(siopcb->siopinib->ctrl, UPD72001_CR1, siopcb->cr1);
}

/*
 *  ���ꥢ��I/O�ݡ��Ȥ��Ф������߽���
 */
static void
upd72001_isr_siop(SIOPCB *siopcb)
{
	if ((siopcb->cr1 & CR1_RECV) != 0 && upd72001_getready(siopcb)) {
		/*
		 *  �������Υ�����Хå��롼�����ƤӽФ���
		 */
		upd72001_ierdy_rcv(siopcb->exinf);
	}
	if ((siopcb->cr1 & CR1_SEND) != 0 && upd72001_putready(siopcb)) {
		/*
		 *  ������ǽ������Хå��롼�����ƤӽФ���
		 */
		upd72001_ierdy_snd(siopcb->exinf);
	}
}

/*
 *  SIO�γ���ߥ����ӥ��롼����
 */
void
upd72001_isr()
{
	if (siopcb_table[0].openflag) {
		upd72001_isr_siop(&(siopcb_table[0]));
	}
#if TNUM_SIOP >= 2
	if (siopcb_table[1].openflag) {
		upd72001_isr_siop(&(siopcb_table[1]));
	}
#endif /* TNUM_SIOP >= 2 */
	upd72001_eoi();
}
