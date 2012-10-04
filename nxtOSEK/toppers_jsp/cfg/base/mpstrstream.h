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
 *  @(#) $Id: mpstrstream.h,v 1.9 2003/12/20 06:51:58 takayuki Exp $
 */

// $Header: /home/CVS/configurator/base/mpstrstream.h,v 1.9 2003/12/20 06:51:58 takayuki Exp $

#ifndef MPSTRSTREAM_H
#define MPSTRSTREAM_H

#ifdef _MSC_VER
#  pragma warning(disable:4290) //C++ ���㳰�λ����̵�뤵��ޤ����ؿ��� __declspec(nothrow) �Ǥʤ����ȤΤ�ɽ������ޤ���
#  pragma warning(disable:4786) //�ǥХå�����Ǽ��̻Ҥ�255ʸ�����ڤ�ΤƤ��ޤ�����
#endif

#include "testsuite.h"
#include "base/except.h"
#include "base/message.h"
#include "base/event.h"

#include <fstream>
#include <sstream>
#include <string>
#include <list>


    //ʣ�����̤���ʤ�����ѥ��ȥ꡼��Υ��饹
class MultipartStream : public Event<ShutdownEvent>::Handler
{
public:

        //ʣ�����̤���ʤ�����ѥ��ȥ꡼��ΰ����̤��������륯�饹
    class Part
    {
    protected:
        std::string       name;
        std::stringstream stream;

    public:
            //���󥹥ȥ饯��
        Part(std::string name) throw();
        Part(const Part & src) throw();

            //������Ƚ��
        inline bool isValid(void) const throw()
        {   return (this != 0) && !name.empty() && stream.good();   }

            //���ȥ꡼��ؤν����
        template<class T>
        Part & operator << ( T src ) throw(Exception)
        {
            if(isValid())
                stream << src;
            else
                ExceptionMessage("Operation was performed against an invalid stream.","̵���ʥ��ȥ꡼����Ф������Ԥ��ޤ���").throwException();

            return *this;
        }

            //���ȥ꡼��˽񤤤����Ƥ�������
        std::string getContents(void) const throw(Exception);

            //���ȥ꡼������Ƥ�ľ�����ꤹ��
        void setContents(std::string contents) throw(Exception);

            //���ȥ꡼��̾�λ���
        inline const std::string & getName(void) const throw(Exception)
        {
            if(!isValid())
                ExceptionMessage("Operation was performed against an invalid stream.","̵���ʥ��ȥ꡼����Ф������Ԥ��ޤ���").throwException();
            return name;
        }

            //�����黻��
        inline Part & operator = (const Part & src) throw()
        {
            name = src.name;
            stream.clear();
            stream << src.stream.str();
        
            return *this;
        }

        TESTSUITE_PROTOTYPE(main)
    };


protected:
    std::string         filename;       //��Ϣ�դ���줿�ե�����̾
    std::list<Part>     parts;          //���̽���(����Ĥ�)
    Part *              current;        //�����Ƥ�������
    bool                dirty;          //�ե�����˽��Ϥ����פ����true (�����񤭹������... �ǤϤʤ����ޤ����Ϥ��Ƥʤ����ɤ���)
    bool                output;         //���Ϥ��Ƥ��ɤ��ʤ�true

    virtual void handler(ShutdownEvent & evt)
    {   serialize();    }
  
public:
        //���󥹥ȥ饯��
    MultipartStream(std::string filename = "") throw();

        //�ǥ��ȥ饯��
    virtual ~MultipartStream(void) throw();

        //������Ƚ��
    inline bool isValid(void) const throw()
    {   return (this != 0) && !filename.empty();   }

        //�ե�����̾
    std::string setFilename(std::string filename) throw(Exception);
    std::string getFilename(void) const throw() { return filename; };

        //���ȥ꡼������Ƥ�ե�����˽���
    bool serialize(void) throw(Exception);

        //���̤�����
    MultipartStream & createPart(std::string name, bool precedence = false) throw(Exception);

        //���̤�����
    MultipartStream & movePart(std::string name) throw(Exception);

        //���Ϥ��뤫�ɤ���������
    inline void enableOutput(void) throw()
    {   if(isValid()) output = true;   }
    inline void disableOutput(void) throw()
    {   if(isValid()) output = false;   }

        //�����ƥ��ӥåȤ�����
    inline void setDirty(bool _dirty = true) throw()
    {   dirty = _dirty;   }

        //����
    template <class T>
    inline MultipartStream & operator << ( T src ) throw(Exception)
    {
        if(this != 0 && current != 0) {
            setDirty();
            (*current) << src;
        }
        else
            ExceptionMessage("Invalid operation against an invalid object","̵���ʥ��֥������Ȥ��Ф����׵�").throwException();
        return *this;
    }

        //���̤����� (Synonym)
    inline MultipartStream & operator[] (std::string name) throw(Exception)
    {   return movePart(name);   }

    TESTSUITE_PROTOTYPE(main)
};

#endif


