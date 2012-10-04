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
 *  @(#) $Id: garbage.h,v 1.7 2003/12/20 06:51:58 takayuki Exp $
 */

// $Header: /home/CVS/configurator/base/garbage.h,v 1.7 2003/12/20 06:51:58 takayuki Exp $


#ifndef GARBAGE_H
#define GARBAGE_H

#ifdef _MSC_VER
#  pragma warning(disable:4290) //C++ ���㳰�λ����̵�뤵��ޤ����ؿ��� __declspec(nothrow) �Ǥʤ����ȤΤ�ɽ������ޤ���
#  pragma warning(disable:4786) //�ǥХå�����Ǽ��̻Ҥ�255ʸ�����ڤ�ΤƤ��ޤ�����
#endif

#include "base/testsuite.h"
#include <list>


    //ưŪ�������������֥������Ȥ�������˴����뤿��Υ���Ȣ�롼����
class TrashBox
{
public:
    typedef std::list<class Garbage *>::iterator Cookie;

protected:
    static TrashBox *    current_box;   //���߻��Ѥ��Ƥ��르��Ȣ
    TrashBox *           previous_box;  //���Υ���Ȣ�ο�
    
    std::list<class Garbage *> garbage; //����

public:
        //������ �� ���ǻ�
    TrashBox(void)  throw();
    ~TrashBox(void) throw();

    inline bool isValid(void) const throw()
    {   return (this != 0);   }

        //����Ȣ�����äƤ��르�ߤ��˴�
    void cleanup(void);

        //���ȤäƤ��르��Ȣ�����
    inline static TrashBox * getCurrentTrashBox(void) throw()
    {   return current_box;   }

        //��������
    inline Cookie addGarbage(class Garbage * _garbage) throw()
    {   return garbage.insert(garbage.begin(), _garbage);   }

        //���߲��
    void recoverGarbage(Cookie cookie) throw();


        //ưŪ�˳��ݤ��������ʤ�
    void * operator new (size_t) throw(std::bad_alloc)
    {   throw std::bad_alloc();   }
    void * operator new (size_t, std::nothrow_t) throw()
    {   return 0;   }

    TESTSUITE_PROTOTYPE(main)
};


    //����Ȣ������르�ߥ��֥������Ȥδ���
class Garbage
{
private:
    class TrashBox *  assigned_box;
    TrashBox::Cookie  cookie;

public:
        //������ �� ���ǻ�
    Garbage(void)  throw();
    virtual ~Garbage(void) throw();

        //�ꤲ�����ߤ򽦤��夲��
    void rescue(void) throw();
};


#endif


