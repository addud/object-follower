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
 *  @(#) $Id: message.h,v 1.5 2003/12/20 06:51:58 takayuki Exp $
 */

// $Header: /home/CVS/configurator/base/message.h,v 1.5 2003/12/20 06:51:58 takayuki Exp $

#ifndef MESSAGE_H
#define MESSAGE_H

#ifdef _MSC_VER
#  pragma warning(disable:4290) //C++ ���㳰�λ����̵�뤵��ޤ����ؿ��� __declspec(nothrow) �Ǥʤ����ȤΤ�ɽ������ޤ���
#  pragma warning(disable:4786) //�ǥХå�����Ǽ��̻Ҥ�255ʸ�����ڤ�ΤƤ��ޤ�����
#endif

#include <string>
#include <sstream>
#include <stdarg.h>
#include <stdexcept>

//#include "base/testsuite.h"
#include "base/singleton.h"
#include "base/except.h"

    /*
     *   ʸ���������إ�ѡ����饹
     */
class Formatter
{
protected:
    std::string       templatestring;    //�ƥ�ץ졼��ʸ����
    std::stringstream content;           //ʸ���������Ƚ񼰺Ѥ�ʸ�����ǽ����ѥ��ȥ꡼��
    bool              accept;            //�����������ǽ���ɤ���

        //���ΰ�����������ؤȰ�ư
    void shift(void) throw();

        //̤����ΰ����� (null) ���ִ�
    void shift_all(void) throw();

public:
        //�ǥե���ȥ��󥹥ȥ饯��
    Formatter(void) throw();

        //���󥹥ȥ饯��
    Formatter(std::string src) throw();

        //���ԡ����󥹥ȥ饯��
    Formatter(const Formatter & src) throw();

        //�ƥ�ץ졼��ʸ��������� (��ȤϾä���)
    void assign(std::string src) throw();

        //���ƤΥ��ꥢ
    void clear(void) throw();

        //�����黻��
    Formatter & operator =(const Formatter & src) throw();

        //����������
    template<class T>
    Formatter & operator << (const T & src) throw()
    {
        std::string::size_type pos;

            //�����������ǽ�ʤ�
        if(accept) {
            pos = content.str().size();
            content << src;

                /* ��ʸ���Ǥʤ���м����������˰�ư */
            if(pos != content.str().size())
                shift();
        }
        return *this;
    }

        //������å������μ��Ф�
    std::string str(void) throw();

        //ɸ����ϥ��ȥ꡼��ؤν����� operator << ���
    friend inline std::ostream & operator << (std::ostream & out, Formatter msg) throw()
    {
        out << msg.content.str();
        return out;
    }

//    TESTSUITE_PROTOTYPE(main)
};

    /*
     *   ��å����������Ѥ�2�����б���Ԥä�ʸ���������إ�ѡ����饹
     */
class Message : public Formatter
{
public:
    enum tagLanguage
    {
        ENGLISH  = 0,
        JAPANESE = 1,

        LAST_LANG,              //�Ǹ�ΰ���
        NEUTRAL  = ENGLISH,     //ɸ�����
    };

        /* ���ϥ�å������������楯�饹 */
    class MessageControl
    {
    protected:
        int language;   //�ɤθ������Ѥ���Τ�

    public:
            //���󥹥ȥ饯��
        SINGLETON_CONSTRUCTOR(MessageControl) throw() : language(NEUTRAL) {};

            //��������
        inline void setLanguage(int _language) throw()  { language = _language; }
        inline int  getLanguage(void) const    throw()  { return language; }

        const char * select(const char * msg1, const char * msg2, va_list vl ) throw();
    };

protected:

        //�������饹�ѥ��󥹥ȥ饯��
    void _initialize(const char * src1, const char * src2, va_list vl) throw();

public:
        //�ǥե���ȥ��󥹥ȥ饯��
    Message(void) throw();

        //���󥹥ȥ饯�� (ñ�����)
    Message(std::string src) throw();

        //���󥹥ȥ饯�� (ʣ������)
    Message(const char * src1, const char * src2, ... ) throw();

        //���ԡ����󥹥ȥ饯��
    Message(const Message & src) throw();

        //�ƥ�ץ졼��ʸ��������� (��ȤϾä���)
    void assign(std::string src) throw() { Formatter::assign(src); }
    void assign(const char * src1, const char * src2, ... ) throw();

        //��������
    static void selectLanguage(enum tagLanguage lang = NEUTRAL) throw();
        
        //����μ���
    static enum tagLanguage getCurrentLanguage(void) throw()
    {   return static_cast<enum tagLanguage>(Singleton<MessageControl>::getInstance()->getLanguage());   }

    //TESTSUITE_PROTOTYPE(main)
};


    /*
     *   ��Ĺ������ʸ���������إ�ѡ����饹
     */
class VerboseMessage : public Message
{
public:
        //���̤ξ�Ĺ���Ͼ������ĥ��饹
    class VerboseControl
    {
    public:
        bool           verbose;     //��Ĺ���Ϥ�Ԥ����ɤ���
        std::ostream * out;         //������

            //���󥹥ȥ饯��
        SINGLETON_CONSTRUCTOR(VerboseControl) throw() : verbose(false), out(0)
        {}

            //��Ĺ��������
        template<class T>
        inline const VerboseControl & operator << (const T & src) const throw()
        {
            if(verbose && out != 0)
                (*out) << src;
            return *this;
        }

            //verbose��������
        void setVerbose(bool _verbose) throw()
        {   verbose = _verbose;   }
        bool getVerbose(void) const throw()
        {   return verbose;   }

            //out��������
        void setStream(std::ostream * _out) throw()
        {   out = _out;   }
        std::ostream * getStream(void) throw()
        {   return out;   }
    };

        //��Ĺ���ϥ��ȥ꡼�� (ñ����޻ߵ����Ĥ���åѡ����饹)
    class VerboseStream
    {
    protected:
        std::ostream * out;

    public:
        VerboseStream(std::ostream * _out = 0) throw() : out(_out) {};

        template<class T>
        VerboseStream & operator << (const T & src) throw()
        {
            if(out != 0)
                (*out) << src;
            return *this;
        }
    };

protected:
        //�ǥե���ȥ��󥹥ȥ饯�� (�ƥ�����)
    VerboseMessage(void) throw();

public:

        //���󥹥ȥ饯��
    VerboseMessage(const char * src) throw();
    VerboseMessage(const std::string & src) throw();
    VerboseMessage(const char * src1, const char * src2, ... ) throw();

        //�ǥ��ȥ饯��
    ~VerboseMessage(void) throw();

        //��Ĺ�������� (������������)
    inline static void setVerbose(bool _verbose) throw()
    {   Singleton<VerboseControl>::getInstance()->setVerbose(_verbose);   }

        //��Ĺ�����襹�ȥ꡼������ (������������)
    inline static void setStream(std::ostream * _stream) throw()
    {   Singleton<VerboseControl>::getInstance()->setStream(_stream);   }

        //��Ĺ��������ξ��ּ���
    inline static bool getVerbose(void) throw()
    {   return Singleton<VerboseControl>::getInstance()->getVerbose();   }

        //��Ĺ�����襹�ȥ꡼��μ��� (���ꤷ����Τ�Ʊ����ΤϽФƤ��ʤ�)
    inline static VerboseStream getStream(void) throw()
    {   return VerboseStream(getVerbose() ? Singleton<VerboseControl>::getInstance()->getStream() : 0);   }

    //TESTSUITE_PROTOTYPE(main)
};

    /*
     *   �㳰��å�������ʸ���������إ�ѡ����饹
     */
class ExceptionMessage : public Message
{
public:
        //�㳰�δ��٥�٥�
    enum tagLevel {
        DEFAULT = 0,
        FATAL   = 1,
        WARNING = 2
    };

#ifdef EXCEPT_H
    class ExceptionMessageException : public Exception
    {
    friend class ExceptionMessage;
    protected:
        ExceptionMessageException(int _code, std::string _details) throw() : Exception("ExceptionMessage", _code, _details) {}
    };
#endif

protected:
    enum tagLevel level;

public:
        //���󥹥ȥ饯��
    ExceptionMessage(const char * src) throw();
    ExceptionMessage(const std::string & src) throw();
    ExceptionMessage(const char * src1, const char * src2, ...) throw();

    ExceptionMessage(enum tagLevel level = DEFAULT) throw();
    ExceptionMessage(enum tagLevel level, const char * src) throw();
    ExceptionMessage(enum tagLevel level, const std::string & src) throw();
    ExceptionMessage(enum tagLevel level, const char * src1, const char * src2, ...) throw();

    ExceptionMessage(const ExceptionMessage & src) throw();


        //���٥�٥뻲��
    inline bool operator == (enum tagLevel _level) const throw()
    {   return level == _level;   }

        //���٥�٥뻲��
    inline bool operator != (enum tagLevel _level) const throw()
    {   return !(operator ==(_level));   }

        //���������� (�ֵ��ͤη���Message & ���� ExceptionMessage & �ˤ��뤿��ξ��ٹ�)
    template<class T>
    inline ExceptionMessage & operator << (const T & src) throw()
    {
        Message::operator << ( src );
        return *this;
    }

#ifdef EXCEPT_H     //Exception���饹����Ѥ�����
        //�㳰��ȯ��
    bool throwException(void) throw(Exception)
    {
        ExceptionMessageException exc(level, str());
        return exc.throwException();
    }
        //�ޥ˥ԥ�졼��
    inline ExceptionMessage & operator << ( ExceptionMessage & (* func)(ExceptionMessage &) ) throw(Exception)
    {   return (*func)(*this);   }

#else               //stdexcept����Ѥ�����
        //�㳰��ȯ��
    template<class T>
    bool throwException(void) throw(T)
    {
        throw T(str());
        return true;
    }
        //�ޥ˥ԥ�졼��
    inline ExceptionMessage & operator << ( ExceptionMessage & (* func)(ExceptionMessage &) ) throw(T)
    {   return (*func)(*this);   }
#endif

    //TESTSUITE_PROTOTYPE(main)
};

#ifdef EXCEPT_H     //Exception���饹����Ѥ�����

        //�㳰�򥹥����뤿��Υޥ˥ԥ�졼��
    inline ExceptionMessage & throwException(ExceptionMessage & excmsg) throw(Exception)
    {
        excmsg.throwException();
        return excmsg;
    }

#else
        //�㳰�򥹥����뤿��Υޥ˥ԥ�졼��
    template<class T>
    inline ExceptionMessage & throwException(ExceptionMessage & excmsg) throw(T)
    {
        excmsg.throwException<T>();
        return excmsg;
    }

#endif



    /*
     *   �ǥХå����������ʸ���������إ�ѡ����饹
     */
class DebugMessage : public Formatter
{
public:
        //���̤ξ�Ĺ���Ͼ������ĥ��饹 (���󥰥�ȥ�ˤ���Τ�VerboseControl��Ʊ����Τ򥯥饹������)
    class DebugControl : public VerboseMessage::VerboseControl
    { public: SINGLETON_CONSTRUCTOR_(DebugControl) throw() : VerboseMessage::VerboseControl(_singleton) {} };


protected:
        //�ǥե���ȥ��󥹥ȥ饯�� (�ƥ�����)
    DebugMessage(void) throw();

public:

        //���󥹥ȥ饯��
    DebugMessage(std::string src) throw();

        //�ǥ��ȥ饯��
    ~DebugMessage(void) throw();

        //��Ĺ�������� (������������)
    inline static void setVerbose(bool _verbose) throw()
    {   Singleton<DebugControl>::getInstance()->setVerbose(_verbose);   }

        //��Ĺ�����襹�ȥ꡼������ (������������)
    inline static void setStream(std::ostream * _stream) throw()
    {   Singleton<DebugControl>::getInstance()->setStream(_stream);   }

        //��Ĺ��������ξ��ּ���
    inline static bool getVerbose(void) throw()
    {   return Singleton<DebugControl>::getInstance()->getVerbose();   }

        //��Ĺ�����襹�ȥ꡼��μ��� (���ꤷ����Τ�Ʊ����ΤϽФƤ��ʤ�)
    inline static VerboseMessage::VerboseStream getStream(void) throw()
    {   return VerboseMessage::VerboseStream(getVerbose() ? Singleton<DebugControl>::getInstance()->getStream() : 0);   }

//  TESTSUITE_PROTOTYPE(main)
};


#endif  //MESSAGE_H


