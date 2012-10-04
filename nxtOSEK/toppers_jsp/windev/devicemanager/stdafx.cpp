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
 *  @(#) $Id: stdafx.cpp,v 1.11 2003/12/24 07:40:42 takayuki Exp $
 */

/*
 * �ǥХ����ޥ͡����� ����(CExeModule)
 */

#pragma warning(disable:4786)	//�ǥХå�ʸ�����255ʸ�����ڤ�ͤ�ޤ���
#pragma warning(disable:4200)	//��ɸ��γ�ĥ��ǽ��ȤäƤ��ޤ� (Ĺ�����������:465����)

#include "stdafx.h"

#ifdef _ATL_STATIC_REGISTRY
#include <statreg.h>
#include <statreg.cpp>
#endif

#include <atlimpl.cpp>
#include <algorithm>

#include <initguid.h>
#include "devicemanager.h"
#include "device.h"
#include "kernel.h"
#include "information.h"
#include "kernellog.h"

using namespace std;

#ifdef _DEBUG
	DWORD Count;
	char Buffer[1024];
	#define DebugOut(x) ::WriteFile(::GetStdHandle(STD_OUTPUT_HANDLE),Buffer, (x), &Count, NULL)
#else
	#define DebugOut(x) /##/
#endif

CExeModule::CExeModule(void) : Kernel(0)
{
	::InitializeCriticalSection(&cs);
}


DeviceID CExeModule::AddDevice(CDevice *device)
{
	list<CDevice *>::iterator scope;
	list<CInformation *>::iterator view;

	::EnterCriticalSection(&cs);

	scope = find(DeviceList.begin(), DeviceList.end(), device);
	if(scope != DeviceList.end())
	{
		::LeaveCriticalSection(&cs);
		return 0;
	}

	DebugOut(::wsprintfA(Buffer,"AddDevice\n"));
	view = ViewerList.begin();
	while(view != ViewerList.end())
	{
		(*view)->Fire_OnDeviceChanged(1,reinterpret_cast<long>(device));
		view ++;
	}

	DeviceList.push_back(device);

	::LeaveCriticalSection(&cs);
	return reinterpret_cast<DeviceID>(device);
}

bool CExeModule::DeleteDevice(CDevice *device)
{
	list<CDevice *>::iterator dev;
	map<Range,CDevice *>::iterator mem[2];

	::EnterCriticalSection(&cs);

	DebugOut(::wsprintfA(Buffer,"DelDevice\n"));

	dev = find(DeviceList.begin(), DeviceList.end(), device);
	if(dev == DeviceList.end())
	{
		::LeaveCriticalSection(&cs);
		return false;
	}

	mem[0] = DeviceMap.begin();
	while(mem[0] != DeviceMap.end())
	{
		if((*mem[0]).second == device)
		{
			mem[1] = mem[0];
			mem[0] ++;

			DeviceMap.erase(mem[1]);
		}else
			mem[0] ++;
	}

	DeviceList.erase(dev);

	list<CInformation *>::iterator view;
	view = ViewerList.begin();
	while(view != ViewerList.end())
	{
		(*view)->Fire_OnDeviceChanged(2,reinterpret_cast<long>(device));
		view ++;
	}

	::LeaveCriticalSection(&cs);
	return true;
}

bool CExeModule::Map(CDevice *device, Range area)
{
	map<Range,CDevice *>::iterator scope;

	::EnterCriticalSection(&cs);
	

	scope = DeviceMap.begin();
	while(scope != DeviceMap.end())
	{
		if( area.IsIncludedIn((*scope).first) )
		{
			::LeaveCriticalSection(&cs);
			return false;
		}
		scope ++;
	}

	DeviceMap[area] = device;

	DebugOut(::wsprintfA(Buffer,"Map\n"));
	list<CInformation *>::iterator view;
	view = ViewerList.begin();
	while(view != ViewerList.end())
	{
		(*view)->Fire_OnDeviceChanged(3,reinterpret_cast<long>(device),area.GetBase());
		view ++;
	}

	::LeaveCriticalSection(&cs);
	return true;
}


bool CExeModule::Unmap(CDevice *device, unsigned long address)
{
	map<Range,CDevice *>::iterator scope;
	Range work(address);

	::EnterCriticalSection(&cs);

	scope = DeviceMap.begin();
	while(scope != DeviceMap.end())
	{
		if( (*scope).second == device && work.IsIncludedIn((*scope).first) )
		{
			DeviceMap.erase(scope);

			DebugOut(::wsprintfA(Buffer,"Unmap\n"));
			list<CInformation *>::iterator view;
			view = ViewerList.begin();
			while(view != ViewerList.end())
			{
				(*view)->Fire_OnDeviceChanged(4,reinterpret_cast<long>(device),address);
				view ++;
			}

			::LeaveCriticalSection(&cs);

			return true;
		}
		scope ++;
	}
	::LeaveCriticalSection(&cs);

	return false;
}

void CExeModule::AddViewer(CInformation *view)
{
	list<CInformation *>::iterator scope;

	::EnterCriticalSection(&cs);
	scope = find(ViewerList.begin(), ViewerList.end(), view);
	if(scope == ViewerList.end())
		ViewerList.push_back(view);
	::LeaveCriticalSection(&cs);
}

void CExeModule::RemoveViewer(CInformation *view)
{
	list<CInformation *>::iterator scope;

	::EnterCriticalSection(&cs);
	scope = find(ViewerList.begin(), ViewerList.end(), view);
	if(scope != ViewerList.end())
		ViewerList.erase(scope);
	::LeaveCriticalSection(&cs);
}

bool CExeModule::AttachKernel(CKernel *kernel)
{
	bool result = false;
	list<CDevice *>::iterator scope;
	list<CInformation *>::iterator view;
	list<CKernelLog *>::iterator watcher;

	DebugOut(::wsprintfA(Buffer,"AttachKernel\n"));

	::EnterCriticalSection(&cs);
	if((Kernel != 0) && (Kernel != kernel))
	{
			//�����-1 => �����ͥ��KeepAlive
		if(FAILED(Kernel->Fire_OnInterruptRequest(-1)))
		{
				//��³�򼺤ä������ͥ�Υǥ��å�
			DetachKernel(Kernel);
		}else
		{
				//��³�Ѥߥ����ͥ뤬����
			if(::MessageBox(NULL,_T("�����������ͥ뤬��ư���졢�ǥХ����ޥ͡��������³���褦�Ȥ��Ƥ��ޤ���\n�����������ͥ����³����ڤ��ؤ��ޤ���?"),_T("TOPPERS/JSP Windows - DeviceManager"),MB_YESNO) == IDYES)
				DetachKernel(Kernel);
		}
	}

	if(Kernel == 0)
	{
		Kernel = kernel;

		scope = DeviceList.begin();
		while(scope != DeviceList.end())
		{
			(*scope)->Fire_OnKernelStart();
			scope ++;
		}

		view = ViewerList.begin();
		while(view != ViewerList.end())
		{
			(*view)->Fire_OnKernelChanged(1);
			view ++;
		}

		watcher = WatcherList.begin();
		while(watcher != WatcherList.end())
		{
			(*watcher)->Fire_OnKernelStart();
			watcher ++;
		}

		DebugOut(::wsprintfA(Buffer,"AttachKernel was performed successfully\n"));
		result = true;
	}
	::LeaveCriticalSection(&cs);

	return result;
}

bool CExeModule::DetachKernel(CKernel *kernel)
{
	bool result;
	list<CDevice *>::iterator scope;
	list<CInformation *>::iterator view;
	list<CKernelLog *>::iterator watcher;

	DebugOut(::wsprintfA(Buffer,"DetachKernel\n"));

	::EnterCriticalSection(&cs);
	if( (result = Kernel == kernel) )
	{
		scope = DeviceList.begin();
		while(scope != DeviceList.end())
		{
			(*scope)->Fire_OnKernelExit();
			scope ++;
		}

		view = ViewerList.begin();
		while(view != ViewerList.end())
		{
			(*view)->Fire_OnKernelChanged(2);
			view ++;
		}

		watcher = WatcherList.begin();
		while(watcher != WatcherList.end())
		{
			(*watcher)->Fire_OnKernelExit();
			watcher ++;
		}

		Kernel = 0l;
		DebugOut(::wsprintfA(Buffer,"DetachKernel was performed successfully\n"));
	}
	::LeaveCriticalSection(&cs);

	return result;
}

bool CExeModule::Read(CKernel * kernel, unsigned long address, unsigned long sz, unsigned char data[])
{
	bool result;
	map<Range,CDevice *>::iterator scope;

	DebugOut(::wsprintfA(Buffer,"Read\n"));

	::EnterCriticalSection(&cs);

	if(Kernel != kernel)
	{
		::LeaveCriticalSection(&cs);

		DebugOut(::wsprintfA(Buffer,"Illegal Kernel\n"));
		
		return false;
	}

	scope = DeviceMap.find(Range(address,sz));
	
	result = (scope != DeviceMap.end());
	if(result)
		(*scope).second->Fire_OnRead(address, sz, data);

	::LeaveCriticalSection(&cs);

	return result;

}

bool CExeModule::Write(CKernel *kernel, unsigned long address, unsigned long sz, unsigned char *data)
{
	bool result;
	map<Range,CDevice *>::iterator scope;

	DebugOut(::wsprintfA(Buffer,"Write\n"));

	::EnterCriticalSection(&cs);

	if(Kernel != kernel)
	{
		::LeaveCriticalSection(&cs);
		DebugOut(::wsprintfA(Buffer,"Request performed by Illegal Kernel\n"));
		return false;
	}

	scope = DeviceMap.find(Range(address,sz));
	
	result = (scope != DeviceMap.end());
	if(result)
	{
		DebugOut(::wsprintfA(Buffer,"FireWrite\n"));
		(*scope).second->Fire_OnWrite(address, sz,data);
	}
	::LeaveCriticalSection(&cs);

	return result;
}

bool CExeModule::RaiseInterrupt(unsigned long inhno)
{
	bool result = false;

	::EnterCriticalSection(&cs);

	if(Kernel != 0 && Kernel->Fire_OnInterruptRequest(inhno) >= 0)
		result = true;

	::LeaveCriticalSection(&cs);

	return result;
}

bool CExeModule::AddLogWatcher(CKernelLog * watcher)
{
	if( find(WatcherList.begin(), WatcherList.end(), watcher) != WatcherList.end() )
		return false;	//¿����Ͽ

	::EnterCriticalSection(&cs);
	WatcherList.push_back(watcher);
	::LeaveCriticalSection(&cs);

	DebugOut(::wsprintfA(Buffer,"Log watcher inserted into the queue successfully\n"));

	return true;
}


void CExeModule::RemoveLogWatcher(CKernelLog * watcher)
{
	list<CKernelLog *>::iterator scope;

	::EnterCriticalSection(&cs);
	scope = find(WatcherList.begin(), WatcherList.end(), watcher);
	if(scope != WatcherList.end())
		WatcherList.erase(scope);
	::LeaveCriticalSection(&cs);

	DebugOut(::wsprintfA(Buffer,"Log watcher removed from the queue successfully\n"));
}



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


typedef	unsigned int BITMASK;

typedef struct {
		unsigned int	logtype;
		unsigned int	logtim;
		BITMASK			valid;
		unsigned int	bufsz;
		unsigned char	buf[];
	} DBIFLOG;
#define DBIFLOG_BUFMARGIN (sizeof(unsigned int)*4)

bool CExeModule::OnLogEvent(CKernel *kernel, long sz, unsigned char *data)
{
	list<CKernelLog *>::iterator scope;

#if 0

	DBIFLOG * log = reinterpret_cast<DBIFLOG *>(data);
	
	DebugOut(::wsprintfA(Buffer,"LOG <%08x> ",log->logtim));
	switch(log->logtype)
	{
	case LOG_TYP_TSKSTAT:
		DebugOut(::wsprintfA(Buffer,"[STATUS] Tsk:%d ",*(int*)log->buf));
		switch(*((int*)log->buf+1))
		{
		case 0x01:
		case 0x02:
			DebugOut(::wsprintfA(Buffer,"<Runnable [Ready+Running]>\n",*(int*)log->buf));
			break;
		case 0x04:
		case 0x0c:
			if(*((int*)log->buf+1) == 0x04)
				DebugOut(::wsprintfA(Buffer,"<Waiting : "));
			else
				DebugOut(::wsprintfA(Buffer,"<Wait-Suspend : "));

			switch(*((int*)log->buf+2))
			{
			case 0x1:
				DebugOut(::wsprintfA(Buffer,"Sleep>\n"));
				break;
			case 0x2:
				DebugOut(::wsprintfA(Buffer,"Delay>\n"));
				break;
			case 0x4:
				DebugOut(::wsprintfA(Buffer,"Semaphore>\n"));
				break;
			default:
				DebugOut(::wsprintfA(Buffer," complex [%04x]>\n", *((int*)log->buf+2)));
				break;
			}

			break;
		case 0x08:
			DebugOut(::wsprintfA(Buffer,"<Suspended>\n"));
			break;
		case 0x10:
			DebugOut(::wsprintfA(Buffer,"<Dormant>\n"));
			break;
		default:
			DebugOut(::wsprintfA(Buffer,"<Unknown : %d>",*(int*)log->buf));
			break;
		}
		break;

	case LOG_TYP_TSKEXC:
		DebugOut(::wsprintfA(Buffer,"[TSKEXC|ENT] Tsk:%d\n",*(int*)log->buf));
		break;

	case LOG_TYP_TSKEXC | LOG_LEAVE:
		DebugOut(::wsprintfA(Buffer,"[TSKEXC|LEA] Tsk:%d\n",*(int*)log->buf));
		break;

	case LOG_TYP_DISPATCH:
		if(*((int*)log->buf+1) == 0)
			DebugOut(::wsprintfA(Buffer,"[DSP|ENT] Tsk:%d Task-context\n",*(int*)log->buf));
		else
			DebugOut(::wsprintfA(Buffer,"[DSP|ENT] Tsk:%d Nontask-context\n",*(int*)log->buf));
		break;

	case LOG_TYP_DISPATCH | LOG_LEAVE:
		DebugOut(::wsprintfA(Buffer,"[DSP|LEA] Tsk:%d\n",*(int*)log->buf));		
		break;

	case LOG_TYP_COMMENT:
		DebugOut(::wsprintfA(Buffer,"[COMMENT (%d)] : ",log->bufsz));
		::WriteFile(::GetStdHandle(STD_OUTPUT_HANDLE), log->buf, log->bufsz-1, &Count, NULL);
		break;
	
	case LOG_TYP_INTERRUPT:
		DebugOut(::wsprintfA(Buffer,"[INT|ENT] %d\n",*(int*)log->buf));
		break;

	case LOG_TYP_INTERRUPT | LOG_LEAVE:
		DebugOut(::wsprintfA(Buffer,"[INT|LEA] %d\n",*(int*)log->buf));
		break;

	case LOG_TYP_CPUEXC:
		DebugOut(::wsprintfA(Buffer,"[CPUEXC|ENT] Tsk:%d\n",*(int*)log->buf));
		break;

	case LOG_TYP_CPUEXC | LOG_LEAVE:
		DebugOut(::wsprintfA(Buffer,"[CPUEXC|LEA] Tsk:%d\n",*(int*)log->buf));
		break;

	case LOG_TYP_TIMERHDR:
	case LOG_TYP_TIMERHDR | LOG_LEAVE:
		if((log->logtype & LOG_LEAVE) != 0)
			DebugOut(::wsprintfA(Buffer,"[INT|LEA]"));
		else
			DebugOut(::wsprintfA(Buffer,"[INT|ENT]"));

		if( *(int*)log->buf == 0x8d )
			DebugOut(::wsprintfA(Buffer," cyclic "));
		else
			DebugOut(::wsprintfA(Buffer," OBJ(%02x) ", *(int*)log->buf));

		DebugOut(::wsprintf(Buffer," ID:%d  EXINF:0x%08x\n",*((int*)log->buf+1), *((int*)log->buf+2)));
		break;

	default:
		DebugOut(::wsprintfA(Buffer,"[UNKNOWN:0x%x]\n",log->logtype));
	};
#endif
	
	if(Kernel != kernel)
	{
		DebugOut(::wsprintfA(Buffer,"Request performed by Illegal Kernel\n"));
		return false;
	}

	::EnterCriticalSection(&cs);
	scope = WatcherList.begin();
	while(scope != WatcherList.end())
	{
		(*scope)->Fire_OnLogEvent(sz, data);
		scope ++;
	}
	::LeaveCriticalSection(&cs);

	return true;
}

