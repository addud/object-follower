/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2003-2004 by Takagi Nobuhisa
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
 *  @(#) $Id: newlibrt.c,v 1.2 2004/09/17 09:11:44 honda Exp $
 */
#include <stddef.h>
#include <reent.h>
#include <errno.h>
#include "../kernel/jsp_kernel.h"

#ifndef	HEAP_TOP
#define	HEAP_TOP		~0UL
#endif

/*
 *	For malloc (Newlib)
 */
static int cxxrt_dis_dsp;

void __malloc_lock(struct _reent *ptr)
{
	if (!iniflg || sns_dsp())
		return;
	dis_dsp();
	cxxrt_dis_dsp = 1;
}

void __malloc_unlock(struct _reent *ptr)
{
	if (!cxxrt_dis_dsp)
		return;
	cxxrt_dis_dsp = 0;
	ena_dsp();
}

void *_sbrk_r(struct _reent *ptr, ptrdiff_t nbyte)
{
	extern char end;
	static char *heap_ptr = &end;
	static char *heap_end = (char*)HEAP_TOP;
	char *base;

	if (!iniflg)
	{
		volatile char _auto;
		if (&end < &_auto && &_auto < heap_end)
			heap_end = (char*)&_auto;
	}

	if (heap_ptr + nbyte + 32 > heap_end)
	{
		ptr->_errno = errno = ENOMEM;
		return (void*)-1;
	}

	base = heap_ptr;
	heap_ptr += nbyte;
	return base;
}

/*
 *	For program termination
 */
#define	ATEXIT_MAX	(32 + 1)

static void (*atexit_table[ATEXIT_MAX])(void);
static int atexit_num;

/*
 * abort���˺ǽ�˸ƽФ����եå�
 * raise(SIGABRT)��ƽФ��褦�ˤ���С��ۥ��ȴĶ��Ȥθߴ���Ȥ뤳�Ȥ���ǽ�ˤʤ롣
 */
void (*_atabort)(void) = 0;

int atexit(void (*func)(void))
{
	int result = -1;
	int sync = iniflg;

	if (sync)
		loc_cpu();

	if (atexit_num < ATEXIT_MAX)
	{
		atexit_table[atexit_num++] = func;
		result = 0;
	}

	if (sync)
		unl_cpu();

	return result;
}

void exit(int status)
{
	if (iniflg)
		kernel_exit();
	_exit(status);
}

void abort(void)
{
	if (_atabort != 0)
		(*_atabort)();
	if (iniflg)
		kernel_abort();
	_exit(3);
}

/*
 *	For software hooks
 */
void software_init_hook(void)
{
	extern void _toppers_cxxrt_init(void);
	_toppers_cxxrt_init();
	{
#ifdef	__ELF__
		extern void _init(void);
		extern void _fini(void);
		atexit(_fini);
		_init();
#else
		extern void __main(void);
		__main();
#endif
	}
}

void software_term_hook(void)
{
	int i;

	for (i = atexit_num - 1; i >= 0; i--)
		(*atexit_table[i])();
}

/* ��󥯲���ѤΥ��ߡ� */
int main() { return 0; }

