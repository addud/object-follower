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
 *  @(#) $Id: fdc37c935a.h,v 1.1 2003/12/11 06:47:39 honda Exp $
 */

/*
 * ������I/O FDC37C935A �ѥɥ饤��
 */
#ifndef _FDC37C935A_H_
#define _FDC37C935A_H_

#include <t_config.h>

/*
 * �١������ɥ쥹 
 */
//#define SMSC_BASE_ADDR 0xB0400000

#define SMSC_CONFIG_PORT (SMSC_BASE_ADDR + 0x7E0)  /* H */
#define SMSC_INDEX_PORT  (SMSC_BASE_ADDR + 0x7E0)  /* H */
#define SMSC_DATA_PORT   (SMSC_BASE_ADDR + 0x7E2)  /* H */


#ifndef _MACRO_ONLY

Inline void
smsc_config_write(UH index, UH data)
{
    sil_wrh_mem((VP)SMSC_INDEX_PORT, (index << 8));
    sil_wrh_mem((VP)SMSC_DATA_PORT, (data << 8));
}

Inline UH
smsc_config_read(UH index)
{
    sil_wrh_mem((VP)SMSC_INDEX_PORT, (index << 8));
    return(sil_reh_mem((VP)SMSC_DATA_PORT) >> 8);
}

/*
 *  �����
 */
extern void smsc_init(void);



#endif /*  _MACRO_ONLY */


/*
 * SCI0
 */
#define SMSC_SCI0_BASE_ADDR  0x03f8

#define SMSC_SCI0_RBR (SMSC_BASE_ADDR + SMSC_SCI0_BASE_ADDR * 2 + 0x0)  /* H */
#define SMSC_SCI0_THR (SMSC_BASE_ADDR + SMSC_SCI0_BASE_ADDR * 2 + 0x0)  /* H */
#define SMSC_SCI0_DLL (SMSC_BASE_ADDR + SMSC_SCI0_BASE_ADDR * 2 + 0x0)  /* H */
#define SMSC_SCI0_IER (SMSC_BASE_ADDR + SMSC_SCI0_BASE_ADDR * 2 + 0x2)  /* H */
#define SMSC_SCI0_DLM (SMSC_BASE_ADDR + SMSC_SCI0_BASE_ADDR * 2 + 0x2)  /* H */
#define SMSC_SCI0_IIR (SMSC_BASE_ADDR + SMSC_SCI0_BASE_ADDR * 2 + 0x4)  /* H */
#define SMSC_SCI0_FCR (SMSC_BASE_ADDR + SMSC_SCI0_BASE_ADDR * 2 + 0x4)  /* H */
#define SMSC_SCI0_LCR (SMSC_BASE_ADDR + SMSC_SCI0_BASE_ADDR * 2 + 0x6)  /* H */
#define SMSC_SCI0_MCR (SMSC_BASE_ADDR + SMSC_SCI0_BASE_ADDR * 2 + 0x8)  /* H */
#define SMSC_SCI0_LSR (SMSC_BASE_ADDR + SMSC_SCI0_BASE_ADDR * 2 + 0xA)  /* H */
#define SMSC_SCI0_MSR (SMSC_BASE_ADDR + SMSC_SCI0_BASE_ADDR * 2 + 0xC)  /* H */
#define SMSC_SCI0_SCR (SMSC_BASE_ADDR + SMSC_SCI0_BASE_ADDR * 2 + 0xE)  /* H */

/*
 *  �����ѡ�I/O(FDC37C935A)�� �ʰ�SIO�ɥ饤��
 */

#ifndef _MACRO_ONLY

/*
 *  ����߰ʳ��ν����
 *  �����ͥ뵯ư���Ѥν����(sys_putc����Ѥ��뤿��)
 */
extern void fdc37c935a_init(void);


/*
 *  ���ꥢ��I/O�ݡ��ȴ����֥�å������
 */
typedef struct sio_port_control_block   SIOPCB;

/*
 *  ������Хå��롼����μ����ֹ�
 */
#define SIO_ERDY_SND    1u      /* ������ǽ������Хå� */
#define SIO_ERDY_RCV    2u      /* �������Υ�����Хå� */


/*
 *  SIO�ɥ饤�Фν�����롼����
 */
extern void smsc_sci0_initialize(void);


/*
 *  �����ץ󤷤Ƥ���ݡ��Ȥ����뤫��
 */
extern BOOL smsc_sci0_openflag(void);


/*
 *  ���ꥢ��I/O�ݡ��ȤΥ����ץ�
 */
extern SIOPCB   *smsc_sci0_opn_por(ID siopid, VP_INT exinf);


/*
 *  ���ꥢ��I/O�ݡ��ȤΥ�����
 */
extern void smsc_sci0_cls_por(SIOPCB *siopcb);


/*
 *  ���ꥢ��I/O�ݡ��Ȥؤ�ʸ������
 */
extern BOOL smsc_sci0_snd_chr(SIOPCB *siopcb, char c);


/*
 *  ���ꥢ��I/O�ݡ��Ȥ����ʸ������
 */
extern INT  smsc_sci0_rcv_chr(SIOPCB *siopcb);


/*
 *  ���ꥢ��I/O�ݡ��Ȥ���Υ�����Хå��ε���
 */
extern void smsc_sci0_ena_cbr(SIOPCB *siopcb, UINT cbrtn);


/*
 *  ���ꥢ��I/O�ݡ��Ȥ���Υ�����Хå��ζػ�
 */
extern void smsc_sci0_dis_cbr(SIOPCB *siopcb, UINT cbrtn);


/*
 *  SIO�γ���ߥ����ӥ��롼����
 */
extern void smsc_sci0_isr(void);


/*
 *  ���ꥢ��I/O�ݡ��Ȥ����������ǽ������Хå�
 */
extern void smsc_sci0_ierdy_snd(VP_INT exinf);


/*
 *  ���ꥢ��I/O�ݡ��Ȥ���μ������Υ�����Хå�
 */
extern void smsc_sci0_ierdy_rcv(VP_INT exinf);




#endif /* _MACRO_ONLY */


#endif /* _FDC37C935A_H_ */
