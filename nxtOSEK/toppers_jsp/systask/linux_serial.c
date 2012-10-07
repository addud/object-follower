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
 *  @(#) $Id: linux_serial.c,v 1.11 2003/12/11 00:36:49 honda Exp $
 */

#define _LINX_SERIAL_

#include <t_services.h>
#include <s_services.h>
#include <signal.h>
#include <termios.h>
#include <fcntl.h>
#include <errno.h>
#undef __USE_MISC 
#include <unistd.h>
#include <linux_sigio.h>
#include "kernel_id.h"


/*
 *  ���ꥢ��ݡ��Ȥ����٥����
 */

typedef struct hardware_serial_port_descripter {
	char   *path;		            /* UNIX ��ǤΥե�����̾ */
	int	   fd;		                /* �ե�����ǥ�������ץ� */
	struct termios	current_term;	/* ü��������� */
	struct termios	saved_term;    
} HWPORT;

#define NUM_PORT	1

#define RAWPORT1	{ 0 }

/*
 *  UNIX ��٥�Υݡ��Ƚ����/����åȥ��������
 *
 *  ���ߤμ����Ǥϡ�ü����Ȥ������������ͤ��Ƥ��ʤ�������ϡ�open ��
 *  ���Τ�ü�����ɤ����ǽ������Ѥ���٤���
 */

Inline void
hw_port_initialize(HWPORT *p)
{
	if (p->path) {
		p->fd = open(p->path, O_RDWR|O_NDELAY);
	}
	else {
		p->fd = 0;			/* ɸ�������Ϥ�Ȥ� */
	}
	fcntl(p->fd, F_SETOWN, getpid());
	fcntl(p->fd, F_SETFL, FASYNC|FNDELAY);
    
    
    tcgetattr(p->fd, &(p->saved_term));
    
	p->current_term = p->saved_term;
    p->current_term.c_lflag &= ~(ECHO);
    p->current_term.c_lflag &= ~(ICANON);
    p->current_term.c_cc[VMIN] = 1;
    p->current_term.c_cc[VTIME] = 0;
    
    tcsetattr(p->fd, TCSAFLUSH, &(p->current_term));
}

Inline void
hw_port_terminate(HWPORT *p)
{
    tcsetattr(p->fd, TCSAFLUSH, &(p->saved_term));
	fcntl(p->fd, F_SETFL, 0);
	if (p->path) {
		close(p->fd);
	}
}


/*
 *  ���ꥢ�륤�󥿥ե������ɥ饤���Ѥ� SIGIO ���Υ��٥�ȥ֥�å�
 */

static SIGIOEB	serial_sigioeb;


/*
 *  ���ꥢ��ݡ��ȴ����֥�å������
 */

typedef struct ioctl_descripter {
	int	echo;
	int	input;
	int	newline;
	int	flowc;
} IOCTL;

#define	SERIAL_BUFSZ	256	/* ���ꥢ�륤�󥿥ե������ѥХåե��Υ����� */

#define	inc(x)		(((x)+1 < SERIAL_BUFSZ) ? (x)+1 : 0)
#define	INC(x)		((x) = inc(x))


typedef struct serial_port_control_block {
	BOOL	init_flag;	/* ������Ѥ��� */
	HWPORT	hwport;		/* �ϡ��ɥ�������¸���� */
	ID	in_semid;	/* �����Хåե������ѥ��ޥե��� ID */
	ID	out_semid;	/* �����Хåե������ѥ��ޥե��� ID */

	int	in_read_ptr;	/* �����Хåե��ɤ߽Ф��ݥ��� */
	int	in_write_ptr;	/* �����Хåե��񤭹��ߥݥ��� */
	int	out_read_ptr;	/* �����Хåե��ɤ߽Ф��ݥ��� */
	int	out_write_ptr;	/* �����Хåե��񤭹��ߥݥ��� */
	UINT	ioctl;		/* ioctl �ˤ���������� */
	BOOL	send_enabled;	/* �����򥤥͡��֥뤷�Ƥ��뤫�� */
	BOOL	ixon_stopped;	/* STOP �������ä����֤��� */
	BOOL	ixoff_stopped;	/* ���� STOP �����ä����֤��� */
	char	ixoff_send;	/* ���� START/STOP �����뤫�� */

	char	in_buffer[SERIAL_BUFSZ];	/* �����Хåե����ꥢ */
	char	out_buffer[SERIAL_BUFSZ];	/* �����Хåե����ꥢ */
} SPCB;


#define	IN_BUFFER_EMPTY(spcb) \
		((spcb)->in_read_ptr == (spcb)->in_write_ptr)
#define	IN_BUFFER_FULL(spcb) \
		((spcb)->in_read_ptr == inc((spcb)->in_write_ptr))
#define	OUT_BUFFER_FULL(spcb) \
		((spcb)->out_read_ptr == inc((spcb)->out_write_ptr))

/*
 *  �⥸�塼����ǻȤ��ؿ�
 */
static void	sigint_handler();
static BOOL	serial_getc(SPCB *spcb, char *c);
static BOOL	serial_putc(SPCB *spcb, char c);


/*
 *  ���ꥢ��ݡ��ȴ����֥�å�������Ƚ����
 */

static SPCB spcb_table[NUM_PORT] = {
    {0, RAWPORT1, SEM_SERIAL1_IN, SEM_SERIAL1_OUT }
};

#define get_spcb(portid)	(&(spcb_table[(portid)-1]))
#define get_spcb_def(portid)	get_spcb((portid) ? (portid) : CONSOLE_PORTID)


/*
 *  �ݡ��Ȥν����
 */
int
serial_opn_por(ID portid)
{

    SPCB	*spcb;
	ER	ercd = E_OK;;

	if (!(1 <= portid && portid <= NUM_PORT)) {
		return(E_PAR);
	}
	spcb = get_spcb(portid);

	/*
	 *  ʣ���Υ�������Ʊ���� serial_open ��Ƥ־����ˤ��б����Ƥ�
	 *  �ʤ���
	 */
	if (spcb->init_flag) {		/* ������Ѥ��Υ����å� */
		return(E_OK);
	}

	/*
	 *  �ѿ��ν����
	 */
	spcb->in_read_ptr = spcb->in_write_ptr = 0;
	spcb->out_read_ptr = spcb->out_write_ptr = 0;
	spcb->ixon_stopped = spcb->ixoff_stopped = FALSE;
	spcb->ixoff_send = 0;

	/*
	 *  �ϡ��ɥ�������¸�ν����
	 */
	hw_port_initialize(&(spcb->hwport));
        
	/*
 	 *  �ץ�����λ�����륷���ʥ����ޤ���
         *  sigaction()�ǽ�ľ�������������Τ�?
	 */
	signal(SIGHUP, sigint_handler);
	signal(SIGINT, sigint_handler);
	signal(SIGTERM, sigint_handler);
        
    spcb->init_flag = TRUE;
	spcb->send_enabled = FALSE;
	return(ercd);
}

/*
 *  �ݡ��ȤΥ���åȥ�����
 */

ER
serial_cls_por(ID portid)
{
	SPCB	*spcb;

	if (!(1 <= portid && portid <= NUM_PORT)) {
		return(E_PAR);		/* �ݡ����ֹ�Υ����å� */
	}

	spcb = get_spcb(portid);
	if (!(spcb->init_flag)) {	/* ������Ѥ��Υ����å� */
		return(E_OBJ);
	}

	/*
	 *  �ϡ��ɥ�������¸�Υ���åȥ��������
	 */
	syscall(loc_cpu());
	hw_port_terminate(&(spcb->hwport));
	syscall(unl_cpu());

	spcb->init_flag = FALSE;
	return(E_OK);
}

/*
 *  �ץ�����λ�����륷���ʥ���Ф���ϥ�ɥ�
 */
void
sigint_handler()
{
	SPCB	*spcb;
	int	i;

	for (i = 1; i <= NUM_PORT; i++) {
		spcb = get_spcb(i);
		if (spcb->init_flag) {
			hw_port_terminate(&(spcb->hwport));
		}
	}
	exit(0);
}

/*
 *  �ե�����ȥ���ط������
 */
#define	STOP	'\023'		/* Control-S */
#define	START	'\021'		/* Control-Q */

#define	IXOFF_STOP	64	/* buffer area size to send STOP */
#define	IXOFF_START	128	/* buffer area size to send START */

#define	in_buf_area(p)							\
		((spcb->in_read_ptr >= spcb->in_write_ptr) ?		\
		 (spcb->in_read_ptr - spcb->in_write_ptr) :		\
		 (spcb->in_read_ptr + SERIAL_BUFSZ - spcb->in_write_ptr))
/*
 *  �桼�ƥ���ƥ��롼����
 */

Inline BOOL
read_char(SPCB *spcb, char *c)
{
	int	n;

	if ((n = read(spcb->hwport.fd, c, 1)) == 1) {
		return(1);
	}
	assert(n < 0 && errno == EWOULDBLOCK);
	return(0);
}

Inline BOOL
write_char(SPCB *spcb, char c)
{
	int	n;

	if ((n = write(spcb->hwport.fd, &c, 1)) == 1) {
		return(1);
	}
	assert(n < 0 && errno == EWOULDBLOCK);
	return(0);
}

/*
 *  ���ꥢ��ݡ��Ȥ���μ���
 */

static BOOL
serial_getc(SPCB *spcb, char *c)
{
	BOOL	buffer_empty;

	syscall(loc_cpu());
	*c = spcb->in_buffer[spcb->in_read_ptr];
        if (inc(spcb->in_write_ptr) == spcb->in_read_ptr) {
            /*
             *  �Хåե��ե���֤�������줿�顢�����ߤ����ä��Τ�
             *  Ʊ�������񤤤򤵤��롣
             */
            kill(getpid(), SIGIO);
        }
        
	INC(spcb->in_read_ptr);

	if (spcb->ixoff_stopped && (in_buf_area(spcb) > IXOFF_START)) {
		if (!write_char(spcb, START)) {
			spcb->ixoff_send = START;
		}
		spcb->ixoff_stopped = FALSE;
	}
	buffer_empty = IN_BUFFER_EMPTY(spcb);
	syscall(unl_cpu());
	return(buffer_empty);
}

ER_UINT
serial_rea_dat(ID portid, char *buf, UINT len)
{
    	SPCB	*spcb;
	BOOL	buffer_empty;
	char	c;
	int	i;


	if (sns_dpn()) {		/* ����ƥ����ȤΥ����å� */
		return(E_CTX);
	}
	if (!(0 <= portid && portid <= NUM_PORT)) {
		return(E_PAR);		/* �ݡ����ֹ�Υ����å� */
	}

	spcb = get_spcb_def(portid);
	if (!(spcb->init_flag)) {	/* ������Ѥ��Υ����å� */
		return(E_OBJ);
	}
	if (len == 0) {
		return(len);
	}


	syscall(wai_sem(spcb->in_semid));
	buffer_empty = FALSE;
	for (i = 0; i < len; i++) {
		buffer_empty = serial_getc(spcb, &c);
        if ((spcb->ioctl & IOCTL_ECHO) != 0) {
			syscall(wai_sem(spcb->out_semid));
			if (!serial_putc(spcb, c)) {
				syscall(sig_sem(spcb->out_semid));
			}
		}
		*buf++ = c;
		if (buffer_empty && i < len - 1) {
			syscall(wai_sem(spcb->in_semid));
		}
	}
	if (!buffer_empty) {
		syscall(sig_sem(spcb->in_semid));
	}
	return(len);
}


/*
 * ���ꥢ��ݡ��Ȥؤ�����
 */

static BOOL
serial_putc(SPCB *spcb, char c)
{
	BOOL	buffer_full;

    if (c == '\n' && (spcb->ioctl & IOCTL_CRLF) != 0) {
		if (serial_putc(spcb, '\r')) {
			syscall(wai_sem(spcb->out_semid));
		}
	}

	syscall(loc_cpu());
	if (!(spcb->ixon_stopped) && write_char(spcb, c)) {
		buffer_full = FALSE;
	}
	else {
		spcb->out_buffer[spcb->out_write_ptr] = c;
		INC(spcb->out_write_ptr);
		buffer_full = OUT_BUFFER_FULL(spcb);
	}
	syscall(unl_cpu());
	return(buffer_full);
}

ER_UINT
serial_wri_dat(ID portid, char *buf, UINT len)
{
	SPCB	*spcb;
	BOOL	buffer_full;
	int	i;

	if (sns_dpn()) {		/* ����ƥ����ȤΥ����å� */
		return(E_CTX);
	}
	if (!(0 <= portid && portid <= NUM_PORT)) {
		return(E_PAR);		/* �ݡ����ֹ�Υ����å� */
	}

	spcb = get_spcb_def(portid);
	if (!(spcb->init_flag)) {	/* ������Ѥ��Υ����å� */
		return(E_OBJ);
	}

	syscall(wai_sem(spcb->out_semid));
	buffer_full = FALSE;
	for (i = 0; i < len; i++) {
		buffer_full = serial_putc(spcb, *buf++);
		if (buffer_full && i < len - 1) {
			syscall(wai_sem(spcb->out_semid));
		}
	}
	if (!buffer_full) {
		syscall(sig_sem(spcb->out_semid));
	}
	return(len);
}

/*
 *  ���ꥢ��ݡ��Ȥ�����
 */

int
serial_ctl_por(ID portid, UINT ioctl)
{
	SPCB	*spcb;

	if (sns_ctx()) {		/* ����ƥ����ȤΥ����å� */
		return(E_CTX);
	}
	if (!(0 <= portid && portid <= NUM_PORT)) {
		return(E_PAR);		/* �ݡ����ֹ�Υ����å� */
	}

	spcb = get_spcb_def(portid);
	if (!(spcb->init_flag)) {	/* ������Ѥ��Υ����å� */
		return(E_OBJ);
	}

    spcb->ioctl = ioctl;
    return(E_OK);
}


/*
 *  ���ꥢ��ݡ��ȳ���ߥϥ�ɥ�
 */

static BOOL
serial_int_handler(ID portid)
{
	SPCB	*spcb;
	BOOL	flag;
	char	c;

	spcb = get_spcb(portid);
	flag = 0;

	/*
	 *  1ʸ����������
	 *
	 *  �ޤ����Хåե��ե�Ǥʤ����ˡ�1ʸ���ɤ�Ǥߤ롥�ɤ��С�
	 *  ����˱�����������Ԥ���
	 */
	if (inc(spcb->in_write_ptr) != spcb->in_read_ptr
            && read_char(spcb, &c)) {
		if ((spcb->ioctl & IOCTL_FCSND) != 0 && c == STOP) {
			spcb->ixon_stopped = TRUE;
		}
        else if (((spcb->ioctl & IOCTL_FCSND) != 0 || spcb->ixon_stopped)
                                 && (c == START || (spcb->ioctl & IOCTL_FCANY) != 0)) {
			spcb->ixon_stopped = FALSE;
		}
		else {
			spcb->in_buffer[spcb->in_write_ptr] = c;
                        if(spcb->in_read_ptr == spcb->in_write_ptr){
                            syscall(sig_sem(spcb->in_semid));
                        }
                        
			INC(spcb->in_write_ptr);
                        
			if ((spcb->ioctl & IOCTL_FCRCV) != 0 && !(spcb->ixoff_stopped)
					&& (in_buf_area(p) < IXOFF_STOP)) {
				spcb->ixoff_stopped = TRUE;
				spcb->ixoff_send = STOP;
			}
		}
		flag = 1;
	}

	/*
	 *  1ʸ����������
	 */
	if (spcb->ixoff_send) {
		if (write_char(spcb, spcb->ixoff_send)) {
			spcb->ixoff_send = 0;
			flag = 1;
		}
	}
	else if (!(spcb->ixon_stopped)
                      && spcb->out_read_ptr != spcb->out_write_ptr) {
		if (write_char(spcb, spcb->out_buffer[spcb->out_read_ptr])) {
                    if(OUT_BUFFER_FULL(spcb)){
			syscall(sig_sem(spcb->out_semid));
                    }
                    INC(spcb->out_read_ptr);                        
                    flag = 1;
		}
	}
	return(flag);
}



/*
 *  SIGIO ������Хå��롼����
 */

static BOOL
serial_sigio_callback(VP arg)
{
	BOOL	flag;

	do {
//		syscall(loc_cpu());
		flag = serial_int_handler(1);
//		syscall(unl_cpu());
	} while (flag);
	return(0);
}



/*
 *  ���ꥢ�륤�󥿥ե������ɥ饤�Фε�ư
 */

void
serial_initialize(VP_INT exinf)
{
	serial_sigioeb.callback = serial_sigio_callback;
	serial_sigioeb.arg = (VP) 0;
	syscall(enqueue_sigioeb_initialize(&serial_sigioeb));
}
