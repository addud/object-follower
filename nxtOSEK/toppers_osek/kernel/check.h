/*
 *  TOPPERS/OSEK Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      OSEK Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2004 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
 *  Copyright (C) 2004 by Witz Corporation, JAPAN
 * 
 *  ��L���쌠�҂́C�ȉ��� (1)�`(4) �̏������CFree Software Foundation 
 *  �ɂ���Č��\����Ă��� GNU General Public License �� Version 2 �ɋL
 *  �q����Ă�������𖞂����ꍇ�Ɍ���C�{�\�t�g�E�F�A�i�{�\�t�g�E�F�A
 *  �����ς������̂��܂ށD�ȉ������j���g�p�E�����E���ρE�Ĕz�z�i�ȉ��C
 *  ���p�ƌĂԁj���邱�Ƃ𖳏��ŋ�������D
 *  (1) �{�\�t�g�E�F�A���\�[�X�R�[�h�̌`�ŗ��p����ꍇ�ɂ́C��L�̒���
 *      ���\���C���̗��p��������щ��L�̖��ۏ؋K�肪�C���̂܂܂̌`�Ń\�[
 *      �X�R�[�h���Ɋ܂܂�Ă��邱�ƁD
 *  (2) �{�\�t�g�E�F�A���C���C�u�����`���ȂǁC���̃\�t�g�E�F�A�J���Ɏg
 *      �p�ł���`�ōĔz�z����ꍇ�ɂ́C�Ĕz�z�ɔ����h�L�������g�i���p
 *      �҃}�j���A���Ȃǁj�ɁC��L�̒��쌠�\���C���̗��p��������щ��L
 *      �̖��ۏ؋K����f�ڂ��邱�ƁD
 *  (3) �{�\�t�g�E�F�A���C�@��ɑg�ݍ��ނȂǁC���̃\�t�g�E�F�A�J���Ɏg
 *      �p�ł��Ȃ��`�ōĔz�z����ꍇ�ɂ́C���̂����ꂩ�̏����𖞂�����
 *      �ƁD
 *    (a) �Ĕz�z�ɔ����h�L�������g�i���p�҃}�j���A���Ȃǁj�ɁC��L�̒�
 *        �쌠�\���C���̗��p��������щ��L�̖��ۏ؋K����f�ڂ��邱�ƁD
 *    (b) �Ĕz�z�̌`�Ԃ��C�ʂɒ�߂���@�ɂ���āCTOPPERS�v���W�F�N�g��
 *        �񍐂��邱�ƁD
 *  (4) �{�\�t�g�E�F�A�̗��p�ɂ�蒼�ړI�܂��͊ԐړI�ɐ����邢���Ȃ鑹
 *      �Q������C��L���쌠�҂����TOPPERS�v���W�F�N�g��Ɛӂ��邱�ƁD
 * 
 *  �{�\�t�g�E�F�A�́C���ۏ؂Œ񋟂���Ă�����̂ł���D��L���쌠�҂�
 *  ���TOPPERS�v���W�F�N�g�́C�{�\�t�g�E�F�A�Ɋւ��āC���̓K�p�\����
 *  �܂߂āC�����Ȃ�ۏ؂��s��Ȃ��D�܂��C�{�\�t�g�E�F�A�̗��p�ɂ�蒼
 *  �ړI�܂��͊ԐړI�ɐ����������Ȃ鑹�Q�Ɋւ��Ă��C���̐ӔC�𕉂�Ȃ��D
 * 
 */

/*
 *	�G���[�`�F�b�N�p�}�N��
 */

#ifndef _CHECK_H_
#define _CHECK_H_

#ifdef EXTENDED_STATUS

#define CHECK_ACCESS(exp) do {			\
	if (!(exp)) {						\
		ercd = E_OS_ACCESS;				\
		goto error_exit;				\
	}									\
} while (0)

#define D_CHECK_ACCESS(exp) do {		\
	if (!(exp)) {						\
		ercd = E_OS_ACCESS;				\
		goto d_error_exit;				\
	}									\
} while (0)

#define CHECK_CALLEVEL(clmask) do {		\
	if ((callevel & (clmask)) == 0) {	\
		ercd = E_OS_CALLEVEL;			\
		goto error_exit;				\
	}									\
} while (0)

#define CHECK_TSKID(tskid) do {			\
	if (!(tskid < tnum_task)) {			\
		ercd = E_OS_ID;					\
		goto error_exit;				\
	}									\
} while (0)

#define CHECK_RESID(resid) do {			\
	if (!(resid < tnum_resource)) {		\
		ercd = E_OS_ID;					\
		goto error_exit;				\
	}									\
} while (0)

#define CHECK_CNTID(cntid) do {			\
	if (!(cntid < tnum_counter)) {		\
		ercd = E_OS_ID;					\
		goto error_exit;				\
	}									\
} while (0)

#define CHECK_ALMID(almid) do {			\
	if (!(almid < tnum_alarm)) {		\
		ercd = E_OS_ID;					\
		goto error_exit;				\
	}									\
} while (0)

#define CHECK_NOFUNC(exp) do {			\
	if (!(exp)) {						\
		ercd = E_OS_NOFUNC;				\
		goto error_exit;				\
	}									\
} while (0)

#define CHECK_RESOURCE(exp) do {		\
	if (!(exp)) {						\
		ercd = E_OS_RESOURCE;			\
		goto error_exit;				\
	}									\
} while (0)

#define D_CHECK_STATE(exp) do {			\
	if (!(exp)) {						\
		ercd = E_OS_STATE;				\
		goto d_error_exit;				\
	}									\
} while (0)

#define CHECK_VALUE(exp) do {			\
	if (!(exp)) {						\
		ercd = E_OS_VALUE;				\
		goto error_exit;				\
	}									\
} while (0)

#else /* EXTENDED_STATUS */

#define CHECK_ACCESS(exp)		((void) 0)
#define D_CHECK_ACCESS(exp)		((void) 0)
#define CHECK_CALLEVEL(clmask)	((void) 0)
#define CHECK_TSKID(tskid)		((void) 0)
#define CHECK_RESID(resid)		((void) 0)
#define CHECK_CNTID(cntid)		((void) 0)
#define CHECK_ALMID(almid)		((void) 0)
#define CHECK_NOFUNC(exp)		((void) 0)
#define CHECK_RESOURCE(exp)		((void) 0)
#define D_CHECK_STATE(exp)		((void) 0)
#define CHECK_VALUE(exp)		((void) 0)

#endif /* EXTENDED_STATUS */
#endif /* _CHECK_H_ */
