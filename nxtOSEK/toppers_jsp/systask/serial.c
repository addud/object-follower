/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2006 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
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
 *  @(#) $Id: serial.c,v 1.16 2006/02/12 05:26:42 hiro Exp $
 */

/*
 *	���ꥢ�륤�󥿥ե������ɥ饤��
 */

#include <t_services.h>
#include <serial.h>
#include <hw_serial.h>
#include "kernel_id.h"

/*
 *  �Хåե��������ȥե�����˴�Ϣ�������
 */

#define	SERIAL_BUFSZ	256		/* �ɥ饤�ФΥХåե������� */

#define	FC_STOP		'\023'		/* ����ȥ���-S */
#define	FC_START	'\021'		/* ����ȥ���-Q */

#define	BUFCNT_STOP	(SERIAL_BUFSZ - 64)	/* STOP��������ʸ���� */
#define	BUFCNT_START	(SERIAL_BUFSZ - 128)	/* START��������ʸ���� */

/*
 *  �������κݤ��������Ԥĺ�����֡�msecñ�̡�
 */
#define	MAX_FLUSH_WAIT	1000

/*
 *  ���ꥢ��ݡ��Ƚ�����֥�å�
 */
typedef struct serial_port_initialization_block {
	ID	rcv_semid;	/* �����Хåե������ѥ��ޥե���ID */
	ID	snd_semid;	/* �����Хåե������ѥ��ޥե���ID */
} SPINIB;

static const SPINIB spinib_table[TNUM_PORT] = {
	{ SERIAL_RCV_SEM1, SERIAL_SND_SEM1 }
#if TNUM_PORT >= 2
	,{ SERIAL_RCV_SEM2, SERIAL_SND_SEM2 }
#endif
#if TNUM_PORT >= 3
	,{ SERIAL_RCV_SEM3, SERIAL_SND_SEM3 }
#endif
};

/*
 *  ���ꥢ��ݡ��ȴ����֥�å�
 */
typedef struct serial_port_control_block {
	const SPINIB *spinib;	/* ���ꥢ��ݡ��Ƚ�����֥�å� */
	SIOPCB	*siopcb;	/* ���ꥢ��I/O�ݡ��ȴ����֥�å� */
	BOOL	openflag;	/* �����ץ�Ѥߥե饰 */
	UINT	ioctl;		/* ư������������� */

	UINT	rcv_read_ptr;	/* �����Хåե��ɽФ��ݥ��� */
	UINT	rcv_write_ptr;	/* �����Хåե�����ߥݥ��� */
	UINT	rcv_count;	/* �����Хåե����ʸ���� */
	char	rcv_fc_chr;	/* ����٤� START/STOP */
	BOOL	rcv_stopped;	/* STOP �����ä����֤��� */

	UINT	snd_read_ptr;	/* �����Хåե��ɽФ��ݥ��� */
	UINT	snd_write_ptr;	/* �����Хåե�����ߥݥ��� */
	UINT	snd_count;	/* �����Хåե����ʸ���� */
	BOOL	snd_stopped;	/* STOP �������ä����֤��� */

	char	rcv_buffer[SERIAL_BUFSZ];	/* �����Хåե� */
	char	snd_buffer[SERIAL_BUFSZ];	/* �����Хåե� */
} SPCB;

static SPCB	spcb_table[TNUM_PORT];

/*
 *  ���ꥢ��ݡ���ID���饷�ꥢ��ݡ��ȴ����֥�å�����Ф�����Υޥ���
 */
#define INDEX_PORT(portid)	((UINT)((portid) - 1))
#define get_spcb(portid)	(&(spcb_table[INDEX_PORT(portid)]))

/*
 *  �ݥ��󥿤Υ��󥯥����
 */
#define INC_PTR(ptr)		{ if (++ptr == SERIAL_BUFSZ) ptr = 0; }

/*
 *  ���ꥢ�륤�󥿥ե������ɥ饤�Фν�����롼����
 */
void
serial_initialize(VP_INT exinf)
{
	SPCB	*spcb;
	UINT	i;

	sio_initialize();
	for (spcb = spcb_table, i = 0; i < TNUM_PORT; spcb++, i++) {
		spcb->spinib = &(spinib_table[i]);
		spcb->openflag = FALSE;
	}
}

/*
 *  ���ꥢ��ݡ��ȤΥ����ץ�
 */
ER
serial_opn_por(ID portid)
{
	SPCB	*spcb;
	ER	ercd;

	if (sns_ctx()) {		/* ����ƥ����ȤΥ����å� */
		return(E_CTX);
	}
	if (!(1 <= portid && portid <= TNUM_PORT)) {
		return(E_ID);		/* �ݡ����ֹ�Υ����å� */
	}
	spcb = get_spcb(portid);

	_syscall(loc_cpu());
	if (spcb->openflag) {		/* �����ץ�Ѥߤ��Υ����å� */
		ercd = E_OBJ;
	}
	else {
		/*
		 *  �ѿ��ν����
		 */
		spcb->ioctl = (IOCTL_ECHO | IOCTL_CRLF
					| IOCTL_FCSND | IOCTL_FCRCV);


		spcb->rcv_read_ptr = spcb->rcv_write_ptr = 0;
		spcb->rcv_count = 0;
		spcb->rcv_fc_chr = '\0';
		spcb->rcv_stopped = FALSE;

		spcb->snd_read_ptr = spcb->snd_write_ptr = 0;
		spcb->snd_count = 0;
		spcb->snd_stopped = FALSE;

		/*
		 *  �ϡ��ɥ�������¸�Υ����ץ����
		 */
		spcb->siopcb = sio_opn_por(portid, (VP_INT) spcb);

		/*
		 *  �������Υ�����Хå�����Ĥ��롥
		 */
		sio_ena_cbr(spcb->siopcb, SIO_ERDY_RCV);
		spcb->openflag = TRUE;
		ercd = E_OK;
	}
	_syscall(unl_cpu());
	return(ercd);
}

/*
 *  ���ꥢ��ݡ��ȤΥ�����
 */
ER
serial_cls_por(ID portid)
{
	SPCB	*spcb;
	ER	ercd;

	if (sns_ctx()) {		/* ����ƥ����ȤΥ����å� */
		return(E_CTX);
	}
	if (!(1 <= portid && portid <= TNUM_PORT)) {
		return(E_ID);		/* �ݡ����ֹ�Υ����å� */
	}
	spcb = get_spcb(portid);

	_syscall(loc_cpu());
	if (!(spcb->openflag)) {	/* �����ץ�Ѥߤ��Υ����å� */
		ercd = E_OBJ;
	}
	else {
		/*
		 *  �ϡ��ɥ�������¸�Υ���������
		 */
		sio_cls_por(spcb->siopcb);
		spcb->openflag = FALSE;
		ercd = E_OK;
	}
	_syscall(unl_cpu());
	return(ercd);
}

/*
 *  ���ꥢ��ݡ��Ȥؤ�ʸ������
 */
Inline BOOL
serial_snd_chr(SPCB *spcb, char c)
{
	if (sio_snd_chr(spcb->siopcb, c)) {
		return(TRUE);
	}
	else {
		sio_ena_cbr(spcb->siopcb, SIO_ERDY_SND);
		return(FALSE);
	}
}

/*
 *  ���ꥢ��ݡ��Ȥؤ�����
 */
static BOOL
serial_wri_chr(SPCB *spcb, char c)
{
	BOOL	buffer_full;

	/*
	 *  LF ������ CR ���������롥
	 */
	if (c == '\n' && (spcb->ioctl & IOCTL_CRLF) != 0) {
		if (serial_wri_chr(spcb, '\r')) {
			_syscall(wai_sem(spcb->spinib->snd_semid));
		}
	}

	_syscall(loc_cpu());
	if (spcb->snd_count == 0 && !(spcb->snd_stopped)
				&& serial_snd_chr(spcb, c)) {
		/*
		 *  ���ꥢ��I/O�ǥХ����������쥸������ʸ��������뤳
		 *  �Ȥ�����������硥
		 */
		buffer_full = FALSE;
	}
	else {
		/*
		 *  �����Хåե���ʸ��������롥
		 */
		spcb->snd_buffer[spcb->snd_write_ptr] = c;
		INC_PTR(spcb->snd_write_ptr);
		spcb->snd_count++;
		buffer_full = (spcb->snd_count == SERIAL_BUFSZ);
	}
	_syscall(unl_cpu());
	return(buffer_full);
}

ER_UINT
serial_wri_dat(ID portid, char *buf, UINT len)
{
	SPCB	*spcb;
	BOOL	buffer_full;
	UINT	i;

	if (sns_dpn()) {		/* ����ƥ����ȤΥ����å� */
		return(E_CTX);
	}
	if (!(1 <= portid && portid <= TNUM_PORT)) {
		return(E_ID);		/* �ݡ����ֹ�Υ����å� */
	}

	spcb = get_spcb(portid);
	if (!(spcb->openflag)) {	/* �����ץ�Ѥߤ��Υ����å� */
		return(E_OBJ);
	}

	buffer_full = TRUE;		/* �롼�פ�1���� wai_sem ���� */
	for (i = 0; i < len; i++) {
		if (buffer_full) {
			_syscall(wai_sem(spcb->spinib->snd_semid));
		}
		buffer_full = serial_wri_chr(spcb, *buf++);
	}
	if (!buffer_full) {
		_syscall(sig_sem(spcb->spinib->snd_semid));
	}
	return((ER_UINT) len);
}

/*
 *  ���ꥢ��ݡ��Ȥ���μ���
 */
static BOOL
serial_rea_chr(SPCB *spcb, char *c)
{
	BOOL	buffer_empty;

	_syscall(loc_cpu());

	/*
	 *  �����Хåե�����ʸ������Ф���
	 */
	*c = spcb->rcv_buffer[spcb->rcv_read_ptr];
	INC_PTR(spcb->rcv_read_ptr);
	spcb->rcv_count--;
	buffer_empty = (spcb->rcv_count == 0);

	/*
	 *  START ���������롥
	 */
	if (spcb->rcv_stopped && spcb->rcv_count <= BUFCNT_START) {
		if (!serial_snd_chr(spcb, FC_START)) {
			spcb->rcv_fc_chr = FC_START;
		}
		spcb->rcv_stopped = FALSE;
	}
	_syscall(unl_cpu());

	/*
	 *  �������Хå�������
	 */
	if ((spcb->ioctl & IOCTL_ECHO) != 0) {
		_syscall(wai_sem(spcb->spinib->snd_semid));
		if (!serial_wri_chr(spcb, *c)) {
			_syscall(sig_sem(spcb->spinib->snd_semid));
		}
	}
	return(buffer_empty);
}

ER_UINT
serial_rea_dat(ID portid, char *buf, UINT len)
{
	SPCB	*spcb;
	BOOL	buffer_empty;
	UINT	i;

	if (sns_dpn()) {		/* ����ƥ����ȤΥ����å� */
		return(E_CTX);
	}
	if (!(1 <= portid && portid <= TNUM_PORT)) {
		return(E_ID);		/* �ݡ����ֹ�Υ����å� */
	}

	spcb = get_spcb(portid);
	if (!(spcb->openflag)) {	/* �����ץ�Ѥߤ��Υ����å� */
		return(E_OBJ);
	}

	buffer_empty = TRUE;		/* �롼�פ�1���� wai_sem ���� */
	for (i = 0; i < len; i++) {
		if (buffer_empty) {
			_syscall(wai_sem(spcb->spinib->rcv_semid));
		}
		buffer_empty = serial_rea_chr(spcb, buf++);
	}
	if (!buffer_empty) {
		_syscall(sig_sem(spcb->spinib->rcv_semid));
	}
	return((ER_UINT) len);
}

/*
 *  ���ꥢ��ݡ��Ȥ�����
 */
ER
serial_ctl_por(ID portid, UINT ioctl)
{
	SPCB	*spcb;

	if (sns_ctx()) {		/* ����ƥ����ȤΥ����å� */
		return(E_CTX);
	}
	if (!(1 <= portid && portid <= TNUM_PORT)) {
		return(E_ID);		/* �ݡ����ֹ�Υ����å� */
	}

	spcb = get_spcb(portid);
	if (!(spcb->openflag)) {	/* �����ץ�Ѥߤ��Υ����å� */
		return(E_OBJ);
	}

	spcb->ioctl = ioctl;
	return(E_OK);
}

/*
 *  ���ꥢ��ݡ��Ⱦ��֤λ���
 */
ER
serial_ref_por(ID portid, T_SERIAL_RPOR *pk_rpor)
{
	SPCB	*spcb;

	if (sns_ctx()) {		/* ����ƥ����ȤΥ����å� */
		return(E_CTX);
	}
	if (!(1 <= portid && portid <= TNUM_PORT)) {
		return(E_ID);		/* �ݡ����ֹ�Υ����å� */
	}

	spcb = get_spcb(portid);
	if (!(spcb->openflag)) {	/* �����ץ�Ѥߤ��Υ����å� */
		return(E_OBJ);
	}

	pk_rpor->reacnt = spcb->rcv_count;
	pk_rpor->wricnt = spcb->snd_count;
	return(E_OK);
}

/*
 *  ���ꥢ��ݡ��Ȥ����������ǽ������Хå�
 */
void
sio_ierdy_snd(VP_INT exinf)
{
	SPCB	*spcb;

	spcb = (SPCB *) exinf;
	if (spcb->rcv_fc_chr != '\0') {
		/*
		 *  START/STOP ���������롥
		 */
		(void) sio_snd_chr(spcb->siopcb, spcb->rcv_fc_chr);
		spcb->rcv_fc_chr = '\0';
	}
	else if (!(spcb->snd_stopped) && spcb->snd_count > 0) {
		/*
		 *  �����Хåե��椫��ʸ������Ф����������롥
		 */
		(void) sio_snd_chr(spcb->siopcb,
				spcb->snd_buffer[spcb->snd_read_ptr]);
		INC_PTR(spcb->snd_read_ptr);
		if (spcb->snd_count == SERIAL_BUFSZ) {
			_syscall(isig_sem(spcb->spinib->snd_semid));
		}
		spcb->snd_count--;
	}
	else {
		/*
		 *  �������٤�ʸ�����ʤ����ϡ�������ǽ������Хå���
		 *  �ػߤ��롥
		 */
		sio_dis_cbr(spcb->siopcb, SIO_ERDY_SND);
	}
}

/*
 *  ���ꥢ��ݡ��Ȥ���μ������Υ�����Хå�
 */
void
sio_ierdy_rcv(VP_INT exinf)
{
	SPCB	*spcb;
	char	c;

	spcb = (SPCB *) exinf;
	c = (char) sio_rcv_chr(spcb->siopcb);
	if ((spcb->ioctl & IOCTL_FCSND) != 0 && c == FC_STOP) {
		/*
		 *  ����������ߤ��롥�������ʸ���Ϥ��Τޤ��������롥
		 */
		spcb->snd_stopped = TRUE;
	}
	else if (spcb->snd_stopped && (c == FC_START
				|| (spcb->ioctl & IOCTL_FCANY) != 0)) {
		/*
		 *  ������Ƴ����롥
		 */
		spcb->snd_stopped = FALSE;
		if (spcb->snd_count > 0) {
			c = spcb->snd_buffer[spcb->snd_read_ptr];
			if (serial_snd_chr(spcb, c)) {
				INC_PTR(spcb->snd_read_ptr);
				if (spcb->snd_count == SERIAL_BUFSZ) {
					_syscall(isig_sem(spcb->spinib
								->snd_semid));
				}
				spcb->snd_count--;
			}
		}
	}
	else if ((spcb->ioctl & IOCTL_FCSND) != 0 && c == FC_START) {
		/*
		 *  �������Ф��ƥե����椷�Ƥ����硤START �ϼΤƤ롥
		 */
	}
	else if (spcb->rcv_count == SERIAL_BUFSZ) {
		/*
		 *  �Хåե��ե�ξ�硤��������ʸ����ΤƤ롥
		 */
	}
	else {
		/*
		 *  ��������ʸ��������Хåե�������롥
		 */
		spcb->rcv_buffer[spcb->rcv_write_ptr] = c;
		INC_PTR(spcb->rcv_write_ptr);
		if (spcb->rcv_count == 0) {
			_syscall(isig_sem(spcb->spinib->rcv_semid));
		}
		spcb->rcv_count++;

		/*
		 *  STOP ���������롥
		 */
		if ((spcb->ioctl & IOCTL_FCRCV) != 0 && !(spcb->rcv_stopped)
					&& (spcb->rcv_count >= BUFCNT_STOP)) {
			if (!serial_snd_chr(spcb, FC_STOP)) {
				spcb->rcv_fc_chr = FC_STOP;
			}
			spcb->rcv_stopped = TRUE;
		}
	}
}
