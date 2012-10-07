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
 *  @(#) $Id: filecontainer.cpp,v 1.11 2003/12/20 06:51:58 takayuki Exp $
 */

#ifdef _MSC_VER
#pragma warning(disable:4786) //�ǥХå�ʸ�����255ʸ�����ڤ�ͤ᤿
#endif

#include "base/filecontainer.h"
#include <memory.h>
#include <fstream>

using namespace std;

namespace {
        /* ���ʤ�10��ʸ����Υѡ��� */
    char * parse_uint(char * src, unsigned int * dest, unsigned int default_value = 0)
    {
        int result = 0;

        if(*src < '0' || *src > '9') {
            *dest = default_value;
            return src;
        }

        do {
            result = result * 10 + *(src++) - '0';
        } while(*src >= '0' && *src <='9');

        *dest = result;
        return src;
    }
}

    /* �ѿ�������ɤ߹��� */
void FileContainer::attachInfo(const string & filename) throw(Exception)
{
    char    buffer[256];
    fstream file;

    char * work;
    struct tagVariableInfo info;

    memset(&info, 0, sizeof(info));

    file.open(filename.c_str(), ios::in);
    if(!file.is_open()) {
        ExceptionMessage("Structure information file(%) was not found. ","��¤�ξ���ե�����(%)�����Ĥ���ޤ��� ") << filename << throwException;
        return;
    }

    while(!file.eof())
    {
        file.get(buffer, 256);

        if(!file.fail()) {
            switch(buffer[0])
            {
            case 's':
                {
                    unsigned int address = 0;
                    unsigned int size    = 0;

                    work = buffer+1;
                    while(*work != ',' && *work != '\x0')
                        work++;
                    if(*work != '\x0') {
                        *work = '\x0';
                        work = parse_uint(work+1,&size);
                        work = parse_uint(work+1,&address);
                    }

                    info.address = static_cast<address_t>(address);
                    info.size    = static_cast<size_t>(size);
                    variableinfo[string(buffer+1)] = info;
                    break;
                }

            case 'd':   //���̻�̾��̵��
                break;

            default:
                ExceptionMessage("Unknown information type identifier found - [%]","̤�Τη����̻� - [%]") << buffer[0] << throwException;
            }
        }
        else
            file.clear();

        file.get();
    }

    file.close();
}

    /* �ѿ�����μ��� */
struct FileContainer::tagVariableInfo FileContainer::getVariableInfo(const string & name) throw(Exception)
{
    map<string, tagVariableInfo>::const_iterator scope;

    scope = variableinfo.find(name);
    if(scope == variableinfo.end()) {
        ExceptionMessage("Operation against the unknwon symbol [%] was rejected.","�����ʥ���ܥ�̾ [%] �ξ����������褦�Ȥ��Ƥ��ޤ�") << name << throwException;

        struct tagVariableInfo dummy;
        memset(&dummy, 0, sizeof(dummy));
        return dummy;
    }

    return scope->second;
}


    /* ���󥹥ȥ饯�� (����ܥ�̾����ꤷ�ƽ����) */
TargetVariableBase::TargetVariableBase(const std::string & sym) throw() 
    : address(0), size(0), offset(0), structure_size(0), loaded(false)
{
    try{
        FileContainer * fc = FileContainer::getInstance();
        address = fc->getSymbolAddress(sym);
        size    = fc->getVariableInfo(sym).size;
        structure_size = size;
    }
    catch(...) {
        address = 0;
        size    = 0;
    }
}

    /* ���󥹥ȥ饯�� (����ܥ�̾, �ǡ���Ĺ����ꤷ�ƽ����) */
TargetVariableBase::TargetVariableBase(const string & sym, size_t _size) throw() 
    : address(0), size(_size), offset(0), structure_size(_size), loaded(false)
{
    try{
        FileContainer * fc = FileContainer::getInstance();
        address = fc->getSymbolAddress(sym);
    }
    catch(...) {
        address = 0;
        size    = 0;
    }
}

    /* ���󥹥ȥ饯�� (����ܥ�̾������̾����ꤷ�ƽ����) */
TargetVariableBase::TargetVariableBase(const string & sym, const string & sz) throw() 
    : address(0), size(0), offset(0), structure_size(0), loaded(false)
{
    try{
        FileContainer * fc = FileContainer::getInstance();
        address = fc->getSymbolAddress(sym);                                //��¤�Τ���Ƭ���ɥ쥹
        size    = fc->getVariableInfo(sz).size;                             //�����ѿ���Ĺ��
        offset  = static_cast<size_t>(fc->getVariableInfo(sz).address);     //�����ѿ��Υ��ե��å�
        structure_size = fc->getVariableInfo(sym).size;                     //��¤�Τ�Ĺ��
    }
    catch(...) {
        address = 0;
        size    = 0;
    }
}

    /* ���ԡ����󥹥ȥ饯�� */
TargetVariableBase::TargetVariableBase(const TargetVariableBase & src) throw()
    : address(0), size(0), offset(0), structure_size(0), loaded(false)
{
    if(src.isValid()) {
        address        = src.address;
        size           = src.size;
        offset         = src.offset;   
        structure_size = src.structure_size;
        loaded         = false;
    }
}


    /* ���֥����������Ƥμ��� */
void TargetVariableBase::loadContent(void * dest, size_t dest_size) throw(Exception)
{
    char * buffer = 0;

    try {
        if(isValid()) {
            buffer = new char[getSize()];
            FileContainer * fc = FileContainer::getInstance();

            fc->loadContents(buffer, getAddress() + getOffset(), getSize());
            if(fc->getByteOrder() != FileContainer::HOSTORDER)
                changeEndian(buffer, getSize());

            if(size < dest_size)
                memset(dest, 0, dest_size);
            else if(size > dest_size)
                ExceptionMessage("[TargetVariableBase::loadContent] Destination storage is too small to store the contents.","[TargetVariableBase::loadContent] ������Хåե��Υ����������������ޤ�").throwException();
            memcpy(dest, buffer, getSize());

            delete [] buffer;
            loaded = true;
        }
        else {
            ExceptionMessage("loadContent was performed with an illegal target variable.","�����ʥ������å��ѿ������loadContent���ƤФ�ޤ���").throwException();
        }
    }
    catch(bad_alloc &) {
        ExceptionMessage("No available memory [%B]","������­�Ǥ� [%B]") << (unsigned int)getSize() << throwException;
    }
    catch(Exception &) {
        if(buffer)
            delete [] buffer;
        throw;
    }
}

    /* �Х��ȥ��������ѹ� */
void TargetVariableBase::changeEndian(char * buffer, size_t size) throw()
{
    char * tail = buffer + size - 1;

    while(buffer < tail) {
        char temporary = *buffer;
        *buffer = *tail;
        *tail   = temporary;

        ++ buffer;
        -- tail;
    }
}



//---------------------------------------------

#ifdef TESTSUITE
#include "base/coverage_undefs.h"

#include <cctype>
#define _isprint(x) isprint(x)

class TFileContainer : public FileContainer
{
public:
    TFileContainer(void) throw() {}
    virtual ~TFileContainer(void) throw() {}

    string module;
    void attachModule(const std::string & _module) throw(Exception) 
    {
        CHECKPOINT("attachModule"); 
        module = _module;
    }

    void *    dest;
    address_t addr;
    size_t    sz;
    void loadContents(void * _dest, address_t _addr, size_t _sz) throw(Exception) 
    {
        CHECKPOINT("loadContents");
        dest = _dest;
        addr = _addr;
        sz   = _sz;
        memset(_dest, ~0, _sz);
    }

    string symbol;
    address_t getSymbolAddress(const std::string & _symbol) throw(Exception) 
    {
        CHECKPOINT("getSymbolAddress");
        symbol = _symbol;
        return 1; 
    }

    std::string getArchitecture(void) throw(Exception)
    {   return "TFileContainer";   }

    TESTSUITE_PROTOTYPE(main)
};

TESTSUITE(main, TFileContainer)
{
    PREDECESSOR("SingletonBase");
    PREDECESSOR("RuntimeObjectTable");

    SingletonBase::ContextChain chain;
    chain.saveContext<RuntimeObjectTable>();
    chain.renewInstance();

    BEGIN_CASE("getInstance","getInstance") {
        BEGIN_CASE("1","������Ͽ����Ƥ��ʤ��Ȥ���getInstance���㳰") {
            bool result = false;
            try { FileContainer::getInstance(); } catch(Exception &) { result = true; }
            if(!result)
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("2","getInstance�ǥ��󥹥��󥹤��֤�") {
            TFileContainer fc;
            FileContainer * instance;
            bool result = true;
            try { instance = FileContainer::getInstance(); } catch(...) { result = false; }
            TEST_CASE("1","�㳰�Ϥ����ʤ�", result);
            TEST_CASE("2","�����Ǥ��륤�󥹥��󥹤�������", instance == &fc);
        } END_CASE;
    } END_CASE;

    BEGIN_CASE("parse_uint","parse_uint") {
        BEGIN_CASE("1","�������ڤ�Ф���") {
            unsigned int dest;
            char * src = "123";
            char * result = parse_uint(src, &dest);

            TEST_CASE("1","result���Ǹ����Ƥ���", result == src + 3);
            TEST_CASE("2","�ͤ�������", dest == 123);
        } END_CASE;

        BEGIN_CASE("2","������̵��ʸ����Ϳ����ȥǥե�����ͤ��֤�") {
            unsigned int dest;
            char * src = "abc";
            char * result = parse_uint(src, &dest, 1234567);

            TEST_CASE("1","result�Ͽʤ�Ǥ��ʤ�", result == src);
            TEST_CASE("2","�ǥե�����ͤ��֤�", dest == 1234567);
        } END_CASE;

        BEGIN_CASE("3","�ǥ�ߥ��ǤȤޤ�") {
            unsigned int dest;
            char * src = "321,123";
            char * result = parse_uint(src, &dest);

            TEST_CASE("1","result�Ͽʤ�Ǥ��ʤ�", result == src + 3);
            TEST_CASE("2","�ǥե�����ͤ��֤�", dest == 321);
        } END_CASE;
    } END_CASE;

    BEGIN_CASE("attachInfo","attachInfo") {
        BEGIN_CASE("1","���̤˽����򤵤���") {
            fstream file("dummy",ios::out);
            file << "s_kernel_tinib_table,32,0\nstask_initialization_block::texrtn,4,28\n";
            file.close();

            TFileContainer fc;

            bool result = true;
            try { fc.attachInfo("dummy"); } catch(...) { result = false; }

            TEST_CASE("1","�㳰�Ϥ����ʤ�", result);

            map<string, struct tagVariableInfo>::iterator scope = fc.variableinfo.find("_kernel_tinib_table");
            TEST_CASE("2","���Ǥ��ɲä���Ƥ��� (tinib)", scope != fc.variableinfo.end());
            TEST_CASE("3","�ͤ������� (tinib)", scope->second.size == 32);

            scope = fc.variableinfo.find("task_initialization_block::texrtn");
            TEST_CASE("4","���Ǥ��ɲä���Ƥ��� (texrtn)", scope != fc.variableinfo.end());
            TEST_CASE("5","�ͤ������� (texrtn.size)", scope->second.size == 4);
            TEST_CASE("6","�ͤ������� (texrtn.address)", scope->second.address == 28);
        } END_CASE;
        remove("dummy");

        BEGIN_CASE("2","����ʸ�� 'd' ��̵�뤹��") {
            fstream file("dummy",ios::out);
            file << "ddummy,0\ndtask_initialization_block::texrtn,4,28\n";
            file.close();

            TFileContainer fc;

            bool result = true;
            try { fc.attachInfo("dummy"); } catch(...) { result = false; }

            TEST_CASE("1","�㳰�Ϥ����ʤ�", result);
            TEST_CASE("2","���Ǥ��ɲä���Ƥ��ʤ�", fc.variableinfo.size() == 0);
        } END_CASE;
        remove("dummy");

        BEGIN_CASE("3","���Ԥ�̵��Ǥ���") {
            fstream file("dummy",ios::out);
            file << "s_kernel_tinib_table,32,0\n\nstask_initialization_block::texrtn,4,28\n";
            file.close();

            TFileContainer fc;

            bool result = true;
            try { fc.attachInfo("dummy"); } catch(...) { result = false; }

            TEST_CASE("1","�㳰�Ϥ����ʤ�", result);

            map<string, struct tagVariableInfo>::iterator scope = fc.variableinfo.find("_kernel_tinib_table");
            TEST_CASE("2","���Ǥ��ɲä���Ƥ��� (tinib)", scope != fc.variableinfo.end());
            TEST_CASE("3","�ͤ������� (tinib)", scope->second.size == 32);

            scope = fc.variableinfo.find("task_initialization_block::texrtn");
            TEST_CASE("4","���Ǥ��ɲä���Ƥ��� (texrtn)", scope != fc.variableinfo.end());
            TEST_CASE("5","�ͤ������� (texrtn.size)", scope->second.size == 4);
            TEST_CASE("6","�ͤ������� (texrtn.address)", scope->second.address == 28);
        } END_CASE;
        remove("dummy");

        BEGIN_CASE("4","'s'��'d'�ʳ���Ϥ���") {
            char c;
            char msg[2] = {0, 0};

            for(c=0;c<128;++c) {
                if(isprint(c) && (c != 's' && c != 'd')) {
                    fstream file("dummy",ios::out);
                    file << c;
                    file << "dummy,0\n";
                    file.close();

                    TFileContainer fc;

                    bool result = false;
                    try { fc.attachInfo("dummy"); } catch(...) { result = true; }

                    msg[0] = c;
                    TEST_CASE_("1","�㳰��������", result, string(msg));
                    TEST_CASE_("2","���Ǥ��ɲä���Ƥ��ʤ�", fc.variableinfo.size() == 0, string(msg));
                }
            }
        } END_CASE;
        remove("dummy");
    } END_CASE;

    chain.restoreContext();
}

class TTargetVariable : public TargetVariable<int>
{
    TESTSUITE_PROTOTYPE(main)

        /*
         * ���󥹥ȥ饯�� (TargetVariable<int>�˲���)
         */
    inline TTargetVariable(FileContainer::address_t addr) throw()
        : TargetVariable<int>(addr)
    {}
    
    inline TTargetVariable(FileContainer::address_t addr, size_t sz) throw()
        : TargetVariable<int>(addr, sz)
    {}

    inline TTargetVariable(FileContainer::address_t addr, size_t sz, size_t ofs, size_t ssz) throw()
        : TargetVariable<int>(addr, sz, ofs, ssz)
    {}

    inline TTargetVariable(const std::string & sym) throw()
        : TargetVariable<int>(sym)
    {}

    inline TTargetVariable(const std::string & sym, const std::string & sz) throw()
        : TargetVariable<int>(sym, sz)
    {}

        /* �ǥ��ȥ饯�� (�ä˲��⤷�ʤ�) */
    virtual ~TTargetVariable(void) throw() 
    {}
};

TESTSUITE(main, TTargetVariable)
{
    PREDECESSOR("SingletonBase");
    PREDECESSOR("TFileContainer");
    PREDECESSOR("RuntimeObjectTable");

    SingletonBase::ContextChain chain;
    chain.saveContext<RuntimeObjectTable>();
    chain.renewInstance();

    TFileContainer fc;
    fstream file("dummy",ios::out);
    file << "s_test,4,0\ns_kernel_tinib_table,32,0\nstask_initialization_block::texrtn,4,28\n";
    file.close();

    fc.attachInfo("dummy");

    BEGIN_CASE("constructor","���󥹥ȥ饯��") {
        BEGIN_CASE("1", "(address_t, size_t)") {
            TTargetVariable tv(1, 2);

            TEST_CASE("1","�ѿ���ͭ��", tv.isValid());
            TEST_CASE("2","���ɥ쥹��������", tv.getAddress() == 1);
            TEST_CASE("3","��������������", tv.getSize() == 2);
            TEST_CASE("4","���ե��åȤ�0", tv.getOffset() == 0);
            TEST_CASE("5","��¤�Υ��������ѿ��������Ȱ��", tv.getStructureSize() == tv.getSize());
        } END_CASE;

        BEGIN_CASE("2","(address_t, size_t, size_t, size_t)") {
            TTargetVariable tv(1,2,3,4);

            TEST_CASE("1","�ѿ���ͭ��", tv.isValid());
            TEST_CASE("2","���ɥ쥹��������", tv.getAddress() == 1);
            TEST_CASE("3","��������������", tv.getSize() == 2);
            TEST_CASE("4","���ե��åȤ�������", tv.getOffset() == 3);
            TEST_CASE("5","��¤�Υ�������������", tv.getStructureSize() == 4);
        } END_CASE;

        BEGIN_CASE("3","(string)") {
            TestSuite::clearCheckpoints();

            TTargetVariable tv("_test");

            TEST_CASE("1","�ѿ���ͭ��", tv.isValid());
            TEST_CASE("2","getSymbolAddress�������뤵��Ƥ���", TestSuite::isReached("getSymbolAddress"));
            TEST_CASE("3","getSymbolAddress�ΰ�����������", fc.symbol.compare("_test") == 0);
            TEST_CASE("3","���ɥ쥹��������", tv.getAddress() == 1);
            TEST_CASE("4","��������������", tv.getSize() == 4);
            TEST_CASE("5","���ե��åȤ�������", tv.getOffset() == 0);
            TEST_CASE("6","��¤�Υ�������������", tv.getStructureSize() == 4);
        } END_CASE;

        BEGIN_CASE("4","(string,string)") {
            TestSuite::clearCheckpoints();

            TTargetVariable tv("_kernel_tinib_table", "task_initialization_block::texrtn");

            TEST_CASE("1","�ѿ���ͭ��", tv.isValid());
            TEST_CASE("2","getSymbolAddress�������뤵��Ƥ���", TestSuite::isReached("getSymbolAddress"));
            TEST_CASE("3","getSymbolAddress�ΰ�����������", fc.symbol.compare("_kernel_tinib_table") == 0);
            TEST_CASE("3","���ɥ쥹��������", tv.getAddress() == 1);
            TEST_CASE("4","��������������", tv.getSize() == 4);
            TEST_CASE("5","���ե��åȤ�������", tv.getOffset() == 28);
            TEST_CASE("6","��¤�Υ�������������", tv.getStructureSize() == 32);
        } END_CASE;

        BEGIN_CASE("5","̵���ʥ�����") {
            TEST_CASE("1","���ɥ쥹0���ѿ���̵�� (1)", !TTargetVariable(0,4).isValid());
            TEST_CASE("2","���ɥ쥹0���ѿ���̵�� (2)", !TTargetVariable(0,4,4,4).isValid());
            TEST_CASE("3","������0���ѿ���̵�� (1)", !TTargetVariable(4,0).isValid());
            TEST_CASE("4","������0���ѿ���̵�� (2)", !TTargetVariable(4,0,4,4).isValid());
            TEST_CASE("5","��¤�Υ�����0���ѿ���̵��", !TTargetVariable(4,4,4,0).isValid());

            TEST_CASE("6","¸�ߤ��ʤ�����ܥ�̾���ѿ���̵��(1)", !TTargetVariable("unknown").isValid());
            TEST_CASE("7","¸�ߤ��ʤ�����ܥ�̾���ѿ���̵��(2)", !TTargetVariable("unknown","task_initialization_block::texrtn").isValid());
            TEST_CASE("8","¸�ߤ��ʤ�����̾���ѿ���̵��", !TTargetVariable("_kernel_tinib_table","unknown").isValid());

            TEST_CASE("10","��Ǽ�ΰ褬��­���Ƥ����ѿ�", !TTargetVariable("_kernel_tinib_table").isValid());
            TEST_CASE("11","̵���ʰ�������ä����", !TTargetVariable(*((TTargetVariable *)0)).isValid());
        } END_CASE;
    } END_CASE;

    BEGIN_CASE("loadContents", "loadContents") {
        BEGIN_CASE("1","�̾ﵯư") {
            int i;
            TTargetVariable tv(0x100);

            bool result = true;
            try { tv.loadContent(&i, sizeof(int)); } catch(...) { result = false; }

            TEST_CASE("1","�㳰�ϵ�����ʤ�", result);
            TEST_CASE("2","��Ȥ�~0�ǥե��뤵��Ƥ���", i == ~0);
        } END_CASE;

        BEGIN_CASE("2","�������礭�ʷ��Ǽ�����") {
            struct { int first; int second; } i;
            TTargetVariable tv(0x100);

            bool result = true;
            try { tv.loadContent(&i, sizeof(i)); } catch(...) { result = false; }

            TEST_CASE("1","�㳰�ϵ�����ʤ�", result);
            TEST_CASE("2","��Ȥ�~0�ǥե��뤵��Ƥ���", i.first == ~0);
            TEST_CASE("3","�Ĥ��0�ǥե��뤵��Ƥ���", i.second == 0);
        } END_CASE;

        BEGIN_CASE("3","̵�������Ǥ��Ф��Ƽ¹Ԥ���") {
            TTargetVariable tv(0, 0, 0, 0);
            int i;

            bool result = false;
            try{ tv.loadContent(&i, sizeof(i)); } catch(...) { result = true; }
            TEST_CASE("1","�㳰��������", result);
        } END_CASE;

        BEGIN_CASE("4","�����⾮���ʷ��Ǽ�����") {
            char i;
            TTargetVariable tv(0x100);

            bool result = false;
            try { tv.loadContent(&i, sizeof(i)); } catch(...) { result = true; }

            TEST_CASE("1","�㳰��������", result);
        } END_CASE;

    } END_CASE;

    BEGIN_CASE("pointer_operators","�ݥ������α黻") {
        TargetVariable<int> tv(0x100);
        TargetVariable<int> tvl(0x100);

        *tvl;

        TEST_CASE("0","[����] tv:���ɥ쥹��0x100", tv.getAddress() == 0x100);
        TEST_CASE("0","[����] tv:��������4", tv.getSize() == 4);
        TEST_CASE("0","[����] tv:��¤�Υ�������4", tv.getStructureSize() == 4);
        TEST_CASE("0","[����] tv:�ɽФ�̤λ", !tv.isLoaded());
        TEST_CASE("0","[����] tvl:���ɥ쥹��0x100", tvl.getAddress() == 0x100);
        TEST_CASE("0","[����] tvl:��������4", tvl.getSize() == 4);
        TEST_CASE("0","[����] tvl:��¤�Υ�������4", tvl.getStructureSize() == 4);
        TEST_CASE("0","[����] tvl:�ɽФ���λ", tvl.isLoaded());

        BEGIN_CASE("1","operator +") {
            TestSuite::clearCheckpoints();

            TargetVariable<int> work = tv + 0x10;
            TEST_CASE("1","work�Υ��ɥ쥹��0x140", work.getAddress() == 0x100 + sizeof(int) * 0x10);
            TEST_CASE("2","work���ɤ߹��ޤ�Ƥ��ʤ�", !work.isLoaded());
        } END_CASE;

        BEGIN_CASE("2","operator -") {
            TestSuite::clearCheckpoints();

            TargetVariable<int> work = tv - 0x10;
            TEST_CASE("1","work�Υ��ɥ쥹��0xc0", work.getAddress() == 0x100 - sizeof(int) * 0x10);
            TEST_CASE("2","work���ɤ߹��ޤ�Ƥ��ʤ�", !work.isLoaded());
        } END_CASE;

        BEGIN_CASE("3","operator ++") {
            TestSuite::clearCheckpoints();

            TargetVariable<int> work(tvl);

            TargetVariable<int> result = (++ work);

            TEST_CASE("1","work�Υ��ɥ쥹��0x104", work.getAddress() == 0x100 + sizeof(int));
            TEST_CASE("2","work == result", work == result);
            TEST_CASE("3","�ɤ߹���̤λ����", !result.isLoaded());
        } END_CASE;

        BEGIN_CASE("4","operator ++(int)") {
            TestSuite::clearCheckpoints();

            TargetVariable<int> work(tvl);

            TargetVariable<int> result = (work++);

            TEST_CASE("1","work�Υ��ɥ쥹��0x104", work.getAddress() == 0x100 + sizeof(int));
            TEST_CASE("2","result�Υ��ɥ쥹��0x100", result.getAddress() == 0x100);
            TEST_CASE("3","�ɤ߹��ߴ�λ����", result.isLoaded());
        } END_CASE;

        BEGIN_CASE("5","operator --") {
            TestSuite::clearCheckpoints();

            TargetVariable<int> work(tvl);

            TargetVariable<int> result = (-- work);

            TEST_CASE("1","work�Υ��ɥ쥹��0x9c", work.getAddress() == 0x100 - sizeof(int));
            TEST_CASE("2","work == result", work == result);
            TEST_CASE("3","�ɤ߹���̤λ����", !result.isLoaded());
        } END_CASE;

        BEGIN_CASE("6","operator --(int)") {
            TestSuite::clearCheckpoints();

            TargetVariable<int> work(tvl);

            TargetVariable<int> result = (work--);

            TEST_CASE("1","work�Υ��ɥ쥹��0x9c", work.getAddress() == 0x100 - sizeof(int));
            TEST_CASE("2","result�Υ��ɥ쥹��0x100", result.getAddress() == 0x100);
            TEST_CASE("3","�ɤ߹��ߴ�λ����", result.isLoaded());
        } END_CASE;

        BEGIN_CASE("7","operator +=") {
            TestSuite::clearCheckpoints();

            TargetVariable<int> work(tvl);

            work += 0x10;

            TEST_CASE("1","work�Υ��ɥ쥹��0x140", work.getAddress() == 0x100 + sizeof(int) * 0x10);
            TEST_CASE("2","�ɤ߹���̤λ����", !work.isLoaded());
        } END_CASE;

        BEGIN_CASE("8","operator -=") {
            TestSuite::clearCheckpoints();

            TargetVariable<int> work(tvl);

            work -= 0x10;

            TEST_CASE("1","work�Υ��ɥ쥹��0xc0", work.getAddress() == 0x100 - sizeof(int) * 0x10);
            TEST_CASE("2","�ɤ߹���̤λ����", !work.isLoaded());
        } END_CASE;

        BEGIN_CASE("9", "operator &") {
            TEST_CASE("1","���ɥ쥹��ȴ����", &tv == 0x100);
            TEST_CASE("2","NULL���󥹥��󥹤ˤ�0���֤�", &(*((TargetVariable<int> *)0)) == 0);
        } END_CASE;

        BEGIN_CASE("10", "operator *") {
            TestSuite::clearCheckpoints();
            TargetVariable<int> work(0x100);

            const void * result = &(*work);

            TEST_CASE("1","loadContents���¹Ԥ���Ƥ���", TestSuite::isReached("loadContents"));
            TEST_CASE("2","������������", fc.addr == 0x100);
            TEST_CASE("3","������������", fc.sz == sizeof(int));

            TestSuite::clearCheckpoints();
            *work;

            TEST_CASE("4","loadContents�ϼ¹Ԥ���ʤ�", !TestSuite::isReached("loadContents"));
        } END_CASE;

        BEGIN_CASE("11","operator ==/!=") {
            TEST_CASE("1","���ɥ쥹�����פ����OK", tv == TTargetVariable(tv.getAddress()));
            TEST_CASE("2","NULL���󥹥��󥹤Ȥ���Ӥ�Ǥ���", tv != *((TTargetVariable *)0));
        } END_CASE;

        BEGIN_CASE("cvr","���Х�å��к�") {
            
            (*((TTargetVariable *)0)) ++;

        } END_CASE;

    } END_CASE;

    chain.restoreContext();
}


#endif

