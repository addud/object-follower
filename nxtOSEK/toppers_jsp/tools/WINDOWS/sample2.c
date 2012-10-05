/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2002 by Embedded and Real-Time Systems Laboratory
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
 *  @(#) $Id: sample2.c,v 1.11 2003/12/24 08:23:58 takayuki Exp $
 */


/*
 * TOPPERS/JSP ����ץ�ץ����  - 5�ͤ�ů�ؼԤˤ��ů�ؼ����� -
 *    �ǥХ������ߥ�졼����� �ǥ�
 *         Last update : 23rd, February, 2001
 */

#include <t_services.h>
#include "kernel_id.h"
#include "sample2.h"
#include "device.h"
#include "debugout.h"

void task(VP_INT exinf)
{
	ID tskid = (ID)exinf ;

	while(1==1)
	{
		set_flg(1,0x10 | (tskid-1));	/* ��ʢ */
		if(pol_sem(tskid) == E_OK)
		{
			if(pol_sem( 1 + (tskid + 4 - 1) % 5 ) == E_OK)
			{
				set_flg(1,0x20 | (tskid-1));	/* ���� */
				dly_tsk(1000 * tskid);

				set_flg(1,0x40 | (tskid-1));	/* ��ʢ */
				sig_sem( 1 + (tskid + 4 - 1) % 5 );
				sig_sem(tskid);
				dly_tsk(1000 * tskid);
				continue;
			}else
				sig_sem(tskid);
		}
		dly_tsk(1000 * tskid);
	}
}

void main_task(VP_INT exinf)
{
	char patternchar[5] = {'.','-','O','.','z'};
	FLGPTN ptn;
	char buffer[6] = "-----";


	serial_ctl_por(TASK_PORTID, (IOCTL_CRLF | IOCTL_FCSND | IOCTL_FCRCV));
	syslog_1(LOG_NOTICE,"Sample program starts (exinf = %d)", exinf);
	
	act_tsk(1);
	act_tsk(2);
	act_tsk(3);
	act_tsk(4);
	act_tsk(5);

	do{
		wai_flg(1, 0xf0, TWF_ORW, &ptn);
		if((ptn & 0xf) >= 5)
			continue;

		OnDevice DeviceWrite(100,4,&ptn);

		if( buffer[ptn & 0xf] != patternchar[(ptn >> 4) & 0xf] )
		{
			buffer[ptn & 0xf] = patternchar[(ptn >> 4) & 0xf];
			syslog_5(LOG_NOTICE,"%c%c%c%c%c",buffer[0],buffer[1],buffer[2],buffer[3],buffer[4]);
			DebugOut(buffer);
			DebugOut("\n");
		}
	}while(1==1);
}
