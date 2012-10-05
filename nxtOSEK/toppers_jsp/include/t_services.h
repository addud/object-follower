/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2005,2006 by Embedded and Real-Time Systems Laboratory
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
 *  @(#) $Id: t_services.h,v 1.7 2006/01/13 00:34:58 hiro Exp $
 */

/*
 *	���ץꥱ��������� ɸ�।�󥯥롼�ɥե�����
 *
 *  ���Υ��󥯥롼�ɥե�����ϡ������ͥ���ư���ץ����Υ�����
 *  �ե�����ǥ��󥯥롼�ɤ���ɸ�।�󥯥롼�ɥե�����Ǥ��롥������ǡ�
 *  kernel.h�ʤ���ˤ������顤t_stddef.h��itron.h��tool_defs.h��
 *  sys_defs.h��cpu_defs.h��t_syslog.h�ˤ�serial.h�򥤥󥯥롼�ɤ��Ƥ�
 *  �롥�ޤ������ץꥱ��������ͭ�פȻפ�������򤤤��Ĥ��ޤ�Ǥ��롥
 *
 *  ������֥����Υ������ե�����䥷���ƥॳ��ե�����졼�����ե�
 *  ���뤫�餳�Υե�����򥤥󥯥롼�ɤ�����ϡ�_MACRO_ONLY ���������
 *  �������Ȥǡ��ޥ�������ʳ��ε��Ҥ�������Ȥ��Ǥ��롥
 */

#ifndef _T_SERVICES_H_
#define _T_SERVICES_H_

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  �����ͥ��ƤӽФ������ɬ�פʥ��󥯥롼�ɥե�����
 */
#include <kernel.h>

#ifndef _MACRO_ONLY

/*
 *  ���ꥢ�륤�󥿥ե������⥸�塼��
 */
#include <serial.h>

/*
 *  �����ͥ�ν�λ����
 */
extern void	kernel_exit(void) throw();

/*
 *  syscall�ޥ���_syscall �ޥ�������
 */

extern void	t_perror(UINT prio, const char *file, int line,
					const char *expr, ER ercd) throw();

Inline ER
_t_perror(const char *file, int line, const char *expr, ER ercd)
{
	if (ercd < 0) {
		t_perror(LOG_ERROR, file, line, expr, ercd);
	}
	return(ercd);
}

Inline ER
_t_panic(const char *file, int line, const char *expr, ER ercd)
{
	if (ercd < 0) {
		t_perror(LOG_EMERG, file, line, expr, ercd);
		kernel_abort();
	}
	return(ercd);
}

#define syscall(s)	_t_perror(__FILE__, __LINE__, #s, (s))
#define _syscall(s)	_t_panic(__FILE__, __LINE__, #s, (s))

#endif /* _MACRO_ONLY */

#ifdef __cplusplus
}
#endif

#endif /* _T_SERVICES_H_ */
