
        �� TOPPERS/JSP�����ͥ� �桼�����ޥ˥奢�� ��
                    ��GHS�ǥХå��Ķ���

        ��Release 1.4 �б����ǽ�����: 24-Dec-2003��

------------------------------------------------------------------------
 TOPPERS/JSP Kernel
     Toyohashi Open Platform for Embedded Real-Time Systems/
     Just Standard Profile Kernel

 Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
                             Toyohashi Univ. of Technology, JAPAN
 Copyright (C) 2003 by Advanced Data Controls, Corp

 �嵭����Ԥϡ��ʲ��� (1)��(4) �ξ�狼��Free Software Foundation 
 �ˤ�äƸ�ɽ����Ƥ��� GNU General Public License �� Version 2 �˵�
 �Ҥ���Ƥ���������������˸¤ꡤ�ܥ��եȥ��������ܥ��եȥ�����
 ����Ѥ�����Τ�ޤࡥ�ʲ�Ʊ���ˤ���ѡ�ʣ�������ѡ������ۡʰʲ���
 ���ѤȸƤ֡ˤ��뤳�Ȥ�̵���ǵ������롥
 (1) �ܥ��եȥ������򥽡��������ɤη������Ѥ�����ˤϡ��嵭������
     ��ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ��꤬�����Τޤޤη��ǥ���
     ����������˴ޤޤ�Ƥ��뤳�ȡ�
 (2) �ܥ��եȥ������򡤥饤�֥������ʤɡ�¾�Υ��եȥ�������ȯ�˻�
     �ѤǤ�����Ǻ����ۤ�����ˤϡ������ۤ�ȼ���ɥ�����ȡ�����
     �ԥޥ˥奢��ʤɡˤˡ��嵭�����ɽ�����������Ѿ�浪��Ӳ���
     ��̵�ݾڵ����Ǻܤ��뤳�ȡ�
 (3) �ܥ��եȥ������򡤵�����Ȥ߹���ʤɡ�¾�Υ��եȥ�������ȯ�˻�
     �ѤǤ��ʤ����Ǻ����ۤ�����ˤϡ����Τ����줫�ξ�����������
     �ȡ�
   (a) �����ۤ�ȼ���ɥ�����ȡ����Ѽԥޥ˥奢��ʤɡˤˡ��嵭����
       �ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ����Ǻܤ��뤳�ȡ�
   (b) �����ۤη��֤��̤�������ˡ�ˤ�äơ�TOPPERS�ץ������Ȥ�
       ��𤹤뤳�ȡ�
 (4) �ܥ��եȥ����������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������뤤���ʤ�»
     ������⡤�嵭����Ԥ����TOPPERS�ץ������Ȥ����դ��뤳�ȡ�

 �ܥ��եȥ������ϡ�̵�ݾڤ��󶡤���Ƥ����ΤǤ��롥�嵭����Ԥ�
 ���TOPPERS�ץ������Ȥϡ��ܥ��եȥ������˴ؤ��ơ�����Ŭ�Ѳ�ǽ����
 �ޤ�ơ������ʤ��ݾڤ�Ԥ�ʤ����ޤ����ܥ��եȥ����������Ѥˤ��ľ
 ��Ū�ޤ��ϴ���Ū�������������ʤ�»���˴ؤ��Ƥ⡤������Ǥ�����ʤ���
------------------------------------------------------------------------

���Υɥ�����ȤǤϡ�TOPPERS/JSP��Green Hills Software(GHS)�Ҥ���ȯ�������糫ȯ�Ķ�MULTI�Ǥι��ۤ�ɬ�פʥե�����ˤĤ��Ʋ��⤹�롣

1. �ǥ��쥯�ȥ�ι���

jsp
  +--config
  |     +---armv4-ghs
  |     |      +---integrator
  |     +---sh3-ghs
  |            +---ms7727cp01
  |            +---solution_engine
  +--tools
        +-----GHS
               +---ghs_hook_bld
               +---kernel_bld
               +---sample


