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
 *  @(#) $Id: collection.cpp,v 1.3 2003/12/15 07:32:13 takayuki Exp $
 */

// $Header: /home/CVS/configurator/base/collection.cpp,v 1.3 2003/12/15 07:32:13 takayuki Exp $

#include "base/collection.h"


using namespace std;

    //�ä˲��⤷�ʤ����󥹥ȥ饯��
Collection::Collection(void) throw()
{}

    //�ǥ��ȥ饯��
Collection::~Collection(void) throw()
{
        //ǰ�Τ�����㳰�ˤդ��򤹤�
    try { clear(); }
    catch(...) {}
}

    //���󥹥��󥹤򥳥쥯�������ɲ� (�������Ͽ��)
bool Collection::addInstance(Collectable * _instance, bool _destruction) throw()
{
    bool result = false;

    if(isValid() && _instance != 0) {

            // Ʊ�����󥹥��󥹤�2����Ͽ���ʤ��褦�ˤ���
        list<Element>::iterator scope;

        scope = container.begin();
        while(scope != container.end()) {
            if(scope->instance == _instance)
                break;
            ++ scope;
        }

        if(scope == container.end()) {
                // ���������Ǥ��ɲ�
            struct Element element;
            element.instance    = _instance;
            element.destruction = _destruction;
            container.push_back(element);
        }
        else {
                // �˴��ؼ��Ϻǿ���ľ���Ƥ���
            scope->destruction = _destruction;
        }

        result = true;
    }

    return result;
}

    //���ꤵ�줿Collectable���󥹥��󥹤������������ؤ����ƥ졼���μ��� (getInstance)
list<Collection::Element>::const_iterator Collection::_findInstance(const Collectable * predecessor) const throw()
{
    list<Element>::const_iterator result;

    result = container.begin();

        //predecessor�����ꤵ��Ƥ�������õ��
    if(predecessor != 0) {
        while(result != container.end()) {
            if(result->instance == predecessor) {
                ++ result;   //������predecessor�μ�����
                break;
            }
            ++ result;
        }
    }

    return result;
}

    //���쥯����󤫤饤�󥹥��󥹤����
Collectable * Collection::getInstance(const type_info & type, const Collectable * predecessor) const throw()
{
    Collectable * result;

    result = 0;
    if(isValid()) {

        list<Element>::const_iterator scope;

            // ��Ԥ��륤�󥹥��󥹤ξ���õ��
        scope = _findInstance(predecessor);

            // ���ꤵ�줿������ļ��Υ��󥹥��󥹤�õ��
        while(scope != container.end()) {
            if(typeid(*scope->instance) == type) {
                result = scope->instance;
                break;
            }
            ++ scope;
        }
    }

    return result;
}

    //���쥯����󤫤饤�󥹥��󥹤���� (�˴��Ϥ��ʤ�)
bool Collection::removeInstance(const Collectable * instance) throw()
{
    bool result = false;

    if(isValid() && instance != 0) {
        list<Element>::iterator scope;

        scope = container.begin();
        while(scope != container.end()) {
            if(scope->instance == instance) {
                    //���Ǥκ��
                container.erase(scope);
                result = true;
                break;
            }
            ++ scope;
        }
    }

    return result;
}

    //�����Ǥ��˴�
void Collection::clear(void)
{
    if(isValid()) {
        list<Element>::iterator scope;
        list<Element>::iterator next;

            //�˴��ե饰���Ĥ��Ƥ��륤�󥹥��󥹤��˴�
        scope = container.begin();
        while(scope != container.end()) {

            next = scope;       //ROT�Ϥ�delete����ȼ�ʬ��ä��ˤ�����Τǡ����ƥ졼������¸���뤿�����˼���������Ƥ���
            ++ next;

            if(scope->destruction)
                delete scope->instance;

            scope = next;
        }

        container.clear();
    }
}

/************************************************* �ƥ��ȥ������� *************************************************/

#ifdef TESTSUITE
#include "coverage_undefs.h"

class TestCollectable : public Collectable
{};

class TestCollectable2 : public Collectable
{   public: ~TestCollectable2(void) throw() { TestSuite::check("TestCollectable2::~TestCollectable2"); }   };

#ifdef _MSC_VER
class TestCollectable3 : public Collectable
{   public: ~TestCollectable3(void) throw(int) { throw 0; }   };
#endif

class TestCollectable4 : public TestCollectable2
{   public: ~TestCollectable4(void) throw() { TestSuite::check("TestCollectable4::~TestCollectable4"); }   };

TESTSUITE(main, Collection)
{
    BEGIN_CASE("addInstance","addInstance") {
        BEGIN_CASE("1","���󥹥��󥹤���������Ͽ�Ǥ���") {
            Collection col;
            TestCollectable test;
            TestCollectable2 test2;

            BEGIN_CASE("1","��Ͽ�Ǥ�TRUE���֤� (1����)") {
                if(!col.addInstance(&test,  false))
                    TEST_FAIL;
            } END_CASE;

            BEGIN_CASE("2","��Ͽ�Ǥ�true���֤� (2����)") {
                if(!col.addInstance(&test2, false))
                    TEST_FAIL;
            } END_CASE;

            BEGIN_CASE("3","�Ŀ�����äƤ�") {
                if(col.container.size() != 2)
                    TEST_FAIL;
            } END_CASE;

            BEGIN_CASE("4","���֤����äƤ�") {
            list<Element>::iterator scope;
                scope = col.container.begin();
                if(scope->instance != &test || scope->destruction != false)
                    TEST_FAIL;
                ++ scope;
                if(scope->instance != &test2 || scope->destruction != false)
                    TEST_FAIL;
                ++ scope;
                if(scope != col.container.end())
                    TEST_FAIL;
            } END_CASE;
        } END_CASE;

        BEGIN_CASE("2","NULL���󥹥��󥹤���Ͽ����ʤ�") {
            Collection col;

            BEGIN_CASE("1","NULL���󥹥��󥹤��Ϥ���false���֤�") {
                if(col.addInstance(0))
                    TEST_FAIL;
            } END_CASE;

            BEGIN_CASE("2","������Ͽ����Ƥ��ʤ�") {
                if(col.container.size() != 0)
                    TEST_FAIL;
            } END_CASE;
        } END_CASE;

        BEGIN_CASE("3","̵���ʥ��󥹥��󥹤��Ф�������false���֤�") {
            Collection col;

            if(col.addInstance(0))
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("4","Ʊ��Υ��󥹥��󥹤�2����Ͽ���Ƥ�1�Ĥ���������Ͽ����ʤ�") {
            Collection col;
            TestCollectable test;

            TEST_CASE("0","[����] ����ܤ���������������", col.addInstance(&test, false));

            TEST_CASE("1","�ؿ�����������λ����", col.addInstance(&test, false));
            TEST_CASE("2","���󥹥��󥹿��������Ƥ��ʤ�", col.container.size() == 1);

        } END_CASE;

    } END_CASE;

    BEGIN_CASE("getInstance(type_info)","getInstance(type_info)") {
        Collection col;
        TestCollectable test;
        TestCollectable test_2;
        TestCollectable test_3;
        TestCollectable2 test2;
        TestCollectable2 test2_2;
        TestCollectable2 test2_3;

        col.addInstance(test);
        col.addInstance(test2);
        col.addInstance(test_2);
        col.addInstance(test2_2);
        col.addInstance(test_3);
        col.addInstance(test2_3);

        Collectable * instance = 0;

        BEGIN_CASE("1","�ǽ�����Ǥ�����Ǥ���") {
            instance = col.getInstance(typeid(TestCollectable));
            if(instance != &test)
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("2","�������Ǥ�����Ǥ���") {
            instance = col.getInstance(typeid(TestCollectable), instance);
            if(instance != &test_2)
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("3","����˼������Ǥ�����Ǥ���") {
            instance = col.getInstance(typeid(TestCollectable), instance);
            if(instance != &test_3)
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("4","���Τޤ��������Ǥ����������NULL���֤�") {
            instance = col.getInstance(typeid(TestCollectable), instance);
            if(instance != 0)
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("5","�ǽ�����Ǥ�����Ǥ���") {
            instance = col.getInstance(typeid(TestCollectable2));
            if(instance != &test2)
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("6","�������Ǥ�����Ǥ���") {
            instance = col.getInstance(typeid(TestCollectable2), instance);
            if(instance != &test2_2)
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("7","����˼������Ǥ�����Ǥ���") {
            instance = col.getInstance(typeid(TestCollectable2), instance);
            if(instance != &test2_3)
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("8","���Τޤ��������Ǥ����������NULL���֤�") {
            instance = col.getInstance(typeid(TestCollectable), instance);
            if(instance != 0)
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("9","���쥯�饹�ǤϤҤä�����ʤ�") {
            instance = col.getInstance(typeid(Collectable));
            if(instance != 0)
                TEST_FAIL;
        } END_CASE;

        TEST_CASE("10","NULL���Ф��Ƽ¹Ԥ����NULL���֤�", ((Collection *)0)->getInstance(typeid(Collectable)) == 0);
    } END_CASE;

    BEGIN_CASE("getInstance<T>()","getInstance<T>()") {
        Collection col;
        TestCollectable test;
        TestCollectable test_2;
        TestCollectable test_3;
        TestCollectable2 test2;
        TestCollectable2 test2_2;
        TestCollectable2 test2_3;

        col.addInstance(test);
        col.addInstance(test2);
        col.addInstance(test_2);
        col.addInstance(test2_2);
        col.addInstance(test_3);
        col.addInstance(test2_3);

        Collectable * instance = 0;

        BEGIN_CASE("1","�ǽ�����Ǥ�����Ǥ���") {
            instance = col.getInstance<TestCollectable>();
            if(instance != &test)
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("2","�������Ǥ�����Ǥ���") {
            instance = col.getInstance<TestCollectable>(instance);
            if(instance != &test_2)
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("3","����˼������Ǥ�����Ǥ���") {
            instance = col.getInstance<TestCollectable>(instance);
            if(instance != &test_3)
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("4","���Τޤ��������Ǥ����������NULL���֤�") {
            instance = col.getInstance<TestCollectable>(instance);
            if(instance != 0)
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("5","�ǽ�����Ǥ�����Ǥ���") {
            instance = col.getInstance<TestCollectable2>();
            if(instance != &test2)
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("6","�������Ǥ�����Ǥ���") {
            instance = col.getInstance<TestCollectable2>(instance);
            if(instance != &test2_2)
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("7","����˼������Ǥ�����Ǥ���") {
            instance = col.getInstance<TestCollectable2>(instance);
            if(instance != &test2_3)
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("8","���Τޤ��������Ǥ����������NULL���֤�") {
            instance = col.getInstance<TestCollectable2>(instance);
            if(instance != 0)
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("9","���쥯�饹�ǰ��óݤ��� ����1") {
            instance = col.getInstance<Collectable>();
            if(instance != &test)
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("10","���쥯�饹�ǰ��óݤ��� ����2") {
            instance = col.getInstance<Collectable>(instance);
            if(instance != &test2)
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("11","���쥯�饹�ǰ��óݤ��� ����3") {
            instance = col.getInstance<Collectable>(instance);
            if(instance != &test_2)
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("12","���쥯�饹�ǰ��óݤ��� ����4") {
            instance = col.getInstance<Collectable>(instance);
            if(instance != &test2_2)
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("13","���쥯�饹�ǰ��óݤ��� ����5") {
            instance = col.getInstance<Collectable>(instance);
            if(instance != &test_3)
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("14","���쥯�饹�ǰ��óݤ��� ����6") {
            instance = col.getInstance<Collectable>(instance);
            if(instance != &test2_3)
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("15","���쥯�饹�ǰ��óݤ��� ����7") {
            instance = col.getInstance<Collectable>(instance);
            if(instance != 0)
                TEST_FAIL;
        } END_CASE;

        TEST_CASE("16","NULL���Ф��Ƽ¹Ԥ����NULL���֤�", ((Collection *)0)->getInstance<Collectable>() == 0);

    } END_CASE;

    BEGIN_CASE("removeInstance","removeInstance") {

        BEGIN_CASE("1","����˺���Ǥ���") {
            Collection col;
            TestCollectable test;
            TestCollectable test2;

            col.addInstance(test);
            col.addInstance(test2);

            BEGIN_CASE("1","¸�ߤ������Ǥ�remove������true") {
                if(!col.removeInstance(&test))
                    TEST_FAIL;
            } END_CASE;

            BEGIN_CASE("2","�����Ⱦä��Ƥ���") {
                if(col.container.size() != 1 || col.container.begin()->instance != &test2)
                    TEST_FAIL;
            } END_CASE;
        } END_CASE;

        BEGIN_CASE("2","NULL���󥹥��󥹤˼¹Ԥ����false") {
            if(((Collection *)0)->removeInstance(0))
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("3","��Ͽ���Ƥ��ʤ����󥹥��󥹤���ꤹ��ȼ��Ԥ���") {
            Collection col;
            TestCollectable test;
            TestCollectable test2;

            col.addInstance(test);

            if(col.removeInstance(&test2))
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("4","NULL���󥹥��󥹤��Ϥ��ȼ��Ԥ���") {
            Collection col;
            TestCollectable test;
            col.addInstance(test);

            if(col.removeInstance(0))
                TEST_FAIL;
        } END_CASE;
    } END_CASE;

    BEGIN_CASE("clear","clear") {
        BEGIN_CASE("1","���Τ���Ͽ����clear") {
            Collection col;
            TestCollectable2 test2;

            TestSuite::clearCheckpoints();
            col.addInstance(test2);
            col.clear();

            BEGIN_CASE("1","���Ǥ��ʤ��ʤäƤ���") {
                if(col.container.size() != 0)
                    TEST_FAIL;
            } END_CASE;

            TEST_CASE("2","test2���˴�����ʤ�", !TestSuite::isReached("TestCollectable2::~TestCollectable2"));
        } END_CASE;

        BEGIN_CASE("2","�ݥ��󥿤���Ͽ����clear") {
            Collection col;
            TestCollectable2 * test2 = new TestCollectable2;
            
            TestSuite::clearCheckpoints();
            col.addInstance(test2);
            col.clear();

            BEGIN_CASE("1","���Ǥ��ʤ��ʤäƤ���") {
                if(col.container.size() != 0)
                    TEST_FAIL;
            } END_CASE;

            TEST_CASE("2","test2���˴������", TestSuite::isReached("TestCollectable2::~TestCollectable2"));
        } END_CASE;

        BEGIN_CASE("3","NULL���֥������Ȥ��Ф��Ƽ¹Ԥ��Ƥ�˽�����ʤ�") {
            ((Collection *)0)->clear();
        } END_CASE;

#ifdef _MSC_VER
        BEGIN_CASE("4","�㳰���Ф�褦�ʥǥ��ȥ饯�����ĥ��󥹥��󥹤��˴�������㳰��ϳ���") {
            Collection col;
            bool result = false;
            TestCollectable3 * test = new TestCollectable3;

            col.addInstance(test);
            try {
                col.clear();
            }
            catch(...) {
                result = true;
            }


            if(!result)
                TEST_FAIL;
        } END_CASE;
#endif
    } END_CASE;

    BEGIN_CASE("destructor","destructor") {
        BEGIN_CASE("1","���Τ���Ͽ�����˴�") {
            Collection * col = new Collection;
            TestCollectable2 test2;

            TestSuite::clearCheckpoints();
            col->addInstance(test2);
            delete col;

            TEST_CASE("1","test2���˴�����ʤ�", !TestSuite::isReached("TestCollectable2::~TestCollectable2"));
        } END_CASE;

        BEGIN_CASE("2","�ݥ��󥿤���Ͽ����clear") {
            Collection * col = new Collection;
            TestCollectable2 * test2 = new TestCollectable2;

            TestSuite::clearCheckpoints();
            col->addInstance(test2);
            delete col;

            TEST_CASE("1","test2���˴������", TestSuite::isReached("TestCollectable2::~TestCollectable2"));
        } END_CASE;

#ifdef _MSC_VER
        BEGIN_CASE("3","�㳰���Ф�褦�ʥǥ��ȥ饯������ĥ��󥹥��󥹤��˴����Ƥ��㳰��ϳ��ʤ�") {
            Collection * col = new Collection;
            TestCollectable3 * test2 = new TestCollectable3;
            bool result = true;
            
            TestSuite::clearCheckpoints();
            col->addInstance(test2);

            try {
                delete col;
            }
            catch(...) {
                result = false;
            }

            if(!result)
                TEST_FAIL;
        } END_CASE;
#endif
    } END_CASE;

    BEGIN_CASE("deleteInstance","deleteInstance") {
        BEGIN_CASE("1","���󥹥��󥹤����Ǥ���") {
            Collection col;
            TestCollectable2 * test = new TestCollectable2;

            TestSuite::clearCheckpoints();
            col.addInstance(test);

            TEST_CASE("0","[����] ��������Ͽ����Ƥ���", col.getInstance<TestCollectable2>() != 0);

            col.deleteInstance<TestCollectable2>();
            TEST_CASE("1","���󥹥��󥹤��ä��Ƥ���", col.getInstance<TestCollectable2>() == 0);
            TEST_CASE("2","�ǥ��ȥ饯�����¹Ԥ���Ƥ���", TestSuite::isReached("TestCollectable2::~TestCollectable2"));
        }END_CASE;

        BEGIN_CASE("2","�ط��ʤ����饹����ꤷ����������ʤ�") {
            Collection col;
            TestCollectable2 * test = new TestCollectable2;

            TestSuite::clearCheckpoints();
            col.addInstance(test);

            TEST_CASE("0","[����] ��������Ͽ����Ƥ���", col.getInstance<TestCollectable2>() != 0);

            col.deleteInstance<TestCollectable>();
            TEST_CASE("1","���󥹥��󥹤��ä��Ƥ��ʤ�", col.getInstance<TestCollectable2>() != 0);
            TEST_CASE("2","�ǥ��ȥ饯�����¹Ԥ���Ƥ��ʤ�", !TestSuite::isReached("TestCollectable2::~TestCollectable2"));
            delete test;
        }END_CASE;

        BEGIN_CASE("3","Ʊ�����饹�����Ǥʤ��������ä���") {
            Collection col;
            TestCollectable2 * test = new TestCollectable2;
            TestCollectable4 * test2 = new TestCollectable4;

            TestSuite::clearCheckpoints();
            col.addInstance(test);
            col.addInstance(test2);

            TEST_CASE("0","[����] ��������Ͽ����Ƥ���", col.getInstance(typeid(TestCollectable2)) != 0);
            TEST_CASE("0","[����] ��������Ͽ����Ƥ���", col.getInstance(typeid(TestCollectable4)) != 0);

            col.deleteInstance<TestCollectable2>();
            TEST_CASE("1","���󥹥��󥹤����٤ƾä��Ƥ���", col.getInstance<TestCollectable2>() == 0);
            TEST_CASE("2","TestCollectable2�Υǥ��ȥ饯�����¹Ԥ���Ƥ���", TestSuite::isReached("TestCollectable2::~TestCollectable2"));
            TEST_CASE("3","TestCollectable4�Υǥ��ȥ饯�����¹Ԥ���Ƥ���", TestSuite::isReached("TestCollectable4::~TestCollectable4"));
        }END_CASE;

        BEGIN_CASE("4","���Τ��˴��оݤˤʤ�ʤ�") {
            Collection col;
            TestCollectable2 test;

            TestSuite::clearCheckpoints();
            col.addInstance(test);

            TEST_CASE("0","[����] ��������Ͽ����Ƥ���", col.getInstance<TestCollectable2>() != 0);

            col.deleteInstance<TestCollectable2>();
            TEST_CASE("1","���󥹥��󥹤��ä��Ƥ���", col.getInstance<TestCollectable2>() == 0);
            TEST_CASE("2","�ǥ��ȥ饯�����¹Ԥ���Ƥ��ʤ�", !TestSuite::isReached("TestCollectable2::~TestCollectable2"));
        }END_CASE;

        BEGIN_CASE("5","NULL���֥������Ȥ��Ф���ȯ�Ԥ��Ƥ�˽�����ʤ�") {
            ((Collection *)0)->deleteInstance<TestCollectable>();
        } END_CASE;

    } END_CASE;

    BEGIN_CASE("replaceInstance","replaceInstance") {
        BEGIN_CASE("1","��Ͽ�ѤߤΥ��󥹥��󥹤������ؤ���") {
            Collection col;
            TestCollectable2 test;
            TestCollectable2 test2;

            TestSuite::clearCheckpoints();
            col.addInstance(test);

            TEST_CASE("0","[����] ��������Ͽ����Ƥ���", col.getInstance(typeid(TestCollectable2)) != 0);
            
            TEST_CASE("1", "�ؿ�����������", col.replaceInstance<TestCollectable2>(test2));
            TEST_CASE("2", "���󥹥��󥹤������ؤ�äƤ���", col.getInstance(typeid(TestCollectable2)) == &test2);
            TEST_CASE("3", "test2�ʳ��˥��󥹥��󥹤Ϥʤ�", col.getInstance(typeid(TestCollectable2), &test2) == 0);
            TEST_CASE("4", "�ǥ��ȥ饯���ϼ¹Ԥ���Ƥʤ�", !TestSuite::isReached("TestCollectable2::~TestCollectable2"));
        } END_CASE;

        BEGIN_CASE("2","��Ͽ�ѤߤΥ��󥹥��󥹤��������饹�Υ��󥹥��󥹤������ؤ���") {
            Collection col;
            TestCollectable2 test;
            TestCollectable4 test2;

            TestSuite::clearCheckpoints();
            col.addInstance(test);

            TEST_CASE("0","[����] ��������Ͽ����Ƥ���", col.getInstance(typeid(TestCollectable2)) != 0);
            
            TEST_CASE("1", "�ؿ�����������", col.replaceInstance<TestCollectable2>(test2));
            TEST_CASE("2", "���󥹥��󥹤������ؤ�äƤ���", col.getInstance<TestCollectable2>() == &test2);
            TEST_CASE("3", "test2�ʳ��˥��󥹥��󥹤Ϥʤ�", col.getInstance(typeid(TestCollectable2)) == 0);
            TEST_CASE("4", "�ǥ��ȥ饯���ϼ¹Ԥ���Ƥʤ�", !TestSuite::isReached("TestCollectable2::~TestCollectable2"));
        } END_CASE;

        BEGIN_CASE("3","̵�ط��ʥ��饹����ꤷ�������ؤ���") {
            Collection col;
            TestCollectable2 test;
            TestCollectable4 test2;

            TestSuite::clearCheckpoints();
            col.addInstance(test);

            TEST_CASE("0","[����] ��������Ͽ����Ƥ���", col.getInstance(typeid(TestCollectable2)) != 0);
            
            TEST_CASE("1", "�ؿ��ϼ��Ԥ���", !col.replaceInstance<TestCollectable>(test2));
            TEST_CASE("2", "���󥹥��󥹤ϻĤäƤ���", col.getInstance<TestCollectable2>() == &test);
        } END_CASE;

        BEGIN_CASE("4","��Ͽ�ѤߤΥ��󥹥��󥹤������ؤ��� (ưŪ����)") {
            Collection col;
            TestCollectable2 * test = new TestCollectable2;
            TestCollectable2 test2;

            TestSuite::clearCheckpoints();
            col.addInstance(test);

            TEST_CASE("0","[����] ��������Ͽ����Ƥ���", col.getInstance(typeid(TestCollectable2)) != 0);
            
            TEST_CASE("1", "�ؿ�����������", col.replaceInstance<TestCollectable2>(test2));
            TEST_CASE("2", "���󥹥��󥹤������ؤ�äƤ���", col.getInstance(typeid(TestCollectable2)) == &test2);
            TEST_CASE("3", "test2�ʳ��˥��󥹥��󥹤Ϥʤ�", col.getInstance(typeid(TestCollectable2), &test2) == 0);
            TEST_CASE("4", "�ǥ��ȥ饯���ϼ¹Ԥ���Ƥ�", TestSuite::isReached("TestCollectable2::~TestCollectable2"));
        } END_CASE;

    } END_CASE;
}


class TestRuntimeObject : public RuntimeObject
{
public:
    TestRuntimeObject(void) { CHECKPOINT("TestRuntimeObject::TestRuntimeObject"); }
    ~TestRuntimeObject(void) { CHECKPOINT("TestRuntimeObject::~TestRuntimeObject"); }
};

class TestRuntimeObject2 : public RuntimeObject
{
public:
    TestRuntimeObject2(void) : RuntimeObject(true) { CHECKPOINT("TestRuntimeObject2::TestRuntimeObject2"); }
    ~TestRuntimeObject2(void) { CHECKPOINT("TestRuntimeObject2::~TestRuntimeObject2"); }
};

TESTSUITE(main, RuntimeObjectTable)
{
    Singleton<RuntimeObjectTable>::Context context;
    Singleton<RuntimeObjectTable>::saveContext(context);

    BEGIN_CASE("getInstance","getInstance") {
        BEGIN_CASE("1","getInstance����������ǽ����") {
            Singleton<RuntimeObjectTable>::renewInstance();
            TestCollectable test;

            Singleton<RuntimeObjectTable>::getInstance()->addInstance(test);

            BEGIN_CASE("1","getInstance(typeid)") {
                if(RuntimeObjectTable::getInstance(typeid(TestCollectable)) != &test)
                    TEST_FAIL;
            } END_CASE;

            BEGIN_CASE("2","getInstance<T>()") {
                if(RuntimeObjectTable::getInstance<TestCollectable>() != &test)
                    TEST_FAIL;
            } END_CASE;
        } END_CASE;
    } END_CASE;

    BEGIN_CASE("RuntimeObject","RuntimeObject") {
        BEGIN_CASE("1","�����������Ͽ���졢�˴��Ǿ��Ǥ���") {
            TestRuntimeObject * ro;

            TestSuite::clearCheckpoints();

            TEST_CASE("0","[����] ��Ͽ����Ƥ��ʤ�", RuntimeObjectTable::getInstance<TestRuntimeObject>() == 0);

            ro = new TestRuntimeObject;

            TEST_CASE("1","���󥹥ȥ饯�����¹Ԥ���Ƥ���", TestSuite::isReached("TestRuntimeObject::TestRuntimeObject"));
            TEST_CASE("2","��Ͽ����Ƥ���", RuntimeObjectTable::getInstance<TestRuntimeObject>() == ro);

            delete ro;

            TEST_CASE("3","�ǥ��ȥ饯�����¹Ԥ���Ƥ���", TestSuite::isReached("TestRuntimeObject::~TestRuntimeObject"));
            TEST_CASE("4","��Ͽ���������Ƥ���", RuntimeObjectTable::getInstance<TestRuntimeObject>() == 0);

        } END_CASE;

        BEGIN_CASE("2","��ư�˴��Υ����å�") {
            TestRuntimeObject * ro;
            TestRuntimeObject2 * ro2;

            TestSuite::clearCheckpoints();

            TEST_CASE("0","[����] ��Ͽ����Ƥ��ʤ�", RuntimeObjectTable::getInstance<TestRuntimeObject>() == 0);
            TEST_CASE("0","[����] ��Ͽ����Ƥ��ʤ�", RuntimeObjectTable::getInstance<TestRuntimeObject2>() == 0);

            ro = new TestRuntimeObject;
            ro2 = new TestRuntimeObject2;

            TEST_CASE("1","���󥹥ȥ饯�����¹Ԥ���Ƥ���(ro)", TestSuite::isReached("TestRuntimeObject::TestRuntimeObject"));
            TEST_CASE("2","���󥹥ȥ饯�����¹Ԥ���Ƥ���(ro2)", TestSuite::isReached("TestRuntimeObject2::TestRuntimeObject2"));
            TEST_CASE("3","��Ͽ����Ƥ���(ro)", RuntimeObjectTable::getInstance<TestRuntimeObject>() == ro);
            TEST_CASE("4","��Ͽ����Ƥ���(ro2)", RuntimeObjectTable::getInstance<TestRuntimeObject2>() == ro2);

            Singleton<RuntimeObjectTable>::getInstance()->clear();

            TEST_CASE("5","�ǥ��ȥ饯���ϼ¹Ԥ���Ƥ��ʤ� (ro)", !TestSuite::isReached("TestRuntimeObject::~TestRuntimeObject"));
            TEST_CASE("6","�ǥ��ȥ饯���ϼ¹Ԥ���Ƥ��� (ro2)", TestSuite::isReached("TestRuntimeObject2::~TestRuntimeObject2"));
            TEST_CASE("7","��Ͽ���������Ƥ���", RuntimeObjectTable::getInstance<TestRuntimeObject>() == 0);
            TEST_CASE("8","��Ͽ���������Ƥ���", RuntimeObjectTable::getInstance<TestRuntimeObject2>() == 0);

            delete ro;
        } END_CASE;

    } END_CASE;

    Singleton<RuntimeObjectTable>::restoreContext(context);
}

#endif

