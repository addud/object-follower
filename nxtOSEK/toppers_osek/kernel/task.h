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
 *	�^�X�N�Ǘ����W���[��
 */

#ifndef _TASK_H_
#define _TASK_H_

/*
 *  �^�X�NID�̓���Ȓl�̒�`
 */
#define TSKID_NULL		((TaskType) UINT8_INVALID)	/* ����ID */

/*
 *  �^�X�N��ԁitcb_stat�j�l�̒�`
 */
#define TS_RUNNABLE		READY				/* ���s��ԁC���s�\��� */
#define TS_DORMANT		SUSPENDED			/* �x�~��� */
#define TS_WAITING		WAITING				/* �҂���� */

/*
 *  �^�X�N����ێ�����ϐ��̐錾�ikernel_cfg.c�j
 */
extern const UINT8	tnum_task;		/* �^�X�N�̐� */
extern const UINT8	tnum_exttask;		/* �g���^�X�N�̐� */

/*
 *  �^�X�N�������u���b�N�ikernel_cfg.c�j
 */
extern const Priority	tinib_inipri[];		/* �����D��x */
extern const Priority	tinib_exepri[];		/* ���s�J�n���̗D��x */
extern const UINT8		tinib_maxact[];		/* ���d�N���v���̍ő吔 */
extern const AppModeType tinib_autoact[];	/* �N�����郂�[�h */
extern const FP			tinib_task[];		/* �^�X�N�̋N���Ԓn */
extern const VP			tinib_stk[];		/* �X�^�b�N�̈�̐擪�Ԓn */
extern const UINT16		tinib_stksz[];		/* �X�^�b�N�̈�̃T�C�Y */

/*
 *  �^�X�N�Ǘ��u���b�N�ikernel_cfg.c�j
 *
 *  ���̑��ɁC�^�X�N�R���e�L�X�g��ۑ����邽�߂̔z�񂪁C�^�[�Q�b�g�ˑ�
 *  �ɒ�`�����D
 */
extern TaskType			tcb_next[];			/* �^�X�N�L���[ */
extern UINT8			tcb_tstat[];		/* �^�X�N��� */
extern Priority			tcb_curpri[];		/* ���݂̗D��x */
extern UINT8			tcb_actcnt[];		/* ���d�N���v���� */
extern EventMaskType	tcb_curevt[];		/* �C�x���g�̌��ݒl */
extern EventMaskType	tcb_waievt[];		/* �҂��Ă���C�x���g */
extern ResourceType		tcb_lastres[];		/* �Ō�Ɋl���������\�[�X */

/*
 *  ���s��Ԃ̃^�X�N
 *
 *  ���s��Ԃ̃^�X�N���Ȃ��ꍇ�ɂ́CTSKID_NULL �ɂ���D
 */
extern TaskType			runtsk;

/*
 *  �ō��D�揇�ʃ^�X�N
 *
 *  �^�X�N���s���́Cruntsk �ƈ�v����D���s�ł����ԁi���s��Ԃ܂���
 *  ���s�\��ԁj�̃^�X�N���Ȃ��ꍇ�ɂ́CTSKID_NULL �ɂ���D
 */
extern TaskType			schedtsk;

/*
 *  ���f�B�L���[���̍ō��D��x
 *
 *  ���f�B�L���[�ɂ͎��s�\��Ԃ̃^�X�N�݂̂��܂ނ̂ŁC���s�\��Ԃ�
 *  �^�X�N�̒��o�̍ō��D��x��ێ�����D���f�B�L���[����̎��i���s�\
 *  ��Ԃ̃^�X�N���������j�� TPRI_MINTASK�i��0�j�ɂ���D
 */
extern Priority			nextpri;

/*
 *  �^�X�N�Ǘ����W���[���̏�����
 */
extern void	task_initialize(void);

/*
 *  �^�X�N�̋N��
 *
 *  �Ώۃ^�X�N�itskid �Ŏw�肵���^�X�N�j���N������i�x�~��Ԃ�����s��
 *  �����ԂɑJ�ڂ�����D�^�X�N�̋N�����ɕK�v�ȏ��������s���D
 */
extern BOOL	make_active(TaskType tskid);

/*
 *  ���s�ł����Ԃւ̈ڍs
 *
 *  �Ώۃ^�X�N�itskid �Ŏw�肵���^�X�N�j�����s�ł����ԂɑJ�ڂ�����D
 *  �Ώۃ^�X�N�̗D��x���C�ō��D��x�^�X�N�ischedtsk�j�̗D��x������
 *  ���ꍇ�ɂ́C�Ώۃ^�X�N��V�����ō��D��x�^�X�N�Ƃ��C����܂ł̍ō�
 *  �D��x�^�X�N�����f�B�L���[�̐擪�ɓ����D�����łȂ��ꍇ�ɂ́C�Ώ�
 *  �^�X�N�����f�B�L���[�̖����ɓ����D�Ώۃ^�X�N���ō��D��x�^�X�N��
 *  �����ꍇ�ɁCTRUE ��Ԃ��D
 */
extern BOOL	make_runnable(TaskType tskid);

/*
 *  �ō��D�揇�ʃ^�X�N�̃T�[�`
 *
 *  ���f�B�L���[���ōł��D�揇�ʂ̍����^�X�N���T�[�`���C��������f�B
 *  �L���[����O���āC�ō��D�揇�ʃ^�X�N�ischedtsk�j�Ƃ���D���ۂɂ́C
 *  ���f�B�L���[���̍ō��D��x�� nextpri �ɐݒ肳��Ă��邽�߂ɃT�[�`
 *  �͕K�v�Ȃ��C�D��x nextpri �̃��f�B�L���[�̐擪�̃^�X�N���ō��D��
 *  ���ʃ^�X�N�Ƃ���D���f�B�L���[�̃T�[�`�́C���̃^�X�N�����f�B�L���[
 *  ����O������� nextpri ���X�V���邽�߂ɕK�v�ƂȂ�D���̃T�[�`�ɁC
 *  ready_primap ��p����D
 *  ���̊֐��́C����܂Ŏ��s��Ԃł������^�X�N���҂���Ԃ��x�~��ԂɈ�
 *  �s�������ɁC���Ɏ��s���ׂ��^�X�N��I�Ԃ��߂ɌĂяo���D����Ă��̊�
 *  ���ł́C����܂ł̍ō��D��x�^�X�N�͖�������D
 */
extern void	search_schedtsk(void);

/*
 *  �^�X�N�̃v���G���v�g
 *
 *  ���^�X�N�����s�\��ԂɈڍs�����C�ō��D��x�^�X�N�����s��Ԃɂ���D
 *  ���̊֐�����߂�����ɁCdispatch ���Ăяo���đ��̃^�X�N�֐؂�ւ���
 *  ���Ƃ�z�肵�Ă���D
 */
extern void	preempt(void);

#endif /* _TASK_H_ */
