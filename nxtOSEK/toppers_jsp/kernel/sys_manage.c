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
 *  @(#) $Id: sys_manage.c,v 1.8 2003/07/01 13:30:35 hiro Exp $
 */

/*
 *	�����ƥ���ִ�����ǽ
 */

#include "jsp_kernel.h"
#include "check.h"
#include "task.h"

/*
 *  ��������ͥ���̤β�ž
 */
#ifdef __rot_rdq

SYSCALL ER
rot_rdq(PRI tskpri)
{
	UINT	pri;
	ER	ercd;

	LOG_ROT_RDQ_ENTER(tskpri);
	CHECK_TSKCTX_UNL();
	CHECK_TPRI_SELF(tskpri);

	t_lock_cpu();
	pri = (tskpri == TPRI_SELF) ? runtsk->priority : INT_PRIORITY(tskpri);
	if (rotate_ready_queue(pri)) {
		dispatch();
	}
	ercd = E_OK;
	t_unlock_cpu();

    exit:
	LOG_ROT_RDQ_LEAVE(ercd);
	return(ercd);
}

#endif /* __rot_rdq */

/*
 *  ��������ͥ���̤β�ž���󥿥�������ƥ������ѡ�
 */
#ifdef __irot_rdq

SYSCALL ER
irot_rdq(PRI tskpri)
{
	ER	ercd;

	LOG_IROT_RDQ_ENTER(tskpri);
	CHECK_INTCTX_UNL();
	CHECK_TPRI(tskpri);

	i_lock_cpu();
	if (rotate_ready_queue(INT_PRIORITY(tskpri))) {
		reqflg = TRUE;
	}
	ercd = E_OK;
	i_unlock_cpu();

    exit:
	LOG_IROT_RDQ_LEAVE(ercd);
	return(ercd);
}

#endif /* __irot_rdq */

/*
 *  �¹Ծ��֤Υ�����ID�λ���
 */
#ifdef __get_tid

SYSCALL ER
get_tid(ID *p_tskid)
{
	ER	ercd;

	LOG_GET_TID_ENTER(p_tskid);
	CHECK_TSKCTX_UNL();

	t_lock_cpu();
	*p_tskid = TSKID(runtsk);
	ercd = E_OK;
	t_unlock_cpu();

    exit:
	LOG_GET_TID_LEAVE(ercd, *p_tskid);
	return(ercd);
}

#endif /* __get_tid */

/*
 *  �¹Ծ��֤Υ�����ID�λ��ȡ��󥿥�������ƥ������ѡ�
 */
#ifdef __iget_tid

SYSCALL ER
iget_tid(ID *p_tskid)
{
	ER	ercd;

	LOG_IGET_TID_ENTER(p_tskid);
	CHECK_INTCTX_UNL();

	i_lock_cpu();
	*p_tskid = (runtsk == NULL) ? TSK_NONE : TSKID(runtsk);
	ercd = E_OK;
	i_unlock_cpu();

    exit:
	LOG_IGET_TID_LEAVE(ercd, *p_tskid);
	return(ercd);
}

#endif /* __iget_tid */

/*
 *  CPU��å����֤ؤΰܹ�
 */
#ifdef __loc_cpu

SYSCALL ER
loc_cpu(void)
{
	ER	ercd;

	LOG_LOC_CPU_ENTER();
	CHECK_TSKCTX();

	if (!(t_sense_lock())) {
		t_lock_cpu();
	}
	ercd = E_OK;

    exit:
	LOG_LOC_CPU_LEAVE(ercd);
	return(ercd);
}

#endif /* __loc_cpu */

/*
 *  CPU��å����֤ؤΰܹԡ��󥿥�������ƥ������ѡ�
 */
#ifdef __iloc_cpu

SYSCALL ER
iloc_cpu(void)
{
	ER	ercd;

	LOG_ILOC_CPU_ENTER();
	CHECK_INTCTX();

	if (!(i_sense_lock())) {
		i_lock_cpu();
	}
	ercd = E_OK;

    exit:
	LOG_ILOC_CPU_LEAVE(ercd);
	return(ercd);
}

#endif /* __iloc_cpu */

/*
 *  CPU��å����֤β��
 *
 *  CPU��å���ϡ��ǥ����ѥå���ɬ�פȤʤ륵���ӥ��������ƤӽФ���
 *  �ȤϤǤ��ʤ����ᡤCPU��å����֤β�����˥ǥ����ѥå����ư����
 *  ɬ�פϤʤ���
 */
#ifdef __unl_cpu

SYSCALL ER
unl_cpu(void)
{
	ER	ercd;

	LOG_UNL_CPU_ENTER();
	CHECK_TSKCTX();

	if (t_sense_lock()) {
		t_unlock_cpu();
	}
	ercd = E_OK;

    exit:
	LOG_UNL_CPU_LEAVE(ercd);
	return(ercd);
}

#endif /* __unl_cpu */

/*
 *  CPU��å����֤β�����󥿥�������ƥ������ѡ�
 *
 *  CPU��å���ϡ��ǥ����ѥå���ɬ�פȤʤ륵���ӥ��������ƤӽФ���
 *  �ȤϤǤ��ʤ����ᡤCPU��å����֤β�����˥ǥ����ѥå���ε�ư����
 *  �᤹��ɬ�פϤʤ���
 */
#ifdef __iunl_cpu

SYSCALL ER
iunl_cpu(void)
{
	ER	ercd;

	LOG_IUNL_CPU_ENTER();
	CHECK_INTCTX();

	if (i_sense_lock()) {
		i_unlock_cpu();
	}
	ercd = E_OK;

    exit:
	LOG_IUNL_CPU_LEAVE(ercd);
	return(ercd);
}

#endif /* __iunl_cpu */

/*
 *  �ǥ����ѥå��ζػ�
 */
#ifdef __dis_dsp

SYSCALL ER
dis_dsp(void)
{
	ER	ercd;

	LOG_DIS_DSP_ENTER();
	CHECK_TSKCTX_UNL();

	t_lock_cpu();
	enadsp = FALSE;
	ercd = E_OK;
	t_unlock_cpu();

    exit:
	LOG_DIS_DSP_LEAVE(ercd);
	return(ercd);
}

#endif /* __dis_dsp */

/*
 *  �ǥ����ѥå��ε���
 */
#ifdef __ena_dsp

SYSCALL ER
ena_dsp(void)
{
	ER	ercd;

	LOG_ENA_DSP_ENTER();
	CHECK_TSKCTX_UNL();

	t_lock_cpu();
	enadsp = TRUE;
	if (runtsk != schedtsk) {
		dispatch();
	}
	ercd = E_OK;
	t_unlock_cpu();

    exit:
	LOG_ENA_DSP_LEAVE(ercd);
	return(ercd);
}

#endif /* __ena_dsp */

/*
 *  ����ƥ����Ȥλ���
 */
#ifdef __sns_ctx

SYSCALL BOOL
sns_ctx(void)
{
	BOOL	state;

	LOG_SNS_CTX_ENTER();
	state = sense_context() ? TRUE : FALSE;
	LOG_SNS_CTX_LEAVE(state);
	return(state);
}

#endif /* __sns_ctx */

/*
 *  CPU��å����֤λ���
 */
#ifdef __sns_loc

SYSCALL BOOL
sns_loc(void)
{
	BOOL	state;

	LOG_SNS_LOC_ENTER();
	state = sense_lock() ? TRUE : FALSE;
	LOG_SNS_LOC_LEAVE(state);
	return(state);
}

#endif /* __sns_loc */

/*
 *  �ǥ����ѥå��ػ߾��֤λ���
 */
#ifdef __sns_dsp

SYSCALL BOOL
sns_dsp(void)
{
	BOOL	state;

	LOG_SNS_DSP_ENTER();
	state = !(enadsp) ? TRUE : FALSE;
	LOG_SNS_DSP_LEAVE(state);
	return(state);
}

#endif /* __sns_dsp */

/*
 *  �ǥ����ѥå���α���֤λ���
 */
#ifdef __sns_dpn

SYSCALL BOOL
sns_dpn(void)
{
	BOOL	state;

	LOG_SNS_DPN_ENTER();
	state = (sense_context() || sense_lock() || !(enadsp)) ? TRUE : FALSE;
	LOG_SNS_DPN_LEAVE(state);
	return(state);
}

#endif /* __sns_dpn */

/*
 *  �����ͥ�ư����֤λ���
 */
#ifdef __vsns_ini

SYSCALL BOOL
vsns_ini(void)
{
	BOOL	state;

	LOG_VSNS_INI_ENTER();
	state = !(iniflg) ? TRUE : FALSE;
	LOG_VSNS_INI_LEAVE(state);
	return(state);
}

#endif /* __vsns_ini */
