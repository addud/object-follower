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
 *  @(#) $Id: component.h,v 1.8 2003/12/20 06:51:58 takayuki Exp $
 */

// $Header: /home/CVS/configurator/base/component.h,v 1.8 2003/12/20 06:51:58 takayuki Exp $

#include "base/testsuite.h"
#include "base/singleton.h"
#include "base/except.h"
#include "base/message.h"
#include "base/option.h"
#include "base/collection.h"
#include "base/directorymap.h"

#include <list>
#include <map>

#ifndef COMPONENT_H
#define COMPONENT_H

class Component : public RuntimeObject
{
public:
        //����ݡ��ͥ�Ȥε�ưͥ����
    enum tagProcessStage {
        INITIALIZE,                 //�Ȥˤ����������ư����������

        BEFORE_PARSE,               //�ѡ�����
        PARSER,                     //�ѡ���
        AFTER_PARSE,                //�ѡ�����

        PREDECESSOR,                //���Ѥ���
        GENERAL_PURPOSE,            //����
        SUCCESSOR,                  //���Ѥθ�

        BEFORE_CODEGENERATION,      //������������
        CODEGENERATOR,              //����������
        AFTER_CODEGENERATION,       //������������

        FINALIZE
    };

        //����ݡ��ͥ�Ȥ˶��̤Υǡ��������/���륯�饹
    class ComponentInfo
    {
    protected:
        std::string                     banner;
        std::multimap<int, Component *> componentList;
        std::list<Component *>          activatedComponentList;

            //���󥹥ȥ饯�� (�ƥ�����)
        ComponentInfo(void) throw() {}
    public:
            //���󥹥ȥ饯��
        SINGLETON_CONSTRUCTOR(ComponentInfo) {}

            //����ݡ��ͥ�Ȥ��ɲ�
        bool addComponent(Component * component, int order) throw();

            //����ݡ��ͥ�Ȥ���Ͽ���
        void removeComponent(Component * component, int order) throw();     //�����ͥ���٤�������
        void removeComponent(Component * component) throw();                //���Ʋ��

            //����ݡ��ͥ�Ȥε�ư�׵�
        bool activateComponent(Component * component) throw();

            //���ץ����Υѡ���
        void parseOption(OptionParameter & option);

            //����ݡ��ͥ�Ȥε�ư
        void activateComponent(void);

            //�۾�����ϥ�ɥ�ε�ư
        void onFatalExit(void);

            //����ݡ��ͥ��T����ư���Ƥ��뤫��Ƚ��
        template<class T>
        bool isActive(void) const throw()
        {
            std::list<Component *>::const_iterator scope;

            scope = activatedComponentList.begin();
            while(scope != activatedComponentList.end()) {
                if(dynamic_cast<T *>(*scope) != 0)
                    return true;
                ++ scope;
            }
            return false;
        }

            //�Хʡ��ѿ��ؤΥ�������
        inline void setBanner(std::string src)
        {   banner = src;    }
        inline std::string getBanner(void) const
        {   return banner;   }


        TESTSUITE_PROTOTYPE(main)
    };


protected:
    static bool is_valid;       //����ݡ��ͥ�Ȥν�����������������ɤ�������ĥե饰

    /*
     *   ��ȴؿ�
     */

        //����ݡ��ͥ�Ȥε�ư
    inline bool activateComponent(void) throw()
    {   return Singleton<ComponentInfo>::getInstance()->activateComponent(this);   }

        //����Ū�ʥ��ץ����ν���
    static void _parseCommonOption(OptionParameter & option) throw();


        //��ʬ����Ԥ��륳��ݡ��ͥ�Ȥε�ưȽ��
    template<class T>
    static bool isActive(void) throw()
    {   
        bool result = false;
        ComponentInfo * info = Singleton<ComponentInfo>::getInstance(std::nothrow);
        if(info != 0)
            result = info->isActive<T>();
        return result;
    }


        /*
         *   ���Ȥθߴ����Τ���Υѥ�᡼�����API
         */

    static bool findOption (const char * key1, const char * key2 = 0, std::string * = 0) throw();
    static bool checkOption(const char * key1, const char * key2 = 0) throw();
    static OptionParameter::OptionItem getOption  (const char * key1, const char * key2 = 0, bool dirty = true) throw();
    static OptionParameter::OptionItem mergeOption(const char * key1, const char * key2 = 0) throw();

public:
        //���󥹥ȥ饯��
    Component(int order = GENERAL_PURPOSE) throw();

        //�ǥ��ȥ饯��
    virtual ~Component(void) throw();

        //ͭ��Ƚ��
    static bool isValid(void) throw()
    {   return is_valid && SingletonBase::isValid();   }

        //����ݡ��ͥ�Ȥμ¹�
    static void executeComponents(OptionParameter & option);
    static void executeComponents(int argc, char * argv []);

        //�Хʡ���������
    static void        setBanner(std::string) throw(std::bad_alloc);
    static std::string getBanner(void)        throw(std::bad_alloc);

    /*
     *   ���٥�ȥϥ�ɥ�
     */

        //���ץ����Υѡ���
    virtual void parseOption(OptionParameter &)
    { parseOption(*Singleton<Directory>::getInstance()); }
    
    virtual void parseOption(Directory &) {}

        //����ݡ��ͥ�Ȥ�����
    virtual void body(void)        { body(*Singleton<Directory>::getInstance()); }
    virtual void body(Directory &) {}

        //�۾ｪλ�ϥ�ɥ�
    virtual void onFatalExit(void) {}



    TESTSUITE_PROTOTYPE(main)
};


#endif



