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
 *  @(#) $Id: option.h,v 1.5 2003/12/20 06:51:58 takayuki Exp $
 */

// $Header: /home/CVS/configurator/base/option.h,v 1.5 2003/12/20 06:51:58 takayuki Exp $

#ifndef OPTION_H
#define OPTION_H

#include "base/testsuite.h"
#include "base/singleton.h"

#include <string>
#include <vector>
#include <map>

#define DEFAULT_PARAMETER "#default"

using namespace std;

/*
 *   ���ץ����ѥ�᡼����������륯�饹
 */
class OptionParameter
{
public:
    class OptionItem : public std::string
    {
    protected:
        bool                      checked;  //���Ѥ������ɤ���
        std::vector<std::string>  param;    //���ץ����

    public:
            //���󥹥ȥ饯��
        OptionItem(void) throw() : string(DEFAULT_PARAMETER), checked(false) {}
        OptionItem(const std::string & name) throw() : string(name), checked(false) {}
        OptionItem(const OptionItem & src) throw() : string(src), checked(src.checked), param(src.param) {}

            //���ץ����ѥ�᡼������Ϥ���OptionItem����������
        static bool createItem(OptionItem & item, string & argv);

            //�̤�OptionItem�����ĥѥ�᡼����ʬ���ɲä���
        void mergeItem(const OptionItem & src);

            //�ѥ�᡼�����ɲ�
        inline void addParameter(const std::string & src) throw()
        {   param.push_back(src);   }

            //�ѥ�᡼�����μ���
        inline size_t countParameter(void) const throw()
        {   return param.size();    }

            //�ѥ�᡼������äƤ��뤫�ɤ���
        inline bool hasParameter(void) const throw()
        {   return countParameter() != 0;   }

            //���֤���ꤷ�ƥѥ�᡼���򻲾� (̵���ʰ��֤��ȶ�ʸ��)
        inline std::string operator[](std::vector<std::string>::size_type offset) const throw()
        {
            string result;

            if(offset < countParameter())
                result = param[offset];

            return result;
        }

            //���Υ��ץ�������Ѥ������Ȥ򵭤� (OptionParameter��𤷤Ƥ����ѤΤߤʤΤ� "_" ��Ĥ��Ƥ���)
        inline void _check(void) throw()
        {   checked = true;   }

            //���Υ��ץ����˿��ä����ɤ���
        inline bool isChecked(void) const throw()
        {   return checked;   }

            //ͭ�����ɤ��� (�ʤʤ���̵��)
        inline bool isValid(void) const throw()
        {   return !empty();   }

            //̵���ʥ��ץ���󥢥��ƥ������
        static OptionItem createInvalidItem(void) throw();

            //���ƤΥѥ�᡼����礷����Τ����
        std::string getParameters(std::string punctuator = " ") const throw();

            //�ѥ�᡼���θĿ�������å�
        bool checkParameterCount(size_t count, bool allow_zero = false) const throw();

        TESTSUITE_PROTOTYPE(main)
    };

protected:
        //���ץ������Ǽ�����ѿ�
    std::map<std::string, OptionItem> container;    //set::begin()��const_iterator�����֤��ʤ��Τǻ����ʤ�map���Ѥ��� (������ͤ����������...)

        //�ץ����̾��
    std::string program_name;

        //���ޥ�ɥ饤����Ϥ��줿�������Τ��
    std::string cmdline;    

        //�ǥե���ȥ��󥹥ȥ饯�� (�ƥ�����)
    OptionParameter(void) throw() {}

        //���Ǥθ���
    std::map<std::string, OptionItem>::iterator _find(const std::string & name, bool check = true) throw();

public:

        //���󥰥�ȥ󥳥󥹥ȥ饯��
    SINGLETON_CONSTRUCTOR(OptionParameter) throw() {}

        //���ץ����ѥ�᡼���Υѡ���
    bool parseOption(int _argc, char const * const * _argv, char const * _default = NULL) throw();

        //���ƤΥ��ץ���󤬻��Ѥ��줿���ɤ����γ�ǧ
    bool validateOption(void) const throw();

        //���Ѥ���ʤ��ä����ץ����������
    std::string getInvalidOptions(void) const throw();

        //�����ƥ�ο��������
    inline size_t countItem(void) const throw()
    {   return container.size();   }

        //���ץ���󥢥��ƥ�λ���
    OptionItem get(const std::string & name, bool check = true) throw();
    
    inline OptionItem operator [] (const std::string & name) throw()
    {   return get(name);   }
    
    inline OptionItem operator [] (const char * name) throw()
    {   return get(string(name));   }

        //���ץ�����̵ͭ�θ���
    inline bool find(std::string name) throw()
    {   return get(name).isValid(); }


        //���ȥޡ�����Ĥ���
    inline bool check(const std::string & name) throw()
    {   return _find(name) != container.end();   }

    inline bool check(const char * name) throw()
    {   return check(string(name));   }

        //�ץ����̾���������
    inline const std::string & getProgramName(void) const throw()
    {   return program_name;    }

        //������򤽤Τޤ޼������� (�ץ����̾�ϴޤޤ�)
    inline const std::string & getCommandLine(void) const throw()
    {   return cmdline;   }

    TESTSUITE_PROTOTYPE(main)
};

    /* �����ƥ����ñ���OptionParameter���뤿��δؿ� */
inline OptionParameter & getOptionParameter(void) throw()
{   return *Singleton<OptionParameter>::getInstance();   }

#endif


