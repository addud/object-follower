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
 *  @(#) $Id: serial.h,v 1.7 2003/06/04 01:46:02 hiro Exp $
 */

/*
 *	���ꥢ�륤�󥿥ե������ɥ饤��
 */

#ifndef _SERIAL_H_
#define _SERIAL_H_

/*
 *  ���ꥢ�륤�󥿥ե������ɥ饤�Ф��Ѥ���ѥ��å�
 */
typedef struct {
		UINT	reacnt;		/* �����Хåե����ʸ���� */
		UINT	wricnt;		/* �����Хåե����ʸ���� */
	} T_SERIAL_RPOR;

/*
 *  ���ꥢ�륤�󥿥ե������ɥ饤�Фν�����롼����
 */
extern void	serial_initialize(VP_INT exinf) throw();

/*
 *  ���ꥢ�륤�󥿥ե������ɥ饤�ФΥ����ӥ�������
 */
extern ER	serial_opn_por(ID portid) throw();
extern ER	serial_cls_por(ID portid) throw();
extern ER_UINT	serial_rea_dat(ID portid, char *buf, UINT len) throw();
extern ER_UINT	serial_wri_dat(ID portid, char *buf, UINT len) throw();
extern ER	serial_ctl_por(ID portid, UINT ioctl) throw();
extern ER	serial_ref_por(ID portid, T_SERIAL_RPOR *pk_rpor) throw();

/*
 *  ���ꥢ�륤�󥿥ե������ɥ饤�Ф�ư�������ѤΤ�������
 *
 *  �ʲ�������ϡ��ӥå���������¤�Ȥä��Ѥ��롥
 */
#define	IOCTL_NULL	0u		/* ����ʤ� */
#define	IOCTL_ECHO	0x0001u		/* ��������ʸ���򥨥����Хå� */
#define	IOCTL_CRLF	0x0010u		/* LF �������������� CR ���ղ� */
#define	IOCTL_FCSND	0x0100u		/* �������Ф��ƥե������Ԥ� */
#define	IOCTL_FCANY	0x0200u		/* �ɤΤ褦��ʸ���Ǥ������Ƴ� */
#define	IOCTL_FCRCV	0x0400u		/* �������Ф��ƥե������Ԥ� */

#endif /* _SERIAL_H_ */
