

@
@  IRQ wrappers.
@
@  These call a C function.
@  We switch to supervisor mode and reenable interrupts to allow nesting.
@
@
#if 0
#else /* patch */
#define _MACRO_ONLY
#include "jsp_kernel.h"
#include <at91sam7s.h>
#endif

  .text
  .code 32
  .align   2

@
@  Macros
@

#if 0
  .macro   irq_wrapper_nested, C_function
#else /* patch */
  .macro   irq_wrapper_nested, C_function jsp_inhno
#endif

@ Save registers on stack
  sub r14,r14,#4 @ fix up for return
  stmfd r13!,{r14}
  mrs  r14,spsr
  stmfd r13!,{r14}

@ Acknowledge the IVR for debugging to support Protected Mode
  ldr   r14,=0xFFFFF100
  str   r14,[r14]

 @ swich to system mode and enable IRQ, but not FIQ
  msr cpsr_c,#0x5F

  @push stack
  stmfd r13!,{r0-r12,r14}


@ Call the function
  ldr r0,=\C_function
  mov lr,pc
  bx  r0

  @ pop stack
#if 0
#else /* patch */
	ldr r0, =iniflg
	ldr r1, [r0]
	cmp r1, #0
#endif
   ldmfd r13!,{r0-r12,r14}
#if 0
#else /* patch */
	bne 0f
#endif

 @ swich to interrupt mode and disable IRQs and FIQs
  msr cpsr_c,#0xD2

@End of interrupt by doing a write to AIC_EOICR
  ldr  r14,=0xFFFFF130
  str  r14,[r14]

  @ Unstack the saved spsr
  ldmfd r13!,{r14}
  msr  spsr_all,r14

  @ Return from interrupt (unstacking the modified r14)
  ldmfd r13!,{pc}^

#if 0
#else /* patch */
0:

        /* 
         *  タスクの動作時モード(スーパーバイザーモード)へ
         */
#if 0
        mov     sp,#(CPSR_SVC | CPSR_FIQ_BIT | CPSR_IRQ_BIT) 
        msr     cpsr_all, sp
#else /* patch */
        msr     cpsr_all, #(CPSR_SVC | CPSR_FIQ_BIT | CPSR_IRQ_BIT)
#endif
        stmfd   sp!, {r0-r3,ip,lr,pc} /* pcはダミー */


        /*
         * spsrと戻り番地を取得するためにIRQモードへ
         */
        mov     r0,#(CPSR_IRQ | CPSR_FIQ_BIT | CPSR_IRQ_BIT)
        msr     cpsr,r0
#if 0
        sub     r0,lr,#4
        mrs     r1,spsr
#else /* patch */
	ldmfd r13!, {r1}
	ldmfd r13!, {r0}
