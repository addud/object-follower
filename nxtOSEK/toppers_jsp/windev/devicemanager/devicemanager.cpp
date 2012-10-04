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
 *  @(#) $Id: devicemanager.cpp,v 1.11 2003/12/24 07:40:42 takayuki Exp $
 */

#include "stdafx.h"
#include "resource.h"
#include <initguid.h>
#include <shellapi.h>
#include "devicemanager.h"
#include <commctrl.h>

#include "devicemanager_i.c"
#include "device.h"
#include "information.h"
#include "kernel.h"
#include "kernellog.h"

#define WM_NOTIFYICONCALLBACK (WM_APP+1)	//NotifyIcon�����������å������˻Ȥ��ֹ�

const DWORD dwTimeOut = 5000;  // EXE������åȥ����󤹤�ޤǤΥ����ɥ���֤Ǥ�
const DWORD dwPause = 1000;    // ����åɤ������Τ��ԤĻ��֤Ǥ�

HINSTANCE ProcessInstance = NULL;   //�ץ����Υ��󥹥��󥹥ϥ�ɥ�


// ����åȥ����� ���٥�ȴƻ��Ѥ� CreateThread ���Ϥ���ޤ�
static DWORD WINAPI MonitorProc(void* pv)
{
    CExeModule* p = (CExeModule*)pv;
    p->MonitorShutdown();
    return 0;
}

LONG CExeModule::Unlock()
{
    LONG l = CComModule::Unlock();
    if (l == 0)
    {
        bActivity = true;
        SetEvent(hEventShutdown); // ��˥����˥�����Ѱܤ������Ȥ򤷤餻�ޤ�
    }
    return l;
}

//����åȥ����󥤥٥�Ȥ�ƻ뤷�ޤ�
void CExeModule::MonitorShutdown()
{
    while (1)
    {
        WaitForSingleObject(hEventShutdown, INFINITE);
        DWORD dwWait=0;
        do
        {
            bActivity = false;
            dwWait = WaitForSingleObject(hEventShutdown, dwTimeOut);
        } while (dwWait == WAIT_OBJECT_0);
        // timed out
        if (!bActivity && m_nLockCnt == 0) // ����ư��Ƥ����Τ��ʤ����ȴ���Ф��ޤ�
        {
#if _WIN32_WINNT >= 0x0400 & defined(_ATL_FREE_THREADED)
            CoSuspendClassObjects();
            if (!bActivity && m_nLockCnt == 0)
#endif
                break;
        }
    }
    CloseHandle(hEventShutdown);
    PostThreadMessage(dwThreadID, WM_QUIT, 0, 0);
}

bool CExeModule::StartMonitor()
{
    hEventShutdown = CreateEvent(NULL, false, false, NULL);
    if (hEventShutdown == NULL)
        return false;
    DWORD dwThreadID;
    HANDLE h = CreateThread(NULL, 0, MonitorProc, this, 0, &dwThreadID);
    return (h != NULL);
}

CExeModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
OBJECT_ENTRY(CLSID_Device, CDevice)
OBJECT_ENTRY(CLSID_Information, CInformation)
OBJECT_ENTRY(CLSID_Kernel, CKernel)
OBJECT_ENTRY(CLSID_KernelLog, CKernelLog)
END_OBJECT_MAP()


LPCTSTR FindOneOf(LPCTSTR p1, LPCTSTR p2)
{
    while (p1 != NULL && *p1 != NULL)
    {
        LPCTSTR p = p2;
        while (p != NULL && *p != NULL)
        {
            if (*p1 == *p)
                return CharNext(p1);
            p = CharNext(p);
        }
        p1 = CharNext(p1);
    }
    return NULL;
}

static void InsertAllDeviceMapList(HWND hList)
{
    _TCHAR buffer[64];
    std::map<Range, class CDevice *>::iterator scope;
    LVITEM item;
    int index;
	int length = 0;

    ListView_DeleteAllItems(hList);
    item.iItem = -1;

    EnterCriticalSection(&_Module.cs);

    scope = _Module.DeviceMap.begin();
    while(scope != _Module.DeviceMap.end()) {
		_TCHAR * strbuf = (_TCHAR *)(BSTR)scope->second->DeviceName;

#ifndef _UNICODE
		length = WideCharToMultiByte(CP_ACP, 0, (BSTR)scope->second->DeviceName, -1, 0, 0, NULL, NULL);
		if(length != 0) {
			strbuf = new _TCHAR [length + 1];
			WideCharToMultiByte(CP_ACP, 0, (BSTR)scope->second->DeviceName, length, (char *)strbuf, length, NULL, NULL);
		}
		else
			strbuf = _T("<unknown>");
#endif

        item.mask = LVIF_TEXT;
        ++ item.iItem;
        item.iSubItem = 0;
        item.pszText = strbuf;
        index = ListView_InsertItem(hList, &item);

		if(length != 0)
			delete [] strbuf;

        wsprintf(buffer, _T("0x%08X -- 0x%08X"), scope->first.GetBase(), scope->first.GetBase() + scope->first.GetLength() - 1);
        ListView_SetItemText(hList, index, 1, buffer);

        ++ scope;
    }

    LeaveCriticalSection(&_Module.cs);
}



INT CALLBACK MemoryMapDialogProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg) {
        case WM_INITDIALOG:
            {
                LVCOLUMN col;

                HWND hList = GetDlgItem(hDlg, IDC_MAPLIST);
                
                col.mask = LVCF_TEXT|LVCF_WIDTH|LVCF_FMT;
                col.fmt = LVCFMT_LEFT;
                col.pszText = _T("�ǥХ���̾");
                col.cx = 200;
                ListView_InsertColumn(hList, 0, &col);

                col.mask = LVCF_TEXT|LVCF_SUBITEM|LVCF_WIDTH|LVCF_FMT;
                col.pszText = _T("���ɥ쥹�ϰ�");
                col.iSubItem = 1;
                col.cx = 230;
                ListView_InsertColumn(hList, 1, &col);
                
                InsertAllDeviceMapList(hList);

                break;
            }

        case WM_COMMAND:
            switch(wParam) {
                case IDOK:
                    DestroyWindow(hDlg);
                    break;
                default:
                    FALSE;
            }
            break;

        case WM_CLOSE:
            DestroyWindow(hDlg);
            break;

        default:
            return FALSE;
    }

    return TRUE;
}

