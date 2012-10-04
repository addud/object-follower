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
 *  @(#) $Id: component.cpp,v 1.13 2003/12/15 07:32:13 takayuki Exp $
 */

// $Header: /home/CVS/configurator/base/component.cpp,v 1.13 2003/12/15 07:32:13 takayuki Exp $

#include "base/component.h"

#include <iostream>

using namespace std;

    //����ݡ��ͥ�����Τ����ѤǤ���ʤ�true
bool Component::is_valid = true;

    //����ݡ��ͥ�Ȥ���Ͽ
bool Component::ComponentInfo::addComponent(Component * component, int order) throw()
{
    bool result = false;

    if(this != 0 && component != 0) {
        componentList.insert(multimap<int, Component *>::value_type(order, component));
        result = true;
    }

    return result;
}

    //����ݡ��ͥ�Ȥ���Ͽ���
void Component::ComponentInfo::removeComponent(Component * component, int order) throw()
{
    if(this != 0 && component != 0) {
        multimap<int, Component *>::iterator scope;

        scope = componentList.lower_bound(order);
        while(scope != componentList.end()) {
                //�⤦���ꤵ�줿ͥ���٤Ϥ��٤Ƹ���
            if(scope->first != order)
                break;
        
                //���ꤵ�줿����ݡ��ͥ�Ȥ˰��פ�������
            if(scope->second == component) {
                multimap<int, Component *>::iterator target = scope;
                ++ scope;
                componentList.erase(target);
            }
            else
                ++ scope;
        }
    }
}

    //����ݡ��ͥ�Ȥ���Ͽ���
void Component::ComponentInfo::removeComponent(Component * component) throw()
{
    if(this != 0 && component != 0) {
        multimap<int, Component *>::iterator scope;

            //���ꤵ�줿����ݡ��ͥ�Ȥ˰��פ����Τ����ƺ��
        scope = componentList.begin();
        while(scope != componentList.end()) {
            if(scope->second == component) {
                multimap<int, Component *>::iterator target = scope;
                ++ scope;
                componentList.erase(target);
            }
            else
                ++ scope;
        }

    }
}

    //����ݡ��ͥ�Ȥε�ư�׵��ȯ��
bool Component::ComponentInfo::activateComponent(Component * component) throw()
{
    bool result = false;

    if(this != 0 && component != 0) {
            //��ư�׵�������˲ä���
        activatedComponentList.push_back(component);
        result = true;
    }

    return result;
}

    //���ץ����Υѡ���
void Component::ComponentInfo::parseOption(OptionParameter & option)
{
    if(this != 0) {
        multimap<int, Component *>::iterator scope;

            //���ƤΥ���ݡ��ͥ�Ȥ�parseOption��¹�
        scope = componentList.begin();
        while(scope != componentList.end()) {
            DebugMessage("Component::parseOption start  - %\n") << typeid(*scope->second).name();
            scope->second->parseOption(option);
            DebugMessage("Component::parseOption finish - %\n") << typeid(*scope->second).name();
            ++ scope;
        }
    }
}

    //����ݡ��ͥ�Ȥε�ư
void Component::ComponentInfo::activateComponent(void)
{
    if(this != 0) {
        list<Component *>::iterator scope;

        try {
                //��ư�׵�Τ��ä����ƤΥ���ݡ��ͥ�Ȥ�ư
            scope = activatedComponentList.begin();
            while(scope != activatedComponentList.end()) {
                DebugMessage("Component::body start  - %\n") << typeid(**scope).name();
                (*scope)->body();
                DebugMessage("Component::body finish - %\n") << typeid(**scope).name();
                ++ scope;
            }
                //�׵�ꥹ�Ȥ򥯥ꥢ
            activatedComponentList.clear();
        }
        catch(...) {
                //onFatalExit�Ѥˡ�activatedComponentList��ư�򤫤�������ݡ��ͥ�Ȥ����˹ʤ�
            ++ scope;
            if(scope != activatedComponentList.end())
                activatedComponentList.erase(scope, activatedComponentList.end());
        
            throw;
        }
    }
}

    //�۾�����ϥ�ɥ�ε�ư
void Component::ComponentInfo::onFatalExit(void)
{
    if(this != 0) {
        Component * handler;

            //��ư�׵�Τ��ä����ƤΥ���ݡ��ͥ�Ȥ�ư
        while(!activatedComponentList.empty()) {
            handler = *activatedComponentList.begin();
            activatedComponentList.pop_front();

                //�ϥ�ɥ��ư
            DebugMessage("Component::onFatalExit start  - %\n") << typeid(*handler).name();
            handler->onFatalExit();
            DebugMessage("Component::onFatalExit fihish - %\n") << typeid(*handler).name();
        }
            //�׵�ꥹ�Ȥ򥯥ꥢ
        activatedComponentList.clear();
    }
}


/*
 *   Component : ����ݡ��ͥ��
 */

    //���󥹥ȥ饯��
Component::Component(int order) throw() : RuntimeObject()
{
        //�����ǽ��ƥ��󥰥�ȥ󥤥󥹥��󥹤˥�����������Τǡ�bad_alloc��ȯ�������ǽ��������
    try {
        Singleton<ComponentInfo>::getInstance()->addComponent(this, order);
    }
    catch(bad_alloc) {
        is_valid = false;
    }
}

    //�ǥ��ȥ饯��
Component::~Component(void) throw()
{   Singleton<ComponentInfo>::getInstance()->removeComponent(this);   }

    //����ݡ��ͥ�Ȥμ¹�
void Component::executeComponents(int argc, char * argv [])
{
    OptionParameter & option = getOptionParameter();

    option.parseOption(argc, argv);
    executeComponents(option);
}

    //����ݡ��ͥ�Ȥμ¹�
void Component::executeComponents(OptionParameter & option)
{
    if(isValid()) {

        _parseCommonOption(option);

        try {
                //���ץ����Υѡ���
            Singleton<ComponentInfo>::getInstance()->parseOption(option);

                //���ƤΥ��ץ���󤬻��ѺѤߤǤʤ���Х��顼
            if(!option.validateOption()) {
                CHECKPOINT("Exception_UnknownOption");
                ExceptionMessage("Unknown option [%] found.","�����ʥ��ץ���󤬻��ꤵ�줿 : %") << option.getInvalidOptions() << throwException;
            }
            else {
                    //����ݡ��ͥ�Ȥμ¹�
                Singleton<ComponentInfo>::getInstance()->activateComponent(); 
            }
        }

            //�㳰��ȯ�� -> �۾ｪλ�ϥ�ɥ�ε�ư
        catch(...) {
            bool continuation;
            do {
                try {
                    continuation = true;
                    Singleton<ComponentInfo>::getInstance()->onFatalExit();
                    continuation = false;
                }
                catch(Exception & e) {
                    CHECKPOINT("Exception_onFatalExit");
                    cerr << Message("[Internal error] onFatalExit threw an exception! : ","[�������顼] onFatalExit����㳰! : ") << e.getDetails() << '\n';
                }
            } while(continuation);

            throw;
        }
    }
}


    //����Ū�ʥ��ץ����ν���
void Component::_parseCommonOption(OptionParameter & option) throw()
{
        //�ǥХå�����
    if(option.find("debug")) {
        DebugMessage::setStream(&cerr);
        DebugMessage::setVerbose(true);
    }

        //��������
    if(option.find("lj") || option.find("-japanese"))
        Message::selectLanguage(Message::JAPANESE);
    if(option.find("le") || option.find("-english"))
        Message::selectLanguage(Message::ENGLISH);

        //��Ĺ��å�����
    if(option.find("v") || option.find("-verbose")) {
        VerboseMessage::setStream(&cout);
        VerboseMessage::setVerbose(true);
    }

        //�Хʡ�ɽ��
    if(!getBanner().empty() && option.find("v") || option.find("-verbose") || option.find("h") || option.find("-help"))
        cout << getBanner() << endl;

        //�إ��ɽ��
    if(option.find("h") || option.find("-help"))
        cout << '\n' << Message(
            "Global option\n"
            " -lj, --japanese : Use Japanese as default language\n"
            " -le, --english  : Use English as default language\n"
            " -v,  --verbose  : Verbose Message\n",
            "���ΤΥ��ץ����\n"
            " -lj, --japanese : ���ܸ��ɽ�����ޤ�\n"
            " -le, --english  : �Ѹ��ɽ�����ޤ�\n"
            " -v,  --verbose  : ��Ĺ��å���������Ϥ��ޤ�\n");
}

    //�Хʡ���������
void Component::setBanner(string src) throw(bad_alloc)
{
    ComponentInfo * info = Singleton<ComponentInfo>::getInstance();
    info->setBanner(src);
}

string Component::getBanner(void) throw(bad_alloc)
{
    ComponentInfo * info = Singleton<ComponentInfo>::getInstance();
    return info->getBanner();
}

/*
 *   ���Ȥθߴ����Τ���Υѥ�᡼�����API
 */

    /* ���ꤵ�줿���ץ�����¸�ߤ��ǧ����ɬ�פǤ���Ф��Υѥ�᡼����������� */
bool Component::findOption(const char * key1, const char * key2, std::string * element) throw()
{
    OptionParameter::OptionItem item;

    item = getOption(key1, key2, true);
    if(item.isValid() && element != 0 && item.hasParameter())
        *element = item[0];

    return item.isValid();
}

    /* ¸�߳�ǧ + �����å���Ĥ��� */
bool Component::checkOption(const char * key1, const char * key2) throw()
{   return getOption(key1, key2, true).isValid();   }

    /* ���ꤵ�줿̾���Υ��ץ����ѥ�᡼������� */
OptionParameter::OptionItem Component::getOption(const char * key1, const char * key2, bool dirty) throw()
{
    OptionParameter::OptionItem item;
        
    if(key1 != 0)
        item = getOptionParameter().get(key1, dirty);
        
    if(key2 != 0) {
        if(item.isValid())
            item.mergeItem(getOptionParameter().get(string("-") + key2, dirty));
        else
            item = getOptionParameter().get(string("-") + key2, dirty);
    }

    return item;
}

    /* 2�ĤΥ��ץ������ܤ�ޡ������� (���äƤ����Ƥ�ޡ��������Τǵ��ˤ��ʤ�) */
OptionParameter::OptionItem Component::mergeOption(const char * key1, const char * key2) throw()
{   return getOption(key1, key2);   }



/****************************************************** �ƥ��ȥ������� ******************************************************/

#ifdef TESTSUITE
#include "coverage_undefs.h"

namespace {
    int counter = 0;

    class TestComponent : public Component
    {
    public:
        bool         check_parseOption;
        bool         check_body;
        bool         check_onFatalExit;
        bool         activation;
        bool         throw_parseOption;
        bool         throw_body;
        bool         throw_onFatalExit;
        int          actcnt;

        TestComponent(int order = GENERAL_PURPOSE) : Component(order)
        {
            check_parseOption = false;
            check_body        = false;
            check_onFatalExit = false;
            activation        = false;
            throw_parseOption = false;
            throw_body        = false;
            throw_onFatalExit = false;
        }

        void parseOption(OptionParameter & option) throw(Exception)
        {
            actcnt = ++counter;
            check_parseOption = true;
            if(activation)
                activateComponent();
            if(throw_parseOption)
                ExceptionMessage("exception","exception").throwException();
        }

        void body(void) throw(Exception)
        {
            actcnt = ++counter;
            check_body = true;
            if(throw_body)
                ExceptionMessage("exception","exception").throwException();
        }

        void onFatalExit(void) throw(Exception)
        {
            actcnt = ++counter;
            check_onFatalExit = true;
            if(throw_onFatalExit)
                ExceptionMessage("exception","exception").throwException();
        }
    };

    class DerivedTestComponent : public TestComponent
    {};
}


TESTSUITE_(main,ComponentInfo,Component)
{
    Singleton<ComponentInfo>::Context context;
    Singleton<ComponentInfo>::saveContext(context);
    Singleton<ComponentInfo>::renewInstance();

    BEGIN_CASE("addComponent","addComponent") {

        BEGIN_CASE("1","�������ɲäǤ���") {
            ComponentInfo info;

            BEGIN_CASE("1","�ؿ�����������") {
                if(!info.addComponent((Component *)0x1234, 10))
                    TEST_FAIL;
            } END_CASE;

            BEGIN_CASE("2","�ɲä���Ƥ���") {
                if(info.componentList.size() != 1)
                    TEST_FAIL;
            } END_CASE;

            BEGIN_CASE("3", "���Ƥ�������") {
                if(info.componentList.begin()->first != 10 || info.componentList.begin()->second != (Component *)0x1234)
                    TEST_FAIL;
            } END_CASE;
        } END_CASE;

        BEGIN_CASE("2","NULL���󥹥��󥹤���Ͽ�Ǥ��ʤ�") {
            ComponentInfo info;

            BEGIN_CASE("1","�ؿ��ϼ��Ԥ���") {
                if(info.addComponent(0, 10))
                    TEST_FAIL;
            } END_CASE;

            BEGIN_CASE("2","���Ǥ��ɲä���Ƥ��ʤ�") {
                if(info.componentList.size() != 0)
                    TEST_FAIL;
            } END_CASE;
        } END_CASE;

        BEGIN_CASE("3","NULL���󥹥��󥹤������false���֤�") {
            if(((ComponentInfo *)0)->addComponent((Component *)0x1234, 10))
                TEST_FAIL;
        } END_CASE;

    } END_CASE;

    BEGIN_CASE("removeComponent(Component *, int)","removeComponent(Component *, int)") {
        BEGIN_CASE("1", "����������Ǥ���") {
            ComponentInfo info;

            info.addComponent((Component *)0x0123, 10); //38���ܤ�if��else��¹Ԥ����뤿��Υ��ߡ�
            info.addComponent((Component *)0x1234, 10);
            info.addComponent((Component *)0x1234, 20);

            info.removeComponent((Component *)0x1234, 10);
            info.removeComponent((Component *)0x0123, 10);

            BEGIN_CASE("1","���ǿ���1") {
                if(info.componentList.size() != 1)
                    TEST_FAIL;
            } END_CASE;

            BEGIN_CASE("2","�Ĥä����Ǥ�order��20") {
                if(info.componentList.begin()->first != 20)
                    TEST_FAIL;
            } END_CASE;
        } END_CASE;

        BEGIN_CASE("2", "NULL���֥������Ȥ���¹Ԥ��Ƥ������") {
            ((ComponentInfo *)0)->removeComponent(0, 0);
        } END_CASE;
    } END_CASE;
            
    BEGIN_CASE("removeComponent(Component *)","removeComponent(Component *)") {
        BEGIN_CASE("1", "����������Ǥ���") {
            ComponentInfo info;
            multimap<int, Component *>::iterator scope;

            info.addComponent((Component *)0x1234, 10);
            info.addComponent((Component *)0x1235, 10);
            info.addComponent((Component *)0x1234, 20);
            info.addComponent((Component *)0x1235, 20);

            info.removeComponent((Component *)0x1234);

            BEGIN_CASE("1","���ǿ���2") {
                if(info.componentList.size() != 2)
                    TEST_FAIL;
            } END_CASE;

            scope = info.componentList.begin();
            BEGIN_CASE("2","�Ĥä����Ǥ����Ƥ�������") {
                if(scope->first != 10 || scope->second != (Component *)0x1235)
                    TEST_FAIL;
                ++ scope;
                if(scope->first != 20 || scope->second != (Component *)0x1235)
                    TEST_FAIL;
            } END_CASE;
        } END_CASE;

        BEGIN_CASE("2", "NULL���֥������Ȥ���¹Ԥ��Ƥ������") {
            ((ComponentInfo *)0)->removeComponent(0);
        } END_CASE;
    } END_CASE;

    BEGIN_CASE("activateComponent","activateComponent") {
        BEGIN_CASE("1","������ɲäǤ���") {
            ComponentInfo info;

            BEGIN_CASE("1","�ؿ�����������") {
                if(!info.activateComponent((Component *)0x1234))
                    TEST_FAIL;
            } END_CASE;

            BEGIN_CASE("2","��ư�׵�ꥹ�Ȥ��������ɲä���Ƥ���") {
                if(info.activatedComponentList.size() != 1)
                    TEST_FAIL;
                if(*info.activatedComponentList.begin() != (Component *)0x1234)
                    TEST_FAIL;
            } END_CASE;

            BEGIN_CASE("3","NULL���֥������Ȥ���ȯ�Ԥ��Ƥ�˽�����ʤ�") {
                ((ComponentInfo *)0)->activateComponent();
            } END_CASE;
        } END_CASE;

        BEGIN_CASE("1","NULL���󥹥��󥹤��ɲä���ʤ�") {
            ComponentInfo info;

            BEGIN_CASE("1","�ؿ��ϼ��Ԥ���") {
                if(info.activateComponent((Component *)0))
                    TEST_FAIL;
            } END_CASE;

            BEGIN_CASE("2","��ư�׵�ꥹ�Ȥ϶��Τޤ�") {
                if(!info.activatedComponentList.empty())
                    TEST_FAIL;
            } END_CASE;
        } END_CASE;
    } END_CASE;

    BEGIN_CASE("Component::Component","Component::Component") {
        Singleton<ComponentInfo>::renewInstance();
        TestComponent * test = 0;

        BEGIN_CASE("0","�������������") {
            if(Singleton<ComponentInfo>::getInstance()->componentList.size() != 0)
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("1","Component�򥤥󥹥��󥹲�����ȡ��������Ͽ�����") {
            test = new TestComponent;
            if(Singleton<ComponentInfo>::getInstance()->componentList.size() != 1)
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("2","��Ͽ����Ƥ������Ƥ�������") {
            if(Singleton<ComponentInfo>::getInstance()->componentList.begin()->second != test)
                TEST_FAIL;
        } END_CASE;
            
        BEGIN_CASE("3","�˴�����ȥ���ȥ꤬�ä���") {
            delete test;
            if(Singleton<ComponentInfo>::getInstance()->componentList.size() != 0)
                TEST_FAIL;
        } END_CASE;
    } END_CASE;

    BEGIN_CASE("parseOption","parseOption") {

        BEGIN_CASE("1","parseOption��¹Ԥ������Ͽ���줿����ݡ��ͥ�Ȥ�parseOption���¹Ԥ����") {
            Singleton<ComponentInfo>::renewInstance();

            TestComponent test;
            TestComponent test2;

            Singleton<ComponentInfo>::getInstance()->parseOption(getOptionParameter());

            if(!test.check_parseOption || !test2.check_parseOption)
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("2","��ư����������� (Ʊ���٥�ʤ���Ͽ��)") {
            Singleton<ComponentInfo>::renewInstance();

            TestComponent test;
            TestComponent test2;

            counter = 0;
            Singleton<ComponentInfo>::getInstance()->parseOption(getOptionParameter());

            if(test.actcnt != 1 || test2.actcnt != 2 )
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("3","��ư����������� (ͥ���ٽ�)") {
            Singleton<ComponentInfo>::renewInstance();

            TestComponent test(10);
            TestComponent test2(1);

            counter = 0;
            Singleton<ComponentInfo>::getInstance()->parseOption(getOptionParameter());

            if(test.actcnt != 2 || test2.actcnt != 1 )
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("4","activate�򤫤����activateList����Ͽ�����") {
            Singleton<ComponentInfo>::renewInstance();

            TestComponent test;
            TestComponent test2;
            list<Component *>::iterator scope;

            test.activation = true;
            test2.activation = true;
            Singleton<ComponentInfo>::getInstance()->parseOption(getOptionParameter());

            if(Singleton<ComponentInfo>::getInstance()->activatedComponentList.size() != 2)
                TEST_FAIL;
            scope = Singleton<ComponentInfo>::getInstance()->activatedComponentList.begin();
            if(*scope != &test)
                TEST_FAIL;
            ++ scope;
            if(*scope != &test2)
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("5","�㳰��ȴ���Ƥ���") {
            Singleton<ComponentInfo>::renewInstance();

            TestComponent test;
            TestComponent test2;
            list<Component *>::iterator scope;
            bool result = false;

            Exception::setThrowControl(true);
            test.throw_parseOption = true;
            try {
                Singleton<ComponentInfo>::getInstance()->parseOption(getOptionParameter());
            }
            catch(...) {
                result = true;
            }

            if(!result)
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("6","�㳰������Ͽ���줿activate�ϻĤ�") {
            Singleton<ComponentInfo>::renewInstance();

            TestComponent test;
            TestComponent test2;
            list<Component *>::iterator scope;
            bool result = false;

            Exception::setThrowControl(true);
            test.activation = true;
            test2.throw_parseOption = true;
            try {
                Singleton<ComponentInfo>::getInstance()->parseOption(getOptionParameter());
            }
            catch(...) {
                result = true;
            }

            if(!result)
                TEST_FAIL;

            if(Singleton<ComponentInfo>::getInstance()->activatedComponentList.size() != 1)
                TEST_FAIL;

            if(*Singleton<ComponentInfo>::getInstance()->activatedComponentList.begin() != &test)
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("7","NULL���󥹥��󥹤���Υ�������Ѥ���") {
            ((ComponentInfo *)0)->parseOption(getOptionParameter());
        } END_CASE;
    }END_CASE;

    BEGIN_CASE("activateCompoent/Component::body","activateCompoent/Component::body") {
        BEGIN_CASE("1","activateComponent�򤹤�ȡ���ư�׵��Ф�������ݡ��ͥ�Ȥ���ư�����") {
            Singleton<ComponentInfo>::renewInstance();

            TestComponent test;
            TestComponent test2;

            test.activation = true;
            test2.activation = true;
            Singleton<ComponentInfo>::getInstance()->parseOption(getOptionParameter());
            Singleton<ComponentInfo>::getInstance()->activateComponent();

            if(!test.check_body || !test2.check_body)
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("2","��ư�׵��Ф��ʤ�����ݡ��ͥ�Ȥϵ�ư����ʤ�") {
            Singleton<ComponentInfo>::renewInstance();

            TestComponent test;
            TestComponent test2;

            test.activation = false;
            test2.activation = true;
            Singleton<ComponentInfo>::getInstance()->parseOption(getOptionParameter());
            Singleton<ComponentInfo>::getInstance()->activateComponent();

            if(test.check_body || !test2.check_body)
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("3","��ư����������� (Ʊ���٥�ʤ���Ͽ��)") {
            Singleton<ComponentInfo>::renewInstance();

            TestComponent test;
            TestComponent test2;
            counter = 0;

            test.activation = test2.activation = true;
            Singleton<ComponentInfo>::getInstance()->parseOption(getOptionParameter());
            Singleton<ComponentInfo>::getInstance()->activateComponent();

            if(test.actcnt != 3 || test2.actcnt != 4 )
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("4","��ư����������� (ͥ���ٽ�)") {
            Singleton<ComponentInfo>::renewInstance();

            TestComponent test(10);
            TestComponent test2(4);
            counter = 0;

            test.activation = test2.activation = true;
            Singleton<ComponentInfo>::getInstance()->parseOption(getOptionParameter());
            Singleton<ComponentInfo>::getInstance()->activateComponent();

            if(test.actcnt != 4 || test2.actcnt != 3 )
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("5","�㳰��ȴ���Ƥ���") {
            Singleton<ComponentInfo>::renewInstance();

            TestComponent test;
            TestComponent test2;
            list<Component *>::iterator scope;
            bool result = false;

            Exception::setThrowControl(true);
            test.activation = test2.activation = true;
            test.throw_body = true;
            Singleton<ComponentInfo>::getInstance()->parseOption(getOptionParameter());
            try {
                Singleton<ComponentInfo>::getInstance()->activateComponent();
            }
            catch(...) {
                result = true;
            }

            if(!result)
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("6","�㳰�򵯤������顢����ޤǤ˵�ư��������ݡ��ͥ�Ȥ�activatedComponentList�˻Ĥ�") {
            Singleton<ComponentInfo>::renewInstance();

            TestComponent test;
            TestComponent test2;
            bool result = false;

            Exception::setThrowControl(true);
            test.activation = test2.activation = true;
            test.throw_body = true;
            Singleton<ComponentInfo>::getInstance()->parseOption(getOptionParameter());
            try {
                Singleton<ComponentInfo>::getInstance()->activateComponent();
            }
            catch(...) {
                result = true;
            }

            if(!result)
                TEST_FAIL;

            if(Singleton<ComponentInfo>::getInstance()->activatedComponentList.size() != 1)
                TEST_FAIL;

            if(*Singleton<ComponentInfo>::getInstance()->activatedComponentList.begin() != &test)
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("8","�㳰�򵯤������顢����ޤǤ˵�ư��������ݡ��ͥ�Ȥ�activatedComponentList�˻Ĥ�(2����)") {
            Singleton<ComponentInfo>::renewInstance();

            TestComponent test;
            TestComponent test2;
            list<Component *>::iterator scope;
            bool result = false;

            Exception::setThrowControl(true);
            test.activation = test2.activation = true;
            test2.throw_body = true;
            Singleton<ComponentInfo>::getInstance()->parseOption(getOptionParameter());
            try {
                Singleton<ComponentInfo>::getInstance()->activateComponent();
            }
            catch(...) {
                result = true;
            }

            if(!result)
                TEST_FAIL;

            if(Singleton<ComponentInfo>::getInstance()->activatedComponentList.size() != 2)
                TEST_FAIL;
            scope = Singleton<ComponentInfo>::getInstance()->activatedComponentList.begin();
            if(*scope != &test)
                TEST_FAIL;
            ++ scope;
            if(*scope != &test2)
                TEST_FAIL;
        } END_CASE;
    } END_CASE;

    BEGIN_CASE("onFatalExit","onFatalExit") {
        BEGIN_CASE("1","OnFatalExit�򤹤�ȵ�ư�׵�ꥹ�Ȥˤ��륳��ݡ��ͥ�Ȥ��ƤФ��") {
            Singleton<ComponentInfo>::renewInstance();

            TestComponent test;
            TestComponent test2;

            test.activation = test2.activation = true;
            test2.throw_body = true;
            Singleton<ComponentInfo>::getInstance()->parseOption(getOptionParameter());
            try{ Singleton<ComponentInfo>::getInstance()->activateComponent(); } catch(...) {}
            Singleton<ComponentInfo>::getInstance()->onFatalExit();

            if(!test.check_onFatalExit || !test2.check_onFatalExit)
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("2","��ư�׵��Ф��ʤ�����ݡ��ͥ�Ȥϵ�ư����ʤ�") {
            Singleton<ComponentInfo>::renewInstance();

            TestComponent test;
            TestComponent test2;

            test.activation = false;
            test2.activation = true;
            test2.throw_body = true;
            Singleton<ComponentInfo>::getInstance()->parseOption(getOptionParameter());
            try{ Singleton<ComponentInfo>::getInstance()->activateComponent(); } catch(...) {}
            Singleton<ComponentInfo>::getInstance()->onFatalExit();

            if(test.check_onFatalExit || !test2.check_onFatalExit)
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("4","��ư����������� (Ʊ���٥�ʤ���Ͽ��)") {
            Singleton<ComponentInfo>::renewInstance();

            TestComponent test;
            TestComponent test2;
            counter = 0;

            test2.throw_body = true;
            test.activation = test2.activation = true;
            Singleton<ComponentInfo>::getInstance()->parseOption(getOptionParameter());
            try{ Singleton<ComponentInfo>::getInstance()->activateComponent(); } catch(...) {}
            Singleton<ComponentInfo>::getInstance()->onFatalExit();

            if(test.actcnt != 5 || test2.actcnt != 6 )
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("5","��ư����������� (ͥ���ٽ�)") {
            Singleton<ComponentInfo>::renewInstance();

            TestComponent test(10);
            TestComponent test2(4);
            counter = 0;

            test.activation = test2.activation = true;
            test.throw_body = true;
            Singleton<ComponentInfo>::getInstance()->parseOption(getOptionParameter());
            try{ Singleton<ComponentInfo>::getInstance()->activateComponent(); } catch(...) {}
            Singleton<ComponentInfo>::getInstance()->onFatalExit();

            if(test.actcnt != 6 || test2.actcnt != 5 )
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("6","�㳰��ȴ���Ƥ���") {
            Singleton<ComponentInfo>::renewInstance();

            TestComponent test;
            TestComponent test2;
            list<Component *>::iterator scope;
            bool result = false;

            Exception::setThrowControl(true);
            test.activation = test2.activation = true;
            test2.throw_body = true;
            test.throw_onFatalExit = true;
            Singleton<ComponentInfo>::getInstance()->parseOption(getOptionParameter());
            try{ Singleton<ComponentInfo>::getInstance()->activateComponent(); } catch(...) {}
            try {
                Singleton<ComponentInfo>::getInstance()->onFatalExit();
            }
            catch(...) {
                result = true;
            }

            if(!result)
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("7","�㳰���������Ȥ����ޤ��¹Ԥ���Ƥ��ʤ�����ݡ��ͥ�ȤΥϥ�ɥ鵯ư�׵�ϻĤ�") {
            Singleton<ComponentInfo>::renewInstance();

            TestComponent test;
            TestComponent test2;
            list<Component *>::iterator scope;
            bool result = false;

            Exception::setThrowControl(true);
            test.activation = test2.activation = true;
            test2.throw_body = true;
            test.throw_onFatalExit = true;
            Singleton<ComponentInfo>::getInstance()->parseOption(getOptionParameter());
            try{ Singleton<ComponentInfo>::getInstance()->activateComponent(); } catch(...) {}
            try{
                Singleton<ComponentInfo>::getInstance()->onFatalExit();
            }
            catch(...) {
                result = true;
            }

            if(!result)
                TEST_FAIL;

            if(Singleton<ComponentInfo>::getInstance()->activatedComponentList.size() != 1)
                TEST_FAIL;

            if(*Singleton<ComponentInfo>::getInstance()->activatedComponentList.begin() != &test2)
                TEST_FAIL;

        } END_CASE;

        BEGIN_CASE("8","NULL���֥������Ȥ���ȯ�Ԥ��Ƥ������") {
            ((ComponentInfo *)0)->onFatalExit();
        } END_CASE;

    } END_CASE;

    BEGIN_CASE("isActive","isActive") {
        BEGIN_CASE("1","��ư��������ݡ��ͥ�Ȥ�Ƚ��Ǥ���") {
            Singleton<ComponentInfo>::renewInstance();

            TestComponent test;         
            Singleton<ComponentInfo>::getInstance()->activateComponent(&test);

            if(!Singleton<ComponentInfo>::getInstance()->isActive<TestComponent>())
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("2","��ư���Ƥ��ʤ�����ݡ��ͥ�Ȥˤ�ȿ�����ʤ�") {
            Singleton<ComponentInfo>::renewInstance();

            TestComponent test;

            if(Singleton<ComponentInfo>::getInstance()->isActive<TestComponent>())
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("3","������������ݡ��ͥ�ȤΥ��󥹥��󥹤ˤ�ȿ������") {
            Singleton<ComponentInfo>::renewInstance();

            DerivedTestComponent test;
            Singleton<ComponentInfo>::getInstance()->activateComponent(&test);

            if(!Singleton<ComponentInfo>::getInstance()->isActive<TestComponent>())
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("4","ʣ����ư���Ƥ��Ƥ��׵�˹�ä���Τ�õ����") {   //isActive��if(dynamic_cast<T *>(iterator->instance) != 0)��else���¹Ԥ�����Τ���Ū
            Singleton<ComponentInfo>::renewInstance();

            TestComponent test;         
            Singleton<ComponentInfo>::getInstance()->activateComponent(&test);
            DerivedTestComponent test2;
            Singleton<ComponentInfo>::getInstance()->activateComponent(&test2);

            if(!Singleton<ComponentInfo>::getInstance()->isActive<DerivedTestComponent>())
                TEST_FAIL;
        } END_CASE;
    } END_CASE;


    Singleton<ComponentInfo>::restoreContext(context);
}

//--------


TESTSUITE(main,Component)
{
    SingletonBase::ContextChain chain;

    chain.saveContext<ComponentInfo>();
    chain.saveContext<OptionParameter>();
    chain.saveContext<VerboseMessage::VerboseControl>();
    chain.saveContext<Message::MessageControl>();
    chain.saveContext<DebugMessage::DebugControl>();

    BEGIN_CASE("executeComponent","executeComponent") {
        BEGIN_CASE("1","�ä˲���ʤ���parseOption/body���¹Ԥ����") {
            chain.renewInstance();

            bool result = true;
            TestComponent test;
            test.activation = true;

            Exception::setThrowControl(true);
            try { executeComponents(getOptionParameter()); }
            catch(...) { result = false; }

            BEGIN_CASE("1","�㳰�ϵ�����ʤ�") {
                if(!result)
                    TEST_FAIL;
            } END_CASE;

            BEGIN_CASE("2","parseOption/body�ϼ¹Ԥ����") {
                 if(!test.check_parseOption || !test.check_body || test.check_onFatalExit)
                     TEST_FAIL;
            } END_CASE;
        } END_CASE;

        BEGIN_CASE("2","�������Ƥʤ����ץ���󤬤���") {
            TestSuite::clearCheckpoints();
            chain.renewInstance();

            char * argv[] = { "test.exe", "-test" };
            bool result = false;
            TestComponent test;
            test.activation = true;

            getOptionParameter().parseOption(2, argv);
            Exception::setThrowControl(true);
            try { executeComponents(getOptionParameter()); }
            catch(...) { result = true; }

            BEGIN_CASE("1","�㳰��������") {
                if(!result)
                    TEST_FAIL;
                if(!TestSuite::isReached("Exception_UnknownOption"))
                    TEST_FAIL;
            } END_CASE;

            BEGIN_CASE("2","parseOption/onFatalExit�ϼ¹Ԥ���뤬body�ϼ¹Ԥ���ʤ�") {
                 if(!test.check_parseOption || test.check_body || !test.check_onFatalExit)
                     TEST_FAIL;
            } END_CASE;
        } END_CASE;

        BEGIN_CASE("3","���ץ����ѡ�������㳰 (activate�ʤ�)") {
            chain.renewInstance();

            bool result = false;
            TestComponent test;
            test.throw_parseOption = true;

            Exception::setThrowControl(true);
            try { executeComponents(getOptionParameter()); }
            catch(...) { result = true; }

            BEGIN_CASE("1","�㳰��������") {
                if(!result)
                    TEST_FAIL;
            } END_CASE;

            BEGIN_CASE("2","parseOption�ϼ¹Ԥ���뤬body/onFatalExit�ϼ¹Ԥ���ʤ�") {
                 if(!test.check_parseOption || test.check_body || test.check_onFatalExit)
                     TEST_FAIL;
            } END_CASE;
        } END_CASE;

        BEGIN_CASE("4","���ץ����ѡ�������㳰 (activate����)") {
            chain.renewInstance();

            bool result = false;
            TestComponent test;
            test.throw_parseOption = true;
            test.activation = true;

            Exception::setThrowControl(true);
            try { executeComponents(getOptionParameter()); }
            catch(...) { result = true; }

            BEGIN_CASE("1","�㳰��������") {
                if(!result)
                    TEST_FAIL;
            } END_CASE;

            BEGIN_CASE("2","parseOption/onFatalExit�ϼ¹Ԥ���뤬body�ϼ¹Ԥ���ʤ�") {
                 if(!test.check_parseOption || test.check_body || !test.check_onFatalExit)
                     TEST_FAIL;
            } END_CASE;
        } END_CASE;

        BEGIN_CASE("5","body���㳰") {
            chain.renewInstance();

            bool result = false;
            TestComponent test;
            test.throw_body = true;
            test.activation = true;

            Exception::setThrowControl(true);
            try { executeComponents(getOptionParameter()); }
            catch(...) { result = true; }

            BEGIN_CASE("1","�㳰��������") {
                if(!result)
                    TEST_FAIL;
            } END_CASE;

            BEGIN_CASE("2","parseOption/body/onFatalExit�Ȥ�¹Ԥ����") {
                 if(!test.check_parseOption || !test.check_body || !test.check_onFatalExit)
                     TEST_FAIL;
            } END_CASE;
        } END_CASE;


        BEGIN_CASE("6","onFatalExit���㳰") {
            TestSuite::clearCheckpoints();
            chain.renewInstance();

            bool result = false;
            TestComponent test;
            test.throw_onFatalExit = true;
            test.activation = true;
            TestComponent test2;
            test2.throw_body = true;
            test2.activation = true;

            Exception::setThrowControl(true);
            try { executeComponents(getOptionParameter()); }
            catch(...) { result = true; }

            BEGIN_CASE("1","�㳰��������") {
                if(!result)
                    TEST_FAIL;
                if(!TestSuite::isReached("Exception_onFatalExit"))
                    TEST_FAIL;
            } END_CASE;

            BEGIN_CASE("2","�ǽ�Υ���ݡ��ͥ�Ȥ�parseOption/body/onFatalExit�Ȥ�¹Ԥ����") {
                 if(!test.check_parseOption || !test.check_body || !test.check_onFatalExit)
                     TEST_FAIL;
            } END_CASE;
            BEGIN_CASE("3","���Υ���ݡ��ͥ�Ȥ�parseOption/body/onFatalExit�Ȥ�¹Ԥ����") {
                 if(!test2.check_parseOption || !test2.check_body || !test2.check_onFatalExit)
                     TEST_FAIL;
            } END_CASE;
        } END_CASE;

        BEGIN_CASE("7","Component::is_valid��false�ΤȤ��ϼ¹Ԥ���ʤ�") {
            chain.renewInstance();

            bool result = true;
            TestComponent test;
            test.activation = true;

            Component::is_valid = false;
            Exception::setThrowControl(true);
            try { executeComponents(getOptionParameter()); }
            catch(...) { result = false; }

            BEGIN_CASE("1","�㳰�ϵ�����ʤ�") {
                if(!result)
                    TEST_FAIL;
            } END_CASE;

            BEGIN_CASE("2","parseOption/body�ϼ¹Ԥ���ʤ�") {
                 if(test.check_parseOption || test.check_body || test.check_onFatalExit)
                     TEST_FAIL;
            } END_CASE;

            Component::is_valid = true;
        } END_CASE;
    } END_CASE;

    BEGIN_CASE("_parseCommonOption","_parseCommonOption") {

        BEGIN_CASE("1", "-debug��DebugMessage��ͭ���ˤʤ�") {
            chain.renewInstance();

            char * argv[] = { "test.exe", "-debug" };
            OptionParameter & param = getOptionParameter();

            param.parseOption(2, argv);
            Component::_parseCommonOption(param);

            if(!DebugMessage::getVerbose())
                TEST_FAIL;

        } END_CASE;

        BEGIN_CASE("2", "-v ��VerboseMessage��ͭ���ˤʤ�") {
            chain.renewInstance();

            char * argv[] = { "test.exe", "-v" };
            OptionParameter & param = getOptionParameter();

            param.parseOption(2, argv);
            Component::_parseCommonOption(param);

            if(!VerboseMessage::getVerbose())
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("3", "--verbose��VerboseMessage��ͭ���ˤʤ�") {
            chain.renewInstance();

            char * argv[] = { "test.exe", "--verbose" };
            OptionParameter & param = getOptionParameter();

            param.parseOption(2, argv);
            Component::_parseCommonOption(param);

            if(!VerboseMessage::getVerbose())
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("4", "-lj ��Message�����ܸ�ˤʤ�") {
            chain.renewInstance();

            char * argv[] = { "test.exe", "-lj" };
            OptionParameter & param = getOptionParameter();

            param.parseOption(2, argv);
            Component::_parseCommonOption(param);

            if(Message::getCurrentLanguage() != Message::JAPANESE)
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("5", "--japanese ��Message�����ܸ�ˤʤ�") {
            chain.renewInstance();

            char * argv[] = { "test.exe", "--japanese" };
            OptionParameter & param = getOptionParameter();

            param.parseOption(2, argv);
            Component::_parseCommonOption(param);

            if(Message::getCurrentLanguage() != Message::JAPANESE)
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("6", "-le ��Message���Ѹ�ˤʤ�") {
            chain.renewInstance();

            char * argv[] = { "test.exe", "-le" };
            OptionParameter & param = getOptionParameter();

            param.parseOption(2, argv);
            Component::_parseCommonOption(param);

            if(Message::getCurrentLanguage() != Message::ENGLISH)
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("7", "--english ��Message���Ѹ�ˤʤ�") {
            chain.renewInstance();

            char * argv[] = { "test.exe", "--english" };
            OptionParameter & param = getOptionParameter();

            param.parseOption(2, argv);
            Component::_parseCommonOption(param);

            if(Message::getCurrentLanguage() != Message::ENGLISH)
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("8","�إ�פ��Ǥ� (-h)") {
            chain.renewInstance();

            char * argv[] = { "test.exe", "-h" };
            OptionParameter & param = getOptionParameter();

            param.parseOption(2, argv);
            cout.str("");
            Component::_parseCommonOption(param);

                //�Ȥꤢ�����������Ϥ���Ƥ��뤳�Ȥ�����ǧ���Ƥ���
            if(cout.str().empty())
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("9","�إ�פ��Ǥ� (--help)") {
            chain.renewInstance();

            char * argv[] = { "test.exe", "--help" };
            OptionParameter & param = getOptionParameter();

            param.parseOption(2, argv);
            cout.str("");
            Component::_parseCommonOption(param);

                //�Ȥꤢ�����������Ϥ���Ƥ��뤳�Ȥ�����ǧ���Ƥ���
            if(cout.str().empty())
                TEST_FAIL;
        } END_CASE;

    } END_CASE;

    BEGIN_CASE("getOption","���ץ����ѥ�᡼���μ���") {
        chain.renewInstance();

        char * argv[] = { "test.exe","-test","param","-test2","param2", "--test","param3","--test2","param4" };
        getOptionParameter().parseOption(9, argv);

        BEGIN_CASE("1","getOption(test)��param������") {
            OptionParameter::OptionItem item;

            item = getOption("test");
            TEST_CASE("1","ͭ�����ͤ��֤�", item.isValid());
            TEST_CASE("2","�����å��ѤߤǤ���", item.isChecked());
            TEST_CASE("3","1�ĤΥѥ�᡼������", item.countParameter() == 1);
            TEST_CASE("4","�ѥ�᡼�������Ƥ����äƤ���", item[0].compare("param") == 0);
        } END_CASE;

        BEGIN_CASE("2","getOption(test,test)��2�Ĥ�Ϣ�뤬����") {
            OptionParameter::OptionItem item;

            TEST_CASE("0","[����] --test�˥����å��ϤĤ��Ƥ��ʤ�", !getOptionParameter().get("-test",false).isChecked());

            item = getOption("test","test");

            TEST_CASE("1","ͭ�����ͤ��֤�", item.isValid());
            TEST_CASE("2","�����å��ѤߤǤ���", item.isChecked());
            TEST_CASE("3","�����å��ѤߤǤ��� (test)", getOptionParameter().get("test",false).isChecked());
            TEST_CASE("4","�����å��ѤߤǤ��� (-test)", getOptionParameter().get("-test",false).isChecked());
            TEST_CASE("5","2�ĤΥѥ�᡼�������", item.countParameter() == 2);
            TEST_CASE("6","1�Ĥ�Υѥ�᡼�����ͤ�������", item[0].compare("param") == 0);
            TEST_CASE("7","2�Ĥ�Υѥ�᡼�����ͤ�������", item[1].compare("param3") == 0);
        } END_CASE;

        BEGIN_CASE("3","getOption(test,unknown)��test�Υѥ�᡼��������") {
            OptionParameter::OptionItem item;

            item = getOption("test","unknown");

            TEST_CASE("1","ͭ�����ͤ��֤�", item.isValid());
            TEST_CASE("2","1�ĤΥѥ�᡼�������", item.countParameter() == 1);
            TEST_CASE("3","�ѥ�᡼�����ͤ�������", item[0].compare("param") == 0);
        } END_CASE;

        BEGIN_CASE("4","getOption(unknown,test)�� -test�Υѥ�᡼��������") {
            OptionParameter::OptionItem item;

            item = getOption("unknown","test");

            TEST_CASE("1","ͭ�����ͤ��֤�", item.isValid());
            TEST_CASE("2","1�ĤΥѥ�᡼�������", item.countParameter() == 1);
            TEST_CASE("3","�ѥ�᡼�����ͤ�������", item[0].compare("param3") == 0);
        } END_CASE;

        BEGIN_CASE("5","getOption(unknown,unknown)��̵���ʥ����ƥब�֤�") {
            OptionParameter::OptionItem item;

            item = getOption("unknown","unknown");

            TEST_CASE("1","̵�����ͤ��֤�", !item.isValid());
        } END_CASE;

        BEGIN_CASE("6","getOption(test2,test2,false)�ǥ����å����Ĥ��ʤ�") {
            OptionParameter::OptionItem item;

            TEST_CASE("0","[����] -test2�˥����å��ϤĤ��Ƥ��ʤ�", !getOptionParameter().get("test2",false).isChecked());
            TEST_CASE("0","[����] --test2�˥����å��ϤĤ��Ƥ��ʤ�", !getOptionParameter().get("-test2",false).isChecked());

            item = getOption("test2","test2",false);

            TEST_CASE("1","ͭ�����ͤ��֤�", item.isValid());
            TEST_CASE("2","�����å��ѤߤǤʤ�", !item.isChecked());
            TEST_CASE("3","�����å��ѤߤǤʤ� (test2)", !getOptionParameter().get("test2",false).isChecked());
            TEST_CASE("4","�����å��ѤߤǤʤ� (-test2)", !getOptionParameter().get("-test2",false).isChecked());
            TEST_CASE("5","2�ĤΥѥ�᡼�������", item.countParameter() == 2);
            TEST_CASE("6","1�Ĥ�Υѥ�᡼�����ͤ�������", item[0].compare("param2") == 0);
            TEST_CASE("7","2�Ĥ�Υѥ�᡼�����ͤ�������", item[1].compare("param4") == 0);
        } END_CASE;

    } END_CASE;

    BEGIN_CASE("findOption","���ץ����ѥ�᡼���μ���") {
        chain.renewInstance();

        char * argv[] = { "test.exe","-test","param","--test","param3", "-noparam"};
        getOptionParameter().parseOption(6, argv);

        BEGIN_CASE("1","findOption(test,test)��param������") {
            string result;

            TEST_CASE("0","[����] �����å��ѤߤǤϤʤ� (test)", !getOptionParameter().get("test",false).isChecked());
            TEST_CASE("0","[����] �����å��ѤߤǤϤʤ� (-test)", !getOptionParameter().get("-test",false).isChecked());
            TEST_CASE("1","�ؿ�����������", findOption("test","test",&result));
            TEST_CASE("2","ʸ�����param���֤�", result.compare("param") == 0);
            TEST_CASE("3","�����å��Ѥ� (test)", getOptionParameter().get("test",false).isChecked());
            TEST_CASE("3","�����å��Ѥ� (-test)", getOptionParameter().get("-test",false).isChecked());
        } END_CASE;

        BEGIN_CASE("2","findOption(test,unknown)��param������") {
            string result;

            TEST_CASE("1","�ؿ�����������", findOption("test","unknown",&result));
            TEST_CASE("2","ʸ�����param���֤�", result.compare("param") == 0);
        } END_CASE;

        BEGIN_CASE("3","findOption(unknown,test)��param3������") {
            string result;

            TEST_CASE("1","�ؿ�����������", findOption("unknown","test",&result));
            TEST_CASE("2","ʸ�����param���֤�", result.compare("param3") == 0);
        } END_CASE;

        BEGIN_CASE("4","findOption(unknown,unknown)��̵���ʥ����ƥब�֤�") {
            string result;

            result.assign("dummy");

            TEST_CASE("1","�ؿ��ϼ��Ԥ���", !findOption("unknown","unknown",&result));
            TEST_CASE("2","ʸ����Ͻ񤭴����ʤ�", result.compare("dummy") == 0);
        } END_CASE;

        BEGIN_CASE("5","findOption(noparam,NULL,&result)") {
            string result;
            result.assign("dummy");

            TEST_CASE("1","�ؿ�����������", findOption("noparam", 0, &result));
            TEST_CASE("2","ʸ������֤������ʤ�", result.compare("dummy") == 0);
        } END_CASE;
    } END_CASE;

    BEGIN_CASE("checkOption","���ץ����ѥ�᡼����¸�߳�ǧ + �����å�") {
        chain.renewInstance();

        char * argv[] = { "test.exe","-test","param","--test","param3", "-test2", "--test3"};
        getOptionParameter().parseOption(7, argv);

        BEGIN_CASE("1","checkOption(test,test)��param������") {
            string result;

            TEST_CASE("0","[����] �����å��ѤߤǤϤʤ� (test)", !getOptionParameter().get("test",false).isChecked());
            TEST_CASE("0","[����] �����å��ѤߤǤϤʤ� (-test)", !getOptionParameter().get("-test",false).isChecked());
            TEST_CASE("1","�ؿ�����������", checkOption("test","test"));
            TEST_CASE("2","�����å��Ѥ� (test)", getOptionParameter().get("test",false).isChecked());
            TEST_CASE("3","�����å��Ѥ� (-test)", getOptionParameter().get("-test",false).isChecked());
        } END_CASE;

        BEGIN_CASE("2","checkOption(test2,unknown)��param������") {
            string result;

            TEST_CASE("0","[����] �����å��ѤߤǤϤʤ� (test2)", !getOptionParameter().get("test2",false).isChecked());
            TEST_CASE("1","�ؿ�����������", checkOption("test2","unknown"));
            TEST_CASE("2","�����å��Ѥ� (test2)", getOptionParameter().get("test2",false).isChecked());
        } END_CASE;

        BEGIN_CASE("3","checkOption(unknown,test3)��param3������") {
            string result;

            TEST_CASE("0","[����] �����å��ѤߤǤϤʤ� (test3)", !getOptionParameter().get("-test3",false).isChecked());
            TEST_CASE("1","�ؿ�����������", checkOption("unknown","test3"));
            TEST_CASE("2","�����å��Ѥ� (test3)", getOptionParameter().get("-test3",false).isChecked());
        } END_CASE;

        BEGIN_CASE("4","checkOption(unknown,unknown)��̵���ʥ����ƥब�֤�") {
            string result;

            result.assign("dummy");

            TEST_CASE("1","�ؿ��ϼ��Ԥ���", !checkOption("unknown","unknown"));
        } END_CASE;
    } END_CASE;

        /* mergeOption�Υ����å����ܤϡ�getOption�Ȥۤ�Ʊ�� */
    BEGIN_CASE("mergeOption","���ץ����ѥ�᡼���η��") {
        chain.renewInstance();

        char * argv[] = { "test.exe","-test","param","-test2","param2", "--test","param3","--test2","param4" };
        getOptionParameter().parseOption(9, argv);

        BEGIN_CASE("1","mergeOption(test)��param������") {
            OptionParameter::OptionItem item;

            item = mergeOption("test");
            TEST_CASE("1","ͭ�����ͤ��֤�", item.isValid());
            TEST_CASE("2","�����å��ѤߤǤ���", item.isChecked());
            TEST_CASE("3","1�ĤΥѥ�᡼������", item.countParameter() == 1);
            TEST_CASE("4","�ѥ�᡼�������Ƥ����äƤ���", item[0].compare("param") == 0);
        } END_CASE;

        BEGIN_CASE("2","mergeOption(test,test)��2�Ĥ�Ϣ�뤬����") {
            OptionParameter::OptionItem item;

            TEST_CASE("0","[����] --test�˥����å��ϤĤ��Ƥ��ʤ�", !getOptionParameter().get("-test",false).isChecked());

            item = mergeOption("test","test");

            TEST_CASE("1","ͭ�����ͤ��֤�", item.isValid());
            TEST_CASE("2","�����å��ѤߤǤ���", item.isChecked());
            TEST_CASE("3","�����å��ѤߤǤ��� (test)", getOptionParameter().get("test",false).isChecked());
            TEST_CASE("4","�����å��ѤߤǤ��� (-test)", getOptionParameter().get("-test",false).isChecked());
            TEST_CASE("5","2�ĤΥѥ�᡼�������", item.countParameter() == 2);
            TEST_CASE("6","1�Ĥ�Υѥ�᡼�����ͤ�������", item[0].compare("param") == 0);
            TEST_CASE("7","2�Ĥ�Υѥ�᡼�����ͤ�������", item[1].compare("param3") == 0);
        } END_CASE;

        BEGIN_CASE("3","mergeOption(test,unknown)��test�Υѥ�᡼��������") {
            OptionParameter::OptionItem item;

            item = mergeOption("test","unknown");

            TEST_CASE("1","ͭ�����ͤ��֤�", item.isValid());
            TEST_CASE("2","1�ĤΥѥ�᡼�������", item.countParameter() == 1);
            TEST_CASE("3","�ѥ�᡼�����ͤ�������", item[0].compare("param") == 0);
        } END_CASE;

        BEGIN_CASE("4","mergeOption(unknown,test)�� -test�Υѥ�᡼��������") {
            OptionParameter::OptionItem item;

            item = mergeOption("unknown","test");

            TEST_CASE("1","ͭ�����ͤ��֤�", item.isValid());
            TEST_CASE("2","1�ĤΥѥ�᡼�������", item.countParameter() == 1);
            TEST_CASE("3","�ѥ�᡼�����ͤ�������", item[0].compare("param3") == 0);
        } END_CASE;

        BEGIN_CASE("5","mergeOption(unknown,unknown)��̵���ʥ����ƥब�֤�") {
            OptionParameter::OptionItem item;

            item = mergeOption("unknown","unknown");

            TEST_CASE("1","̵�����ͤ��֤�", !item.isValid());
        } END_CASE;

    } END_CASE;

    chain.restoreContext();
}
#endif


