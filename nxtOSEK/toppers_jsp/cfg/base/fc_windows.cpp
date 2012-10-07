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
 *  @(#) $Id: fc_windows.cpp,v 1.12 2003/12/20 06:51:58 takayuki Exp $
 */

#if (defined(FILECONTAINER_WINDOWS) || defined(TESTSUITE)) && defined(_MSC_VER)

#pragma warning(disable:4786)

#include "base/filecontainer.h"
#include <windows.h>
#include <imagehlp.h>
#include <string>

using namespace std;

namespace {

    class FileContainerWindowsImpl : public FileContainer
    {
    protected:
        HANDLE          process;
        LOADED_IMAGE    image;
        DWORD           base;

        inline bool isLoaded(void) const
        {   return base != 0;   }

    public:
        FileContainerWindowsImpl(void) throw();
        virtual ~FileContainerWindowsImpl(void) throw();

            /* ���󥿥ե������� */
        virtual void        attachModule(const string & filename) throw(Exception);
        virtual void        loadContents(void * dest, address_t address, size_t size) throw(Exception);
        virtual address_t   getSymbolAddress(const string & symbol) throw(Exception);
        virtual std::string getArchitecture(void) throw();

        TESTSUITE_PROTOTYPE(main)
    };

    FileContainerWindowsImpl instance_of_FileContaienrWindowsImpl;

        /* ���󥹥ȥ饯�� */
    FileContainerWindowsImpl::FileContainerWindowsImpl(void) throw()
        : process(NULL), image(), base(0)
    {}

        /* �ǥ��ȥ饯�� */
    FileContainerWindowsImpl::~FileContainerWindowsImpl(void) throw()
    {
        if(isLoaded()) {
            ::UnMapAndLoad(&image);
            ::SymUnloadModule(process, base);
            process = NULL;
            base    = 0;
        }
    }

        /* �оݥ⥸�塼��γ��� */
    void FileContainerWindowsImpl::attachModule(const std::string & _filename) throw(Exception)
    {
        string filename(_filename);

        process = ::GetCurrentProcess();
        if(::SymInitialize( process , NULL, FALSE) == FALSE)
            ExceptionMessage("[Internal Error] ImageHelper API initialization failure","[�������顼] ������˼��Ԥ��ޤ��� (ImageHlp)").throwException();

        base = ::SymLoadModule(process, NULL, (PSTR)filename.c_str(), NULL, 0, 0);

        image.SizeOfImage = sizeof(LOADED_IMAGE);
        if(::MapAndLoad((PSTR)filename.c_str(), NULL, &image, FALSE, TRUE) == FALSE)
            ExceptionMessage("[Internel error] Module loading failure [%]","[�������顼] �⥸�塼����ɤ߹��ߤ˼��Ԥ��ޤ��� [%]") << filename << throwException;
    }

        /* ���Ƥμ��� */
    void FileContainerWindowsImpl::loadContents(void * dest, address_t address, size_t size) throw(Exception)
    {
        PIMAGE_SECTION_HEADER header;
        unsigned int i;

        address -= base;
        for(i=0;i<image.NumberOfSections;i++) {
            header = image.Sections+i;
            if(address >= header->VirtualAddress && address < header->VirtualAddress + header->SizeOfRawData) {
                address -= header->VirtualAddress - header->PointerToRawData;
                ::CopyMemory(dest,image.MappedAddress + address,size);
                break;
            }
        }

        if(i == image.NumberOfSections)
            ExceptionMessage("[Internel error] Memory read with unmapped address","[�������顼] �ޥåפ���Ƥʤ����ɥ쥹��Ȥäƥ���꡼�ɤ��Ԥ��ޤ���").throwException();
    }

        /* ����ܥ륢�ɥ쥹�β�� */
    FileContainer::address_t FileContainerWindowsImpl::getSymbolAddress(const string & _symbol) throw(Exception)
    {
        FileContainer::address_t result = 0;
        string symbol(_symbol);
        IMAGEHLP_SYMBOL sym;

        if(process == NULL || base == 0)
            ExceptionMessage("Not initialized","���������Ƥޤ���").throwException();

        sym.SizeOfStruct = sizeof(sym);
        sym.MaxNameLength = 0;

        if(::SymGetSymFromName(process, (PSTR)symbol.c_str(), &sym) == TRUE)
            result = static_cast<FileContainer::address_t>(sym.Address);
     
        if(result == 0)
            ExceptionMessage("Unknown symbol [%]","�����ʥ���ܥ�̾ [%]") << symbol << throwException;

        return static_cast<FileContainer::address_t>(sym.Address);
    }

    string FileContainerWindowsImpl::getArchitecture(void) throw()
    {   return "Windows (Win32)";   }

}

//---------------------------------------------

#ifdef TESTSUITE
#include "base/coverage_undefs.h"

#pragma warning(disable:4311) //'reinterpret_cast' : �ݥ��󥿤� 'const int *__w64 ' ���� 'FileContainer::address_t' ���ڤ�ͤ�ޤ���

extern "C" const int FileContainerWindowsImplTestVariable = 0x01234567;
extern "C" const int _FileContainerWindowsImplTestVariableWithUnderbar = 0x89abcdef;

TESTSUITE(main, FileContainerWindowsImpl)
{
    PREDECESSOR("TFileContainer");

    SingletonBase::ContextChain chain;
    chain.saveContext<RuntimeObjectTable>();
    chain.renewInstance();

    BEGIN_CASE("attachModule","attachModule") {
        BEGIN_CASE("1","�¹Ԥ��Ƥ���ץ���ब�����뤫") {
            FileContainerWindowsImpl fcwi;
            bool result = true;
            try { fcwi.attachModule(TestSuite::getProgName()); } catch(...) { result = false; }
            
            TEST_CASE("1", "�㳰�ϵ����ʤ�", result);
        } END_CASE;

        BEGIN_CASE("2","¸�ߤ��ʤ��ե�����̾���㳰") {
            FileContainerWindowsImpl fcwi;
            bool result = false;
            try { fcwi.attachModule("..."); } catch(...) { result = true; }
            
            TEST_CASE("1", "�㳰��������", result);
        } END_CASE;
    } END_CASE;

    BEGIN_CASE("getSymbolAddress","getSymbolAddress") {
        FileContainerWindowsImpl fcwi;

        BEGIN_CASE("1","��������Ƥ��ʤ����֤Ǹ�������") {
            bool result = false;
            try { fcwi.getSymbolAddress("FileContainerWindowsImplTestVariable"); } catch(...) { result = true; }
            TEST_CASE("1","�㳰��������", result);
        } END_CASE;

        fcwi.attachModule(TestSuite::getProgName());

        BEGIN_CASE("2","¸�ߤ��륷��ܥ�򸡺�����") {
            FileContainer::address_t addr = 0;
            bool result = true;

            try { addr = fcwi.getSymbolAddress("FileContainerWindowsImplTestVariable"); } catch(...) { result = false; }

            TEST_CASE("1","�㳰�ϵ����ʤ�", result);
            TEST_CASE("2","���ɥ쥹��������", addr == reinterpret_cast<FileContainer::address_t>(&FileContainerWindowsImplTestVariable));
        } END_CASE;

        BEGIN_CASE("3",";�פ�_�򾡼���ղä��ʤ�") {
            FileContainer::address_t addr = 0;
            bool result = false;

            try { addr = fcwi.getSymbolAddress("FileContainerWindowsImplTestVariableWithUnderbar"); } catch(...) { result = true; }

            TEST_CASE("1","�㳰��������", result);
            TEST_CASE("2","���ɥ쥹��0�Τޤ�", addr == 0);
        } END_CASE;

        BEGIN_CASE("4","¸�ߤ��ʤ�����ܥ�򸡺�����") {
            FileContainer::address_t addr = 0;
            bool result = false;

            try { addr = fcwi.getSymbolAddress("____unknown____"); } catch(...) { result = true; }

            TEST_CASE("1","�㳰��������", result);
        } END_CASE;
    } END_CASE;

    BEGIN_CASE("loadContents","loadContents") {
        FileContainerWindowsImpl fcwi;
        fcwi.attachModule(TestSuite::getProgName());

        BEGIN_CASE("1","¸�ߤ����ѿ����ɤ߽Ф�") {
            FileContainer::address_t addr;
            int i;

            addr = fcwi.getSymbolAddress("FileContainerWindowsImplTestVariable");
            bool result = true;
            try { fcwi.loadContents(&i, addr, sizeof(i)); } catch(...) { result = false; }

            TEST_CASE("1","�㳰�ϵ����ʤ�", result);
            TEST_CASE("2","�ɤ߽Ф��줿���Ƥ�������", i == FileContainerWindowsImplTestVariable);
        } END_CASE;

        BEGIN_CASE("2","¸�ߤ��ʤ��ѿ����ɤ߽Ф�") {
            FileContainer::address_t addr;
            int i;

            addr = ~0;
            bool result = false;
            try { fcwi.loadContents(&i, addr, sizeof(i)); } catch(Exception &) { result = true; }

            TEST_CASE("1","�㳰��������", result);
        } END_CASE;

    } END_CASE;

    chain.restoreContext();
}

#endif /* TESTSUITE */

#endif /* FILECONTAINER_WINDOWS || TESTSUITE */

