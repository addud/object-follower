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
 *  @(#) $Id: manager.cpp,v 1.11 2003/12/15 07:32:13 takayuki Exp $
 */

// $Header: /home/CVS/configurator/base/manager.cpp,v 1.11 2003/12/15 07:32:13 takayuki Exp $

#ifdef _MSC_VER
#  pragma warning(disable:4786)
#  define CDECL __cdecl
#else
#  define CDECL
#endif

#include <stdlib.h>
#include <fstream>
#include <iostream>

#include "base/event.h"
#include "base/message.h"
#include "base/component.h"
#include "base/directorymap.h"

using namespace std;

Event<StartupEvent>   startupEvent;
Event<ShutdownEvent>  shutdownEvent;

int CDECL main(int argc, char ** argv)
{
    ShutdownEvent evt;
    OptionParameter & option= getOptionParameter();

    evt.exit_code = EXIT_FAILURE;

    if(SingletonBase::isValid() && Component::isValid()) {

        option.parseOption(argc, argv, "-h");

        try {
            startupEvent.raise();
            Component::executeComponents(option);
            evt.exit_code = EXIT_SUCCESS;
        }
        catch(Exception & e)
        {
            cerr << Message("Program failed in its process by following reason.\n","�ץ�������̿Ū�ʥ��顼�ˤ�����Ǥ���ޤ���.\n");
            cerr << "  " << e.getDetails() << '\n';
        }
        catch(ExceptionMessage & e) {
            CHECKPOINT("catch(ExceptionMessage)");
            cerr << "Program failed : " << e << '\n';
        }
        catch(bad_alloc & e) {
            CHECKPOINT("catch(bad_alloc)");
            cerr << "Program failed : bad_alloc (" << e.what() << ")\n";
        }
        catch(...) {
            CHECKPOINT("catch(...)");
            cerr << "Program filed : Unknown Exception Occured\n";
        }
    }
    else
        cerr << "Program initialization failure\n";

    try {
        DebugMessage("shutdown event - exitcode(%)\n") << evt.exit_code;
        shutdownEvent.raise(evt);
    }
    catch(Exception & e)
    {
        DebugMessage("exception was raised in the event - %\n") << e.getDetails();
        cerr << Message("Program failed in its process by following reason.\n","�ץ�������̿Ū�ʥ��顼�ˤ�����Ǥ���ޤ���.\n");
        cerr << "  " << e.getDetails() << '\n';
    }

    catch(...) {
        DebugMessage("exception was raised in the event\n");
        CHECKPOINT("catch(...) in shutdownEvent::raise");
        evt.exit_code = EXIT_FAILURE;
    }

    DebugMessage("Exit code (%)\n") << evt.exit_code;

    return evt.exit_code;
}

/************************************* �ƥ��ȥ������� *************************************/

#ifdef TESTSUITE
#include "coverage_undefs.h"

namespace {

    extern void testsuite(TestSuiteControl & _suite_control);
    TestSuite testsuite_onTop("Entrypoint(main)", testsuite);

    class TestComponent : public Component
    {
    public:
        int mode;

        void parseOption(OptionParameter &)
        {
            switch(mode) {
                case 0:
                    CHECKPOINT("TestComponent::case 0");
                    break;
                case 1:
                    ExceptionMessage("exception").throwException();
                case 2:
                    throw bad_alloc();
            }
        }
    };

    void dummyStartupHandler(StartupEvent &)
    {
        TestSuite::check("dummyStartupHandler");
    }

    int dummyShutdownHandler_exit_code;
    void dummyShutdownHandler(ShutdownEvent & evt)
    {
        dummyShutdownHandler_exit_code = evt.exit_code;
        TestSuite::check("dummyShutdownHandler");
    }

        //�ƥ��ȥ������Ȥ�����
    void testsuite(TestSuiteControl & _suite_control)
    {
        SingletonBase::ContextChain chain;

        chain.saveContext<Component::ComponentInfo>();
        chain.saveContext<Event<StartupEvent>::handler_list_type>();
        chain.saveContext<Event<ShutdownEvent>::handler_list_type>();

        BEGIN_CASE("1","main�ؿ�ñ�� + ����ݡ��ͥ�Ȥʤ�") {
            chain.renewInstance();

            Event<StartupEvent>::add(dummyStartupHandler);
            Event<ShutdownEvent>::add(dummyShutdownHandler);

            BEGIN_CASE("1","���̤˼¹Ԥ���") {
                TestSuite::clearCheckpoints();

                char * argv[] = { "test.exe" };

                Exception::setThrowControl(true);
                TestComponent test;
                test.mode = 0;

                TEST_CASE("1","main�ؿ���EXIT_SUCCESS���֤�", main(1, argv) == EXIT_SUCCESS);

                TEST_CASE("2","�㳰���¹Ԥ���ʤ� catch(Exception)", !TestSuite::isReached("catch(Exception)"));
                TEST_CASE("3","�㳰���¹Ԥ���ʤ� catch(bad_alloc)", !TestSuite::isReached("catch(bad_alloc)"));
                TEST_CASE("4","�㳰���¹Ԥ���ʤ� catch(...)",       !TestSuite::isReached("catch(...)"));
                TEST_CASE("5","Component���¹Ԥ���Ƥ���", TestSuite::isReached("TestComponent::case 0"));
                TEST_CASE("6","�������ȥ��åץϥ�ɥ餬��ư����Ƥ���", TestSuite::isReached("dummyStartupHandler"));
                TEST_CASE("7","����åȥ�����ϥ�ɥ餬��ư����Ƥ���", TestSuite::isReached("dummyShutdownHandler"));
                TEST_CASE("8","����åȥ�����ϥ�ɥ��EXIT_SUCCESS������Ƥ���", dummyShutdownHandler_exit_code == EXIT_SUCCESS);
            } END_CASE;

            BEGIN_CASE("2","Exception�㳰���֤�") {
                TestSuite::clearCheckpoints();

                char * argv[] = { "test.exe" };

                Exception::setThrowControl(true);
                TestComponent test;
                test.mode = 1;

                TEST_CASE("1","main�ؿ���EXIT_FAILURE���֤�", main(1, argv) == EXIT_FAILURE);

                TEST_CASE("2","�㳰���¹Ԥ����   catch(Exception)", TestSuite::isReached("catch(Exception)"));
                TEST_CASE("3","�㳰���¹Ԥ���ʤ� catch(bad_alloc)", !TestSuite::isReached("catch(bad_alloc)"));
                TEST_CASE("4","�㳰���¹Ԥ���ʤ� catch(...)",       !TestSuite::isReached("catch(...)"));
                TEST_CASE("5","�������ȥ��åץϥ�ɥ餬��ư����Ƥ���", TestSuite::isReached("dummyStartupHandler"));
                TEST_CASE("6","����åȥ�����ϥ�ɥ餬��ư����Ƥ���", TestSuite::isReached("dummyShutdownHandler"));
                TEST_CASE("7","����åȥ�����ϥ�ɥ��EXIT_FAILURE������Ƥ���", dummyShutdownHandler_exit_code == EXIT_FAILURE);
            } END_CASE;

            BEGIN_CASE("3","bad_alloc�㳰���֤�") {
                TestSuite::clearCheckpoints();

                char * argv[] = { "test.exe" };

                Exception::setThrowControl(true);
                TestComponent test;
                test.mode = 2;

                TEST_CASE("1","main�ؿ���EXIT_FAILURE���֤�", main(1, argv) == EXIT_FAILURE);

                TEST_CASE("2","�б�����catch�Τߤ��¹Ԥ���Ƥ���", !TestSuite::isReached("catch(Exception)") && TestSuite::isReached("catch(bad_alloc)") && !TestSuite::isReached("catch(...)"));
                TEST_CASE("3","�������ȥ��åץϥ�ɥ餬��ư����Ƥ���", TestSuite::isReached("dummyStartupHandler"));
                TEST_CASE("4","����åȥ�����ϥ�ɥ餬��ư����Ƥ���", TestSuite::isReached("dummyShutdownHandler"));
                TEST_CASE("5","����åȥ�����ϥ�ɥ��EXIT_FAILURE������Ƥ���", dummyShutdownHandler_exit_code == EXIT_FAILURE);
            } END_CASE;
        } END_CASE;

        chain.restoreContext();
    }

}

#endif


