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
 *  @(#) $Id: syslog.c,v 1.9 2003/06/04 01:46:16 hiro Exp $
 */

/*
 *	�����ƥ����ǽ
 */

#undef OMIT_SYSLOG
#include "jsp_kernel.h"
#include "time_event.h"
#include "syslog.h"

/*
 *  ����ƥ����Ȥ˰ͤ�ʤ�CPU��å�����å����
 */
#define	lock_cpu()	(sense_context() ? i_lock_cpu() : t_lock_cpu())
#define	unlock_cpu()	(sense_context() ? i_unlock_cpu() : t_unlock_cpu())

#ifdef __logini

/*
 *  ���Хåե��Ȥ���˥����������뤿��Υݥ���
 */
SYSLOG	syslog_buffer[TCNT_SYSLOG_BUFFER];	/* ���Хåե� */
UINT	syslog_count;			/* ���Хåե���Υ��ο� */
UINT	syslog_head;			/* ��Ƭ�Υ��γ�Ǽ���� */
UINT	syslog_tail;			/* ���Υ��γ�Ǽ���� */
UINT	syslog_lost;			/* ����줿���ο� */

/*
 *  ���Ϥ��٤�������ν����١ʥӥåȥޥåס�
 */
UINT	syslog_logmask;			/* ���Хåե��˵�Ͽ���٤������� */
UINT	syslog_lowmask;			/* ���٥���Ϥ��٤������� */

/*
 *  �����ƥ����ǽ�ν����
 */
void
syslog_initialize()
{
	syslog_count = 0;
	syslog_head = syslog_tail = 0;
	syslog_lost = 0;

	syslog_logmask = 0;
	syslog_lowmask = LOG_UPTO(LOG_NOTICE);
}     

#endif /* __logini */

/* 
 *  ������ν���
 *
 *  CPU��å����֤�¹ԥ���ƥ����Ȥˤ�餺ư��Ǥ���褦�˼������Ƥ��롥
 */
#ifdef __vwri_log

SYSCALL ER
vwri_log(UINT prio, SYSLOG *p_log)
{
	BOOL	locked;

	locked = sense_lock();
	if (!locked) {
		lock_cpu();
	}

	/*
	 *  �����������
	 */
	p_log->logtim = systim_offset + current_time;

	/*
	 *  ���Хåե��˵�Ͽ
	 */
	if ((syslog_logmask & LOG_MASK(prio)) != 0) {
		syslog_buffer[syslog_tail] = *p_log;
		syslog_tail++;
		if (syslog_tail >= TCNT_SYSLOG_BUFFER) {
			syslog_tail = 0;
		}
		if (syslog_count < TCNT_SYSLOG_BUFFER) {
			syslog_count++;
		}
		else {
			syslog_head = syslog_tail;
			syslog_lost++;
		}
	}

	/*
	 *  ���٥����
	 */
	if ((syslog_lowmask & LOG_MASK(prio)) != 0) {
		syslog_print(p_log, sys_putc);
	}

	if (!locked) {
		unlock_cpu();
	}
	return(E_OK);
}

#endif /* __vwri_log */

/*
 *  ���Хåե�������ɽФ�
 *
 *  CPU��å����֤�¹ԥ���ƥ����Ȥˤ�餺ư��Ǥ���褦�˼������Ƥ��롥
 */
#ifdef __vrea_log

SYSCALL ER_UINT
vrea_log(SYSLOG *p_log)
{
	BOOL	locked;
	ER_UINT	ercd;

	locked = sense_lock();
	if (!locked) {
		lock_cpu();
	}
	if (syslog_count > 0) {
		*p_log = syslog_buffer[syslog_head];
		syslog_count--;
		syslog_head++;
		if (syslog_head >= TCNT_SYSLOG_BUFFER) {
			syslog_head = 0;
		}
		ercd = (ER_UINT) syslog_lost;
		syslog_lost = 0;
	}
	else {
		ercd = E_OBJ;
	}
	if (!locked) {
		unlock_cpu();
	}
	return(ercd);
}

#endif /* __vrea_log */

/* 
 *  ���Ϥ��٤�������ν����٤�����
 */
#ifdef __vmsk_log

SYSCALL ER
vmsk_log(UINT logmask, UINT lowmask)
{
	syslog_logmask = logmask;
	syslog_lowmask = lowmask;
	return(E_OK);
}

#endif /* __vmsk_log */

/* 
 *  �����ƥ����ǽ�ν�λ����
 *
 *  ���Хåե��˵�Ͽ���줿����������٥���ϵ�ǽ���Ѥ��ƽ��Ϥ�
 *  �롥
 */
#ifdef __logter

void
syslog_terminate()
{
	syslog_printf("-- buffered messages --", NULL, sys_putc);
	syslog_output(sys_putc);
}

#endif /* __logter */
