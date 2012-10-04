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
 *  @(#) $Id: api.h,v 1.2 2003/06/30 15:44:11 takayuki Exp $
 */

#ifndef API_H
#define API_H

#define __cycini
#define __cycenq
#define __sta_cyc
#define __stp_cyc
#define __cyccal
#define __dtqini
#define __dtqenq
#define __dtqfenq
#define __dtqdeq
#define __dtqsnd
#define __dtqrcv
#define __snd_dtq
#define __psnd_dtq
#define __ipsnd_dtq
#define __tsnd_dtq
#define __fsnd_dtq
#define __ifsnd_dtq
#define __rcv_dtq
#define __prcv_dtq
#define __trcv_dtq
#define __flgini
#define __flgcnd
#define __set_flg
#define __iset_flg
#define __clr_flg
#define __wai_flg
#define __pol_flg
#define __twai_flg
#define __excini
#define __vxsns_ctx
#define __vxsns_loc
#define __vxsns_dsp
#define __vxsns_dpn
#define __vxsns_tex
#define __inhini
#define __mbxini
#define __snd_mbx
#define __rcv_mbx
#define __prcv_mbx
#define __trcv_mbx
#define __mpfini
#define __mpfget
#define __get_mpf
#define __pget_mpf
#define __tget_mpf
#define __rel_mpf
#define __semini
#define __sig_sem
#define __isig_sem
#define __wai_sem
#define __pol_sem
#define __twai_sem
#define __rot_rdq
#define __irot_rdq
#define __get_tid
#define __iget_tid
#define __loc_cpu
#define __iloc_cpu
#define __unl_cpu
#define __iunl_cpu
#define __dis_dsp
#define __ena_dsp
#define __sns_ctx
#define __sns_loc
#define __sns_dsp
#define __sns_dpn
#define __logini
#define __vwri_log
#define __vrea_log
#define __vmsk_log
#define __logter
#define __tskini
#define __tsksched
#define __tskrun
#define __tsknrun
#define __tskdmt
#define __tskact
#define __tskext
#define __tskpri
#define __tskrot
#define __tsktex
#define __ras_tex
#define __iras_tex
#define __dis_tex
#define __ena_tex
#define __sns_tex
#define __act_tsk
#define __iact_tsk
#define __can_act
#define __ext_tsk
#define __ter_tsk
#define __chg_pri
#define __get_pri
#define __slp_tsk
#define __tslp_tsk
#define __wup_tsk
#define __iwup_tsk
#define __can_wup
#define __rel_wai
#define __irel_wai
#define __sus_tsk
#define __rsm_tsk
#define __frsm_tsk
#define __dly_tsk
#define __tmeini
#define __tmeup
#define __tmedown
#define __tmeins
#define __tmedel
#define __isig_tim
#define __set_tim
#define __get_tim
#define __vxget_tim
#define __waimake
#define __waicmp
#define __waitmo
#define __waitmook
#define __waican
#define __wairel
#define __wobjwai
#define __wobjwaitmo
#define __wobjpri


#endif

