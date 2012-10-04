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
 *  @(#) $Id: clause.cpp,v 1.3 2003/12/15 07:32:13 takayuki Exp $
 */

// $Header: /home/CVS/configurator/base/clause.cpp,v 1.3 2003/12/15 07:32:13 takayuki Exp $

#include "base/clause.h"
#include "base/message.h"

using namespace std;

/*
 *   ��ʸ��ΰ����������륯�饹
 */

    //���ꤷ��̾�����֤���ޥåפ����
Clause::map_type * Clause::getClauseMap(string name) throw()
{
    map_type * result = NULL;
    Namespace::iterator scope;

    Namespace * const ns = Singleton<Namespace>::getInstance(nothrow);
    if(ns!= 0) {
        scope = ns->find(name);
        if(scope != ns->end())
            result = &(scope->second);
    }

    return result;
}

    //�����Ͽ
void Clause::addClause(string _namespace, string _identifier) throw()
{
    if(isValid()) {
        Namespace * const ns = Singleton<Namespace>::getInstance(nothrow);
        if(ns != 0)
            (*ns)[_namespace][_identifier] = this;
//          ns->operator [](_namespace).insert(map_type::value_type(_identifier, this));        //��񤭤����ʤ����
    }
}

    //�ȡ�������Ф����ἱ��̾����������
string Clause::getClauseIdentifier(Token token) throw()
{
    string result;

    switch(token.getType()) {
        case Token::IDENTIFIER:
        case Token::PUNCTUATOR:
            result = token.getLiteral();    
            break;
        case Token::INTEGER:
            result.assign(INTEGER_CLAUSE_IDENTIFIER);
            break;
        case Token::LITERAL:
            result.assign(LITERAL_CLAUSE_IDENTIFIER);
            break;
        case Token::OPERATOR:
            result.assign(OPERATOR_CLAUSE_IDENTIFIER);
            break;
        default:
            result = string();
    }

    return result;
}

    //��β���
bool Clause::parseClause(string ns, Parser & p)
{
    bool result = false;
    map_type::iterator scope;
    map_type * clause = getClauseMap(ns);

        //��������
    if(clause == 0 || p.eof())
        return false;

        //�ȡ����󤫤鼱��̾����Ф�
    Token  token;
    string identifier;

    token      = p.getToken();
    identifier = getClauseIdentifier(token);
    
        //��������μ¹�
    scope = clause->find(identifier);
    if(scope != clause->end()) {

            //�ǥХå��ѥ�å���������
        DebugMessage("Clause::parseClause(%) - %\n") << ns << identifier;

        try {
            scope->second->before(token, p);
            scope->second->body(token, p);  //�ҥåȤ�����Τ�¹�
            scope->second->after(token, p);
            result = true;
        }
        catch(...) {
            scope->second->onFail(token, p);    //���Ԥ����Ȥ��θ�����򤪴ꤤ����
            throw;
        }
    }
    else
        p.putback(token);   //���̻Ҥ˥ޥå������Τ���Ͽ����Ƥ��ʤ�

    return result;
}

    //first�ǻϤޤ��᤬���뤫
bool Clause::hasClause(string ns, string first) throw()
{
    map_type * clause = getClauseMap(ns);
    if(clause == 0)
        return false;

    return clause->find(first) != clause->end();
}

    //�ѡ���������
void Clause::before(const Token &, Parser &)
{}

    //�ѡ��������
void Clause::after(const Token &, Parser &)
{}

    //ɸ����㳰ȯ�����θ�����롼����
void Clause::onFail(const Token &, Parser & p) throw()
{
    Token token;

        //�Ǹ�ޤ��ɤߤ���
    while(!p.eof())
        token = p.getToken();
}

    //���ʣ���μ���̾���б��դ���
void Clause::addMultipleClauses(string ns, string id_list) throw()
{
    string            id;
    string::size_type pos;
    string::size_type prev;

        //����ޤǶ��ڤ�줿�������addClause��ȯ��
    if(isValid()) {
        prev = 0;
        do {
            pos = id_list.find_first_of(',', prev);
            id  = id_list.substr(prev, pos - prev);

            addClause(ns, id);

            prev = pos + 1;
        } while(pos != string::npos);
    }
}

    //[�إ����] ��Ͽ����Ƥ�����ΰ������������
std::string Clause::makeClauseList(string ns, int width) throw()
{
    string result;
    map_type::iterator scope;
    map_type * clause = getClauseMap(ns);
    size_t max_length = 0;

        //�����ʸ����Ĺ�����
    scope = clause->begin();
    while(scope != clause->end()) {
        size_t i = scope->first.size();
        if(i > max_length)
            max_length = i;
        ++ scope;
    }

        //���������
    size_t max_column = width/(max_length+1);
    size_t column = 0;
    scope = clause->begin();
    while(scope != clause->end()) {
        size_t i = scope->first.size();

        result += scope->first;

        ++ column;
        ++ scope;

            //��������
        if(column == max_column || scope == clause->end())
            result += '\n';
        else {
            result += ',';
            result += string(max_length - i, ' ');
        }
    }

    return result;
}


    /*
     *   ��ŪAPI
     */

    //�ѡ���������
void StaticAPI::before(const Token & first, Parser & p)
{
    Token token = p.getToken();
    if(token != Token::LPAREN) {
        ExceptionMessage("StaticAPI [%] lacks left-parenthesis '('.","��ŪAPI[%]�ˤϳ��'('���礱�Ƥ���") << first.getLiteral() << throwException;
    }
}

    //�ѡ��������
void StaticAPI::after(const Token & first, Parser & p)
{
    Token token = p.getToken();
    if(token != Token::RPAREN) {
        ExceptionMessage("StaticAPI [%] lacks right-parenthesis ')'.","��ŪAPI[%]�ˤϳ��')'���礱�Ƥ���") << first.getLiteral() << throwException;
    }
    else {
        token = p.getToken();
        if(token != ";")
            ExceptionMessage("StaticAPI [%] lacks ';' at the end of declaration.","��ŪAPI[%]��������';'���礱�Ƥ���") << first.getLiteral() << throwException;
    }
}

    //���Ի��β�������
void StaticAPI::onFail(const Token & , Parser & p) throw()
{   skip(p, false);   }


    //�����å�
    //   invalid_api : ���˺ǽ���ɤ߽Ф����API��̵��
void StaticAPI::skip(Parser & p, bool invalid_api) throw()
{
        //���ߥ���� or ������ŪAPI�νи��ޤ�
    Token token;
    bool  condition; //�����к�

    if(invalid_api)
        token = p.getToken();   //����API̾���ɤ����Ф�

    do {
        token = p.getToken(true);

        condition = (!token.isValid()) ||                                                   //̵���ʥȡ�����
                    (token == Token::PUNCTUATOR && token == ";") ||                         //���ߥ����
                    (token == Token::IDENTIFIER && hasStaticAPI(token.getLiteral()));       //��ŪAPI��

    } while(!condition);

    if(token == Token::IDENTIFIER)
        p.putback(token);
}

    /*
     *   �ץ�ץ����ǥ��쥯�ƥ���
     */

    //�ѡ��������
void Directives::after(const Token & first, Parser & p) throw(Exception)
{
    Token token = p.getToken(true);
    if(!token.isValid() || !p.isLocatedonHeadofLine())
        ExceptionMessage("Directive [%] has a wrong parameter or misses a new-line.","�ǥ��쥯�ƥ���[%]�������ʰ��������뤫�����Ԥ��ʤ�") << first.getLiteral() << throwException;
}

    //�ѡ������Ի��β�������
void Directives::onFail(const Token & , Parser & p) throw()
{
        //���β��Ԥޤ��ɤ����Ф�
    Token token;

    do {
        token = p.getToken(true);
    } while(token.isValid() && !p.isLocatedonHeadofLine());
}

/************************************************* �ƥ��ȥ������� *************************************************/

#ifdef TESTSUITE

#include "coverage_undefs.h"
#include <sstream>

namespace {
    class Clause_test : public Clause
    {
    public:
        Token        first;
        Token        second;
        bool         throw_exception;

        Clause_test(void) throw() : first(Token::ERROR), throw_exception(false) {}

        void body(const Token & _first, Parser & _p)
        {
            TestSuite::check("Clause_test::body");
            first = _first;
            second = _p.getToken();
            if(throw_exception)
                throw 0;
        }

        void before(const Token & , Parser & )
        {
            TestSuite::check("Clause_test::before");
        }

        void after(const Token &, Parser &)
        {
            TestSuite::check("Clause_test::after");
        }

        void onFail(const Token & _first, Parser & p) throw()
        {
            TestSuite::check("Clause_test::onFail");
            first = _first;
        }

        void onFail_super(const Token & _first, Parser & p) throw()
        {   Clause::onFail(_first, p);   }
    };
}

TESTSUITE(main, Clause)
{
    SingletonBase::ContextChain chain;
    chain.saveContext<Namespace>();

    BEGIN_CASE("getClauseIdentifier","getClauseIdentifier") {
        BEGIN_CASE("1","���̤μ��̻ҤϤ��Τޤޤ���Ȥˤʤ�") {
            Token token(Token::IDENTIFIER, "test");

            if(getClauseIdentifier(token).compare("test") != 0)
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("2","���ͤ���Ȥ˴ط��ʤ�" INTEGER_CLAUSE_IDENTIFIER "���֤�") {
            Token token(Token::INTEGER, "", "", 0);

            if(getClauseIdentifier(token).compare(INTEGER_CLAUSE_IDENTIFIER) != 0)
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("3","��ƥ�����Ȥ˴ط��ʤ�" LITERAL_CLAUSE_IDENTIFIER "���֤�") {
            Token token(Token::LITERAL, "");

            if(getClauseIdentifier(token).compare(LITERAL_CLAUSE_IDENTIFIER) != 0)
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("4","�黻�Ҥ���Ȥ˴ط��ʤ�" OPERATOR_CLAUSE_IDENTIFIER "���֤�") {
            Token token(Token::OPERATOR);

            if(getClauseIdentifier(token).compare(OPERATOR_CLAUSE_IDENTIFIER) != 0)
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("5","����Υȡ�����ˤ϶�ʸ��(==�����)���֤�") {
            Token token(Token::SPACE);

            if(!getClauseIdentifier(token).empty())
                TEST_FAIL;
        } END_CASE;

        TEST_CASE("6","���顼�ȡ�����ˤ϶�ʸ��(==�����)���֤�", getClauseIdentifier(Token(Token::ERROR)).empty());
        TEST_CASE("7","EOS�ȡ�����ˤ϶�ʸ��(==�����)���֤�",   getClauseIdentifier(Token(Token::END_OF_STREAM)).empty());

    } END_CASE;

    BEGIN_CASE("getClauseMap","getClauseMap") {
        BEGIN_CASE("1","������Ͽ���Ƥ��ʤ����֤ˤ�NULL���֤�") {
            chain.renewInstance();
            if(Clause::getClauseMap("unknown") != 0)
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("2","���Ǥ��������0���֤�") {
            chain.renewInstance();
            Singleton<Namespace>::getInstance()->operator []("test");

            if(Clause::getClauseMap("test") == 0)
                TEST_FAIL;
        } END_CASE;
    } END_CASE;

    BEGIN_CASE("addClause","addClause") {
        BEGIN_CASE("1","���֥������Ȥ���Ͽ�Ǥ���") {
            chain.renewInstance();
            Clause_test ct;
            Clause_test ct2;

            BEGIN_CASE("1","���̤���Ͽ����") {
                ct.addClause("test","first_literal");

                TEST_CASE("1","̾�����֤������Ƥ���", Singleton<Namespace>::getInstance()->size() == 1);
                TEST_CASE("2","\"test\"�Ȥ������֤�����", Singleton<Namespace>::getInstance()->find("test") != Singleton<Namespace>::getInstance()->end());
                TEST_CASE("3","getClause�ǥ��ɥ쥹������", Clause::getClauseMap("test") != 0); 
                TEST_CASE("4","̾�����֤���ο���1",  Clause::getClauseMap("test")->size() == 1);
                TEST_CASE("5","\"first_literal\"�ΥΡ��ɤ�����", Clause::getClauseMap("test")->find("first_literal") != Clause::getClauseMap("test")->end());
                TEST_CASE("6","��Ϣ�դ���줿�ͤ�������", (*Clause::getClauseMap("test"))["first_literal"] == &ct);
            } END_CASE;

            BEGIN_CASE("2","2���ܤ���Ͽ����") {
                ct2.addClause("test","second_literal");

                TEST_CASE("1","̾�����֤������Ƥ��ʤ�", Singleton<Namespace>::getInstance()->size() == 1);
                TEST_CASE("2","\"test\"�Ȥ������֤�����", Singleton<Namespace>::getInstance()->find("test") != Singleton<Namespace>::getInstance()->end());
                TEST_CASE("3","̾�����֤���ο���2",  Clause::getClauseMap("test")->size() == 2);
                TEST_CASE("4","\"second_literal\"�ΥΡ��ɤ�����", Clause::getClauseMap("test")->find("second_literal") != Clause::getClauseMap("test")->end());
                TEST_CASE("5","��Ϣ�դ���줿�ͤ�������", (*Clause::getClauseMap("test"))["second_literal"] == &ct2);
            } END_CASE;

            BEGIN_CASE("3","2���ܤ�1���ܤǾ����Ͽ����") {
                ct.addClause("test","second_literal");
                TEST_CASE("1","��񤭤���Ƥ���", (*Clause::getClauseMap("test"))["second_literal"] == &ct);
            } END_CASE;

            BEGIN_CASE("4","�㤦̾�����֤���Ͽ����") {
                ct.addClause("TEST","first_literal");

                TEST_CASE("1","̾�����֤������Ƥ���", Singleton<Namespace>::getInstance()->size() == 2);
                TEST_CASE("2","\"TEST\"�Ȥ������֤�����", Singleton<Namespace>::getInstance()->find("TEST") != Singleton<Namespace>::getInstance()->end());
                TEST_CASE("3","getClause�ǥ��ɥ쥹������", Clause::getClauseMap("TEST") != 0); 
                TEST_CASE("4","̾�����֤���ο���1",  Clause::getClauseMap("TEST")->size() == 1);
                TEST_CASE("5","\"first_literal\"�ΥΡ��ɤ�����", Clause::getClauseMap("TEST")->find("first_literal") != Clause::getClauseMap("TEST")->end());
                TEST_CASE("6","��Ϣ�դ���줿�ͤ�������", (*Clause::getClauseMap("TEST"))["first_literal"] == &ct);
            } END_CASE;

        } END_CASE;

        BEGIN_CASE("2","̵���ʥ��֥������Ȥ���Ͽ����ʤ�") {
            chain.renewInstance();

            ((Clause_test *)0)->addClause("test","first_literal");

            TEST_CASE("1","̾�����֤������Ƥ��ʤ�", Singleton<Namespace>::getInstance()->size() == 0);
        } END_CASE;

    } END_CASE;

    BEGIN_CASE("hasClause","hasClause") {
        Clause_test ct;
        chain.renewInstance();

        TEST_CASE("1","�������Ǥ��ʤ��Ȥ��ˤ������ư���", !Clause::hasClause("dummy","null"));

        ct.addClause("test","first_literal");

        TEST_CASE("2","��Ͽ�������Ǥ�õ����true���֤�", Clause::hasClause("test","first_literal"));
        TEST_CASE("3","¸�ߤ��ʤ����Ǥ�false���֤�", !Clause::hasClause("dummy","null"));
    } END_CASE;

    BEGIN_CASE("addMultipleClauses","addMultipleClauses") {
        BEGIN_CASE("1","ñ��������Ͽ�Ǥ���") {
            chain.renewInstance();
            Clause_test ct;

            ct.addMultipleClauses("test","first");

            TEST_CASE("1","��Ͽ�����᤬����", Clause::hasClause("test","first"));
        } END_CASE;

        BEGIN_CASE("2","ʣ���������Ͽ����") {
            chain.renewInstance();
            Clause_test ct;

            ct.addMultipleClauses("test","first,second,third");

            TEST_CASE("1","��Ͽ�����᤬����", Clause::hasClause("test","first"));
            TEST_CASE("2","��Ͽ�����᤬����", Clause::hasClause("test","second"));
            TEST_CASE("3","��Ͽ�����᤬����", Clause::hasClause("test","third"));
        } END_CASE;

    } END_CASE;

    BEGIN_CASE("Clause::onFail","Clause::onFail") {
        stringstream buf;
        Parser p(&buf, "test");
        Token token;
        Clause_test ct;

        buf.str("first second third 4 5 6 siebt acht neunt 0xa");

        ct.onFail_super(token, p);
        TEST_CASE("1","���ȥ꡼��ϺǸ�ޤǿʤ�Ǥ���", p.eof());
    } END_CASE;

    BEGIN_CASE("parseClause","parseClause") {
        chain.renewInstance();
        Clause_test ct;

        ct.addClause("test","first");

        BEGIN_CASE("1","̾�����֤����򤷤����������¹ԤǤ���") {
            stringstream buf;
            Parser p(&buf, "test");
            buf.str("first second");

            TestSuite::clearCheckpoints();
            TEST_CASE("1","�ؿ�����������", Clause::parseClause("test", p));
            TEST_CASE("2","Clause::before���¹Ԥ���Ƥ���", TestSuite::isReached("Clause_test::before"));
            TEST_CASE("3","Clause::body���¹Ԥ���Ƥ���", TestSuite::isReached("Clause_test::body"));
            TEST_CASE("4","body��first��������", ct.first == "first");
            TEST_CASE("5","body���ɤ߽Ф����ȡ�����������", ct.second == "second");
            TEST_CASE("6","Clause::after���¹Ԥ���Ƥ���", TestSuite::isReached("Clause_test::after"));
        } END_CASE;

        BEGIN_CASE("2","��ν�������㳰���������onFail���ƤФ��") {
            stringstream buf;
            Parser p(&buf, "test");
            buf.str("first second");

            ct.throw_exception = true;
            TestSuite::clearCheckpoints();

            bool result = false;
            try { Clause::parseClause("test", p); }
            catch(...){ result = true; }

            TEST_CASE("1","�㳰��������", result);
            TEST_CASE("2","Clause::body���¹Ԥ���Ƥ���", TestSuite::isReached("Clause_test::body"));
            TEST_CASE("3","Clause::onFail���¹Ԥ���Ƥ���", TestSuite::isReached("Clause_test::onFail"));
        } END_CASE;

        BEGIN_CASE("3","¸�ߤ��ʤ�̾�����֤���ꤹ��") {
            stringstream buf;
            Parser p(&buf, "test");
            buf.str("first second");

            TEST_CASE("1","�ؿ��ϼ��Ԥ���", !Clause::parseClause("unknown", p));
        } END_CASE;

        BEGIN_CASE("4","EOF��ã�������ȥ꡼�����ꤹ��") {
            stringstream buf;
            Parser p(&buf, "test");
            buf.str("");
            buf.get();

            TEST_CASE("0","[����]���ȥ꡼��Ͻ�ü��ã���Ƥ���", buf.eof());
            TEST_CASE("1","�ؿ��ϼ��Ԥ���", !Clause::parseClause("unknown", p));
        } END_CASE;
    } END_CASE;

    chain.restoreContext();
}




namespace {
    class StaticAPI_test : public StaticAPI
    {
    public:
        StaticAPI_test(void) throw() : StaticAPI() {}
        StaticAPI_test(string src) throw() : StaticAPI(src) {}

        void body(const Token & , Parser &) { TestSuite::check("StaticAPI::body"); }
        void onFail_super(const Token & first, Parser & p) throw() { StaticAPI::onFail(first, p); }
    };
}

TESTSUITE(main, StaticAPI)
{
    Singleton<Namespace>::Context context;
    Singleton<Namespace>::saveContext(context);

    Exception::setThrowControl(true);

    BEGIN_CASE("regist","regist") {
        BEGIN_CASE("1","ñ���̾������ꤷ����Ͽ�Ǥ���") {
            Singleton<Namespace>::renewInstance();
            StaticAPI_test api;

            api.regist("VTST_API");

            TEST_CASE("1","API����������Ͽ�Ǥ��Ƥ���",StaticAPI::hasStaticAPI("VTST_API"));
        } END_CASE;

        BEGIN_CASE("2","ʣ����̾������ꤷ����Ͽ����") {
            Singleton<Namespace>::renewInstance();
            StaticAPI_test api;

            api.regist("API_1,API_2,API_3");

            TEST_CASE("1","API����������Ͽ�Ǥ��Ƥ���",StaticAPI::hasStaticAPI("API_1"));
            TEST_CASE("2","API����������Ͽ�Ǥ��Ƥ���",StaticAPI::hasStaticAPI("API_2"));
            TEST_CASE("3","API����������Ͽ�Ǥ��Ƥ���",StaticAPI::hasStaticAPI("API_3"));
        } END_CASE;

        BEGIN_CASE("3","��񤭤���") {
            Singleton<Namespace>::renewInstance();
            StaticAPI_test api;
            StaticAPI_test api2;
            StaticAPI_test api3;

            api.regist("test");
            TEST_CASE("1","API����������Ͽ�Ǥ��Ƥ���",StaticAPI::hasStaticAPI("test"));
            TEST_CASE("2","API�ϥ�ɥ餬������", (*StaticAPI::getClauseMap(NAMESPACE_STATICAPI))["test"] == &api);

            api2.regist("test");
            TEST_CASE("3","API�ϥ�ɥ餬��񤭤���Ƥ���", (*StaticAPI::getClauseMap(NAMESPACE_STATICAPI))["test"] == &api2);

            api3.regist("test");
            TEST_CASE("4","API�ϥ�ɥ餬��񤭤���Ƥ���", (*StaticAPI::getClauseMap(NAMESPACE_STATICAPI))["test"] == &api3);
        } END_CASE;

        BEGIN_CASE("4","���󥹥ȥ饯������Ͽ") {
            Singleton<Namespace>::renewInstance();
            StaticAPI_test api("API1,API2,API3");

            TEST_CASE("1","API����������Ͽ�Ǥ��Ƥ���",StaticAPI::hasStaticAPI("API1"));
            TEST_CASE("2","API����������Ͽ�Ǥ��Ƥ���",StaticAPI::hasStaticAPI("API2"));
            TEST_CASE("3","API����������Ͽ�Ǥ��Ƥ���",StaticAPI::hasStaticAPI("API3"));
        } END_CASE;
    } END_CASE;

    BEGIN_CASE("parseStaticAPI","parseStaticAPI") {
        BEGIN_CASE("1","��ŪAPI�������������Ǥ���") {
            Singleton<Namespace>::renewInstance();
            stringstream buf;
            StaticAPI_test api("API");

            buf.str("API();");
            Parser p(&buf, "test");

            TestSuite::clearCheckpoints();
            bool result = true;
            try { StaticAPI::parseStaticAPI(p); }
            catch(...) { result = false; }

            TEST_CASE("1","�㳰�ϵ���ʤ�", result);
            TEST_CASE("2","��ŪAPI�����Τ��ƤФ�Ƥ���", TestSuite::isReached("StaticAPI::body"));
        } END_CASE;

        BEGIN_CASE("2","'('˺����㳰") {
            Singleton<Namespace>::renewInstance();
            stringstream buf;
            StaticAPI_test api("API");

            buf.str("API);");
            Parser p(&buf, "test");

            TestSuite::clearCheckpoints();
            bool result = false;
            try { StaticAPI::parseStaticAPI(p); }
            catch(...) { result = true; }

            TEST_CASE("1","�㳰������", result);
            TEST_CASE("2","��ŪAPI�����Τ��ƤФ�ʤ�", !TestSuite::isReached("StaticAPI::body"));
        } END_CASE;

        BEGIN_CASE("3","')'˺����㳰") {
            Singleton<Namespace>::renewInstance();
            stringstream buf;
            StaticAPI_test api("API");

            buf.str("API(; NEXT");
            Parser p(&buf, "test");

            TestSuite::clearCheckpoints();
            bool result = false;
            try { StaticAPI::parseStaticAPI(p); }
            catch(...) { result = true; }

            TEST_CASE("1","�㳰������", result);
            TEST_CASE("2","��ŪAPI�����Τ��ƤФ�Ƥ���", TestSuite::isReached("StaticAPI::body"));
        } END_CASE;

        BEGIN_CASE("4","';'˺����㳰") {
            Singleton<Namespace>::renewInstance();
            stringstream buf;
            StaticAPI_test api("API");

            buf.str("API() NEXT");
            Parser p(&buf, "test");

            TestSuite::clearCheckpoints();
            bool result = false;
            try { StaticAPI::parseStaticAPI(p); }
            catch(...) { result = true; }

            TEST_CASE("1","�㳰������", result);
            TEST_CASE("2","��ŪAPI�����Τ��ƤФ�Ƥ���", TestSuite::isReached("StaticAPI::body"));
        } END_CASE;
    } END_CASE;

    BEGIN_CASE("onFail","onFail") {
        BEGIN_CASE("1","���ߥ����ޤ��ɤ����Ф�") {
            Singleton<Namespace>::renewInstance();
            stringstream buf;
            Parser p(&buf, "test");
            StaticAPI_test api;
            Token token;
            buf.str("api parameter;next_api next_api_parameter;");

            api.onFail_super(Token(), p);

            TEST_CASE("1","���ߥ����μ����ɤ��", p.getToken() == "next_api");
        } END_CASE;

        BEGIN_CASE("2","����API�ޤ��ɤ����Ф�") {
            Singleton<Namespace>::renewInstance();
            stringstream buf;
            Parser p(&buf, "test");
            StaticAPI_test api("api,next_api");
            buf.str("api parameter_1 parameter_2 next_api next_api_parameter;");

            api.onFail_super(p.getToken(), p);

            TEST_CASE("1","����API̾���ɤ��", p.getToken() == "next_api");
        } END_CASE;
    } END_CASE;

    BEGIN_CASE("skip","skip") {
        BEGIN_CASE("1","���ߥ����ޤ��ɤ����Ф�") {
            Singleton<Namespace>::renewInstance();
            stringstream buf;
            Parser p(&buf, "test");
            StaticAPI_test api;
            Token token;
            buf.str("api parameter;next_api next_api_parameter;");

            StaticAPI::skip(p);

            TEST_CASE("1","���ߥ����μ����ɤ��", p.getToken() == "next_api");
        } END_CASE;

        BEGIN_CASE("2","����API�ޤ��ɤ����Ф�") {
            Singleton<Namespace>::renewInstance();
            stringstream buf;
            Parser p(&buf, "test");
            StaticAPI_test api("api,next_api");
            buf.str("parameter_1 parameter_2 next_api next_api_parameter;");

            StaticAPI::skip(p);

            TEST_CASE("1","����API̾�����ɤ��", p.getToken() == "next_api");
        } END_CASE;

        BEGIN_CASE("3","��Ƭ��API̾�Ǥ��ɤ����Ф��Ǥ���") {
            Singleton<Namespace>::renewInstance();
            stringstream buf;
            Parser p(&buf, "test");
            StaticAPI_test api("api,next_api");
            buf.str("api parameter_1 parameter_2 next_api next_api_parameter;");

            StaticAPI::skip(p);

            TEST_CASE("1","����API̾���ɤ��", p.getToken() == "next_api");
        } END_CASE;
    } END_CASE;
    
    Singleton<Namespace>::restoreContext(context);
}


namespace {
    class Directives_test : public Directives
    {
    public:
        bool throws;

        Directives_test(void) throw() : Directives(), throws(false) {}
        Directives_test(string src) throw() : Directives(src), throws(false)  {}

        void body(const Token & , Parser & ) throw(int)
        {
            TestSuite::check("Directives::body");
            if(throws)
                throw 0;
        }
    };
}

TESTSUITE(main, Directives)
{
    Singleton<Namespace>::Context context;
    Singleton<Namespace>::saveContext(context);

    Exception::setThrowControl(true);

    BEGIN_CASE("regist","regist") {
        BEGIN_CASE("1","ñ���̾������ꤷ����Ͽ�Ǥ���") {
            Singleton<Namespace>::renewInstance();
            Directives_test api;

            api.regist("include");

            TEST_CASE("1","API����������Ͽ�Ǥ��Ƥ���",Directives::hasDirectives("include"));
        } END_CASE;

        BEGIN_CASE("2","ʣ����̾������ꤷ����Ͽ����") {
            Singleton<Namespace>::renewInstance();
            Directives_test api;

            api.regist("pragma,define,endif");

            TEST_CASE("1","�ǥ��쥯�ƥ��֤���������Ͽ�Ǥ��Ƥ���",Directives::hasDirectives("pragma"));
            TEST_CASE("2","�ǥ��쥯�ƥ��֤���������Ͽ�Ǥ��Ƥ���",Directives::hasDirectives("define"));
            TEST_CASE("3","�ǥ��쥯�ƥ��֤���������Ͽ�Ǥ��Ƥ���",Directives::hasDirectives("endif"));
        } END_CASE;

        BEGIN_CASE("3","��񤭤���") {
            Singleton<Namespace>::renewInstance();
            Directives_test api;
            Directives_test api2;
            Directives_test api3;

            api.regist("test");
            TEST_CASE("1","�ǥ��쥯�ƥ��֤���������Ͽ�Ǥ��Ƥ���",Directives::hasDirectives("test"));
            TEST_CASE("2","�ǥ��쥯�ƥ��֥ϥ�ɥ餬������", (*Directives::getClauseMap(NAMESPACE_DIRECTIVES))["test"] == &api);

            api2.regist("test");
            TEST_CASE("3","�ǥ��쥯�ƥ��֥ϥ�ɥ餬��񤭤���Ƥ���", (*Directives::getClauseMap(NAMESPACE_DIRECTIVES))["test"] == &api2);

            api3.regist("test");
            TEST_CASE("4","�ǥ��쥯�ƥ��֥ϥ�ɥ餬��񤭤���Ƥ���", (*Directives::getClauseMap(NAMESPACE_DIRECTIVES))["test"] == &api3);
        } END_CASE;

        BEGIN_CASE("4","���󥹥ȥ饯������Ͽ") {
            Singleton<Namespace>::renewInstance();
            Directives_test api("pragma,define,endif");

            TEST_CASE("1","�ǥ��쥯�ƥ��֤���������Ͽ�Ǥ��Ƥ���",Directives::hasDirectives("pragma"));
            TEST_CASE("2","�ǥ��쥯�ƥ��֤���������Ͽ�Ǥ��Ƥ���",Directives::hasDirectives("define"));
            TEST_CASE("3","�ǥ��쥯�ƥ��֤���������Ͽ�Ǥ��Ƥ���",Directives::hasDirectives("endif"));
        } END_CASE;
    } END_CASE;
    
    BEGIN_CASE("parseDirectives","parseDirectives") {
        BEGIN_CASE("1","�ǥ��쥯�ƥ��֤������������Ǥ���") {
            Singleton<Namespace>::renewInstance();
            stringstream buf;
            Directives_test api("pragma");

            buf.str("pragma\nnext\n");
            Parser p(&buf, "test");

            TestSuite::clearCheckpoints();
            bool result = true;
            try { Directives::parseDirectives(p); }
            catch(...) { result = false; }

            TEST_CASE("1","�㳰�ϵ���ʤ�", result);
            TEST_CASE("2","�ǥ��쥯�ƥ��֤����Τ��ƤФ�Ƥ���", TestSuite::isReached("Directives::body"));
        } END_CASE;

        BEGIN_CASE("2","���Ԥʤ�(�����ѥ�᡼��)���㳰") {
            Singleton<Namespace>::renewInstance();
            stringstream buf;
            Directives_test api("pragma");

            buf.str("pragma next\n");
            Parser p(&buf, "test");

            TestSuite::clearCheckpoints();
            bool result = false;
            try { Directives::parseDirectives(p); }
            catch(...) { result = true; }

            TEST_CASE("1","�㳰������", result);
            TEST_CASE("2","�ǥ��쥯�ƥ��֤����Τ��ƤФ�Ƥ���", TestSuite::isReached("Directives::body"));
        } END_CASE;

        BEGIN_CASE("3","���Ԥʤ�(EOF)���㳰") {
            Singleton<Namespace>::renewInstance();
            stringstream buf;
            Directives_test api("pragma");

            buf.str("pragma");
            Parser p(&buf, "test");

            TestSuite::clearCheckpoints();
            bool result = false;
            try { Directives::parseDirectives(p); }
            catch(...) { result = true; }

            TEST_CASE("1","�㳰������", result);
            TEST_CASE("2","�ǥ��쥯�ƥ��֤����Τ��ƤФ�Ƥ���", TestSuite::isReached("Directives::body"));
        } END_CASE;
    } END_CASE;

    BEGIN_CASE("onFail","onFail") {
        BEGIN_CASE("1","body���㳰�������onFail�����β��Ԥޤ��ɤ����Ф�") {
            Singleton<Namespace>::renewInstance();
            stringstream buf;
            Directives_test api("pragma");
            buf.str("pragma parameter\nnext\n");
            Parser p(&buf, "test");

            api.throws = true;
            bool result = false;
            try { Directives::parseDirectives(p); }
            catch(...) { result = true; }

            TEST_CASE("1","�㳰������", result);
            TEST_CASE("2","�Ĥä����Ƥ�������", p.getToken() == "next");
            TEST_CASE("3","�ȡ�����Ϲ�Ƭ", p.isHeadofLine());
        } END_CASE;
    } END_CASE;
            
    Singleton<Namespace>::restoreContext(context);
}

#endif



