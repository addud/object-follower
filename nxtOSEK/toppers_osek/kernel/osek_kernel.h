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
 *	OSEK�J�[�l�� �W���C���N���[�h�t�@�C��
 *
 *  ���̃C���N���[�h�t�@�C���́C�J�[�l�����\������v���O�����̃\�[�X�t�@
 *  �C���ŕK���C���N���[�h����ׂ��W���C���N���[�h�t�@�C���ł���D
 *
 *  �A�Z���u������̃\�[�X�t�@�C����V�X�e���R���t�B�M�����[�V�����t�@
 *  �C�����炱�̃t�@�C�����C���N���[�h���鎞�́C_MACRO_ONLY ���`����
 *  �������ƂŁC�}�N����`�ȊO�̋L�q���������Ƃ��ł���D
 */

#ifndef _OSEK_KERNEL_H_
#define _OSEK_KERNEL_H_

/*
 *  �J�[�l���������ʂ̃C���N���[�h�t�@�C��
 */
#include <kernel.h>

/*
 *  �J�[�l�����Ŏg�p����f�[�^�^�̒�`
 */
#ifndef _MACRO_ONLY
typedef void		*VP;			/* �^����܂�Ȃ����̂ւ̃|�C���^ */
typedef void		(*FP)(void);	/* �v���O�����̋N���Ԓn�i�|�C���^�j */
typedef UINT8		Priority;		/* �D��x�i�^�X�N�CISR�j */
typedef	UINT8		IPL;			/* �����ݗD�惌�x�� */
#endif /* _MACRO_ONLY */

/*
 *  �D��x�̒i�K���̒�`
 */
#define TNUM_PRIORITY	((Priority) 16)

/*
 *  ��ʓI�Ȓ萔�̒�`
 */
#define	NULL			((void *) 0)		/* �����|�C���^ */

/*
 *  �D��x�l�̒�`
 */
#define TPRI_MINTASK	((Priority) 0)		/* �Œ�^�X�N�D��x */
#define TPRI_MAXTASK	((Priority)(TNUM_PRIORITY - 1))
											/* �ō��^�X�N�D��x */
#define TPRI_SCHEDULER	((Priority) 127)	/* �X�P�W���[���̗D��x */
#define TPRI_MINISR		((Priority) 128)	/* �Œኄ���ݗD��x */
#define TPRI_NULL		((Priority) UINT8_INVALID)
											/* �����D��x */

/*
 *  �C�x���g�}�X�N�l�̒�`
 */
#define EVTMASK_NONE	((EventMaskType) 0)	/* �C�x���g�Ȃ� */

/*
 *  �A�v���P�[�V�������[�h�l�̒�`
 */
#define APPMODE_NONE	((AppModeType) 0)	/* ���[�h�Ȃ� */

/*
 *  IPL�l�̒�`
 */
#define IPL_ENA_ALL	((IPL) 0)		/* ���ׂĂ̊����݂����� */

/*
 *  ���s���̃R���e�L�X�g�icallevel�j�̒l�̒�`
 */
#define TCL_NULL		((UINT8) 0x00)	/* �T�[�r�X�R�[�����Ăяo���Ȃ� */
#define TCL_TASK		((UINT8) 0x01)	/* �^�X�N */
#define TCL_ISR2		((UINT8) 0x02)	/* �J�e�S��2 ISR */
#define TCL_ERROR		((UINT8) 0x04)	/* ErrorHook */
#define TCL_PREPOST		((UINT8) 0x08)	/* PreTaskHook�CPostTaskHook */
#define TCL_STARTUP		((UINT8) 0x10)	/* StartupHook */
#define TCL_SHUTDOWN	((UINT8) 0x20)	/* ShutdownHook */

/*
 *  �^�[�Q�b�g�ˑ����̒�`
 */
#include <t_config.h>

#ifndef _MACRO_ONLY
/*
 *  OS���s����̂��߂̕ϐ��iosctl.c�j
 */
extern UINT8		callevel;	/* ���s���̃R���e�L�X�g */
extern AppModeType	appmode;	/* �A�v���P�[�V�������[�h */

/*
 *  OS���̃N���e�B�J���Z�N�V��������֐�
 */
Inline void	lock_cpu(void);		/* �N���e�B�J���Z�N�V�����J�n */
Inline void	unlock_cpu(void);	/* �N���e�B�J���Z�N�V�����I�� */

Inline void
lock_cpu(void)
{
	disable_int();
}

Inline void
unlock_cpu(void)
{
	enable_int();
}

/*
 *  �G���[�t�b�N�Ăяo���̂��߂̐錾�iosctl.c�j
 *
 *  �T�[�r�X�R�[�����ŃG���[�����������ꍇ�ɂ́C�T�[�r�X�R�[���ւ̃p��
 *  ���[�^�� _errorhook_par1�`3 �ɐݒ肵����Ccall_errorhook ���Ăяo���D
 *  call_errorhook �ւ́C�G���[�R�[�h�ƃT�[�r�X�R�[����ID��n���D
 */
extern void	call_errorhook(StatusType ercd, OSServiceIdType svcid);

/*
 *  �|�X�g�^�X�N�t�b�N/�v���^�X�N�t�b�N�Ăяo���̂��߂̐錾�iosctl.c�j
 */
extern void	call_posttaskhook(void);
extern void	call_pretaskhook(void);

/*
 *  �e���W���[���̏������ikernel_cfg.c�j
 */
extern void	object_initialize(void);

#endif /* _MACRO_ONLY */

/*
 *  �g���X�e�[�^�X��W����
 */
#ifndef BASIC_STATUS
#define EXTENDED_STATUS
#endif /* BASIC_STATUS */

#endif /* _OSEK_KERNEL_H_ */
