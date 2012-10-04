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
 *  @(#) $Id: syslog.h,v 1.3 2003/07/08 14:44:19 hiro Exp $
 */

/*
 *	�����ƥ����ǽ
 */

#ifndef _SYSLOG_H_
#define _SYSLOG_H_

#include <t_syslog.h>

/*
 *  ���Хåե��Ȥ���˥����������뤿��Υݥ���
 */
#ifndef TCNT_SYSLOG_BUFFER
#define TCNT_SYSLOG_BUFFER	32	/* ���Хåե��Υ����� */
#endif /* TCNT_SYSLOG_BUFFER */

extern SYSLOG	syslog_buffer[];	/* ���Хåե� */
extern UINT	syslog_count;		/* ���Хåե���Υ��ο� */
extern UINT	syslog_head;		/* ��Ƭ�Υ��γ�Ǽ���� */
extern UINT	syslog_tail;		/* ���Υ��γ�Ǽ���� */
extern UINT	syslog_lost;		/* ����줿���ο� */

/*
 *  ���Ϥ��٤�������ν����١ʥӥåȥޥåס�
 */
extern UINT	syslog_logmask;		/* ���Хåե��˵�Ͽ���٤������� */
extern UINT	syslog_lowmask;		/* ���٥���Ϥ��٤������� */

#ifndef OMIT_SYSLOG

/*
 *  �����ƥ����ǽ�ν����
 */
extern void	syslog_initialize(void);

/*
 *  �����ƥ����ǽ�ν�λ����
 */
extern void	syslog_terminate(void);

#else /* OMIT_SYSLOG */

#define syslog_initialize()	((void) 0)
#define syslog_terminate()	((void) 0)

#endif /* OMIT_SYSLOG */
#endif /* _SYSLOG_H_ */
