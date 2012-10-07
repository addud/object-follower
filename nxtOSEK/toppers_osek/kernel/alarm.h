/*
 *  TOPPERS/OSEK Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      OSEK Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2004,2006 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
 *  Copyright (C) 2004-2006 by Witz Corporation, JAPAN
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
 *	�A���[���@�\
 */

#ifndef _ALARM_H_
#define _ALARM_H_

/*
 *  �A���[��ID�̓���Ȓl�̒�`
 */
#define ALMID_NULL		((AlarmType) UINT8_INVALID)	/* ����ID */

/*
 *  �J�E���^���E�A���[������ێ�����ϐ��̐錾
 */
extern const UINT8		tnum_counter;		/* �J�E���^�̐� */
extern const UINT8		tnum_alarm;			/* �A���[���̐� */

/*
 *  �J�E���^�������u���b�N
 */
extern const TickType	cntinib_maxval[];	/* �J�E���^�̍ő�l */
extern const TickType	cntinib_maxval2[];	/* �J�E���^�̍ő�l��2�{+1 */
extern const TickType	cntinib_tickbase[];	/* 1��Ői�ރe�B�b�N�� */
extern const TickType	cntinib_mincyc[];	/* �����̍ŏ��l */

/*
 *  �J�E���^�Ǘ��u���b�N
 */
extern TickType			cntcb_curval[];		/* �J�E���^�̌��݃e�B�b�N */
extern AlarmType		cntcb_almque[];		/* �A���[���̃L���[ */

/*
 *  �A���[���������u���b�N
 */
extern const CounterType alminib_cntid[];	/* �t������Ă���J�E���^ */
extern const FP			 alminib_cback[];	/* �A���[���R�[���o�b�N */
extern const AppModeType alminib_autosta[];	/* �N�����郂�[�h */
extern const TickType	 alminib_almval[];	/* expire ����e�B�b�N�l */
extern const TickType	 alminib_cycle[];	/* �A���[���̎��� */

/*
 *  �A���[���Ǘ��u���b�N
 *
 *  �A���[�����A���[���L���[�ɑ}������Ă��Ȃ��ꍇ�Calmcb_next�ɂ�
 *  ���̃A���[����ID�������Ă���inext���������w���Ă���j�D
 */
extern AlarmType		almcb_next[];		/* �A���[���L���[ */
extern AlarmType		almcb_prev[];		/* �A���[���L���[ */
extern TickType			almcb_almval[];		/* expire ����e�B�b�N�l */
extern TickType			almcb_cycle[];		/* �A���[���̎��� */

/*
 *  �A���[���@�\�̏�����
 */
extern void	alarm_initialize(void);

#endif /* _ALARM_H_ */
