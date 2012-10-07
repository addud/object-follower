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
 *  @(#) $Id: coverage.cpp,v 1.5 2003/12/15 07:32:13 takayuki Exp $
 */

#include "base/coverage_defs.h"
#include "base/coverage_undefs.h"

#include <iostream>
#include <iomanip>

using namespace std;

#if defined(COVERAGE)
/*
 *   ��ñ�ʥ��Х�å������å�
 */

    //�ե����ޥåȺѤߥե�������־���μ���
string Coverage::Location::getDetails(void) const
{
    string result;

    result = string(filename) + ":" + String(lineno);
    if(*additional != '\x0')
        result += string("(") + additional + ")";

    return result;
}



    //���Ǥ������
Coverage::BranchMap::~BranchMap(void) throw()
{
    iterator scope;

    scope = begin();
    while(scope != end()) {
        delete scope->second;
        ++ scope;
    }

    clear();
}

    //���Ǥ���Ͽ
Coverage::BranchBase::BranchBase(const Location & location) throw()
{
    BranchMap * bmap = Singleton<BranchMap>::getInstance();
    NewBranchList * blist = Singleton<NewBranchList>::getInstance();

    (*bmap)[location] = this;
    blist->push_back(this);
}

    //location�˰��פ������Ǥμ���
Coverage::BranchBase * Coverage::BranchBase::find(const Location & location) throw()
{
    BranchMap * bmap = Singleton<BranchMap>::getInstance();
    BranchMap::iterator scope;
    BranchBase * result = 0;

    scope = bmap->find(location);
    if(scope != bmap->end())
        result = scope->second;

    return result;
}

    //BranchIf���󥹥ȥ饯��
Coverage::If::If(const Location & location) throw() : BranchBase(location), true_case(false), false_case(false)
{}

    //if��������Ƚ�� (��Ω/����Ω��ξ�������äƤ���)
bool Coverage::If::checkValidity(void) const throw()
{   return true_case && false_case;   }

    //�̲����μ���
string Coverage::If::getDetails(void) const throw()
{
    string result;

    if(true_case)
        result += "true";

    if(false_case) {
        if(true_case)
            result += "/";
        result += "false";
    }

    return result;
}

    //ifʬ���Υ����å�
bool Coverage::If::branch(const Location & location, bool expression) throw()
{
    If * node = dynamic_cast<If *>(find(location));
    if(node == 0)
        node = new(nothrow) If(location);

    if(node != 0) {
        if(expression)
            node->true_case = true;
        else
            node->false_case = true;
    }
    else
        cerr << "[Coverage::Branch] Memory allocation error!\n";

    return expression;
}


    //While���󥹥ȥ饯��
Coverage::While::While(const Location & location) throw() : BranchBase(location), valid(false)
{}

    //While��������Ƚ�� (���ʤ��Ȥ���ϥ롼�פ����ޤ�äƤ���)
bool Coverage::While::checkValidity(void) const throw()
{   return valid;   }

    //�̲����μ���
string Coverage::While::getDetails(void) const throw()
{
    string result;

    if(valid)
        result = "valid";
    else
        result = "invalid";

    return result;
}

    //whileʬ���Υ����å� (���ʤ��Ȥ���ϥ롼�פ����ޤ�äƤ���)
bool Coverage::While::branch(const Location & location, bool expression) throw()
{
    While * node = dynamic_cast<While *>(find(location));
    if(node == 0)
        node = new(nothrow) While(location);

    if(node != 0) {
        if(expression)
            node->valid = true;
    }
    else
        cerr << "[Coverage::Branch] Memory allocation error!\n";

    return expression;
}


    //Switch���󥹥ȥ饯��
Coverage::Switch::Switch(const Location & location) throw() : BranchBase(location)
{}

    //Switch��������Ƚ�� (�̲ᤷ�����Ǥ�����Ф��Ƥ��� (�塹Ƚ������줿��))
bool Coverage::Switch::checkValidity(void) const throw()
{   return true;   }

    //�̲����μ���
string Coverage::Switch::getDetails(void) const throw()
{
    stringstream buf;
    set<int>::const_iterator scope;

    scope = checkpoint.begin();
    while(scope != checkpoint.end()) {
        buf << *scope;

        ++ scope;
        if(scope != checkpoint.end())
            buf << ", ";
    }
        
    return buf.str();
}

    //Switchʬ���Υ����å�
void Coverage::Switch::_branch(const Location & location, int expression) throw()
{
    Switch * node = dynamic_cast<Switch *>(find(location));
    if(node == 0)
        node = new(nothrow) Switch(location);

    if(node != 0) {
        if(expression)
            node->checkpoint.insert(expression);
    }
    else
        cerr << "[Coverage::Branch] Memory allocation error!\n";
}

    //���Ƥι��ܤ�ɽ��
void Coverage::printCoverage(ostream & out)
{
    BranchMap * bmap = Singleton<BranchMap>::getInstance();
    BranchMap::iterator scope;

    unsigned long cases = 0;
    unsigned long fails = 0;

    scope = bmap->begin();
    while(scope != bmap->end()) {
        ++ cases;

        if(scope->second->checkValidity())
            out << "Success : ";
        else {
            out << "Failure : ";
            ++ fails;
        }
        out << scope->first.getDetails() << ' ' << scope->second->getDetails() << '\n';

        ++ scope;
    }

    out << fails << " fails in " << cases << " cases (" << setprecision(2) << (fails * 100.0 / cases) << "%)\n";
}

    //�����̲ᤷ�����ɤ����Υ����å�
bool Coverage::checkValidity(void)
{
    bool result = true;

    NewBranchList * blist = Singleton<NewBranchList>::getInstance();
    NewBranchList::iterator scope;

    scope = blist->begin();
    while(scope != blist->end()) {
        if(!(*scope)->checkValidity())
            result = false;
        ++ scope;
    }

    blist->clear();
    return result;
}
    //̾�Τμ���
string Coverage::getBranchName(BranchBase * node)
{
        //���פ������Ǥθ���
    BranchMap * bmap = Singleton<BranchMap>::getInstance();
    BranchMap::iterator scope;

    scope = bmap->begin();
    while(scope != bmap->end()) {
        if(scope->second == node)
            break;
        ++ scope;
    }

    //assert(scope != bmap->end());
    
    return scope->first.getDetails();
}

#endif /* COVERAGE */

