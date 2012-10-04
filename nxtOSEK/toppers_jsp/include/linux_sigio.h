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
 *  @(#) $Id: linux_sigio.h,v 1.10 2003/12/06 06:18:55 hiro Exp $
 */

/*
 *  LINUX�� �Υ�֥�å���I/O ���ݡ��ȥ⥸�塼��
 *
 *  �Υ�֥�å���I/O ���ݡ��ȥ⥸�塼��ϡ�SIGIO �����ʥ�ˤ�ꡤ�桼
 *  ������Ͽ����������Хå��ؿ���ƤӽФ���ǽ����ġ�
 *
 *  SIGIO �����ʥ�ˤ�ꥳ����Хå��ؿ���¹Ԥ����������ˤϡ�SIGIO 
 *  ���Υ��٥�ȥ֥�å����Ѱդ������� callback �ե�����ɤ˥�����Х�
 *  ���ؿ���arg �ե�����ɤ˥�����Хå��ؿ����Ϥ����������ꤷ��
 *  eneuque_sigioeb ���Ѥ��� SIGIO ���Υ��٥�ȥ��塼����Ͽ���롥
 *
 *  �ƤӽФ��줿������Хå��ؿ��� 0 ���֤��ȡ���Ϣ���� SIGIO ���Υ���
 *  ��ȥ֥�å� �ϥ��塼����Ͽ���줿�ޤޤȤʤꡤ³�� SIGIO �����ʥ��
 *  �Ƥ�Ʊ������ ��Хå��ؿ����ƤӽФ���롥������Хå��ؿ��� 0 �ʳ�
 *  ���֤��ȡ�SIGIO ���Υ��٥�ȥ֥�å��ϥ��塼���������졤������Х�
 *  ���ؿ��Ϥ���ʹ߸ƤӽФ���ʤ��ʤ롥
 */

#ifndef	_LINUX_SIGIO_H_
#define	_LINUX_SIGIO_H_

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  SIGIO ���Υ��٥�ȥ֥�å������
 */
typedef BOOL	(*SIGIO_CBACK)(VP);	/* SIGIO ������Хå��ؿ��η� */

typedef struct bsd_sigio_event_block {
	VP		queue[2];	/* SIGIO ���Υ��٥�ȥ��塼���ꥢ */
	SIGIO_CBACK	callback;	/* SIGIO ������Хå��ؿ� */
	VP		arg;		/* ������Хå��ؿ����Ϥ����� */
} SIGIOEB;

/*
 *  SIGIO ���Υ��٥�ȥ֥�å�����Ͽ
 */
extern ER	enqueue_sigioeb(SIGIOEB *sigioeb) throw();

/*
 *  �����ƥ൯ư���� SIGIO ���Υ��٥�ȥ֥�å�����Ͽ
 */
extern ER	enqueue_sigioeb_initialize(SIGIOEB *sigioeb) throw();

/*
 *   �Υ�֥�å���I/O �⥸�塼�뵯ư�롼����
 */

extern void linux_sigio_initialize(VP_INT exinf) throw();

/*
 *  ����ߥϥ�ɥ�Υ٥����ֹ�
 */
#define	INHNO_SIGIO	SIGIO

/*
 *  SIGIO�����ߥϥ�ɥ�
 */

extern void linux_sigio_handler() throw();
    
/*
 * SIGIO������������
 */
#define LINUX_SIGIO_PRIORITY      2
#define LINUX_SIGIO_STACK_SIZE 8192

extern void linux_sigio_task(void) throw();

#ifdef __cplusplus
}
#endif

#endif /* _LINUX_SIGIO_H_ */
