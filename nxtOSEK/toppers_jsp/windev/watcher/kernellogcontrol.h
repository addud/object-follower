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
 *  @(#) $Id: kernellogcontrol.h,v 1.2 2003/06/30 15:58:39 takayuki Exp $
 */

// KernelLogControl.h : Declaration of the CKernelLogControl

#ifndef __KERNELLOGCONTROL_H_
#define __KERNELLOGCONTROL_H_

#include "resource.h"       // �ᥤ�� ����ܥ�
#include <atlctl.h>
#include "watcherCP.h"

const CLSID CLSID_KernelLog = {0x4BD327FC,0x9E4A,0x4A5D,{0x95,0x03,0x27,0xC9,0x79,0xA8,0xE8,0x02}};

MIDL_INTERFACE("395F900A-AC7E-4A78-9BC1-EE5EF76254FF")
IKernelLog : public IUnknown
{
public:
};

MIDL_INTERFACE("35E35399-55ED-45FC-8F0B-4A1BC6CEA3F0")
_IKernelLogEvents : public IUnknown
{
public:
    virtual HRESULT STDMETHODCALLTYPE OnKernelStart(void) = 0;
    virtual HRESULT STDMETHODCALLTYPE OnKernelExit( void) = 0;
    virtual HRESULT STDMETHODCALLTYPE OnLogEvent(long sz, byte __RPC_FAR data[]) = 0;
};

/////////////////////////////////////////////////////////////////////////////
// CKernelLogControl
class ATL_NO_VTABLE CKernelLogControl : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IDispatchImpl<IKernelLogControl, &IID_IKernelLogControl, &LIBID_WATCHERLib>,
	public CComControl<CKernelLogControl>,
	public IPersistStreamInitImpl<CKernelLogControl>,
	public IOleControlImpl<CKernelLogControl>,
	public IOleObjectImpl<CKernelLogControl>,
	public IOleInPlaceActiveObjectImpl<CKernelLogControl>,
	public IViewObjectExImpl<CKernelLogControl>,
	public IOleInPlaceObjectWindowlessImpl<CKernelLogControl>,
	public IConnectionPointContainerImpl<CKernelLogControl>,
	public IPersistStorageImpl<CKernelLogControl>,
	public ISpecifyPropertyPagesImpl<CKernelLogControl>,
	public IQuickActivateImpl<CKernelLogControl>,
	public IDataObjectImpl<CKernelLogControl>,
	public IProvideClassInfo2Impl<&CLSID_KernelLogControl, &DIID__IKernelLogControlEvents, &LIBID_WATCHERLib>,
	public IPropertyNotifySinkCP<CKernelLogControl>,
	public CComCoClass<CKernelLogControl, &CLSID_KernelLogControl>,
	public CProxy_IKernelLogControlEvents< CKernelLogControl >,
	public _IKernelLogEvents
{
public:
	CKernelLogControl()
	{
		buffer = NULL;
		log    = NULL;
	}

DECLARE_REGISTRY_RESOURCEID(IDR_KERNELLOGCONTROL)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CKernelLogControl)
	COM_INTERFACE_ENTRY(IKernelLogControl)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IViewObjectEx)
	COM_INTERFACE_ENTRY(IViewObject2)
	COM_INTERFACE_ENTRY(IViewObject)
	COM_INTERFACE_ENTRY(IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceObject)
	COM_INTERFACE_ENTRY2(IOleWindow, IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceActiveObject)
	COM_INTERFACE_ENTRY(IOleControl)
	COM_INTERFACE_ENTRY(IOleObject)
	COM_INTERFACE_ENTRY(IPersistStreamInit)
	COM_INTERFACE_ENTRY2(IPersist, IPersistStreamInit)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY(ISpecifyPropertyPages)
	COM_INTERFACE_ENTRY(IQuickActivate)
	COM_INTERFACE_ENTRY(IPersistStorage)
	COM_INTERFACE_ENTRY(IDataObject)
	COM_INTERFACE_ENTRY(IProvideClassInfo)
	COM_INTERFACE_ENTRY(IProvideClassInfo2)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
	COM_INTERFACE_ENTRY(_IKernelLogEvents)
END_COM_MAP()

BEGIN_PROP_MAP(CKernelLogControl)
	PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
	PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
	// Example entries
	// PROP_ENTRY("Property Description", dispid, clsid)
	// PROP_PAGE(CLSID_StockColorPage)
END_PROP_MAP()

BEGIN_CONNECTION_POINT_MAP(CKernelLogControl)
	CONNECTION_POINT_ENTRY(IID_IPropertyNotifySink)
	CONNECTION_POINT_ENTRY(DIID__IKernelLogControlEvents)
END_CONNECTION_POINT_MAP()

BEGIN_MSG_MAP(CKernelLogControl)
	CHAIN_MSG_MAP(CComControl<CKernelLogControl>)
	DEFAULT_REFLECTION_HANDLER()
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);



// IViewObjectEx
	DECLARE_VIEW_STATUS(VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE)

// IKernelLogControl
public:
	STDMETHOD(get_Param)(long index, /*[out, retval]*/ long *pVal);
	STDMETHOD(get_isValid)(/*[out, retval]*/ BOOL *pVal);
	STDMETHOD(get_Logtim)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_Type)(/*[out, retval]*/ long *pVal);
	STDMETHOD(Close)();
	STDMETHOD(Open)();

	HRESULT OnDraw(ATL_DRAWINFO& di)
	{
		RECT& rc = *(RECT*)di.prcBounds;
		Rectangle(di.hdcDraw, rc.left, rc.top, rc.right, rc.bottom);

		SetTextAlign(di.hdcDraw, TA_CENTER|TA_BASELINE);
		LPCTSTR pszText = _T("ATL 3.0 : KernelLogControl");
		TextOut(di.hdcDraw, 
			(rc.left + rc.right) / 2, 
			(rc.top + rc.bottom) / 2, 
			pszText, 
			lstrlen(pszText));

		return S_OK;
	}
// IKernelLog
// _IKernelLogEvents
	STDMETHOD(OnKernelStart)()
	{
		Fire_OnKernelStart();
		return S_OK;
	}
	STDMETHOD(OnKernelExit)()
	{
		Fire_OnKernelExit();
		return S_OK;
	}
	STDMETHOD(OnLogEvent)(LONG sz, byte __RPC_FAR data [])
	{
		if(buffer != NULL)
			::GlobalFree((HGLOBAL)buffer);

		log = reinterpret_cast<DBIFLOG *>(data);
		Fire_OnLogEvent(*(int *)data);
		log = NULL;

		return S_OK;
	}

	CComPtr<IKernelLog> manager;
	DWORD				cookie;
	DBIFLOG *			log;
	void *				buffer;
};

#endif //__KERNELLOGCONTROL_H_
