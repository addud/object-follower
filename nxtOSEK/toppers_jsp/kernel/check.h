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
 *  @(#) $Id: check.h,v 1.7 2003/06/04 01:46:16 hiro Exp $
 */

/*
 *	���顼�����å��ѥޥ���
 */

#ifndef _CHECK_H_
#define _CHECK_H_

/*
 *  ͥ���٤��ϰϤ�Ƚ��
 */
#define VALID_TPRI(tpri) \
	(TMIN_TPRI <= (tpri) && (tpri) <= TMAX_TPRI)

/*
 *  ������ͥ���٤Υ����å���E_PAR��
 */
#define CHECK_TPRI(tpri) {					\
	if (!VALID_TPRI(tpri)) {				\
		ercd = E_PAR;					\
		goto exit;					\
	}							\
}

#define CHECK_TPRI_INI(tpri) {					\
	if (!(VALID_TPRI(tpri) || (tpri) == TPRI_INI)) {	\
		ercd = E_PAR;					\
		goto exit;					\
	}							\
}

#define CHECK_TPRI_SELF(tpri) {					\
	if (!(VALID_TPRI(tpri) || (tpri) == TPRI_SELF)) {	\
		ercd = E_PAR;					\
		goto exit;					\
	}							\
}

/*
 *  �����ॢ���Ȼ����ͤΥ����å���E_PAR��
 */
#define CHECK_TMOUT(tmout) {					\
	if (!(TMO_FEVR <= (tmout))) {				\
		ercd = E_PAR;					\
		goto exit;					\
	}							\
}

/*
 *  ����¾�Υѥ�᡼�����顼�Υ����å���E_PAR��
 */
#define CHECK_PAR(exp) {					\
	if (!(exp)) {						\
		ercd = E_PAR;					\
		goto exit;					\
	}							\
}

/*
 *  ���֥�������ID���ϰϤ�Ƚ��
 */
#define VALID_TSKID(tskid) \
	(TMIN_TSKID <= (tskid) && (tskid) <= tmax_tskid)

#define VALID_SEMID(semid) \
	(TMIN_SEMID <= (semid) && (semid) <= tmax_semid)

#define VALID_FLGID(flgid) \
	(TMIN_FLGID <= (flgid) && (flgid) <= tmax_flgid)

#define VALID_DTQID(dtqid) \
	(TMIN_DTQID <= (dtqid) && (dtqid) <= tmax_dtqid)

#define VALID_MBXID(mbxid) \
	(TMIN_MBXID <= (mbxid) && (mbxid) <= tmax_mbxid)

#define VALID_MPFID(mpfid) \
	(TMIN_MPFID <= (mpfid) && (mpfid) <= tmax_mpfid)

#define VALID_CYCID(cycid) \
	(TMIN_CYCID <= (cycid) && (cycid) <= tmax_cycid)

/*
 *  ���֥�������ID�Υ����å���E_ID��
 */
#define CHECK_TSKID(tskid) {					\
	if (!VALID_TSKID(tskid)) {				\
		ercd = E_ID;					\
		goto exit;					\
	}							\
}

#define CHECK_TSKID_SELF(tskid) {				\
	if (!(VALID_TSKID(tskid) || (tskid) == TSK_SELF)) {	\
		ercd = E_ID;					\
		goto exit;					\
	}							\
}

#define CHECK_SEMID(semid) {					\
	if (!VALID_SEMID(semid)) {				\
		ercd = E_ID;					\
		goto exit;					\
	}							\
}

#define CHECK_FLGID(flgid) {					\
	if (!VALID_FLGID(flgid)) {				\
		ercd = E_ID;					\
		goto exit;					\
	}							\
}

#define CHECK_DTQID(dtqid) {					\
	if (!VALID_DTQID(dtqid)) {				\
		ercd = E_ID;					\
		goto exit;					\
	}							\
}

#define CHECK_MBXID(mbxid) {					\
	if (!VALID_MBXID(mbxid)) {				\
		ercd = E_ID;					\
		goto exit;					\
	}							\
}

#define CHECK_MPFID(mpfid) {					\
	if (!VALID_MPFID(mpfid)) {				\
		ercd = E_ID;					\
		goto exit;					\
	}							\
}

#define CHECK_CYCID(cycid) {					\
	if (!VALID_CYCID(cycid)) {				\
		ercd = E_ID;					\
		goto exit;					\
	}							\
}

/*
 *  �ƽФ�����ƥ����ȤΥ����å���E_CTX��
 */
#define CHECK_TSKCTX() {					\
	if (sense_context()) {					\
		ercd = E_CTX;					\
		goto exit;					\
	}							\
}

#define CHECK_INTCTX() {					\
	if (!sense_context()) {					\
		ercd = E_CTX;					\
		goto exit;					\
	}							\
}

/*
 *  �ƽФ�����ƥ����Ȥ�CPU��å����֤Υ����å���E_CTX��
 */
#define CHECK_TSKCTX_UNL() {					\
	if (sense_context() || t_sense_lock()) {		\
		ercd = E_CTX;					\
		goto exit;					\
	}							\
}

#define CHECK_INTCTX_UNL() {					\
	if (!sense_context() || i_sense_lock()) {		\
		ercd = E_CTX;					\
		goto exit;					\
	}							\
}

/*
 *  �ǥ����ѥå���α���֤Ǥʤ����Υ����å���E_CTX��
 */
#define CHECK_DISPATCH() {					\
	if (sense_context() || t_sense_lock() || !(enadsp)) {	\
		ercd = E_CTX;					\
		goto exit;					\
	}							\
}

/*
 *  ����¾�Υ���ƥ����ȥ��顼�Υ����å���E_CTX��
 */
#define CHECK_CTX(exp) {					\
	if (!(exp)) {						\
		ercd = E_CTX;					\
		goto exit;					\
	}							\
}

/*
 *  ������������ꤷ�Ƥ��ʤ����Υ����å���E_ILUSE��
 */
#define CHECK_NONSELF(tcb) {					\
	if ((tcb) == runtsk) {					\
		ercd = E_ILUSE;					\
		goto exit;					\
	}							\
}

/*
 *  ����¾���������ѥ��顼�Υ����å���E_ILUSE��
 */
#define CHECK_ILUSE(exp) {					\
	if (!(exp)) {						\
		ercd = E_ILUSE;					\
		goto exit;					\
	}							\
}

#endif /* _CHECK_H_ */
