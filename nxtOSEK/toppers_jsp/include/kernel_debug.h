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
 *  @(#) $Id: kernel_debug.h,v 1.2 2003/07/01 13:36:30 hiro Exp $
 */

/*
 *	��ITRON4.0���� �ǥХå��ѥ��󥯥롼�ɥե�����
 *
 *  ���Υե�����ϡ���ITRON4.0���ͤΥ���������ɥץ�ե����볰������ȡ�
 *  ITRON�ǥХå��󥰥��󥿥ե��������ͤ˴ޤޤ���������ǡ�JSP������
 *  ��ΥǥХå����ݡ��ȵ�ǽ��ɬ�פ������ޤࡥ
 */

#ifndef _KERNEL_DEBUG_H_
#define _KERNEL_DEBUG_H_

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  ���������֤����
 */
#define TTS_RUN		0x01u			/* �¹Ծ��� */
#define TTS_RDY		0x02u			/* �¹Բ�ǽ���� */
#define TTS_WAI		0x04u			/* �Ԥ����� */
#define TTS_SUS		0x08u			/* �����Ԥ����� */
#define TTS_WAS		(TTS_WAI|TTS_SUS)	/* ����Ԥ����� */
#define TTS_DMT		0x10u			/* �ٻ߾��� */

#define TTW_SLP		0x0001u		/* �����Ԥ����� */
#define TTW_DLY		0x0002u		/* ���ַв��Ԥ����� */
#define TTW_SEM		0x0004u		/* ���ޥե��񸻤γ����Ԥ����� */
#define TTW_FLG		0x0008u		/* ���٥�ȥե饰�Ԥ����� */
#define TTW_SDTQ	0x0010u		/* �ǡ������塼�ؤ������Ԥ����� */
#define TTW_RDTQ	0x0020u		/* �ǡ������塼����μ����Ԥ����� */
#define TTW_MBX		0x0040u		/* �᡼��ܥå�������μ����Ԥ����� */
#define TTW_MTX		0x0080u		/* �ߥ塼�ƥå����Υ�å��Ԥ����� */
#define TTW_SMBF	0x0100u		/* ��å������Хåե��ؤ������Ԥ� */
#define TTW_RMBF	0x0200u		/* ��å������Хåե�����μ����Ԥ� */
#define TTW_CAL		0x0400u		/* ���ǥ֤θƽФ��Ԥ����� */
#define TTW_ACP		0x0800u		/* ���ǥ֤μ����Ԥ����� */
#define TTW_RDV		0x1000u		/* ���ǥ֤ν�λ�Ԥ����� */
#define TTW_MPF		0x2000u		/* ����Ĺ����֥�å��γ����Ԥ� */
#define TTW_MPL		0x4000u		/* ����Ĺ����֥�å��γ����Ԥ� */

/*
 *  ��ǽ�����ɤ����
 */
#define TFN_CRE_TSK	(-5)
#define TFN_DEL_TSK	(-6)
#define TFN_ACT_TSK	(-7)
#define TFN_CAN_ACT	(-8)
#define TFN_STA_TSK	(-9)
#define TFN_EXT_TSK	(-10)
#define TFN_EXD_TSK	(-11)
#define TFN_TER_TSK	(-12)
#define TFN_CHG_PRI	(-13)
#define TFN_GET_PRI	(-14)
#define TFN_REF_TSK	(-15)
#define TFN_REF_TST	(-16)

#define TFN_SLP_TSK	(-17)
#define TFN_TSLP_TSK	(-18)
#define TFN_WUP_TSK	(-19)
#define TFN_CAN_WUP	(-20)
#define TFN_REL_WAI	(-21)
#define TFN_SUS_TSK	(-22)
#define TFN_RSM_TSK	(-23)
#define TFN_FRSM_TSK	(-24)
#define TFN_DLY_TSK	(-25)

#define TFN_DEF_TEX	(-27)
#define TFN_RAS_TEX	(-28)
#define TFN_DIS_TEX	(-29)
#define TFN_ENA_TEX	(-30)
#define TFN_SNS_TEX	(-31)
#define TFN_REF_TEX	(-32)

#define TFN_CRE_SEM	(-33)
#define TFN_DEL_SEM	(-34)
#define TFN_SIG_SEM	(-35)
#define TFN_WAI_SEM	(-37)
#define TFN_POL_SEM	(-38)
#define TFN_TWAI_SEM	(-39)
#define TFN_REF_SEM	(-40)

#define TFN_CRE_FLG	(-41)
#define TFN_DEL_FLG	(-42)
#define TFN_SET_FLG	(-43)
#define TFN_CLR_FLG	(-44)
#define TFN_WAI_FLG	(-45)
#define TFN_POL_FLG	(-46)
#define TFN_TWAI_FLG	(-47)
#define TFN_REF_FLG	(-48)

#define TFN_CRE_DTQ	(-49)
#define TFN_DEL_DTQ	(-50)
#define TFN_SND_DTQ	(-53)
#define TFN_PSND_DTQ	(-54)
#define TFN_TSND_DTQ	(-55)
#define TFN_FSND_DTQ	(-56)
#define TFN_RCV_DTQ	(-57)
#define TFN_PRCV_DTQ	(-58)
#define TFN_TRCV_DTQ	(-59)
#define TFN_REF_DTQ	(-60)

#define TFN_CRE_MBX	(-61)
#define TFN_DEL_MBX	(-62)
#define TFN_SND_MBX	(-63)
#define TFN_RCV_MBX	(-65)
#define TFN_PRCV_MBX	(-66)
#define TFN_TRCV_MBX	(-67)
#define TFN_REF_MBX	(-68)

#define TFN_CRE_MPF	(-69)
#define TFN_DEL_MPF	(-70)
#define TFN_REL_MPF	(-71)
#define TFN_GET_MPF	(-73)
#define TFN_PGET_MPF	(-74)
#define TFN_TGET_MPF	(-75)
#define TFN_REF_MPF	(-76)

#define TFN_SET_TIM	(-77)
#define TFN_GET_TIM	(-78)

#define TFN_CRE_CYC	(-79)
#define TFN_DEL_CYC	(-80)
#define TFN_STA_CYC	(-81)
#define TFN_STP_CYC	(-82)
#define TFN_REF_CYC	(-83)

#define TFN_ROT_RDQ	(-85)
#define TFN_GET_TID	(-86)
#define TFN_LOC_CPU	(-89)
#define TFN_UNL_CPU	(-90)
#define TFN_DIS_DSP	(-91)
#define TFN_ENA_DSP	(-92)
#define TFN_SNS_CTX	(-93)
#define TFN_SNS_LOC	(-94)
#define TFN_SNS_DSP	(-95)
#define TFN_SNS_DPN	(-96)
#define TFN_REF_SYS	(-97)

#define TFN_DEF_INH	(-101)
#define TFN_CRE_ISR	(-102)
#define TFN_DEL_ISR	(-103)
#define TFN_REF_ISR	(-104)
#define TFN_DIS_INT	(-105)
#define TFN_ENA_INT	(-106)
#define TFN_CHG_IXX	(-107)
#define TFN_GET_IXX	(-108)

#define TFN_DEF_SVC	(-109)
#define TFN_DEF_EXC	(-110)
#define TFN_REF_CFG	(-111)
#define TFN_REF_VER	(-112)

#define TFN_IACT_TSK	(-113)
#define TFN_IWUP_TSK	(-114)
#define TFN_IREL_WAI	(-115)
#define TFN_IRAS_TEX	(-116)
#define TFN_ISIG_SEM	(-117)
#define TFN_ISET_FLG	(-118)
#define TFN_IPSND_DTQ	(-119)
#define TFN_IFSND_DTQ	(-120)
#define TFN_IROT_RDQ	(-121)
#define TFN_IGET_TID	(-122)
#define TFN_ILOC_CPU	(-123)
#define TFN_IUNL_CPU	(-124)
#define TFN_ISIG_TIM	(-125)

#define TFN_CRE_MTX	(-129)
#define TFN_DEL_MTX	(-130)
#define TFN_UNL_MTX	(-131)
#define TFN_LOC_MTX	(-133)
#define TFN_PLOC_MTX	(-134)
#define TFN_TLOC_MTX	(-135)
#define TFN_REF_MTX	(-136)

#define TFN_CRE_MBF	(-137)
#define TFN_DEL_MBF	(-138)
#define TFN_SND_MBF	(-141)
#define TFN_PSND_MBF	(-142)
#define TFN_TSND_MBF	(-143)

#define TFN_VXSNS_CTX	(-225)
#define TFN_VXSNS_LOC	(-226)
#define TFN_VXSNS_DSP	(-227)
#define TFN_VXSNS_DPN	(-228)
#define TFN_VXSNS_TEX	(-229)
#define TFN_VSNS_INI	(-232)

#define TFN_VXGET_TIM	(-233)

/*
 *  ���֥�����������������ITRON�ǥХå��󥰥��󥿥ե��������͡�
 */
#define OBJ_SEMAPHORE		(128)
#define OBJ_EVENTFLAG		(129)
#define OBJ_DATAQUEUE		(130)
#define OBJ_MAILBOX		(131)
#define OBJ_MUTEX		(132)
#define OBJ_MESSAGEBUFFER	(133)
#define OBJ_RENDEZVOUSPORT	(135)
#define OBJ_RENDEZVOUS		(136)
#define OBJ_FMEMPOOL		(137)
#define OBJ_VMEMPOOL		(138)
#define OBJ_TASK		(139)
#define OBJ_READYQUEUE		(141)
#define OBJ_TIMERQUEUE		(142)
#define OBJ_CYCLICHANDLER	(144)
#define OBJ_ALARMHANDLER	(145)
#define OBJ_OVERRUNHANDLER	(146)
#define OBJ_ISR			(147)
#define OBJ_KERNELSTATUS	(148)
#define OBJ_TASKEXCEPTION	(149)
#define OBJ_CPUEXCEPTION	(150)

#ifdef __cplusplus
}
#endif

#endif /* _KERNEL_DEBUG_H_ */
