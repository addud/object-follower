/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2002-2003 by Embedded and Real-Time Systems Laboratory
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
 *  @(#) $Id: singleton.cpp,v 1.5 2003/12/15 07:32:14 takayuki Exp $
 */

// $Header: /home/CVS/configurator/base/singleton.cpp,v 1.5 2003/12/15 07:32:14 takayuki Exp $

#include "base/singleton.h"
#include "base/testsuite.h"

using namespace std;

    //Singleton ��Ū�ѿ�
bool SingletonBase::initialize = false;     //������Ѥߥե饰
bool SingletonBase::is_valid   = true;      //���󥹥������������ե饰

struct SingletonBase::chain * SingletonBase::top  = 0;  //�ǥ��ȥ饯����������Υȥå�


/************************************* �ƥ��ȥ������� *************************************/

#ifdef TESTSUITE
#include "base/coverage_undefs.h"

    bool throw_DummyType;
    class DummyType {
    public:
        static int counter;
        int dummy_value;
        int order;
        SINGLETON_CONSTRUCTOR(DummyType) throw(bad_alloc) : dummy_value(0), order(++counter)
        {
            CHECKPOINT("DummyType::DummyType");
            if(throw_DummyType)
                throw bad_alloc();
        } 
        ~DummyType(void) throw(int)
        {
            CHECKPOINT("DummyType::~DummyType");
            if(throw_DummyType)
                throw 0;
            if(counter-- != order)
                CHECKPOINT("illegal order");
        }
    };

    SINGLETON_WRAPPER(DummyType2, DummyType)

    int DummyType::counter = 0;

    TESTSUITE(main, SingletonBase)
    {
        struct chain * old_top  = top;

        top  = 0;

        BEGIN_CASE("getInstance","getInstance") {
            BEGIN_CASE("1","ñ��Υ��󥹥��󥹤����������") {
                TestSuite::clearCheckpoints();
                DummyType * dummy = Singleton<DummyType>::getInstance();
                TEST_CASE("1","���󥹥ȥ饯������ư����Ƥ���", TestSuite::isReached("DummyType::DummyType"));

                TestSuite::clearCheckpoints();
                TEST_CASE("2","���󥹥��󥹤����������", Singleton<DummyType>::getInstance() == dummy);
                TEST_CASE("3","2���ܰʹߤϥ��󥹥ȥ饯������ư����ʤ�", !TestSuite::isReached("DummyType::DummyType"));
                TEST_CASE("4","���󥰥�ȥ�ν����������äƤ���", SingletonBase::initialize);
                TEST_CASE("5","�ǥ��ȥ饯���������󤬹�������Ƥ���", SingletonBase::top != 0);
            } END_CASE;
        } END_CASE;

        BEGIN_CASE("final_release","final_release") {
            BEGIN_CASE("1","���󥹥��󥹤�����Ǥ���") {
                TEST_CASE("0","[����] ������٤����Ǥ�����", SingletonBase::top != 0);

                TestSuite::clearCheckpoints();
                SingletonBase::final_release();

                TEST_CASE("1","�ǥ��ȥ饯������ư����Ƥ���", TestSuite::isReached("DummyType::~DummyType"));
                TEST_CASE("2","�ǥ��ȥ饯���������󤬤ʤ��ʤäƤ���", SingletonBase::top == 0);
            } END_CASE;

            BEGIN_CASE("2","���֤�������") {
                DummyType::counter = 0;

                DummyType  * dummy  = Singleton<DummyType>::getInstance();
                DummyType2 * dummy2 = Singleton<DummyType2>::getInstance();

                TEST_CASE("0","[����] ���������������", dummy->order == 1 && dummy2->order == 2);

                TestSuite::clearCheckpoints();
                SingletonBase::final_release();

                TEST_CASE("1","�ǥ��ȥ饯������ư����Ƥ���", TestSuite::isReached("DummyType::~DummyType"));
                TEST_CASE("2","�ǥ��ȥ饯���������󤬤ʤ��ʤäƤ���", SingletonBase::top == 0);
                TEST_CASE("3","�˴������������", !TestSuite::isReached("illegal order"));
            } END_CASE;

        } END_CASE;

        BEGIN_CASE("getInstance","getInstance") {
            BEGIN_CASE("1","���������㳰") {
                BEGIN_CASE("1","getInstance()") {
                    throw_DummyType = true;
                    bool result = false;
                    try { Singleton<DummyType>::getInstance(); }
                    catch(...) { result = true; }

                    TEST_CASE("1","�㳰�ϵ�����",result);
                    TEST_CASE("2","�ǥ��ȥ饯����������ˤϲ���Ĥʤ��äƤ��ʤ�", SingletonBase::top == 0);
                } END_CASE;

                SingletonBase::final_release();

                BEGIN_CASE("2","getInstance(nothrow)") {

                    DummyType * dummy;
                    throw_DummyType = true;
                    bool result = true;
                    try { dummy = Singleton<DummyType>::getInstance(nothrow); }
                    catch(...) { result = false; }

                    TEST_CASE("1","�㳰�ϵ����ʤ�",result);
                    TEST_CASE("2","NULL���֤�", dummy == 0);
                    TEST_CASE("3","�ǥ��ȥ饯����������ˤϲ���Ĥʤ��äƤ��ʤ�", SingletonBase::top == 0);
                } END_CASE;
            } END_CASE;
        } END_CASE;

        top  = old_top;
    }

#endif



