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
 *  @(#) $Id: cxxrt.c,v 1.3 2004/09/17 09:11:44 honda Exp $
 */
#include "../kernel/jsp_kernel.h"
#include "../kernel/task.h"
#include "kernel_id.h"

typedef int _toppers_cxxrt_sync_t;
typedef volatile char _toppers_cxxrt_once_t;

static inline int _get_tid()
{
	return runtsk - tcb_table + TMIN_TSKID;
}

/*
 *	For Syncronization
 */
int _toppers_cxxrt_lock(_toppers_cxxrt_sync_t *sync)
{
	if (iniflg)
		dis_dsp();
	return 0;
}

int _toppers_cxxrt_trylock(_toppers_cxxrt_sync_t *sync)
{
	return _toppers_cxxrt_lock(sync);
}

int _toppers_cxxrt_unlock(_toppers_cxxrt_sync_t *sync)
{
	if (iniflg)
		ena_dsp();
	return 0;
}

int _toppers_cxxrt_get_tskid(void)
{
	return iniflg ? _get_tid() : 0;
}

/*
 *	For recursive semaphore lock
 */
static ID cxxrt_holder;
static UINT cxxrt_counter;

static inline void _toppers_cxxrt_recursive_semaphore_lock(ID semid)
{
	if (iniflg && !sns_dsp())
	{
		ID tskid;
		tskid = _get_tid();

		if (cxxrt_holder != tskid)
		{
			wai_sem(semid);
			cxxrt_holder = tskid;
		}
		++cxxrt_counter;
	}
}

static inline void _toppers_cxxrt_recursive_semaphore_unlock(ID semid)
{
	if (iniflg && !sns_dsp())
	{
		if (--cxxrt_counter == 0)
		{
			cxxrt_holder = 0;
			sig_sem(semid);
		}
	}
}


/*
 *	For function call once
 */
int _toppers_cxxrt_once(_toppers_cxxrt_once_t *once, void (*func)(void))
{
	if (!*once)
	{
		static _toppers_cxxrt_sync_t sync;

		_toppers_cxxrt_recursive_semaphore_lock(_CXXRT_SEM);
		if (!*once)
		{
			(*func)();
			*once = 1;
		}
		_toppers_cxxrt_recursive_semaphore_unlock(_CXXRT_SEM);
	}
	return 0;
}


/*
 *	For task-local storage
 */
#ifndef CXXRT_KEY_MAX
#define CXXRT_KEY_MAX	2
#endif

struct _toppers_cxxrt_tls
{
	void **data;
	void (*dtor)(void*);
};

extern const ID tmax_tskid;

static void **tls_data[CXXRT_KEY_MAX];
static struct _toppers_cxxrt_tls tls[CXXRT_KEY_MAX];

int _toppers_cxxrt_key_create(struct _toppers_cxxrt_tls **key, void (*dtor)(void*))
{
	struct _toppers_cxxrt_tls *p;

	for (p = &tls[0]; p < &tls[CXXRT_KEY_MAX]; p++)
	{
		if (p->data == NULL)
		{
			p->data = tls_data[p - &tls[0]];
			p->dtor = dtor;
			*key = p;
			return 0;
		}
	}
	return -1;
}

int _toppers_cxxrt_key_delete(struct _toppers_cxxrt_tls *key)
{
	int i;

	for (i = 0; i <= tmax_tskid; i++)
	{
		if (key->dtor != 0)
			(*key->dtor)(key->data[i]);
	}
	key->data = NULL;
	key->dtor = 0;
	return 0;
}

/* JSP 1.4�Ȥθߴ����Τ����_toppers_cxxrt_reset_specific��Ĥ��Ƥ��� */
void _toppers_cxxrt_reset_specific(void)
{
}

void _toppers_cxxrt_init(void)
{
	int i, tmax = tmax_tskid + 1;
	void **p = (void**)malloc(sizeof(void*) * CXXRT_KEY_MAX * tmax);

	for (i = 0; i < CXXRT_KEY_MAX * tmax; i++)
		p[i] = NULL;
	for (i = 0; i < CXXRT_KEY_MAX; i++)
		tls_data[i] = p + i * tmax;
}

