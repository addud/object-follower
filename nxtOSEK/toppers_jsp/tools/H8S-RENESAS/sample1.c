/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2004 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
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
 *  @(#) $Id: sample1.c,v 1.6 2007/04/02 03:14:01 honda Exp $
 */

/* 
 *  ����ץ�ץ����(1)������
 *
 *  JSP�����ͥ�δ���Ū��ư����ǧ���뤿��Υ���ץ�ץ���ࡥ
 *
 *  �ץ����γ���:
 *
 *  �桼�����󥿥ե�������������ĥᥤ�󥿥����ʥ�����ID: MAIN_TASK��
 *  ͥ����: MAIN_PRIORITY�ˤȡ����Ĥ�����¹Ԥ���륿�����ʥ�����ID:
 *  TASK1��TASK3�����ͥ����: MID_PRIORITY�ˤǹ�������롥�ޤ�����ư��
 *  ����2�äμ����ϥ�ɥ�ʼ����ϥ�ɥ�ID: CYCHDR1�ˤ��Ѥ��롥
 *
 *  ����¹Ԥ���륿�����ϡ�task_loop ����롼�פ�¹Ԥ����٤ˡ�������
 *  ���¹���Ǥ��뤳�Ȥ򤢤�魯��å�������ɽ�����롥
 *
 *  �����ϥ�ɥ�ϡ����Ĥ�ͥ���١�HIGH_PRIORITY��MID_PRIORITY��
 *  LOW_PRIORITY�ˤΥ�ǥ����塼���ž�����롥�ץ����ε�ưľ��ϡ�
 *  �����ϥ�ɥ����߾��֤ˤʤäƤ��롥
 *
 *  �ᥤ�󥿥����ϡ����ꥢ��I/O�ݡ��Ȥ����ʸ�����Ϥ�Ԥ���ʸ�����Ϥ�
 *  �ԤäƤ���֤ϡ�����¹Ԥ���륿�������¹Ԥ���Ƥ���ˡ����Ϥ��줿
 *  ʸ�����б�����������¹Ԥ��롥���Ϥ��줿ʸ���Ƚ����δط��ϼ����̤ꡥ
 *  Control-C �ޤ��� 'Q' �����Ϥ����ȡ��ץ�����λ���롥
 *
 *  '1' : �ʹߤΥ��ޥ�ɤ� TASK1 ���Ф��ƹԤ���
 *  '2' : �ʹߤΥ��ޥ�ɤ� TASK2 ���Ф��ƹԤ���
 *  '3' : �ʹߤΥ��ޥ�ɤ� TASK3 ���Ф��ƹԤ���
 *  'a' : �������� act_tsk �ˤ�굯ư���롥
 *  'A' : ���������Ф��뵯ư�׵�� can_act �ˤ�ꥭ��󥻥뤹�롥
 *  'e' : �������� ext_tsk ��ƤӽФ�������λ�����롥
 *  't' : �������� ter_tsk �ˤ�궯����λ���롥
 *  '>' : ��������ͥ���٤� HIGH_PRIORITY �ˤ��롥
 *  '=' : ��������ͥ���٤� MID_PRIORITY �ˤ��롥
 *  '<' : ��������ͥ���٤� LOW_PRIORITY �ˤ��롥
 *  'G' : ��������ͥ���٤� get_pri ���ɤ߽Ф���
 *  's' : �������� slp_tsk ��ƤӽФ����������Ԥ��ˤ����롥
 *  'S' : �������� tslp_tsk(10��) ��ƤӽФ����������Ԥ��ˤ����롥
 *  'w' : �������� wup_tsk �ˤ�굯�����롥
 *  'W' : ���������Ф��뵯���׵�� can_wup �ˤ�ꥭ��󥻥뤹�롥
 *  'l' : �������� rel_wai �ˤ�궯��Ū���Ԥ�����ˤ��롥
 *  'u' : �������� sus_tsk �ˤ�궯���Ԥ����֤ˤ��롥
 *  'm' : �������ζ����Ԥ����֤� rsm_tsk �ˤ�������롥
 *  'M' : �������ζ����Ԥ����֤� frsm_tsk �ˤ�궯��������롥
 *  'd' : �������� dly_tsk(10��) ��ƤӽФ��������ַв��Ԥ��ˤ����롥
 *  'x' : �������˥ѥ����� 0x0001 ���㳰�������׵᤹�롥
 *  'X' : �������˥ѥ����� 0x0002 ���㳰�������׵᤹�롥
 *  'y' : �������� dis_tex ��ƤӽФ������������㳰��ػߤ��롥
 *  'Y' : �������� ena_tex ��ƤӽФ������������㳰����Ĥ��롥
 *  'r' : ���Ĥ�ͥ���١�HIGH_PRIORITY��MID_PRIORITY��LOW_PRIORITY�ˤ�
 *        ��ǥ����塼���ž�����롥
 *  'c' : �����ϥ�ɥ��ư����롥
 *  'C' : �����ϥ�ɥ����ߤ����롥
 *  'z' : CPU�㳰��ȯ�������롥
 *  'Z' : �ץ�����λ���롥
 *  'V' : vxget_tim ����ǽɾ���ѥ����ƥ�����2���ɤࡥ
 *  'v' : ȯ�Ԥ��������ƥॳ�����ɽ������ʥǥե���ȡˡ�
 *  'q' : ȯ�Ԥ��������ƥॳ�����ɽ�����ʤ���
 */

#include <t_services.h>
#include "kernel_id.h"
#include "sample1.h"

/*
 *  �¹Լ¹Ԥ���륿�����ؤΥ�å������ΰ�
 */
char	message[3];

/*
 *  �롼�ײ��
 */
UW	task_loop;		/* ��������ǤΥ롼�ײ�� */
UW	tex_loop;		/* �㳰�����롼������ǤΥ롼�ײ�� */

/*
 *  �¹Լ¹Ԥ���륿����
 */
void task(VP_INT exinf)
{
	volatile UW	i;
	INT		n = 0;
	INT		tskno = (INT) exinf;
	const char	*graph[] = { "|", "  +", "    *" };
	char		c;

	ena_tex();
	while (1) {
		syslog(LOG_NOTICE, "task%d is running (%03d).   %s",
					tskno, ++n, graph[tskno-1]);
		for (i = 0; i < task_loop; i++);
		c = message[tskno-1];
		message[tskno-1] = 0;
		switch (c) {
		case 'e':
			syslog(LOG_INFO, "#%d#ext_tsk()", tskno);
			ext_tsk();
		case 's':
			syslog(LOG_INFO, "#%d#slp_tsk()", tskno);
			syscall(slp_tsk());
			break;
		case 'S':
			syslog(LOG_INFO, "#%d#tslp_tsk(10000)", tskno);
			syscall(tslp_tsk(10000));
			break;
		case 'd':
			syslog(LOG_INFO, "#%d#dly_tsk(10000)", tskno);
			syscall(dly_tsk(10000));
			break;
		case 'y':
			syslog(LOG_INFO, "#%d#dis_tex()", tskno);
			syscall(dis_tex());
			break;
		case 'Y':
			syslog(LOG_INFO, "#%d#ena_tex()", tskno);
			syscall(ena_tex());
			break;
#ifdef CPUEXC1
		case 'z':
			syslog(LOG_NOTICE, "#%d#raise CPU exception", tskno);
			RAISE_CPU_EXCEPTION;
			break;
#endif /* CPUEXC1 */
		case 'Z':
			syslog(LOG_NOTICE, "Sample program ends with exception.");
			kernel_exit();
			break;
		default:
			break;
		}
	}
}

/*
 *  �¹Ԥ��Ƽ¹Ԥ���륿�����ѤΥ������㳰�����롼����
 */
void tex_routine(TEXPTN texptn, VP_INT exinf)
{
	volatile UW	i;
	INT	tskno = (INT) exinf;

	syslog(LOG_NOTICE, "task%d receives exception 0x%04x. ",
					tskno, texptn);
	for (i = 0; i < tex_loop; i++);

	if (texptn & 0x8000) {
		syslog(LOG_INFO, "#%d#ext_tsk()", tskno);
		ext_tsk();
	}
}

/*
 *  CPU�㳰�ϥ�ɥ�
 */
#ifdef CPUEXC1

void
cpuexc_handler(VP p_excinf)
{
	ID	tskid;

	syslog(LOG_NOTICE, "CPU exception handler (p_excinf = %08p).",
							p_excinf);
	if (sns_ctx() != TRUE) {
		syslog(LOG_WARNING,
			"sns_ctx() is not TRUE in CPU exception handler.");
	}
	if (sns_dpn() != TRUE) {
		syslog(LOG_WARNING,
			"sns_dpn() is not TRUE in CPU exception handler.");
	}
	syslog(LOG_DEBUG,
		"sns_loc = %d sns_dsp = %d", (int)sns_loc(), (int)sns_dsp());
	syslog(LOG_DEBUG,
		"vxsns_loc = %d vxsns_ctx = %d vxsns_dsp = %d vxsns_dpn = %d",
		(int)vxsns_loc(p_excinf), (int)vxsns_ctx(p_excinf),
		(int)vxsns_dsp(p_excinf), (int)vxsns_dpn(p_excinf));

	if (!vxsns_loc(p_excinf) && !vxsns_ctx(p_excinf)) {
		syscall(iget_tid(&tskid));
		syscall(iras_tex(tskid, 0x8000));
	}
	else {
		syslog(LOG_NOTICE, "Sample program ends with exception.");
		kernel_exit();
	}
}

#endif /* CPUEXC1 */

/*
 *  �����ϥ�ɥ�
 *
 *  HIGH_PRIORITY��MID_PRIORITY��LOW_PRIORITY �γ�ͥ���٤Υ�ǥ����塼
 *  ���ž�����롥
 */
void cyclic_handler(VP_INT exinf)
{
	irot_rdq(HIGH_PRIORITY);
	irot_rdq(MID_PRIORITY);
	irot_rdq(LOW_PRIORITY);
}


#define PORTID_SCI2	3
#if PORTID_SCI2 == TASK_PORTID
#error PORTID_SCI2 == TASK_PORTID is not allowed.
#endif /*  PORTID_SCI2 == TASK_PORTID  */

static const char output_text[] = "This is SCI2 output test.";

/*
 *  �ᥤ�󥿥���
 */
void main_task(VP_INT exinf)
{
	char	c;
	ID	tskid = TASK1;
	volatile UW	i;
	INT	tskno = 1;
	ER_UINT	ercd;	
	PRI	tskpri;
	SYSTIM	stime1, stime2;
#ifndef OMIT_VGET_TIM
	SYSUTIM	utime1, utime2;
#endif /* OMIT_VGET_TIM */

	vmsk_log(LOG_UPTO(LOG_INFO), LOG_UPTO(LOG_EMERG));
	syslog(LOG_NOTICE, "Sample program starts (exinf = %d).", (int)exinf);
	syslog(LOG_NOTICE, "This program output low level log to port POL_PORTID");
	syscall(serial_ctl_por(TASK_PORTID,
			(IOCTL_CRLF | IOCTL_FCSND | IOCTL_FCRCV)));

	/*  SCI2�ؤν���  */
	syscall(serial_opn_por(PORTID_SCI2));
	syscall(serial_ctl_por(PORTID_SCI2,
			(IOCTL_CRLF | IOCTL_FCSND | IOCTL_FCRCV)));
	syscall(serial_wri_dat(PORTID_SCI2, output_text, sizeof(output_text)));
	
	/*
 	 *  �롼�ײ��������
	 */
	task_loop = LOOP_REF;
	get_tim(&stime1);
	for (i = 0; i < task_loop; i++);
	get_tim(&stime2);
	task_loop = LOOP_REF * 400 / (stime2 - stime1);
	tex_loop = task_loop / 5;

	/*
 	 *  �������ε�ư
	 */
	act_tsk(TASK1);
	act_tsk(TASK2);
	act_tsk(TASK3);

	/*
 	 *  �ᥤ��롼��
	 */
	do {
		syscall(serial_rea_dat(TASK_PORTID, &c, 1));
		switch (c) {
		case 'e':
		case 's':
		case 'S':
		case 'd':
		case 'y':
		case 'Y':
		case 'z':
		case 'Z':
			message[tskno-1] = c;
			break;
		case '1':
			tskno = 1;
			tskid = TASK1;
			break;
		case '2':
			tskno = 2;
			tskid = TASK2;
			break;
		case '3':
			tskno = 3;
			tskid = TASK3;
			break;
		case 'a':
			syslog(LOG_INFO, "#act_tsk(%d)", tskno);
			syscall(act_tsk(tskid));
			break;
		case 'A':
			syslog(LOG_INFO, "#can_act(%d)", tskno);
			syscall(ercd = can_act(tskid));
			if (ercd >= 0) {
				syslog(LOG_NOTICE, "can_act(%d) returns %d",
						tskno, ercd);
			}
			break;
		case 't':
			syslog(LOG_INFO, "#ter_tsk(%d)", tskno);
			syscall(ter_tsk(tskid));
			break;
		case '>':
			syslog(LOG_INFO, "#chg_pri(%d, HIGH_PRIORITY)", tskno);
			chg_pri(tskid, HIGH_PRIORITY);
			break;
		case '=':
			syslog(LOG_INFO, "#chg_pri(%d, MID_PRIORITY)", tskno);
			chg_pri(tskid, MID_PRIORITY);
			break;
		case '<':
			syslog(LOG_INFO, "#chg_pri(%d, LOW_PRIORITY)", tskno);
			chg_pri(tskid, LOW_PRIORITY);
			break;
		case 'G':
			syslog(LOG_INFO, "#get_pri(%d, &tskpri)", tskno);
			syscall(ercd = get_pri(tskid, &tskpri));
			if (ercd >= 0) {
				syslog(LOG_NOTICE, "priority of task %d is %d",
						tskno, tskpri);
			}
			break;
		case 'w':
			syslog(LOG_INFO, "#wup_tsk(%d)", tskno);
			syscall(wup_tsk(tskid));
			break;
		case 'W':
			syslog(LOG_INFO, "#can_wup(%d)", tskno);
			syscall(ercd = can_wup(tskid));
			if (ercd >= 0) {
				syslog(LOG_NOTICE, "can_wup(%d) returns %d",
						tskno, ercd);
			}
			break;
		case 'l':
			syslog(LOG_INFO, "#rel_wai(%d)", tskno);
			syscall(rel_wai(tskid));
			break;
		case 'u':
			syslog(LOG_INFO, "#sus_tsk(%d)", tskno);
			syscall(sus_tsk(tskid));
			break;
		case 'm':
			syslog(LOG_INFO, "#rsm_tsk(%d)", tskno);
			syscall(rsm_tsk(tskid));
			break;
		case 'M':
			syslog(LOG_INFO, "#frsm_tsk(%d)", tskno);
			syscall(frsm_tsk(tskid));
			break;
		case 'x':
			syslog(LOG_INFO, "#ras_tex(%d, 0x0001)", tskno);
			syscall(ras_tex(tskid, 0x0001));
			break;
		case 'X':
			syslog(LOG_INFO, "#ras_tex(%d, 0x0002)", tskno);
			syscall(ras_tex(tskid, 0x0002));
			break;
		case 'r':
			syslog(LOG_INFO, "#rot_rdq(three priorities)");
			rot_rdq(HIGH_PRIORITY);
			rot_rdq(MID_PRIORITY);
			rot_rdq(LOW_PRIORITY);
			break;
		case 'c':
			sta_cyc(CYCHDR1);
			break;
		case 'C':
			stp_cyc(CYCHDR1);
			break;
#ifndef OMIT_VGET_TIM
		case 'V':
			syscall(vxget_tim(&utime1));
			syscall(vxget_tim(&utime2));
			syslog(LOG_NOTICE, "utime1 = %d, utime2 = %d",
						(UINT) utime1, (UINT) utime2);
			break;
#endif /* OMIT_VGET_TIM */
		case 'v':
			vmsk_log(LOG_UPTO(LOG_INFO), LOG_UPTO(LOG_EMERG));
			break;
		case 'q':
			vmsk_log(LOG_UPTO(LOG_NOTICE), LOG_UPTO(LOG_EMERG));
			break;
		default:
			break;
		}
	} while (c != '\003' && c != 'Q');

	syslog(LOG_NOTICE, "Sample program ends.");
	kernel_exit();
}

