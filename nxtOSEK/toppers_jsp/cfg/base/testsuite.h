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
 *  @(#) $Id: testsuite.h,v 1.4 2003/12/20 06:51:58 takayuki Exp $
 */

/*
 *   �ƥ��ȥ������ȼ¹���� ���饹/�ޥ���饤�֥��
 */

// $Header: /home/CVS/configurator/base/testsuite.h,v 1.4 2003/12/20 06:51:58 takayuki Exp $


#ifdef TESTSUITE

    //���ʥꥪ��ü�ޥ���(Exception���饹��̵ͭ�ˤ�ä���Ȥ��ؤ������ΤǤ����ˤ���)
#  undef END_CASE
#  ifdef EXCEPT_H
#    define END_CASE }catch(TestSuite::Fail & x) { _suite_control.fail_in_suite(x.getMessage()); } catch(Exception & exc) { _suite_control.fail_in_suite(string("�������㳰 : ") + exc.getDetails()); } catch(...) { _suite_control.fail_in_suite("�ƥ��ȼ¹�����������㳰�������ä��������Ǥ��줿"); } _suite_control.leave_case(); }
#  else
#    define END_CASE }catch(TestSuite::Fail & x) { _suite_control.fail_in_suite(x.getMessage()); } catch(...) { _suite_control.fail_in_suite("�ƥ��ȼ¹�����������㳰�������ä��������Ǥ��줿"); } _suite_control.leave_case(); }
#  endif

#endif


#ifndef TESTSUITE_H
#define TESTSUITE_H

    //�ƥ��ȥ������Ȥ򤫤��뤫�ɤ���
//#define TESTSUITE


#if defined(TESTSUITE) //&& defined(_DEBUG)

    //���ȥ꡼������Ƥ�ƥ��ȤǻȤ������Τ������ؤ���
#include <iostream>
#define cin  _cin
#define cout _cout
#define cerr _cerr

#include <sstream>

namespace std {
    extern stringstream _cin;
    extern stringstream _cout;
    extern stringstream _cerr;
}

#include <string>
#include <list>
#include <set>
#include <map>


    //ɸ��Υƥ��ȥ������ȴؿ��Υץ�ȥ���������ѥޥ���
#define TESTSUITE_PROTOTYPE(suite) \
    public: \
        static void test_suite_##suite(TestSuiteControl & _suite_control);


    //ɸ��Υƥ��ȥ������ȴؿ�������ѥޥ��� (�虜�ȥ������ȼ¹Ԥξ�拾��ѥ����Ѥ����̾��Ʊ��̾���ˤ���)
#undef TESTSUITE
#define TESTSUITE(suite,cls) \
    TestSuite TestSuite_##cls##_##suite(#cls "(" #suite ")", cls::test_suite_##suite); \
    void cls::test_suite_##suite(TestSuiteControl & _suite_control)

#define TESTSUITE_(suite,cls,spr) \
    TestSuite TestSuite_##spr##_##cls##_##suite(#spr "::" #cls "(" #suite ")", spr::cls::test_suite_##suite); \
    void spr::cls::test_suite_##suite(TestSuiteControl & _suite_control)

    //¿�ż¹��ɻ��ѥޥ���
#define PROCEED_ONCE static bool _proceed_once_flag_ = false; if(_proceed_once_flag_) return; else _proceed_once_flag_ = true;

    //���ʥꥪ���ϥޥ���
#define BEGIN_CASE(x,y) if(_suite_control.enter_case(x,y,__FILE__,__LINE__)) { try {

    //���ʥꥪ���ԥޥ���
#define TEST_FAIL     throw TestSuite::Fail();
#define TEST_FAIL_(x) throw TestSuite::Fail(x);

    //û�����ʥꥪ�ѥޥ���
#define TEST_CASE(x,y,z)   BEGIN_CASE(x,y) { if(!(z)) TEST_FAIL;    } END_CASE
#define TEST_CASE_(x,y,z,u) BEGIN_CASE(x,y) { if(!(z)) TEST_FAIL_(u); } END_CASE

    //��ãȽ��ޥ���
#define CHECKPOINT(x) TestSuite::check(x);

    //���󥰥�ȥ�����
#define SINGLETON(x)    Singleton<x>::Context context;     Singleton<x>::saveContext(context);
#define SINGLETON_(x,y) Singleton<x>::Context context_##y; Singleton<x>::saveContext(context_##y);

/*
 *  �ƥ��ȥ������Ȥμ¹����楯�饹
 */
class TestSuiteControl {
protected:
    std::list<std::string> session;         //���ߤΥ��å����̾�����å�

    std::string    target_session;          //�����оݥ��å����̾
    std::string    current_session;         //���ߤΥ������ȥ��ʥꥪ̾
    std::string    current_description;     //���ߤΥ������ȥ��ʥꥪ������
    std::ostream * out;                     //�����ν�����
    bool           fail;                    //���Ԥ������ʥꥪ�����ä����ɤ���
    bool           verbose;                 //��Ĺ���Ϥ��뤫�ݤ�

    unsigned int   case_count;              //�����������
    unsigned int   fail_count;              //���Ԥ����������ο�

        //���ʥꥪ̾�μ���
    std::string get_suitename(const char * name = "") const;


public:
        //���󥹥ȥ饯��
    TestSuiteControl(std::ostream & _out, const char * _pattern = "");

        //�ƥ��ȥ��ʥꥪ��ɽ������ (�ֵ��� : �¹Ԥ���ɬ�פ����뤫�ɤ���)
    bool        _enter_case(const char * session, const char * description, const char * filename = "", long lineno = -1);
    inline void leave_case(void) { leave_session(); }

        //���󥰥륹�ƥå׼¹Ի���������ӹ��ޤʤ�����Υ�å�
    inline bool enter_case(const char * session, const char * description, const char * filename = "", long lineno = -1)
    {   return _enter_case(session, description, filename, lineno);   }

        //�ƥ��ȥ��å����̾ (���ʥꥪ�ץ�ե�����) ������/���
    void enter_session(const std::string & session);
    void leave_session(void);

        //�ƥ��ȥ��ʥꥪ�μ������
    void fail_in_suite(std::string msg="");                                           

        //���Ԥ������ʥꥪ��̵ͭ�γ�ǧ
    inline bool is_failed(void) const
    {   return fail;   }

        //��Ĺ���Ϥ�����
    inline void set_verbose(bool _verbose = true)
    {   verbose = _verbose;   }

        //�¹Ԥ����ƥ��ȥ������ο�
    inline unsigned int countCases(void) const
    {   return case_count;   }

        //���Ԥ����ƥ��ȥ������ο�
    inline unsigned int countFails(void) const
    {   return fail_count;   }
};

    //���󥰥�ȥ�Υƥ��ȥ������ȤΤ���ˤ����ǥ��󥯥롼��
#include "base/singleton.h"

/*
 *  �ƥ��ȥ������ȼ¹ԥ��饹
 */
class TestSuite {
public:
    class Fail  //�ƥ��ȥ������������Τ��Ѥ����㳰�ѥ��饹
    {
    protected:
        std::string msg;

    public:
            //���󥹥ȥ饯��
        Fail(std::string src = "") throw() : msg(src) {}

            //���ԡ����󥹥ȥ饯��
        Fail(const Fail & src) throw() : msg(src.msg) {}
        
            //��å����������
        inline const std::string & getMessage(void) const throw()
        {   return msg;   }
    };

    typedef void (*SuiteFunction)(TestSuiteControl &);

        /* ���饹��Υƥ��ȥ������Ȥ˴ؤ��������ݻ����륯�饹 */
    class SuiteContainerNode
    {
    protected:
        std::string   session;
        SuiteFunction suite;
    
    public:
            //�������Ⱦ��󥳥󥹥ȥ饯��
        SuiteContainerNode(const char * session, SuiteFunction suite);
        SuiteContainerNode(const SuiteContainerNode & src);

            //�������Ȥμ¹�
        bool invoke(TestSuiteControl & suite_control);

            //��������̾�μ���
        inline const std::string & getName(void) const throw()
        {   return session;   }
    };

        //�¹Ԥ��٤��ƥ��ȥ������Ȥ���ĥ��󥹥��󥹤Υꥹ�Ȥη�
    class SuiteContainer : public std::list<SuiteContainerNode>
    {   public: SINGLETON_CONSTRUCTOR(SuiteContainer) {}   };

        /* �¹ԥ��ץ���� */
    enum tagPerformOption {
        THROUGH = 1,    //���٤��̤��Ǽ¹Ԥ��� (���������ߤ�ʤ�)
        VERBOSE = 2,    //��Ĺ����

        DEFAULT = THROUGH
    };

        /* �����å��ݥ���Ȥ��Ǽ���륯�饹 */
    class Checkpoint : public std::set<std::string>
    { public: SINGLETON_CONSTRUCTOR(Checkpoint) throw() {} };

protected:
    bool            fail;       //�Ǹ�˼¹Ԥ����������Ȥ����Ԥ������ɤ������ݻ������ѿ�
    static bool     starvated;  //new�˼��Ԥ��뤫�ɤ���

public:
        //���󥹥ȥ饯��
    TestSuite(const char * session, SuiteFunction suite);

        //�ǥ��ȥ饯��
    ~TestSuite(void);

        //�ƥ��ȥ������Ȥμ¹�  (�ֵ���:�������Ȥ��������¹Ԥ��줿���ɤ���)
    static bool performTestSuite(int flags = THROUGH, const char * pattern = "");

        //�ƥ��ȥ������Ȥμ¹� (�����Ѵ�)
    inline static bool performTestSuite(const char * pattern)
    {   return performTestSuite(THROUGH, pattern);   }

        //��Ͽ����Ƥ���ȥåץ�٥륹�����Ȥΰ���ɽ��
    static void listTestSuite(void);

        /*
         *   �����å��ݥ�����Ѵؿ�
         */

        //�̲ᤷ�����Ȥ����
    inline static void check(std::string checkname)
    {   Singleton<Checkpoint>::getInstance()->insert(checkname);   }

        //����ޤǤ˼�����������
    inline static void clearCheckpoints(void)
    {   Singleton<Checkpoint>::getInstance()->clear();   }

        //���ΰ��֤��褿��
    static bool isReached(std::string checkname);

        /*
         *   �ƥ����Ѻ�ȴؿ�
         */

        //�ե��������Ȥ򳫤��ƥ����å�����
    static bool compareFileContents(const char * filename, const char * filecontents, bool remove = true);
};

/*
 *  �������ȼ¹���main�ؿ�
 */
extern int main(int argc, char ** argv);

#define main pseudo_main    //�̾��main�򺹤�����

    //�ʰץ��եȥ������ȥ졼����ǽ�Υ��󥯥롼��
#include "base/coverage_defs.h"

#else

/*********************************************************************************************/
/*
 *  �ƥ��Ȥ�¹Ԥ��ʤ��Ȥ��Υ��饹���
 */

#define TESTABLEOBJECT(x)
#define TESTABLEOBJECT_(x,y)
#define TESTSUITE_PROTOTYPE(x)
#define TESTSUITE_(x,y)
#define PROCEED_ONCE

#define BEGIN_CASE(x,y)
#define END_CASE
#define TEST_FAIL

#define CHECKPOINT(x)

/*
    *  �ƥ��ȥ������ȼ¹ԥ��饹
    */
class TestSuite {
public:
        //�ƥ��ȥ������Ȥμ¹�  (�ֵ���:�������Ȥ��������¹Ԥ������ɤ���)
    inline static bool performTestSuite(void) { return true; };
};

#endif

#endif /* TESTSUITE_H */

