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
 *  @(#) $Id: collection.h,v 1.6 2003/12/20 06:51:58 takayuki Exp $
 */

// $Header: /home/CVS/configurator/base/collection.h,v 1.6 2003/12/20 06:51:58 takayuki Exp $

#ifndef COLLECTION_H
#define COLLECTION_H

#include "base/testsuite.h"
#include "base/singleton.h"

#include <typeinfo>
#include <list>

    //Collection����Ͽ���������֥������ȤΥ��饹�δ��쥯�饹
class Collectable
{
public:
             Collectable(void) throw() {}   //�ä˲��⤷�ʤ�
    virtual ~Collectable(void) throw() {}   //�ä˲��⤷�ʤ�
};



    //���뷿�Υ��󥹥��󥹤���Ͽ�����ݻ����뤿��Υ��饹
class Collection
{
public:
    struct Element
    {
        Collectable * instance;
        bool          destruction;
    };

protected:
    std::list<Element> container;

        //predecessor�μ���ؤ����ƥ졼�������� (getInstance)
    std::list<Element>::const_iterator _findInstance(const Collectable * predecesor) const throw();

public:
        //���󥹥ȥ饯�� & �ǥ��ȥ饯��
             Collection(void)  throw();
    virtual ~Collection(void) throw();

        //ͭ��Ƚ��
    inline bool isValid(void) const throw()
    {   return this != 0;   }

        //���쥯�����ؤ��ɲ� (�ݥ�����)
    bool addInstance(Collectable * instance, bool destruction = true)  throw();
    
        //���쥯�����ؤ��ɲ� (������)
    inline bool addInstance(Collectable & instance, bool destruction = false) throw()
    {   return addInstance(&instance, destruction);   }

        //���쥯����󤫤�μ��� (��������)
    Collectable * getInstance(const std::type_info & type, const Collectable * predecessor = 0) const throw();

        //���쥯����󤫤�μ��� (����������Τ⥵����)
    template<class T> T * getInstance(const Collectable * predecessor = 0) const throw()
    {
        T * result = 0;

        if(isValid()) {
            std::list<Element>::const_iterator iterator = _findInstance(predecessor);

            while(iterator != container.end()) {
                result = dynamic_cast<T *>(iterator->instance);
                if(result != 0)
                    break;
                ++ iterator;
            }
        }
        return result;
    }

        //���쥯����󤫤��������ޤ����ƤΥ��饹���󥹥��󥹤��� (�˴��оݤξ����˴���Ԥ�)
    template<class T> void deleteInstance(void) throw()
    {
        if(isValid()) {
            std::list<Element>::iterator iterator;

            iterator = container.begin();
            while(iterator != container.end()) {
                if(dynamic_cast<T *>(iterator->instance) != 0) {

                        //����оݤʤ饤�󥹥��󥹤���
                    if(iterator->destruction)
                        delete iterator->instance;

                        //�ꥹ�Ȥ������
                    std::list<Element>::iterator target = iterator;
                    ++ iterator;
                    container.erase(target);
                }
                else
                    ++ iterator;
            }
        }
    }

        //��Ϣ�դ���줿���󥹥��󥹤������ؤ���
    template<class T> inline bool replaceInstance(Collectable * instance, bool destruction = true) throw()
    {
            //��ʬ��̵�ط��ʥ��饹�ϥ���ǥå����Ȥ��ƻ���Ǥ��ʤ�
        if(dynamic_cast<T *>(instance) == 0)
            return false;

        deleteInstance<T>();
        return addInstance(instance, destruction);
    }

        //��Ϣ�դ���줿���󥹥��󥹤������ؤ���
    template<class T> inline bool replaceInstance(Collectable & instance, bool destruction = false) throw()
    {
            //��ʬ��̵�ط��ʥ��饹�ϥ���ǥå����Ȥ��ƻ���Ǥ��ʤ�
        if(dynamic_cast<T *>(&instance) == 0)
            return false;

        deleteInstance<T>();
        return addInstance(&instance, destruction);
    }


        //���쥯����󤫤饤�󥹥��󥹤���� (�˴��Ϥ��ʤ�)
    bool removeInstance(const Collectable * instance) throw();

        //�����Ǥ��˴�
    void clear(void);

    TESTSUITE_PROTOTYPE(main)
};


    //�¹Ի����֥������Ȼ��ȥơ��֥�
class RuntimeObjectTable : protected Collection
{
friend class RuntimeObject;
public:
    SINGLETON_CONSTRUCTOR(RuntimeObjectTable) throw() {}

    static Collectable * getInstance(const std::type_info & type, const Collectable * predecessor = 0) throw()
    {
        RuntimeObjectTable * table = Singleton<RuntimeObjectTable>::getInstance(std::nothrow);
        Collectable * result = 0;

        if(table != 0)
            result = table->Collection::getInstance(type, predecessor);
        return result;
    }

        //���쥯����󤫤�μ��� (����������Τ⥵����)
    template<class T> static T * getInstance(const Collectable * predecessor = 0) throw()
    {
        RuntimeObjectTable * table = Singleton<RuntimeObjectTable>::getInstance();
        T * result = 0;

        if(table != 0) {
            std::list<Element>::const_iterator iterator = table->_findInstance(predecessor);

            while(iterator != table->container.end()) {
                result = dynamic_cast<T *>(iterator->instance);
                if(result != 0)
                    break;
                ++ iterator;
            }
        }
        return result;
    }

        /* Visual C++ 6.0 Fatal error C1001�к� */
    template<class T> static T * getInstance(T ** dest, const Collectable * predecessor = 0) throw()
    {
        RuntimeObjectTable * table = Singleton<RuntimeObjectTable>::getInstance();
        T * result = 0;

        if(table != 0) {
            std::list<Element>::const_iterator iterator = table->_findInstance(predecessor);

            while(iterator != table->container.end()) {
                result = dynamic_cast<T *>(iterator->instance);
                if(result != 0)
                    break;
                ++ iterator;
            }
        }
        if(dest != 0)
            *dest = result;

        return result;
    }

    TESTSUITE_PROTOTYPE(main)
};

    //�¹Ի����֥�������
class RuntimeObject : public Collectable
{
public:
    RuntimeObject(bool destruction = false) throw()
    {
        RuntimeObjectTable * table = Singleton<RuntimeObjectTable>::getInstance();
        if(table != 0)
            table->addInstance(this, destruction);
    }

    virtual ~RuntimeObject(void) throw()
    {
        RuntimeObjectTable * table = Singleton<RuntimeObjectTable>::getInstance();
        if(table != 0)
            table->removeInstance(this);
    }
};

    /* �� fatal error C1001: INTERNAL COMPILER ERROR (msc1.cpp:1794) */
#if _MSC_VER < 1300 
#  define getRuntimeObjectInstance(x) (dynamic_cast<x *>(RuntimeObjectTable::getInstance(typeid(x))))       //���Τˤ�Ʃ��ǤϤʤ����������ƨ���뤷���ʤ�
#else
#  define getRuntimeObjectInstance(x) (RuntimeObjectTable::getInstance<x>())
#endif


#endif