2.�б��ץ��å�

��SH3(solution engine��ms7727)
��armv4(Integrator/AP������ARM966ES��ARM920T)


3.���ǥ��쥯�ȥ�ȥե����������

GNU�Ķ��Ǥμ����Ȱۤʤ�ե������config/armv4-ghs�ޤ���config/sh3-ghs�ǥ��쥯�ȥ���֤���Ƥ��롣
�ޤ���tools/GHS�ǥ��쥯�ȥ�ˤϥ����ͥ�ʤɤ�ӥ�ɤ��뤿��Υե������GHS��ȯ�Ķ��˰�¸����ե����뤬�֤���Ƥ��롣

3.1 config/armv4-ghs

a. armv4t-ghs.bld ---- armv4��¸����integrator�Υӥ�ɥե�����
b. integrator/integrator.bld ---- integrator��¸���Υӥ�ɥե�����
c. ����¾ ---- armv4��¸���Υ�����
armv4t-ghs.bld����integrator.bld�����󥯥롼�ɤ���Ƥ��ꡢarmv4t-ghs.bld��ץ������Ȥ˥��󥯥롼�ɤ���С���ưŪ��integrator.bld�����󥯥롼�ɤ���롣

3.2 config/sh3-ghs

a. sh3_ms7727-ghs.bld ---- sh3��ms7727��¸���Υӥ�ɥե�����
b. sh3_solution-ghs.bld ---- sh3��solution_engine��¸���Υӥ�ɥե�����
c. ms7727cp01/ms7727cp01.bld ---- ms7727��¸���Υӥ�ɥե�����
d. solution_engine/solution.bld ---- solution_engine��¸���Υӥ�ɥե�����

sh3_ms7727-ghs.bld����ms7727cp01.bld�����󥯥롼�ɤ���Ƥ��ꡢsh3_ms7727-ghs.bld��ץ������Ȥ˥��󥯥롼�ɤ���С���ưŪ��ms7727cp01.bld�����󥯥롼�ɤ���롣sh3_solution.bld��Ʊ�ͤǤ��롣

3.3 tools/GHS/kernel_bld

���Υǥ��쥯�ȥ�ϥ����ͥ�䥷���������ʤɤ�ӥ�ɤ��뤿��Υե����뤬�֤���Ƥ��롣

a. kernel.bld ---- �����ͥ��饤�֥��˥ӥ�ɤ��뤿��Υե����롣���Υӥ�ɥե�����ˤϰʲ��Υӥ�ɥե����뤬�ޤޤ�Ƥ��롣
 �� cyclic.bld 
 �� dataqueue.bld 
 �� eventflag.bld
 �� exception.bld
 �� interrupt.bld
 �� mailbox.bld
 �� mempfix.bld
 �� semaphore.bld
 �� sys_manage.bld
 �� syslog.bld
 �� task.bld
 �� task_except.bld
 �� task_manage.bld
 �� task_sync.bld
 �� time_event.bld
 �� time_manage.bld
 �� wait.bld

kernel.bld��ץ������Ȥ˥��󥯥롼�ɤ���С���ưŪ�˥����ͥ�Υ饤�֥�꤬�ץ������Ȥ˥��󥯥롼�ɤ��졢�ץ������Ȥ�ӥ�ɤ���ȥ����ͥ��ӥ�ɤ���롣kernel.bld���������Τ��ᡢCPU���ץ����䥤�󥯥롼�ɥե�����Υ������ѡ����ʤɤ����ꤵ��Ƥ��餺��ñ�ȤǤϥӥ�ɤǤ��ʤ��������ͥ������ӥ�ɤ����硢kernel.bld�����򥤥󥯥롼�ɤ��Ƥ����̤Υӥ�ɥե����������������Υӥ�ɥե������CPU���ץ����䥵�����ѡ���������򤹤���ɤ���

