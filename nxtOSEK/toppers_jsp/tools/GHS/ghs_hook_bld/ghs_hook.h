/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *                2003      by Advanced Data Controls, Corp
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
 *  @(#) $Id: ghs_hook.h,v 1.2 2003/12/19 11:48:37 honda Exp $
 */

#ifdef GHS_HOOK
#include "hook.h"

#define TRACE_TNUM_TSKID 16
#define TRACE_TNUM_EVT 16

#ifndef BUFF_SIZE
#define BUFF_SIZE   0x4000	/* 0x400 | 0x800 | 0x1000 | 0x2000 | 0x4000 */
#endif

/* tskstat */

#define S_DMT       0x00    /* DORMANT */
#define S_RDY       0x10    /* RUN,READY */
#define S_SLP       0x20    /* wait due to slp_tsk or tslp_tsk */
#define S_DLY       0x30    /* wait due to dly_tsk */
#define S_RDV       0x40    /* wait for rendezvous completion */
#define S_FLG       0x50    /* wait due to wai_flg or twai_flg */
#define S_SMB       0x60    /* wait due to snd_mbf or tsnd_mbf */
#define S_CAL       0x70    /* wait for rendezvous call */
#define S_ACP       0x80    /* wait for rendezvous accept */
#define S_SEM       0x90    /* wait due to wai_sem or twai_sem */
#define S_MBX       0xa0    /* wait due to rcv_msg or trcv_msg */
#define S_MBF       0xb0    /* wait due to rcv_mbf or trcv_mbf */
#define S_MPL       0xc0    /* wait due to get_blk or tget_blk */
#define S_MPF       0xd0    /* wait due to get_blf or tget_blf */

typedef struct
{
	short max_tid;
    unsigned short trc_grp;
    unsigned short sys_grp;
    short tnum_tskid;
    short tnum_evt;
    unsigned char task_id[TRACE_TNUM_TSKID];
    unsigned char evtcode[TRACE_TNUM_EVT];
} T_HOOK;

typedef struct
{   char bigendian;
    char dummy;
    unsigned short size;
    unsigned short putp;
    unsigned short getp;
} T_TRACE;

typedef struct
{
    T_TRACE trace;
    T_HOOK hook;
    long syscall[BUFF_SIZE];
} T_ROS;

extern T_ROS Ros_buf;

void ghs_hook4(int sts, int p1, int p2);
void ghs_hook5(int sts, int p1, int p2, int p3);
void ghs_hook6(int sts, int p1, int p2, int p3, int p4);
void ghs_hook7(int sts, int p1, int p2, int p3, int p4, int p5);
void ghs_hook8(int sts, int p1, int p2, int p3, int p4, int p5, int p6);
void ghs_hook9(int sts, int p1, int p2, int p3, int p4, int p5, int p6, int p7);
#endif

