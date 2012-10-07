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
 *  @(#) $Id: message.cpp,v 1.4 2003/12/15 07:32:13 takayuki Exp $
 */

// $Header: /home/CVS/configurator/base/message.cpp,v 1.4 2003/12/15 07:32:13 takayuki Exp $

#include "base/message.h"

using namespace std;


/*****************************************************************************/

/*
 *   ��å�����������ʸ���������إ�ѡ����饹
 */

    //�ǥե���ȥ��󥹥ȥ饯��
Formatter::Formatter(void) throw() : templatestring(""), accept(false)
{}

    //���󥹥ȥ饯��
Formatter::Formatter(string src) throw() : templatestring(src)
{   shift();   }

    //���ԡ����󥹥ȥ饯��
Formatter::Formatter(const Formatter & src) throw() : templatestring(src.templatestring), accept(src.accept)
{
    string work;

    work = src.content.str();
    content << work;
}

    //���ΰ�����������ؤȰ�ư
void Formatter::shift(void) throw()
{
    string::size_type pos;

    accept = false;
    if(!templatestring.empty()) {

        do {
            pos = templatestring.find_first_of("%");

            if(pos != string::npos) {

                    /* %�����äƤ��줬\%�Ȥ������ʤ顢%�򤽤Τޤ޽Ф� */
                if(pos != string::npos && pos != 0 && templatestring.at(pos - 1) == '\\') {

                    if(pos > 1)
                        content << templatestring.substr(0, pos - 2);
                    content << '%';

                    templatestring = templatestring.substr(pos + 1);

                    continue;
                }
                else {
                        /* %���ޤ����� */
                    if(pos != string::npos)
                        accept = true;
                    break;
                }
            }
        } while(pos != string::npos);

        if(pos != string::npos) {
            if(pos != 0)
                content << templatestring.substr(0, pos);
            templatestring = templatestring.substr(pos + 1);
        }
        else {
            content << templatestring;
            templatestring.erase();
        }
    }
}


    //̤����ΰ����� (null) ���ִ�
void Formatter::shift_all(void) throw()
{
    while(accept)
        *this << "(null)";
}

    //������å������μ��Ф�
string Formatter::str(void) throw()
{
    shift_all();
    return content.str();
}

    //�ƥ�ץ졼��ʸ��������� (��ȤϾä���)
void Formatter::assign(string src) throw()
{
    clear();
    templatestring.assign(src);
    shift();
}

    //���Ƥξõ�
void Formatter::clear(void) throw()
{
    if(!templatestring.empty())
        templatestring.erase();
    content.str(string(""));
    accept = false;
}

    //�����黻��
Formatter & Formatter::operator =(const Formatter & src) throw()
{
    string work;

    templatestring = src.templatestring;
    accept         = src.accept;

    work = src.content.str();
    content << work;

    return *this;
}


/*****************************************************************************/

/*
 *   ��å�����������ʸ���������إ�ѡ����饹
 */

const char * Message::MessageControl::select(const char * msg1, const char * msg2, va_list vl) throw()
{
    const char * msg = msg1;
    int i = language;

    if(i > 0) {
        msg = msg2;

        while(--i > 0)
            msg = va_arg(vl, const char *);
    }

    return msg;
}

    //�ǥե���ȥ��󥹥ȥ饯�� (�ƥ�����)
Message::Message(void) throw()
{}

    //���󥹥ȥ饯��
Message::Message(string src) throw() : Formatter(src)
{}

    //���󥹥ȥ饯�� (ʣ������)
Message::Message(const char * src1, const char * src2, ...) throw()
{
    va_list vl;

    va_start(vl, src2);
    templatestring.assign(Singleton<MessageControl>::getInstance()->select(src1, src2, vl));
    shift();
}

    //���ԡ����󥹥ȥ饯��
Message::Message(const Message & src) throw() : Formatter(src)
{}

    //�������饹�ν�����Ѵؿ� (ʣ������)
void Message::_initialize(const char * src1, const char * src2, va_list vl) throw()
{
    content.clear();
    accept = false;
    templatestring.assign(Singleton<MessageControl>::getInstance()->select(src1, src2, vl));
    shift();
}

    //��������
void Message::selectLanguage(enum tagLanguage lang) throw()
{
    if(lang >= 0 && lang < LAST_LANG)
        Singleton<Message::MessageControl>::getInstance()->setLanguage(lang);
}

    //�ƥ�ץ졼��ʸ��������� (��ȤϾä���)
void Message::assign(const char * src1, const char * src2, ... ) throw()
{
    va_list vl;

    clear();

    va_start(vl, src2);
    templatestring.assign(Singleton<MessageControl>::getInstance()->select(src1, src2, vl));
    shift();
}

/*****************************************************************************/

/*
 *   ��Ĺ������ʸ���������إ�ѡ����饹
 */

    //�ǥե���ȥ��󥹥ȥ饯��
VerboseMessage::VerboseMessage(void) throw() : Message()
{}

    //���󥹥ȥ饯��
VerboseMessage::VerboseMessage(const char * src) throw() : Message(src)
{}

    //���󥹥ȥ饯��
VerboseMessage::VerboseMessage(const string & src) throw() : Message(src)
{}

    //���󥹥ȥ饯��
VerboseMessage::VerboseMessage(const char * src1, const char * src2, ... ) throw() : Message()
{
    va_list vl;

    va_start(vl, src2);
    _initialize(src1, src2, vl);
}

    //�ǥ��ȥ饯��
VerboseMessage::~VerboseMessage(void) throw()
{   Singleton< VerboseControl >::getInstance()->operator << (str());    }

/*****************************************************************************/

/*
 *   �㳰��å�������ʸ���������إ�ѡ����饹
 */

    //���󥹥ȥ饯��
ExceptionMessage::ExceptionMessage(const char * src) throw() : Message(src), level(DEFAULT)
{}

    //���󥹥ȥ饯��
ExceptionMessage::ExceptionMessage(const std::string & src) throw() : Message(src), level(DEFAULT)
{}

    //���󥹥ȥ饯��
ExceptionMessage::ExceptionMessage(const char * src1, const char * src2, ...) throw() : Message(), level(DEFAULT)
{
    va_list vl;
    
    va_start(vl, src2);
    _initialize(src1, src2, vl);
}

    //���󥹥ȥ饯��
ExceptionMessage::ExceptionMessage(enum tagLevel _level) throw() : Message(), level(_level)
{}

    //���󥹥ȥ饯��
ExceptionMessage::ExceptionMessage(enum tagLevel _level, const char * src) throw() : Message(src), level(_level)
{}

    //���󥹥ȥ饯��
ExceptionMessage::ExceptionMessage(enum tagLevel _level, const std::string & src) throw() : Message(src), level(_level)
{}

    //���󥹥ȥ饯��
ExceptionMessage::ExceptionMessage(enum tagLevel _level, const char * src1, const char * src2, ...) throw() : Message(), level(_level)
{
    va_list vl;
    
    va_start(vl, src2);
    _initialize(src1, src2, vl);
}

    //���ԡ����󥹥ȥ饯��
ExceptionMessage::ExceptionMessage(const ExceptionMessage & src) throw() : Message(src), level(src.level)
{}


/*****************************************************************************/

/*
 *   �ǥХå���å�������ʸ���������إ�ѡ����饹
 */

    //���󥹥ȥ饯��
DebugMessage::DebugMessage(string src) throw() : Formatter(src)
{}

    //�ǥ��ȥ饯��
DebugMessage::~DebugMessage(void) throw()
{   Singleton<DebugControl>::getInstance()->operator << (str());    }