void ShowMemoryMapDialog(HWND hParent)
{
    HWND hDlg = CreateDialog(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDD_MAPLISTDIALOG), hParent, MemoryMapDialogProc);
    ShowWindow(hDlg, SW_SHOW);
}


//---------------------------------------------------------------------
// NotifyIcon ����ƥ����ȥ�˥塼
INT DummyDialogContextMenu(HWND hDlg)
{
	enum tagMenuID {
		IDM_EXIT = 1,
        IDM_MAPLIST = 2
	};

	_TCHAR buffer[128];

	HMENU hMenu = CreatePopupMenu();
	if(hMenu == NULL)
		return 0;

	InsertMenu(hMenu, -1, MF_BYPOSITION|MF_STRING, 0, _Module.Kernel != 0 ? _T("�����ͥ뵯ư��") : _T("�����ͥ�̤��³"));
	wsprintf(buffer, _T("��³�ǥХ����� : %d"), _Module.DeviceList.size());
	InsertMenu(hMenu, -1, MF_BYPOSITION|MF_STRING, 0, buffer);
	wsprintf(buffer, _T("���պѤ߶��ֿ� : %d"), _Module.DeviceMap.size());
	InsertMenu(hMenu, -1, MF_BYPOSITION|MF_STRING, 0, buffer);
	wsprintf(buffer, _T("��³�����å���� : %d"), _Module.WatcherList.size());
	InsertMenu(hMenu, -1, MF_BYPOSITION|MF_STRING, 0, buffer);
	InsertMenu(hMenu, -1, MF_BYPOSITION|MF_SEPARATOR, 0, NULL);
	InsertMenu(hMenu, -1, MF_BYPOSITION|MF_STRING,    IDM_MAPLIST, _T("����ޥå�ɽ��"));
	InsertMenu(hMenu, -1, MF_BYPOSITION|MF_STRING,    IDM_EXIT,    _T("������λ"));

	POINT curpos = {0,0};
	GetCursorPos(&curpos);

	int cmd = TrackPopupMenu(hMenu, TPM_RIGHTALIGN|TPM_BOTTOMALIGN|TPM_RETURNCMD|TPM_RIGHTBUTTON, curpos.x, curpos.y, 0, hDlg, NULL);

	switch(cmd) {
	case IDM_EXIT:
		PostQuitMessage(0);
		break;
    case IDM_MAPLIST:
        ShowMemoryMapDialog(hDlg);
        break;
	default:
		break;
	}

	return cmd;
}


