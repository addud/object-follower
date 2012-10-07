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
 *  @(#) $Id: cpu_config.c,v 1.14 2004/09/17 09:58:17 honda Exp $
 */

/*
 *	�ץ��å���¸�⥸�塼���ARM4vT�ѡ�
 */

#include "jsp_kernel.h"
#include "check.h"
#include <armv4.h>
#include "task.h"

#ifndef VECTOR_IN_ROM
/*
 * �㳰�٥����˽񤭹��ޤ줿������̿�᤬���Ȥ��륢�ɥ쥹
 * 
 */
UW *arm_vector_add[8];


/*
 * �㳰�˱������ϥ�ɥ�ε�ư����
 */
UW arm_handler_add[8];

#endif /* VECTOR_IN_ROM */

/*
 * �����ߤΥͥ��Ȳ���Υ������
 */
UW interrupt_count;


/*
 * CPU/����ߥϥ�ɥ�ν����������ǰ��Ū�˻��Ѥ��륹���å�
 */
UW int_stack[INT_STACK_SIZE];


/*
 *  CPU�㳰�ϥ�ɥ������
 */
void
define_exc(EXCNO excno, FP exchdr)
{
#ifndef VECTOR_IN_ROM
    arm_install_handler(excno,exchdr);
#endif /* VECTOR_IN_ROM */
}


/*
 *  ̤������㳰�����ä����ν���
 */
void
undef_exception(){
  syslog(LOG_EMERG, "Unregistered Exception occurs. UNDEF");
    while(1);
}

void
swi_exception(){
  syslog(LOG_EMERG, "Unregistered Exception occurs. SWI");
  while(1);
}

void
prefetch_exception(){
  syslog(LOG_EMERG, "Unregistered Exception occurs. PREFETCH");
  while(1);
}

void
data_abort_exception(){
  syslog(LOG_EMERG, "Unregistered Exception occurs. DATA ABORT");
  while(1);
}


void
irq_exception(){
  syslog(LOG_EMERG, "Unregistered Exception occurs. IRQ");
  while(1);
}

void
fiq_exception(){
  syslog(LOG_EMERG, "Unregistered Exception occurs. FIQ");
  while(1);
}



/*
 *  �ץ��å���¸�ν����
 */
void
cpu_initialize()
{
#ifndef VECTOR_IN_ROM
    UW i,vector_value;
#endif /* VECTOR_IN_ROM */

	interrupt_count = 1;

#ifndef VECTOR_IN_ROM
    /*
     * �㳰�٥�������Ͽ����Ƥ���̿�ᤫ�黲�Ȥ���륢�ɥ쥹�ȡ�
     *���Υ��ɥ쥹������(�ϥ�ɥ�μ¹���)����¸���롥
     */
    for(i = 0; i <=7; i++){
        vector_value = *(volatile UW *)(i*4);
        vector_value &= 0x00000fff;
        arm_vector_add[i] =  (UW *)(vector_value + 8) + i;
        arm_handler_add[i] = *(arm_vector_add[i]);
    }
#endif /* VECTOR_IN_ROM */
}


/*
 *  �ץ��å���¸�ν�λ����
 */
void
cpu_terminate()
{
#ifndef VECTOR_IN_ROM
    UW i;
    /*  �٥����ơ��֥�򸵤��᤹��*/
    for(i = 0; i <=7; i++)
        *arm_vector_add[i] = arm_handler_add[i];
#endif /* VECTOR_IN_ROM */
}
