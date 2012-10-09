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
 *  @(#) $Id: sil.h,v 1.9 2006/02/12 05:27:25 hiro Exp $
 */

/*
 *	�����ƥ।�󥿥ե������쥤��ʥ������åȶ�������
 *
 *  ������֥����Υ������ե�����䥷���ƥॳ��ե�����졼�����ե�
 *  ���뤫�餳�Υե�����򥤥󥯥롼�ɤ�����ϡ�_MACRO_ONLY ���������
 *  �������Ȥǡ��ޥ�������ʳ��ε��Ҥ�������Ȥ��Ǥ��롥
 *
 *  ���Υ��󥯥롼�ɥե�����ϡ�ɸ�।�󥯥롼�ɥե������s_services.h��
 *  �ǥ��󥯥롼�ɤ���롥�ޤ��������ͥ뤫��ƤФ��ǥХ����ɥ饤�Ф�
 *  ���󥯥롼�ɥե�����ǡ�����饤��ؿ��ʤɤǥ����ƥ।�󥿥ե�����
 *  �쥤����Ѥ��Ƥ�����ˤ⡤���Υե����뤬���󥯥롼�ɤ���롥����
 *  �㳰������ơ�¾�Υե����뤫��ľ�ܥ��󥯥롼�ɤ���뤳�ȤϤʤ���
 *
 *  ������ǥ��󥯥롼�ɤ��Ƥ���ե����������ơ�¾�Υ��󥯥롼�ɥե�
 *  ����˰�¸���Ƥ��ʤ���
 */

#ifndef _SIL_H_
#define _SIL_H_

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
 *  ����ǥ�������������
 */
#define	SIL_ENDIAN_LITTLE	0	/* ��ȥ륨��ǥ����� */
#define	SIL_ENDIAN_BIG		1	/* �ӥå�����ǥ����� */

#ifndef _MACRO_ONLY

/*
 *  ����ߥ�å����֤�����
 */
#ifndef SIL_PRE_LOC
#include <kernel.h>
#define	SIL_PRE_LOC	BOOL _sil_loc_ = sns_loc()
#define	SIL_LOC_INT()	((void)(!(_sil_loc_) \
				&& (sns_ctx() ? iloc_cpu() : loc_cpu())))
#define	SIL_UNL_INT()	((void)(!(_sil_loc_) \
				&& (sns_ctx() ? iunl_cpu() : unl_cpu())))
#endif /* SIL_PRE_LOC */

/*
 *  ���������Ԥ�
 */
extern void	sil_dly_nse(UINT dlytim) throw();

/*
 *  ����ǥ������ȿž
 */
#ifndef SIL_REV_ENDIAN_H
#define	SIL_REV_ENDIAN_H(data) \
	((VH)((((UH)(data) & 0xff) << 8) | (((UH)(data) >> 8) & 0xff)))
#endif /* SIL_REV_ENDIAN_H */

#ifndef SIL_REV_ENDIAN_W
#define	SIL_REV_ENDIAN_W(data) \
	((VW)((((UW)(data) & 0xff) << 24) | (((UW)(data) & 0xff00) << 8) \
		| (((UW)(data)>> 8) & 0xff00) | (((UW)(data) >> 24) & 0xff)))
#endif /* SIL_REV_ENDIAN_H */

/*
 *  ������֥��������ؿ�
 */
#ifndef OMIT_SIL_ACCESS

/*
 *  8�ӥå�ñ�̤��ɽФ��������
 */
#ifdef _int8_

Inline VB
sil_reb_mem(VP mem)
{
	VB	data;

	data = *((volatile VB *) mem);
	return(data);
}

Inline void
sil_wrb_mem(VP mem, VB data)
{
	*((volatile VB *) mem) = data;
}

#endif /* _int8_ */

/*
 *  16�ӥå�ñ�̤��ɽФ��������
 */
#ifdef _int16_

Inline VH
sil_reh_mem(VP mem)
{
	VH	data;

	data = *((volatile VH *) mem);
	return(data);
}

Inline void
sil_wrh_mem(VP mem, VH data)
{
	*((volatile VH *) mem) = data;
}

