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
 *  @(#) $Id: testsuite.cpp,v 1.3 2003/12/15 07:32:14 takayuki Exp $
 */

// $Header: /home/CVS/configurator/base/testsuite.cpp,v 1.3 2003/12/15 07:32:14 takayuki Exp $

#include "base/testsuite.h"

#include "base/coverage_defs.h"
#include "base/coverage_undefs.h"

#ifdef TESTSUITE

#undef  main           //�ƥ��ȥ��������Ѥ�main���������Τ�undef����
#undef  cin
#undef  cout
#undef  cerr

#include <stdlib.h>     //EXIT_SUCCESS|EXIT_FAILURE��
#include <fstream>      //��ȴؿ���
#include <cstdio>
#include <iomanip>

using namespace std;

/* ���ȥ꡼���������Ѥ��ѿ���� */
namespace std {
    stringstream _cin;
    stringstream _cout;
    stringstream _cerr;
}

/*
 *  �ƥ��ȥ������Ȥμ¹����楯�饹 ; class TestSuiteControl
 */


    //���󥹥ȥ饯��
TestSuiteControl::TestSuiteControl(ostream & _out, const char * _pattern) : target_session(_pattern), out(&_out), fail(false), verbose(false), case_count(0), fail_count(0)
{}

    //���ʥꥪ̾�μ���
string TestSuiteControl::get_suitename(const char * name) const
{
    string result;
    list<string>::const_iterator scope;

    scope = session.begin();
    while(scope != session.end()) {
        result += *scope;
        result += '.';
        ++ scope;
    }

    if(name != NULL)
        result += name;

    return result;
}


    //�ƥ��ȥ��ʥꥪ��ɽ������ (�ֵ��� : �¹Ԥ���ɬ�פ����뤫�ɤ���)
bool TestSuiteControl::_enter_case(const char * session, const char * description, const char * filename, long lineno)
{
    bool         result;
    stringstream buf;

        //ɽ�������
    current_session.assign(get_suitename(session));

        //�ܺپ��������
    if(description != 0)
        buf << description;

        //�ե�����̾ (filename:lineno) ������
    if(filename != 0) {
        string            work(filename);
        string::size_type pos;

            //�ե�ѥ����褿��û���ڤ�
        pos = work.find_last_of("/\\");
        if(pos != string::npos)
            work.erase(0, pos + 1);

        buf << '(' << work;
        if(lineno != -1)
            buf << ':' << lineno;
        buf << ')';
    }
    current_description = buf.str();
    
        //�¹Ԥ���ɬ�פ�̵ͭ�γ�ǧ
    result = (target_session.empty() || current_session.find(target_session) != string::npos);

    if(result) {
        if(verbose) {
            string indent;
            indent.assign(2 * this->session.size(), ' ');
            (*out) << indent << '[' << session << "] " << current_description << endl;

            //(*out) << '[' << current_session << "] " << current_description << endl;
        }

        enter_session(session);
        ++ case_count;
    }

    return result;
}

    //�ƥ��ȥ��å����̾ (���ʥꥪ�ץ�ե�����) ������
void TestSuiteControl::enter_session(const string & _session)
{   session.push_back(_session);   }

    //�ƥ��ȥ��å����̾ (���ʥꥪ�ץ�ե�����) �β��
void TestSuiteControl::leave_session(void)
{   session.pop_back();   }

    //�ƥ��ȥ��ʥꥪ�μ������
void TestSuiteControl::fail_in_suite(string msg)
{
    fail = true;
    (*out) << "Failed : [" << current_session << "]\n   " << current_description << endl;
    if(!msg.empty())
        (*out) << "     #" << msg << endl;
    ++ fail_count;
}


    //�������Ⱦ��󥳥󥹥ȥ饯��
TestSuite::SuiteContainerNode::SuiteContainerNode(const char * _session, SuiteFunction _suite) : session(_session), suite(_suite)
{}

    //�������Ⱦ��󥳥󥹥ȥ饯��
TestSuite::SuiteContainerNode::SuiteContainerNode(const SuiteContainerNode & src) : session(src.session), suite(src.suite)
{}

    //�������Ȥμ¹�
bool TestSuite::SuiteContainerNode::invoke(TestSuiteControl & suite_control)
{
    if(suite != 0) {
        suite_control.enter_session(session);
        (*suite)(suite_control);
        suite_control.leave_session();
    }

    return !suite_control.is_failed();
}

/*
 *  �ƥ��ȥ������ȼ¹ԥ��饹
 */

    //���󥹥ȥ饯��
TestSuite::TestSuite(const char * session, SuiteFunction suite) : fail(false)
{   Singleton<SuiteContainer>::getInstance()->push_back(SuiteContainerNode(session, suite));   }


    //�ǥ��ȥ饯��
TestSuite::~TestSuite(void)
{}


    //�ƥ��ȥ������Ȥμ¹�  (�ֵ���:�������Ȥ�¹Ԥ������ɤ���)
bool TestSuite::performTestSuite(int flags, const char * pattern)
{
    bool                        result;
    TestSuiteControl            suite_control(cerr, pattern);
    SuiteContainer *            container;
    SuiteContainer::iterator    scope;

        //�¹ԥ������ȥꥹ�Ȥλ���
    container = Singleton<SuiteContainer>::getInstance();

        //��Ĺ��������
    if( (flags & VERBOSE) != 0 )
        suite_control.set_verbose();

        //����Ͽ�������Ȥμ¹�
    scope = container->begin();
    while(scope != container->end()) {

        result = scope->invoke(suite_control);

            //���������ߤ�� or �̤��Ǽ¹�
        if( !result && (flags & THROUGH) == 0)
            break;

        ++ scope;
    }

        //���顼���ʤ����OKɽ��
    if(!suite_control.is_failed())
        cerr << "OK (" << suite_control.countCases() << " passed)" << endl;
    else
        cerr << "Failed (" << suite_control.countFails() << '/' << suite_control.countCases() << ')' << endl;

    return !suite_control.is_failed();    //�������Ȥ�����˼¹ԤǤ�����true
}


    //��Ͽ����Ƥ���ȥåץ�٥륹�����Ȥΰ���ɽ��
void TestSuite::listTestSuite(void)
{
    SuiteContainer::iterator  scope;
    int                       count;
    SuiteContainer *          container;

    count     = 0;
    container = Singleton<SuiteContainer>::getInstance();
    
    scope = container->begin();
    while(scope != container->end()) {
        cout << "  ";
        cout.width(3);
        cout << count << ':' << scope->getName() << endl;

        ++ count;
        ++ scope;
    }
    cout << "Total " << count << " sets of suite exist.\n";
}



/*
 *   �����å��ݥ�����Ѵؿ�
 */

bool TestSuite::isReached(std::string checkname)
{
    set<string>::iterator scope;

    scope = Singleton<Checkpoint>::getInstance()->find(checkname);

    return scope != Singleton<Checkpoint>::getInstance()->end();
}


/*
 *   �ƥ��ȥ������ȼ¹��Ѻ�ȴؿ�
 */

    //�ե������������
bool TestSuite::compareFileContents(const char * filename, const char * filecontents, bool _remove)
{
    fstream file(filename,ios::in);
    int     ch;
    bool    result = true;

        //���ƥ����å�
    while(result && *filecontents != '\x0' && file.good()) {
        ch = file.get();

        if(ch != (int)*filecontents)
            result = false;

        ++ filecontents;
    }

        //EOF��ã���Ƥ��뤫
    if(result) {
        if(!file.good() || file.get() != EOF)
            result = false;
    }

    file.close();

    if(_remove)
        ::remove(filename);

    return result;
}

    
/*
    *   �ƥ��ȥ������ȼ¹���main�ؿ�
    */
int main(int argc, char ** argv)
{
    int    result;
    int    pos;
    int    flags;
    string category;

    flags = TestSuite::DEFAULT;

    for(pos = 1; pos < argc; ++ pos) {
        if(*argv[pos] == '-') {
            switch(argv[pos][1]) {
            case 'v': 
                flags |= TestSuite::VERBOSE;
                break;
            case 'V': 
                flags &= ~TestSuite::VERBOSE;
                break;
            case 't': 
                flags |= TestSuite::THROUGH;
                break;
            case 'T': 
                flags &= ~TestSuite::THROUGH;
                break;
            case 'l': 
                TestSuite::listTestSuite();
                return EXIT_SUCCESS;
            case 'h':
                cerr << "Usage : program (option) (suite)\n"
                            " -v, -V  : Verbose output on(-v) / off(-V)\n"
                            " -t, -T  : Go through with the suite, on(-t) / off(-T)\n"
                            " -l      : List the top level suites\n";
                return EXIT_SUCCESS;
            default:
                cerr << "Unknown option [" << argv[pos] << "]\n";
                return EXIT_FAILURE;
            }
        }
        else {
            if(!category.empty()) {
                cerr << "Two or more category specified.\n";
                return EXIT_FAILURE;
            }
            category.assign(argv[pos]);
        }
    }

    result = EXIT_FAILURE;
    if(TestSuite::performTestSuite(flags, category.c_str()))
        result = EXIT_SUCCESS;

#ifdef COVERAGE
    fstream fout("coverage.txt",ios::out);
    if(fout.is_open()) {
        Coverage::printCoverage(fout);
        fout.close();
    }
#endif

    return result;
}

#endif //TESTSUITE

