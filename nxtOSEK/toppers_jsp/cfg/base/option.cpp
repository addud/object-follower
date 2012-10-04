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
 *  @(#) $Id: option.cpp,v 1.3 2003/12/15 07:32:14 takayuki Exp $
 */

// $Header: /home/CVS/configurator/base/option.cpp,v 1.3 2003/12/15 07:32:14 takayuki Exp $

#include "base/option.h"
#include <assert.h>
#include <algorithm>

using namespace std;

    //�̤�OptionItem�����ĥѥ�᡼����ʬ���ɲä���
void OptionParameter::OptionItem::mergeItem(const OptionItem & src)
{
    vector<string>::const_iterator scope;

        //���ƤΥѥ�᡼����ʬ�θ����ɲ�
    scope = src.param.begin();
    while(scope != src.param.end()) {
        param.push_back(*scope);
        ++ scope;
    }
}

    //ʸ�������Ƭ�ˤ������ʸ���������
namespace {
    void TrimString(string & src)
    {
        string::size_type pos;

        pos = src.find_first_not_of(" \t\r\n");
        if(pos != 0)
            src.erase(0, pos);
    }
}

    //���ץ����ѥ�᡼������Ϥ���OptionItem����������
bool OptionParameter::OptionItem::createItem(OptionItem & _dest, string & argv)
{
    bool              result;
    string            param;
    string::size_type pos;
    OptionItem        dest;

    result = true;

    TrimString(argv);
    if(argv.empty())
        result = false;     //��Ȥ����ä�
    else {
            //���ץ����Υ����å�
        if(argv[0] == '-') {
            pos = argv.find_first_of(" =");

            if(argv.substr(0,pos).compare("-") == 0) {  // - �����Υ��ץ����ϼ����դ��ʤ�
                result = false;
            }
            else {
                if(pos != 1) {
                    if(pos != string::npos) {
                        dest = argv.substr(1, pos - 1);
                        argv.erase(0, pos + 1);
                    }
                    else {
                        dest = argv.substr(1);
                        argv.erase();
                    }
                }
            }
        }

        TrimString(argv);
        while(!argv.empty() && argv[0] != '-') {
            if(argv[0] == '"') {

                    //�Фˤʤ���֥륯�����Ȥ�õ��
                pos = argv.find_first_of('"',1);
                if(pos == string::npos) {
                    result = false;
                    break;
                }

                    //���֥륯�����Ȥ���Ȥ���
                param = argv.substr(1, pos - 1);

                    //���֥륯�����Ȥ�ä�
                ++ pos;
            }
            else {

                    //���ζ��ڤ��õ��
                pos = argv.find_first_of(" \t\r\n");
                if(pos == string::npos)
                    param = argv;
                else
                    param = argv.substr(0,pos);
            }

            dest.addParameter(param);
            argv.erase(0, pos);
            
            TrimString(argv);
        }
    }

    if(result)
        _dest = dest;

    return result;
}

    //̵���ʥ��ץ���󥢥��ƥ������
OptionParameter::OptionItem OptionParameter::OptionItem::createInvalidItem(void) throw()
{
    OptionItem result;

    result.assign("");
    return result;
}


    //���ƤΥѥ�᡼����礷����Τ����
string OptionParameter::OptionItem::getParameters(string punctuator) const throw()
{
    string result;

    vector<string>::const_iterator scope;

    if(isValid()) {
        scope = param.begin();
        while(scope != param.end()) {
            result += punctuator;
            result += *scope;
            ++ scope;
        }

        if(!result.empty())
            result.erase(0, punctuator.size()); //��Ƭ�ζ��ڤ�Ҥ���
    }

    return result;
}

    //���ץ����θĿ��Υ����å�
bool OptionParameter::OptionItem::checkParameterCount(size_t required, bool allow_zero) const throw()
{
    bool result = true;
    if(isValid()) {
        size_t count = countParameter();
        if(count != required || (!allow_zero && count == 0))
            result = false;
    }
    else
        result = false;
    return result;
}

        //���ץ����ѥ�᡼���Υѡ���
bool OptionParameter::parseOption(int _argc, char const * const * _argv, char const * _default) throw()
{
    bool        result;
    string      arguments;
    OptionItem  work;
    int         i;

    map<string, OptionItem>::iterator scope;

        //�ץ����̾�μ���
    if(_argc > 0)
        program_name.assign(_argv[0]);

        //���ƤĤʤ���
    for(i=1;i<_argc;++i) {
        arguments += _argv[i];
        arguments += ' ';
    }

    if(arguments.empty() && _default != 0)
        arguments.assign(_default);

    cmdline += arguments;

    result = true;

        //�ƥ��ץ����β���
    while(!arguments.empty()) {

        if(!OptionItem::createItem(work, arguments)) {
            result = false;
            break;
        }

            //Ʊ��Υ��ץ���󤬤�����ޡ�������
        scope = container.find(work);
        if(scope != container.end())
            scope->second.mergeItem(work);
        else
            container.insert(std::map<std::string, OptionItem>::value_type(work, work));
    }

    return result;
}

    //���Ǥθ���
map<string, OptionParameter::OptionItem>::iterator OptionParameter::_find(const std::string & name, bool check) throw()
{
    map<string, OptionParameter::OptionItem>::iterator scope;

    scope = container.find(name);

        //���Ǥ���Ѥ������Ȥ�Ͽ���Ƥ���
    if(check && scope != container.end())
        scope->second._check();

    return scope;
}


    //���ץ���󥢥��ƥ�λ���
OptionParameter::OptionItem OptionParameter::get(const std::string & name, bool check) throw()
{
    OptionItem                        result;
    map<string, OptionItem>::iterator scope;

    scope = _find(name, check);
    if(scope != container.end())
        result = scope->second;
    else
        result = OptionItem::createInvalidItem();

    return result;
}


    //���ƤΥ��ץ���󤬻��Ѥ��줿���ɤ����γ�ǧ
bool OptionParameter::validateOption(void) const throw()
{
    map<string, OptionItem>::const_iterator scope;
    bool result = true;

        //���ƤΥ��ץ���󤬥����å��ѤߤǤ��뤳�Ȥ��ǧ
    scope = container.begin();
    while(scope != container.end()) {
        if(!scope->second.isChecked()) {
            result = false;
            break;
        }
        ++ scope;
    }

    return result;
}


    //���Ѥ���ʤ��ä����ץ����������
string OptionParameter::getInvalidOptions(void) const throw()
{
    map<string, OptionItem>::const_iterator scope;
    string result;

        //���Ѥ���ʤ��ä����ƤΥ��ץ������Ф���
    scope = container.begin();
    while(scope != container.end()) {
        const OptionItem & item = scope->second;
        if(!item.isChecked()) {
            result += " -";
            result += item;

                //���ץ����ѥ�᡼�������
            size_t params = item.countParameter();
            for(size_t i=0; i<params; ++i) {
                result += " \"";
                result += item[i];
                result += '\"';
            }
        }
        ++ scope;
    }

        //��Ƭ�ζ���������
    if(!result.empty())
        result = result.substr(1);

    return result;
}

/***************** �ƥ��ȥ������� *****************/

#ifdef TESTSUITE
#include "coverage_undefs.h"


TESTSUITE_(main,OptionItem,OptionParameter)
{
    BEGIN_CASE("01","�ǥե���ȥѥ�᡼����" DEFAULT_PARAMETER "�ˤʤäƤ���") {
        OptionItem work;
        if(work.compare(DEFAULT_PARAMETER) != 0)
            TEST_FAIL;
    } END_CASE;

    //----

    BEGIN_CASE("02","���󥹥ȥ饯�������å� (checked == false, �ѥ�᡼��̾)") {

        BEGIN_CASE("1","OptionItem(void)") {
            OptionItem work;
            if(work.checked != false)
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("2","OptionItem(const string &)") {
            OptionItem work("test");
            if(work.compare("test") != 0 || work.checked != false)
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("3","OptionItem(const OptionItem &)") {
            OptionItem dummy("test");
            OptionItem work(dummy);
            if(work.compare("test") != 0 || work.checked != false)
                TEST_FAIL;
        } END_CASE;

    } END_CASE;

    //----

    BEGIN_CASE("03", "addParameter / countParameter / operator []") {
        const char * container[] = { "first", "second", "third", "forth", "fifth", NULL };
        const char ** param = container;
        int i;

        OptionItem work;

        BEGIN_CASE("1", "��ä�ľ���countParameter��0") {
            if(work.countParameter() != 0)
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("2", "addParameter���뤿�Ӥ�1����������Ϥ�") {
            while(*param != NULL) {
                size_t count = work.countParameter();

                work.addParameter(*param);

                if(work.countParameter() != count + 1)
                    TEST_FAIL;

                ++ param;
            }
        } END_CASE;

        BEGIN_CASE("3", "���줿��ΤϤ��������äƤ�") {
            i = 0;
            param = container;
            while(*param != NULL) {
                if(work[i].compare(*param) != 0)
                    TEST_FAIL;

                ++ i;
                ++ param;
            }
        } END_CASE;

        BEGIN_CASE("4", "operator[]���ϰϳ��Υѥ�᡼���������ȶ�ʸ�����֤�") {
            if(!work[10000].empty())
                TEST_FAIL;
        } END_CASE;
    } END_CASE;

    //----

    BEGIN_CASE("04", "hasParameter") {
        OptionItem work;

        BEGIN_CASE("1", "��Ȥ��ʤ��Ȥ���false���֤�") {
            if(work.hasParameter())
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("2", "��Ȥ�����Ȥ���true���֤�") {
            work.addParameter("dummy");
            if(!work.hasParameter())
                TEST_FAIL;
        } END_CASE;
    } END_CASE;
        
    //----

    BEGIN_CASE("mergeItem", "mergeItem") {
        OptionItem work;
        OptionItem work2;

        work.addParameter("one");
        work2.addParameter("two");
        
        work.mergeItem(work2);

        BEGIN_CASE("1","�ޡ�������Ƥ���") {
            if(work[0].compare("one") != 0 || work[1].compare("two") != 0 || work.countParameter() != 2)
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("2","�ѹ������Ѳ��ʤ�") {
            if(work2[0].compare("two") != 0 || work2.countParameter() != 1)
                TEST_FAIL;
        } END_CASE;

    } END_CASE;
        
    //----

    BEGIN_CASE("isChecked/checked", "isChecked/check") {
        OptionItem work;

        BEGIN_CASE("1","�ǽ��unchecked����") {
            if(work.isChecked() != false)
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("2","check��Ĥ���") {
            work._check();
            if(work.isChecked() != true)
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("3","�⤦����äƤ�ȥ���ˤʤ�ʤ�") {
            work._check();
            if(work.isChecked() != true)
                TEST_FAIL;
        } END_CASE;

    } END_CASE;

    //----

    BEGIN_CASE("CopyConstructor", "���ԡ����󥹥ȥ饯���ǥѥ�᡼�����ܤ뤫") {
        OptionItem src;
        src.addParameter("one");

        OptionItem dest(src);

        if(dest.countParameter() != 1 || dest[0].compare("one") != 0)
            TEST_FAIL;
    } END_CASE;

    //----

    BEGIN_CASE("TrimString", "TrinString��������ư����") {
        BEGIN_CASE("1","��Ƭ�ζ���ʸ�����ä���") {
            string work(" \r\n\ttest");
            TrimString(work);
            if(work.compare("test") != 0)
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("2","����ʸ��������������ʸ����") {
            string work("     ");
            TrimString(work);
            if(!work.empty())
                TEST_FAIL;
        } END_CASE;
    } END_CASE;

    //----

    BEGIN_CASE("createItem", "createItem�ؿ���ư���") {
        BEGIN_CASE("1", "���äݤ�ʸ����򤤤��ȼ��Ԥ���") {
            OptionItem work;
            string param("");
            if(OptionItem::createItem(work, param))
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("2", "�����ʤ����ץ����") {
            OptionItem work;
            string     arg("-test");
            if(!OptionItem::createItem(work, arg))
                TEST_FAIL;
            if(work.compare("test") != 0 || work.hasParameter())
                TEST_FAIL;
            if(!arg.empty())
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("3", "Ϣ³��������ʤ����ץ����") {
            OptionItem work;
            string     arg("-test -test2");
            if(!OptionItem::createItem(work, arg))
                TEST_FAIL;
            if(arg.compare("-test2") != 0)
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("4", "�����Ĥ����ץ����(-test param)") {
            OptionItem work;
            string     arg("-test param");
            if(!OptionItem::createItem(work, arg))
                TEST_FAIL;
            if(work.compare("test") != 0)
                TEST_FAIL;
            if(work.countParameter() != 1 || work[0].compare("param") != 0)
                TEST_FAIL;
            if(!arg.empty())
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("5", "�����Ĥ����ץ����(-test=param)") {
            OptionItem work;
            string     arg("-test=param");
            if(!OptionItem::createItem(work, arg))
                TEST_FAIL;
            if(work.compare("test") != 0)
                TEST_FAIL;
            if(work.countParameter() != 1 || work[0].compare("param") != 0)
                TEST_FAIL;
            if(!arg.empty())
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("6", "�����Ĥ����ץ����(-test=\"a b c\")") {
            OptionItem work;
            string     arg("-test=\"a b c\"");
            if(!OptionItem::createItem(work, arg))
                TEST_FAIL;
            if(work.compare("test") != 0)
                TEST_FAIL;
            if(work.countParameter() != 1 || work[0].compare("a b c") != 0)
                TEST_FAIL;
            if(!arg.empty())
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("7", "Ϣ³���������Ĥ����ץ����(-test one two)") {
            OptionItem work;
            string     arg("-test one two");
            if(!OptionItem::createItem(work, arg))
                TEST_FAIL;
            if(work.compare("test") != 0)
                TEST_FAIL;
            if(work.countParameter() != 2 || work[0].compare("one") != 0 || work[1].compare("two") != 0)
                TEST_FAIL;
            if(!arg.empty())
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("8", "�ϥ��ե�") {
            BEGIN_CASE("1", "�ϥ��ե�����ΰ����ϼ����դ��ʤ�") {
                OptionItem work;
                string     arg("-");
                if(OptionItem::createItem(work, arg))
                    TEST_FAIL;
            } END_CASE;

            BEGIN_CASE("2", "�ϥ��ե�����ΰ����ϼ����դ��ʤ�(Ϣ³)") {
                OptionItem work;
                string     arg("- - -");
                if(OptionItem::createItem(work, arg))
                    TEST_FAIL;
            } END_CASE;

            BEGIN_CASE("3", "���֥륯�����ȤǤ�����줿�ϥ��ե�ϼ����դ���") {
                OptionItem work;
                string     arg("\"-\"");
                if(!OptionItem::createItem(work, arg))
                    TEST_FAIL;
                if(work.compare(DEFAULT_PARAMETER) != 0 || work.countParameter() != 1 || work[0].compare("-") != 0)
                    TEST_FAIL;
            } END_CASE;
    
        } END_CASE;

        BEGIN_CASE("9", "�Фˤʤ���֥륯�����Ȥ��礱�������ϼ����դ��ʤ�") {
            OptionItem work;
            string     arg("-test=\"a b c");
            if(OptionItem::createItem(work, arg))
                TEST_FAIL;
        } END_CASE;

    } END_CASE;

    BEGIN_CASE("isValid/createInvalidItem", "̵���򼨤����󥹥��󥹤������Ǥ��������Ƚ��Ǥ���") {
        OptionItem work;

        BEGIN_CASE("1","�ǥե���ȥ��󥹥ȥ饯���������������֥������Ȥ�ͭ��") {
            if(!work.isValid())
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("2","̵�����󥹥��󥹤�����̵��") {
            work = OptionItem::createInvalidItem();
            if(work.isValid())
                TEST_FAIL;
        } END_CASE;
    } END_CASE;

    BEGIN_CASE("getParameters","getParameters") {
        BEGIN_CASE("1","���������ץ�������Ǥ���") {
            OptionItem work;
            string     arg("-test a b c d e f g");

            TEST_CASE("0","[����]���ץ������Ϥ���������", OptionItem::createItem(work,arg));
            TEST_CASE("1","���Ǥ���", work.getParameters().compare("a b c d e f g") == 0);
            TEST_CASE("2","���ڤ�����ꤷ�Ʒ��Ǥ���", work.getParameters(",").compare("a,b,c,d,e,f,g") == 0);
        } END_CASE;
    } END_CASE;

    BEGIN_CASE("checkParameterCount","checkParameterCount") {
        BEGIN_CASE("1","���ץ����ο������äƤ����true") {
            OptionItem work;
            string     arg("-test a b c d e f g");

            TEST_CASE("0","[����]���ץ������Ϥ���������", OptionItem::createItem(work,arg));

            if(!work.checkParameterCount(7))
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("2","���ץ����ο����ְ�äƤ����false") {
            OptionItem work;
            string     arg("-test a b c d e f g");

            TEST_CASE("0","[����]���ץ������Ϥ���������", OptionItem::createItem(work,arg));

            if(work.checkParameterCount(2))
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("3","���ץ���󤬤ʤ��ơ�!allow_zero�ʤ�false") {
            OptionItem work;
            string     arg("-test");

            TEST_CASE("0","[����]���ץ������Ϥ���������", OptionItem::createItem(work,arg));

            if(work.checkParameterCount(1,false))
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("4","���ץ���󤬤ʤ��ơ�allow_zero�ʤ�true") {
            OptionItem work;
            string     arg("-test");

            TEST_CASE("0","[����]���ץ������Ϥ���������", OptionItem::createItem(work,arg));

            if(work.checkParameterCount(1,true))
                TEST_FAIL;
        } END_CASE;

    } END_CASE;
}

/********************************* �ƥ��ȥ������� *********************************/

TESTSUITE(main,OptionParameter)
{
    SINGLETON(OptionParameter);

    BEGIN_CASE("countItem","���ץ���󥢥��ƥ�ο��������������Ǥ���") {
        OptionParameter param;
        if(param.countItem() != 0)
            TEST_FAIL;

        param.container.insert(pair<string, OptionItem>(DEFAULT_PARAMETER, OptionItem()));
        if(param.countItem() != 1)
            TEST_FAIL;
    } END_CASE;

    BEGIN_CASE("opeator []","operator []�����Ǥ˥��������Ǥ���") {
        OptionParameter param;
        OptionItem work;
        string arg("-test param");

        OptionItem::createItem(work, arg);
        param.container.insert(pair<string, OptionItem>(work, work));

        BEGIN_CASE("1", "operator [] (const string &)�����Ĥ˥��������Ǥ���") {
            if(param[string("test")][0].compare("param") != 0)
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("2", "operator [] (const char *)�����Ĥ˥��������Ǥ���") {
            if(param["test"][0].compare("param") != 0)
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("3", "operator []�ǿ���ȡ�check������") {
            if(!param["test"].isChecked())
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("4", "operator []��̵���ʥ����������ȡ�̵���ʥǡ������֤äƤ���") {
            if(param["nonexist"].isValid())
                TEST_FAIL;
        } END_CASE;
    } END_CASE;

    BEGIN_CASE("get","���ǤؤΥ�������") {
        OptionParameter param;
        OptionItem work;

        OptionItem::createItem(work, string("-test param"));
        param.container.insert(pair<string, OptionItem>(work, work));
        OptionItem::createItem(work, string("-test2 param2"));
        param.container.insert(pair<string, OptionItem>(work, work));

        BEGIN_CASE("1","get(test)�����Ǥ������Ǥ��������å�������") {
            TEST_CASE("1","���Ǥ�¸�ߤ���", (work = param.get("test")).isValid());
            TEST_CASE("2","�����å������äƤ���", work.isChecked() );
            TEST_CASE("3","���Ǥϥѥ�᡼�������", work.hasParameter() );
        } END_CASE;

        BEGIN_CASE("2","get(test2,false)�����Ǥ������Ǥ��������å��ϤĤ��ʤ�") {
            TEST_CASE("1","���Ǥ�¸�ߤ���", (work = param.get("test2",false)).isValid());
            TEST_CASE("2","�����å������äƤ��ʤ�", !work.isChecked() );
        } END_CASE;

        BEGIN_CASE("3","���Ǥ˥����å��ΤĤ���test���Ф���get(test,false)�����Ǥ������Ǥ��������å��Ѥ�") {
            TEST_CASE("1","���Ǥ�¸�ߤ���", (work = param.get("test",false)).isValid());
            TEST_CASE("2","�����å������äƤ��ʤ�", work.isChecked() );
        } END_CASE;

        BEGIN_CASE("4","get(̵����̾��)��̵�������Ǥ��֤�") {
            TEST_CASE("1","���Ǥ�¸�ߤ���", !param.get("unknown").isValid());
        } END_CASE;
    } END_CASE;


    BEGIN_CASE("parseOption","�ѥ�᡼���Υѡ���������ˤǤ��뤫") {
        BEGIN_CASE("01","��Ȥ�����ʤ��ѥ�᡼����Ϳ���Ƥ���������") {
            OptionParameter param;
            char ** argv = { NULL };

            if(!param.parseOption(0, argv))
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("02","�ץ����̾�ϥ��ץ����Ȥ��Ʋ��Ϥ���ʤ�") {
            OptionParameter param;
            char * argv[] = { "test.exe", NULL };

            if(!param.parseOption(1, argv))
                TEST_FAIL;
            if(param.countItem() != 0)
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("03","�ѥ�᡼��������ʤ�˲��Ϥ����") {
            OptionParameter param;
            char * argv[] = { "test.exe", "-test", "param", "-test2=\"dummy\"", NULL };

            if(!param.parseOption(4, argv))
                TEST_FAIL;
            if(param.countItem() != 2)
                TEST_FAIL;
            
            if(param[string("test")][0].compare("param") != 0)
                TEST_FAIL;

            if(param["test2"][0].compare("dummy") != 0)
                TEST_FAIL;

            if(param.getProgramName().compare("test.exe") != 0)
                TEST_FAIL;

        } END_CASE;

        BEGIN_CASE("04","�����󤬼���") {
            OptionParameter param;
            char * argv[] = { "test.exe", "-test", "param", "-test2=\"dummy\"", NULL };

            if(!param.parseOption(4, argv))
                TEST_FAIL;

            if(param.getCommandLine().compare("-test param -test2=\"dummy\" ") != 0)
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("05","���������̵���Ȥ��ˤϥǥե���Ȱ�����Ҥ��Ƥ���") {
            OptionParameter param;
            char * argv[] = { "test.exe", NULL };

            if(!param.parseOption(1, argv, "-default=parameter"))
                TEST_FAIL;

            if(param.getCommandLine().compare("-default=parameter ") != 0)
                TEST_FAIL;
        } END_CASE;

    } END_CASE;

    BEGIN_CASE("04","���ȥޡ�����Ĥ���") {
        OptionParameter param;
        char * argv[] = { "test.exe", "-test", "param", "-test2=\"dummy\"", NULL };

        if(!param.parseOption(4, argv))
            TEST_FAIL;

        if(param.container.find(string("test"))->second.isChecked())
            TEST_FAIL;

        param.check("test");
        if(!param.container.find(string("test"))->second.isChecked())
            TEST_FAIL;
    } END_CASE;

    BEGIN_CASE("05","validateOption") {
        OptionParameter param;
        char * argv[] = { "test.exe", "-test", "param", "-test2=\"dummy\"", NULL };

        if(!param.parseOption(4, argv))
            TEST_FAIL;

        BEGIN_CASE("1","������Ѥ��Ƥ��ʤ��Ȥ��ˤ�false") {
            if(param.validateOption())
                TEST_FAIL;
        } END_CASE;

        param["test"]._check();
        BEGIN_CASE("2","�ۤ��˥����å����Ƥ��ʤ����ץ���󤬤����false") {
            if(param.validateOption())
                TEST_FAIL;
        } END_CASE;

        param["test2"]._check();
        BEGIN_CASE("3","���ƻ��Ѥ�����true") {
            if(!param.validateOption())
                TEST_FAIL;
        } END_CASE;
    } END_CASE;

    BEGIN_CASE("06","getInvalidOptions") {
        OptionParameter param;
        char * argv[] = { "test.exe", "-test", "param", "-test2=\"dummy\"", NULL };

        if(!param.parseOption(4, argv))
            TEST_FAIL;

        BEGIN_CASE("1","������Ѥ��Ƥ��ʤ��Ȥ��ˤ����ƤΥ��ץ����̵��") {
            if(param.getInvalidOptions().compare("-test \"param\" -test2 \"dummy\"") != 0)
                TEST_FAIL;
        } END_CASE;

        param["test"]._check();
        BEGIN_CASE("2","�ۤ��˥����å����Ƥ��ʤ����ץ���󤬤���Ф��줬����") {
            if(param.getInvalidOptions().compare("-test2 \"dummy\"") != 0)
                TEST_FAIL;
        } END_CASE;
    } END_CASE;

    BEGIN_CASE("07","find") {
        OptionParameter param;
        char * argv[] = { "test.exe", "-test", "param", "-test2=\"dummy\"", NULL };

        if(!param.parseOption(4, argv))
            TEST_FAIL;

        BEGIN_CASE("1","¸�ߤ��륪�ץ������Ф���true���֤�") {
            if(!param.find("test") || !param.find("test2"))
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("2","¸�ߤ��ʤ����ץ������Ф���false���֤�") {
            if(param.find("unknown"))
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("3","��ʸ�����Ф���false���֤�") {
            if(param.find(""))
                TEST_FAIL;
        } END_CASE;
    } END_CASE;

    Singleton<OptionParameter>::restoreContext(context);
}

#endif


