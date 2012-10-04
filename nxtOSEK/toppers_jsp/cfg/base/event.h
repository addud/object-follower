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
 *  @(#) $Id: event.h,v 1.9 2004/09/06 15:00:49 honda Exp $
 */

// $Header: /home/CVS/configurator/base/event.h,v 1.9 2004/09/06 15:00:49 honda Exp $

#ifndef EVENT_H
#define EVENT_H

#include "base/testsuite.h"
#include "base/singleton.h"

#include <list>

    //���٥�ȥեå��μ��ޤȤ���
template<typename T>
class Event
{
public:
    typedef void (*handler_type)(T &);

    class handler_list_type : public std::list<handler_type>
    {   public: SINGLETON_CONSTRUCTOR(handler_list_type) throw() {}   };

    /*
     *   ���饹����Υϥ�ɥ���
     */

    class Handler
    {
    friend class Event;
    public:
        class instance_list_type : public std::list<Handler *>
        {   public: SINGLETON_CONSTRUCTOR(instance_list_type) throw() {}   };

        virtual void handler(T & ev) = 0;

    protected:
            //��Ͽ
        Handler(void) throw()
        {   Singleton<instance_list_type>::getInstance()->push_back(this);   }
        
            //��Ͽ���
        virtual ~Handler(void) throw()
        {
            typename Event<T>::Handler::instance_list_type * list = Singleton<instance_list_type>::getInstance(std::nothrow);
            typename Event<T>::Handler::instance_list_type::iterator scope;

            if(list != 0) {
                scope = list->begin();
                while(scope != list->end()) {
                    if(*scope == this) {
                        typename Event<T>::Handler::instance_list_type::iterator target = scope;
                        ++ scope;
                        list->erase(target);
                    }
                    else
                        ++ scope;
                }
            }
        }
    };

public:
    typedef T value_type;

    Event(void) {}
    virtual ~Event(void) {}

    /*
     *  �����ƥ��å��ʥϥ�ɥ���
     */

        //���٥�Ȥ˥ϥ�ɥ���ɲ�
    inline static void add(handler_type func) throw(std::bad_alloc)
    {   Singleton<handler_list_type>::getInstance()->push_back(func);   }

        //���٥�Ȥ���ϥ�ɥ����
    static void remove(handler_type func) throw()
    {
        typename Event<T>::handler_list_type * list;
        typename Event<T>::handler_list_type::iterator scope;

        list = Singleton<handler_list_type>::getInstance(std::nothrow);
        if(list != 0) {
            scope = list->begin();
            while(scope != list->end()) {
                if(*scope == func) {
                    typename handler_list_type::iterator target = scope;
                    ++ scope;
                    list->erase(target);
                }
                else
                    ++ scope;
            }
        }
    }

    /*
     *  �������
     */
        //���٥�Ȥ�ȯ��
    static void raise(T & ev)
    {
            typedef typename Event<T>::handler_list_type handler_list_type_t; 
            typedef typename Event<T>::Handler::instance_list_type instance_list_type_t;

        /* ��Ͽ���줿��Ū�ʴؿ��˥��٥�Ȥ�ȯ�� */ {
           handler_list_type_t * list;
            typename handler_list_type_t::iterator scope;

            list = Singleton<handler_list_type_t>::getInstance();   //throw(bad_cast)

            scope = list->begin();
            while(scope != list->end()) {
                (**scope)(ev);
                ++ scope;
            }
        }

        /* ��Ͽ���줿���饹���󥹥��󥹤˥��٥�Ȥ�ȯ�� */ {
            instance_list_type_t * list;
            typename instance_list_type_t::iterator scope;

            list = Singleton<instance_list_type_t>::getInstance();  //throw(bad_cast)

            scope = list->begin();
            while(scope != list->end()) {
                (*scope)->handler(ev);
                ++ scope;
            }
        }
    }

        //���٥�Ȥ�ȯ�� (�����ʤ�)
    inline static void raise(void)
    {
        T ev;
        raise(ev);
    }
};


    /*
     *  ���ѥ��٥��
     */

    //���󥹥ȥ饯������ư������ä����ȡ�������˵��륤�٥��
class StartupEvent {};


    //�������Ԥ���鷺���ץ���ब�����Ȥ��˵��륤�٥��
struct ShutdownEvent
{
    int exit_code;
};

#endif



