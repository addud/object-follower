/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2003 by Embedded and Real-Time Systems Laboratory
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
 *  @(#) $Id: kernel_cfg.h,v 1.5 2003/12/06 13:09:46 hiro Exp $
 */

/*
 *	kernel_cfg.c �ѥ��󥯥롼�ɥե�����
 */

#ifndef _KERNEL_CFG_H_
#define _KERNEL_CFG_H_

/*
 *  �����ͥ�ɸ�।�󥯥롼�ɥե�����
 */
#include <../kernel/jsp_kernel.h>

/*
 *  �����ͥ�γƥ��󥯥롼�ɥե�����
 */
#include <../kernel/task.h>
#include <../kernel/semaphore.h>
#include <../kernel/eventflag.h>
#include <../kernel/dataqueue.h>
#include <../kernel/mailbox.h>
#include <../kernel/mempfix.h>
#include <../kernel/cyclic.h>
#include <../kernel/interrupt.h>
#include <../kernel/exception.h>
#include <../kernel/time_event.h>

/*
 *  �����ͥ�Υ�����ꥢ��������뤿��Υǡ�����
 *
 *  �����å��ΰ�ȸ���Ĺ����ס����ΰ��VP���Υ����������礭��ñ
 *  �̤ǥ��饤�󤵤���ɬ�פ�������ˤϡ�__STK_UNIT ��__MPF_UNIT ��
 *  ���줾�쥢�饤�󤵤���ñ�̤Υǡ�������������롥
 *
 *  �ʲ�������ϡ�__STK_UNIT ����� __MPF_UNIT �Υ������� 2�ζҾ�Ǥ�
 *  �뤳�Ȥ��ꤷ�Ƥ��롥
 */

#ifndef __STK_UNIT
typedef VP	__STK_UNIT;
#endif /* __STK_UNIT */

#ifndef __MPF_UNIT
typedef VP	__MPF_UNIT;
#endif /* __MPF_UNIT */

#define __TROUND_STK_UNIT(sz) \
		(((sz) + sizeof(__STK_UNIT) - 1) & ~(sizeof(__STK_UNIT) - 1))
#define __TCOUNT_STK_UNIT(sz) \
		(((sz) + sizeof(__STK_UNIT) - 1) / sizeof(__STK_UNIT))

#define __TROUND_MPF_UNIT(sz) \
		(((sz) + sizeof(__MPF_UNIT) - 1) & ~(sizeof(__MPF_UNIT) - 1))
#define __TCOUNT_MPF_UNIT(sz) \
		(((sz) + sizeof(__MPF_UNIT) - 1) / sizeof(__MPF_UNIT))

/*
 *  ��͡��ष������ܥ�򸵤��᤹����Υ��󥯥롼�ɥե�����
 */
#include <../kernel/jsp_unrename.h>
#include <sys_unrename.h>
#include <cpu_unrename.h>

#endif /* _KERNEL_CFG_H_ */
