/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2004 by Embedded and Real-Time Systems Laboratory
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
 *  @(#) $Id: t_syslog.h,v 1.4 2004/01/05 05:15:01 hiro Exp $
 */

/*
 *	�����ƥ����ǽ
 *
 *  �����ƥ�������ӥ��ϡ������ƥ�Υ��������Ϥ��뤿��Υ����ӥ�
 *  �Ǥ��롥�����ͥ뤫��Υ�����ν��Ϥˤ��Ѥ��뤿�ᡤ�������Ԥ�����
 *  �ˤϤ��뤳�ȤϤʤ���
 *
 *  ������ϡ������ͥ���Υ��Хåե��˽񤭹��फ�����٥��ʸ����
 *  �ϴؿ����Ѥ��ƽ��Ϥ��롥�ɤ����Ȥ����ϡ���ĥ�����ӥ���������ڤ�
 *  �����뤳�Ȥ��Ǥ��롥
 *
 *  ���Хåե��ΰ褬�����Хե��������ˤϡ��Ť��������ä��ƾ�
 *  �񤭤��롥
 *
 *  ������֥����Υ������ե�����䥷���ƥॳ��ե�����졼�����ե�
 *  ���뤫�餳�Υե�����򥤥󥯥롼�ɤ�����ϡ�_MACRO_ONLY ���������
 *  �������Ȥǡ��ޥ�������ʳ��ε��Ҥ�������Ȥ��Ǥ��롥
 *
 *  ���Υ��󥯥롼�ɥե�����ϡ�kernel.h �� sil.h �ǥ��󥯥롼�ɤ���롥
 *  ¾�Υե����뤫��ľ�ܥ��󥯥롼�ɤ���뤳�ȤϤʤ���
 *
 *  ���Υե�����򥤥󥯥롼�ɤ������ˡ�t_stddef.h �� itron.h �򥤥�
 *  �롼�ɤ��Ƥ������Ȥ�ɬ�פǤ��롥
 */

#ifndef _T_SYSLOG_H_
#define _T_SYSLOG_H_

/*
 *  ������μ��̤����
 *
 *  LOG_TYPE_CYC��LOG_TYPE_ASSERT �ʳ��ϡ��ǥХå��󥰥��󥿥ե�������
 *  �ͤȹ��פ��Ƥ��롥
 */
#define LOG_TYPE_INH		0x01u	/* ����ߥϥ�ɥ� */
#define LOG_TYPE_ISR		0x02u	/* ����ߥ����ӥ��롼���� */
#define LOG_TYPE_CYC		0x03u	/* �����ϥ�ɥ� */
#define LOG_TYPE_EXC		0x04u	/* CPU�㳰�ϥ�ɥ� */
#define LOG_TYPE_TEX		0x05u	/* �������㳰�����롼���� */
#define LOG_TYPE_TSKSTAT	0x06u	/* �����������Ѳ� */
#define LOG_TYPE_DSP		0x07u	/* �ǥ����ѥå��� */
#define LOG_TYPE_SVC		0x08u	/* �����ӥ������� */
#define LOG_TYPE_COMMENT	0x09u	/* ������ */
#define LOG_TYPE_ASSERT		0x0au	/* �����������μ��� */

#define LOG_ENTER		0x00u	/* ���������� */
#define LOG_LEAVE		0x80u	/* �и�����λ */

/*
 *  ������ν����٤����
 */
#define LOG_EMERG	0u		/* ����åȥ�������ͤ��륨�顼 */
#define LOG_ALERT	1u
#define LOG_CRIT	2u
#define LOG_ERROR	3u		/* �����ƥ२�顼 */
#define LOG_WARNING	4u		/* �ٹ��å����� */
#define LOG_NOTICE	5u
#define LOG_INFO	6u
#define LOG_DEBUG	7u		/* �ǥХå��ѥ�å����� */

#ifndef _MACRO_ONLY

/*
 *  ������Υǡ�����¤
 */

#define TMAX_LOGINFO	6

typedef struct {
		UINT	logtype;		/* ������μ��� */
		SYSTIM	logtim;			/* ������ */
		VP_INT	loginfo[TMAX_LOGINFO];	/* ����¾�Υ����� */
	} SYSLOG;

/*
 *  ������ν����٤Υӥåȥޥåפ��뤿��Υޥ���
 */
#define LOG_MASK(prio)	(1u << (prio))
#define LOG_UPTO(prio)	((1u << ((prio) + 1)) - 1)

#ifndef OMIT_SYSLOG

/*
 *  ������ν���
 */
extern ER	vwri_log(UINT prio, SYSLOG *p_log) throw();

/*
 *  ���Хåե�����Υ�������ɽФ�
 */
extern ER_UINT	vrea_log(SYSLOG *p_log) throw();

/* 
 *  ���Ϥ��٤�������ν����٤�����
 */
extern ER	vmsk_log(UINT logmask, UINT lowmask) throw();

/*
 *  ���������Ϥ��뤿��Υ饤�֥��ؿ�
 */

Inline ER
_syslog_0(UINT prio, UINT type)
{
	SYSLOG	log;

	log.logtype = type;
	return(vwri_log(prio, &log));
}

Inline ER
_syslog_1(UINT prio, UINT type, VP_INT arg1)
{
	SYSLOG	log;

	log.logtype = type;
	log.loginfo[0] = arg1;
	return(vwri_log(prio, &log));
}

Inline ER
_syslog_2(UINT prio, UINT type, VP_INT arg1, VP_INT arg2)
{
	SYSLOG	log;

	log.logtype = type;
	log.loginfo[0] = arg1;
	log.loginfo[1] = arg2;
	return(vwri_log(prio, &log));
}

Inline ER
_syslog_3(UINT prio, UINT type, VP_INT arg1, VP_INT arg2, VP_INT arg3)
{
	SYSLOG	log;

	log.logtype = type;
	log.loginfo[0] = arg1;
	log.loginfo[1] = arg2;
	log.loginfo[2] = arg3;
	return(vwri_log(prio, &log));
}

Inline ER
_syslog_4(UINT prio, UINT type, VP_INT arg1, VP_INT arg2,
				VP_INT arg3, VP_INT arg4)
{
	SYSLOG	log;

	log.logtype = type;
	log.loginfo[0] = arg1;
	log.loginfo[1] = arg2;
	log.loginfo[2] = arg3;
	log.loginfo[3] = arg4;
	return(vwri_log(prio, &log));
}

Inline ER
_syslog_5(UINT prio, UINT type, VP_INT arg1, VP_INT arg2,
				VP_INT arg3, VP_INT arg4, VP_INT arg5)
{
	SYSLOG	log;

	log.logtype = type;
	log.loginfo[0] = arg1;
	log.loginfo[1] = arg2;
	log.loginfo[2] = arg3;
	log.loginfo[3] = arg4;
	log.loginfo[4] = arg5;
	return(vwri_log(prio, &log));
}

Inline ER
_syslog_6(UINT prio, UINT type, VP_INT arg1, VP_INT arg2, VP_INT arg3,
				VP_INT arg4, VP_INT arg5, VP_INT arg6)
{
	SYSLOG	log;

	log.logtype = type;
	log.loginfo[0] = arg1;
	log.loginfo[1] = arg2;
	log.loginfo[2] = arg3;
	log.loginfo[3] = arg4;
	log.loginfo[4] = arg5;
	log.loginfo[5] = arg6;
	return(vwri_log(prio, &log));
}

#else /* OMIT_SYSLOG */

#define vwri_log(prio, p_log)		E_OK
#define vrea_log(p_log)			E_OK
#define vmsk_log(logmask, lowmask)	E_OK

#define _syslog_0(prio, type)						E_OK
#define _syslog_1(prio, type, arg1)					E_OK
#define _syslog_2(prio, type, arg1, arg2)				E_OK
#define _syslog_3(prio, type, arg1, arg2, arg3)				E_OK
#define _syslog_4(prio, type, arg1, arg2, arg3, arg4)			E_OK
#define _syslog_5(prio, type, arg1, arg2, arg3, arg4, arg5)		E_OK
#define _syslog_6(prio, type, arg1, arg2, arg3, arg4, arg5, arg6)	E_OK

#endif /* OMIT_SYSLOG */

/*
 *  ������ʥ����ȡˤ���Ϥ��뤿��Υޥ���
 *
 *  format ����Ӹ�³�ΰ����������������å������򡤽����� prio ��
 *  ������Ȥ��ƽ��Ϥ��뤿��Υޥ���arg1��argn �� VP_INT���˥���
 *  ���Ȥ��뤿�ᡤVP_INT���˷��Ѵ��Ǥ���Ǥ�դη��Ǥ褤��
 */

#define	syslog_0(prio, format) \
		_syslog_1(prio, LOG_TYPE_COMMENT, (VP_INT) format)

#define	syslog_1(prio, format, arg1) \
		_syslog_2(prio, LOG_TYPE_COMMENT, (VP_INT) format, \
							(VP_INT)(arg1))

#define	syslog_2(prio, format, arg1, arg2) \
		_syslog_3(prio, LOG_TYPE_COMMENT, (VP_INT) format, \
					(VP_INT)(arg1), (VP_INT)(arg2))

#define	syslog_3(prio, format, arg1, arg2, arg3) \
		_syslog_4(prio, LOG_TYPE_COMMENT, (VP_INT) format, \
			(VP_INT)(arg1), (VP_INT)(arg2), (VP_INT)(arg3))

#define	syslog_4(prio, format, arg1, arg2, arg3, arg4) \
		_syslog_5(prio, LOG_TYPE_COMMENT, (VP_INT) format, \
			(VP_INT)(arg1), (VP_INT)(arg2), (VP_INT)(arg3), \
							(VP_INT)(arg4))

#define	syslog_5(prio, format, arg1, arg2, arg3, arg4, arg5) \
		_syslog_6(prio, LOG_TYPE_COMMENT, (VP_INT) format, \
			(VP_INT)(arg1), (VP_INT)(arg2), (VP_INT)(arg3), \
					(VP_INT)(arg4), (VP_INT)(arg5))

/*
 *  ������ʥ����ȡˤ���Ϥ��뤿��Υ饤�֥��ؿ���vasyslog.c��
 */
extern ER	syslog(UINT prio, const char *format, ...) throw();

/* 
 *  ������Υե����ޥåȽ��ϡ�log_output.c��
 */
extern void	syslog_printf(const char *format, VP_INT *args,
						void (*putc)(char)) throw();
extern void	syslog_print(SYSLOG *p_log, void (*putc)(char)) throw();
extern void	syslog_output(void (*putc)(char)) throw();

#endif /* _MACRO_ONLY */
#endif /* _T_SYSLOG_H_ */
