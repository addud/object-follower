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
 *  @(#) $Id: kernel.h,v 1.22 2007/05/08 07:33:51 honda Exp $
 */

/*
 *	��ITRON4.0����ɸ�।�󥯥롼�ɥե�����
 *
 *  ���Υե�����Ǥϡ�����������ɥץ�ե������ɬ�פʤ�Τȡ�JSP����
 *  �ͥ��ȼ��γ�ĥ��ǽ��ɬ�פʤ�Τ�����������Ƥ��롥�ǡ�����������ϡ�
 *  ����������ɥץ�ե���������������礦�ɤ�Ĺ���ˤϤ��Ƥ��ʤ���
 *
 *  ������֥����Υ������ե�����䥷���ƥॳ��ե�����졼�����ե�
 *  ���뤫�餳�Υե�����򥤥󥯥롼�ɤ�����ϡ�_MACRO_ONLY ���������
 *  �������Ȥǡ��ޥ�������ʳ��ε��Ҥ�������Ȥ��Ǥ��롥
 *
 *  ���Υ��󥯥롼�ɥե�����ϡ�ɸ�।�󥯥롼�ɥե������t_services.h 
 *  �� jsp_kernel.h�ˤǥ��󥯥롼�ɤ���롥�ޤ���¾�� ITRON����OS ����
 *  ���եȥ�������ݡ��ƥ��󥰤�����ʤɤˤϡ����Υե������ľ�ܥ���
 *  ���롼�ɤ��Ƥ�褤�������㳰������ơ�¾�Υե����뤫��ľ�ܥ��󥯥롼
 *  �ɤ���뤳�ȤϤʤ���
 *
 *  ������ǥ��󥯥롼�ɤ��Ƥ���ե����������ơ�¾�Υ��󥯥롼�ɥե�
 *  ����˰�¸���Ƥ��ʤ���
 */

#ifndef _KERNEL_H_
#define _KERNEL_H_

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  �����ͥ롦���ץꥱ������� ���̥��󥯥롼�ɥե�����
 */
#include <t_stddef.h>

/*
 *  ITRON���Ͷ��̵���Υǡ�������������ޥ���
 */
#include <itron.h>

/*
 *  �����ƥ��ץ��å��˰�¸�������
 */
#include <sys_defs.h>
#include <cpu_defs.h>

/*
 *  �����ƥ�������ӥ��Τ�������
 */
#include <t_syslog.h>

/*
 *  ����ޥ���
 */
#define	TROUND_VP(sz)	(((sz) + sizeof(VP) - 1) & ~(sizeof(VP) - 1))
#define	TCOUNT_VP(sz)	(((sz) + sizeof(VP) - 1) / sizeof(VP))

/*
 *  �ǡ����������
 */
#ifndef _MACRO_ONLY

typedef	UINT		TEXPTN;		/* �������㳰�װ��Υӥåȥѥ����� */
typedef	UINT		FLGPTN;		/* ���٥�ȥե饰�Υӥåȥѥ����� */

typedef	struct t_msg {			/* �᡼��ܥå����Υ�å������إå� */
	struct t_msg	*next;
} T_MSG;

typedef	struct t_msg_pri {		/* ͥ�����դ���å������إå� */
	T_MSG		msgque;		/* ��å������إå� */
	PRI		msgpri;		/* ��å�����ͥ���� */
} T_MSG_PRI;

#endif /* _MACRO_ONLY */

/*
 *  �����ӥ�����������
 */
#ifndef _MACRO_ONLY

/*
 *  ������������ǽ
 */
extern ER	act_tsk(ID tskid) throw();
extern ER	iact_tsk(ID tskid) throw();
extern ER_UINT	can_act(ID tskid) throw();
extern void	ext_tsk(void) throw();
extern ER	ter_tsk(ID tskid) throw();
extern ER	chg_pri(ID tskid, PRI tskpri) throw();
extern ER	get_pri(ID tskid, PRI *p_tskpri) throw();

/*
 *  ��������°Ʊ����ǽ
 */
extern ER	slp_tsk(void) throw();
extern ER	tslp_tsk(TMO tmout) throw();
extern ER	wup_tsk(ID tskid) throw();
extern ER	iwup_tsk(ID tskid) throw();
extern ER_UINT	can_wup(ID tskid) throw();
extern ER	rel_wai(ID tskid) throw();
extern ER	irel_wai(ID tskid) throw();
extern ER	sus_tsk(ID tskid) throw();
extern ER	rsm_tsk(ID tskid) throw();
extern ER	frsm_tsk(ID tskid) throw();
extern ER	dly_tsk(RELTIM dlytim) throw();

/*
 *  �������㳰������ǽ
 */
extern ER	ras_tex(ID tskid, TEXPTN rasptn) throw();
extern ER	iras_tex(ID tskid, TEXPTN rasptn) throw();
extern ER	dis_tex(void) throw();
extern ER	ena_tex(void) throw();
extern BOOL	sns_tex(void) throw();

/*
 *  Ʊ�����̿���ǽ
 */
extern ER	sig_sem(ID semid) throw();
extern ER	isig_sem(ID semid) throw();
extern ER	wai_sem(ID semid) throw();
extern ER	pol_sem(ID semid) throw();
extern ER	twai_sem(ID semid, TMO tmout) throw();

extern ER	set_flg(ID flgid, FLGPTN setptn) throw();
extern ER	iset_flg(ID flgid, FLGPTN setptn) throw();
extern ER	clr_flg(ID flgid, FLGPTN clrptn) throw();
extern ER	wai_flg(ID flgid, FLGPTN waiptn,
			MODE wfmode, FLGPTN *p_flgptn) throw();
extern ER	pol_flg(ID flgid, FLGPTN waiptn,
			MODE wfmode, FLGPTN *p_flgptn) throw();
extern ER	twai_flg(ID flgid, FLGPTN waiptn,
			MODE wfmode, FLGPTN *p_flgptn, TMO tmout) throw();

extern ER	snd_dtq(ID dtqid, VP_INT data) throw();
extern ER	psnd_dtq(ID dtqid, VP_INT data) throw();
extern ER	ipsnd_dtq(ID dtqid, VP_INT data) throw();
extern ER	tsnd_dtq(ID dtqid, VP_INT data, TMO tmout) throw();
extern ER	fsnd_dtq(ID dtqid, VP_INT data) throw();
extern ER	ifsnd_dtq(ID dtqid, VP_INT data) throw();
extern ER	rcv_dtq(ID dtqid, VP_INT *p_data) throw();
extern ER	prcv_dtq(ID dtqid, VP_INT *p_data) throw();
extern ER	trcv_dtq(ID dtqid, VP_INT *p_data, TMO tmout) throw();

extern ER	snd_mbx(ID mbxid, T_MSG *pk_msg) throw();
extern ER	rcv_mbx(ID mbxid, T_MSG **ppk_msg) throw();
extern ER	prcv_mbx(ID mbxid, T_MSG **ppk_msg) throw();
extern ER	trcv_mbx(ID mbxid, T_MSG **ppk_msg, TMO tmout) throw();

/*
 *  ����ס��������ǽ
 */
extern ER	get_mpf(ID mpfid, VP *p_blk) throw();
extern ER	pget_mpf(ID mpfid, VP *p_blk) throw();
extern ER	tget_mpf(ID mpfid, VP *p_blk, TMO tmout) throw();
extern ER	rel_mpf(ID mpfid, VP blk) throw();

/*
 *  ���ִ�����ǽ
 */
extern ER	set_tim(const SYSTIM *p_systim) throw();
extern ER	get_tim(SYSTIM *p_systim) throw();
extern ER	isig_tim(void) throw();

extern ER	sta_cyc(ID cycid) throw();
extern ER	stp_cyc(ID cycid) throw();

/*
 *  �����ƥ���ִ�����ǽ
 */
extern ER	rot_rdq(PRI tskpri) throw();
extern ER	irot_rdq(PRI tskpri) throw();
extern ER	get_tid(ID *p_tskid) throw();
extern ER	iget_tid(ID *p_tskid) throw();
extern ER	loc_cpu(void) throw();
extern ER	iloc_cpu(void) throw();
extern ER	unl_cpu(void) throw();
extern ER	iunl_cpu(void) throw();
extern ER	dis_dsp(void) throw();
extern ER	ena_dsp(void) throw();
extern BOOL	sns_ctx(void) throw();
extern BOOL	sns_loc(void) throw();
extern BOOL	sns_dsp(void) throw();
extern BOOL	sns_dpn(void) throw();

/*
 *  �����ȼ������ӥ�������
 */
extern BOOL	vxsns_ctx(VP p_excinf) throw();
extern BOOL	vxsns_loc(VP p_excinf) throw();
extern BOOL	vxsns_dsp(VP p_excinf) throw();
extern BOOL	vxsns_dpn(VP p_excinf) throw();
extern BOOL	vxsns_tex(VP p_excinf) throw();
extern BOOL	vsns_ini(void) throw();

#endif /* _MACRO_ONLY */

/*
 *  ���֥�������°�������
 */
#define TA_HLNG		0x00u		/* �������ѥ��󥿥ե����� */
#define TA_ASM		0x01u		/* ������֥�����ѥ��󥿥ե����� */

#define TA_TFIFO	0x00u		/* ���������Ԥ������FIFO��� */
#define TA_TPRI		0x01u		/* ���������Ԥ������ͥ���ٽ�� */

#define TA_MFIFO	0x00u		/* ��å��������塼��FIFO��� */
#define TA_MPRI		0x02u		/* ��å��������塼��ͥ���ٽ�� */

#define TA_ACT		0x02u		/* ��������ư���줿���֤����� */

#define TA_WSGL		0x00u		/* ���٥�ȥե饰���Ԥ���������1�Ĥ� */
#define TA_CLR		0x04u		/* ���٥�ȥե饰�Υ��ꥢ���� */

#define	TA_STA		0x02u		/* �����ϥ�ɥ��ư����֤����� */

/*
 *  �����ӥ��������ư��⡼�ɤ����
 */
#define	TWF_ANDW	0x00u		/* ���٥�ȥե饰��AND�Ԥ� */
#define	TWF_ORW		0x01u		/* ���٥�ȥե饰��OR�Ԥ� */

/*
 *  ����¾����������
 */
#define	TSK_SELF	0		/* ������������ */
#define	TSK_NONE	0		/* �������륿�������ʤ� */
#define	TPRI_SELF	0		/* ���������Υ١���ͥ���٤λ��� */
#define	TPRI_INI	0		/* �������ε�ư��ͥ���٤λ��� */

/*
 *  ��������ȥޥ���
 */

/*
 *  ͥ���٤��ϰ�
 */
#define	TMIN_TPRI	1		/* ������ͥ���٤κǾ��� */
#define	TMAX_TPRI	16		/* ������ͥ���٤κ����� */
#define	TMIN_MPRI	1		/* ��å�����ͥ���٤κǾ��� */
#define	TMAX_MPRI	16		/* ��å�����ͥ���٤κ����� */

/*
 *  �С���������
 */
#define	TKERNEL_MAKER	0x0118u		/* �����ͥ�Υ᡼���������� */
#define	TKERNEL_PRID	0x0001u		/* �����ͥ�μ����ֹ� */
#define	TKERNEL_SPVER	0x5402u		/* ITRON���ͤΥС�������ֹ� */
#define	TKERNEL_PRVER	0x1043u		/* �����ͥ�ΥС�������ֹ� */

/*
 *  ���塼���󥰡��ͥ��Ȳ���κ�����
 */
#define	TMAX_ACTCNT	1		/* ��ư�׵ᥭ�塼���󥰿��κ����� */
#define	TMAX_WUPCNT	1		/* �����׵ᥭ�塼���󥰿��κ����� */
#define	TMAX_SUSCNT	1		/* �����Ԥ��׵�ͥ��ȿ��κ����� */

/*
 *  �ӥåȥѥ�����Υӥåȿ�
 */
#define	TBIT_TEXPTN	(sizeof(TEXPTN) * CHAR_BIT)
					/* �������㳰�װ��Υӥåȿ� */
#define	TBIT_FLGPTN	(sizeof(FLGPTN) * CHAR_BIT)
					/* ���٥�ȥե饰�Υӥåȿ� */

#ifdef __cplusplus
}
#endif

#endif /* _KERNEL_H_ */
