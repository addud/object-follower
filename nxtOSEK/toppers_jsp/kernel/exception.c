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
 *  @(#) $Id: exception.c,v 1.9 2003/06/04 01:46:16 hiro Exp $
 */

/*
 *	CPU�㳰������ǽ
 */

#include "jsp_kernel.h"
#include "task.h"
#include "exception.h"

/*
 *  CPU�㳰�ϥ�ɥ��ֹ�ο���kernel_cfg.c��
 */
extern const UINT	tnum_excno;

/*
 *  CPU�㳰�ϥ�ɥ������֥�å��Υ��ꥢ��kernel_cfg.c��
 */
extern const EXCINIB	excinib_table[];

/* 
 *  CPU�㳰�ϥ�ɥ������ǽ�ν����
 */
#ifdef __excini

void
exception_initialize()
{
	UINT		i;
	const EXCINIB	*excinib;

	for (excinib = excinib_table, i = 0; i < tnum_excno; excinib++, i++) {
		define_exc(excinib->excno, excinib->exchdr);
	}
}

#endif /* __excini */

/*
 *  CPU�㳰��ȯ����������ƥ����Ȥλ���
 */
#ifdef __vxsns_ctx

SYSCALL BOOL
vxsns_ctx(VP p_excinf)
{
	BOOL	state;

	LOG_VXSNS_CTX_ENTER(p_excinf);
	state = exc_sense_context(p_excinf) ? TRUE : FALSE;
	LOG_VXSNS_CTX_LEAVE(state);
	return(state);
}

#endif /* __vxsns_ctx */

/*
 *  CPU�㳰��ȯ����������CPU��å����֤λ���
 */
#ifdef __vxsns_loc

SYSCALL BOOL
vxsns_loc(VP p_excinf)
{
	BOOL	state;

	LOG_VXSNS_LOC_ENTER(p_excinf);
	state = exc_sense_lock(p_excinf) ? TRUE : FALSE;
	LOG_VXSNS_LOC_LEAVE(state);
	return(state);
}

#endif /* __vxsns_loc */

/*
 *  CPU�㳰��ȯ���������Υǥ����ѥå��ػ߾��֤λ���
 *
 *  sns_dsp ��Ʊ��ν������ƤȤʤ롥
 */
#ifdef __vxsns_dsp

SYSCALL BOOL
vxsns_dsp(VP p_excinf)
{
	BOOL	state;

	LOG_VXSNS_DSP_ENTER(p_excinf);
	state = !(enadsp) ? TRUE : FALSE;
	LOG_VXSNS_DSP_LEAVE(state);
	return(state);
}

#endif /* __vxsns_dsp */

/*
 *  CPU�㳰��ȯ���������Υǥ����ѥå���α���֤λ���
 */
#ifdef __vxsns_dpn

SYSCALL BOOL
vxsns_dpn(VP p_excinf)
{
	BOOL	state;

	LOG_VXSNS_DPN_ENTER(p_excinf);
	state = (exc_sense_context(p_excinf) || exc_sense_lock(p_excinf)
					|| !(enadsp)) ? TRUE : FALSE;
	LOG_VXSNS_DPN_LEAVE(state);
	return(state);
}

#endif /* __vxsns_dpn */

/*
 *  CPU�㳰��ȯ���������Υ������㳰�����ػ߾��֤λ���
 *
 *  sns_tex ��Ʊ��ν������ƤȤʤ롥
 */
#ifdef __vxsns_tex

SYSCALL BOOL
vxsns_tex(VP p_excinf)
{
	BOOL	state;

	LOG_VXSNS_TEX_ENTER(p_excinf);
	state = (runtsk != NULL && runtsk->enatex) ? FALSE : TRUE;
	LOG_VXSNS_TEX_LEAVE(state);
	return(state);
}

#endif /* __vxsns_tex */
