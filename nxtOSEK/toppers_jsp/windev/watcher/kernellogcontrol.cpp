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
 *  @(#) $Id: kernellogcontrol.cpp,v 1.2 2003/06/30 15:58:39 takayuki Exp $
 */

// KernelLogControl.cpp : CKernelLogControl �Υ���ץ���ơ������

#include "stdafx.h"
#include "Watcher.h"
#include "KernelLogControl.h"

/////////////////////////////////////////////////////////////////////////////
// CKernelLogControl


STDMETHODIMP CKernelLogControl::Open()
{
	// TODO: ���ΰ��֤˥���ץ�����ѤΥ����ɤ��ɲä��Ƥ�������
	if(!FAILED(manager.CoCreateInstance(CLSID_KernelLog)) && !FAILED(manager.Advise((_IKernelLogEvents *)this,__uuidof(_IKernelLogEvents),&cookie)))
		return S_OK;
	if(!!manager)
		manager.Release();
	return E_FAIL;
}

STDMETHODIMP CKernelLogControl::Close()
{
	// TODO: ���ΰ��֤˥���ץ�����ѤΥ����ɤ��ɲä��Ƥ�������
	if(!manager)
		return E_FAIL;

	AtlUnadvise(manager, __uuidof(_IKernelLogEvents),cookie);
	manager.Release();
	cookie = 0;
	return S_OK;
}

STDMETHODIMP CKernelLogControl::get_Type(long *pVal)
{
	// TODO: ���ΰ��֤˥���ץ�����ѤΥ����ɤ��ɲä��Ƥ�������
	if(log != NULL)
	{
		*pVal = (long)log->header.logtype;
	}else
		*pVal = 0;

	return S_OK;
}

STDMETHODIMP CKernelLogControl::get_Logtim(long *pVal)
{
	// TODO: ���ΰ��֤˥���ץ�����ѤΥ����ɤ��ɲä��Ƥ�������
	if(log != NULL)
	{
		*pVal = (long)log->header.logtim;
	}else
		*pVal = 0;
	return S_OK;
}

STDMETHODIMP CKernelLogControl::get_isValid(BOOL *pVal)
{
	// TODO: ���ΰ��֤˥���ץ�����ѤΥ����ɤ��ɲä��Ƥ�������
	if(log != NULL)
		*pVal = TRUE;
	else
		*pVal = FALSE;
	return S_OK;
}

STDMETHODIMP CKernelLogControl::get_Param(long index, long *pVal)
{
	// TODO: ���ΰ��֤˥���ץ�����ѤΥ����ɤ��ɲä��Ƥ�������
	*pVal = *((long *)&log->body + index);

	return S_OK;
}
