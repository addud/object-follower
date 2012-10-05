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
 *  @(#) $Id: clause.h,v 1.4 2003/12/20 06:51:58 takayuki Exp $
 */

// $Header: /home/CVS/configurator/base/clause.h,v 1.4 2003/12/20 06:51:58 takayuki Exp $

#ifndef CLAUSE_H
#define CLAUSE_H

#include "base/testsuite.h"
#include "base/parser.h"
#include "base/singleton.h"
#include "base/except.h"

#include <map>
#include <string>

#define INTEGER_CLAUSE_IDENTIFIER   "##INTEGER" //2Ϣ��#�ȼ��̻Ҥ�쵤�˼��Ф����ȤϤǤ��ʤ��Τ�̾�����Ťʤ뤳�ȤϤʤ�
#define LITERAL_CLAUSE_IDENTIFIER   "##STRING"
#define OPERATOR_CLAUSE_IDENTIFIER  "##OPERATOR"

    //��ʸ��ΰ����������륯�饹
class Clause
{
public:
        //����̾�����֤�°������Υޥå�
    typedef std::map<std::string, Clause *> map_type;

        //̾������
    class Namespace : public std::map<std::string, map_type>
    { public: SINGLETON_CONSTRUCTOR(Namespace) throw() {} };

protected:
    static map_type * getClauseMap(std::string ns) throw();

        //�ȡ����󤫤鼱��̾����������
    static std::string getClauseIdentifier(Token token) throw();

        //���Ȥ���Ͽ����
    void   addClause(std::string ns, std::string identifier) throw();

        //��ʬ��ʣ����leading identifier���б��դ���
    void   addMultipleClauses(std::string ns, std::string identifier_list) throw();

protected:  /* ���󥿥ե����� */

        //�ѡ�������
    virtual void before(const Token & first, Parser & p);
    virtual void body  (const Token & first, Parser & p) = 0;
    virtual void after (const Token & first, Parser & p);

        //�ѡ������Ի��β�������
    virtual void onFail(const Token & first, Parser & p) throw();

public:
    Clause(void) throw() {}
    virtual ~Clause(void) throw() {}

        //ͭ��Ƚ��
    inline bool isValid(void) const throw()
    {   return (this != 0);   }

        //��β���
    static bool parseClause(std::string ns, Parser & p);

        //first�ǻϤޤ��᤬���뤫
    static bool hasClause(std::string ns, std::string first) throw();

        //[�إ����] ��Ͽ����Ƥ�����ΰ������������
    static std::string makeClauseList(std::string ns, int width = 80) throw();

    TESTSUITE_PROTOTYPE(main)
};


    /*
     *   ��ŪAPI
     */
#define NAMESPACE_STATICAPI "StaticAPI"

class StaticAPI : public Clause
{
protected:

    virtual void before(const Token & first, Parser & p);
    virtual void after (const Token & first, Parser & p);

        //�ѡ������Ի��β�������
    virtual void onFail(const Token & first, Parser & p) throw();

public:
        //�ǥե���ȥ��󥹥ȥ饯�� (���⤷�ʤ�)
    StaticAPI(void) throw() {}      
        //API̾����ꤷ������ (regist����)
    StaticAPI(std::string apinamelist) throw()
    {   addMultipleClauses(NAMESPACE_STATICAPI, apinamelist);   }

    inline void regist(std::string apinamelist) throw()
    {   addMultipleClauses(NAMESPACE_STATICAPI, apinamelist);   }

        //��β���
    static bool parseStaticAPI(Parser & p)
    {   return Clause::parseClause(NAMESPACE_STATICAPI, p);   }

        //first�ǻϤޤ��᤬���뤫
    inline static bool hasStaticAPI(std::string first) throw()
    {   return Clause::hasClause(NAMESPACE_STATICAPI, first);   }

        //[�إ����] ��Ͽ����Ƥ�����ΰ������������
    inline static std::string makeClauseList(int width = 80) throw()
    {   return Clause::makeClauseList(NAMESPACE_STATICAPI, width);   }

        //�����å�
    static void skip(Parser & p, bool invalid_api = true) throw();

    TESTSUITE_PROTOTYPE(main)
};


    /*
     *   �ץ�ץ����ǥ��쥯�ƥ���
     */
#define NAMESPACE_DIRECTIVES "Directives"

class Directives : public Clause
{
protected:

    virtual void after(const Token & first, Parser & p) throw(Exception);

        //�ѡ������Ի��β�������
    virtual void onFail(const Token & first, Parser & p) throw();

public:
        //�ǥե���ȥ��󥹥ȥ饯�� (���⤷�ʤ�)
    Directives(void) throw() {}      
        //API̾����ꤷ������ (regist����)
    Directives(std::string apinamelist) throw()
    {   addMultipleClauses(NAMESPACE_DIRECTIVES, apinamelist);   }

    inline void regist(std::string apinamelist) throw()
    {   addMultipleClauses(NAMESPACE_DIRECTIVES, apinamelist);   }

        //��β���
    inline static bool parseDirectives(Parser & p)
    {   return Clause::parseClause(NAMESPACE_DIRECTIVES, p);   }

        //first�ǻϤޤ��᤬���뤫
    inline static bool hasDirectives(std::string first) throw()
    {   return Clause::hasClause(NAMESPACE_DIRECTIVES, first);   }

        //[�إ����] ��Ͽ����Ƥ�����ΰ������������
    inline static std::string makeClauseList(int width = 80) throw()
    {   return Clause::makeClauseList(NAMESPACE_DIRECTIVES, width);   }

    TESTSUITE_PROTOTYPE(main)
};

#endif



