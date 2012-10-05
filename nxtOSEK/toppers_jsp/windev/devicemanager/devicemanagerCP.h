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
 *  @(#) $Id: devicemanagerCP.h,v 1.5 2003/12/24 07:40:42 takayuki Exp $
 */

#ifndef _ATLDEVICEMANAGERCP_H_
#define _ATLDEVICEMANAGERCP_H_

template <class T>
class CProxy_IKernelEvents : public IConnectionPointImpl<T, &IID__IKernelEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	HRESULT Fire_OnInterruptRequest(ULONG inhno)
	{
		HRESULT ret;
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			_IKernelEvents* p_IKernelEvents = reinterpret_cast<_IKernelEvents*>(sp.p);
			if (p_IKernelEvents != NULL)
				ret = p_IKernelEvents->OnInterruptRequest(inhno);
		}	return ret;
	
	}
};




template <class T>
class CProxy_IDeviceEvents : public IConnectionPointImpl<T, &IID__IDeviceEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	HRESULT Fire_OnRead(LONG address, LONG sz, unsigned char * data)
	{
		HRESULT ret;
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			_IDeviceEvents* p_IDeviceEvents = reinterpret_cast<_IDeviceEvents*>(sp.p);
			if (p_IDeviceEvents != NULL)
				ret = p_IDeviceEvents->OnRead(address, sz, data);
		}	return ret;
	
	}
	HRESULT Fire_OnWrite(LONG address, LONG sz, unsigned char * data)
	{
		HRESULT ret;
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			_IDeviceEvents* p_IDeviceEvents = reinterpret_cast<_IDeviceEvents*>(sp.p);
			if (p_IDeviceEvents != NULL)
				ret = p_IDeviceEvents->OnWrite(address, sz,data);
		}	return ret;
	
	}
	HRESULT Fire_OnKernelStart()
	{
		HRESULT ret;
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			_IDeviceEvents* p_IDeviceEvents = reinterpret_cast<_IDeviceEvents*>(sp.p);
			if (p_IDeviceEvents != NULL)
				ret = p_IDeviceEvents->OnKernelStart();
		}	return ret;
	
	}
	HRESULT Fire_OnKernelExit()
	{
		HRESULT ret;
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			_IDeviceEvents* p_IDeviceEvents = reinterpret_cast<_IDeviceEvents*>(sp.p);
			if (p_IDeviceEvents != NULL)
				ret = p_IDeviceEvents->OnKernelExit();
		}	return ret;
	
	}
};




template <class T>
class CProxy_IInformationEvents : public IConnectionPointImpl<T, &IID__IInformationEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	HRESULT Fire_OnDeviceChanged(SHORT reason, LONG devid, LONG extra = 0)
	{
		HRESULT ret;
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			_IInformationEvents* p_IInformationEvents = reinterpret_cast<_IInformationEvents*>(sp.p);
			if (p_IInformationEvents != NULL)
				ret = p_IInformationEvents->OnDeviceChanged(reason, devid, extra);
		}	return ret;
	
	}
	HRESULT Fire_OnKernelChanged(SHORT reason)
	{
		HRESULT ret;
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			_IInformationEvents* p_IInformationEvents = reinterpret_cast<_IInformationEvents*>(sp.p);
			if (p_IInformationEvents != NULL)
				ret = p_IInformationEvents->OnKernelChanged(reason);
		}	return ret;
	
	}
};


template <class T>
class CProxy_IKernelLogEvents : public IConnectionPointImpl<T, &IID__IKernelLogEvents, CComDynamicUnkArray>
{
public:
	bool onKernelStart_Performed;

	CProxy_IKernelLogEvents(void) : onKernelStart_Performed(false) {};

	//Warning this class may be recreated by the wizard.
public:
	HRESULT Fire_OnKernelStart()
	{
		HRESULT ret;
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			_IKernelLogEvents* p_IKernelLogEvents = reinterpret_cast<_IKernelLogEvents*>(sp.p);
			if (p_IKernelLogEvents != NULL)
			{
				if((ret = p_IKernelLogEvents->OnKernelStart()) == S_OK)
					onKernelStart_Performed = true;
			}
		}
		return ret;
	}

	HRESULT Fire_OnKernelExit()
	{
		HRESULT ret;
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			_IKernelLogEvents* p_IKernelLogEvents = reinterpret_cast<_IKernelLogEvents*>(sp.p);
			if (p_IKernelLogEvents != NULL)
				ret = p_IKernelLogEvents->OnKernelExit();
		}
		onKernelStart_Performed = false;	
		return ret;
	}

	HRESULT Fire_OnLogEvent(LONG sz, unsigned char * data)
	{
		HRESULT ret;
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			_IKernelLogEvents* p_IKernelLogEvents = reinterpret_cast<_IKernelLogEvents*>(sp.p);
			if (p_IKernelLogEvents != NULL)
			{
				if(!onKernelStart_Performed)
					p_IKernelLogEvents->OnKernelStart();
				ret = p_IKernelLogEvents->OnLogEvent(sz, data);
			}
		}
		if(nConnectionIndex != 0)
			onKernelStart_Performed = true;	
		return ret;	
	}
};
#endif
