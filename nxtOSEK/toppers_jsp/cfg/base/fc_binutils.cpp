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
 *  @(#) $Id: fc_binutils.cpp,v 1.21 2004/09/04 15:50:13 honda Exp $
 */

#if defined(FILECONTAINER_BINUTILS) || defined(TESTSUITE)

#ifdef _MSC_VER
#pragma warning(disable:4786) //�ǥХå�ʸ�����255ʸ�����ڤ�ͤ᤿
#endif

#include "base/filecontainer.h"
#include <string>
#include <map>
#include <fstream>
#include <cassert>
#include <cctype>
#include <cstdio>
#include <cstdlib>

#define _isspace(x)  isspace(x)
#define _isprint(x)  isprint(x)

#define SIZE_LOADPAGE 65536         //�Х��ʥ�ǡ������Ǽ����ڡ���ñ��

#define SIZE_TO_CONFIRM_BINARYFILE 128  //�ե����뤬�Х��ʥ��ޤफ�ɤ������ǧ����Τ��ɤ߽Ф��ǡ�����Ĺ�� (�Хåե�����ΤǤ��ޤ��礭�����ʤ�����)

#define MAGIC_SYMBOL "_checker_magic_number"
#define MAGIC_NUMBER 0x01234567                         //4�Х��Ȥ�����

#define CMD_GNUNM      "nm"
#define CMD_GNUOBJCOPY "objcopy"

#define MAKE_BASEADDRESS(x)   ((x) & ~(SIZE_LOADPAGE-1))
#define MAKE_OFFSETADDRESS(x) ((x) &  (SIZE_LOADPAGE-1))

using namespace std;

namespace {

    class FileContainerBinutilsImpl : public FileContainer
    {
    public:
        typedef void (interceptor_func_t)(fstream &, const string &);      //�԰դ�ˬ�줿�Х��ʥ�ե�����ν�����б�����ؿ��η�

    protected:
        string                 symbol_prefix;
        map<string, address_t> symbol_table;
        map<address_t, char *> contents;

        address_t last_address;     //����å����ɤ�
        char *    last_page;

            //�ǡ���������
        void loadSymbols(fstream & file)  throw(Exception);
        void loadDataContents(fstream & file) throw(Exception);

            //contents��1�Х��Ƚ񤭹���
        void writeByte(address_t address, unsigned int) throw(Exception);

            //��ư����
        void searchSymbolPrefix(void) throw();
        void searchByteOrder(void)    throw();

    public:
        FileContainerBinutilsImpl(void) throw();
        virtual ~FileContainerBinutilsImpl(void) throw();

            /* ���󥿥ե������� */
        virtual void        attachModule(const string & filename) throw(Exception);
        virtual void        loadContents(void * dest, address_t address, size_t size) throw(Exception);
        virtual address_t   getSymbolAddress(const string & symbol) throw(Exception);
        virtual std::string getArchitecture(void) throw();

        TESTSUITE_PROTOTYPE(main)
    };

    namespace {
        FileContainerBinutilsImpl instance_of_FileContainerBinutilsImpl;
    }

        /* ���󥹥ȥ饯�� */
    FileContainerBinutilsImpl::FileContainerBinutilsImpl(void) throw()
        : symbol_prefix(""), symbol_table(), contents(), last_address(0), last_page(0)
    {}

        /* �ǥ��ȥ饯�� : �ǡ����Хåե��β��� */
    FileContainerBinutilsImpl::~FileContainerBinutilsImpl(void) throw()
    {
        map<address_t, char *>::iterator scope;

        scope = contents.begin();
        while(scope != contents.end()) {
            delete [] scope->second;
            ++ scope;
        }
        symbol_table.clear();
        contents.clear();
    }

        /* �ե�����̾�򥫥�ޤ���Ĥ�ʬ���� */
    void splitFilename(const string & src, string & first, string & second) throw(Exception)
    {
        if(!src.empty()) {
            string::size_type pos;

            pos = src.find_first_of(',');
            if(pos != string::npos) {
                first  = src.substr(0, pos);
                second = src.substr(pos + 1);
            }
            else {
                    //�ե�����̾����Ĥ������ꤵ��Ƥ��ʤ�
                first  = src;
                second = src;
            }
        }
        else
            ExceptionMessage("[FCBI] Empty filename could not be accepted.","[FCBI] �ե�����̾������ޤ���").throwException();
    }

        /* �ե����뤬�Х��ʥ�ǡ�������äƤ��뤫�ɤ�����Ƚ�� */
    bool hasBinaryContents(fstream & file) throw()
    {
        assert(file.is_open());

        bool        result = false;
        char        buffer[SIZE_TO_CONFIRM_BINARYFILE];
        streamsize  length;

        file.read(buffer, SIZE_TO_CONFIRM_BINARYFILE);
        length = file.gcount();

        for(streamsize i = 0; i < length; ++ i) {
            if(buffer[i] < 0 || !(_isprint(buffer[i]) || _isspace(buffer[i]))){
                result = true;
                break;
            }
        }

		if(!result) {
	        file.clear();
    	    file.seekg(0, ios::beg);    //��Ƭ���ᤷ�Ƥ���
		}

        return result;
    }

        /* �ƥ����ȥե�����򳫤� (�Х��ʥ���ä����ˤ��н�) */
    void openTextFile(fstream & file, const string & filename, FileContainerBinutilsImpl::interceptor_func_t * interceptor) throw(Exception)
    {
        assert(!filename.empty());
        assert(!file.is_open());

        file.open(filename.c_str(), ios::in|ios::binary);
        if(!file.is_open()) {
            ExceptionMessage("File '%' could not be opened.","�ե����� '%' �ϳ����ޤ���") << filename << throwException;
            return;
        }

            /* �Х��ʥ�ե�������ä���... */
        while(hasBinaryContents(file)) {
            file.close();
            
            if(interceptor != 0) {
                (*interceptor)(file, filename);
                interceptor = 0;    //�н�ϰ��Τ�
            }

            if(!file.is_open()) {
                break;
            }
        }

            /* �ե����뤬�����ʤ��ä����㳰 */
        if(!file.is_open())
            ExceptionMessage("Program failed to convert the binary '%' into suitable style. Please specify a suitable TEXT file.",
                            "�ץ����ϥХ��ʥ�ե�����'%'���Ѵ��˼��Ԥ��ޤ������������ƥ����ȥե��������ꤷľ���Ƥ���������")
                                << filename << throwException;
    }

        /* ���Ū�ʥե�����̾������ */
    const char * makeTemporaryFilename(void) throw()
    {
        static char filename[10];

        sprintf(filename, "cfg%06x", (int)(rand() & 0xffffffl));

        return filename;
    }


        /* �Х��ʥ��GNU-NM��Ȥä��Ѵ����� */
    void interceptWithGnuNM(fstream & file, const string & filename) throw(Exception)
    {
        assert(!file.is_open());

        string cmdline;
        string symfile;

        symfile.assign(makeTemporaryFilename());
        cmdline = string(CMD_GNUNM) + " " + filename + " > " + symfile;
        VerboseMessage("[EXEC] %\n") << cmdline;

		system(cmdline.c_str());

            /* ��������������ե�������� */
        file.open(symfile.c_str(), ios::in);
        if(file.is_open()) {
            remove(symfile.c_str());
        }
    }

        /* �Х��ʥ��GNU-OBJCOPY��Ȥä��Ѵ����� */
    void interceptWithGnuObjcopy(fstream & file, const string & filename) throw(Exception)
    {
        assert(!file.is_open());

        string cmdline;
        string srecfile;

        srecfile.assign(makeTemporaryFilename());
        cmdline = string(CMD_GNUOBJCOPY) + " -F srec " + filename + " " + srecfile;
        VerboseMessage("[EXEC] %\n") << cmdline;

		system(cmdline.c_str());

            /* ��������������ե�������� */
        file.open(srecfile.c_str(), ios::in);
        if(file.is_open()) {
            remove(srecfile.c_str());
        }
    }

        /* 16�ʤ���10�ʤؤ��Ѵ� (�ݥ��󥿰�ư, Ĺ�������դ�) */
    unsigned int hextodec(const char * & src, size_t length) throw()
    {
        assert(length <= sizeof(unsigned int) * 2);

        unsigned int result = 0;
        unsigned int digit;

        while(length-- > 0) {
            if(*src >= '0' && *src <= '9')
                digit = *src - '0';
            else if(*src >= 'A' && *src <='F')
                digit = *src - 'A' + 10;
            else if(*src >= 'a' && *src <='f')
                digit = *src - 'a' + 10;
            else
                break;

            ++ src;
            result = (result << 4) | (digit & 0xf);
        }

        return result;
    }

        /* NM�����Ϥ����Ԥ�ѡ��� */
    bool readGnuNmLine(fstream & file, FileContainer::address_t & address, string & attribute, string & symbolname) throw()
    {
        assert(file.is_open());

        string src;
        string addr;
        string::size_type pos1;
        string::size_type pos2;

            /* ��Ȥ���ˤ��Ƥ��� */
        address = 0;
        if(!attribute.empty())
            attribute.erase();
        if(!symbolname.empty())
            symbolname.erase();

            //���ιԤ���� (����, ̤�������ܥ���ɤ����Ф�)
        do {
            if(file.eof())
                return false;

            getline(file, src, '\n');
        } while(src.empty() || src.at(0) == ' ');

            //�Ԥ�ʬ��
        pos1 = src.find_first_of(' ');
        addr = src.substr(0, pos1);

        pos2 = src.find_first_of(' ', pos1 + 1);
        attribute  = src.substr(pos1 + 1, pos2 - pos1 - 1);
        symbolname = src.substr(pos2 + 1);

            //���ɥ쥹�Υѡ���  (�� : �ʤ�Ǥ���ʤ��ޤ��ޤ�äƤ뤫�Ȥ����ȡ����ɥ쥹��32bit��Ķ���륿�����åȤ����뤫��)
        while(!addr.empty()) {
            size_t length = addr.size();
            const char * src = addr.c_str();
            if(length > sizeof(unsigned int) * 2)
                length = sizeof(unsigned int) * 2;
            address = (address << (length * 2)) | (hextodec(src, length));
            addr.erase(0, length);
        }

        return true;
    }

        /* ����ܥ���ɤ߹��� */
    void FileContainerBinutilsImpl::loadSymbols(fstream & file) throw(Exception)
    {
        assert(file.is_open());

        address_t address;
        string    attribute;
        string    symbolname;

        while(readGnuNmLine(file, address, attribute, symbolname)) {
            symbol_table.insert(map<string, address_t>::value_type(symbolname, address));
        }

		VerboseMessage("% symbols loaded\n") << symbol_table.size() << &throwException;

        file.close();
    }

        /* contents��1�Х��Ƚ񤭹��� */
    void FileContainerBinutilsImpl::writeByte(address_t address, unsigned int value) throw(Exception)
    {
        address_t & base = last_address;
        char *    & page = last_page;

            /* ����å����ɤ����Ȥ��ʤ��ʤ顢�ڡ�����õ�� */
        if(MAKE_BASEADDRESS(address) != last_address || last_page == 0) {
            map<address_t, char *>::iterator scope;

            base  = MAKE_BASEADDRESS(address);
            scope = contents.find(base);
            if(scope == contents.end()) {
                page = new(nothrow) char [SIZE_LOADPAGE];
                if(page == 0) {
                    ExceptionMessage("Not enough memory available to store the contents","����������­�Τ��ᡢ�ǡ����γ�Ǽ�˼��Ԥ��ޤ���").throwException();
                    return;
                }
                contents.insert(map<address_t,char*>::value_type(base, page));
            }
            else
                page = scope->second;
        }

        *(page + (address - base)) = static_cast<char>(value & 0xff);
    }

        /* �����ζ���ʸ�����ڤ��� */
    void trimString(string & src) throw()
    {
        string::size_type pos;

        pos = src.find_last_not_of(" \t\r\n");
        if(pos != string::npos && pos != src.size())
            src.erase(pos + 1);
    }

        /* ��ȥ���S�쥳���ɤ����ɤ߹��� */
        /*
                The general format of an S-record follows: 
                +-------------------//------------------//-----------------------+
                | type | count | address  |            data           | checksum |
                +-------------------//------------------//-----------------------+
        */
    bool readRecord(fstream & file, string & dest) throw(Exception)
    {
        unsigned int sum;
        unsigned int count;
        unsigned int i;
        const char * pos;

            /* ���ιԤ��ɤ߹��� */
        do {
                //getline��ReadFile��Ƥ�ǥ֥�å�����Τǡ��μ¤�EOF��ȿ�������뤿��ˤ�������
            int ch = file.get();
            if(ch == EOF)
                return false;

            file.putback(static_cast<char>(ch));
            getline(file, dest);
        } while(dest.empty());

        trimString(dest);

            /* ��������Ƚ�� */

        if(dest[0] != 'S')      //��Ƭ��'S'�ǻϤޤ�ʤ�
            ExceptionMessage("The file is not a Motorola S-Record file.","��ȥ���S�ե����ޥåȤ�̵���Ԥ����Ĥ���ޤ���") << throwException;

        pos = dest.c_str() + 2;
        count = hextodec(pos, 2);
        if(dest.size() != (count + 2)*2)
            ExceptionMessage("Illegal S-Record found (count unmatched).","������S�쥳���ɤ�����ޤ� (�������԰���)") << throwException;

        sum = count;
        for(i = 0; i < count; ++ i)
            sum += hextodec(pos, 2);

        if((sum & 0xff) != 0xff)
            ExceptionMessage("Illegal S-Record found (check-sum unmatched).","������S�쥳���ɤ�����ޤ� (�����å������԰���)") << throwException;

        return true;
    }

        /* ���γ��ϥ��ɥ쥹������ */
    FileContainer::address_t parseRecordAddress(const string & src, FileContainer::address_t base) throw()
    {
        const char * record = src.c_str();
        FileContainer::address_t result = 0;

        record += 4;
        switch(*(record - 3)) {
            case '1':
                result = hextodec(record, 4);
                break;
            case '2':
                result = hextodec(record, 6);
                break;
            case '3':
                result = hextodec(record, 8);
                break;
            case '5':
                result = base;
                break;
            default:
                break;
        }

        return result;
    }

        /* �ǡ�����ʬ������Ĥ��ƥ���å� */
    void chopRecord(string & src) throw()
    {
        string::size_type start;

        switch(src[1]) {
            case '1':  start = 4 + 4;  break;
            case '2':  start = 4 + 6;  break;
            case '3':  start = 4 + 8;  break;
            default:   start = 4;      break;
        }

            //��Ƭ4�Х��� + ���ɥ쥹�� + �Ǹ�Υ���������
        src = src.substr(start, src.size() - start - 2);
    }

        /* �ץ����ǡ������ɤ߹��� */
    void FileContainerBinutilsImpl::loadDataContents(fstream & file) throw(Exception)
    {
        assert(file.is_open());

        address_t address;
        string    line;

        address = 0;
        while(readRecord(file, line)) {

            address = parseRecordAddress(line, address);

            chopRecord(line);

                /* �ǡ����γ�Ǽ */
            const char * pos = line.c_str();
            while(*pos != '\x0') {
                unsigned int data = hextodec(pos, 2);
                writeByte(address, data);
                ++ address;
            }
        }

        file.close();
    }

        /* ����ܥ�ץ�ե������μ�ưȽ�� */
    void FileContainerBinutilsImpl::searchSymbolPrefix(void) throw()
    {
        const char *  candidate_list[] = {"", "_", NULL};
        const char ** candidate;

        for(candidate = candidate_list; *candidate != NULL; ++ candidate) {
            map<string, address_t>::const_iterator scope;
            string symbol;
            
            symbol = string(*candidate) + MAGIC_SYMBOL;
            scope  = symbol_table.find(symbol);

            if(scope != symbol_table.end())
                break;
        }

        if(*candidate != NULL)
            symbol_prefix.assign(*candidate);
    }

        /* ����ǥ�����μ�ưȽ�� */
    void FileContainerBinutilsImpl::searchByteOrder(void) throw()
    {
        address_t address;
        union {
            char         buffer[4];
            unsigned int value;
        };

        try {
            value   = 0;
            address = getSymbolAddress(MAGIC_SYMBOL);
            loadContents(buffer, address, 4);

            if(value == MAGIC_NUMBER) {
                byteorder = HOSTORDER;
            }
            else {
                buffer[0] ^= buffer[3], buffer[3] ^= buffer[0], buffer[0] ^= buffer[3]; // swap(buffer[0], buffer[3])
                buffer[1] ^= buffer[2], buffer[2] ^= buffer[1], buffer[1] ^= buffer[2]; // swap(buffer[1], buffer[2])

                if(value == MAGIC_NUMBER)
                    byteorder = HOSTORDER == LITTLE ? BIG : LITTLE;
                else
                    throw false;
            }
        }
        catch(...) {}
    }

        /* �⥸�塼��Υ����å� -> ����ܥ��ɽФ�, �ǡ�����Ǽ */
    void FileContainerBinutilsImpl::attachModule(const string & filename) throw(Exception)
    {
        fstream file;
        string  symbol_filename;
        string  contents_filename;

        splitFilename(filename, symbol_filename, contents_filename);

        openTextFile(file, symbol_filename, interceptWithGnuNM);
        loadSymbols(file);

        openTextFile(file, contents_filename, interceptWithGnuObjcopy);
        loadDataContents(file);

        searchSymbolPrefix();
        searchByteOrder();
    }

        /* ��Ǽ���Ƥ������Ƥμ��� */
    void FileContainerBinutilsImpl::loadContents(void * _dest, address_t address, size_t size) throw(Exception)
    {
        char * dest = static_cast<char *>(_dest);

        while(size > 0) {
            map<address_t, char *>::const_iterator scope;

            address_t  base   = MAKE_BASEADDRESS(address);
            address_t  offset = MAKE_OFFSETADDRESS(address);
            size_t     transfer_size = size;

            if(transfer_size > SIZE_LOADPAGE - offset)
                transfer_size = SIZE_LOADPAGE - offset;

            scope = contents.find(base);
            if(scope == contents.end())
                ExceptionMessage("[Internel error] Memory read with unmapped address","[�������顼] �ޥåפ���Ƥʤ����ɥ쥹��Ȥäƥ���꡼�ɤ��Ԥ��ޤ���").throwException();

            memcpy(dest, scope->second + offset, transfer_size);

            dest += transfer_size;
            size -= transfer_size;
        }
    }

        /* ����ܥ�Υ��ɥ쥹�μ��� */
    FileContainer::address_t FileContainerBinutilsImpl::getSymbolAddress(const string & symbol) throw(Exception)
    {
        string symbolname;
        map<string, address_t>::const_iterator scope;

        symbolname = symbol_prefix + symbol;

        scope = symbol_table.find(symbolname);
        if(scope == symbol_table.end())
            ExceptionMessage("Unknown symbol '%'","�����ʥ���ܥ�̾ '%'") << symbol << throwException;

        return scope->second;
    }

        /* �������ƥ�����̾�μ��� */
    string FileContainerBinutilsImpl::getArchitecture(void) throw()
    {
        if(byteorder == LITTLE)
            return "Little endian target (with GNU/Binutils)";
        else
            return "Big endian target (with GNU/Binutils)";
    }

}

//---------------------------------------------

#ifdef TESTSUITE
#include "base/coverage_undefs.h"

namespace {
    fstream * interceptor_file;
    string    interceptor_filename;
    void interceptor(fstream & file, const string & filename)
    {
        CHECKPOINT("interceptor");
        interceptor_file = &file;
        interceptor_filename = filename;

        if(filename.compare("textfile") == 0) {
            remove(filename.c_str());
            file.open(filename.c_str(), ios::out);
            file << "text";
            file.close();

            file.open(filename.c_str(), ios::in|ios::binary);
        }
        else if(filename.compare("binaryfile") == 0) {
            remove(filename.c_str());
            file.open(filename.c_str(), ios::out|ios::binary);
            file.write("\x1",1);
            file.close();

            file.open(filename.c_str(), ios::in|ios::binary);
        }
    }
}

TESTSUITE(main, FileContainerBinutilsImpl)
{
    PREDECESSOR("TFileContainer");

    SingletonBase::ContextChain chain;
    chain.saveContext<RuntimeObjectTable>();

    BEGIN_CASE("splitFilename","splitFilename") {
        BEGIN_CASE("1","����ޤ�������ڤ��") {
            string first, second;
            
            splitFilename("a,b", first, second);
            TEST_CASE("1","first����Ȥ�������", first.compare("a") == 0);
            TEST_CASE("2","second����Ȥ�������", second.compare("b") == 0);
        } END_CASE;

        BEGIN_CASE("2","����ޤ�̵��������Ϳ����ȡ�ξ����Ʊ����Ȥ�����") {
            string first, second;

            splitFilename("abc", first, second);
            TEST_CASE("1","first����Ȥ�������", first.compare("abc") == 0);
            TEST_CASE("2","second����Ȥ�������", second.compare("abc") == 0);
        } END_CASE;

        BEGIN_CASE("3","��ʸ����Ϳ������㳰") {
            bool result = false;
            string first, second;
            try { splitFilename("", first, second); } catch(Exception &) { result = true; }
            if(!result)
                TEST_FAIL;
        } END_CASE;
    } END_CASE;

    BEGIN_CASE("hasBinaryContents","hasBinaryContents") {
        BEGIN_CASE("1","�ƥ����ȥե�����򿩤碌��") {
            fstream file("test", ios::out);
            file << "This is a sample text file.";
            file.close();

            file.open("test",ios::in|ios::binary);
            TEST_CASE("1","�ؿ���false���֤�", !hasBinaryContents(file));
            TEST_CASE("2","file��eof��ã���Ƥ��ʤ�", !file.eof());
            file.close();

            remove("test");
        } END_CASE;

        BEGIN_CASE("2","�Х��ʥ�ǡ����򿩤碌��") {
            fstream file("test", ios::out|ios::binary);
            file << "This is a sample text file.";
            file.write("\x0\x1\x2\x3", 4);
            file.close();

            file.open("test",ios::in|ios::binary);
            TEST_CASE("1","�ؿ���true���֤�", hasBinaryContents(file));
            TEST_CASE("2","file��eof��ã���Ƥ��ʤ�", !file.eof());
            file.close();

            remove("test");
        } END_CASE;
    } END_CASE;

    BEGIN_CASE("openTextFile","openTextFile") {
        BEGIN_CASE("1","�ƥ����ȥե��������ꤹ��") {
            TestSuite::clearCheckpoints();
            fstream file("test", ios::out);
            file << "This is a sample text file.";
            file.close();

            bool result = true;
            try { openTextFile(file, "test", interceptor); } catch(Exception &) { result = false; }

            TEST_CASE("1","�㳰�ϵ����ʤ�", result);
            TEST_CASE("2","�ե����뤬������Ƥ���", file.is_open());
            TEST_CASE("3","interceptor�ϥ����뤵��Ƥ��ʤ�", !TestSuite::isReached("interceptor"));

            string work;
            getline(file, work, '\n');
            TEST_CASE("4","�ɤ߽Ф��줿���Ƥ�������", work.compare("This is a sample text file.") == 0);

            file.close();
            remove("test");
        } END_CASE;

        BEGIN_CASE("2","�Х��ʥ�ե��������ꤹ�� (interceptor�ϥե�����򳫤��ʤ�)") {
            TestSuite::clearCheckpoints();
            fstream file("test", ios::out|ios::binary);
            file.write("\x1", 1);
            file.close();

            bool result = false;
            try { openTextFile(file, "test", interceptor); } catch(Exception &) { result = true; }

            TEST_CASE("1","�㳰��������", result);
            TEST_CASE("2","�ե����뤬������Ƥ���", !file.is_open());
            TEST_CASE("3","interceptor�������뤵��Ƥ���", TestSuite::isReached("interceptor"));
            TEST_CASE("4","interceptor�ΰ����������� (file)", interceptor_file == &file);
            TEST_CASE("5","interceptor�ΰ�����������", interceptor_filename.compare("test") == 0);

            file.close();
            remove("test");
        } END_CASE;

        BEGIN_CASE("3","¸�ߤ��ʤ��ե��������ꤹ��") {
            TestSuite::clearCheckpoints();
            fstream file;
            bool result = false;
            try { openTextFile(file, "___unknown___", interceptor); } catch(Exception &) { result = true; }

            TEST_CASE("1","�㳰��������", result);
            TEST_CASE("2","�ե����뤬������Ƥ��ʤ�", !file.is_open());
            TEST_CASE("3","interceptor�������뤵��Ƥ��ʤ�", !TestSuite::isReached("interceptor"));
        } END_CASE;

        BEGIN_CASE("4","interceptor���ƥ����ȥե��������������") {
            TestSuite::clearCheckpoints();
            fstream file("textfile", ios::out|ios::binary);
            file.write("\x1", 1);
            file.close();

            bool result = true;
            try { openTextFile(file, "textfile", interceptor); } catch(Exception &) { result = false; }

            TEST_CASE("1","�㳰�ϵ����ʤ�", result);
            TEST_CASE("2","�ե����뤬������Ƥ���", file.is_open());
            TEST_CASE("3","interceptor�������뤵��Ƥ���", TestSuite::isReached("interceptor"));
            TEST_CASE("4","interceptor�ΰ����������� (file)", interceptor_file == &file);
            TEST_CASE("5","interceptor�ΰ�����������", interceptor_filename.compare("textfile") == 0);

            string work;
            getline(file, work, '\n');
            TEST_CASE("4","�ɤ߽Ф��줿���Ƥ�������", work.compare("text") == 0);

            file.close();
            remove("textfile");
        } END_CASE;

        BEGIN_CASE("5","interceptor���Х��ʥ�ե��������������") {
            TestSuite::clearCheckpoints();
            fstream file("binaryfile", ios::out|ios::binary);
            file.write("\x1", 1);
            file.close();

            bool result = false;
            try { openTextFile(file, "binaryfile", interceptor); } catch(Exception &) { result = true; }

            TEST_CASE("1","�㳰�ϵ�����", result);
            TEST_CASE("2","�ե����뤬������Ƥ��ʤ�", !file.is_open());
            TEST_CASE("3","interceptor�������뤵��Ƥ���", TestSuite::isReached("interceptor"));
            TEST_CASE("4","interceptor�ΰ����������� (file)", interceptor_file == &file);
            TEST_CASE("5","interceptor�ΰ�����������", interceptor_filename.compare("binaryfile") == 0);

            file.close();
            remove("binaryfile");
        } END_CASE;
    } END_CASE;

    BEGIN_CASE("hextodec","hextodec") {
        const char * letter = "0123456789abcdEFg";
        const char * work = letter;

        TEST_CASE("1", "�ڤ�Ф��줿�ͤ�������", hextodec(work, 2) == 1);
        TEST_CASE("2", "work���ʤ�Ǥ���", work == letter + 2);
        TEST_CASE("3", "�ڤ�Ф��줿�ͤ�������", hextodec(work, 4) == 0x2345);
        TEST_CASE("4", "work���ʤ�Ǥ���", work == letter + 6);
        TEST_CASE("5", "�ڤ�Ф��줿�ͤ�������", hextodec(work, 8) == 0x6789abcd);
        TEST_CASE("6", "work���ʤ�Ǥ���", work == letter + 14);
        TEST_CASE("7", "�ڤ�Ф��줿�ͤ�������", hextodec(work, 8) == 0xef);
        TEST_CASE("8", "work��'g'�ΰ��֤ǤȤޤ�", *work == 'g');
        TEST_CASE("9", "�ڤ�Ф��줿�ͤ�������", hextodec(work, 8) == 0);
        TEST_CASE("10", "work��'g'�ΰ��֤ǤȤޤ�", *work == 'g');
    } END_CASE;

    BEGIN_CASE("readGnuNmLine","readGnuNmLine") {
        fstream file("test", ios::out);
        file << "0804aab0 T _kernel_task_initialize\n0805d8a0 B _kernel_tcb_table\n\n0804e560 R _kernel_tinib_table\n         U getpid@@GLIBC_2.0\n";
        file.close();

        address_t address;
        string    attribute;
        string    symbolname;

        file.open("test", ios::in);
        BEGIN_CASE("1","���̤Υ���ȥ꤬�ɤ��") {
            TEST_CASE("1","�ؿ�����������", readGnuNmLine(file, address, attribute, symbolname));
            TEST_CASE("2","address��������", address == 0x0804aab0);
            TEST_CASE("3","attribute��������", attribute.compare("T") == 0);
            TEST_CASE("4","symbolname��������", symbolname.compare("_kernel_task_initialize") == 0);
        } END_CASE;

        BEGIN_CASE("2","���̤Υ���ȥ꤬�ɤ�� (2)") {
            TEST_CASE("1","�ؿ�����������", readGnuNmLine(file, address, attribute, symbolname));
            TEST_CASE("2","address��������", address == 0x0805d8a0);
            TEST_CASE("3","attribute��������", attribute.compare("B") == 0);
            TEST_CASE("4","symbolname��������", symbolname.compare("_kernel_tcb_table") == 0);
        } END_CASE;

        BEGIN_CASE("3","���Ԥ��ɤ����Ф��Ƽ����ɤ��") {
            TEST_CASE("1","�ؿ�����������", readGnuNmLine(file, address, attribute, symbolname));
            TEST_CASE("2","address��������", address == 0x0804e560);
            TEST_CASE("3","attribute��������", attribute.compare("R") == 0);
            TEST_CASE("4","symbolname��������", symbolname.compare("_kernel_tinib_table") == 0);
        } END_CASE;

        BEGIN_CASE("4","���ɥ쥹��̵������ȥ��̵�뤹��") {
            TEST_CASE("1","�ؿ��ϼ��Ԥ���", !readGnuNmLine(file, address, attribute, symbolname));
        } END_CASE;

        file.close();
        remove("test");
    } END_CASE;

    BEGIN_CASE("loadSymbols","loadSymbols") {
        fstream file("test", ios::out);
        file << "0804aab0 T _kernel_task_initialize\n0805d8a0 B _kernel_tcb_table\n\n0804e560 R _kernel_tinib_table\n         U getpid@@GLIBC_2.0\n";
        file.close();

        file.open("test",ios::in);

        FileContainerBinutilsImpl fcbi;
        fcbi.loadSymbols(file);

        TEST_CASE("1","�ɤ߹��ޤ줿����ȥ�ο���������", fcbi.symbol_table.size() == 3);
        TEST_CASE("2","�ե�������Ĥ����Ƥ���", !file.is_open());

        remove("test");
    } END_CASE;

    BEGIN_CASE("writeByte","writeByte") {
        FileContainerBinutilsImpl fcbi;

        BEGIN_CASE("1","¸�ߤ��ʤ��ڡ����ؤν񤭹���") {
            TEST_CASE("0", "[����] contents�����ǿ���0", fcbi.contents.size() == 0);
            fcbi.writeByte(0x100, 0);

            TEST_CASE("1","contents�����Ǥ������Ƥ���", fcbi.contents.size() == 1);

            const char * scope = fcbi.contents.find(MAKE_BASEADDRESS(0x100))->second + MAKE_OFFSETADDRESS(0x100);
            TEST_CASE("2","�񤭹��ޤ�Ƥ������Ƥ�������", *scope == 0);
        } END_CASE;

        BEGIN_CASE("2","¸�ߤ���ڡ����ؤν񤭹��� (Ϣ³��������)") {
            fcbi.writeByte(0x100, 0xff);

            TEST_CASE("1","contents�����Ǥ������Ƥ��ʤ�", fcbi.contents.size() == 1);

            const char * scope = fcbi.contents.find(MAKE_BASEADDRESS(0x100))->second + MAKE_OFFSETADDRESS(0x100);
            TEST_CASE("2","�񤭹��ޤ�Ƥ������Ƥ�������", *scope == 0xff);
        } END_CASE;

        BEGIN_CASE("3","�������ڡ����ؤν񤭹���") {
            fcbi.writeByte(0x10000000, 0xff);

            TEST_CASE("1","contents�����Ǥ������Ƥ���", fcbi.contents.size() == 2);

            const char * scope = fcbi.contents.find(MAKE_BASEADDRESS(0x10000000))->second + MAKE_OFFSETADDRESS(0x10000000);
            TEST_CASE("2","�񤭹��ޤ�Ƥ������Ƥ�������", *scope == 0xff);
        } END_CASE;

        BEGIN_CASE("4","��¸�Υڡ����ؤΥ�������") {
            fcbi.writeByte(0x100, 0x0);

            TEST_CASE("1","contents�����Ǥ������Ƥ��ʤ�", fcbi.contents.size() == 2);

            const char * scope = fcbi.contents.find(MAKE_BASEADDRESS(0x100))->second + MAKE_OFFSETADDRESS(0x100);
            TEST_CASE("2","�񤭹��ޤ�Ƥ������Ƥ�������", *scope == 0x0);
        } END_CASE;
    } END_CASE;

    BEGIN_CASE("readRecord","readRecord") {
        fstream file("test",ios::out);
        file << "S315080480F42F6C69622F6C642D6C696E75782E736F98\n\nS315080480F42F6C69622F6C642D6C696E75782E736F98\nS308080481042E320005\nDUMMY\nS31808048108040000001000000001000000474E550056\nS31008048108040000001000000001000000474E550056\n";
        file.close();

        file.open("test",ios::in);
        BEGIN_CASE("1","���辰����") {
            string work;
            bool result;
            bool exception = false;
            try { result = readRecord(file, work); } catch(Exception &) { exception = true; }
            TEST_CASE("1","�㳰�ϵ�����ʤ�", !exception);
            TEST_CASE("2","�ؿ���true���֤�", result);
            TEST_CASE("3","�ɤ߽Ф��줿���Ƥ�������", work.compare("S315080480F42F6C69622F6C642D6C696E75782E736F98") == 0);
        } END_CASE;

        BEGIN_CASE("2","���辰���� (���Ԥ��ɤ����Ф�)") {
            string work;
            bool result;
            bool exception = false;
            try { result = readRecord(file, work); } catch(Exception &) { exception = true; }
            TEST_CASE("1","�㳰�ϵ�����ʤ�", !exception);
            TEST_CASE("2","�ؿ���true���֤�", result);
            TEST_CASE("3","�ɤ߽Ф��줿���Ƥ�������", work.compare("S315080480F42F6C69622F6C642D6C696E75782E736F98") == 0);
        } END_CASE;

        BEGIN_CASE("3","�����å����ब��äƤ��륨��ȥ�") {
            string work;
            bool result;
            bool exception = false;
            try { result = readRecord(file, work); } catch(Exception &) { exception = true; }
            TEST_CASE("1","�㳰�򤪤���", exception);
        } END_CASE;

        BEGIN_CASE("4","��Ƭ��S�ǻϤޤ�ʤ�����ȥ�") {
            string work;
            bool result;
            bool exception = false;
            try { result = readRecord(file, work); } catch(Exception &) { exception = true; }
            TEST_CASE("1","�㳰�򤪤���", exception);
        } END_CASE;

        BEGIN_CASE("5","���ꤵ�줿Ĺ������Ĺ������ȥ�") {
            string work;
            bool result;
            bool exception = false;
            try { result = readRecord(file, work); } catch(Exception &) { exception = true; }
            TEST_CASE("1","�㳰�򤪤���", exception);
        } END_CASE;

        BEGIN_CASE("6","���ꤵ�줿Ĺ������û������ȥ�") {
            string work;
            bool result;
            bool exception = false;
            try { result = readRecord(file, work); } catch(Exception &) { exception = true; }
            TEST_CASE("1","�㳰�򤪤���", exception);
        } END_CASE;

        BEGIN_CASE("7","�ե����뽪ü") {
            string work;
            bool result;
            bool exception = false;
            try { result = readRecord(file, work); } catch(Exception &) { exception = true; }
            TEST_CASE("1","�㳰�򤪤����ʤ�", !exception);
            TEST_CASE("2","�ؿ���false���֤�", !result);
        } END_CASE;

        remove("test");
    } END_CASE;

    BEGIN_CASE("chopRecord","chopRecord") {
        BEGIN_CASE("1","S1�쥳����") {
            string src("S106080480F42F4A");

            chopRecord(src);
            TEST_CASE("1","�ͤ�������", src.compare("80F42F") == 0);
        } END_CASE;

        BEGIN_CASE("2","S2�쥳����") {
            string src("S206080480F42F4A");

            chopRecord(src);
            TEST_CASE("1","�ͤ�������", src.compare("F42F") == 0);
        } END_CASE;

        BEGIN_CASE("3","S3�쥳����") {
            string src("S306080480F42F4A");

            chopRecord(src);
            TEST_CASE("1","�ͤ�������", src.compare("2F") == 0);
        } END_CASE;

        BEGIN_CASE("4","S4�쥳����") {
            string src("S406080480F42F4A");

            chopRecord(src);
            TEST_CASE("1","�ͤ�������", src.compare("080480F42F") == 0);
        } END_CASE;

        BEGIN_CASE("5","S5�쥳����") {
            string src("S506080480F42F4A");

            chopRecord(src);
            TEST_CASE("1","�ͤ�������", src.compare("080480F42F") == 0);
        } END_CASE;

    } END_CASE;

    BEGIN_CASE("loadDataContents/loadContents","loadDataContents/loadContents") {
        fstream file("test", ios::out);
        file << "S30D000000000123456789ABCDEF32\nS509FEDCBA9876543210BE";
        file.close();

        BEGIN_CASE("1","���辰����") {
            FileContainerBinutilsImpl fcbi;

            file.open("test",ios::in);
            bool exception = false;
            try { fcbi.loadDataContents(file); } catch(...) { exception = true; }

            TEST_CASE("1","�㳰�ϵ�����ʤ�", !exception);
            TEST_CASE("2","�ǡ��������ݤ���Ƥ���", fcbi.contents.size() == 1);
            TEST_CASE("3","�ե�������Ĥ����Ƥ���", !file.is_open());
            BEGIN_CASE("4","��Ǽ�����ͤ��������ɤ��") {
                unsigned int i;

                assert(sizeof(unsigned int) >= 4);
                i = 0;
                
                fcbi.loadContents(&i, 0, 4);
                TEST_CASE("1","1-4�Х�����", i == 0x67452301);
                fcbi.loadContents(&i, 4, 4);
                TEST_CASE("1","5-8�Х�����", i == 0xefcdab89);
                fcbi.loadContents(&i, 8, 4);
                TEST_CASE("1","9-12�Х�����", i == 0x98badcfe);
                fcbi.loadContents(&i,12, 4);
                TEST_CASE("1","13-16�Х�����", i == 0x10325476);
            } END_CASE;
        } END_CASE;
        remove("test");

        BEGIN_CASE("2","loadContents�ǰ��٤˥ڡ�����������Ķ�����̤��׵᤹��") {
            FileContainerBinutilsImpl fcbi;
            unsigned int i;

            for(i=0;i<SIZE_LOADPAGE*2;++i)
                fcbi.writeByte(i, i);

            unsigned char * buffer = new unsigned char [SIZE_LOADPAGE * 2];
            fcbi.loadContents(buffer, 0, SIZE_LOADPAGE * 2);

            for(i=0;i<SIZE_LOADPAGE*2;++i)
                if(*(buffer + i) != (i & 0xff))
                    TEST_FAIL;

            delete [] buffer;
        } END_CASE;

    } END_CASE;

    BEGIN_CASE("searchSymbolPrefix","searchSymbolPrefix") {

        BEGIN_CASE("1","�ץ�ե��������ʤ�") {
            FileContainerBinutilsImpl fcbi;
            fcbi.symbol_table.insert(pair<string, address_t>(MAGIC_SYMBOL, 0x100));

            fcbi.searchSymbolPrefix();
            if(!fcbi.symbol_prefix.empty())
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("2","�ѿ�̾��\"_\"���Ĥ�������") {
            FileContainerBinutilsImpl fcbi;
            fcbi.symbol_table.insert(pair<string, address_t>("_" MAGIC_SYMBOL, 0x100));

            fcbi.searchSymbolPrefix();
            if(fcbi.symbol_prefix.compare("_") != 0)
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("3","\"__\"�ˤ�ȿ�����ʤ�") {
            FileContainerBinutilsImpl fcbi;
            fcbi.symbol_table.insert(pair<string, address_t>("__" MAGIC_SYMBOL, 0x100));

            fcbi.searchSymbolPrefix();
            if(!fcbi.symbol_prefix.empty())
                TEST_FAIL;
        } END_CASE;
            
        BEGIN_CASE("4","ȯ���Ǥ��ʤ���硢�ѹ����ʤ�") {
            FileContainerBinutilsImpl fcbi;
            fcbi.symbol_prefix.assign("test");

            fcbi.searchSymbolPrefix();
            if(fcbi.symbol_prefix.compare("test") != 0)
                TEST_FAIL;
        } END_CASE;
    } END_CASE;

    BEGIN_CASE("searchByteOrder","searchByteOrder") {
        BEGIN_CASE("1","�ۥ��Ȥ�Ʊ������ǥ�����") {
            FileContainerBinutilsImpl fcbi;
            unsigned int value = MAGIC_NUMBER;
            fcbi.symbol_table.insert(pair<string, address_t>(MAGIC_SYMBOL, 0x100));

            for(int i=0;i<4;i++)
                fcbi.writeByte(0x100 + i, *((char *)&value + i));

            fcbi.byteorder = UNKNOWN;
            fcbi.searchByteOrder();

            if(fcbi.byteorder != HOSTORDER)
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("2","�ۥ��ȤȰ㤦����ǥ�����") {
            FileContainerBinutilsImpl fcbi;
            unsigned int value = MAGIC_NUMBER;
            fcbi.symbol_table.insert(pair<string, address_t>(MAGIC_SYMBOL, 0x100));

            for(int i=0;i<4;i++)
                fcbi.writeByte(0x100 + i, *((char *)&value + (3 - i)));

            fcbi.byteorder = UNKNOWN;
            fcbi.searchByteOrder();

            if(fcbi.byteorder == HOSTORDER)
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("3","����ܥ뤬̵��") {
            FileContainerBinutilsImpl fcbi;
            unsigned int value = MAGIC_NUMBER;

            for(int i=0;i<4;i++)
                fcbi.writeByte(0x100 + i, *((char *)&value + (3 - i)));

            fcbi.byteorder = UNKNOWN;
            fcbi.searchByteOrder();

            if(fcbi.byteorder != UNKNOWN)
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("4","�ǡ�����̵��") {
            FileContainerBinutilsImpl fcbi;
            unsigned int value = MAGIC_NUMBER;
            fcbi.symbol_table.insert(pair<string, address_t>(MAGIC_SYMBOL, 0x100));

            fcbi.byteorder = UNKNOWN;
            fcbi.searchByteOrder();

            if(fcbi.byteorder != UNKNOWN)
                TEST_FAIL;
        } END_CASE;
    } END_CASE;

    chain.restoreContext();
}

#endif /* TESTSUITE */

#endif /* FILECONTAINER_BINUTILS || TESTSUITE */

