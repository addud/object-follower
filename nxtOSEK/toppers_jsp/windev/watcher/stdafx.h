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
 *  @(#) $Id: stdafx.h,v 1.2 2003/06/30 15:58:39 takayuki Exp $
 */

// stdafx.h : ɸ��Υ����ƥ� ���󥯥롼�� �ե����롢
//            �ޤ��ϻ��Ȳ����¿�������Ĥ��ޤ��ѹ�����ʤ�
//            �ץ����������ѤΥ��󥯥롼�� �ե�����򵭽Ҥ��ޤ���

#if !defined(AFX_STDAFX_H__D427C5C9_3DF2_4C06_BC74_B35DCF7062FC__INCLUDED_)
#define AFX_STDAFX_H__D427C5C9_3DF2_4C06_BC74_B35DCF7062FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define STRICT
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0400
#endif
#define _ATL_APARTMENT_THREADED

#include <atlbase.h>
// CComModule ���饹���������������饹����Ѥ��ơ������С��饤�ɤ�����
// _Module ��̾�����ѹ����ʤ��Ǥ���������
extern CComModule _Module;
#include <atlcom.h>
#include <atlctl.h>


/*
 *  ITRON�ǥХå��󥰥��󥿥ե�������Ϣ�����
 */

/*
 *  �ǥ����ѥå�����
 */
#define DSP_NORMAL		0;	//����������ƥ����Ȥ���Υǥ����ѥå�
#define DSP_NONTSKCTX	1;	//����߽��������CPU�㳰����Υǥ����ѥå� 

typedef	short		 BITMASK;
typedef unsigned int INHNO;

/* ����ߥϥ�ɥ� */
typedef struct t_rglog_interrupt{
	int inhno;	//����ߥϥ�ɥ��ֹ�
} T_RGLOG_INTERRUPT;

/* ����ߥ����ӥ��ϥ�ɥ�(̤����) */
typedef struct t_rglog_isr {
	int		isrid;	//����ߥ����ӥ��롼����ID
	int     inhno;	//����ߥϥ�ɥ��ֹ�
} T_RGLOG_ISR;

/* �����।�٥�ȥϥ�ɥ� */
typedef struct t_rglog_timerhdr {
	unsigned int	type;	//�����ޡ��μ���
	int             hdrid;	//�����।�٥�ȥϥ�ɥ��ID
	void *          exinf;	//��ĥ����
} T_RGLOG_TIMERHDR;

/* CPU�㳰�ϥ�ɥ� */
typedef struct t_rglog_cupexc {
	int		tskid;	//�оݤȤʤ륿����ID
} T_RGLOG_CPUEXC;

/* �������㳰�����롼���� */
typedef struct t_rglog_tskexc {
	int		tskid;	//�оݤȤʤ륿����ID
} T_RGLOG_TSKEXC;

/* �����������Ѳ� */
typedef struct t_rglog_tskstat {
	int		tskid;		//������ID
	int		tskstat;	//�����西��������
	int		tskwait;	//�Ԥ�����
	int		wobjid;		//�Ԥ��оݤΥ��֥�������ID
} T_RGLOG_TSKSTAT;

/* �ǥ����ѥå��㳫�� */
typedef struct t_rglog_dispatch_enter {
	int				tskid;		//������ID
	unsigned int	disptype;	//�ǥ����ѥå�����
} T_RGLOG_DISPATCH_ENTER;

/* �ǥ����ѥå��㽪λ */
typedef struct t_rglog_dispatch_leave {
	int		tskid;		//������ID
} T_RGLOG_DISPATCH_LEAVE;

/* �����ӥ������� */
typedef struct t_rglog_svc {
	int				fncno;		//��ǽ������
	unsigned int	prmcnt;		//�ѥ�᡼����
	void *			prmary[1];	//�ѥ�᡼��
} T_RGLOG_SVC;

/* �����ȡ�ʸ����ΤߤΥ��� */
typedef struct t_rglog_comment {
	unsigned int	length;		//ʸ�����Ĺ��
	char			strtext[1];	//ʸ����(NULL��ü)-���Ǥ���
} T_RGLOG_COMMENT;

typedef struct t_rglog_header {
	unsigned int	logtype;
	unsigned int	logtim;
	unsigned int	valid;
	unsigned int	bufsz;
} T_RGLOG_HEADER;

typedef union t_rglog_body
{
	T_RGLOG_INTERRUPT		interrupt;
	T_RGLOG_ISR				isr;
	T_RGLOG_TIMERHDR		timerhdr;
	T_RGLOG_CPUEXC			cpuexc;
	T_RGLOG_TSKEXC			tskexc;
	T_RGLOG_TSKSTAT			tskstat;
	T_RGLOG_DISPATCH_ENTER	dispatch_enter;
	T_RGLOG_DISPATCH_LEAVE	dispatch_leave;
	T_RGLOG_SVC				svc;
	T_RGLOG_COMMENT			comment;
} T_RGLOG_BODY;

typedef struct DBIFLOG
{
	struct	t_rglog_header	header;
	union	t_rglog_body	body;
} DBIFLOG;

typedef struct t_rglog
{
	unsigned int logtype;
	unsigned int logtim;
	unsigned int valid;
	unsigned int bufsz;
	char		 buf[1];
} T_RGLOG;

/*
 *  ������μ��̤����
 */
#define LOG_TYP_INTERRUPT	0x01	/* ����ߥϥ�ɥ� */
#define LOG_TYP_ISR			0x02	/* ����ߥ����ӥ��ϥ�ɥ� */
#define LOG_TYP_TIMERHDR	0x03	/* �����।�٥�ȥϥ�ɥ� */
#define LOG_TYP_CPUEXC		0x04	/* CPU�㳰�ϥ�ɥ� */
#define LOG_TYP_TSKEXC		0x05	/* �������㳰�����롼���� */
#define LOG_TYP_TSKSTAT		0x06	/* �����������Ѳ� */
#define LOG_TYP_DISPATCH	0x07	/* �ǥ����ѥå��� */
#define LOG_TYP_SVC			0x08	/* �����ӥ������� */
#define LOG_TYP_COMMENT		0x09	/* �����ȡ�ʸ����ΤߤΥ��� */
#define LOG_ENTER			0x00	/* ���������� */
#define LOG_LEAVE			0x80	/* �и�����λ */

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �����Ԥ�ľ�����ɲä�������������ޤ���

#endif // !defined(AFX_STDAFX_H__D427C5C9_3DF2_4C06_BC74_B35DCF7062FC__INCLUDED)
