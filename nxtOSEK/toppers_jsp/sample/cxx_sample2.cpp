/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2003-2004 Takagi Nobuhisa
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
 *  @(#) $Id: cxx_sample2.cpp,v 1.4 2004/09/17 09:11:34 honda Exp $
 */

/*
 *  C++����ץ�ץ����(2)������
 *
 *  ���Υ���ץ�ץ����ϡ�ů�ؼԤο����פ�١����Ȥ��ơ�C++�γƵ�ǽ
 *  �Υǥ��ԤäƤ��롣
 *  5�ͤ�ů�ؼԤ������Υե���������ݡ��ΰդ˥ǥåɥ�å���ȯ��������
 *  �����ॢ���Ȥ򸡽Ф���������C++���㳰�����Ф��Ƥ��롣
 *
 *  ư�����'q'�����Ϥ����ư�����ߤ��뤳�Ȥ��Ǥ���restart? [y|n]����
 *  ����'y'�����Ϥ���кƵ�ư��'n'�����Ϥ���н�λ���롣
 *  �ޤ���ư�����'a'�����Ϥ���Х��ܡ��Ȥ��롣
 */

#include <t_services.h>
#include <cstdlib>
#include <new>
#include "kernel_id.h"
#include "cxx_sample2.h"

//	��ޥ���������ƥ��ȥ��饹
//	��Ū���֥������ȤΥ��󥹥ȥ饯���ȥǥ��ȥ饯����ư���ץ�
class non_multitask_test
{
	int* x_;
public:
	non_multitask_test()
		: x_(new int(12345))	// �����ͥ���ư����֤Ǥ�new�黻��
	{
	}
	~non_multitask_test()
	{
		if (*x_== 12345)
			syslog(LOG_NOTICE,"non-multitask test succeeded");
		else
			syslog(LOG_NOTICE,"non-multitask test failed");
		delete x_;				// �����ͥ���ư����֤Ǥ�delete�黻��
		x_ = 0;
	}
} test;

class timeout_error
{
};

// �������
int rnd()
{
	static unsigned int seed = 1;
	loc_cpu();
	seed = seed * 1566083941UL + 1;
	unl_cpu();
	return (seed >> 16) % 0x7fff;
}

//	�ե��������饹
class fork
{
	ID semid_;
	bool used_;
public:
	explicit fork(int semid)
		: semid_(semid), used_(false)
	{
	}
	~fork()
	{
		if (used_)
			give();
	}
	ID id() const { return semid_; }
	bool is_used() const { return used_; }
	void take()
	{
		if (twai_sem(semid_, 500*5) == E_TMOUT)
			throw timeout_error();
		used_ = true;
	}
	void give()
	{
		used_ = false;
		sig_sem(semid_);
	}
};

fork* p_fork[5];

//	ů�ؼԥ��饹
class philosopher
{
	ID		tskid_;
	fork* left_;
	fork* right_;
public:
	explicit philosopher(int tskid, fork* left, fork* right)
		: tskid_(tskid),
			left_(left), right_(right)
	{
		syslog(LOG_NOTICE,"philosofer #%d", tskid);
	}
	void think()
	{
		syslog(LOG_NOTICE, "#%d thinking...", tskid_);
		dly_tsk(100 * (rnd() % 5 + 1));
	}
	void eat()
	{
		syslog(LOG_NOTICE, "#%d eat up", tskid_);
		dly_tsk(100 * (rnd() % 5 + 1));
	}
	void run()
	{
		for (;;)
		{
			try
			{
				//	�տ�Ū�˥ǥåɥ�å���ȯ�������롣
				left_->take();
				syslog(LOG_NOTICE, "#%d take left fork(%d)", tskid_, left_->id());

				dly_tsk(100 * (rnd() % 5 + 1));

				right_->take();
				syslog(LOG_NOTICE, "#%d take right fork(%d)", tskid_, right_->id());

				eat();

				left_->give();
				syslog(LOG_NOTICE, "#%d give left fork(%d)", tskid_, left_->id());
				right_->give();
				syslog(LOG_NOTICE, "#%d give right fork(%d)", tskid_, right_->id());
				think();
			}
			catch (timeout_error&)
			{
				//	�����ॢ���Ȥˤ��ǥåɥ�å��򸡽Ф���ȡ��ե�������������
				syslog(LOG_NOTICE, "#%d !!!! timeout error !!!!", tskid_);
				if (left_->is_used())
				{
					left_->give();
					syslog(LOG_NOTICE, "#%d give left fork(%d)", tskid_, left_->id());
				}
				if (right_->is_used())
				{
					right_->give();
					syslog(LOG_NOTICE, "#%d give right fork(%d)", tskid_, right_->id());
				}
				rot_rdq(TPRI_SELF);
			}
		}
	}
};

void task(VP_INT exinf)
{
	_toppers_cxxrt_reset_specific();	// �������κƵ�ư���ǽ�ˤ��뤿��ν��������
	ID		tskid = ID(exinf);
	fork* left	= p_fork[(tskid - 1) % 5];
	fork* right = p_fork[(tskid - 1 + 4) % 5];
	philosopher phil(tskid, left, right);
	phil.run();
}

//	std::atexit����Ͽ���뽪λ���ؿ�
void finish()
{
	syslog(LOG_NOTICE, "finish");
}


//	�ᥤ�󥿥���
void main_task(VP_INT exinf)
{
	serial_ctl_por(TASK_PORTID, (IOCTL_CRLF | IOCTL_FCSND | IOCTL_FCRCV));
	syslog(LOG_NOTICE,"Sample program starts (exinf = %d)", exinf);

	std::atexit(finish);

	try
	{
		for (;;)
		{
			for (ID semid = 1; semid <= 5; semid++)
				p_fork[semid - 1] = new fork(semid);

			for (ID tskid = 1; tskid <= 5; tskid++)
				act_tsk(tskid);

			char c;
			do
			{
				serial_rea_dat(TASK_PORTID, &c, 1);
				if (c == 'a')
					std::abort();
			} while (c != 'q' && c != 'Q');

			for (ID tskid = 1; tskid <= 5; tskid++)
			{
				ter_tsk(tskid);
			}

			for (ID semid = 1; semid <= 5; semid++)
			{
				delete p_fork[semid - 1];
				p_fork[semid - 1] = 0;
			}

			do
			{
				syslog(LOG_NOTICE, "restart? [y|n] ");
				serial_rea_dat(TASK_PORTID, &c, 1);
			} while (c != 'y' && c != 'n');

			if (c == 'n')
				break;
		}

		syslog(LOG_NOTICE, "multitask test succeeded");
	}
	catch (std::bad_alloc&)
	{
		syslog(LOG_NOTICE, "multitask test failed");
	}

	std::exit(0);
}

