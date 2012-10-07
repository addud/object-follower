/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2004 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
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
 *  @(#) $Id: itron.h,v 1.16 2004/12/22 03:38:00 hiro Exp $
 */

/*
 *	ITRON���Ͷ��̵���Υǡ�������������ޥ���
 *
 *  ���Υե�����ˤϡ�����������ɥץ�ե�����ˤ�ɬ�פʤ������ޤ��
 *  ���롥�ǡ�����������ϡ�����������ɥץ�ե���������������礦�ɤ�
 *  Ĺ���ˤϤ��Ƥ��ʤ���
 *
 *  ������֥����Υ������ե�����䥷���ƥॳ��ե�����졼�����ե�
 *  ���뤫�餳�Υե�����򥤥󥯥롼�ɤ�����ϡ�_MACRO_ONLY ���������
 *  �������Ȥǡ��ޥ�������ʳ��ε��Ҥ�������Ȥ��Ǥ��롥
 *
 *  ���Υ��󥯥롼�ɥե�����ϡ�kernel.h �� sil.h �ǥ��󥯥롼�ɤ���롥
 *  �ޤ���ITRON���Ͷ��̵���˽�򤹤륽�եȥ��������ʤΥ��󥯥롼�ɥե�
 *  ����ϡ����Υե������ľ�ܥ��󥯥롼�ɤ��Ƥ�褤�������㳰������ơ�
 *  ¾�Υե����뤫��ľ�ܥ��󥯥롼�ɤ���뤳�ȤϤʤ���
 *
 *  ���Υե�����򥤥󥯥롼�ɤ������ˡ�t_stddef.h �򥤥󥯥롼�ɤ���
 *  �������Ȥ�ɬ�פǤ��롥
 */

#ifndef _ITRON_H_
#define _ITRON_H_

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  ��ȯ�Ķ��˰�¸�������
 */
#include <tool_defs.h>

/*
 *  ��ȯ�Ķ���ɸ�।�󥯥롼�ɥե������NULL �� size_t �������ɬ�ס�
 *
 *  C++/EC++ �Ǥϡ�ɸ����;�� stddef.h �����ݡ��Ȥ���Ƥ���Ȥϸ¤��
 *  �������ۤȤ�ɤν����Ϥǥ��ݡ��Ȥ���Ƥ��롥
 */
#ifndef _MACRO_ONLY
#include <stddef.h>
#endif /* _MACRO_ONLY */

/*
 *  ����ѥ����¸�Υǡ������Υǥե�������
 */
#ifndef _bool_
#define	_bool_		int		/* �֡��뷿 */
#endif /* _bool_ */

/*
 *  ITRON���Ͷ��̥ǡ�����
 */
#ifndef _MACRO_ONLY

#ifdef _int8_
typedef	signed _int8_		B;	/* ����դ�8�ӥå����� */
typedef	unsigned _int8_		UB;	/* ���̵��8�ӥå����� */
typedef	_int8_			VB;	/* ������ޤ�ʤ�8�ӥåȤ��� */
#endif /* _int8_ */

#ifdef _int16_
typedef	signed _int16_		H;	/* ����դ�16�ӥå����� */
typedef	unsigned _int16_ 	UH;	/* ���̵��16�ӥå����� */
typedef	_int16_			VH;	/* ������ޤ�ʤ�16�ӥåȤ��� */
#endif /* _int16_ */

typedef	signed _int32_		W;	/* ����դ�32�ӥå����� */
typedef	unsigned _int32_	UW;	/* ���̵��32�ӥå����� */
typedef	_int32_			VW;	/* ������ޤ�ʤ�32�ӥåȤ��� */

#ifdef _int64_
typedef	signed _int64_		D;	/* ����դ�64�ӥå����� */
typedef	unsigned _int64_	UD;	/* ���̵��64�ӥå����� */
typedef	_int64_			VD;	/* ������ޤ�ʤ�64�ӥåȤ��� */
#endif /* _int64_ */

typedef	void		*VP;		/* ������ޤ�ʤ���ΤؤΥݥ��� */
typedef	void		(*FP)();	/* �ץ����ε�ư���ϡʥݥ��󥿡� */

typedef signed int	INT;		/* �����ʥ�����������դ����� */
#if 0
typedef unsigned int	UINT;		/* �����ʥ����������̵������ */
#else /* patch */
#ifndef UINT_DEFINED
#define UINT_DEFINED
typedef unsigned int	UINT;		/* �����ʥ����������̵������ */
#endif
#endif

typedef _bool_		BOOL;		/* ������ */

typedef INT		FN;		/* ��ǽ������ */
typedef	INT		ER;		/* ���顼������ */
typedef	INT		ID;		/* ���֥������Ȥ�ID�ֹ� */
typedef	UINT		ATR;		/* ���֥������Ȥ�°�� */
typedef	UINT		STAT;		/* ���֥������Ȥξ��� */
typedef	UINT		MODE;		/* �����ӥ��������ư��⡼�� */
typedef	INT		PRI;		/* ͥ���� */
typedef	size_t		SIZE;		/* �����ΰ�Υ����� */

typedef	INT		TMO;		/* �����ॢ���Ȼ��� */
typedef	UINT		RELTIM;		/* ���л��� */
typedef	UW		SYSTIM;		/* �����ƥ���� */

#ifdef _vp_int_
typedef	_vp_int_	VP_INT;		/* VP �ޤ��� INT */
#else /* _vp_int_ */
typedef	VP		VP_INT;		/* VP �ޤ��� INT */
#endif /* _vp_int_ */

typedef	INT		ER_BOOL;	/* ER �ޤ��� BOOL */
typedef	INT		ER_ID;		/* ER �ޤ��� ID */
typedef	INT		ER_UINT;	/* ER �ޤ��� UINT */

#endif /* _MACRO_ONLY */

/*
 *  ITRON���Ͷ������
 */

/*
 *  ����
 *
 *  _MACRO_ONLY �λ��ˤϡ�NULL ��������ʤ�������ϡ�_MACRO_ONLY �λ�
 *  ��stddef.h �򥤥󥯥롼�ɤ��ʤ����ᡤ�����Ǥʤ����� NULL �������
 *  �����㤦��ǽ�������뤿��Ǥ��롥�ޤ��������ƥॳ��ե�����졼����
 *  ��ե���������������ˤ� NULL ��������ƤϤʤ�ʤ����ᡤ������
 *  �����������ʤ������Թ礬�褤��
 */
#ifndef _MACRO_ONLY
#ifndef NULL				/* stddef.h �˴ޤޤ�Ƥ���Ϥ� */
#define	NULL		0		/* ̵���ݥ��� */
#endif /* NULL */
#endif /* _MACRO_ONLY */

#define	TRUE		1		/* �� */
#define	FALSE		0		/* �� */
#define	E_OK		0		/* ���ｪλ */

/*
 *  ���顼������
 */
#define	E_SYS		(-5)		/* �����ƥ२�顼 */
#define	E_NOSPT		(-9)		/* ̤���ݡ��ȵ�ǽ */
#define	E_RSFN		(-10)		/* ͽ��ǽ������ */
#define	E_RSATR		(-11)		/* ͽ��°�� */
#define	E_PAR		(-17)		/* �ѥ�᡼�����顼 */
#define	E_ID		(-18)		/* ����ID�ֹ� */
#define	E_CTX		(-25)		/* ����ƥ����ȥ��顼 */
#define	E_MACV		(-26)		/* ���ꥢ��������ȿ */
#define	E_OACV		(-27)		/* ���֥������ȥ���������ȿ */
#define	E_ILUSE		(-28)		/* �����ӥ��������������� */
#define	E_NOMEM		(-33)		/* ������­ */
#define	E_NOID		(-34)		/* ID�ֹ���­ */
#define	E_OBJ		(-41)		/* ���֥������Ⱦ��֥��顼 */
#define	E_NOEXS		(-42)		/* ���֥�������̤���� */
#define	E_QOVR		(-43)		/* ���塼���󥰥����С��ե� */
#define	E_RLWAI		(-49)		/* �Ԥ����֤ζ������ */
#define	E_TMOUT		(-50)		/* �ݡ���󥰼��Ԥޤ��ϥ����ॢ���� */
#define	E_DLT		(-51)		/* �Ԥ����֥������Ȥκ�� */
#define	E_CLS		(-52)		/* �Ԥ����֥������Ȥξ����Ѳ� */
#define	E_WBLK		(-57)		/* �Υ�֥�å��󥰼��դ� */
#define	E_BOVR		(-58)		/* �Хåե������С��ե� */

/*
 *  ���֥�������°��
 */
#define	TA_NULL		0u		/* ���֥�������°������ꤷ�ʤ� */

/*
 *  �����ॢ���Ȼ���
 */
#define TMO_POL		0		/* �ݡ���� */
#define TMO_FEVR	(-1)		/* �ʵ��Ԥ� */
#define TMO_NBLK	(-2)		/* �Υ�֥�å��� */

/*
 *  ITRON���Ͷ��̥ޥ���
 */

/*
 *  ���顼������������ʬ��ޥ���
 *
 *  ANSI C����ε��ʤǤϡ������եȱ黻�ҡ�>>�ˤ�����ĥ����뤳�Ȥ���
 *  �ڤ��Ƥ��ʤ����ᡤSERCD�ޥ���������ñ�� ((ercd) >> 8) �Ȥ���ȡ�
 *  �����եȱ黻�Ҥ�����ĥ���ʤ�����ѥ���Ǥϡ�SERCD �����ͤ�������
 *  �ˤʤäƤ��ޤ���
 */
#define	ERCD(mercd,sercd)	(((sercd) << 8) | ((mercd) & 0xff))

#ifdef _int8_
#define	MERCD(ercd)		((ER)((B)(ercd)))
#define	SERCD(ercd)		((ER)((B)((ercd) >> 8)))
#else /* _int8_ */
#define	MERCD(ercd)		(((ercd) & 0x80) == 0 ? ((ercd) & 0xff) \
							: ((ercd) | ~0xff))
#define	SERCD(ercd)		((~((~0) >> 8)) | ((ercd) >> 8))
#endif /* _int8_ */

#ifdef __cplusplus
}
#endif

#endif /* _ITRON_H_ */
