/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2004-2005 by Embedded and Real-Time Systems Laboratory
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
 *  @(#) $Id: vasyslog.c,v 1.7 2005/11/24 11:46:02 hiro Exp $
 */

/*
 *	���ѿ������Υ����ƥ���饤�֥��
 */

#include <t_services.h>
#include <stdarg.h>

ER
syslog(UINT prio, const char *format, ...)
{
	SYSLOG	log;
	va_list	ap;
	int	i;
	int	c;
	BOOL	lflag;

	log.logtype = LOG_TYPE_COMMENT;
	log.loginfo[0] = (VP_INT) format;
	i = 1;
	va_start(ap, format);

	while ((c = *format++) != '\0' && i < TMAX_LOGINFO) {
		if (c != '%') {
			continue;
		}

		lflag = FALSE;
		c = *format++;
		while ('0' <= c && c <= '9') {
			c = *format++;
		}
		if (c == 'l') {
			lflag = TRUE;
			c = *format++;
		}
		switch (c) {
		case 'd':
			log.loginfo[i++] = lflag ?
					(VP_INT) va_arg(ap, long) :
					(VP_INT) va_arg(ap, int);
			break;
		case 'u':
		case 'x':
		case 'X':
			log.loginfo[i++] = lflag ?
					(VP_INT) va_arg(ap, unsigned long) :
					(VP_INT) va_arg(ap, unsigned int);
			break;
		case 'p':
			log.loginfo[i++] = (VP_INT) va_arg(ap, void *);
			break;
		case 'c':
			log.loginfo[i++] = (VP_INT) va_arg(ap, int);
			break;
		case 's':
			log.loginfo[i++] = (VP_INT) va_arg(ap, const char *);
			break;
		case '\0':
			format--;
			break;
		default:
			break;
		}
	}
	va_end(ap);
	return(vwri_log(prio, &log));
}
