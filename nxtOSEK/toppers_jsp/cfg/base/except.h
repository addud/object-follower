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
 *  @(#) $Id: except.h,v 1.9 2003/12/20 06:51:58 takayuki Exp $
 */

// $Header: /home/CVS/configurator/base/except.h,v 1.9 2003/12/20 06:51:58 takayuki Exp $

#ifndef EXCEPT_H
#define EXCEPT_H

#ifdef _MSC_VER
#  pragma warning(disable:4290) //C++ ���㳰�λ����̵�뤵��ޤ����ؿ��� __declspec(nothrow) �Ǥʤ����ȤΤ�ɽ������ޤ���
#endif

//#include "testsuite.h"

#include <string>
#include <typeinfo>

    //�㳰���쥯�饹
class Exception
{
private:
    static bool is_throwable;

protected:
    int         code;       //�㳰������
    std::string classname;  //�����㳰�������������饹��̾�� (������)
    std::string details;    //�㳰������

        //���󥹥ȥ饯��
    Exception(std::string classname = "Exception", int code = 0, std::string details = "") throw();
    Exception(std::string classname, std::string details) throw();

        //�ǥ��ȥ饯��
public:
    Exception(const Exception & src) throw();

    virtual ~Exception(void) throw();

        //is-an-instance-of�ط���ɾ��
    inline bool isInstanceOf(const char * _classname) const throw()
    {   return classname.compare(_classname) == 0;   }

        //�㳰�����ɤ��������
    inline int getCode(void) const throw()
    {   return code;   }

        //�㳰���������������
    inline std::string getDetails(void) const throw()
    {   return details;   }

        //���ߤ��㳰����ե饰�ξ��֤˽��ä��㳰��ȯ�Ԥ���
    inline bool throwException(void)
    {
        if(is_throwable)
            throw *this;
        return is_throwable;
    }

        //is_throwable�Υ�������
    static void setThrowControl(bool _throwable) throw()
    {   is_throwable = _throwable;   }

    static bool getThrowControl(void) throw()
    {   return is_throwable;   }


//  TESTSUITE_PROTOTYPE(main)
};


#define EXCEPTION(x)       class x : public Exception { public: x(void) throw() : Exception(#x)       {} };
#define EXCEPTION_(x,y)    class x : public Exception { public: x(void) throw() : Exception(#x, y)    {} };
#define EXCEPTION__(x,y,z) class x : public Exception { public: x(void) throw() : Exception(#x, y, z) {} };

#endif



