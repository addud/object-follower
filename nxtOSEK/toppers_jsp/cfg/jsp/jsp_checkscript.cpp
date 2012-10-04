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
 *  @(#) $Id: jsp_checkscript.cpp,v 1.18 2005/07/27 10:26:30 honda Exp $
 */

// $Header: /home/CVS/configurator/jsp/jsp_checkscript.cpp,v 1.18 2005/07/27 10:26:30 honda Exp $

#include "jsp/jsp_defs.h"
#include "jsp/jsp_common.h"

#include <string>
#include <iostream>

#include "base/component.h"
#include "base/mpstrstream.h"

using namespace std;
using namespace ToppersJsp;

class CheckScriptGenerator : public Component
{
protected:
    virtual void parseOption(Directory & container);
    virtual void body(Directory & container);
    
    void insertMagic(void) throw(Exception);

public:
    CheckScriptGenerator(void) : Component(FINALIZE) {};
} instance_of_CheckScriptGenerator;

void CheckScriptGenerator::parseOption(Directory & container)
{
    MultipartStream * stream;
    string work;

    if(findOption("h","help"))
    {
        cerr << '\n' << Message(
            "Configuration Checker Script Generation Option\n"
            "  -c, --check  : Generate a checker script\n",
            "�����ͥ빽�������å�������ץ������ѥ��ץ����\n"
            "  -c, --check  : �����å�������ץȤ��������ޤ�\n");
        return;
    }

    if(findOption("c","check",&work))
    {
        if(work.empty())
            work.assign("kernel_chk.c");

        stream = new MultipartStream(work);
        stream->createPart("header")
               .createPart("body")
               .createPart("footer");

        container["/file/kernel_chk"] = stream;

        checkOption("ci","checker-macro");
        activateComponent();
    }
}

static void createScriptEntry(Directory & container, MultipartStream * out, const char * objname, const char * member, bool mode = true)
{
    string work;
    string inib;
    Directory * scope;
    int i, j;
    
    (*out) << container.format("\n\t\t/* $@ */\n\n");

    if(mode)
    {
        scope = container.getFirstChild();
        while(scope != 0)
        {
            work = scope->getKey();
            if(work[0] < '0' || work[1] > '9')
                (*out) << "\tOBJECT(" << container.getKey() << '_' << scope->toInteger() << ',' << work << ");\n";

            scope = scope->getNext();
        }

        (*out) << container.format("\tEVAR(ID,_kernel_tmax_$(/prefix/$@/id)id);\n");
    }else
    {
        i = 0;
        scope = container.getFirstChild();
        while(scope != 0)
        {
            work = scope->getKey();
            (*out) << "\tOBJECT(" << container.getKey() << '_' << (i++) << ',' << scope->getKey() << ");\n";
            scope = scope->getNext();
        }

        (*out) << container.format("\tEVAR(ID,_kernel_tnum_$(/prefix/$@/id)no);\n");
    }

    (*out) << container.format("\tEVAR($(/prefix/$@/SID)INIB,_kernel_$(/prefix/$@/sid)inib_table);\n");

    work.assign(member);
    i = 0;
    j = work.find_first_of(',');
    if(objname == NULL)
        inib = container.getKey();
    else
        inib = objname;
    
    do {
        (*out) << "\tMEMBER(" << inib << "_initialization_block," << work.substr(i, j-i) << ");\n";

        i = j + 1;
        j = work.find_first_of(',', i);
    } while(i != string::npos+1);
    (*out) << '\n';
}

inline void createScriptEntry(Directory & container, MultipartStream * out, const char * member)
{   createScriptEntry(container, out, NULL, member, true);  }

void CheckScriptGenerator::insertMagic(void) throw(Exception)
{
    KernelCfg * out = dynamic_cast<KernelCfg *>(RuntimeObjectTable::getInstance(typeid(KernelCfg)));
    if(out != 0) {
        out->movePart("others");
        out->createPart("checkscript");
        (*out) << Message("\t/* Variables for kernel checker */\n", "\t/* �����ͥ�����å����ѿ� */\n");
        (*out) << "const UW _checker_magic_number = 0x01234567;\n\n";
    }
}

void CheckScriptGenerator::body(Directory & container)
{
    MultipartStream * out;

    out = reinterpret_cast<MultipartStream *>(container["/file/kernel_chk"].toPointer());

    out->movePart("header") <<
        "#include \"jsp_kernel.h\"\n"
        "#include \"logtask.h\"\n"
        "#include \"timer.h\"\n\n";


	string work;
	if(findOption("ci","checker-macro",&work)) {

			/* ��Ȥ����Ǥʤ��ä���include�򤹤뤬�����ʤ�include�����Ǥ��ʤ� */
		if(!work.empty())
			(*out) << "#include \"" << work << "\"\n\n";
	}
	else {
		(*out) <<	"#define OBJECT(x,y) __asm(\"d\" #x \",\" #y \"@\");\n"
			        "#define MEMBER(x,y) __asm(\"s\" #x \"::\" #y \",(%0),(%1)@\" ::\\\n"
			        "     \"i\"(sizeof(((struct x *)0)->y)), \"i\"(&((struct x *)0)->y));\n"
			        "#define VAR(x) __asm(\"s\" #x \",(%0),(0)@\" :: \"i\"(sizeof(x)));\n"
			        "#define EVAR(x,y) __asm(\"s\" #y \",(%0),(0)@\" :: \"i\"(sizeof(x)));\n"
			        "#define SVAR(x) __asm(\"s\" #x \",(%0),(0)@\" :: \"i\"(sizeof(x[0])));\n"
			        "#define DEFS(x) __asm(\"s\" #x \",(%0),(0)@\" :: \"i\"((unsigned long)x));\n\n";
	}

    (*out) <<	"#include \"queue.h\"\n\n"
		        "#include \"task.h\"\n"
		        "#include \"semaphore.h\"\n"
		        "#include \"eventflag.h\"\n"
		        "#include \"dataqueue.h\"\n"
		        "#include \"mailbox.h\"\n"
		        "#include \"mempfix.h\"\n"
		        "#include \"cyclic.h\"\n"
		        "#include \"../kernel/exception.h\"\n"
		        "#include \"interrupt.h\"\n"
		        "#include \"wait.h\"\n\n"
		        "void checker_function(void)\n{\n";

    out->movePart("footer") << "}\n";

    out->movePart("body") <<
        "\tDEFS(TMAX_TPRI);\n\tDEFS(TMIN_TPRI);\n\n"
        "\tDEFS(TMAX_MPRI);\n\tDEFS(TMIN_MPRI);\n\n"
//      "\tDEFS(TMAX_MAXSEM);\n\n"
        "\tDEFS(TMAX_RELTIM);\n\n"
        "\tMEMBER(queue,next);\n\tMEMBER(queue,prev);\n\n";

    createScriptEntry(container[OBJECTTREE "/" TASK],      out, "tskatr,exinf,task,ipriority,stksz,stk,texatr,texrtn");
    createScriptEntry(container[OBJECTTREE "/" SEMAPHORE], out, "sematr,isemcnt,maxsem");
    createScriptEntry(container[OBJECTTREE "/" EVENTFLAG], out, "flgatr,iflgptn");
    createScriptEntry(container[OBJECTTREE "/" DATAQUEUE], out, "dtqatr,dtqcnt,dtq");
    createScriptEntry(container[OBJECTTREE "/" MAILBOX], out, "mbxatr,maxmpri");
    createScriptEntry(container[OBJECTTREE "/" FIXEDSIZEMEMORYPOOL], out, "fixed_memorypool", "mpfatr,blksz,mpf,limit");
    createScriptEntry(container[OBJECTTREE "/" CYCLICHANDLER], out, "cyclic_handler", "cycatr,exinf,cychdr,cyctim,cycphs");
    createScriptEntry(container[OBJECTTREE "/" INTERRUPTHANDLER], out, "interrupt_handler", "inhno,inhatr,inthdr", false);
    createScriptEntry(container[OBJECTTREE "/" EXCEPTIONHANDLER], out, "cpu_exception_handler", "excno,excatr,exchdr", false);

    insertMagic();

    VerboseMessage("Configuration check script generation was finished successfully.\n","�����ͥ빽�������å�������ץȥե��������Ϥ��ޤ���\n");
}

