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
 *  @(#) $Id: parser.h,v 1.14 2003/12/20 06:32:48 takayuki Exp $
 */


// $Header: /home/CVS/configurator/base/parser.h,v 1.14 2003/12/20 06:32:48 takayuki Exp $

#ifndef PARSER_H
#define PARSER_H

#include "base/defs.h"

#include "base/message.h"

#include "base/directorymap.h"
#include "base/component.h"

#include <stdarg.h>
#include <iostream>
#include <list>
#include <string>
#include <fstream>
#include <sstream>

#define PARSERESULT         "/parse_result"

#ifndef  ERROR
#undef   ERROR   /* MinGW�Ķ�����wingdi.h��ERROR���������� */
#endif

class Token : public std::string
{
        //���Фα��äϤ��ʤ�
public:
    enum tagTokenType
    {
        IDENTIFIER      = 0x01,
        INTEGER         = 0x02,
        STRINGLITERAL   = 0x03,
        STRING          = 0x04,
        OPERATOR        = 0x05,
        PUNCTUATOR      = 0x06,
        RESERVEDWORD    = 0x07,
        SPECIAL         = 0x80,
        SPACE           = 0x81,
        UNKNOWN         = 0xfd,
        ERROR           = 0xfe,
        EOS             = 0xff      //End of Stream
    };

    enum tagTokenType   type;
    long                value;
    unsigned int        line;

    Token(void)                 { type = UNKNOWN;  value = 0;   };
    Token(const Token & src)    { (*this) = src; };
    Token(enum tagTokenType, const char *);

    operator const enum tagTokenType (void) const { return type; };

    Token & operator =(const Token & src);
    bool operator == (const Token & src) const;

    Token & trim(void);
    Token & chopLiteral(void);
    void    confirm(const char *) const;
};

class Parser
{
public:
    enum tagFunctionarities
    {   UNKNOWN = 0, DIRECTIVE = 1, LOGGING = 2 };

    struct tagFile
    {
        std::string    identifier;
        std::istream * stream;
        unsigned int   line;
    };

protected:
    static const char * Punctuator;
    static const char * Operator;
    static Token        lastErrorToken;
    
    std::string *       LogBuffer;
    unsigned int        PutBackCount;
    bool                isHeadofLine;

    Directory *         Container;

    tagFile *             current;
    std::list<Token>      TokenStack;
    std::list<tagFile *>  fileStack;
    int                   functionalities;

    std::string           preprocessname;   //�ץ�ץ��å����̤��Ȥ��˻Ȥä�̾��
    std::string           originalname;     //�����̾��

    bool parseDirectives(Token &, int, bool);

    bool getIdentifier(Token &, int);
    bool getWhitespace(Token &, int, bool);
    bool getInteger(Token &, int);
    bool getStringLiteral(Token &, int);
    bool getOperator(Token &, int);

    int  getChar(void);
    void putBack(int);

    void initialize(void) { current = 0; functionalities = DIRECTIVE|LOGGING; PutBackCount = 0; LogBuffer = 0; isHeadofLine = true; };

    bool isenabled(enum tagFunctionarities func)  { return (functionalities & (int)func) != 0; };

public:
    Parser(Directory & cnt) : Container(&cnt) { initialize(); };
    Parser(Directory * cnt) : Container(cnt)  { initialize(); };
    ~Parser(void);

    void pushStream(const std::string & filename, std::string = "");
    void pushStdStream(std::string = "Standard Input");

    void setStreamIdentifier(const std::string & id);
    void setCurrentLine(unsigned int pos) { current->line = pos; };
    unsigned int getCurrentLine(void);
    const char * getStreamIdentifier(void);
    std::string getStreamLocation(void);

    enum Token::tagTokenType getToken(Token &,bool = false);
    void getToken(Token &,enum Token::tagTokenType, const char * = NULL);
    void getToken(const char *) throw(Exception);
    void getToken(const char *, const char * , const char * = 0, const char * = 0) throw(Exception);

    void putBack(Token &);

    static const Token & getLastErrorToken(void) { return lastErrorToken; };

    void enable(enum tagFunctionarities func)  { functionalities |=  (int)func; };
    void disable(enum tagFunctionarities func) { functionalities &= ~(int)func; };

    std::string *  setLogBuffer(std::string * buffer);
    std::streampos getLogBufferPos(int offset = 0);

    void doPreProcess(const char * cmd);
};


//---

class ParseUnit
{
protected:
    static Token & parseParameter(Parser &);
    static int     parseParameters(Parser &, Directory *, int, int=0);
    static int     parseParameters(Parser &, Directory *, const char *);

public:
    ParseUnit(void *, const char *);
    virtual ~ParseUnit(void) {};

    const char * getIdentifier(void) const;
    virtual void body(const std::string &, Directory &, Parser &, const std::string &) =0;

    static void printList(void * container);
};

#define __DECLARE_PARSEUNIT(x,y,z) class x##_##y : public x { public: x##_##y(void) : x(z) {}; protected: virtual void body(const std::string &, Directory &, Parser &, const std::string &); } instance_of_##x##_##y; void x##_##y::body(const std::string & identifier, Directory & container, Parser & p, const std::string & domain)

//---

class StaticAPI : public ParseUnit
{
protected:
    static Directory * last;
    Directory * allocate(Parser & p, Directory &, const Token &, const char *, bool = true);
    Directory * allocate(Directory &, const Token &, const char *, bool = true);
    Directory * find    (Directory &, const Token &, const char *);

public:
    StaticAPI(const char * name) : ParseUnit(&(container()), name) {};

    static void printList(void)         { ParseUnit::printList(&(container())); };
    static void clearLastObject(void)   { last = NULL; };
    static void dropLastObject(void);

    static std::map<std::string, class ParseUnit *> & container(void);
};

#define DECLARE_API(x,y) __DECLARE_PARSEUNIT(StaticAPI,x,y)

//---

class Directive : public ParseUnit
{
public:
    static std::map<std::string, class ParseUnit *> & container(void);

    Directive(const char * name) : ParseUnit(&(container()), name) {};
    static void printList(void) { ParseUnit::printList(&(container())); }
};

#define DECLARE_DIRECTIVE(x,y) __DECLARE_PARSEUNIT(Directive,x,y)

//---

class ParserComponent : public Component
{
protected:
    int  failCount;
    bool ignoreUnknownAPI;

    static void throughConfigurationFile(std::string & log, Directory & container);

    virtual void parseOption(Directory &);    
    virtual void body(Directory &);

    bool         parseStaticAPI(Parser & p, Directory & container, Token token, const std::string = "");

    virtual bool parse(Parser & p, Directory & container) = 0;

public:
    ParserComponent(void) throw();
    virtual ~ParserComponent(void) throw();
};

//---

namespace Common {
    
    enum tagAssignmentOrder { UNKNOWN, ALPHABETIC, FCFS, REVERSE=0x80, REVERSE_ALPHABETIC, REVERSE_FCFS };

    enum tagAssignmentOrder parseOrder(Directory * order_option_node);
    enum tagAssignmentOrder parseOrder(OptionParameter::OptionItem order_option_node);
    int assignID(Directory & container, const char * category, const char * top, enum tagAssignmentOrder = FCFS);
}

//---

inline Token::Token(enum tagTokenType type, const char * term)
{
    type = type;
    value = 0;
    assign(term);
}

inline Token & Token::operator =(const Token & src)
{   
    type = src.type; 
    value = src.value; 
    line = src.line;
    assign(src); 
    return *this;   
}

inline bool Token::operator ==(const Token & src) const
{
    if(type != src.type)
        return false;
    if(type == Token::INTEGER && value != src.value)
        return false;
    else
        if(compare(src) != 0)
            return false;

    return true;
}

inline void Token::confirm(const char * str) const
{
    if(compare(str) != 0)
        ExceptionMessage("Illegal token (%) appears during parse process.","������Ϥ�����������ʥȡ�����(%)���и����ޤ���") << str << throwException;
}

inline void Parser::getToken(Token & token, enum Token::tagTokenType type, const char * term)
{
    getToken(token, type == Token::SPACE);

    if(type == Token::STRING && token == Token::STRINGLITERAL)
        token.chopLiteral();

    if((type != token) || (term != NULL && token.compare(term) != 0))
    {
        lastErrorToken = token;
        ExceptionMessage("Parse error on reading [%]","������ϤΥ��顼 [%]") << token << throwException;
    }
}

inline void Parser::putBack(Token & token)
{   TokenStack.push_front(token);   }

inline Directory * StaticAPI::find(Directory & container, const Token & token, const char * id)
{
    Directory * node;

    node = container.findChild(id,token.c_str(),NULL);
    if(node == 0)
        ExceptionMessage("The object %(%) does not exist.","���֥�������%(%)��̤����Ǥ�") << token << throwException;

    return node;
}

inline void StaticAPI::dropLastObject(void)
{
    if(last != NULL)
    {
        last->erase();
        last = NULL;
    }
}

inline Directory * StaticAPI::allocate(Parser & p, Directory & container, const Token & token, const char * category, bool regist)
{
    Directory * node = allocate(container, token, category, regist);
    if(node != 0)
        (*node)["position"] = p.getStreamLocation();
    return node;
}

inline void Parser::setStreamIdentifier(const std::string & id)
{
    if(preprocessname.compare(id) != 0)
        current->identifier = id;
    else
        current->identifier = originalname;
}

#endif

