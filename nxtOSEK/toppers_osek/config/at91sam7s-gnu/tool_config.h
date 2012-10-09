/*
 *  TOPPERS/OSEK Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      OSEK Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2004 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
 *  Copyright (C) 2006 by Witz Corporation, JAPAN
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
 *	�J�����ˑ����W���[��(arm-elf-gcc�p)
 *
 *  ���̃C���N���[�h�t�@�C���́Ct_config.h �݂̂���C���N���[�h�����D
 *  ���̃t�@�C�����璼�ڃC���N���[�h���Ă͂Ȃ�Ȃ��D
 */


#ifndef _TOOL_CONFIG_H_
#define _TOOL_CONFIG_H_

/*
 *  �J�����ˑ��̏������͎g�p���Ȃ�
 */
#define tool_initialize()

/*
 *  �g���[�X���O�̐ݒ�
 */

#define LOG_ACTTSK_ENTER(tskid)
#define LOG_ACTTSK_LEAVE(ercd)
#define LOG_TERTSK_ENTER()
#define LOG_TERTSK_LEAVE(ercd)
#define LOG_CHNTSK_ENTER(tskid)
#define LOG_CHNTSK_LEAVE(ercd)
#define LOG_SCHED_ENTER()
#define LOG_SCHED_LEAVE(ercd)
#define LOG_GETTID_ENTER(p_tskid)
#define LOG_GETTID_LEAVE(ercd, tskid)
#define LOG_GETTST_ENTER(tskid, p_state)
#define LOG_GETTST_LEAVE(ercd, state)
#define LOG_DISINT_ENTER()
#define LOG_DISINT_LEAVE()
#define LOG_ENAINT_ENTER()
#define LOG_ENAINT_LEAVE()
#define LOG_SUSALL_ENTER()
#define LOG_SUSALL_LEAVE()
#define LOG_RSMALL_ENTER()
#define LOG_RSMALL_LEAVE()
#define LOG_SUSOSI_ENTER()
#define LOG_SUSOSI_LEAVE()
#define LOG_RSMOSI_ENTER()
#define LOG_RSMOSI_LEAVE()
#define LOG_GETRES_ENTER(resid)
#define LOG_GETRES_LEAVE(ercd)
#define LOG_RELRES_ENTER(resid)
#define LOG_RELRES_LEAVE(ercd)
#define LOG_SETEVT_ENTER(tskid, mask)
#define LOG_SETEVT_LEAVE(ercd)
#define LOG_CLREVT_ENTER(mask)
#define LOG_CLREVT_LEAVE(ercd)
#define LOG_GETEVT_ENTER(tskid, p_mask)
#define LOG_GETEVT_LEAVE(ercd, mask)
#define LOG_WAIEVT_ENTER(mask)
#define LOG_WAIEVT_LEAVE(ercd)
#define LOG_GETALB_ENTER(almid, info)
#define LOG_GETALB_LEAVE(ercd)
#define LOG_GETALM_ENTER(almid, p_tick)
#define LOG_GETALM_LEAVE(ercd)
#define LOG_SETREL_ENTER(almid, incr, cycle)
#define LOG_SETREL_LEAVE(ercd)
#define LOG_SETABS_ENTER(almid, start, cycle)
#define LOG_SETABS_LEAVE(ercd)
#define LOG_CANALM_ENTER(almid)
#define LOG_CANALM_LEAVE(ercd)
#define LOG_SIGCNT_ENTER(cntid)
#define LOG_SIGCNT_LEAVE(ercd)
#define LOG_GETAAM_ENTER()
#define LOG_GETAAM_LEAVE(mode)
#define LOG_STAOS_ENTER(mode)
#define LOG_STAOS_LEAVE()
#define LOG_STUTOS_ENTER(ercd)
#define LOG_STUTOS_LEAVE()

#endif /* _TOOL_CONFIG_H_ */
