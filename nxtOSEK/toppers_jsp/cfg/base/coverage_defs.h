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
 *  @(#) $Id: coverage_defs.h,v 1.4 2003/12/15 07:32:13 takayuki Exp $
 */

/*
    #ifdef�ط�
    coverage_defs�ϡ�undefs�ǲ���������Ȥ��ɤ߹����礬����Τǡ�
        �ѡ��Ȥ򤤤��Ĥ���ʬ�䤷�Ƥ���.
        - COVERAGE      : ���Х�å���ǽ����Ѥ��뤫�ɤ���
        - COVERAGE_H    : coverage.cpp�˴�Ϣ������ʬ�ǡ�¿���������ƤϺ�����
        - COVERAGE_DEFS : ���Х�å��˴�Ϣ������ʬ�ǡ�coverage_undefs.h��undef�Ǥ����⤦����coverage_defs.h���ɤ�Ǥ�����פʤ��
*/


#ifdef COVERAGE

#include "base/singleton.h"

    /* �إå� */
#include <string>
#include <map>
#include <set>
#include <iostream>


#ifndef COVERAGE_H
#define COVERAGE_H
/*
 *   ��ñ�ʥ��Х�å������å�
 */

class Coverage {
public:
        /* �����ݻ����륯�饹 */
    class Location {
    protected:
        const char *  filename;
        unsigned int  lineno;
        const char *  additional;

    public:
        Location(const char * _filename, unsigned int _lineno, const char * _additional = "") : filename(_filename), lineno(_lineno), additional(_additional) {}
        Location(const Location & src) : filename(src.filename), lineno(src.lineno), additional(src.additional) {}

        inline Location & operator = (const Location & right)
        {
            filename   = right.filename;
            lineno     = right.lineno;
            additional = right.additional;

            return *this;
        }

        inline bool operator == (const Location & right) const
        {   return lineno == right.lineno && std::string(filename).compare(right.filename) == 0 && std::string(additional).compare(right.additional) == 0;   }

        inline bool operator < (const Location & right) const
        {
            if(lineno < right.lineno)
                return true;
            if(std::string(filename).compare(right.filename) < 0)
                return true;

            return false;
        }

        inline std::string getFilename(void) const
        {   return std::string(filename);   }

        inline unsigned int getLineno(void) const
        {   return lineno;   }

        inline std::string getAdditional(void) const
        {   return std::string(additional);   }

            //�ե����ޥåȺѤߥե�������־���μ��� filename:lineno(additional)
        std::string getDetails(void) const;
    };

        //ʬ�����Х�å�Ƚ��Υ١������饹
    class BranchBase {
    protected:
        BranchBase(const Location & location) throw();   //���Ǥ���Ͽ
        static BranchBase * find(const Location & location) throw();     //location�˰��פ������Ǥμ���

    public:
        virtual ~BranchBase(void) throw() {}                        //�ǥ��ȥ饯��
        virtual bool checkValidity(void) const throw(...) = 0;      //������Ƚ��
        virtual std::string getDetails(void) const throw(...) = 0;  //�ǡ���ɽ��
    };

        //if-statement�˰��ä����륯�饹
    class If : public BranchBase {
    protected:
        bool true_case;
        bool false_case;

        If(const Location & location) throw(); //branch��ͳ��̵�������������ʤ�

    public:
        virtual bool checkValidity(void) const throw();         //��������Ƚ��
        virtual std::string getDetails(void) const throw();     //�ǡ���ɽ��

        static bool branch(const Location & location, bool expression) throw();
    };
    
        //while-statement�˰��ä����륯�饹
    class While : public BranchBase {
    protected:
        bool valid;

        While(const Location & location) throw();
    public:
        virtual bool checkValidity(void) const throw();         //��������Ƚ��
        virtual std::string getDetails(void) const throw();     //�ǡ���ɽ��

        static bool branch(const Location & location, bool expression) throw();
    };

        //switch-statement�˰��ä����륯�饹
    class Switch : public BranchBase {
    protected:
        std::set<int> checkpoint;

        Switch(const Location & location) throw();
        static void _branch(const Location & location, int expression) throw();

    public:
        virtual bool checkValidity(void) const throw();         //��������Ƚ��
        virtual std::string getDetails(void) const throw();     //�ǡ���ɽ��

        template<class T>
        static T branch(const Location & location, T expression) throw()
        {
            _branch(location, (int)expression);
            return expression;
        }
    };


protected:
    class BranchMap : public std::map<Location, BranchBase *> {
    public:
        SINGLETON_CONSTRUCTOR(BranchMap) {}
        ~BranchMap(void) throw();
    
    };
    class NewBranchList : public std::list<BranchBase *>
    {   public: SINGLETON_CONSTRUCTOR(NewBranchList) {}   };

        //���ܤ�ɽ��
    static std::string getBranchName(BranchBase * node);

public:
        //�����̲ᤷ�����ɤ����Υ����å�
    static bool checkValidity(void);

        //���Ƥι��ܤ�ɽ��
    static void printCoverage(std::ostream & out);

};

#endif /* COVERAGE_H */


#ifndef COVERAGE_DEFS
#define COVERAGE_DEFS

#define if(x)    i##f(Coverage::If::branch(Coverage::Location(__FILE__, __LINE__, "if"), (x) ? true : false))
#define while(x) w##hile(Coverage::While::branch(Coverage::Location(__FILE__, __LINE__, "while"), (x) ? true : false))
#define switch(x) s##witch(Coverage::Switch::branch(Coverage::Location(__FILE__, __LINE__, "switch"), (x)))

#endif  /* COVERAGE_DEFS */

#else

#include <iostream>

#ifndef COVERAGE_H
#define COVERAGE_H
class Coverage {
public:
    static bool checkValidity(void) { return true; }
    static void printCoverage(std::ostream &) {}
};
#endif /* COVERAGE_H */

#endif