b. library.bld ---- log_output.c, strerror.c, t_perror.c, vasyslog.c�򥪥֥������Ȥ˥ӥ�ɤ��뤿��Υե�����Ǥ��롣

c. systask.bld ---- serial.c, timer.c, logtask.c �򥪥֥������ȥե�����˥ӥ�ɤ��뤿��Υե�����Ǥ��롣



3.4  tools/GHS/ghs_hook_bld

���Υǥ��쥯�ȥ�ϥȥ졼�����ޥ���ʤɤΥ����ͥ�ΥǥХå������MULTI�ǥХå���ɽ�������뤿��Υ����ɤ��֤���Ƥ��롣

a. ghs_hook.bld ---- �ǥХå������ɽ������뤿��Υ����ɤΥӥ�ɥե�����
b. ����¾ ---- �ǥХå������ɽ������뤿��Υ�����

�ȥ졼�����ޥ���ǽ����Ѥ���ʤ�ץ������ȤΥӥ�ɥե�����Υե����륪�ץ�����GHS_HOOK��������ʤ���Фʤ�ʤ�������ˡ�GHS_HOOK=2����ꤹ��ȥȥ졼���ǡ����ϡ�ɬ�פʤ�Τ��������򤷤Ƽ������뤳�Ȥ��Ǥ��ޤ���GHS_HOOK=1���ǥե���Ȥǡ����ƤΥȥ졼���ǡ�������������롣

BUFF_SIZE=xxx���������С��ȥ졼�����ޥ����ѤΥХåե������������Ǥ��롣��������BUFF_SIZE ��ɬ����1024(1kbyte) , 2048(2kbyte) , 4096(4kbyte) , 8192(8kbyte) , 16384(16kbyte) ���椫����ꤷ�Ƥ���������BUFF_SIZE�Υǥե�����ͤ�16kbyte�Ǥ��롣


3.5 tools/GHS/sample

���Υǥ��쥯�ȥ�ϥ���ץ�ץ����Υ����ɤΥӥ�ɥե����뤬�֤���Ƥ��롣

a. arm920t.bld ---- Integrator/ARM920T�ѤΥ���ץ�ץ����Υӥ�ɥե�����
b. solution_engine.bld ---- SH3/Solution Engine�ѤΥ���ץ�ץ����Υӥ�ɥե�����
c. linker_arm.lnk ---- ARMV4�Υ�󥫡��ե�����
d. linker_sh3.lnk ---- SH3�Υ�󥫡��ե�����
e. kernel.bld ---- 3.3��򻲾�
f. systask.bld ---- 3.3��򻲾�
g. library.bld ---- 3.3��򻲾�
h. armv4t-ghs.bld�ޤ���sh3_solution-ghs.bld ---- 3.1��ޤ���3.2��򻲾�
i. user_program.bld --- ����ץ�ץ����Υ����ɤΥӥ�ɥե����롣
j. configuration.bld --- ����ե�����졼�����ե������������뤿��Υӥ�ɥե�����
k. ����¾ --- ����ץ�ץ����Υ�����

arm920t.bld�ޤ���solution_engine.bld�ι����ϰʲ��˼�����

arm920t.bld/solution_engine.bld
    |-------kernel.bld
    |-------systask.bld
    |-------library.bld
    |-------armv4t-ghs.bld/sh3_solution-ghs.bld
    |-------ghs_hook.bld
    |-------user_program.bld
    |------------|---configuration.bld
    |------------|---------|----sample1.cfg
    |------------|----sample1.c
    |------------|----sample1.h
    |-------linker_arm.lnk/linker_sh3.lnk


��1��˼������ǥ��쥯�ȥ깽���Ǥϡ�arm920t.bld�ޤ���solution_engine.bld�򲿤��ѹ����ʤ��ǥӥ�ɤǤ��뤬���ǥ��쥯�ȥ�ι������ۤʤ��硢�������ѡ������Ѥ���ɬ�פ����롣

