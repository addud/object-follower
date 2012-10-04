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
 *  @(#) $Id: kernellog.h,v 1.2 2003/12/20 09:19:59 takayuki Exp $
 */

// KernelLog.h : CKernelLog �����

#ifndef __KERNELLOG_H_
#define __KERNELLOG_H_

#include "resource.h"       // �ᥤ�� ����ܥ�
#include "devicemanagerCP.h"

/////////////////////////////////////////////////////////////////////////////
// CKernelLog
class ATL_NO_VTABLE CKernelLog : 
    public CComObjectRootEx<CComSingleThreadModel>,
    public CComCoClass<CKernelLog, &CLSID_KernelLog>,
    public IConnectionPointContainerImpl<CKernelLog>,
    public IKernelLog,
    public CProxy_IKernelLogEvents< CKernelLog >
{
public:
    CKernelLog();
    ~CKernelLog();

DECLARE_REGISTRY_RESOURCEID(IDR_KERNELLOG)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CKernelLog)
    COM_INTERFACE_ENTRY(IKernelLog)
    COM_INTERFACE_ENTRY(IConnectionPointContainer)
    COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
END_COM_MAP()
BEGIN_CONNECTION_POINT_MAP(CKernelLog)
CONNECTION_POINT_ENTRY(IID__IKernelLogEvents)
END_CONNECTION_POINT_MAP()


// IKernelLog
public:
};

#endif //__KERNELLOG_H_



#if 0

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
                ret = p_IKernelLogEvents->OnKernelStart();
        }
        onKernelStart_Performed = true;
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
        onKernelStart_Performed = true; 
        return ret; 
    }
};
#endif