#endif

        /*
         *  スーパーバイザーモードに
         */
        and     r2,  r1, #CPSR_FIQ_BIT /* FIQビットの継承 */
        orr     r2,  r2, #(CPSR_SVC|CPSR_IRQ_BIT)
        msr     cpsr_all, r2
        str     r0, [sp,#0x18] /* Store pc */
        stmfd   sp!,{r1}       /* spsr */


        /*
         *  多重割り込みか判定
         */
        ldr     r2, =interrupt_count
        ldr     r3, [r2]
        add     r0,r3,#1
        str     r0, [r2]
        cmp     r3, #0x00

        moveq   r2,sp            /* ネスト割り込みでない場合 */
#if 0
        ldreq   sp,=STACKTOP     /* スタックの変更    */
#else /* patch */
        ldreq   sp,=(nontask_stack + NONTASK_STACK_SIZE)     /* スタックの変更    */
#endif
        stmeqfd sp!,{r2}         /* タスクスタックの保存 */

        /*
         *  割り込み要因の判定．
         */
#if 0
        ldr     r3, =TADR_AIC_BASE
        ldr     r0, [r3, #TOFF_AIC_IVR]
        str     r3, [r3, #TOFF_AIC_IVR]
#else /* patch */
	ldr r0, =int_table
	ldr r1, [r0, #(\jsp_inhno * 4)]
	cmp r1, #0
	beq 1f
#endif

        /*
         * 割り込み許可
         */
        mrs     r2, cpsr
        and     r2,  r2, #~CPSR_IRQ_BIT /* 割込み許可 */
        msr     cpsr,r2

        /*
         * Call Handler
         */
        mov     lr,  pc
#if 0
        mov     pc,  r0
#else /* patch */
	bx r1
#endif

        /* 
         * 割り込み禁止 
         */
        mrs     r2, cpsr
        and     r2,  r2, #CPSR_FIQ_BIT /* FIQビットの継承 */
        orr     r2,  r2, #(CPSR_SVC|CPSR_IRQ_BIT)
        msr     cpsr,r2

#if 0
#else /* patch */
1:
#endif
        /*
         * 割込みクリア
         */
        ldr     r3, =TADR_AIC_BASE
        mov     r0, #0
        str     r0, [r3, #TOFF_AIC_EOICR]

        /* 
         * 割込みネスト回数(interrupt_count) デクリメント 
         */
        ldr     r2, =interrupt_count
        ldr     r1, [r2]
        sub     r3, r1, #1
        str     r3, [r2]
        cmp     r3, #0x00
#if 0
        bne     return_to_task_irq
#else /* patch */
        bne     2f
#endif

        /* 
         * タスクスタックの復帰 
         */
        ldmfd   sp!,{r0}
        mov     sp, r0

        ldr     r1, =reqflg    /* Check reqflg */
        ldr     r0, [r1]
        cmp     r0, #0
#if 0
        beq     return_to_task_irq
#else /* patch */
        beq     2f
#endif
        mov     r0, #0
        str     r0, [r1]       /* Clear reqflg */
        b       ret_int

#if 0
return_to_task_irq:
#else /* patch */
2:
#endif
        /*
         *  復帰処理
         *  割り込み許可となるがタスクコンテキスト上に保存しているため，
         *  問題はない
         */
        ldmfd   sp!,{r1}           /* CPSRの復帰処理 */
        mrs     r2, cpsr           /* FIQを継承            */
        and     r2, r2, #CPSR_FIQ_BIT
        and     r1, r1, #~CPSR_FIQ_BIT
        orr     r1, r1, r2
        msr     spsr, r1           /* 割り込み許可   */
        ldmfd   sp!,{r0-r3,ip,lr,pc}^ /*タスク復帰 + 割込み許可 */
#endif
  .endm

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
  .macro   irq_wrapper_not_nested, C_function

@ Save registers on stack
  sub r14,r14,#4 @ fix up for return
  stmfd r13!,{r0-r12,r14}

@ Acknowledge the IVR for debugging to support Protected Mode
  ldr   r14,=0xFFFFF100
  str   r14,[r14]

@ Call the function
  ldr r0,=\C_function
  mov lr,pc
  bx  r0

@End of interrupt by doing a write to AIC_EOICR
  ldr  r14,=0xFFFFF130
  str  r14,[r14]

  @ Return from interrupt (unstacking the modified r14)
  ldmfd r13!,{r0-r12,pc}^

  .endm

@
@	ISRs
@
@


	.global spurious_isr
	.global default_isr
	.global default_fiq
default_fiq:
spurious_isr:
default_isr:
	b default_isr

  .extern systick_isr_C
  .global systick_isr_entry
systick_isr_entry:
#if 0
  irq_wrapper_nested systick_isr_C
#else /* patch */
  irq_wrapper_nested systick_isr_C IRQ_SYSIRQ_PID
#endif

  .extern systick_low_priority_C
  .global systick_low_priority_entry
systick_low_priority_entry:
#if 0
  irq_wrapper_nested systick_low_priority_C
#else /* patch */
  irq_wrapper_nested systick_low_priority_C IRQ_PWM_PID
#endif

  .extern udp_isr_C
  .global udp_isr_entry
udp_isr_entry:
#if 0
  irq_wrapper_nested udp_isr_C
#else /* patch */
  irq_wrapper_nested udp_isr_C IRQ_UDP_PID
#endif

  .extern spi_isr_C
  .global spi_isr_entry
spi_isr_entry:
#if 0
  irq_wrapper_nested spi_isr_C
#else /* patch */
  irq_wrapper_nested spi_isr_C IRQ_SPI_PID
#endif

  .extern twi_isr_C
  .global twi_isr_entry
twi_isr_entry:
#if 0
  irq_wrapper_nested twi_isr_C
#else /* patch */
  irq_wrapper_nested twi_isr_C IRQ_TWI_PID
#endif
  
  .extern sound_isr_C
  .global sound_isr_entry
sound_isr_entry:
#if 0
  irq_wrapper_nested sound_isr_C
#else /* patch */
  irq_wrapper_nested sound_isr_C IRQ_SSC_PID
#endif

  .extern uart_isr_C_0
  .global uart_isr_entry_0
uart_isr_entry_0:
#if 0
  irq_wrapper_nested uart_isr_C_0
#else /* patch */
  irq_wrapper_nested uart_isr_C_0 IRQ_US0_PID
#endif

  .extern uart_isr_C_1
  .global uart_isr_entry_1
uart_isr_entry_1:
#if 0
  irq_wrapper_nested uart_isr_C_1
#else /* patch */
  irq_wrapper_nested uart_isr_C_1 IRQ_US1_PID
#endif

  .extern nxt_motor_isr_C
  .global nxt_motor_isr_entry
nxt_motor_isr_entry:
#if 0
  irq_wrapper_nested nxt_motor_isr_C
#else /* patch */
  irq_wrapper_nested nxt_motor_isr_C IRQ_PIOA_PID
#endif


  .extern i2c_timer_isr_C
  .global i2c_timer_isr_entry
i2c_timer_isr_entry:
#if 0
  irq_wrapper_nested i2c_timer_isr_C
#else /* patch */
  irq_wrapper_nested i2c_timer_isr_C IRQ_TC0_PID
#endif

#if 0
#else /* patch */
	.text
	.align 2
	.global lejos_osek_run
lejos_osek_run:
	msr cpsr, #(CPSR_IRQ_BIT | CPSR_FIQ_BIT | CPSR_SVC)
	ldr sp, =(nontask_stack + NONTASK_STACK_SIZE)
	b kernel_start
	.text
	.align 2
	.global lejos_osek_stop
lejos_osek_stop:
	msr cpsr, #(CPSR_IRQ_BIT | CPSR_FIQ_BIT | CPSR_SVC)
	ldr r0, =TADR_PIT_BASE
	mov r1, #0
	str r1, [r0, #TOFF_PIT_MR]
	b start
#endif
