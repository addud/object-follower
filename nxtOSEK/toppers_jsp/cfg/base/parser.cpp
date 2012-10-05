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
 *  @(#) $Id: parser.cpp,v 1.18 2003/12/15 07:32:14 takayuki Exp $
 */



// $Header: /home/CVS/configurator/base/parser.cpp,v 1.18 2003/12/15 07:32:14 takayuki Exp $

#include "base/defs.h"
#include "base/parser.h"
#include <sstream>
#include <set>
#include <map>
#include <iomanip>

using namespace std;

/*
 *  ��Ƭ�������ˤ������ʸ���������
 */
Token & Token::trim(void)
{
    string::iterator scope;

        /* ������ */
    scope = begin();
    while(*scope == ' ' || *scope == '\t' || *scope == '\r' || *scope == '\n')
        ++ scope;
    erase(begin(), scope);

    if(!empty())
    {
            /* ������ */
        scope = end();
        do {
            -- scope;
        } while(*scope == ' ' || *scope == '\t' || *scope == '\r' || *scope == '\n');
        ++ scope;
        erase(scope, end());
    }
    return *this;
}


 /*
  *  ʸ�����ƥ���Ÿ�� (���֥륯�����Ȥμ����� + ���������ץ������󥹤�Ÿ��)
  */
Token & Token::chopLiteral(void)
{
    if(type != STRINGLITERAL)
        return *this;

    string::iterator scope;

        //���顼�����Τ�������˲������򤹤�
    string src(*this);
    string work;

    if(src[0] != '"' || src[src.length()-1] != '"')
        return *this;

    src = src.substr(1, src.length()-2);

    scope = src.begin();
    while(scope != src.end())
    {
        if(*scope == '\\')
        {
                //��ƥ���������\�ǽ���뤳�ȤϤʤ��Τǥ����å����ʤ�
            ++ scope;
            switch(*scope)
            {
            case '"':   work += '"';   break;
            case 't':   work += '\t';  break;
            case 'r':   work += '\r';  break;
            case 'n':   work += '\n';  break;
            case 'b':   work += '\b';  break;
            case '\\':   work += '\\';  break;
            default:
                ExceptionMessage("Illegal escape sequence [\\%]","���������ץ�������[\\%]�������Ǥ�") << *scope << throwException;
            }
        }else
            work += *scope;

        ++ scope;
    }

    type = STRING;
    assign(work);
    value = this->length();

    return *this;
}

    /* ���ڤ�ʸ�� (��ʸ�������ǰ�̣������ʸ��) */
const char * Parser::Punctuator =
    ",;(){}";

    /* �黻�� (�ü�ʸ������ʤ�ʸ��) */
const char * Parser::Operator =
    "+-*/&|%^~!?[]=:.#";

Token Parser::lastErrorToken;


 /*
  *  ���ȥ꡼�फ���ʸ�������ڤ�Ф�
  */
inline int Parser::getChar(void)
{
    int work = current->stream->get();

        /* ���ֹ�ν��� */
    if(work == '\n')
        current->line ++;
    
        /* ���ȥ꡼����Τ���ν��� */
    if(PutBackCount == 0)
    {
        if(LogBuffer != 0 && isenabled(LOGGING))
            *LogBuffer += static_cast<char>(work);
    }else
        PutBackCount --;    //���Ǥ��ɤ߹���Ǥ���

    return work;
}

 /*
  *  ���Ф�������ʸ���򥹥ȥ꡼����֤�
  */
inline void Parser::putBack(int ch)
{
        /* ���ֹ�Τ���ν��� */
    if(ch == '\n')
        current->line --;

        /* ���ȥ꡼����Τ���ν��� */
    PutBackCount ++;

    current->stream->putback(ch);
}

 /*
  *  Parser���饹�Υǥ��ȥ饯��
  */
Parser::~Parser(void)
{
    list<tagFile *>::iterator scope;

        /* �Ǹ�ޤǥѡ������Ƥʤ��ʤ顢�Ȥꤢ���������å�������Ƥ��� */
    if(current != 0)
        fileStack.push_front(current);

        /* �����å�������������˴� */
    scope = fileStack.begin();
    while(scope != fileStack.end())
    {
        if((*scope)->stream != 0 && (*scope)->stream != &cin)
            delete (*scope)->stream;        //���ȥ꡼����˴�
        delete (*scope);                    //��¤�ΤΥǡ����ΰ���˴�

        ++ scope;
    }

        /* ǰ�Τ��� */
    fileStack.clear();
    TokenStack.clear();
}


 /*
  *  ���̻Ҥ��ڽФ� (���̻� = [a-zA-Z_][0-9a-zA-Z_]*)
  */
bool Parser::getIdentifier(Token & token,int ch)
{
    token.value = 0;

    do {
        token.value ++;
        token += static_cast<char>(ch);
        ch = getChar();
    } while( (ch >='a' && ch <= 'z') || (ch >='A' && ch <= 'Z') || (ch == '_') || (ch >= '0' && ch <= '9') );

    if(ch != -1)
        putBack(static_cast<char>(ch));

    token.type = Token::IDENTIFIER;
    return true;
}


 /*
  *  �ǥ��쥯�ƥ��֤��ڽФ��Ƚ���
  */
bool Parser::parseDirectives(Token & token, int ch, bool allow_space)
{
    Token directive;
    map<string, ParseUnit *>::iterator scope;

        //�����ɤ����Ф�
    do {
        token += static_cast<char>(ch);
        ch = getChar();
    } while(ch == ' ' || ch == '\t');
    
    if(ch >= '0' && ch <= '9')
    {
            //GNU-cpp line�ǥ��쥯�ƥ��� �к�
        directive.assign("line");
        this->putBack(ch);
    }else
    {
            //�ǥ��쥯�ƥ��֤��ɤ߽Ф�
        putBack(ch);
        getToken(directive);
        token += directive;
    }

        //line�ǥ��쥯�ƥ��֤β���
    if(directive.compare("line") == 0)
    {
        Token token;

        getToken(token, Token::INTEGER);
        setCurrentLine(token.value -1);

        getToken(token, Token::STRINGLITERAL);
        try {
            token.chopLiteral();
        }
        catch(Exception &) {
            token.assign("Unknown");
        }
        setStreamIdentifier(token);

        return true;
    }

        //pragma�ǥ��쥯�ƥ��֤β���
    if(directive.compare("pragma") == 0)    
    {
        getToken(directive);
        token += " ";
        token += directive;

        if((scope = Directive::container().find(directive)) != Directive::container().end())
        {
            (*scope).second->body(directive, *Container, *this, string(""));

                //;ʬ�ʥȡ�������ɤ����Ф�
            if(!TokenStack.empty())
            {
                do {
                    token = TokenStack.front();
                    TokenStack.pop_front();
                } while(!TokenStack.empty() && !allow_space && token.type == Token::SPACE);

                return true;
            }
        }
    }

        //include�ǥ��쥯�ƥ��֤β���
    if(directive.compare("include") == 0)
    {
        cerr << getStreamLocation() << Message(": Configurator found 'include' directive\nKernel configuration file must be preprocessed.\n",": #include�ǥ��쥯�ƥ��֤�ȯ�����ޤ���\n �����ͥ빽���ե������C�ץ�ץ��å����̲ᤵ����ɬ�פ�����ޤ�\n");
        ExceptionMessage("Illegal kernel configuration file","�����ʥ����ͥ빽���ե�����").throwException();
    }

    putBack(directive);
    return false;
}


 /*
  *  ����ʸ�����ڽФ�
  *    �����ڡ���, ����   ��#�ǻϤޤäƲ��Ԥޤ�    ��C����Υ����ȥ֥�å�
  *    ��2Ϣ�Υ���å���(//)������Ԥޤ�
  *    �����4�Ĥ��Ȥ߹�碌�����
  */
bool Parser::getWhitespace(Token & token, int ch, bool allow_space)
{
    int prev;

    token.type = Token::SPACE;
    switch(ch)
    {
    case '/':
        ch = getChar();

        switch(ch)
        {
            /* �����ȥ֥�å� */
        case '*':
            token += "/*";
            prev = '\x0';
            while( ((ch = getChar()) != '/') || (prev!='*'))
            {
                token += static_cast<char>(ch);
                prev = ch;
            }
            token += static_cast<char>(ch);
            break;

            /* ���֥륹��å��� */
        case '/':
            token += '/';
            do {
                token += static_cast<char>(ch);
            } while( (ch = getChar()) != '\n' );
            break;

            /* ����'/'�ǻϤޤä������Ǥ��� */
        default:
            putBack(ch);
            return getOperator(token, '/');;
        }
        break;

        /* # �ǻϤޤ�� */
    case '#':
            /* �ǥ��쥯�ƥ��֤�̵�� or ����ʥǥ��쥯�ƥ��֤��Τ�ʤ� */
        if(! (isenabled(DIRECTIVE) && parseDirectives(token, ch, allow_space)) )
        {
                //���Ԥޤ��ɤ����Ф�
            TokenStack.clear();
            do {
                token += static_cast<char>(ch);
                ch = getChar();
            } while(ch != '\n');
            putBack(ch);
        }
        break;

        /* ¯�˸�������ʸ�� */
    case ' ':
    case '\t':
    case '\n':
    case '\r':
        do {
            token += static_cast<char>(ch);
            ch = getChar();
        } while((ch == ' ') || (ch == '\n') || (ch == '\r') || (ch == '\t'));
        putBack(static_cast<char>(ch));
        break;
    }
    return true;
}

 /*
  *  �����ͤ��ڽФ� (8/10/16��, ����/���)
  *   ��2�ʤ���ɾ���ä��ΤǤ��ޤ���
  */
bool Parser::getInteger(Token & token, int ch)
{
    bool minus = false; 

    if(ch == '-')
    {
        minus = true;
        ch = getChar();
        if(ch < '0' || ch >'9')
        {
            putBack(static_cast<char>(ch));
            return false;
        }
        token += "-";
    }

    token.type = Token::INTEGER;
    token.value = 0;

    if(ch == '0')
    {
        token += static_cast<char>(ch);
        ch = getChar();
        if(ch == 'x' || ch == 'X')
        {
            token += static_cast<char>(ch);
            ch = getChar();
            while((ch >= '0' && ch <= '9') || (ch >= 'a' && ch <= 'f') || (ch >= 'A' && ch <= 'F'))
            {
                token += static_cast<char>(ch);
                if((ch -= '0') >= 10)
                {
                    ch = ch + '0' - 'A' + 10;
                    if(ch >= 16)
                        ch = ch - ('a' - 'A');
                }
                token.value = token.value * 16 + ch;
                ch = getChar();
            }
        }else
        {
            while(ch >= '0' && ch <= '7')
            {
                token += static_cast<char>(ch);
                token.value = token.value * 8 + ch - '0';
                ch = getChar();
            }
        }
    }else
    {
        do {
            token += static_cast<char>(ch);
            token.value = token.value * 10 + ch - '0';
            ch = getChar();
        } while(ch >= '0' && ch <= '9');
    }

        /* integer-suffix */
    if(ch != -1)
    {
        bool unsigned_suffix = false;
        bool long_suffix     = false;

        int  first_longsuffix;

        if(ch == 'u' || ch == 'U')
        {
            unsigned_suffix = true;
            token += static_cast<char>(ch);
            ch = getChar();
        }

        if(ch == 'i' || ch == 'I')  //i8, i16, i32, i64
        {
            int  first, second;
            bool accept = false;
            const signed char suffix_list[10] = { -1, '6', -1, '2', -1, -1, '4', -1, 0, -1};    //8, 16, 32, 64�Τߤ����

            first  = getChar();
            second = -1;
            if(first >= '0' && first <= '9')
            {
                if(suffix_list[first - '0'] > 0)
                {
                    second = getChar();
                    if(second == suffix_list[first - '0'])
                        accept = true;
                }else
                    if(suffix_list[first - '0'] == 0)
                        accept = true;
            }

            if(!accept)
            {
                if(second != -1)
                    putBack(second);
                putBack(first);
            } else
            {
                token += static_cast<char>(ch);
                token += static_cast<char>(first);
                if(second != -1)
                    token += static_cast<char>(second);
                ch = getChar();
            }
        } else
        {
            if(ch == 'l' || ch == 'L')
            {
                first_longsuffix = ch;
                long_suffix = true;

                token += static_cast<char>(ch);
                ch = getChar();
                if(ch == first_longsuffix)
                {
                    token += static_cast<char>(ch);
                    ch = getChar();
                }
            }

            if(!unsigned_suffix && (ch == 'u' || ch == 'U'))
            {
                token += static_cast<char>(ch);
                ch = getChar();
            }
        }
    }

    if(minus)
        token.value = - token.value;

    if(ch != -1)
        putBack(static_cast<char>(ch));

    return true;
}


 /*
  *  ���ڥ졼��(�ü�ʸ�����ȹ礻����ʤ�ȡ�����)���ڽФ�
  */
bool Parser::getOperator(Token & token, int ch)
{
    const char * work;

        /* ch�����ڥ졼��ʸ���Ǥ��뤫�ɤ����Τ���� */
    for(work = Operator;*work != '\x0' && *work != ch;work++);
    if(*work == '\x0')
        return false;

        /* ��³����ʸ���⥪�ڥ졼��ʸ���Ǥ��뤫�ɤ����Τ���� */
    do {
        token += static_cast<char>(ch);
        ch = getChar();
        for(work = Operator;*work != '\x0' && *work != ch;work++);
    } while(*work != '\x0');

    putBack(ch);
    token.type = Token::OPERATOR;
    return true;
}


 /*
  *  ʸ�����ƥ�� (���֥륯�����Ȥǳ��줿ʸ��)
  *    �����󥰥륯�����Ȥ�����褦�ˤ���
  *
  *    VisualStudio6.0�ǥ���ѥ��뤷����硢���Ԥ�LF�Υե�������Ф���tellg���
  *    get�����EOF���֤뤿�ᡢƱ�����򥳥��ȥ����Ȥ��Ƥ�����
  */
bool Parser::getStringLiteral(Token & token, int delimitor)
{
    int ch;
    int prev;

    ch = delimitor;

    token.value = 1;
    token.type = Token::STRINGLITERAL;
    token.assign("");
    token += static_cast<char>(ch);

    while(!current->stream->bad() && !current->stream->eof())
    {
        prev = ch;
        ch = getChar();
        token += static_cast<char>(ch);
        token.value ++;

        if(ch == delimitor && prev != '\\')
            return true;
    }

        //���ä����Ĥ��ƺƥ����ץ󤷤ơ���ƥ�볫�Ϥ� " �μ��˰�ư
    
    ExceptionMessage(ExceptionMessage::FATAL, "Unterminated string literal appeared.","�Ĥ����Ƥ��ʤ�ʸ����ƥ��򸡽Ф��ޤ���").throwException();
    return false;
}


 /*
  *  �ȡ�������ڽФ�
  */
enum Token::tagTokenType Parser::getToken(Token & token, bool allow_space)
{
    int ch;
    const char * work;

    do {
        token.erase();
        token.type = Token::ERROR;
        token.value = 0;

            //�ȡ����󥹥��å������ڤ�Ф�
        if(!TokenStack.empty())
        {
            do {
                token = TokenStack.front();
                TokenStack.pop_front();
            } while(!TokenStack.empty() && !allow_space && token.type == Token::SPACE);

            if(!allow_space && token.type != Token::SPACE)
                return token.type;
        }

            //���ȥ꡼�फ���ڤ�Ф�
        if(current == NULL || current->stream == NULL || current->stream->bad())
        {
            token.assign("<End of stream>");
            return (token.type = Token::EOS);
        }

            //�����ȤΥ��ȥ꡼�ब���ˤʤä�
        if(current->stream->eof())
        {
                //�ե����륹���å����鼡�Υ��ȥ꡼�����
            if(!fileStack.empty())
            {
                if(current->stream != &cin)
                    delete current->stream;
                delete current;
                
                current = *fileStack.begin();
                fileStack.pop_front();
            }else
            {
                token.assign("<End of stream>");
                return (token.type = Token::EOS);
            }
        }

        ch = getChar();

            //First(whitespaces) is [ \n\t\r/#]
        if( (ch == ' ') || (ch == '\t') || (ch == '\n') || (ch == '\r') || (ch == '/') || (isHeadofLine && ch == '#'))
        {
            if(ch == '\n')
                isHeadofLine = true;

            if(getWhitespace(token, ch, allow_space))
                if((token == Token::SPACE && allow_space) || !(token == Token::SPACE || token == Token::ERROR))
                    return token.type;

            continue;
        }else
            break;
    }while(true);

    isHeadofLine = false;

    token.line = current->line;

        //First(identifier) is [a-zA-Z_]
    if( (ch >='a' && ch <= 'z') || (ch >='A' && ch <= 'Z') || (ch == '_') )
        if(getIdentifier(token, ch))
            return Token::IDENTIFIER;

        //First(integer) is [\-0-9]
    if( (ch >='0' && ch <='9') || (ch == '-') )
        if(getInteger(token,ch))
            return Token::INTEGER;

        //First(string) is ["']
    if( ch == '"' || ch == '\'')
        if(getStringLiteral(token,ch))
            return Token::STRINGLITERAL;

        //Operator
    if(getOperator(token,ch))
        return Token::OPERATOR;

        //Punctuator
    work = Punctuator;
    while(*work != '\x0')
        if( *(work++) == ch )
        {
            token += static_cast<char>(ch);
            return (token.type = Token::PUNCTUATOR);
        }

    token += static_cast<char>(ch);
    token.type = Token::UNKNOWN;
    return Token::UNKNOWN;
}


 /*
  *  �ȡ������� ���ȥ꡼�४�ڥ졼�� (��˥ƥ�����Ū)
  */
ostream & operator << (ostream & out, Token & src)
{
    switch(src.type)
    {
    case Token::IDENTIFIER:
        out << "<IDENTIFIER:["; break;
    case Token::INTEGER:
        out << "<INTEGER:["; break;
    case Token::STRINGLITERAL:
        out << "<STRINGLITERAL:["; break;
    case Token::STRING:
        out << "<STRING:["; break;
    case Token::OPERATOR:
        out << "<OPERATOR:["; break;
    case Token::PUNCTUATOR:
        out << "<PUNCTUATOR:["; break;
    case Token::RESERVEDWORD:
        out << "<RESERVEDWORD:["; break;
    case Token::SPECIAL:
        out << "<SPECIAL:["; break;
    case Token::SPACE:
        out << "<SPACE:["; break;
    case Token::UNKNOWN:
        out << "<UNKNOWN>"; return out;
    case Token::ERROR:
        out << "<ERROR>"; return out;
    default:
        out << "<???:[";
    }

    return out << static_cast<string &>(src) << "]("<<src.value<<")>";
}

 /*
  *  ͽ�����ڽФ�(�Ȥ��������ǧ)
  */
void Parser::getToken(const char * term) throw(Exception)
{
    Token token;

    if(term == NULL)
        ExceptionMessage("Internal: GetToken received an empty string as reserved word.","�������顼: GetToken�˶�ʸ�����Ϥ���ޤ���").throwException();

    getToken(token, false);
    if(token.compare(term) != 0) {
        lastErrorToken = token;
        ExceptionMessage("Token [%] should be replaced by [%]","����[%]��[%]�Ǥ���٤��Ǥ�") << token << term << throwException;
    }
}

void Parser::getToken(const char * first, const char * second, const char * third, const char * fourth) throw(Exception)
{
    getToken(first);
    if(second != NULL)
        getToken(second);
    if(third != NULL)
        getToken(third);
    if(fourth != NULL)
        getToken(fourth);
}

string Parser::getStreamLocation(void)
{
    list<tagFile *>::iterator scope;

    string location;
    char buffer[16];

    if(current == 0)
        return string("");

    ::sprintf(buffer, ":%d", current->line);
    location += current->identifier;
    location += buffer;

    if(!fileStack.empty())
    {
        location += " (included at ";

        scope = fileStack.begin();
        while(scope != fileStack.end())
        {
            ::sprintf(buffer, ":%d, ", (*scope)->line);
            location += (*scope)->identifier;
            location += buffer;

            ++ scope;

        }

        location.erase(location.size()-2);
        location += ")";
    }

    return location;
}

void Parser::pushStream(const std::string & filename, std::string strid)
{
    fstream * fin;

    if(current != 0)
        fileStack.push_front(current);
        
    fin = new fstream(filename.c_str(),ios::in);

    if(fin->is_open())
    {
        if(strid.size() == 0)
            strid = filename;

        current = new tagFile;
        current->stream     = fin;
        current->identifier = strid;
        current->line       = 1;
    }else
    {       
        ExceptionMessage("File operation failure : [%]","�ե��������˼��Ԥ��ޤ��� [%]") << filename << throwException;
        delete fin;
    }
}

void Parser::pushStdStream(std::string strid)
{
    stringstream * work = new stringstream;
    char buffer[1024];
    int  count;

        //ɸ�����Ϥξ���򤹤٤Ƽ����� (���顼�н��Ѥ� seekg/tellg ��Ȥ�����)
    do {
        cin.read(buffer, 1024);
        count = cin.gcount();
        work->write(buffer, count);
    } while(count != 0);

    if(current != 0)
        fileStack.push_front(current);

    current = new tagFile;
    current->stream     = work;
    current->identifier = strid;
    current->line       = 1;
}

string * Parser::setLogBuffer(string * buffer)
{
    string * old = LogBuffer;
    LogBuffer = buffer;
    PutBackCount = 0;
    return old;
}

streampos Parser::getLogBufferPos(int offset)
{
    streampos pos;
    
    pos = 0;
    if(LogBuffer != 0)
        pos = LogBuffer->size();
    pos += static_cast<streampos>(offset - PutBackCount);
    return pos;
}

#ifdef CALL_EXTERNAL_PROGRAM 
void Parser::doPreProcess(const char * cmd)
{
    string         tempfilename;
    char           buffer[1024];
    int            count;
    fstream        tempfile;
    string         work;
    stringstream * stream;

    if(current == NULL || current->stream == NULL)
        ExceptionMessage("No stream specified for processing","�����оݤȤʤ륹�ȥ꡼�ब���ꤵ��Ƥ��ޤ���").throwException();


        /* ���Υ��ȥ꡼������Ƥ򤹤٤ƥƥ�ݥ��˽񤭽Ф� */

    strcpy(buffer,"cfgXXXXXX");
    mktemp(buffer);

    tempfilename.assign(buffer);
    tempfile.open(tempfilename.c_str(),ios::out);

    if(!tempfile.is_open())
        ExceptionMessage("Failed to open a temporary file","�ƥ�ݥ��ե�����κ����˼��Ԥ��ޤ���").throwException();

    do {
        current->stream->read(buffer, 1024);
        count = current->stream->gcount();
        tempfile.write(buffer, count);
    } while(count != 0);
    tempfile.close();


        /* ���ȥ꡼�ູ���ؤ� */

    preprocessname = tempfilename;
    originalname   = current->identifier;

    if(current->stream != &cin)
        delete current->stream;
    stream = new stringstream;
    current->stream = stream;


        /* �ץ�ץ��å��ε�ư & ���Ϥμ����� */

    work  = string(cmd) + " " + tempfilename;
    VerboseMessage(" Start the external preprocessor [%]\n"," �����ץ�����ư���ޤ� [%]\n") << work;

    FILE * pipe = popen(work.c_str(),"r");
    while(feof(pipe) == 0)
        stream->put((char)fgetc(pipe));

    pclose(pipe);
    remove(tempfilename.c_str());
    isHeadofLine = true;
}
#else
void Parser::doPreProcess(const char * cmd)
{}
#endif /* CALL_EXTERNAL_PROGRAM */


ParseUnit::ParseUnit(void * _container, const char * name)
{
    map<string, ParseUnit *> * container;
    string work(name);
    string apiname;
    string::size_type i,j;

    i = 0;
    container = reinterpret_cast<map<string, ParseUnit *> *>(_container);
    
    do {
        j = work.find_first_of(',', i);
        apiname = work.substr(i, j-i);

        if(container->find(apiname) != container->end())
            ExceptionMessage("Multiple registration of [%]\n","[%]����ʣ������Ͽ����褦�Ȥ��Ƥ��ޤ�") << apiname << throwException;
        (*container)[apiname] = this;
        i = j + 1;
    }while(j != string::npos);
}

void ParseUnit::printList(void * _container)
{
    int i;
    map<string, ParseUnit *> * container;
    map<string, ParseUnit *>::iterator scope;

    container = reinterpret_cast<map<string, ParseUnit *> *>(_container);
    if(container->empty())
    {
        cerr << "  " << Message("None of element registed\n", "��Ͽ����Ƥ������ǤϤ���ޤ���\n");
        return;
    }

    i = 0;
    scope = container->begin();
    while(scope != container->end())
    {
        cerr << '[' << (*scope).first << "] ";

        if(i++ >= 6)
        {
            i = 0;
            cerr << '\n';
        }

        ++ scope;
    }

    if(i != 0)
        cerr << '\n';
}

Token & ParseUnit::parseParameter(Parser & p)
{
    static Token result;
    Token token;
    int nest = 0;

    result.type = Token::ERROR;
    result.value = 0;
    result.assign("");

    do
    {
        p.getToken(token);
        if(token == Token::PUNCTUATOR)
        {
            if(token.compare("(") == 0)
                nest ++;
            else if(token.compare(")") == 0)
                nest --;
            else if(nest == 0)
                break;
            if(nest < 0)
                ExceptionMessage("')' appeared before '('.","�б����ʤ��Ĥ���̤�����ޤ�").throwException();
        }

        if(result == Token::ERROR)
            result = token;
        else
        {
            result.type = Token::STRING;
            result += ' ';
            result += token;
        }

    }while(true);

    p.putBack(token);
    result.trim();
    return result;
}

int ParseUnit::parseParameters(Parser & p, Directory * container, int min, int max)
{
    Token work;
    int count = 0;

    if(max == 0)
        max = min;

    do
    {
        Token & token = parseParameter(p);
        if(token.type == Token::ERROR)
            break;

        if(token == Token::INTEGER)
            container->addChild(new Directory(token.value));
        else
            container->addChild(new Directory((string &)token));

        count ++;
        p.getToken(work);
    }while(work.compare(",")==0 && count < max);

    if(count < min)
        ExceptionMessage("Too few parameters [%/%]","�ѥ�᡼���ο������ʤ����ޤ� [%/%]") << count << min << throwException;

    p.putBack(work);
    return count;
}

int ParseUnit::parseParameters(Parser & p, Directory * container, const char * paramlist)
{
    Token work;
    int count;
    string list;
    string key;
    string::size_type head,tail;

    list.assign(paramlist);

    count = 0;
    head = 0;
    tail = list.find_first_of(',');
    key = list.substr(head,tail-head);

    do
    {
        if(head == string::npos)
            ExceptionMessage("Too many parameters","�ѥ�᡼���ο���¿�����ޤ�").throwException();

        Token & token = parseParameter(p);
        if(token.type == Token::ERROR)
            break;

        if(token == Token::INTEGER)
            container->addChild(key,new Directory(token.value));
        else
            container->addChild(key,new Directory((string &)token));

        if(tail != string::npos)
        {
            head = tail + 1;
            tail = list.find_first_of(',',head);
            key = list.substr(head,tail != string::npos ? tail-head : string::npos);
            count ++;
            p.getToken(work);
        }else
            break;
    }while(work.compare(",")==0);

    if(tail != string::npos)
        ExceptionMessage("Too few parameters","�ѥ�᡼���ο������ʤ����ޤ�").throwException();

    return count;
}

//------

Directory * StaticAPI::last = NULL;

map<std::string, class ParseUnit *> & StaticAPI::container(void)
{
    static map<std::string, class ParseUnit *> _container;
    return _container;
}

Directory * StaticAPI::allocate(Directory & container, const Token & token, const char * id, bool regist)
{
    static unsigned int assignment_count = 0;
    Directory * node;

    if(!(token == Token::IDENTIFIER || token == Token::INTEGER))
        ExceptionMessage("Given token(%) is not suitable for an object identifier.","���֥������Ȥμ���̾�Ȥ������ѤǤ��ʤ�����(%)�����ꤵ��ޤ���") << token << throwException;

    if(regist && (token == Token::INTEGER && token.value <= 0))
        ExceptionMessage("Cannot assign an ID number less or equal to 0.","0�ʲ���ID�ֹ�����ꤹ�뤳�ȤϤǤ��ޤ���").throwException();


    node = container.findChild(id);
    if(node != 0)
    {
        Directory::iterator scope;

        scope = node->begin();
        while(scope != node->end())
        {
            if((*scope).first.compare(token) == 0)
                ExceptionMessage("Identifier % is already used.","����̾%�Ϥ��Ǥ����Ѥ���Ƥ��ޤ�") << token << throwException;
            ++ scope;
        }
    }else
        node = container.addChild(id);

    node = node->addChild(token);
    (*node)["#order"] = assignment_count++;

    if(token == Token::IDENTIFIER)
    {
        if(regist)
        {
            Directory * scope = container.openChild("/","identifier",token.c_str(),NULL);
            if(*scope == Directory::INTEGER)
                *node = scope->toInteger();
        }
    }else
        *node = token.value;

    last = node;
    return node;
}

//------

map<std::string, class ParseUnit *> & Directive::container(void)
{
    static map<std::string, class ParseUnit *> _container;
    return _container;
}

//------

ParserComponent::ParserComponent(void) throw() : Component(PARSER)
{}

ParserComponent::~ParserComponent(void) throw()
{}

void ParserComponent::parseOption(Directory & container)
{
    if(findOption("h", "help"))
    {
        cerr << Message(
            "Static API parser\n"
            "  -s, --source=filename     : Specify the source file\n"
            "  -idir ,--ignore-directive : Ignore directives\n"
            "  -iapi ,--ignore-api       : Ignore unknown static api\n"
            "  -t, --through             : Get unprocessed APIs through\n"
            "  --print-api               : Show registered static api list\n", 
            "��ŪAPI�ѡ���\n"
            "  -s, --source=�ե�����̾   : ���ϥե�����̾����ꤷ�ޤ�\n"
            "  -idir ,--ignore-directive : �ǥ��쥯�ƥ��֤β��Ϥ�Ԥ��ޤ���\n"
            "  -iapi, --ignore-api       : ��Ͽ����Ƥ��ʤ�API��̵�뤷�ޤ�\n"
            "  -t, --through             : �������ʤ��ä�API���̲ᤵ���ޤ�\n"
            "  --print-api               : ��Ͽ����Ƥ���API�ΰ�����ɽ�����ޤ�\n");
        return;
    }

    if(findOption("-print-api"))
    {
        cerr << Message("List of Registerd Static API\n","��ŪAPI ����\n");
        StaticAPI::printList();
        return;
    }

    checkOption("idir", "ignore-directive");
    checkOption("iapi", "ignore-api");
    checkOption("t", "through");

    if(checkOption("s","source") || checkOption(DEFAULT_PARAMETER))
        activateComponent();
}

bool ParserComponent::parseStaticAPI(Parser & p, Directory & container, Token token, const string domain)
{
    bool isParseErrorOccured = false;
    map<string, ParseUnit *>::iterator api;
    Directory * node = NULL;

    if(token.type != Token::IDENTIFIER)
        return false;

    StaticAPI::clearLastObject();
    node = container[PARSERESULT].addChild();

    try {
        node->addChild("api",new Directory(token));
        node->addChild("begin",new Directory((long)p.getLogBufferPos(-(int)token.size()-1)));
        if(!domain.empty())
            node->addChild("domain", new Directory(domain));

        api = StaticAPI::container().find(token);
        if(api == StaticAPI::container().end())
        {
            if(ignoreUnknownAPI)
            {
                cerr << Message("%: Unknown static api % was ignored. (skipped)\n","%: ����Ͽ��API % ��̵�뤵��ޤ�\n") << p.getStreamLocation() << token;
                do {
                    p.getToken(token);
                }while(token.compare(";") != 0);
                node->addChild("end",new Directory((long)p.getLogBufferPos()));
                (*node) = (long)0;
                return true;
            }
            ExceptionMessage("Static API [%] is not registered in the configurator", "��ŪAPI[%]��̤��Ͽ�Ǥ�") << token << throwException;
        }

        DebugMessage("  StaticAPI [%]\n") << (*api).first;

        p.getToken("(");

        (*api).second->body(token, container, p, domain);

        p.getToken(")");
        p.getToken(";");

        node->addChild("end",new Directory((long)p.getLogBufferPos()));
        (*node) = (long)1;
    }
    catch(Exception & e)
    {
        int offset;
        string work;
        work = p.getStreamLocation() + Message(":[Error] ",":[���顼] ").str() + e.getDetails();
        isParseErrorOccured = true;

        StaticAPI::dropLastObject();
        failCount ++;

        offset = 0;
        token = p.getLastErrorToken();
        while (token != Token::ERROR && token != Token::EOS)
        {
            if( token == ";" )
                break;

                //�ɤ߽Ф����ȡ�������ŪAPI��Ʊ��̾���ʤ� ���äȥ��ߥ����˺��
            api = StaticAPI::container().find(token);
            if(api != StaticAPI::container().end())
            {
                cerr << Message("<The following error must be occured by lack of ';' at the end of previous line>\n","<���Υ��顼��ľ���Ԥ�';'˺��ˤ���ǽ�����⤤�Ǥ�>\n");
                offset = -(int)token.size();
                p.putBack(token);
                break;
            }

            p.getToken(token);
        }

        node->addChild("end",new Directory((long)p.getLogBufferPos(offset)));
        (*node) = (long)0;

        cerr << work << '\n';

        ExceptionMessage("Fatal error on Static API parsing","��ŪAPI�ι�ʸ���Ϥ˼��Ԥ��ޤ���").throwException();
    }

    return true;
}

/*
 *  �����Ǥ��ʤ��ä�API��ɸ����Ϥ��Ǥ��Ф�
 */
void ParserComponent::throughConfigurationFile(string & log, Directory & container)
{
    Directory *        node;
    string::size_type  pos;
    string::size_type  begin;
    string::size_type  end;

    pos = 0;
    end = 0;

    node = container[PARSERESULT].getFirstChild();
    while(node != NULL)
    {
        begin = static_cast<string::size_type>((*node)["begin"].toInteger());
        end   = static_cast<string::size_type>((*node)["end"].toInteger());

        if(pos < begin)
            cout << log.substr(pos, begin - pos);

        if(node->toInteger() == 0)
        {
            cout << log.substr(begin, end - begin);
        }else
        {
            for(pos = begin; pos < end; ++pos)
                if( log.at(pos) == '\n' )
                    cout << '\n';
        }
        node = node->getNext();
    }

    if(end < log.size())
        cout << log.substr(end);

    ExceptionMessage("","").throwException();
}


void ParserComponent::body(Directory & container)
{
    Token token;
    Parser p(container);
    string logbuffer;
    OptionParameter::OptionItem item;
    unsigned int itemcount = 0;

    failCount = 0;
    
        //idir���ץ����ν���
    if(findOption("idir","ignore-directive"))
        p.disable(Parser::DIRECTIVE);

    ignoreUnknownAPI = findOption("iapi", "ignore-api");

    if(findOption("t","through"))
    {
        p.setLogBuffer(&logbuffer);
        ignoreUnknownAPI = true;
    }

        //���ϥ�����
    item = getOption("s", "source");
    item.mergeItem(getOption(DEFAULT_PARAMETER));
    if(item.countParameter() == 0)
    {
        p.pushStdStream(Message("Standard Input","ɸ������").str());
        VerboseMessage("Starting parse with standard input\n","ɸ�����Ϥ���λ�����Ϥ򳫻Ϥ��ޤ���\n");
    }

    try{
        do {
            if(item.hasParameter())
            {
                VerboseMessage("Starting parse with file[%]\n","�ե�����[%]�λ�����Ϥ򳫻Ϥ��ޤ���\n") << item[itemcount];
                p.pushStream(item[itemcount]);
            }

            this->parse(p, container);

            if(p.getToken(token) != Token::EOS)
                ExceptionMessage("Buffer has remaining tokens, parsing is not yet finished", "�ѡ��������Ǥ���ޤ���").throwException();

            if(failCount != 0)
                ExceptionMessage("Total % failures found in this configuration.","%�Ĥξ㳲������ޤ�") << failCount << throwException;

            VerboseMessage("Parse finished\n","������Ϥ�����˽�λ���ޤ���\n");

        } while(++itemcount < item.countParameter());

        if(findOption("t","through"))
            throughConfigurationFile(logbuffer,container);

        container[PARSERESULT].erase();
    }
    catch(Exception & e)
    {
        string work;

        work = p.getStreamLocation() + Message(":[Error] ",":[���顼] ").str() + e.getDetails();
        ExceptionMessage(work.c_str()).throwException();
    }
}

    // ���ץ����Ρ��ɤ��������ˡ���������
enum Common::tagAssignmentOrder Common::parseOrder(Directory * node)
{
    Directory * scope;
    int         i;

        //�����ѥ�᡼������
    i = FCFS;
    if(node != 0)
    {
        scope = node->getFirstChild();
        while(scope != 0)
        {
            string param = scope->toString();
            if(param.compare("alphabetic") == 0 || param.compare("ALPHABETIC") == 0)
                i = (i & 0xf0) | ALPHABETIC;
            else if(param.compare("fcfs") == 0 || param.compare("FCFS") == 0)
                i = (i & 0xf0) | FCFS;
            else if(param.compare("reverse") == 0 || param.compare("REVERSE") == 0)
                i |= REVERSE;

            scope = scope->getNext();
        }
    }

    return static_cast<enum tagAssignmentOrder>(i);
}

    // ���ץ����Ρ��ɤ��������ˡ���������
enum Common::tagAssignmentOrder Common::parseOrder(OptionParameter::OptionItem item)
{
    Directory node;
    unsigned int i;

    for(i=0;i<item.countParameter();++i)
        node.addChild(item[i]);

    return parseOrder(&node);
}

    //ID�ͤΥ����������
    //  (¾�ξ�꤫���Ȥ��ΤǤ����˰�ư)
int Common::assignID(Directory & container, const char * category, const char * top, enum tagAssignmentOrder order)
{
    Directory * node  = 0;
    Directory * scope = 0;
    Directory * work  = 0;
    set<int> idpool;
    map<int, Directory *> sorter;
    map<int, Directory *>::iterator p_sorter;
    int i;

        //������
    node = container.findChild(top,category,NULL);
    if(node == 0)
        return 0;

    for(i=1;i< (signed int) node->size() + 32; i++)
        idpool.insert(i);

        //���ս�η���ȡ������Ѥ�ID�κ��
    i = 0;
    scope = node->getFirstChild();
    while(scope != 0)
    {
        if( *scope == Directory::INTEGER )
            idpool.erase(*scope);
        else
        {
                //��ʣ̾�Τ�¸�ߥ����å�
            work = container.openChild("/","identifier",scope->getKey().c_str(),NULL);
            if( *work == Directory::INTEGER)
            {
                VerboseMessage("Assigning the same ID (%) since the name (%[%]) is duplicated\n","ID�ֹ�(%)��ۼ�Ʊ̾�Υ��֥�������(%[%])�˳�����Ƥޤ���\n") << work->toInteger() << scope->getKey() << category;
                idpool.erase(*scope = work->toInteger());
            } else
            {
                    //������ˡ�˽��äƳ���������ɲ�
                switch(order)
                {
                case ALPHABETIC:
                    sorter[i++] = scope;
                    break;
                case REVERSE_ALPHABETIC:
                    sorter[i--] = scope;
                    break;
                case FCFS:
                default:
                    sorter[scope->openChild("#order")->toInteger()] = scope;
                    break;
                case REVERSE_FCFS:
                    sorter[-scope->openChild("#order")->toInteger()] = scope;
                    break;
                }
            }
        }
        scope = scope->getNext();
    }

        //ID����
    p_sorter = sorter.begin();
    while(p_sorter != sorter.end())
    {
        scope = (*p_sorter).second;
        if( !(*scope == Directory::INTEGER) )
        {
            i = *(idpool.begin());
            idpool.erase(idpool.begin());

            work = container.openChild("/","identifier",scope->getKey().c_str(),NULL);
            *work = i;
            *scope = i;
        }
        ++ p_sorter;
    }

        //����ɽ����
    if(node->size() != 0 && VerboseMessage::getVerbose())
    {
        VerboseMessage("Object ID assignment list [%]\n","���֥�������ID����ɽ [%]\n") << category;

        sorter.clear();
        scope = node->getFirstChild();
        while(scope != 0)
        {
            sorter[scope->toInteger()] = scope;
            scope = scope->getNext();
        }

        p_sorter = sorter.begin();
        while(p_sorter != sorter.end())
        {
            VerboseMessage("  % : %\n") << setw(3) << (*p_sorter).first << (*p_sorter).second->getKey();
            ++ p_sorter;
        }
    }

        //��������Ƚ��
    if((signed)node->size()+1 != *(idpool.begin()))
        ExceptionMessage("Discontinuous % ID assignment occured","��Ϣ³�ʥ��֥�������ID(%)") << category << throwException;

    return node->size();
}

