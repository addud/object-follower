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
 *  @(#) $Id: jsp_check.cpp,v 1.25 2005/07/06 01:29:21 honda Exp $
 */

// $Header: /home/CVS/configurator/jsp/jsp_check.cpp,v 1.25 2005/07/06 01:29:21 honda Exp $

#include "base/defs.h"
#include "jsp/jsp_defs.h"
#include "base/message.h"
#include "base/component.h"
#include "base/filecontainer.h"

#include <fstream>
#include <iomanip>

class ConfigurationChecker : public Component
{
public:

    enum tagCheckLevel
    {
        UNKNOWN    = 0,
        LAZY       = 1,     /* ��̿Ū (�Ԥ��᤮��¤�ɻ���)  */
        STANDARD   = 2,     /* ITRON���ͤ��ϰ� (��¤�����) */
        TOPPERS    = 4,     /* TOPPERS/JSP���ϰ���          */
        RESTRICTED = 8,     /* �Ҥ�ü������ޤ���           */

        NORMAL     = 8
    };

protected:
    enum tagCheckLevel current_level;

    unsigned int error_count;
    std::string banner;

    void set_banner(Directory &, Formatter , const char *, int);
    void notify(enum tagCheckLevel, Formatter , bool = true);

    bool check_taskblock(Directory &, FileContainer *);
    bool check_semaphoreblock(Directory &, FileContainer *);
    bool check_eventflagblock(Directory &, FileContainer *);
    bool check_dataqueueblock(Directory &, FileContainer *);
    bool check_mailboxblock(Directory &, FileContainer *);
    bool check_fixed_memorypoolblock(Directory &, FileContainer *);
    bool check_cyclic_handlerblock(Directory &, FileContainer *);
    bool check_interrupt_handlerblock(Directory &, FileContainer *);
    bool check_exception_handlerblock(Directory &, FileContainer *);

    virtual void parseOption(Directory &);
    virtual void body(Directory &);

public:
    ConfigurationChecker(void) throw();
    ~ConfigurationChecker(void) throw() {}
};

//------------------------------------------------------
using namespace std;

static ConfigurationChecker  instance_of_ConfigurationChecker;

//------------------------------------------------------
    //�������åȤ�Ʊ̾�η������礭�ʷ������
    // (��) �����, �黻����ǽ�ʷ��Ǥ��뤳��

typedef          int  DT_INT;
typedef unsigned int  DT_UINT;
typedef unsigned long DT_FP;
typedef unsigned long DT_VP_INT;
typedef unsigned long DT_VP;
typedef          long DT_RELTIM;

//------------------------------------------------------

ConfigurationChecker::ConfigurationChecker(void) throw()
{
    setBanner("--- TOPPERS/JSP Configuration Checker (ver 2.4) ---");
}

void ConfigurationChecker::set_banner(Directory & container, Formatter object, const char * type, int id)
{
    Directory * node;
    char buffer[32];

    banner = string("    ") + object.str() + " : ";

    sprintf(buffer, "id = %d", id);

    node = container.findChild(OBJECTTREE, type, NULL)->getFirstChild();
    while(node != 0 && node->toInteger() != id)
        node = node->getNext();

    if( node != 0 ) {
        banner += node->getKey() + " (" + buffer + ") ";

        node = node->findChild("position");
        if(node != 0)
            banner += string("at ") + node->toString();
    }
    else
        banner += buffer;

    if(VerboseMessage::getVerbose())
    {
        cout << banner << endl;
        banner.erase();
    }
}

void ConfigurationChecker::notify(enum tagCheckLevel level, Formatter msg, bool error)
{
    if((level & current_level) != 0)
    {

        if(!banner.empty())
        {
            cout << banner << endl;
            banner.erase();
        }

        cout << "      ";

        if(error)
        {
            cout << Message("[ Error ] ","[���顼] ");
            error_count ++;
        }else
            cout << Message("[Warning] ","[ �ٹ� ] ");
        cout << msg << endl;
    }
}

    /*
     * ���������֥������Ȥ˴ؤ��륨�顼����
     */

bool ConfigurationChecker::check_taskblock(Directory & parameter, FileContainer * container)
{
    unsigned int id;
    unsigned int maxpri;
    unsigned int minpri;
    unsigned int old_error_count = error_count;

    TargetVariable<unsigned int> _kernel_tmax_tskid("_kernel_tmax_tskid");

    Message object("Task","������");

    if(!_kernel_tmax_tskid.isValid())
        ExceptionMessage(
            "Internal error: Unknown symbol (Probably, Symbol table was stripped)",
            "�������顼: �����ʥ���ܥ�̾ (�¹Է���������ܥ�ơ��֥��ޤ�Ǥʤ���ǽ��������ޤ�)").throwException();

    if(*_kernel_tmax_tskid < 1)
    {
        notify(RESTRICTED,
            Message("  [Task] : No tasks created\n","  [������] : ���������֥������Ȥ�����ޤ���\n"));
        return true;
    }

    TargetVariable<DT_UINT> tskatr("_kernel_tinib_table", "task_initialization_block::tskatr");
    TargetVariable<DT_FP>   task("_kernel_tinib_table", "task_initialization_block::task");
    TargetVariable<DT_INT>  ipriority("_kernel_tinib_table", "task_initialization_block::ipriority");
    TargetVariable<DT_UINT> texatr("_kernel_tinib_table", "task_initialization_block::texatr");
    TargetVariable<DT_UINT> stksz("_kernel_tinib_table", "task_initialization_block::stksz");

    maxpri = container->getVariableInfo("TMAX_TPRI").value;
    minpri = container->getVariableInfo("TMIN_TPRI").value;

    VerboseMessage("% object : % items\n","%���֥������� : % ��\n") << object << *_kernel_tmax_tskid;
    for(id = 1; id <= *_kernel_tmax_tskid; id++)
    {
        set_banner(parameter, object, TASK, id);

            /*
             *  °�������å�
             */

            // °���ͤ� TA_HLNG|TA_ASM|TA_ACT �ʳ����ͤ�ȤäƤ���
        if((*tskatr & ~0x3) != 0)
            notify( STANDARD,
                Message("Illegal task attribute (It should be ((TA_HLNG||TA_ASM)|TA_ACT))",
                        "�����ʥ�����°�� ((TA_HLNG||TA_ASM)|TA_ACT)�ʳ�"));

            // °���ͤ� TA_ASM ���ޤޤ�Ƥ���
        if((*tskatr & 0x1) != 0)
            notify( RESTRICTED,
                Message("TA_ASM specified as task attribute takes no effect.",
                        "������°����TA_ASM�����ꤵ��Ƥ���"));

            /* ��ư���Ϥ�0 */
        if(*task == 0)
            notify(RESTRICTED,
                Message("The address of task routine is equal to zero.",
                        "�������Ϥ�0�����ꤵ��Ƥ��ޤ�"));

            /*
             *  ͥ���٥����å�
             */

            // ����ͥ���٤ȺǾ�ͥ���٤����꤬��������
        if(maxpri < minpri)
            notify(LAZY,
                Message("Illegal Priority Settings found (TMAX_TPRI(%) < TMIN_TPRI).",
                        "���ͥ���٤�����ͥ����(%)��Ķ���Ƥ���") << minpri);

            // ͥ���٤��ϰϤ�[�Ǿ�ͥ����, ����ͥ����]���ϰϤ�Ķ���Ƥ���
        if(*ipriority > (signed)(maxpri - minpri))
            notify(TOPPERS,
                Message("Initial priority is greater than maximum priority (%).",
                        "���ͥ���٤�����ͥ����(%)��Ķ���Ƥ���") << maxpri);
        if(*ipriority < 0)
            notify(STANDARD,
                Message("Initial priority is less than the minimum priority (%).",
                        "���ͥ���٤�����ͥ����(%)�򲼲��") << minpri);

            /*
             *   �������㳰°�������å�
             */

            // °���ͤ�TA_HLNG or TA_ASM�Ǥʤ�
        if((*texatr & ~0x3) != 0)
            notify(STANDARD,
                Message("Task exception routine has an illegal attribute specifier.",
                        "�������㳰��̵����°��(TA_HLNG,TA_ASM�ʳ�) �����ꤵ��Ƥ��ޤ�"));

            // °���ͤ� TA_ASM ���ޤޤ�Ƥ���
        if((*texatr & 0x1) != 0)
            notify( RESTRICTED,
                Message("TA_ASM, specified as texatr, does not always take effect.",
                        "�������㳰��TA_ASM�����ꤵ��Ƥ��ޤ�"));

            /*
             *   �����å������å�
             */

            // �����å���������0
        if(*stksz == 0)
            notify(RESTRICTED,
                Message("Stack size is equal to zero.",
                        "�����å���������0�����ꤵ��Ƥ��ޤ�"));

            // �����å������Ϥ�0
        if(*stksz == 0)
            notify(RESTRICTED,
                Message("The address of task stack is equal to zero.",
                        "�����å��������Ϥ�0�����ꤵ��Ƥ��ޤ�"));

        ++ tskatr, ++ task, ++ ipriority, ++ texatr, ++ stksz;
    }

    return old_error_count == error_count;
}

bool ConfigurationChecker::check_semaphoreblock(Directory & parameter, FileContainer * container)
{
    unsigned int id;
    unsigned int old_error_count = error_count;

    Message object("Semaphore","���ޥե�");

    TargetVariable<DT_UINT> _kernel_tmax_semid("_kernel_tmax_semid");
    if(*_kernel_tmax_semid < 1)
        return true;

    TargetVariable<DT_UINT> sematr("_kernel_seminib_table","semaphore_initialization_block::sematr");
    TargetVariable<DT_UINT> maxsem("_kernel_seminib_table","semaphore_initialization_block::maxsem");
    TargetVariable<DT_UINT> isemcnt("_kernel_seminib_table","semaphore_initialization_block::isemcnt");

    VerboseMessage("% object : % items\n","%���֥������� : % ��\n")
        << object << *_kernel_tmax_semid;

    for(id = 1; id <= *_kernel_tmax_semid; id++)
    {
        set_banner(parameter, object, SEMAPHORE, id);

            //attribute validation check
        if((*sematr & ~0x1) != 0)
            notify(STANDARD,
                Message("Illegal attribute (It should be (TA_TFIFO||TA_TPRI)).",
                        "(TA_TFIFO||TA_TPRI)�ʳ���°�������ꤵ��Ƥ���"));

            //maxcnt < isemcnt
        if(*maxsem < *isemcnt)
            notify(STANDARD,
                Message("Initial count[%] is greater than the maximum count[%] of this semaphore",
                        "�����[%]��������[%]��Ķ���Ƥ���") << *isemcnt << *maxsem);

        if(*maxsem == 0)
            notify(STANDARD,
                Message("Maximum count must be greater than zero.",
                        "���ޥե��κ��祫����Ȥ�1�ʾ�Ǥʤ���Ф����ޤ���"));

        ++ sematr, ++ maxsem, ++ isemcnt;
    }

    return old_error_count == error_count;
}


bool ConfigurationChecker::check_eventflagblock(Directory & parameter, FileContainer * container)
{
    unsigned int id;
    unsigned int old_error_count = error_count;

    Message object("Event flag","���٥�ȥե饰");

    TargetVariable<DT_UINT> _kernel_tmax_flgid("_kernel_tmax_flgid");
    if(*_kernel_tmax_flgid < 1)
        return true;

    TargetVariable<DT_UINT> flgatr("_kernel_flginib_table","eventflag_initialization_block::flgatr");

    VerboseMessage("% object : % items\n","%���֥������� : % ��\n")
         << object << *_kernel_tmax_flgid;

    for(id = 1; id <= *_kernel_tmax_flgid; id++)
    {
        set_banner(parameter, object, EVENTFLAG, id);
            
            //attribute validation check
        if((*flgatr & ~0x7) != 0)
            notify(STANDARD,
                Message("Illegal attribute value [0x%]",
                        "��������°���� [0x%]") << setbase(16) << (*flgatr & ~0x7));

        if((*flgatr & 0x2) != 0)
            notify(TOPPERS,     //��¸����ľ��ʤ��Τ�RESTRICTED�ˤ��ʤ�
                Message("Attribute TA_WMUL is not supported in current version.",
                        "TA_WMUL�ϥ��ݡ��ȳ�"));
    
        ++ flgatr;
    }

    return old_error_count == error_count;
}


bool ConfigurationChecker::check_dataqueueblock(Directory & parameter, FileContainer * container)
{
    unsigned int id;
    unsigned int old_error_count = error_count;

    Message object("Data queue","�ǡ������塼");

    TargetVariable<DT_UINT> _kernel_tmax_dtqid("_kernel_tmax_dtqid");
    if(*_kernel_tmax_dtqid < 1)
        return true;

    TargetVariable<DT_UINT> dtqatr("_kernel_dtqinib_table", "dataqueue_initialization_block::dtqatr");
    TargetVariable<DT_UINT> dtqcnt("_kernel_dtqinib_table", "dataqueue_initialization_block::dtqcnt");
    TargetVariable<DT_VP_INT> dtq("_kernel_dtqinib_table", "dataqueue_initialization_block::dtq");

    VerboseMessage("% object : % items\n","%���֥������� : % ��\n")
        << object << *_kernel_tmax_dtqid;

    for(id = 1; id <= *_kernel_tmax_dtqid; id++)
    {
        set_banner(parameter, object, DATAQUEUE, id);

            //attribute validation check
        if((*dtqatr & ~0x1) != 0)
            notify(STANDARD,
                Message("Illegal attribute value [0x%]",
                        "��������°���� [0x%]") << setbase(16) << (*dtqatr & ~0x1));

        if(*dtqcnt != 0 && *dtq == 0)
            notify(TOPPERS,
                Message("Dataqueue buffer should not be NULL", "�ǡ������塼�ΥХåե���NULL��"));

        ++ dtqatr, ++ dtqcnt, ++ dtq;
    }

    return old_error_count == error_count;
}


bool ConfigurationChecker::check_mailboxblock(Directory & parameter, FileContainer * container)
{
    unsigned int id;
    unsigned int old_error_count = error_count;

    Message object("Mailbox","�᡼��ܥå���");

    TargetVariable<DT_UINT> _kernel_tmax_mbxid("_kernel_tmax_mbxid");
    if(*_kernel_tmax_mbxid < 1)
        return true;
    
    TargetVariable<DT_UINT> mbxatr("_kernel_mbxinib_table","mailbox_initialization_block::mbxatr");
    TargetVariable<DT_INT>  maxmpri("_kernel_mbxinib_table","mailbox_initialization_block::maxmpri");

    DT_INT maxpri = container->getVariableInfo("TMAX_MPRI").value;
    DT_INT minpri = container->getVariableInfo("TMIN_MPRI").value;

    VerboseMessage("% object : % items\n","%���֥������� : % ��\n") << object << *_kernel_tmax_mbxid;
    for(id = 1; id <= *_kernel_tmax_mbxid; id++)
    {
        set_banner(parameter, object, MAILBOX, id);

            //attribute validation check
        if((*mbxatr & ~0x3) != 0)
            notify(STANDARD,
                Message("Illegal attribute value [0x%]",
                        "��������°���� [0x%]") << setbase(16) << (*mbxatr & ~0x3));
    
            //mailbox message priority check
        if(*maxmpri < 0)
            notify(STANDARD,
                Message("Priority must not be a negative number.","ͥ���٤�����"));

        if(*maxmpri < minpri)
            notify(STANDARD,
                Message("Message priority should be greater than or equal to %.",
                        "��å�����ͥ���٤�%�ʾ�Ǥʤ���Ф����ޤ���") << minpri);

        if(*maxmpri > maxpri)
            notify(STANDARD,
                Message("Message priority should be less than or equal to %.",
                        "��å�����ͥ���٤�%�ʲ��Ǥʤ���Ф����ޤ���") << maxpri);

        ++ mbxatr, ++ maxmpri;
    }

    return old_error_count == error_count;
}

bool ConfigurationChecker::check_fixed_memorypoolblock(Directory & parameter, FileContainer * container)
{
    unsigned int id;
    unsigned int old_error_count = error_count;

    Message object("Fixed size memory pool","����Ĺ����ס���");

    TargetVariable<DT_UINT> _kernel_tmax_mpfid("_kernel_tmax_mpfid");
    if(*_kernel_tmax_mpfid < 1)
        return true;

    TargetVariable<DT_UINT> mpfatr("_kernel_mpfinib_table", "fixed_memorypool_initialization_block::mpfatr");
    TargetVariable<DT_UINT> limit ("_kernel_mpfinib_table", "fixed_memorypool_initialization_block::limit");
    TargetVariable<DT_VP>   mpf   ("_kernel_mpfinib_table", "fixed_memorypool_initialization_block::mpf");
    TargetVariable<DT_UINT> blksz ("_kernel_mpfinib_table", "fixed_memorypool_initialization_block::blksz");

    VerboseMessage("% object : % items\n","%���֥������� : % ��\n") << object << *_kernel_tmax_mpfid;
    for(id = 1; id <= *_kernel_tmax_mpfid; id++)
    {
        set_banner(parameter, object, FIXEDSIZEMEMORYPOOL, id);

            //attribute validation check
        if((*mpfatr & ~0x1) != 0)
            notify(STANDARD,
                Message("Illegal attribute value [0x%]","��������°���� [0x%]") << (*mpfatr & ~0x1));

            //�֥�å�����0
        if(*mpf == *limit)
            notify(STANDARD,
                Message("blkcnt should be a non-zero value.","�֥�å�����0�Ǥ�"));

            //�֥�å���������0
        if(*blksz == 0)
            notify(STANDARD,
                Message("blksz should be a non-zero value.","�֥�å���������0�Ǥ�"));

            //�Хåե����ɥ쥹��0
        if(*mpf == 0)
            notify(TOPPERS,
                Message("buffer address is a NULL pointer.","�Хåե����ɥ쥹��NULL�ݥ��󥿤ˤʤäƤ��ޤ�"));

        ++ mpfatr, ++ limit, ++ mpf, ++ blksz;
    }

    return old_error_count == error_count;
}


bool ConfigurationChecker::check_cyclic_handlerblock(Directory & parameter, FileContainer * container)
{
    unsigned int id;
    unsigned int old_error_count = error_count;

    Message object("Cyclic handler","�����ϥ�ɥ�");

    TargetVariable<DT_UINT> _kernel_tmax_cycid("_kernel_tmax_cycid");
    if(*_kernel_tmax_cycid < 1)
        return true;

    DT_RELTIM maxreltim = container->getVariableInfo("TMAX_RELTIM").value;
    TargetVariable<DT_UINT> cycatr("_kernel_cycinib_table", "cyclic_handler_initialization_block::cycatr");
    TargetVariable<DT_RELTIM> cyctim("_kernel_cycinib_table", "cyclic_handler_initialization_block::cyctim");
    TargetVariable<DT_RELTIM> cycphs("_kernel_cycinib_table", "cyclic_handler_initialization_block::cycphs");

    VerboseMessage("% object : % items\n","%���֥������� : % ��\n") << object << *_kernel_tmax_cycid;
    for(id = 1; id <= *_kernel_tmax_cycid; id++)
    {
        set_banner(parameter, object, CYCLICHANDLER, id);

            //attribute validation check
        if((*cycatr & ~0x7) != 0)
            notify(STANDARD,
                Message("Illegal attribute value [0x%]","��������°���� [0x%]") << (*cycatr & ~0x1));

        if((*cycatr & 0x4) != 0)
            notify(TOPPERS,     //���¸���ʤΤ�RESTRICTED�ˤ��ʤ�
                Message("TA_PHS is not supported in this kernel.","TA_PHS�ϥ��ݡ��ȳ�"));

            // °���ͤ� TA_ASM ���ޤޤ�Ƥ���
        if((*cycatr & 0x1) != 0)
            notify( RESTRICTED,
                Message("TOPPERS/JSP Kernel never minds the flag 'TA_ASM'.",
                        "TOPPERS/JSP�����ͥ�����Ƥε����¸����TA_ASM�򥵥ݡ��Ȥ���Ȥϸ¤�ʤ�"));

            //RELTIM�Ǥ�ɽ���ϰ���ˤ��뤫�ɤ����Υ����å�
        if(*cyctim > maxreltim)
            notify(STANDARD,
                Message("The cyclic object has a period (%) that exceeds the maximum period (%)",
                        "��ư����(%)��ɽ����ǽ�����л��֤��ϰ�(%)��Ķ���Ƥ��ޤ�") << *cyctim << maxreltim);

            //��ư������0�Ǥʤ����ȤΥ����å�
        if(*cyctim == 0)
            notify(STANDARD,
                Message("The cyclic object has a ZERO period.",
                        "��ư������0�ˤʤäƤ��ޤ�"));

        if(*cycphs > maxreltim)
            notify(STANDARD,
                Message("The cyclic object has a initial delay (%) that exceeds the maximum period (%)",
                        "��ư����(%)��ɽ����ǽ�����л��֤��ϰ�(%)��Ķ���Ƥ��ޤ�") << *cycphs << maxreltim);

        ++ cycatr, ++ cyctim, ++ cycphs;
    }

    return old_error_count == error_count;
}

bool ConfigurationChecker::check_interrupt_handlerblock(Directory & parameter, FileContainer * container)
{
    unsigned int id;
    unsigned int old_error_count = error_count;

    Message object("Interrupt handler","����ߥϥ�ɥ�");

    TargetVariable<DT_UINT> _kernel_tnum_inhno("_kernel_tnum_inhno");
    if(*_kernel_tnum_inhno == 0)
        return true;

    TargetVariable<DT_UINT> inhatr("_kernel_inhinib_table", "interrupt_handler_initialization_block::inhatr");
    TargetVariable<DT_FP>   inthdr("_kernel_inhinib_table", "interrupt_handler_initialization_block::inthdr");

    VerboseMessage("% object : % items\n","%���֥������� : % ��\n") << object << *_kernel_tnum_inhno;
    for(id = 0; id < *_kernel_tnum_inhno; id++)
    {
        set_banner(parameter, object, INTERRUPTHANDLER, id);

            //attribute validation check
        if((*inhatr & 0x1) != 0)
            notify(STANDARD,
                Message("The attribute can take only TA_HLNG|TA_ASM",
                        "TA_HLNG|TA_ASM�ʳ���°��������Ǥ��ޤ���"));

            // °���ͤ� TA_ASM ���ޤޤ�Ƥ���
        if((*inhatr & 0x1) != 0)
            notify(RESTRICTED,
                Message("TOPPERS/JSP Kernel never minds the flag 'TA_ASM'.",
                        "TA_ASM�����Ѥ���Ƥ���"));

            // ��ư���ϥ����å�
        if(*inthdr == 0)
            notify(RESTRICTED,
                Message("NULL pointer is specified as an inthdr address.",
                        "����ߥϥ�ɥ�����Ϥ�NULL�Ǥ�"));

        ++ inhatr, ++ inthdr;
    }

    return old_error_count == error_count;
}

bool ConfigurationChecker::check_exception_handlerblock(Directory & parameter, FileContainer * container)
{
    unsigned int id;
    unsigned int old_error_count = error_count;

    Message object("Exception handler","�㳰�ϥ�ɥ�");

    TargetVariable<DT_UINT> _kernel_tnum_excno("_kernel_tnum_excno");
    if(*_kernel_tnum_excno == 0)
        return true;

    TargetVariable<DT_UINT> excatr("_kernel_excinib_table", "cpu_exception_handler_initialization_block::excatr");
    TargetVariable<DT_FP>   exchdr("_kernel_excinib_table", "cpu_exception_handler_initialization_block::exchdr");

    VerboseMessage("% object : % items\n","%���֥������� : % ��\n") << object << *_kernel_tnum_excno;
    for(id = 0; id < *_kernel_tnum_excno; id++)
    {
        set_banner(parameter, object, EXCEPTIONHANDLER, id);

            //attribute validation check
        if((*excatr & 0x1) != 0)
            notify(STANDARD,
                Message("The attribute can take only TA_HLNG|TA_ASM",
                        "TA_HLNG|TA_ASM�ʳ���°��������Ǥ��ޤ���"));

            // °���ͤ� TA_ASM ���ޤޤ�Ƥ���
        if((*excatr & 0x1) != 0)
            notify(RESTRICTED,
                Message("TOPPERS/JSP Kernel never minds the flag 'TA_ASM'.",
                        "TOPPERS/JSP�����ͥ�����Ƥε����¸����TA_ASM�򥵥ݡ��Ȥ���Ȥϸ¤�ʤ�"));

            // ��ư���ϥ����å�
        if(*exchdr == 0)
            notify(RESTRICTED,
                Message("NULL pointer is specified as an exchdr address.",
                        "�㳰�ϥ�ɥ�����Ϥ�NULL�Ǥ�"));

        ++ excatr, ++ exchdr;
    }

    return old_error_count == error_count;
}

//------------------------------------------------------

void ConfigurationChecker::parseOption(Directory & parameter)
{
    string loadmodule;
    string work;

    if(findOption("h","help"))
    {
        cout << endl << Message(
            "Configuration checker - option\n"
            "  -m, --module=filename : Specify the load module (essential option)\n"
            "  -cs, --script=filename  : Specify the checker script file\n"
            "  -cl, --checklevel=level : Specify one of the check levels below \n"
            "    l(azy)       : Minimum check will be performed.\n"
            "    s(tandard)   : includes some ITRON Standard check items.\n"
            "    t(oppers)    : checks whether it meets TOPPERS/JSP restrictions\n"
            "    r(estricted) : All of check items will be performed.\n",
            "����ե�����졼���������å� - ���ץ����\n"
            "  -m, --module=�ե�����̾ : ���ɥ⥸�塼��̾����ꤷ�ޤ� (ɬ�ܹ���)\n"
            "  -cs, --script=�ե�����̾  : �����å�������ץȤ���ꤷ�ޤ�\n"
            "  -cl, --checklevel=level : Specify one of the check levels below \n"
            "    l(azy)       : �Ǿ��¤Υ����å��Τߤ�Ԥ��ޤ�\n"
            "    s(tandard)   : ITRON���ͤ��ϰϤǥ����å���Ԥ��ޤ�\n"
            "    t(oppers)    : TOPPERS/JSP�����ͥ�����¤����������Ȥ��ǧ���ޤ�\n"
            "    r(estricted) : �����¸����ޤ����ƤΥ����å����ܤ�»ܤ��ޤ�\n");
        cout << endl 
             << Message("Supported architecture : ", "�б��������ƥ����� : ")
             << FileContainer::getInstance()->getArchitecture()
             << endl;
        return;
    }

    if(findOption("m","module",&loadmodule) || findOption(DEFAULT_PARAMETER,NULL,&loadmodule))
    {
        if(findOption("s","source"))
            ExceptionMessage("Configuration checker can not execute while Configurator executes","����ե�����졼���ȥ����å���Ʊ���˵�ư�Ǥ��ޤ���").throwException();

        parameter["/file/loadmodule"] = loadmodule;
        activateComponent();
    }

    if(!findOption("cs","script",&work))
        work = loadmodule.substr(0,loadmodule.find_last_of('.')) + ".chk";
    parameter["/file/checkerscript"] = work;

    work.erase();
    if(findOption("obj","load-object",&work))
    {
        if(work.empty())
            work.assign("kernel_obj.dat");

        fstream f(work.c_str(), ios::in|ios::binary);
        if(f.is_open())
        {
            parameter["/object"].Load(&f);
            f.close();
        }else
            ExceptionMessage(" Failed to open the file '%' for storing object definitions"," ���֥������Ⱦ�����Ǽ���뤿��Υե�����(%)�������ޤ���") << work << throwException;
    }

    if(findOption("cl","checklevel",&work))
    {
        current_level = UNKNOWN;

        if(work.compare("lazy") == 0 || work[0] == 'l')
            current_level = LAZY;
        if(work.compare("standard") == 0 || work[0] == 's')
            current_level = STANDARD;
        if(work.compare("toppers") == 0 || work[0] == 't')
            current_level = TOPPERS;
        if(work.compare("restricted") == 0 || work[0] == 'r')
            current_level = RESTRICTED;

        if(current_level == UNKNOWN)
            ExceptionMessage(" Unknown check level [%] specified"," ̵���ʥ����å���٥���� [%]") << work << throwException;
    }else
        current_level = NORMAL;

    checkOption("cpu", "cpu");
    checkOption("system", "system");
}

void ConfigurationChecker::body(Directory & parameter)
{
    FileContainer * container;
    bool result = true;

        /* ���ͥ���٤ι⤤���顼���оݤ� */
    current_level = static_cast<enum tagCheckLevel>(static_cast<int>(current_level) * 2 - 1);

    container = FileContainer::getInstance();
    container->attachInfo(parameter["/file/checkerscript"].toString());
    container->attachModule(parameter["/file/loadmodule"].toString());

    if(VerboseMessage::getVerbose())
    {
        cout << Message("  Target architecture : ","  �������åȥ������ƥ����� : ")
             << container->getArchitecture() << endl;
    }

    error_count = 0;
    result &= check_taskblock(parameter,container);
    result &= check_semaphoreblock(parameter,container);
    result &= check_eventflagblock(parameter,container);
    result &= check_dataqueueblock(parameter,container);
    result &= check_mailboxblock(parameter,container);
    result &= check_fixed_memorypoolblock(parameter,container);
    result &= check_cyclic_handlerblock(parameter,container);
    result &= check_interrupt_handlerblock(parameter,container);
    result &= check_exception_handlerblock(parameter,container);

    if(!result)
        ExceptionMessage("Total % errors found in current configuration.\n","������%�ĤΥ��顼�����Ф���ޤ���\n") << error_count << throwException;

    VerboseMessage("No error found in current configuration\n","�����˰۾�Ϥ���ޤ���Ǥ���\n");
}

