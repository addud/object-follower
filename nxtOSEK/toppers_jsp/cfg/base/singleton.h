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
 *  @(#) $Id: singleton.h,v 1.12 2004/09/06 15:00:49 honda Exp $
 */

// $Header: /home/CVS/configurator/base/singleton.h,v 1.12 2004/09/06 15:00:49 honda Exp $

#include "base/testsuite.h"

#ifndef SINGLETON_H
#define SINGLETON_H

#ifdef _MSC_VER
#  pragma warning(disable:4290) //C++ ���㳰�λ����̵�뤵��ޤ����ؿ��� __declspec(nothrow) �Ǥʤ����ȤΤ�ɽ������ޤ���
#  pragma warning(disable:4291) //��������ݥɤ��㳰�򥹥�ݤ���ȡ�'new' �黻�Ҥ���Ѥ��Ƥ���ȥ����������ޤ���
#  pragma warning(disable:4786) //�ǥХå�����Ǽ��̻Ҥ� 255 ʸ�����ڤ�ΤƤ��ޤ�����
#endif

#include <new>
#include <stdexcept>

/*
 *  ���󥰥�ȥ�ѥ����� ����
 */

    //���󥰥�ȥ���쥯�饹
    //  #gcc��friend class Singleton�򿩤äƤ���ʤ��ΤǴ������
class SingletonBase {
public:
        //�ǥ��ȥ饯���Υ�������
    struct chain {
        struct chain * next;
        void (*destructor)(void);
    };

        //���󥰥�ȥ�ǥ��󥹥��󥹤������������Ȥ򼨤�����Υ��饹
        //    ���Υ��饹��Singleton���餷�����β��Ǥ��ʤ��Τǡ�
        //    �ۤ��Υ��饹���餳�������ˤ�ĥ��󥹥ȥ饯������Ѥ��뤳�ȤϤǤ��ʤ�
    class SingletonConstructionLocker
    {
    friend class SingletonBase;
    protected:
        SingletonConstructionLocker() {}
    };

private:
    static bool   initialize;       //������Ѥߤ� (atexit��Ƥ�����ɤ���)
    static bool   is_valid;         //�����˼��Ԥ������󥰥�ȥ󥬤��뤫�ɤ���
    static struct chain * top;      //�ǥ��ȥ饯����������

        //�ǥ��ȥ饯���ε�ư
    static void final_release(void) throw()
    {
            //��Ƭ������ (�������Ф�)
        while(top != 0) {
            struct chain * node = top;
            top = node->next;

            (*node->destructor)();

            delete node;
        }
    }

protected:
        //��������˥ǥ��ȥ饯�����ɲ�
    static bool addDestructor(void (* destructor)(void)) throw()
    {
        bool result = false;
        struct SingletonBase::chain * node = new(std::nothrow) struct SingletonBase::chain;
        if(node != 0) {

                //���������Ǥ���Ƭ���ɲ�
            node->next       = top;
            node->destructor = destructor;
            
            top = node;

            result = true;

                //�����˴��Τ���˺Ǹ���˴��롼�����ư������
            if(!initialize) {
                atexit(final_release);
                initialize = true;
            }
        }
        return result;
    }

        //SingletonConstructionLocker�ե����ȥ�
    inline static SingletonConstructionLocker getLocker(void)
    {   return SingletonConstructionLocker();   }

public:
        //�����˼��Ԥ������󥰥�ȥ󤬤ʤ����Ȥ����
    static bool isValid(void) throw()
    {   return is_valid;   }

#ifdef TESTSUITE
        /*
         *   ����ƥ����ȥ������� (�ƥ����ѥ��󥰥�ȥ󥳥�ƥ����������������)
         */
    class ContextChain {
    protected:
        struct chain {
            struct chain * next;
            void * context;
            void (*restore)(void * & context) throw();
            void (*renew)(void) throw();
            void (*clear)(void);
        } * top;

    public:
        ContextChain(void) throw() : top(0)
        {}

        ~ContextChain(void) throw()
        {   restoreContext();   }

            /* ����ƥ����Ȥ����� */
        void restoreContext(void) throw()
        {
            while(top != 0) {
                struct chain * node = top;
                top = top->next;

                (*node->restore)(node->context);
                delete node;
            }
        }

            /* ���ƤΥ��󥹥��󥹤������ */
        void renewInstance(void) throw(std::bad_alloc)
        {
            struct chain * node = top;
            while(node != 0) {
                (*node->renew)();
                node = node->next;
            }
        }
            
            /* ���ƤΥ��󥹥��󥹤��˴� */
        void clearInstance(void) throw(std::bad_alloc)
        {
            struct chain * node = top;
            while(node != 0) {
                (*node->clear)();
                node = node->next;
            }
        }
            
            /* ����ƥ����Ȥ����� */
        template<class T> void saveContext(void) throw(std::bad_alloc)
        {
            struct chain * node = new struct chain;

            node->next = top;
            node->restore = reinterpret_cast<void(*)(void*&)>(Singleton<T>::restoreContext);
            node->renew   = Singleton<T>::renewInstance;
            node->clear   = Singleton<T>::clearInstance;

            Singleton<T>::saveContext(reinterpret_cast<Singleton<T>::Context &>(node->context));

            top = node;
        }
    };
#endif


    TESTSUITE_PROTOTYPE(main)
};


template<class T>
class Singleton : SingletonBase
{
protected:
    Singleton(void);
    ~Singleton(void);

    static T * instance;

        //�ǥ��ȥ饯��
    static void destructor(void) throw()
    {
        if(instance != 0) {
            try{ delete instance; } catch(...) {}
            instance = 0;
        }
    }

        //���󥹥��󥹤����� (���󥹥������� + �ǥ��ȥ饯����Ͽ + ���顼����)
    static T * createInstance(std::nothrow_t) throw()
    {
        T * instance = 0;
        try {
            instance = new(std::nothrow) T(getLocker());

            if(instance != 0) {
                if(!addDestructor(destructor))
                    throw false;    //catch���¹Ԥ�������
            }
        }
        catch(...) {
            if(instance != 0) {
                try { delete instance; } catch(...) {}
                instance = 0;
            }
        }
        return instance;
    }

        //���󥹥������� (bad_alloc�㳰�򥹥��������)
    static T * createInstance(void) throw(std::bad_alloc)
    {
        instance = createInstance(std::nothrow);
        if(instance == 0)
            throw std::bad_alloc();
        return instance;
    }

public:
        //���󥹥��󥹤μ���
    inline static T * getInstance(void) throw(std::bad_alloc)
    {
        if(instance == 0)
            instance = createInstance();
        return instance;
    }

        //���󥹥��󥹤μ���
    inline static T * getInstance(std::nothrow_t) throw()
    {
        if(instance == 0)
            instance = createInstance(std::nothrow);
        return instance;
    }

#ifdef TESTSUITE    /* �ƥ����� */

    typedef T * Context;    //������

        //���������󥹥��󥹤�����
    static void renewInstance(void) throw(std::bad_alloc)
    {
        destructor();                     //���Υ��󥹥��󥹤��˴�
        instance = new T(getLocker());    //���������󥹥��󥹤����� (�ǥ��ȥ饯������Ͽ����Ƥ��ޤ��Τ�createInstance��Ƥ�ǤϤ����ʤ�)
    }

        //���󥹥����˴�
    static void clearInstance(void) throw()
    {   destructor();   }

        //����ƥ���������
    static void saveContext(Context & context) throw()
    {
        context  = instance;
        instance = 0;
    }

        //����ƥ���������
    static void restoreContext(Context & context) throw()
    {
        destructor();           //���Υ��󥹥��󥹤��˴�
        instance = context;     //���򤷤����󥹥��󥹤�����
    }

#endif /* TESTSUITE */

};



    //Singleton ��Ū�ѿ�
template<class T> T * Singleton<T>::instance = 0;

#define SINGLETON_CONSTRUCTOR(x)  explicit x(const SingletonBase::SingletonConstructionLocker &)
#define SINGLETON_CONSTRUCTOR_(x) explicit x(const SingletonBase::SingletonConstructionLocker & _singleton)

#define SINGLETON_WRAPPER(derived, base) class derived : public base { public: SINGLETON_CONSTRUCTOR_(derived) throw() : base(_singleton) {} };

#endif /* SINGLETON_H */

