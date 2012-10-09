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
 *  @(#) $Id: jsp_common.cpp,v 1.4 2003/12/20 06:51:58 takayuki Exp $
 */

#include "jsp/jsp_common.h"

#include "base/option.h"

#include <ctime>

#if defined(_MSC_VER) || defined(__BORLANDC__)
#  define  GETLOGINNAME_WINDOWS
#  include <windows.h>
#elif __GNUC__
#  define  GETLOGINNAME_UNIX
#  include <unistd.h>
#endif

using namespace std;

#if 0
namespace {
    string get_loginname(void) throw()
    {
        string result("TOPPERS/JSP KernelConfigurator");

#ifdef GETLOGINNAME_WINDOWS
        char  buffer[1024];
        DWORD sz = 1024;
        ::GetUserName(buffer, &sz);
        result.assign(buffer);
#elif defined(GETLOGINNAME_UNIX)
        result.assign(getlogin());
#endif

        return result;
    }
}
#endif


    //���󥯥롼�ɥե�����η����ѹ�����
string ToppersJsp::conv_includefile(string file) throw()
{
    OptionParameter & option = getOptionParameter();
    string result;

        //il���ץ�����դ����Ȥ��ˤ� "<...>" �����ǽ���
    if(option["il"].isValid())
        result = string("<") + file + ">";
    else
        result = string("\"") + file + "\"";

    return result;
}

    //�����ͥ���ѿ�̾�η����ѹ�����
string ToppersJsp::conv_kernelobject(string obj) throw()
{
    OptionParameter & option = getOptionParameter();
    string result;

    result = obj;

        // TOPPERS/JSP rel 1.3����ϥ����ͥ��ѿ���Ƭ�� _kernel_ ��Ĥ���
    if(!option["1.3"].isValid())
        result = string("_kernel_") + obj;

    return result;
}

ToppersJsp::SpecialtyFile::SpecialtyFile(void) throw() : MultipartStream(), RuntimeObject(true)
{}

#if 0
string ToppersJsp::get_agreement(string filename) throw()
{
    const char * base_agreement =
        "/*\n"
        " *  TOPPERS/JSP Kernel\n"
        " *      Toyohashi Open Platform for Embedded Real-Time Systems/\n"
        " *      Just Standard Profile Kernel\n"
        " * \n"
        " *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory\n"
        " *                              Toyohashi Univ. of Technology, JAPAN\n"
        " * \n"
        " *  �嵭����Ԥϡ��ʲ��� (1)��(4) �ξ�狼��Free Software Foundation \n"
        " *  �ˤ�äƸ�ɽ����Ƥ��� GNU General Public License �� Version 2 �˵�\n"
        " *  �Ҥ���Ƥ���������������˸¤ꡤ�ܥ��եȥ��������ܥ��եȥ�����\n"
        " *  ����Ѥ�����Τ�ޤࡥ�ʲ�Ʊ���ˤ���ѡ�ʣ�������ѡ������ۡʰʲ���\n"
        " *  ���ѤȸƤ֡ˤ��뤳�Ȥ�̵���ǵ������롥\n"
        " *  (1) �ܥ��եȥ������򥽡��������ɤη������Ѥ�����ˤϡ��嵭������\n"
        " *      ��ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ��꤬�����Τޤޤη��ǥ���\n"
        " *      ����������˴ޤޤ�Ƥ��뤳�ȡ�\n"
        " *  (2) �ܥ��եȥ������򡤥饤�֥������ʤɡ�¾�Υ��եȥ�������ȯ�˻�\n"
        " *      �ѤǤ�����Ǻ����ۤ�����ˤϡ������ۤ�ȼ���ɥ�����ȡ�����\n"
        " *      �ԥޥ˥奢��ʤɡˤˡ��嵭�����ɽ�����������Ѿ�浪��Ӳ���\n"
        " *      ��̵�ݾڵ����Ǻܤ��뤳�ȡ�\n"
        " *  (3) �ܥ��եȥ������򡤵�����Ȥ߹���ʤɡ�¾�Υ��եȥ�������ȯ�˻�\n"
        " *      �ѤǤ��ʤ����Ǻ����ۤ�����ˤϡ����Τ����줫�ξ�����������\n"
        " *      �ȡ�\n"
        " *    (a) �����ۤ�ȼ���ɥ�����ȡ����Ѽԥޥ˥奢��ʤɡˤˡ��嵭����\n"
        " *        �ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ����Ǻܤ��뤳�ȡ�\n"
        " *    (b) �����ۤη��֤��̤�������ˡ�ˤ�äơ�TOPPERS�ץ������Ȥ�\n"
        " *        ��𤹤뤳�ȡ�\n"
        " *  (4) �ܥ��եȥ����������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������뤤���ʤ�»\n"
        " *      ������⡤�嵭����Ԥ����TOPPERS�ץ������Ȥ����դ��뤳�ȡ�\n"
        " * \n"
        " *  �ܥ��եȥ������ϡ�̵�ݾڤ��󶡤���Ƥ����ΤǤ��롥�嵭����Ԥ�\n"
        " *  ���TOPPERS�ץ������Ȥϡ��ܥ��եȥ������˴ؤ��ơ�����Ŭ�Ѳ�ǽ����\n"
        " *  �ޤ�ơ������ʤ��ݾڤ�Ԥ�ʤ����ޤ����ܥ��եȥ����������Ѥˤ��ľ\n"
        " *  ��Ū�ޤ��ϴ���Ū�������������ʤ�»���˴ؤ��Ƥ⡤������Ǥ�����ʤ���\n"
        " * \n";

    string work(base_agreement);

        //CVS��ID���Τ�Τ򤯤äĤ���
    time_t t;
    time(&t);

    work += string(" * @(#)$Id: ");
    work += filename;
    work += " ";
    work += static_cast<const char *>(asctime(localtime(&t)));
    
    work.erase(work.size() - 1);    //asctime�ǲ��Ԥ�����Τ�chomp

    work += " ";
    work += get_loginname();
    work += " Exp $\n */\n\n";

    return work;
}
#endif


/***************************************** �ƥ��ȥ������� *****************************************/

#ifdef TESTSUITE

class SpecialtyFile_test : public ToppersJsp::SpecialtyFile
{
public:
    ~SpecialtyFile_test(void) throw() { TestSuite::check("SpecialtyFile::~SpecialtyFile"); }
    TESTSUITE_PROTOTYPE(main)
};

TESTSUITE(main, SpecialtyFile_test)
{
    BEGIN_CASE("constructor","constructor") {
        BEGIN_CASE("1","���������ROT�˾��") {
            SpecialtyFile_test file;

            if(RuntimeObjectTable::getInstance<SpecialtyFile_test>() == 0)
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("2","�˴����оݤˤʤäƤ���") {
            Singleton<RuntimeObjectTable>::Context context;
            Singleton<RuntimeObjectTable>::saveContext(context);

            Singleton<RuntimeObjectTable>::renewInstance();

            new SpecialtyFile_test;

            TEST_CASE("0","[����] ��Ͽ����Ƥ���", RuntimeObjectTable::getInstance<SpecialtyFile_test>() != 0);
            
            TestSuite::clearCheckpoints();
            Singleton<RuntimeObjectTable>::renewInstance(); //���󥹥��󥹤κ�������ROT����������

            TEST_CASE("1","ROT����������Ƥ���", RuntimeObjectTable::getInstance<SpecialtyFile_test>() == 0);
            TEST_CASE("2","�ǥ��ȥ饯������ư����Ƥ���", TestSuite::isReached("SpecialtyFile::~SpecialtyFile"));

            Singleton<RuntimeObjectTable>::restoreContext(context);
        } END_CASE;
    } END_CASE;

    BEGIN_CASE("createInstance","createInstance") {
        BEGIN_CASE("1","���󥹥��󥹤������Ǥ���") {
            SpecialtyFile_test * file = SpecialtyFile::createInstance<SpecialtyFile_test>("test.txt");

            file->disableOutput();  //���Ϥ���Ƥ⺤��Τ�

            TEST_CASE("1","��NULL���֤�", file != 0);
            TEST_CASE("2","�ե�����̾������",  file->getFilename().compare("test.txt") == 0);
        } END_CASE;

        BEGIN_CASE("2","��ʸ�����Ϥ����㳰") {

            bool result = false;
            try {
                SpecialtyFile::createInstance<SpecialtyFile_test>("");
            }
            catch(Exception &) {
                result = true;
            }

            TEST_CASE("1","�㳰��������", result);
            TEST_CASE("2","���֥������ȤϤʤ�", RuntimeObjectTable::getInstance<SpecialtyFile_test>() == 0);
        } END_CASE;
    } END_CASE;
}

namespace {
    extern void testsuite(TestSuiteControl & _suite_control);
    TestSuite testsuite_onTop("TOPPERS/JSP Common Function(main)", testsuite);

            //�ƥ��ȥ������Ȥ�����
    void testsuite(TestSuiteControl & _suite_control)
    {
        Singleton<OptionParameter>::Context context;
        Singleton<OptionParameter>::saveContext(context);

        BEGIN_CASE("conv_includefile","conv_includefile") {
            BEGIN_CASE("1","-il���դ��Ƥ��ʤ��ȥ��֥륯�����ȤǤ�����") {
                Singleton<OptionParameter>::renewInstance();

                if(ToppersJsp::conv_includefile("test.h").compare("\"test.h\"") != 0)
                    TEST_FAIL;
            } END_CASE;

            BEGIN_CASE("1","-il���դ��Ƥ����<>�Ǥ�����") {
                Singleton<OptionParameter>::renewInstance();
                char * argv[] = {"test.exe","-il"};
                getOptionParameter().parseOption(2, argv);

                if(ToppersJsp::conv_includefile("test.h").compare("<test.h>") != 0)
                    TEST_FAIL;
            } END_CASE;
        } END_CASE;

        BEGIN_CASE("conv_kernelobject","conv_kernelobject") {
            BEGIN_CASE("1","-1.3���դ��Ƥ��ʤ���_kernel_���դ�") {
                Singleton<OptionParameter>::renewInstance();

                if(ToppersJsp::conv_kernelobject("test").compare("_kernel_test") != 0)
                    TEST_FAIL;
            } END_CASE;

            BEGIN_CASE("1","-1.3���դ��Ƥ���Ȥ��Τޤ޽ФƤ���") {
                Singleton<OptionParameter>::renewInstance();
                char * argv[] = {"test.exe","-1.3"};
                getOptionParameter().parseOption(2, argv);

                if(ToppersJsp::conv_kernelobject("test").compare("test") != 0)
                    TEST_FAIL;
            } END_CASE;
        } END_CASE;

        Singleton<OptionParameter>::restoreContext(context);

    }
}
#endif


