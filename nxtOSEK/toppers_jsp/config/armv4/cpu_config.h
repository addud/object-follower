/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2004 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2007-     by Monami Software Limited Partnership, JAPAN
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
 *  @(#) $Id: cpu_config.h,v 1.19 2004/09/17 13:45:55 honda Exp $
 */

/*
 *  �ץ��å���¸�⥸�塼���ARM4vT�ѡ�
 *
 *  ���Υ��󥯥롼�ɥե�����ϡ�t_config.h �Τߤ��饤�󥯥롼�ɤ���롥
 *  ¾�Υե����뤫��ľ�ܥ��󥯥롼�ɤ��ƤϤʤ�ʤ���
 */

#ifndef _CPU_CONFIG_H_
#define _CPU_CONFIG_H_

/*
 *  �����ͥ���������̾�Υ�͡���
 */
#include "cpu_rename.h"

/*
 *  �ץ��å����ü�̿��Υ���饤��ؿ����
 */
#ifndef _MACRO_ONLY
#include <cpu_insn.h>
#endif /* _MACRO_ONLY */

/*
 * �����ƥ��������
 */
#include "sys_defs.h"

/*
 *  TCB ��Ϣ�����
 *
 *  cpu_context.h ��������������쥬��Ȥ��������Ȥΰ�¸���δط��ǡ�
 *  cpu_context.h �ˤ�������ʤ���
 */

/*
 *  TCB ��Υե�����ɤΥӥå��������
 */
#define    TBIT_TCB_TSTAT       8    /* tstat �ե�����ɤΥӥå��� */
#define    TBIT_TCB_PRIORITY    8    /* priority �ե�����ɤΥӥå��� */

#ifndef _MACRO_ONLY
/*
 *  ����������ƥ����ȥ֥�å������
 */
typedef struct task_context_block {
    VP    sp;        /* �����å��ݥ��� */
    FP    pc;        /* �ץ���५���� */
} CTXB;

/*
 * �����ߤΥͥ��Ȳ���Υ������
 */
extern UW interrupt_count;


/*
 *  �����ƥ���ֻ���
 */
Inline UB
current_mode()
{
    return(current_sr() & CPSR_MODE_MASK);
}

Inline BOOL
sense_context()
{
    return(interrupt_count > 0);
}

Inline BOOL
sense_lock()
{
    return(current_sr() & CPSR_IRQ_BIT);
}

#define t_sense_lock    sense_lock
#define i_sense_lock    sense_lock


/*
 *  CPU��å��Ȥ��β��
 *
 */

#define t_lock_cpu      lock_cpu
#define i_lock_cpu      lock_cpu
#define t_unlock_cpu    unlock_cpu
#define i_unlock_cpu    unlock_cpu


Inline void
lock_cpu()
{
    disint();
}

Inline void
unlock_cpu()
{
    enaint();
}


/*
 *  �������ǥ����ѥå���
 */

/*
 *  �ǹ�ͥ���̥������ؤΥǥ����ѥå���cpu_support.S��
 *
 *  dispatch �ϡ�����������ƥ����Ȥ���ƤӽФ��줿�����ӥ����������
 *  ��ǡ�CPU��å����֤ǸƤӽФ��ʤ���Фʤ�ʤ���
 */
extern void    dispatch(void);


/*
 *  ���ߤΥ���ƥ����Ȥ�ΤƤƥǥ����ѥå���cpu_support.S��
 *
 *  exit_and_dispatch �ϡ�CPU��å����֤ǸƤӽФ��ʤ���Фʤ�ʤ���
 */
extern void    exit_and_dispatch(void);


#ifndef VECTOR_IN_ROM
/*
 * �㳰�٥����˽񤭹��ޤ줿������̿�᤬���Ȥ��륢�ɥ쥹
 */
extern UW * arm_vector_add[8];


/*
 * �㳰�˱������ϥ�ɥ�ε�ư����
 */
extern UW arm_handler_add[8];
#endif /* VECTOR_IN_ROM */

/*
 *  CPU�㳰�ϥ�ɥ������
 */
extern void define_exc(EXCNO excno, FP exchdr);


#ifndef VECTOR_IN_ROM
Inline void
arm_install_handler(EXCNO excno, FP exchdr)
{
    *arm_vector_add[excno] = (UW)exchdr;
}
#endif /* VECTOR_IN_ROM */

/*
 *  CPU�㳰�ϥ�ɥ�ν���������
 */


/*
 *  CPU�㳰�ϥ�ɥ�ν����������������ޥ���
 *
 */
#define __EXCHDR_ENTRY(exchdr, stacktop)    \
extern void exchdr##_entry(VP sp);          \
asm(".text                             \n"  \
#exchdr "_entry:                       \n"  \
"       ldr   sp,.int_stack_"#exchdr"  \n"  /* �����å����ڤ��ؤ�        */\
"       sub   lr,lr,#4                 \n"  /* undef�Ǥ⤳��Ǥ�����?    */\
"       stmfd sp!, {r0 - r2,lr}        \n"  /* ���Ū��int_stack������   */ \
"       mrs   r1, spsr                 \n"  /* SVC�⡼�ɤ��ڤ��ؤ��뤿�� */ \
"       mov   r0, sp                   \n"  /* ��¸����                  */ \
"       mov   r2,#0xd3                 \n"  /* CPSR�ν񤭴���(SVC�⡼�ɤ�)*/ \
"       msr   cpsr,r2                  \n" \
"       ldr   r2,[r0,#0x0C]            \n"     /* load  PC            */\
"       stmfd sp!,{r2}                 \n"     /* Store PC            */\
"       stmfd sp!,{r3,ip,lr}           \n"     /* Store r3,ip,lr      */\
"       ldmfd r0!,{r2,ip,lr}           \n"     /* load  r0,r1,r2      */\
"       stmfd sp!,{r1,r2,ip,lr}        \n"     /* SPSR,Store r0,r1,r2 */\
"       ldr   r2, .interrupt_count_"#exchdr"\n" /* ¿�ų����ߤ�Ƚ��  */\
"       ldr   r3, [r2]                 \n" \
"       add   r0,r3,#1                 \n" \
"       str   r0, [r2]                 \n" \
"       mov   r0,sp                    \n" /* �㳰�ϥ�ɥ�ؤΰ��� */\
"       cmp   r3, #0x00                \n" \
"       ldreq   sp,stack_"#exchdr"     \n" /* �����å����ѹ�       */\
"       stmeqfd sp!,{r0}               \n" /* �����������å�����¸ */\
"       and   r2, r1, #0xc0            \n" /* �㳰ȯ������CPU��å�����(IRQ) */\
"       orr   r2, r2, #0x13            \n" /* ��FIQ��Ѿ�. SVC�⡼�� */\
"       msr   cpsr,r2                  \n" \
"       bl    "#exchdr"                \n" /* �ϥ�ɥ�ƤӽФ�     */\
"       mrs   r2, cpsr                 \n" /* FIQ��Ѿ�            */\
"       and   r2, r2, #0x40            \n" /*                      */\
"       orr   r2, r2, #0x93            \n" /* �����߶ػ�         */\
"       msr   cpsr,r2                  \n" \
"       ldr   r2,.interrupt_count_"#exchdr" \n"/* �����߲����   */\
"       ldr   r1, [r2]                 \n"     /* �ǥ������     */\
"       sub   r3,r1,#1                 \n"\
"       str   r3, [r2]                 \n"\
"       cmp   r3,#0x00                 \n" /* �����ߥͥ��ȿ�?    */\
"       bne   return_to_task_"#exchdr" \n" \
"       ldmfd sp!,{r0}                 \n" /* �����������å������� */\
"       mov   sp, r0                   \n"\
"       ldr   r1, reqflg_"#exchdr"     \n" /* Check reqflg         */\
"       ldr   r0,[r1]                  \n"\
"       cmp   r0,#0                    \n"\
"       beq   return_to_task_"#exchdr" \n"\
"       mov   r0,#0                    \n"\
"       str   r0,[r1]                  \n" /* Clear reqflg   */\
"       b     _kernel_ret_exc          \n" /* ret_int��      */\
"return_to_task_"#exchdr":             \n" \
"       ldmfd sp!,{r1}                 \n" /* CPSR���������� r1 <- cpsr*/\
"       mrs   r2, cpsr                 \n" /* FIQ��Ѿ�            */\
"       and   r2, r2, #0x40            \n" /*                      */\
"       and   r1, r1, #~0x40           \n" /*                      */\
"       orr   r1, r1, r2               \n" /*                      */\
"       msr   spsr, r1                 \n" /* �����ߵ���   */\
"       ldmfd sp!,{r0-r3,ip,lr,pc}^    \n"\
"       .align 4                       \n"\
".int_stack_"#exchdr":                 \n"\
"       .long _kernel_int_stack + 6 * 4 \n"\
"reqflg_"#exchdr":                     \n"\
"       .long     _kernel_reqflg       \n"\
"stack_"#exchdr":                      \n"\
"       .long   " #stacktop "          \n"\
".interrupt_count_"#exchdr":            \n"\
"       .long   _kernel_interrupt_count \n")


#define _EXCHDR_ENTRY(exchdr, stacktop)    __EXCHDR_ENTRY(exchdr, stacktop)

#define EXCHDR_ENTRY(exchdr)    _EXCHDR_ENTRY(exchdr, STACKTOP)

#define EXC_ENTRY(exchdr) exchdr##_entry


/*
 *  CPU�㳰��ȯ���������Υ����ƥ���֤λ���
 */

/*
 *  CPU�㳰��ȯ���������Υǥ����ѥå�
 */
Inline BOOL
exc_sense_context(VP p_excinf)
{
    return(interrupt_count > 1);    
}


/*
 *  CPU�㳰��ȯ����������CPU��å����֤λ���
 */
Inline BOOL
exc_sense_lock(VP p_excinf)
{
    return((*((UW *)p_excinf) & CPSR_IRQ_BIT) == CPSR_IRQ_BIT );
}


/*
 * ̤������㳰�����ä����
 */
extern void undef_exception();
extern void swi_exception();
extern void prefetch_exception();
extern void data_abort_exception();
extern void irq_abort_exception();
extern void fiq_abort_exception();


/*
 *  �ץ��å���¸�ν����
 */
extern void    cpu_initialize(void);


/*
 *  �ץ��å���¸�ν�λ������
 */
extern void    cpu_terminate(void);


/*
 * CPU/����ߥϥ�ɥ�ν�����������ǰ��Ū�˻��Ѥ��륹���å�
 */
#define INT_STACK_SIZE 6
extern UW int_stack[INT_STACK_SIZE];


#endif /* _MACRO_ONLY */
#if 0
#else /* patch */
#define COPYRIGHT_CPU \
"Copyright (C) 2007-     by Monami Software Limited Partnership, JAPAN\n"
#endif
#endif /* _CPU_CONFIG_H_ */
