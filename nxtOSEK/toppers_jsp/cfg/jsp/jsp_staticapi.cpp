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
 *  @(#) $Id: jsp_staticapi.cpp,v 1.16 2003/12/24 07:33:26 takayuki Exp $
 */

// $Header: /home/CVS/configurator/jsp/jsp_staticapi.cpp,v 1.16 2003/12/24 07:33:26 takayuki Exp $

#include "jsp/jsp_defs.h"

#include "base/parser.h"
#include "base/mpstrstream.h"
#include <iostream>

using namespace std;

DECLARE_API(INCLUDE,"INCLUDE")
{
    Token token;
    Directory * node;
    Directory * scope;

    last = NULL;
    p.getToken(token, Token::STRINGLITERAL);
    token.chopLiteral();

    if( (token[0] != '\"' || token[token.size()-1] != '\"') &&
        (token[0] != '<' || token[token.size()-1] != '>') )
        ExceptionMessage("An include filename must be enclosed with \"...\" or <...>","�ե�����̾�� \"...\" �� <...> �η��Ǥʤ���Фʤ�ޤ���").throwException();

    node = container.openChild(OBJECTTREE,INCLUDEFILE,NULL);
    last = node;

        //��ʣ�����å�
    scope = node->getFirstChild();
    while(scope != 0)
    {
        if(token.compare((*scope).toString()) == 0)
        {
            cerr << p.getStreamLocation() << ' ' << (Message("Include file % was already specified (ignored).","���󥯥롼�ɥե�����%��ʣ������ꤵ��ޤ��� (̵�뤷�ޤ�)") << token) << endl;
            return;
        }
        scope = scope->getNext();
    }
    
    node->addChild(new Directory(token));
}

DECLARE_API(CRE_TSK,"CRE_TSK")
{
    Token token;
    string work;
    Directory * node;

    p.getToken(token);
    node = allocate(container[OBJECTTREE], token, TASK);
    (*node)["position"] = p.getStreamLocation();

    p.getToken(",","{",NULL);
    parseParameters(p,node,"tskatr,exinf,task,itskpri,stksz");
    p.getToken(",","NULL","}",NULL);

    (*node)["texatr"] = "TA_NULL";
    (*node)["texrtn"] = "NULL";

    if(container["/cpu"].toString().compare("nios32") == 0) 
    {
        (*node)["hi_limit"] = "TSK_HI_LIMIT";
        (*node)["lo_limit"] = "TSK_LO_LIMIT";
    }
}

DECLARE_API(VATT_TRW,"VATT_TRW")
{
    Token token;
    Directory * node;

    if(container["/cpu"].toString().compare("nios32") != 0)
        ExceptionMessage("VATT_TRW is not supported except for the processor 'nios32'.","VATT_TRW��nios32�ץ��å��ǤΤߥ��ݡ��Ȥ���ޤ�").throwException();

    p.getToken(token);
    node = find(container[OBJECTTREE], token, TASK);

    p.getToken(",","{",NULL);
    parseParameters(p, node, "hi_limit,lo_limit");
    p.getToken("}");
}

DECLARE_API(DEF_TEX,"DEF_TEX")
{
    Token token;
    Directory * node;

    p.getToken(token);
    node = find(container[OBJECTTREE], token, TASK);

    p.getToken(",","{",NULL);
    parseParameters(p, node, "texatr,texrtn");
    p.getToken("}");
}

DECLARE_API(CRE_SEM,"CRE_SEM")
{
    Token token;
    Directory * node;

    p.getToken(token);
    node = allocate(container[OBJECTTREE], token, SEMAPHORE);
    (*node)["position"] = p.getStreamLocation();

    p.getToken(",","{",NULL);
    parseParameters(p,node,"sematr,isemcnt,maxsem");
    p.getToken("}");
}

DECLARE_API(CRE_FLG,"CRE_FLG")
{
    Token token;
    Directory * node;

    p.getToken(token);
    node = allocate(container[OBJECTTREE], token, EVENTFLAG);
    (*node)["position"] = p.getStreamLocation();

    p.getToken(",","{",NULL);
    parseParameters(p,node,"flgatr,iflgptn");
    p.getToken("}");
}

DECLARE_API(CRE_DTQ,"CRE_DTQ")
{
    Token token;
    Directory * node;

    p.getToken(token);
    node = allocate(container[OBJECTTREE], token, DATAQUEUE);
    (*node)["position"] = p.getStreamLocation();

    p.getToken(",","{",NULL);
    parseParameters(p,node,"dtqatr,dtqcnt");
    p.getToken(",","NULL","}",NULL);
}

DECLARE_API(CRE_MBX,"CRE_MBX")
{
    Token token;
    Directory * node;

    p.getToken(token);
    node = allocate(container[OBJECTTREE], token, MAILBOX);
    (*node)["position"] = p.getStreamLocation();

    p.getToken(",","{",NULL);
    parseParameters(p,node,"mbxatr,maxmpri");
    p.getToken(",","NULL","}",NULL);
}

DECLARE_API(CRE_MPF,"CRE_MPF")
{
    Token token;
    Directory * node;

    p.getToken(token);
    node = allocate(container[OBJECTTREE], token, FIXEDSIZEMEMORYPOOL);
    (*node)["position"] = p.getStreamLocation();

    p.getToken(",","{",NULL);
    parseParameters(p,node,"mpfatr,blkcnt,blksz");
    p.getToken(",","NULL","}",NULL);
}

DECLARE_API(CRE_CYC,"CRE_CYC")
{
    Token token;
    Directory * node;

    p.getToken(token);
    node = allocate(container[OBJECTTREE], token, CYCLICHANDLER);
    (*node)["position"] = p.getStreamLocation();

    p.getToken(",","{",NULL);
    parseParameters(p,node,"cycatr,exinf,cychdr,cyctim,cycphs");
    p.getToken("}");
}

DECLARE_API(DEF_INH,"DEF_INH")
{
    Token token;
    Directory * node;

    p.getToken(token);
    node = allocate(container[OBJECTTREE], token, INTERRUPTHANDLER, false);
    (*node)["position"] = p.getStreamLocation();

    p.getToken(",","{",NULL);
    parseParameters(p,node,"inhatr,inthdr");
    p.getToken("}");
}

DECLARE_API(DEF_EXC,"DEF_EXC")
{
    Token token;
    Directory * node;

    p.getToken(token);
    node = allocate(container[OBJECTTREE], token, EXCEPTIONHANDLER, false);
    (*node)["position"] = p.getStreamLocation();

    p.getToken(",","{",NULL);
    parseParameters(p,node,"excatr,exchdr");
    p.getToken("}");
}

DECLARE_API(ATT_INI,"ATT_INI")
{
    Token token;
    Directory * node;

    node = container.openChild(OBJECTTREE,INITIALIZER,NULL)->addChild();
    last = node;

    (*node)["position"] = p.getStreamLocation();

    p.getToken("{",NULL);
    parseParameters(p,node,"iniatr,exinf,inirtn");
    p.getToken("}");
}

DECLARE_API(ATT_FIN, "VATT_TER")
{
    Token token;
    Directory * node;

    node = container.openChild(OBJECTTREE,TERMINATOR,NULL)->addChild();
    last = node;

    (*node)["position"] = p.getStreamLocation();

    p.getToken("{",NULL);
    parseParameters(p,node,"teratr,exinf,terrtn");
    p.getToken("}");
}


