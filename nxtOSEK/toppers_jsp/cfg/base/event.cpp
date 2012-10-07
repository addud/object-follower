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
 *  @(#) $Id: event.cpp,v 1.5 2003/12/20 06:51:58 takayuki Exp $
 */

// $Header: /home/CVS/configurator/base/event.cpp,v 1.5 2003/12/20 06:51:58 takayuki Exp $

#include "base/event.h"

using namespace std;

/***************************** �ƥ��ȥ������� *****************************/

#ifdef TESTSUITE
#include "base/coverage_undefs.h"

namespace {
    class Event_fortest : public Event<int> 
    {   TESTSUITE_PROTOTYPE(main)   };

    int * ptr_i_dummy_handler;
    void dummy_handler(int & i)
    {
        ptr_i_dummy_handler = &i;
        ++ i;
        TestSuite::check("dummy_handler");
    }

    class EventHandler : public Event_fortest::Handler
    {
    public:
        int * ptr_i;

        EventHandler(void)  throw() { TestSuite::check("EventHandler::EventHandler");  }
        ~EventHandler(void) throw() { TestSuite::check("EventHandler::~EventHandler"); }
        void handler(Event_fortest::value_type & i) { ptr_i = &i; ++i; TestSuite::check("EventHandler::handler"); }
    };
}

TESTSUITE(main,Event_fortest)
{
    BEGIN_CASE("add","add") {
        BEGIN_CASE("1","add�ǥϥ�ɥ餬��Ͽ�Ǥ���") {
            Singleton<Event_fortest::handler_list_type>::renewInstance();

            Event_fortest::add(dummy_handler);

            TEST_CASE("1","�ϥ�ɥ�ꥹ�Ȥ�1�����Ƥ���", Singleton<Event_fortest::handler_list_type>::getInstance()->size() == 1);
            TEST_CASE("2","�ϥ�ɥ�ꥹ�Ȥ���Ȥ�������", *Singleton<Event_fortest::handler_list_type>::getInstance()->begin() == dummy_handler);
        } END_CASE;

        BEGIN_CASE("2","Ʊ���ϥ�ɥ��ʣ������Ͽ�Ǥ���") {
            Singleton<Event_fortest::handler_list_type>::renewInstance();

            Event_fortest::add(dummy_handler);
            Event_fortest::add(dummy_handler);
            Event_fortest::add(dummy_handler);

            TEST_CASE("1","�ϥ�ɥ�ꥹ�Ȥ���Ȥ�3", Singleton<Event_fortest::handler_list_type>::getInstance()->size() == 3);
            TEST_CASE("2","�ϥ�ɥ�ꥹ�Ȥ���Ȥ�������", *Singleton<Event_fortest::handler_list_type>::getInstance()->begin() == dummy_handler);
        } END_CASE;
    } END_CASE;

    BEGIN_CASE("remove","remove") {
        BEGIN_CASE("1","add����Ͽ�����ϥ�ɥ�����Ǥ���") {
            Singleton<Event_fortest::handler_list_type>::renewInstance();

            Event_fortest::add(dummy_handler);
            Event_fortest::remove(dummy_handler);

            TEST_CASE("1","�ϥ�ɥ�ꥹ�Ȥ����ǿ���0", Singleton<Event_fortest::handler_list_type>::getInstance()->size() == 0);
        } END_CASE;

        BEGIN_CASE("2","��Ͽ�������ƤΥϥ�ɥ餬�ä���") {
            Singleton<Event_fortest::handler_list_type>::renewInstance();

            Event_fortest::add(dummy_handler);
            Event_fortest::add(dummy_handler);
            Event_fortest::add(dummy_handler);
            Event_fortest::remove(dummy_handler);

            TEST_CASE("1","�ϥ�ɥ�ꥹ�Ȥ����ǿ���0", Singleton<Event_fortest::handler_list_type>::getInstance()->size() == 0);
        } END_CASE;
    } END_CASE;

    BEGIN_CASE("constructor/destructor","constructor/destructor") {
        Singleton<Event_fortest::Handler::instance_list_type>::renewInstance();

        TEST_CASE("0","[����] �ϥ�ɥ�ꥹ�Ȥ���Ȥ�0", Singleton<Event_fortest::Handler::instance_list_type>::getInstance()->size() == 0);
        {
            EventHandler evhdr;
            TEST_CASE("1","�ϥ�ɥ�ꥹ�Ȥ���Ͽ����Ƥ���", Singleton<Event_fortest::Handler::instance_list_type>::getInstance()->size() == 1);
            TEST_CASE("2","��������Ͽ����Ƥ���", *Singleton<Event_fortest::Handler::instance_list_type>::getInstance()->begin() == &evhdr);
        }
        TEST_CASE("3","�ϥ�ɥ�ϲ������Ƥ���", Singleton<Event_fortest::Handler::instance_list_type>::getInstance()->size() == 0);
    } END_CASE;

    BEGIN_CASE("raise","raise") {
        BEGIN_CASE("1","��Ͽ������Ū�ʥϥ�ɥ餬�¹Ԥ����") {
            Singleton<Event_fortest::handler_list_type>::renewInstance();
            TestSuite::clearCheckpoints();

            Event_fortest::add(dummy_handler);

            int i = 0;
            Event_fortest::raise(i);

            TEST_CASE("1","�ϥ�ɥ餬�¹Ԥ����",TestSuite::isReached("dummy_handler"));
            TEST_CASE("2","�����֤Ǹ��Ƥ����ѿ���Ʊ��", &i == ptr_i_dummy_handler);
            TEST_CASE("3","�ͤ����󥯥���Ȥ���Ƥ���", i == 1);
        } END_CASE;

        BEGIN_CASE("2","��Ͽ�������󥹥��󥹤Υϥ�ɥ餬�¹Ԥ����") {
            Singleton<Event_fortest::handler_list_type>::renewInstance();
            TestSuite::clearCheckpoints();
            EventHandler evhdr;

            int i = 0;
            Event_fortest::raise(i);

            TEST_CASE("1","�ϥ�ɥ餬�¹Ԥ����",TestSuite::isReached("EventHandler::handler"));
            TEST_CASE("2","�����֤Ǹ��Ƥ����ѿ���Ʊ��", &i == evhdr.ptr_i);
            TEST_CASE("3","�ͤ����󥯥���Ȥ���Ƥ���", i == 1);
        } END_CASE;

        BEGIN_CASE("3","ξ��Ʊ�� (���֤��ä˵��ˤ��ʤ�)") {
            Singleton<Event_fortest::handler_list_type>::renewInstance();
            TestSuite::clearCheckpoints();
            EventHandler evhdr;

            Event_fortest::add(dummy_handler);

            int i = 0;
            Event_fortest::raise(i);

            TEST_CASE("1","�ϥ�ɥ餬�¹Ԥ����",TestSuite::isReached("dummy_handler"));
            TEST_CASE("2","�ϥ�ɥ餬�¹Ԥ����",TestSuite::isReached("EventHandler::handler"));
            TEST_CASE("3","�ͤ����󥯥���Ȥ���Ƥ���", i == 2);
        } END_CASE;

        BEGIN_CASE("4","ʣ����Ͽ") {
            Singleton<Event_fortest::handler_list_type>::renewInstance();
            TestSuite::clearCheckpoints();
            EventHandler evhdr;
            EventHandler evhdr2;

            Event_fortest::add(dummy_handler);
            Event_fortest::add(dummy_handler);

            int i = 0;
            Event_fortest::raise(i);

            TEST_CASE("1","�ϥ�ɥ餬�¹Ԥ����",TestSuite::isReached("dummy_handler"));
            TEST_CASE("2","�ϥ�ɥ餬�¹Ԥ����",TestSuite::isReached("EventHandler::handler"));
            TEST_CASE("3","�ͤ����󥯥���Ȥ���Ƥ���", i == 4);
        } END_CASE;
    } END_CASE;
}


#endif