//---------------------------------------------------------------------
// NotifyIcon�ѤΥ��ߡ��������� ��å������ϥ�ɥ�
INT CALLBACK DummyDialogProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg) {

	case WM_NOTIFYICONCALLBACK:
		switch(lParam) {
		case WM_RBUTTONUP:
			DummyDialogContextMenu(hDlg);
			break;
		default:
			return FALSE;
		}
		break;

	case WM_INITDIALOG: 
		{
				/* �������ȥ쥤�˥����������Ͽ */
			NOTIFYICONDATA nd;
			HICON hIcon = LoadIcon(ProcessInstance, MAKEINTRESOURCE(IDI_ICON1));
			nd.cbSize = sizeof(nd);
			nd.hWnd = hDlg;
			nd.uID = 100;
			nd.uFlags = NIF_ICON|NIF_MESSAGE|NIF_TIP;
			nd.hIcon = hIcon;
			nd.uCallbackMessage = WM_NOTIFYICONCALLBACK;
			::lstrcpy(nd.szTip, _T("TOPPERS/JSP DeviceManager"));
			Shell_NotifyIcon(NIM_ADD, &nd);

			break;
		}

	case WM_DESTROY:
		{
			NOTIFYICONDATA nd;
			nd.cbSize = sizeof(nd);
			nd.hWnd = hDlg;
			nd.uID = 100;
			nd.uFlags = 0;
			Shell_NotifyIcon(NIM_DELETE, &nd);
			break;
		}

	default:
		return FALSE;
	}

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
//
extern "C" int WINAPI _tWinMain(HINSTANCE hInstance, 
    HINSTANCE /*hPrevInstance*/, LPTSTR lpCmdLine, int /*nShowCmd*/)
{
    lpCmdLine = GetCommandLine(); // ���ιԤ� _ATL_MIN_CRT �Τ����ɬ�פǤ�
    
#if _WIN32_WINNT >= 0x0400 & defined(_ATL_FREE_THREADED)
    HRESULT hRes = CoInitializeEx(NULL, COINIT_MULTITHREADED);
#else
    HRESULT hRes = CoInitialize(NULL);
#endif
    _ASSERTE(SUCCEEDED(hRes));
    _Module.Init(ObjectMap, hInstance, &LIBID_ATLDEVICEMANAGERLib);
    _Module.dwThreadID = GetCurrentThreadId();
    TCHAR szTokens[] = _T("-/");

    int nRet = 0;
    BOOL bRun = TRUE;
    LPCTSTR lpszToken = FindOneOf(lpCmdLine, szTokens);
    while (lpszToken != NULL)
    {
        if (lstrcmpi(lpszToken, _T("UnregServer"))==0)
        {
            _Module.UpdateRegistryFromResource(IDR_ATLDeviceManager, FALSE);
            nRet = _Module.UnregisterServer(TRUE);
            bRun = FALSE;
            break;
        }
        if (lstrcmpi(lpszToken, _T("RegServer"))==0)
        {
            _Module.UpdateRegistryFromResource(IDR_ATLDeviceManager, TRUE);
            nRet = _Module.RegisterServer(TRUE);
            bRun = FALSE;
            break;
        }
        lpszToken = FindOneOf(lpszToken, szTokens);
    }

    if (bRun)
    {
		HWND dummy_dialog_handle = NULL;

		//::AllocConsole();

		ProcessInstance = hInstance;
		dummy_dialog_handle = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_DUMMYDIALOG), NULL, DummyDialogProc);
		ShowWindow(dummy_dialog_handle, SW_HIDE);

        _Module.StartMonitor();
#if _WIN32_WINNT >= 0x0400 & defined(_ATL_FREE_THREADED)
        hRes = _Module.RegisterClassObjects(CLSCTX_LOCAL_SERVER, 
            REGCLS_MULTIPLEUSE | REGCLS_SUSPENDED);
        _ASSERTE(SUCCEEDED(hRes));
        hRes = CoResumeClassObjects();
#else
        hRes = _Module.RegisterClassObjects(CLSCTX_LOCAL_SERVER, 
            REGCLS_MULTIPLEUSE);
#endif
        _ASSERTE(SUCCEEDED(hRes));

        MSG msg;
        while (GetMessage(&msg, 0, 0, 0))
            DispatchMessage(&msg);

        _Module.RevokeClassObjects();
        Sleep(dwPause); //����åɤ���λ����ޤ��Ԥ��ޤ�

		if(dummy_dialog_handle != NULL)
			::DestroyWindow(dummy_dialog_handle);

		::FreeConsole();
	}

    _Module.Term();
    CoUninitialize();
    return nRet;
}
