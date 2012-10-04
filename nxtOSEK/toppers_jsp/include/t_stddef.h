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
 *  @(#) $Id: t_stddef.h,v 1.7 2004/01/05 05:11:37 hiro Exp $
 */

/*
 *	�����ͥ롦���ץꥱ������� ���̥��󥯥롼�ɥե�����
 *
 *  ���Υ��󥯥롼�ɥե�����ϡ�kernel.h �� sil.h ����Ƭ�ǥ��󥯥롼��
 *  ����롥¾�Υե����뤫��ľ�ܥ��󥯥롼�ɤ���뤳�ȤϤʤ���
 *
 *  ������ǥ��󥯥롼�ɤ��Ƥ���ե����������ơ�¾�Υ��󥯥롼�ɥե�
 *  ����˰�¸���Ƥ��ʤ���
 */

#ifndef _T_STDDEF_H_
#define _T_STDDEF_H_

/*
 *  ��ȯ�Ķ��˰�¸�������
 */
#include <tool_defs.h>

/*
 *  ��ȯ�Ķ���ɸ�।�󥯥롼�ɥե������CHAR_BIT �������ɬ�ס�
 *
 *  C++/EC++ �Ǥϡ�ɸ����;�� limits.h �����ݡ��Ȥ���Ƥ���Ȥϸ¤��
 *  �������ۤȤ�ɤν����Ϥǥ��ݡ��Ȥ���Ƥ��롥
 */
#ifndef _MACRO_ONLY
#include <limits.h>
#endif /* _MACRO_ONLY */

/*
 *  ����ѥ���γ�ĥ��ǽ�Τ���Υޥ���Υǥե�������
 */
#ifndef Inline
#define	Inline		static inline
#endif /* Inline */

/*
 *  C����/EC++�� throw() ���н�
 */
#if !defined(__cplusplus) || defined(__embedded_cplusplus)
#define throw()
#endif

/*
 *  assert�ޥ�������
 */
#undef assert
#ifndef NDEBUG
#define assert(exp) \
	((void)(!(exp) ? (_syslog_3(LOG_EMERG, LOG_TYPE_ASSERT,		\
				(VP_INT)(__FILE__), (VP_INT)(__LINE__),	\
				(VP_INT)(#exp)),			\
				kernel_abort(), 0) : 0))
#else /* NDEBUG */
#define	assert(exp)	((void) 0)
#endif /* NDEBUG */

#endif /* _T_STDDEF_H_ */