#if SIL_ENDIAN == SIL_ENDIAN_BIG	/* �ӥå�����ǥ�����ץ��å� */

#define	sil_reh_bem(mem)	sil_reh_mem(mem)
#define	sil_wrh_bem(mem, data)	sil_wrh_mem(mem, data)

#ifndef OMIT_SIL_REH_LEM

Inline VH
sil_reh_lem(VP mem)
{
	VH	data;

	data = *((volatile VH *) mem);
	return(SIL_REV_ENDIAN_H(data));
}

#endif /* OMIT_SIL_REH_LEM */
#ifndef OMIT_SIL_WRH_LEM

Inline void
sil_wrh_lem(VP mem, VH data)
{
	*((volatile VH *) mem) = SIL_REV_ENDIAN_H(data);
}

#endif /* OMIT_SIL_WRH_LEM */
#else /* SIL_ENDIAN == SIL_ENDIAN_BIG *//* ��ȥ륨��ǥ�����ץ��å� */

#define	sil_reh_lem(mem)	sil_reh_mem(mem)
#define	sil_wrh_lem(mem, data)	sil_wrh_mem(mem, data)

#ifndef OMIT_SIL_REH_BEM

Inline VH
sil_reh_bem(VP mem)
{
	VH	data;

	data = *((volatile VH *) mem);
	return(SIL_REV_ENDIAN_H(data));
}

#endif /* OMIT_SIL_REH_BEM */
#ifndef OMIT_SIL_WRH_BEM

Inline void
sil_wrh_bem(VP mem, VH data)
{
	*((volatile VH *) mem) = SIL_REV_ENDIAN_H(data);
}

#endif /* OMIT_SIL_WRH_BEM */
#endif /* SIL_ENDIAN == SIL_ENDIAN_BIG */
#endif /* _int16_ */

/*
 *  32�ӥå�ñ�̤��ɽФ��������
 */

Inline VW
sil_rew_mem(VP mem)
{
	VW	data;

	data = *((volatile VW *) mem);
	return(data);
}

Inline void
sil_wrw_mem(VP mem, VW data)
{
	*((volatile VW *) mem) = data;
}

#if SIL_ENDIAN == SIL_ENDIAN_BIG	/* �ӥå�����ǥ�����ץ��å� */

#define	sil_rew_bem(mem)	sil_rew_mem(mem)
#define	sil_wrw_bem(mem, data)	sil_wrw_mem(mem, data)

#ifndef OMIT_SIL_REW_LEM

Inline VW
sil_rew_lem(VP mem)
{
	VW	data;

	data = *((volatile VW *) mem);
	return(SIL_REV_ENDIAN_W(data));
}

#endif /* OMIT_SIL_REW_LEM */
#ifndef OMIT_SIL_WRW_LEM

Inline void
sil_wrw_lem(VP mem, VW data)
{
	*((volatile VW *) mem) = SIL_REV_ENDIAN_W(data);
}

#endif /* OMIT_SIL_WRW_LEM */
#else /* SIL_ENDIAN == SIL_ENDIAN_BIG *//* ��ȥ륨��ǥ�����ץ��å� */

#define	sil_rew_lem(mem)	sil_rew_mem(mem)
#define	sil_wrw_lem(mem, data)	sil_wrw_mem(mem, data)

#ifndef OMIT_SIL_REW_BEM

Inline VW
sil_rew_bem(VP mem)
{
	VW	data;

	data = *((volatile VW *) mem);
	return(SIL_REV_ENDIAN_W(data));
}

#endif /* OMIT_SIL_REW_BEM */
#ifndef OMIT_SIL_WRW_BEM

Inline void
sil_wrw_bem(VP mem, VW data)
{
	*((volatile VW *) mem) = SIL_REV_ENDIAN_W(data);
}

#endif /* OMIT_SIL_WRW_BEM */
#endif /* SIL_ENDIAN == SIL_ENDIAN_BIG */
#endif /* OMIT_SIL_ACCESS */

#endif /* _MACRO_ONLY */

#ifdef __cplusplus
}
#endif

#endif /* _SIL_H_ */
