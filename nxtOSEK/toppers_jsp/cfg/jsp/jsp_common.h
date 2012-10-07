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
 *  @(#) $Id: jsp_common.h,v 1.8 2004/09/06 15:00:49 honda Exp $
 */

// $Header: /home/CVS/configurator/jsp/jsp_common.h,v 1.8 2004/09/06 15:00:49 honda Exp $


#ifndef JSP_COMMON_H
#define JSP_COMMON_H

#include "base/testsuite.h"

#include "base/mpstrstream.h"
#include "base/collection.h"
#include "base/except.h"
#include "base/event.h"

#include <string>


namespace ToppersJsp {

        //�����ͥ빽���ե�����
    class SpecialtyFile : public MultipartStream, public RuntimeObject
    {
    protected:
        SpecialtyFile(void) throw();

        template<class T>
        static T * createInstance(std::string filename) throw(Exception)
        {
            T * old;
            T * result = 0;

                //ROT��Ͽ��� ���֥������Ⱥ�� (ͣ�������ݾ� (�����ɥ��󥰥�ȥ�ǤϤʤ�) )
            old = dynamic_cast<T *>(RuntimeObjectTable::getInstance(typeid(T)));
            if(old != 0)
                delete old;

            result = new(std::nothrow) T;
            if(result == 0)
                ExceptionMessage("Internal error : Object creation failure [ToppersJsp::KernelCfg::createKernelCfg]","�������顼 : ���֥����������������顼 [createKernelCfg]") << throwException;

            try {
                result->setFilename(filename);
            }
            catch(...) {
                if(result != 0)
                    delete result;
                throw;
            }
            return result;
        }

    };


    /*
     *  Visual C++ 6.0 : fatal error C1001: INTERNAL COMPILER ERROR (msc1.cpp:1794) �к� 
     *    (�Ȥ�����ꡢ¿����Ͽ���Ƥ�Ť����󥹥��󥹤���Ͽ�����å��򤷤ʤ�)
     */
#if defined(_MSC_VER) && (_MSC_VER < 1300)
#  define SPECIALTY_FILE(x)                                                             \
    class x : public SpecialtyFile {                                                    \
        public:                                                                         \
            struct CreationEvent { class x * file; };                                   \
            static inline x * createInstance(std::string filename) throw(Exception)     \
            {                                                                           \
                x * instance = new(std::nothrow) x;                                     \
                if(instance != 0)                                                       \
                    instance->setFilename(filename);                                    \
                return instance;                                                        \
            }                                                                           \
    }
#else
#  define SPECIALTY_FILE(x)                                                             \
    class x : public SpecialtyFile {                                                    \
        public:                                                                         \
            struct CreationEvent { class x * file; };                                   \
            static inline x * createInstance(std::string filename) throw(Exception)     \
            {   return SpecialtyFile::createInstance<x>(filename);   }                  \
    }
#endif

        //TOPPERS/JSP�Υ���ե�����졼�����ǽФƤ����ü�ʥե�����
    SPECIALTY_FILE(KernelCfg);
    SPECIALTY_FILE(KernelID);

        //�С������֤�ۤ����Ѵ��ʤ�
    std::string conv_includefile(std::string file) throw(); //���󥯥롼�ɥե�����̾
    std::string conv_kernelobject(std::string obj) throw(); //�����ͥ���ѿ�̾

        //����ʤ�
//  std::string get_agreement(std::string filename = "") throw();   //ʸ���μ���
}

#endif

