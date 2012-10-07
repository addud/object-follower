/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2003 by Embedded and Real-Time Systems Laboratory
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
 *  @(#) $Id: cmdwatch.cpp,v 1.3 2003/06/30 15:51:47 takayuki Exp $
 */

// cmdwatch.cpp : ���󥽡��� ���ץꥱ�������Υ���ȥ� �ݥ���Ȥ�������ޤ���
//

#include <stdio.h>
#include <stdarg.h>

#include <windows.h>
#include <objbase.h>
#include <unknwn.h>
#include <ocidl.h>

#include <conio.h>

#pragma warning(disable:4200) //��ɸ��γ�ĥ��ǽ : Ĺ��0���������Ĺ�¤��

#define TMAX_LOGINFO	8

typedef	unsigned int BITMASK;
typedef struct {
		unsigned int	logtype;
		unsigned int	logtim;
		unsigned int	valid;
		unsigned int	bufsz;
		unsigned char	buf[];
	} DBIFLOG;

#define DBIFLOG_BUFMARGIN ((unsigned int)(&((DBIFLOG *)0)->buf))

/*
 *  ������ν����٤����
 */
#define LOG_EMERG	0		/* ����åȥ�������ͤ��륨�顼 */
#define LOG_ALERT	1
#define LOG_CRIT	2
#define LOG_ERR		3		/* �����ƥ२�顼 */
#define LOG_WARNING	4		/* �ٹ��å����� */
#define LOG_NOTICE	5
#define LOG_INFO	6
#define LOG_DEBUG	7		/* �ǥХå��ѥ�å����� */

/*
 *  ������ν����٤Υӥåȥޥåפ��뤿��Υޥ���
 */
#define LOG_MASK(prio)	(1 << (prio))
#define LOG_UPTO(prio)	((1 << ((prio) + 1)) - 1)

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



static FILE * destination = NULL;

static const char * apiname[] = 
{ "cre_tsk","del_tsk","act_tsk","can_act","sta_tsk","ext_tsk","exd_tsk","ter_tsk","chg_pri","get_pri","ref_tsk","ref_tst","slp_tsk","tslp_tsk","wup_tsk","can_wup","rel_wai","sus_tsk","rsm_tsk","frsm_tsk","dly_tsk","","def_tex","ras_tex","dis_tex","ena_tex","sns_tex","ref_tex","cre_sem","del_sem","sig_sem","","wai_sem","pol_sem","twai_sem","ref_sem","cre_flg","del_flg","set_flg","clr_flg","wai_flg","pol_flg","twai_flg","ref_flg","cre_dtq","del_dtq","","","snd_dtq","psnd_dtq","tsnd_dtq","fsnd_dtq","rcv_dtq","prcv_dtq","trcv_dtq","ref_dtq","cre_mbx","del_mbx","snd_mbx","","rcv_mbx","prcv_mbx","trcv_mbx","ref_mbx","cre_mpf","del_mpf","rel_mpf","","get_mpf","pget_mpf","tget_mpf","ref_mpf","set_tim","get_tim","cre_cyc","del_cyc","sta_cyc","stp_cyc","ref_cyc","","rot_rdq","get_tid","","","loc_cpu","unl_cpu","dis_dsp","ena_dsp","sns_ctx","sns_loc","sns_dsp","sns_dpn","ref_sys","","","","def_inh","cre_isr","del_isr","ref_isr","dis_int","ena_int","chg_ixx","get_ixx","def_svc","def_exc","ref_cfg","ref_ver","iact_tsk","iwup_tsk","irel_wai","iras_tex","isig_sem","iset_flg","ipsnd_dtq","ifsnd_dtq","irot_rdq","iget_tid","iloc_cpu","iunl_cpu","isig_tim","","","","cre_mtx","del_mtx","unl_mtx","","loc_mtx","ploc_mtx","tloc_mtx","ref_mtx","cre_mbf","del_mbf","","","snd_mbf","psnd_mbf","tsnd_mbf" };



void Printf(const char * format, ... )
{
	va_list vl;
	char buffer[1024];
	int i;

	va_start(vl,format);
	i = ::vsprintf(buffer, format, vl);
	if(destination != NULL)
		fwrite(buffer, i, 1, destination);
	fwrite(buffer, i, 1, stdout);
}

const char * get_apiname(int fncd)
{	return apiname[-5 - fncd];	};

void print_log(DBIFLOG * log)
{
	int i;

	Printf("%10d ms : ",log->logtim);
	switch(log->logtype)
	{
	case LOG_TYP_SVC:
		Printf("[SVC|ENT] %s (",get_apiname(*(int*)log->buf));

		for(i=0;i < *((int*)log->buf+1);i++)
		{
			if(i!=0)
				Printf(", ");
			Printf("0x%08x",*((int*)log->buf+2+i));
		}
		Printf(")\n");
		break;

	case LOG_TYP_SVC|LOG_LEAVE:
		Printf("[SVC|LEA] %s",get_apiname(*(int*)log->buf));
		if(*((int*)log->buf+1) > 0)
			Printf(" (ercd = 0x%08x)",*((int*)log->buf+2));
		Printf("\n");
		break;

	case LOG_TYP_TSKSTAT:
		Printf("[TSKSTAT] Tsk:%d ",*(int*)log->buf);
		switch(*((int*)log->buf+1))
		{
		case 0x01:
		case 0x02:
			Printf("<Ready>\n",*(int*)log->buf);
			break;
		case 0x04:
		case 0x0c:
			if(*((int*)log->buf+1) == 0x04)
				Printf("<Waiting : ");
			else
				Printf("<Wait-Suspend : ");

			switch(*((int*)log->buf+2))
			{
			case 0x1:
				Printf("Sleep>\n");
				break;
			case 0x2:
				Printf("Delay>\n");
				break;
			case 0x4:
				Printf("Semaphore (id=%d)>\n",*((int*)log->buf+3));
				break;
			case 0x8:
				Printf("Eventflag (id=%d)>\n",*((int*)log->buf+3));
				break;
			case 0x10:
				Printf("Dataqueue[send] (id=%d)>\n",*((int*)log->buf+3));
				break;
			case 0x20:
				Printf("Dataqueue[receive] (id=%d)>\n",*((int*)log->buf+3));
				break;
			case 0x40:
				Printf("Mailbox (id=%d)>\n",*((int*)log->buf+3));
				break;
			case 0x80:
				Printf("Mutex (id=%d)>\n",*((int*)log->buf+3));
				break;
			case 0x100:
				Printf("MessageBuffer[send] (id=%d)>\n",*((int*)log->buf+3));
				break;
			case 0x200:
				Printf("MessageBuffer[receive] (id=%d)>\n",*((int*)log->buf+3));
				break;
			case 0x400:
				Printf("Rendezvous[call] (id=%d)>\n",*((int*)log->buf+3));
				break;
			case 0x800:
				Printf("Rendezvous[accept] (id=%d)>\n",*((int*)log->buf+3));
				break;
			case 0x1000:
				Printf("Rendezvous[completion] (id=%d)>\n",*((int*)log->buf+3));
				break;
			case 0x2000:
				Printf("Fixed Memorypool (id=%d)>\n",*((int*)log->buf+3));
				break;
			case 0x4000:
				Printf("Variable Memorypool (id=%d)>\n",*((int*)log->buf+3));
				break;
			default:
				Printf(" complex [%04x]>\n", *((int*)log->buf+2));
				break;
			}
			break;

		case 0x08:
			Printf("<Suspended>\n");
			break;
		case 0x10:
			Printf("<Dormant>\n");
			break;
		default:
			Printf("<Unknown : %d>",*(int*)log->buf);
			break;
		}
		break;

	case LOG_TYP_TSKEXC:
		Printf("[TEX|ENT] Tsk:%d\n",*(int*)log->buf);
		break;

	case LOG_TYP_TSKEXC | LOG_LEAVE:
		Printf("[TEX|LEA] Tsk:%d\n",*(int*)log->buf);
		break;

	case LOG_TYP_DISPATCH:
		if(*((int*)log->buf+1) == 0)
			Printf("[DSP|ENT] Tsk:%d Task-context\n",*(int*)log->buf);
		else
			Printf("[DSP|ENT] Tsk:%d Nontask-context\n",*(int*)log->buf);
		break;

	case LOG_TYP_DISPATCH | LOG_LEAVE:
		Printf("[DSP|LEA] Tsk:%d\n",*(int*)log->buf);		
		break;

	case LOG_TYP_COMMENT:
		*((char *)log->buf + log->bufsz -1) = '\x0';
		Printf("[COMMENT](%d) : <%s>\n",*(int *)log->buf,log->buf+sizeof(int));
		break;
	
	case LOG_TYP_INTERRUPT:
		Printf("[INT|ENT] %d\n",*(int*)log->buf);
		break;

	case LOG_TYP_INTERRUPT | LOG_LEAVE:
		Printf("[INT|LEA] %d\n",*(int*)log->buf);
		break;

	case LOG_TYP_CPUEXC:
		Printf("[CEX|ENT] Tsk:%d\n",*(int*)log->buf);
		break;

	case LOG_TYP_CPUEXC | LOG_LEAVE:
		Printf("[CEX|LEA] Tsk:%d\n",*(int*)log->buf);
		break;

	case LOG_TYP_TIMERHDR:
	case LOG_TYP_TIMERHDR | LOG_LEAVE:
		if((log->logtype & LOG_LEAVE) != 0)
			Printf("[INT|LEA]");
		else
			Printf("[INT|ENT]");

		if( *(int*)log->buf == 0x8d )
			Printf(" cyclic ");
		else
			Printf(" OBJ(%02x) ", *(int*)log->buf);

		Printf(" ID:%d  EXINF:0x%08x\n",*((int*)log->buf+1), *((int*)log->buf+2));
		break;

	default:
		Printf("[UNKNOWN] : 0x%x\n",log->logtype);
	};
}




const CLSID CLSID_KernelLog = {0x4BD327FC,0x9E4A,0x4A5D,{0x95,0x03,0x27,0xC9,0x79,0xA8,0xE8,0x02}};

MIDL_INTERFACE("395F900A-AC7E-4A78-9BC1-EE5EF76254FF")
IKernelLog : public IUnknown
{
public:
};


struct __declspec(uuid("35E35399-55ED-45FC-8F0B-4A1BC6CEA3F0")) _IKernelLogEvents;

class IKernelLogEvents : public IUnknown
{
public:
	STDMETHOD(QueryInterface)(REFIID, void **);
	STDMETHOD_(ULONG,AddRef)();
	STDMETHOD_(ULONG,Release)();
    virtual HRESULT STDMETHODCALLTYPE OnKernelStart(void);
    virtual HRESULT STDMETHODCALLTYPE OnKernelExit(void);
    virtual HRESULT STDMETHODCALLTYPE OnLogEvent(long sz, byte __RPC_FAR data[]);

	IKernelLogEvents(void)  { RefCount = 0; };
//	virtual ~IKernelLogEvents(void) { 	if(destination != NULL) fclose(destination); };

	LONG RefCount;
};

HRESULT IKernelLogEvents::QueryInterface(REFIID riid, void ** ppvObject)
{
	if( riid == __uuidof(_IKernelLogEvents) || riid == __uuidof(IUnknown) )
	{
		*ppvObject = this;
		::InterlockedIncrement(&RefCount);
		return S_OK;
	}

	return E_NOINTERFACE;
}

ULONG IKernelLogEvents::AddRef(void)
{	return ::InterlockedIncrement(&RefCount);	}

ULONG IKernelLogEvents::Release(void)
{
	if( ::InterlockedDecrement(&RefCount) == 0 )
	{
		delete this;
		return 0;
	}
	return RefCount;
}

HRESULT IKernelLogEvents::OnKernelExit(void)
{
	Printf("OnKernelExit at \n");

	if(destination != NULL)
	{
		fclose(destination);
		destination = 0;
	}
	return S_OK;
}

HRESULT IKernelLogEvents::OnKernelStart(void)
{
	char buffer[256];
	SYSTEMTIME systim;

	if(destination != NULL)
		fclose(destination);

	::GetLocalTime(&systim);
	::wsprintf(buffer, "kernel-log-%04d%02d%02d-%02d%02d%02d.txt", systim.wYear, systim.wMonth, systim.wDay, systim.wHour, systim.wMinute, systim.wSecond);
	destination = fopen(buffer, "wt");

	Printf("OnKernelStart\n");
	return S_OK;
}

HRESULT IKernelLogEvents::OnLogEvent(long sz, byte data [])
{
	print_log((DBIFLOG *)data);
	return S_OK;
}


	//���ͥ������ݥ���Ȥؤ���³
bool Advise(IUnknown * container, REFIID iid, IUnknown * sink, DWORD * cookie, IConnectionPoint ** pcp = NULL)
{
	IConnectionPointContainer * cpc;
	IConnectionPoint * cp;

	HRESULT result;

	if(pcp == NULL)
		pcp = &cp;

	container->QueryInterface(IID_IConnectionPointContainer, (void **)&cpc);
	if(cpc == 0)
		return false;

	cpc->FindConnectionPoint(iid, pcp);
	cpc->Release();
	if(*pcp == 0)
		return false;

	if(FAILED(result = (*pcp)->Advise(sink, cookie)))
		return false;

	if(pcp == &cp)
		cp->Release();
	return true;
}

DWORD tmain_threadid;

BOOL WINAPI HandlerRoutine(DWORD dwCtrlType)
{
	switch(dwCtrlType)
	{
	case CTRL_C_EVENT:
		::PostThreadMessage(tmain_threadid,WM_QUIT,0,0);
		break;
	default:
		return FALSE;
	}

	return TRUE;
}

int main(int argc, char * argv[])
{
	IKernelLog *		pKernelLog;
	IKernelLogEvents *	psKernelLogEvents;
	IConnectionPoint *	cp;
	DWORD				cookie;
	MSG msg;

	IKernelLogEvents a;

	::CoInitialize(NULL);

	destination = 0;
	tmain_threadid = ::GetCurrentThreadId();

	if(!FAILED(::CoCreateInstance(CLSID_KernelLog, NULL, CLSCTX_ALL, __uuidof(IKernelLog), (void **)&pKernelLog)))
	{
		cp = NULL;
		psKernelLogEvents = new IKernelLogEvents;

		if(Advise(pKernelLog, __uuidof(_IKernelLogEvents), psKernelLogEvents, &cookie, &cp))
		{
			::SetConsoleCtrlHandler(HandlerRoutine, TRUE);
			while(::GetMessage(&msg, NULL, 0, 0) != 0)
			{   ::DispatchMessage(&msg);   }
			::SetConsoleCtrlHandler(HandlerRoutine, FALSE);
			
			cp->Unadvise(cookie);
		}

		delete psKernelLogEvents;

		if(pKernelLog != NULL)
			pKernelLog->Release();
	}

	if(destination != NULL)
	{
		Printf("\n\nSuspended by Ctrl-C event occursion.\n");
		fclose(destination);
	}

	::CoUninitialize();
	return 0;
}

