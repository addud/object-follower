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
 *  @(#) $Id: mpstrstream.cpp,v 1.9 2003/12/15 07:32:13 takayuki Exp $
 */

// $Header: /home/CVS/configurator/base/mpstrstream.cpp,v 1.9 2003/12/15 07:32:13 takayuki Exp $

#include "base/mpstrstream.h"

using namespace std;

/*
 *   ʣ�����̤���ʤ륹�ȥ꡼��ΰ����̤��������륯�饹
 */

    //���󥹥ȥ饯��
MultipartStream::Part::Part(string _name) throw() : name(_name)
{}

    //���ԡ����󥹥ȥ饯��
MultipartStream::Part::Part(const MultipartStream::Part & src) throw() : name("")
{
    if(src.isValid()) {
        name.assign(src.name);
        setContents(src.getContents());
    }
}

    //���ȥ꡼��˽񤤤����Ƥ�������
string MultipartStream::Part::getContents(void) const throw(Exception)
{
    string result;

    if(isValid())
        result = stream.str();
    else
        ExceptionMessage("Operation was performed against an invalid stream.","̵���ʥ��ȥ꡼����Ф������Ԥ��ޤ���").throwException();

    return result;
}

    //���ȥ꡼������Ƥ�ľ�����ꤹ��
void MultipartStream::Part::setContents(string contents) throw(Exception)
{
    if(isValid()) {
        stream.clear();
        stream << contents;
    }
    else
        ExceptionMessage("Operation was performed against an invalid stream.","̵���ʥ��ȥ꡼����Ф������Ԥ��ޤ���").throwException();
}



/*
 *   ʣ�����̤���ʤ륹�ȥ꡼��ΰ����̤��������륯�饹
 */

    //���󥹥ȥ饯��
MultipartStream::MultipartStream(string _filename) throw() : filename(_filename), current(0), dirty(false), output(true)
{
    dirty = isValid();  //���Ǥ��äƤ�ե��������ʤ��Ȥ����ʤ��Τ�...   
}

MultipartStream::~MultipartStream(void) throw()
{
    if(isValid() && dirty) {
            //��
        try { serialize(); }
        catch(...) {}
    }
}

    //�ե�����̾�δ�Ϣ�դ�
string MultipartStream::setFilename(string _filename) throw(Exception)
{
    string result;

    if(this != 0) {
        if(!_filename.empty()) {
            result   = filename;
            filename = _filename;
            dirty    = isValid();
        }
        else
            ExceptionMessage("Empty filename should not be allowed.","���Υե�����̾�ϻ��ѤǤ��ʤ�").throwException();
    }
    else
        ExceptionMessage("Invalid object can not perform the request.","̵���ʥ��֥������Ȥ��Ф����׵�ϼ¹ԤǤ��ʤ�").throwException();

    return result;
}

    //�ե�������� (�����˥ե�����˽��Ϥ����Ȥ�����true)
bool MultipartStream::serialize(void) throw(Exception)
{
    bool result = false;

    if(isValid() && dirty && output) {

        fstream file(filename.c_str(), ios::out);
        if(file.is_open()) {
            list<Part>::iterator scope;

                //���Ƥ����̤����Ƥ����
            scope = parts.begin();
            while(scope != parts.end()) {
                file << scope->getContents();
                ++ scope;
            }

            file.close();
            dirty  = false;
            result = true;
        }
        else {
            ExceptionMessage("File could not open [%]","�ե����뤬�����ʤ� [%]") << filename << throwException;
            disableOutput();    //�ǥ��ȥ饯�����⤦����ĩ�魯��Τ�
        }
    }
    else {
        if(!isValid())
            ExceptionMessage("Invalid object can not perform the request.","̵���ʥ��֥������Ȥ��Ф����׵�ϼ¹ԤǤ��ʤ�").throwException();
    }

    return result;
}

    //���̤κ���
MultipartStream & MultipartStream::createPart(string name, bool precedence) throw(Exception)
{
    if(this != 0) {
        list<Part>::iterator scope;
        list<Part>::iterator newnode;

            //Ʊ��̾�����ʤ����Ȥ��ǧ
        scope = parts.begin();
        while(scope != parts.end()) {
            if(scope->getName().compare(name) == 0) {
                ExceptionMessage("The part \"%\" is already created.","����̾[%]�Ϥ��Ǥ����Ѥ���Ƥ���") << name << throwException;
                break;
            }
            ++ scope;
        }

            //Ʊ��̾�����ʤ��ʤ����Ǥ��ɲ�
        if(scope == parts.end()) {
            
                //�������֤θ���
            if(current != 0) {
                scope = parts.begin();
                while(scope != parts.end() && &(*scope) != current)
                    ++ scope;

                    //�������֤�Ĵ�� (���߰��֤���ˤ��餹 when precedence = false; )
                if(scope != parts.end() && !precedence)
                    ++ scope;
            }
            else
                scope = parts.end();

                //���Ǥ�����
            newnode = parts.insert(scope, Part(name));
            current = &(*newnode);
        }
    }else
        ExceptionMessage("Invalid object can not perform the request.","̵���ʥ��֥������Ȥ��Ф����׵�ϼ¹ԤǤ��ʤ�").throwException();

    return *this;
}

    //���̤�����
MultipartStream & MultipartStream::movePart(string name) throw(Exception)
{
    list<Part>::iterator scope;

    if(this != 0 && !name.empty()) {

            //̾�������פ����Τ�õ��
        scope = parts.begin();
        while(scope != parts.end()) {
            if(scope->getName() == name) {
                current = &(*scope);
                break;
            }
            ++ scope;
        }

            //���Ĥ���ʤ��ä�
        if(scope == parts.end())
            ExceptionMessage("Unknown part [%] specified.","̵���ʼ���̾ [%]") << name << throwException;
    }
    else{
        if(this == 0)
            ExceptionMessage("Invalid object can not perform the request.","̵���ʥ��֥������Ȥ��Ф����׵�ϼ¹ԤǤ��ʤ�").throwException();
        else //if(name.empty()) //������if�ξ���ꡢ����if�Ͼ�˿�
            ExceptionMessage("Empty identifier was passed as a name of part.","��ʸ�����Ϥ��줿").throwException();
    }

    return *this;
}


/********************************** �ƥ��ȥ������� **********************************/

#ifdef TESTSUITE

#include "coverage_undefs.h"

#include <iomanip>
#include <cstdio>

#ifdef _MSC_VER
#  pragma warning(disable:4101)   //�������ѿ��ϰ��٤�Ȥ��Ƥ��ޤ���
#endif

TESTSUITE_(main,Part, MultipartStream)
{
    BEGIN_CASE("constructor/isValid","���󥹥ȥ饯�� / ������Ƚ��") {
        BEGIN_CASE("1","̾���Ĥ��Ǻ���������ͭ���ʥѡ��Ȥ�����") {
            Part part("test");
            if(!part.isValid())
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("2","̾���ʤ��Ǻ���������̵���ʥѡ��Ȥˤʤ�") {
            Part part("");
            if(part.isValid())
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("3","NULL��̵���ʥѡ���") {
            if(((Part *)0)->isValid())
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("4","NULL���֥������Ȥǥ��ԡ����󥹥ȥ饯����ư���Ƥ⼺�Ԥ��ʤ�") {
            Part * part = 0;
            Part work(*part);
        } END_CASE;

    } END_CASE;

    BEGIN_CASE("operator <<","operator <<") {
        BEGIN_CASE("1", "���ϤǤ���") {
            Part part("test");

            part << "test";

            if(part.stream.str().compare("test") != 0)
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("2", "iomanip���Ȥ���") {
            Part part("test");

            part << setw(8) << setbase(16) << setfill('0') << 0x1234567;

            if(part.stream.str().compare("01234567") != 0)
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("3", "̵���ʥ��ȥ꡼��˽񤤤����㳰������") {
            Part part("");
            bool result = false;

            if(part.isValid())
                TEST_FAIL;

            Exception::setThrowControl(true);
            try {
                Message::selectLanguage(Message::NEUTRAL);
                part << setw(8) << setbase(16) << setfill('0') << 0x1234567;
            }
            catch(Exception & e) {
                if(e.getDetails().compare("Operation was performed against an invalid stream.") == 0)
                    result = true;
            }
            if(!result)
                TEST_FAIL;
        } END_CASE;
    } END_CASE;

    BEGIN_CASE("getContents","getContents") {
        BEGIN_CASE("1", "�񤤤����Ƥ������Ǥ���") {
            Part part("test");

            part << "test";

            if(part.getContents().compare("test") != 0)
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("2", "�񤤤��ɤ�Ǥޤ��񤤤��ɤ��") {
            Part part("test");

            part << "abc";
            if(part.getContents().compare("abc") != 0)
                TEST_FAIL;

            part << "def";
            if(part.getContents().compare("abcdef") != 0)
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("3", "̵���ʥ��ȥ꡼�फ���ɤ�����㳰������") {
            Part part("");
            bool result = false;

            if(part.isValid())
                TEST_FAIL;

            Exception::setThrowControl(true);
            try {
                string work = part.getContents();
            }
            catch(Exception & e) {
                if(e.getDetails().compare("Operation was performed against an invalid stream.") == 0)
                    result = true;
            }
            if(!result)
                TEST_FAIL;
        } END_CASE;
    } END_CASE;

    BEGIN_CASE("setContents","setContents") {
        BEGIN_CASE("1", "���ꤷ�����Ƥ������Ǥ���") {
            Part part("test");

            part.setContents("test");

            if(part.getContents().compare("test") != 0)
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("2", "setContents�����ꤷ�����Ȥ��ɵ��Ǥ���") {
            Part part("test");

            part.setContents("abc");
            part << "def";
            if(part.getContents().compare("abcdef") != 0)
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("3", "̵���ʥ��ȥ꡼������ꤷ�����㳰������") {
            Part part("");
            bool result = false;

            if(part.isValid())
                TEST_FAIL;

            Exception::setThrowControl(true);
            try {
                part.setContents("test");
            }
            catch(Exception & e) {
                if(e.getDetails().compare("Operation was performed against an invalid stream.") == 0)
                    result = true;
            }
            if(!result)
                TEST_FAIL;
        } END_CASE;
    } END_CASE;

    BEGIN_CASE("getName","getName") {
        BEGIN_CASE("1", "�ѡ���̾�������������Ǥ���") {
            Part part("name_of_stream");

            if(part.getName().compare("name_of_stream") != 0)
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("2", "�����ʥѡ��Ȥ�̾��������㳰������") {
            Part part("");
            bool result = false;

            Exception::setThrowControl(true);
            try { string work = part.getName(); }
            catch(Exception & e) {
                if(e.getDetails().compare("Operation was performed against an invalid stream.") == 0)
                    result = true;
            }
            if(!result)
                TEST_FAIL;
        } END_CASE;
    } END_CASE;

    BEGIN_CASE("CopyConstructor","���ԡ����󥹥ȥ饯��") {
        Part source("test");
        source << "abcdefg";

        Part dest(source);
        BEGIN_CASE("1","���ȥ꡼������Ƥ����������ԡ��Ǥ��Ƥ���") {
            if(dest.getContents().compare("abcdefg") != 0)
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("2","����̾�����������ԡ��Ǥ��Ƥ���") {
            if(dest.getName() != source.getName())
                TEST_FAIL;
        } END_CASE;
    } END_CASE;
}

TESTSUITE(main,MultipartStream)
{
    BEGIN_CASE("constructor/isValid","constructor/isValid") {
        BEGIN_CASE("1","�ե�����̾����ꤷ�������������֥������Ȥ�ͭ��") {
            MultipartStream mps("test.dat");

            if(!mps.isValid())
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("2","�ե�����̾������ʤ����֥������Ȥ�̵��") {
            MultipartStream mps;

            if(mps.isValid())
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("3","���Υե�����̾����ĥ��֥������Ȥ�̵��") {
            MultipartStream mps("");

            if(mps.isValid())
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("4","NULL���֥������Ȥ�̵��") {
            if(((MultipartStream *)0)->isValid())
                TEST_FAIL;
        } END_CASE;
    } END_CASE;

    BEGIN_CASE("setFilename","setFilename") {
        BEGIN_CASE("1","�ե�����̾����ꤻ�������������ե������̾����Ĥ���") {
            MultipartStream mps;
            if(mps.isValid())
                TEST_FAIL;

            BEGIN_CASE("1","���ȥ꡼���ͭ���ˤʤ�") {
                mps.setFilename("test");
                if(!mps.isValid())
                    TEST_FAIL;
            } END_CASE;

            BEGIN_CASE("2","���ȥ꡼���̾�����ѹ�����Ƥ���") {
                if(mps.filename.compare("test") != 0)
                    TEST_FAIL;
            } END_CASE;
        } END_CASE;

        BEGIN_CASE("2","�ե�����̾����ꤷ�����������ե������̾����Ĥ���") {
            MultipartStream mps("initialname");
            if(!mps.isValid())
                TEST_FAIL;

            BEGIN_CASE("1","���ȥ꡼���ͭ���ˤʤ�") {
                mps.setFilename("test");
                if(!mps.isValid())
                    TEST_FAIL;
            } END_CASE;

            BEGIN_CASE("2","���ȥ꡼���̾�����ѹ�����Ƥ���") {
                if(mps.filename.compare("test") != 0)
                    TEST_FAIL;
            } END_CASE;
        } END_CASE;

        BEGIN_CASE("3","��ʸ�����Ϥ����㳰") {
            MultipartStream mps;
            bool result = false;

            Exception::setThrowControl(true);
            try { mps.setFilename(""); }
            catch(Exception & e)
            {   result = true;   }
            if(!result)
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("4","NULL���֥������Ȥ�̾����Ĥ�����㳰") {
            bool result = false;

            Exception::setThrowControl(true);
            try { ((MultipartStream *)0)->setFilename("test"); }
            catch(Exception & e)
            {   result = true;   }
            if(!result)
                TEST_FAIL;
        } END_CASE;
    } END_CASE;

    BEGIN_CASE("serialize","serialize") {

        BEGIN_CASE("1", "NULL���֥������Ȥ��Ф��륷�ꥢ�饤�����㳰") {
            bool result = false;

            Exception::setThrowControl(true);
            try 
            {   ((MultipartStream *)0)->serialize();   }
            catch(Exception & e)
            {   result = true;   }

            if(!result)
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("2", "̵���ʥ��֥������Ȥ��Ф��륷�ꥢ�饤�����㳰") {
            bool result = false;
            MultipartStream mps;

            Exception::setThrowControl(true);
            try
            {   mps.serialize();   }
            catch(Exception & e)
            {   result = true;   }

            if(!result)
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("3", "����˥��ꥢ�饤���Ǥ���") {
            MultipartStream mps("debug.out");
            Part part("abc");

            part << "abcdefg";
            mps.parts.push_back(part);
            mps.dirty = true;

            ::remove("debug.out");
            BEGIN_CASE("1", "���ꥢ�饤����true���֤�") {
                if(!mps.serialize())
                    TEST_FAIL;
            } END_CASE;

            BEGIN_CASE("2", "���Ϥ����ե���������Ƥ�������") {
                if(!TestSuite::compareFileContents("debug.out","abcdefg"))
                    TEST_FAIL;
            } END_CASE;
            
        } END_CASE;

        BEGIN_CASE("4", "���Ƥ����äƤ�dirty=false�ʤ���Ϥ���ʤ�") {
            MultipartStream mps("debug.out");
            Part part("abc");

            part << "abcdefg";
            mps.parts.push_back(part);
            mps.dirty = false;

            ::remove("debug.out");
            BEGIN_CASE("1", "���ꥢ�饤����false���֤�") {
                if(mps.serialize())
                    TEST_FAIL;
            } END_CASE;

            BEGIN_CASE("2", "�ե�����Ͻ��Ϥ���Ƥ��ʤ�") {
                fstream file("debug.out",ios::in);
                if(file.is_open())
                    TEST_FAIL;
            } END_CASE;
        } END_CASE;

        BEGIN_CASE("5", "���Ƥ����äƤ���϶ػߤʤ���Ϥ���ʤ�") {
            MultipartStream mps("debug.out");
            Part part("abc");

            part << "abcdefg";
            mps.parts.push_back(part);
            mps.dirty = true;

            mps.disableOutput();

            ::remove("debug.out");
            BEGIN_CASE("1", "���ꥢ�饤����false���֤�") {
                if(mps.serialize())
                    TEST_FAIL;
            } END_CASE;

            BEGIN_CASE("2", "�ե�����Ͻ��Ϥ���Ƥ��ʤ�") {
                fstream file("debug.out",ios::in);
                if(file.is_open())
                    TEST_FAIL;
            } END_CASE;
        } END_CASE;
    } END_CASE;

    BEGIN_CASE("Destructor","Destructor") {
        BEGIN_CASE("1","��äƲ���") {
            MultipartStream mps("debug.out");
            Part part("abc");

            part << "abcdefg";
            mps.parts.push_back(part);
            mps.dirty = true;

            ::remove("debug.out");
        } END_CASE;

        BEGIN_CASE("2","���Ƥ��ե�����˳�Ǽ����Ƥ���") {
            if(!TestSuite::compareFileContents("debug.out","abcdefg"))
                TEST_FAIL;
        } END_CASE;
    } END_CASE;

    BEGIN_CASE("createPart","createPart") {
        BEGIN_CASE("1","�ѡ��Ȥ���Ͽ����") {
            MultipartStream mps("debug.out");
            mps.disableOutput();

            BEGIN_CASE("1","�㳰�ʤ���Ͽ�Ǥ���") {
                Exception::setThrowControl(true);
                mps .createPart("abc")
                    .createPart("def")
                    .createPart("ghi");
            } END_CASE;

            BEGIN_CASE("2","��Ȥ���Ͽ����¤�Ǥ���") {
                list<Part>::iterator scope;
                scope = mps.parts.begin();
                if(scope->getName().compare("abc") != 0)
                    TEST_FAIL;
                ++ scope;
                if(scope->getName().compare("def") != 0)
                    TEST_FAIL;
                ++ scope;
                if(scope->getName().compare("ghi") != 0)
                    TEST_FAIL;
                ++ scope;
                if(scope != mps.parts.end())
                    TEST_FAIL;
            } END_CASE;

        } END_CASE;

        BEGIN_CASE("2","�ѡ��Ȥ�ս����Ͽ����") {
            MultipartStream mps("debug.out");
            mps.disableOutput();

            BEGIN_CASE("1","�㳰�ʤ���Ͽ�Ǥ���") {
                Exception::setThrowControl(true);
                mps .createPart("abc",true)
                    .createPart("def",true)
                    .createPart("ghi",true);
            } END_CASE;

            BEGIN_CASE("2","��Ȥ���Ͽ�����ս���¤�Ǥ���") {
                list<Part>::iterator scope;
                scope = mps.parts.begin();
                if(scope->getName().compare("ghi") != 0)
                    TEST_FAIL;
                ++ scope;
                if(scope->getName().compare("def") != 0)
                    TEST_FAIL;
                ++ scope;
                if(scope->getName().compare("abc") != 0)
                    TEST_FAIL;
                ++ scope;
                if(scope != mps.parts.end())
                    TEST_FAIL;
            } END_CASE;

        } END_CASE;

        BEGIN_CASE("3","NULL���Ф��������㳰��ȯ������") {
            bool result = false;
            Exception::setThrowControl(true);
            try {
                ((MultipartStream *)0)->createPart("test");
            }
            catch(...)
            {   result = true;   }
            if(!result)
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("4","Ʊ��̾���Υѡ��Ȥ�����㳰������") {
            BEGIN_CASE("1","Ʊ��̾���Υѡ��Ȥ�����㳰������") {
                bool result = false;
                MultipartStream mps("debug.out");
                Exception::setThrowControl(true);

                try {
                    mps .createPart("abc")
                        .createPart("def")
                        .createPart("abc");
                }
                catch(...)
                {   result = true;   }

                if(!result)
                    TEST_FAIL;
            } END_CASE;

            BEGIN_CASE("2","�㳰�������Ƥ�������ư��") {
                bool result = true;
                MultipartStream mps("debug.out");
                Exception::setThrowControl(false);

                BEGIN_CASE("1","�㳰�ϥ�������ʤ�") {
                try {
                        mps .createPart("abc")
                            .createPart("def")
                            .createPart("abc");
                    }
                    catch(...)
                    {   result = false;   }

                    if(!result)
                        TEST_FAIL;
                } END_CASE;

                BEGIN_CASE("2","���߰��֤��Ѳ����ʤ�") {
                    if(mps.current == 0 || mps.current->getName().compare("def") != 0)
                        TEST_FAIL;
                } END_CASE;
            } END_CASE;
        } END_CASE;

        Exception::setThrowControl(true);

        BEGIN_CASE("5","��Ͽ����ȸ��߰��֤��Ѳ�����") {
            MultipartStream mps("debug.out");
            mps.disableOutput();

            BEGIN_CASE("1","��Ͽ����Ȱ��֤��Ѳ����� (1)") {
                mps.createPart("abc");
                if(mps.current == 0 || mps.current->getName().compare("abc") != 0)
                    TEST_FAIL;
            } END_CASE;

            BEGIN_CASE("2","��Ͽ����Ȱ��֤��Ѳ����� (2)") {
                mps.createPart("def");
                if(mps.current == 0 || mps.current->getName().compare("def") != 0)
                    TEST_FAIL;
            } END_CASE;

            BEGIN_CASE("3","��Ͽ����Ȱ��֤��Ѳ����� (3)") {
                mps.createPart("ghi");
                if(mps.current == 0 || mps.current->getName().compare("ghi") != 0)
                    TEST_FAIL;
            } END_CASE;
        } END_CASE;
    } END_CASE;

    BEGIN_CASE("opeator <<","operator <<") {

        BEGIN_CASE("1","operator <<���Ȥ���") {
            MultipartStream mps("debug.out");

            mps.createPart("test");

            mps << "abcdefghijklmn";
        } END_CASE;

        BEGIN_CASE("2","���Ϥ��줿��Ȥ�������") {
            if(!TestSuite::compareFileContents("debug.out","abcdefghijklmn"))
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("3","NULL���֥������Ȥ˽��Ϥ�����㳰") {
            bool result = false;
            Exception::setThrowControl(true);
            try {
                *((MultipartStream *)0) << "test";
            }
            catch(...)
            {   result = true;   }
            if(!result)
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("4","�ѡ��Ȥ�������äƤ��ʤ����֥������Ȥ˽��Ϥ�����㳰") {
            bool result = false;
            Exception::setThrowControl(true);
            try {
                MultipartStream mps("debug.out");
                mps.disableOutput();
                *((MultipartStream *)0) << "test";
            }
            catch(...)
            {   result = true;   }
            if(!result)
                TEST_FAIL;
        } END_CASE;

    } END_CASE;

    BEGIN_CASE("movePart/operator []","movePart/operator []") {
        BEGIN_CASE("1","���̤˰�ư����") {
            MultipartStream mps("debug.out");
            mps.disableOutput();

            mps .createPart("abc")
                .createPart("def")
                .createPart("ghi");

            BEGIN_CASE("1","��ư�Ǥ���") {
                mps.movePart("def");

                if(mps.current->getName().compare("def") != 0)
                    TEST_FAIL;
            } END_CASE;

            BEGIN_CASE("2","̵����̾�����������㳰") {
                bool result = false;
                Exception::setThrowControl(true);

                try {
                    mps.movePart("unknwon");
                }
                catch(...)
                {   result = true;   }
                if(!result)
                    TEST_FAIL;
            } END_CASE;

            BEGIN_CASE("3","��ʸ�����������㳰") {
                bool result = false;
                Exception::setThrowControl(true);

                try {
                    mps.movePart("");
                }
                catch(...)
                {   result = true;   }
                if(!result)
                    TEST_FAIL;
            } END_CASE;
        } END_CASE;

        BEGIN_CASE("2", "NULL���֥�����������������㳰") {
            bool result = false;
            Exception::setThrowControl(true);

            try {
                ((MultipartStream *)0)->movePart("");
            }
            catch(...)
            {   result = true;   }
            if(!result)
                TEST_FAIL;
        } END_CASE;
    } END_CASE;
}


#endif




