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
 *  @(#) $Id: garbage.cpp,v 1.6 2003/12/15 07:32:13 takayuki Exp $
 */

// $Header: /home/CVS/configurator/base/garbage.cpp,v 1.6 2003/12/15 07:32:13 takayuki Exp $

#include "base/garbage.h"

#include <stdexcept>
#include <algorithm>

using namespace std;

TrashBox * TrashBox::current_box = 0;

//----------------------------------------------------------------
// Garbage : ����

    //���󥹥ȥ饯��
Garbage::Garbage(void) throw()
{
        //����Ȣ�˴�Ϣ�դ���
    assigned_box = TrashBox::getCurrentTrashBox();
    if(assigned_box->isValid())
        cookie = assigned_box->addGarbage(this);
}

    //�ǥ��ȥ饯��
Garbage::~Garbage(void) throw()
{
    rescue();
}

    //���ߵ߽�
void Garbage::rescue(void) throw()
{
    if(assigned_box->isValid()) {
        assigned_box->recoverGarbage(cookie);
        assigned_box = 0;
    }
}


//----------------------------------------------------------------
// TrashBox : ���ߤ������Ȣ

TrashBox::TrashBox(void) throw()
{
        //����Ȣ�κ����ؤ�
    previous_box = current_box;
    current_box  = this;
}

TrashBox::~TrashBox(void) throw()
{
        //���ߤ��ʤ��ʤ�ޤǺ��
    while(!garbage.empty()) {
            //�դ�
        try{   cleanup();   }
        catch(...) {}
    }

        //����Ȣ�κ����ؤ�
    current_box = previous_box;
}

/*
    //����Ȣ�����줿���ߤ������
void TrashBox::recoverGarbage(Garbage * _garbage, TrashBox::Cookie cookie) throw()
{
    if(isValid() && _garbage != 0) {
        bool forward = true;
        list<Garbage *>::iterator scope;

        if(!garbage.empty()) {
            scope = garbage.erase(cookie);

                //��ʬ����������
            if(scope != garbage.end() || garbage.empty())
                forward = false;
        }

            //�ƥ���Ȣ�˲���
        if(forward && previous_box->isValid())
            previous_box->recoverGarbage(_garbage, cookie);
    }
}
*/
    /*  �������Υ�� 
              ��Ϣ�դ���줿����Ȣ���ä��뤳�Ȥ�̵��(�������֤ϥ���Ȣ�Τۤ���Ĺ���Ϥ�)�Τǡ��Ƥ˲�������ɬ�פ�̵������ä�if(forward...������ס�
              ��ʬ�������Ǥ��ʤ����ߤ�̵���Τ�(cleanup��recoverGargabe��ƤФʤ�)��erase���ֵ��ͤΥ����å������ס�
              ���̺���׵�ϥ��ߤ���Ф����Τǡ��¹Ԥ��줿�����ǥ��ߤ�1�İʾ�¸�ߤ���Ϥ��ʤΤǡ�empty�����å�������.
              ���λ�����erase�����ˤʤꡢ�����������ס�
    */

    //����Ȣ�����줿���ߤ������  
void TrashBox::recoverGarbage(TrashBox::Cookie cookie) throw()
{   garbage.erase(cookie);  }

    //����Ȣ����ˤ���
void TrashBox::cleanup(void)
{
        //��ʬ���ȥåץ�٥르��Ȣ�Ǥʤ��ä��鼺��
    if(current_box != this)
        throw std::runtime_error("TrashBox::cleanup can be performed from the top level trash box only.");

    try {
        while(!garbage.empty())
            delete *garbage.begin();        //���ߥꥹ�Ȥ������Ǥ򳰤��ΤϻҤ�����
    }
    catch(...) {
        garbage.erase(garbage.begin());     //�㳰�򵯤������ǽ�����Ǥ���
        throw;                              //����
    }
}



/****************************************** �ƥ��ȥ������� ******************************************/

#ifdef TESTSUITE
#include "coverage_undefs.h"

namespace { int counter = 0; }

#ifdef _MSC_VER
    class DummyGarbage : public Garbage
    {
    public:
        int * count;
        bool throw_exception;

        DummyGarbage(int * _count = 0) : count(_count), throw_exception(false)
        { TestSuite::check("DummyGarbage::DummyGarbage");  }

        ~DummyGarbage(void) throw(int)
        {
            if(count != 0) *count = ++counter;
            if(throw_exception) throw 0;
            TestSuite::check("DummyGarbage::~DummyGarbage"); 
        }

    };
#elif __GNUC__
    class DummyGarbage : public Garbage
    {
    public:
        int * count;

        DummyGarbage(int * _count = 0) : count(_count)
        { TestSuite::check("DummyGarbage::DummyGarbage");  }

        ~DummyGarbage(void) throw()
        {
            if(count != 0) *count = ++counter;
            TestSuite::check("DummyGarbage::~DummyGarbage"); 
        }
    };
#endif

TESTSUITE(main, TrashBox)
{
    BEGIN_CASE("1","����Ȣ�������Ͽ�����") {
        TrashBox mybox;
        TEST_CASE("1", "��ä�����Ȣ�����ߤΥ���Ȣ�ˤʤäƤ���", TrashBox::current_box == &mybox);
        
        {
            TrashBox mybox2;
            TEST_CASE("2", "��ä�����Ȣ�����ߤΥ���Ȣ�ˤʤäƤ��� (2)", TrashBox::current_box == &mybox2);
            TEST_CASE("3", "��Ȥ�ȤΥ���Ȣ����¸����Ƥ���", mybox2.previous_box == &mybox);
        }

        TEST_CASE("4", "��ȤΥ���Ȣ�����", TrashBox::current_box == &mybox);
    } END_CASE;

    BEGIN_CASE("2","isValid") {
        TrashBox mybox;

        TEST_CASE("1","��ä�����Ȣ������", mybox.isValid());
        TEST_CASE("2","NULLȢ�ϰ۾�", !((TrashBox *)0)->isValid());
    } END_CASE;

    BEGIN_CASE("3","operator new") {
        BEGIN_CASE("1","new TrashBox��bad_alloc�㳰���֤�") {
            bool result = false;

            try { TrashBox * box = new TrashBox; }
            catch(bad_alloc) { result = true; }

            if(!result)
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("2","new(nothrow) TrashBox��NULL���֤�") {
            bool result = true;
            TrashBox * box;

            try { box = new(nothrow) TrashBox; }
            catch(...) { result = false; }

            TEST_CASE("1", "new(nothrow)���㳰���֤��ʤ�", result);
            TEST_CASE("2", "new(nothrow)��NULL���֤�",   box == 0);
        } END_CASE;
    } END_CASE;

    BEGIN_CASE("4","����Ū���������") {
        BEGIN_CASE("1","�����ȥ���Ȣ���鳰����") {
            TrashBox mybox;

            DummyGarbage * garbage = new DummyGarbage;

            TEST_CASE("0","[����] ���ߤ����äƤ���", std::find(mybox.garbage.begin(), mybox.garbage.end(), garbage) != mybox.garbage.end());
            delete garbage;
            TEST_CASE("1","���ߤ��ä��Ƥ���", std::find(mybox.garbage.begin(), mybox.garbage.end(), garbage) == mybox.garbage.end());


        } END_CASE;

        BEGIN_CASE("2","�ƤΥ���Ȣ�����äƤ����Τ⥴��Ȣ���鳰����") {
            TrashBox mybox;
            DummyGarbage * garbage = new DummyGarbage;
            TEST_CASE("0","[����] ���ߤ����äƤ���", find(mybox.garbage.begin(), mybox.garbage.end(), garbage) != mybox.garbage.end());

            TrashBox secondbox;
            delete garbage;

            TEST_CASE("1","���ߤ��ä��Ƥ���", find(mybox.garbage.begin(), mybox.garbage.end(), garbage) == mybox.garbage.end());
           
        } END_CASE;
    } END_CASE;

    BEGIN_CASE("5","TrashBox::cleanup") {
        BEGIN_CASE("1","ưŪ�˺�ä����֥������Ȥ��˴��Ǥ���") {
            TrashBox mybox;
            DummyGarbage * garbage;

            TestSuite::clearCheckpoints();

            garbage = new DummyGarbage;
            TEST_CASE("0","[����] ���󥹥ȥ饯������ư����Ƥ���", TestSuite::isReached("DummyGarbage::DummyGarbage"));

            mybox.cleanup();
            TEST_CASE("1","�ǥ��ȥ饯������ư����Ƥ���", TestSuite::isReached("DummyGarbage::~DummyGarbage"));
        } END_CASE;

#ifdef _MSC_VER
        BEGIN_CASE("2","�㳰�Ϥ���") {
            TrashBox mybox;
            DummyGarbage * garbage;

            TestSuite::clearCheckpoints();

            garbage = new DummyGarbage;
            garbage->throw_exception = true;

            bool result = false;
            try { mybox.cleanup(); }
            catch(...) { result = true; }

            if(!result)
                TEST_FAIL;
        } END_CASE;

        BEGIN_CASE("3","�㳰�򵯤��������֥������Ȥ��˲�����Ƥ��� (2���˴��ˤʤ�ʤ�)") {
            TrashBox mybox;
            DummyGarbage * garbage;
            DummyGarbage * garbage2;

            TestSuite::clearCheckpoints();

            garbage = new DummyGarbage;
            garbage->throw_exception = true;
            garbage2 = new DummyGarbage;
            garbage2->throw_exception = true;

            try { mybox.cleanup(); }
            catch(...) {}
            try { mybox.cleanup(); }    //������AccessViolation��������ʤ�
            catch(...) {}

            if(!mybox.garbage.empty())
                TEST_FAIL;
        } END_CASE;
#endif

        BEGIN_CASE("4","����ν����������") {
            TrashBox mybox;
            DummyGarbage * garbage;
            DummyGarbage * garbage2;
            DummyGarbage * garbage3;
            int g  = 0;
            int g2 = 0;
            int g3 = 0;

            TestSuite::clearCheckpoints();

            garbage  = new DummyGarbage(&g);
            garbage2 = new DummyGarbage(&g2);
            garbage3 = new DummyGarbage(&g3);

            mybox.cleanup();

            TEST_CASE("1","�ǽ����Ͽ���줿��ΤϺǸ�˺��",g == 3);
            TEST_CASE("2","������Ͽ���줿��Τ�2���ܤ˺��",g2 == 2);
            TEST_CASE("3","������Ͽ���줿��ΤϺǽ�˺��",g3 == 1);
        } END_CASE;

        BEGIN_CASE("5","�ȥåץ�٥�Ǥʤ�����Ȣ��cleanup�Ǥ��ʤ�") {
            TrashBox outerbox;
            TrashBox innerbox;

            bool result = false;
            try {   outerbox.cleanup();   }
            catch(std::runtime_error)
            {   result = true;   }

            if(!result)
                TEST_FAIL;
        } END_CASE;

    } END_CASE;

    BEGIN_CASE("6","�ǥ��ȥ饯���ˤ���˴�") {
        BEGIN_CASE("1","ưŪ�˺�ä����֥������Ȥ��˴��Ǥ��� (TrashBox::~TrashBox)") {
            {
                TrashBox mybox;
                DummyGarbage * garbage;

                TestSuite::clearCheckpoints();

                garbage = new DummyGarbage;
                TEST_CASE("0","[����] ���󥹥ȥ饯������ư����Ƥ���", TestSuite::isReached("DummyGarbage::DummyGarbage"));
            }
            TEST_CASE("1","�ǥ��ȥ饯������ư����Ƥ���", TestSuite::isReached("DummyGarbage::~DummyGarbage"));
        } END_CASE;

        BEGIN_CASE("2","�㳰�Ϥ��ʤ�") {
            bool result = true;
            try{
                TrashBox mybox;
                DummyGarbage * garbage;

                TestSuite::clearCheckpoints();

                garbage = new DummyGarbage;
                TEST_CASE("0","[����] ���󥹥ȥ饯������ư����Ƥ���", TestSuite::isReached("DummyGarbage::DummyGarbage"));
            }
            catch(...)
            { result = false; }
            TEST_CASE("1","�㳰�Ϥ��ʤ�", result);
        } END_CASE;

    } END_CASE;

    BEGIN_CASE("7","rescue") {
        DummyGarbage * garbage;
        {
            TrashBox mybox;
            garbage = new DummyGarbage;
            garbage->rescue();

            TestSuite::clearCheckpoints();
        }
        TEST_CASE("1","rescue�������ߤϺ������ʤ�", !TestSuite::isReached("DummyGarbage::~DummyGarbage"));
        delete garbage;
    } END_CASE;

    BEGIN_CASE("8","��Ū�ʥ��֥������Ȥ�¿���˴�����ʤ�") {
        TrashBox outerbox;
        {
            DummyGarbage garbage;
            TrashBox innerbox;
            DummyGarbage garbage2;

            TEST_CASE("0","[����] ���󥹥ȥ饯������ư����Ƥ���", TestSuite::isReached("DummyGarbage::DummyGarbage"));
        }   //������2���˴���MACV�ˤʤ�ʤ�
    } END_CASE;
}

#endif



