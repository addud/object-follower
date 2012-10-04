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
 *  @(#) $Id: log_output.c,v 1.11 2007/03/27 08:56:12 hiro Exp $
 */

/*
 *	�����ƥ���Υե����ޥåȽ���
 */

#include <t_services.h>

/*
 *  �ݥ��󥿤��Ǽ�Ǥ����������Υǥե���Ȥ����
 */
#ifndef _intptr_
#define _intptr_	long
#endif /* _intptr_ */

/*
 *  ���ͤ�ʸ������Ѵ�
 */
#define CONVERT_BUFLEN	((sizeof(_intptr_) * CHAR_BIT + 2) / 3)
					/* _intptr_���ο��ͤκ���ʸ���� */
static void
convert(unsigned _intptr_ val, unsigned int radix, const char *radchar,
		int width, int minus, int padzero, void (*putc)(char))
{
	char	buf[CONVERT_BUFLEN];
	int	i, j;

	i = 0;
	do {
		buf[i++] = radchar[val % radix];
		val /= radix;
	} while (val != 0);

	width -= minus;
	if (minus > 0 && padzero > 0) {
		(*putc)('-');
	}
	for (j = i; j < width; j++) {
		(*putc)((char)(padzero > 0 ? '0' : ' '));
	}
	if (minus > 0 && padzero <= 0) {
		(*putc)('-');
	}
	while (i > 0) {
		(*putc)(buf[--i]);
	}
}

/*
 *  ������Υե����ޥåȽ���
 */
static const char raddec[] = "0123456789";
static const char radhex[] = "0123456789abcdef";
static const char radHEX[] = "0123456789ABCDEF";

void
syslog_printf(const char *format, VP_INT *args, void (*putc)(char))
{
	int		c;
	int		width;
	int		padzero;
	_intptr_	val;
	const char	*str;

	while ((c = *format++) != '\0') {
		if (c != '%') {
			(*putc)((char) c);
			continue;
		}

		width = padzero = 0;
		if ((c = *format++) == '0') {
			padzero = 1;
			c = *format++;
		}
		while ('0' <= c && c <= '9') {
			width = width * 10 + c - '0';
			c = *format++;
		}
		if (c == 'l') {
			c = *format++;
		}
		switch (c) {
		case 'd':
			val = (_intptr_)(*args++);
			if (val >= 0) {
				convert((unsigned _intptr_) val, 10, raddec,
						width, 0, padzero, putc);
			}
			else {
				convert((unsigned _intptr_)(-val), 10, raddec,
						width, 1, padzero, putc);
			}
			break;
		case 'u':
			val = (_intptr_)(*args++);
			convert((unsigned _intptr_) val, 10, raddec,
						width, 0, padzero, putc);
			break;
		case 'x':
		case 'p':
			val = (_intptr_)(*args++);
			convert((unsigned _intptr_) val, 16, radhex,
						width, 0, padzero, putc);
			break;
		case 'X':
			val = (_intptr_)(*args++);
			convert((unsigned _intptr_) val, 16, radHEX,
						width, 0, padzero, putc);
			break;
		case 'c':
			(*putc)((char)(_intptr_)(*args++));
			break;
		case 's':
			str = (const char *)(*args++);
			while ((c = *str++) != '\0') {
				(*putc)((char) c);
			}
			break;
		case '%':
			(*putc)('%');
			break;
		case '\0':
			format--;
			break;
		default:
			break;
		}
	}
	(*putc)('\n');
}

void
syslog_print(SYSLOG *p_log, void (*putc)(char))
{
	switch (p_log->logtype) {
	case LOG_TYPE_COMMENT:
		syslog_printf((const char *)(p_log->loginfo[0]),
					&(p_log->loginfo[1]), putc);
		break;
	case LOG_TYPE_ASSERT:
		syslog_printf("%s:%u: Assertion `%s' failed.",
					&(p_log->loginfo[0]), putc);
		break;
	}
}

static void
syslog_lostmsg(INT lost, void (*putc)(char))
{
	VP_INT	lostinfo[1];

	lostinfo[0] = (VP_INT) lost;
	syslog_printf("%d messages are lost.", lostinfo, putc);
}

void
syslog_output(void (*putc)(char))
{
	SYSLOG	log;
	INT	lostnum, n;

	lostnum = 0;
	while ((n = vrea_log(&log)) >= 0) {
		lostnum += n;
		if (log.logtype < LOG_TYPE_COMMENT) {
			continue;
		}
		if (lostnum > 0) {
			syslog_lostmsg(lostnum, putc);
			lostnum = 0;
		}
		syslog_print(&log, putc);
	}
	if (lostnum > 0) {
		syslog_lostmsg(lostnum, putc);
	}
}
