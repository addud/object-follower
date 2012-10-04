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
 *  @(#) $Id: filecontainer.h,v 1.8 2003/12/15 07:32:13 takayuki Exp $
 */

// $Header: /home/CVS/configurator/base/filecontainer.h,v 1.8 2003/12/15 07:32:13 takayuki Exp $

#ifndef FILECONTAINER_H
#define FILECONTAINER_H

#ifdef _MSC_VER
#pragma warning(disable:4786) //�ǥХå������255ʸ�����ڤ�ͤ�ޤ���
#endif

#include "testsuite.h"

#include <string>
#include <map>

#include "base/except.h"
#include "base/message.h"
#include "base/collection.h"

class FileContainer : public RuntimeObject
{
public:
    typedef unsigned long address_t;

    struct tagVariableInfo {
        address_t  address;
        union {
            size_t     size;
            int        value;
        };
    };

    enum tagByteOrder { LITTLE, BIG, HOSTORDER=LITTLE, UNKNOWN };   /* UNKNOWN�ϥƥ����� */

protected:
    enum tagByteOrder byteorder;

    std::map<std::string, struct tagVariableInfo> variableinfo;

    FileContainer(void) throw() : byteorder(HOSTORDER) {}
    virtual ~FileContainer(void) throw() {}

public:
        /* ���󥿥ե������� */
    virtual void                    attachModule(const std::string & filename) throw(Exception) = 0;
    virtual void                    loadContents(void * dest, address_t address, size_t size) throw(Exception) = 0;
    virtual address_t               getSymbolAddress(const std::string & symbol) throw(Exception) = 0;
    virtual std::string             getArchitecture(void) throw(Exception) = 0;

    virtual struct tagVariableInfo  getVariableInfo(const std::string & name) throw(Exception);
    virtual void                    attachInfo(const std::string & filename) throw(Exception);

        /* ��Ͽ����Ƥ��륳��ƥʤθƤӽФ� */
    static inline FileContainer * getInstance(void) throw(Exception)
    {
        FileContainer * result;
        RuntimeObjectTable::getInstance(&result);
        if(result == 0)
            ExceptionMessage("[Internal error] Filecontainer has no instance.","[�������顼] FileContainer�Υ��󥹥��󥹤�����ޤ���").throwException();
        return result;
    }

    enum tagByteOrder getByteOrder(void) const
    {   return byteorder;   }
};

class TargetVariableBase
{
protected:
    FileContainer::address_t address;               //�ѿ��Υ��ɥ쥹
    size_t                   size;                  //�ѿ��Υ�����
    size_t                   offset;                //°���빽¤�Τ���Ƭ����Υ��ե��å�
    size_t                   structure_size;        //°���빽¤�Τ��礭��
    bool                     loaded;                //�ͤ��ɽФ��ѤߤǤ��뤳�Ȥ��ݻ�����ե饰

    inline TargetVariableBase(FileContainer::address_t _address, size_t _size) throw()
        : address(_address), size(_size), offset(0), structure_size(_size), loaded(false)
    {}

    inline TargetVariableBase(FileContainer::address_t addr, size_t sz, size_t ofs, size_t ssz) throw()
        : address(addr), size(sz), offset(ofs), structure_size(ssz), loaded(false)
    {}
    
    TargetVariableBase(const std::string & sym) throw();
    TargetVariableBase(const std::string & sym, size_t _size) throw();
    TargetVariableBase(const std::string & sym, const std::string & sz) throw();
    TargetVariableBase(const TargetVariableBase & src) throw();

    virtual ~TargetVariableBase(void) throw() {}

        /* ���Ƥμ��� */
    void loadContent(void * dest, size_t dest_size) throw(Exception);

        /* ����ǥ������Ѵ� */
    void changeEndian(char * buffer, size_t size) throw();

        /* ���ɥ쥹�ΰ�ư (�Ĥ��Ǥ�loaded�򲼤���) */
    inline void setAddress(int offset) throw()
    {
        if(isValid()) {
            address += offset;
            loaded   = false;
        }
    }

public:
    inline bool isValid(void) const throw()
    {   return this != 0 && address != 0 && size != 0 && structure_size != 0;   }

    inline size_t getSize(void) const throw()
    {   return this != 0 ? size : 0;   }

    inline size_t getOffset(void) const throw()
    {   return this != 0 ? offset : 0;   }

    inline size_t getStructureSize(void) const throw()
    {   return this != 0 ? structure_size : 0;   }

    inline FileContainer::address_t getAddress(void) const throw()
    {   return this != 0 ? address : 0;   }

    inline bool isLoaded(void) const throw()
    {   return this != 0 ? loaded : false;   }

        /* ����Ū����� */
    inline bool operator == (const TargetVariableBase & right) const throw()
    {   return isValid() && right.isValid() && address == right.address;   }

    inline bool operator != (const TargetVariableBase & right) const throw()
    {   return ! operator ==(right);   }

    inline FileContainer::address_t operator & (void) const throw()
    {   return isValid() ? address + offset : 0;   }

    inline size_t sizeOf(void) const throw()
    {   return isValid() ? size : 0;   }
};

template<class T>
class TargetVariable : public TargetVariableBase
{
protected:
    T    entity;

public:
        /*
         * ���󥹥ȥ饯�� (TargetVariableBase�˲���)
         */
    inline TargetVariable(FileContainer::address_t addr) throw()
        : TargetVariableBase(addr, sizeof(T)), entity() 
    {}

    inline TargetVariable(FileContainer::address_t addr, size_t sz) throw()
        : TargetVariableBase(addr, sz), entity() 
    {}

    inline TargetVariable(FileContainer::address_t addr, size_t sz, size_t ofs, size_t ssz) throw()
        : TargetVariableBase(addr, sz, ofs, ssz), entity() 
    {}

    inline TargetVariable(const std::string & sym) throw()
        : TargetVariableBase(sym), entity()
    {}

    inline TargetVariable(const std::string & sym, const std::string & sz) throw()
        : TargetVariableBase(sym, sz), entity() 
    {}

    inline TargetVariable(const TargetVariable<T> & src) throw()
        : TargetVariableBase(src), entity()
    {
        if(isValid() && src.isValid()) {
            loaded = src.loaded;
            entity = src.entity;
        }
    }

        /* �ǥ��ȥ饯�� (�ä˲��⤷�ʤ�) */
    virtual ~TargetVariable(void) throw() 
    {}

        /* ����Ƚ��˳�Ǽ�˽�ʬ�ʥ����������뤫�ɤ������ɲä��Ƥ��� */
    inline bool isValid(void) const
    {   return TargetVariableBase::isValid() && (sizeof(T) >= getSize());   }

        /*
         * �ݥ�������ư��򤹤륪�ڥ졼����
         */
    inline TargetVariable<T> offsetInBytes(int offset) const throw()
    {   return TargetVariable<T>(getAddress() + offset, getSize(), getOffset(), getStructureSize());   }

    inline TargetVariable<T> operator + (int index) const throw()
    {   return offsetInBytes(index * static_cast<int>(getStructureSize()));   }

    inline TargetVariable<T> operator - (int index) const throw()
    {   return offsetInBytes(- index * static_cast<int>(getStructureSize()));   }

    inline TargetVariable<T> operator ++ (int) throw()
    {
        TargetVariable<T> result(*this);
        ++ (*this);
        return result;
    }

    inline TargetVariable<T> operator -- (int) throw()
    {
        TargetVariable<T> result(*this);
        -- (*this);
        return result;
    }

    inline TargetVariable<T> & operator ++ (void) throw()
    {
        setAddress(static_cast<int>(getStructureSize()));
        return *this;
    }

    inline TargetVariable<T> & operator -- (void) throw()
    {  
        setAddress(-static_cast<int>(getStructureSize()));   
        return *this;
    }

    inline TargetVariable<T> & operator += (int sz) throw()
    {   
        setAddress(static_cast<int>(getStructureSize()) * sz);   
        return *this;
    }

    inline TargetVariable<T> & operator -= (int sz) throw()
    {   
        setAddress(-static_cast<int>(getStructureSize()) * sz);   
        return *this;
    }

    inline const T & operator * (void) throw(Exception)
    {
        if(!isLoaded())
            loadContent(&entity, sizeof(T));
        return entity;
    }

    inline T operator [] (int index) const throw(Exception)
    {   return * TargetVariable<T>(getAddress() + index * getStructureSize(), getSize(), getOffset(), getStructureSize());   }
};

#endif

