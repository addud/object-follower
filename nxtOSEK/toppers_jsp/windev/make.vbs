' TOPPERS/JSP Kernel
'     Toyohashi Open Platform for Embedded Real-Time Systems/
'     Just Standard Profile Kernel
'
' Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
'                             Toyohashi Univ. of Technology, JAPAN
'
' ��L���쌠�҂́C�ȉ��� (1)�`(4) �̏������CFree Software Foundation 
' �ɂ���Č��\����Ă��� GNU General Public License �� Version 2 �ɋL
' �q����Ă�������𖞂����ꍇ�Ɍ���C�{�\�t�g�E�F�A�i�{�\�t�g�E�F�A
' �����ς������̂��܂ށD�ȉ������j���g�p�E�����E���ρE�Ĕz�z�i�ȉ��C
' ���p�ƌĂԁj���邱�Ƃ𖳏��ŋ�������D
' (1) �{�\�t�g�E�F�A���\�[�X�R�[�h�̌`�ŗ��p����ꍇ�ɂ́C��L�̒���
'     ���\���C���̗��p��������щ��L�̖��ۏ؋K�肪�C���̂܂܂̌`�Ń\�[
'     �X�R�[�h���Ɋ܂܂�Ă��邱�ƁD
' (2) �{�\�t�g�E�F�A���C���C�u�����`���ȂǁC���̃\�t�g�E�F�A�J���Ɏg
'     �p�ł���`�ōĔz�z����ꍇ�ɂ́C�Ĕz�z�ɔ����h�L�������g�i���p
'     �҃}�j���A���Ȃǁj�ɁC��L�̒��쌠�\���C���̗��p��������щ��L
'     �̖��ۏ؋K����f�ڂ��邱�ƁD
' (3) �{�\�t�g�E�F�A���C�@��ɑg�ݍ��ނȂǁC���̃\�t�g�E�F�A�J���Ɏg
'     �p�ł��Ȃ��`�ōĔz�z����ꍇ�ɂ́C���̂����ꂩ�̏����𖞂�����
'     �ƁD
'   (a) �Ĕz�z�ɔ����h�L�������g�i���p�҃}�j���A���Ȃǁj�ɁC��L�̒�
'       �쌠�\���C���̗��p��������щ��L�̖��ۏ؋K����f�ڂ��邱�ƁD
'   (b) �Ĕz�z�̌`�Ԃ��C�ʂɒ�߂���@�ɂ���āCTOPPERS�v���W�F�N�g��
'       �񍐂��邱�ƁD
' (4) �{�\�t�g�E�F�A�̗��p�ɂ�蒼�ړI�܂��͊ԐړI�ɐ����邢���Ȃ鑹
'     �Q������C��L���쌠�҂����TOPPERS�v���W�F�N�g��Ɛӂ��邱�ƁD
'
' �{�\�t�g�E�F�A�́C���ۏ؂Œ񋟂���Ă�����̂ł���D��L���쌠�҂�
' ���TOPPERS�v���W�F�N�g�́C�{�\�t�g�E�F�A�Ɋւ��āC���̓K�p�\����
' �܂߂āC�����Ȃ�ۏ؂��s��Ȃ��D�܂��C�{�\�t�g�E�F�A�̗��p�ɂ�蒼
' �ړI�܂��͊ԐړI�ɐ����������Ȃ鑹�Q�Ɋւ��Ă��C���̐ӔC�𕉂�Ȃ��D
'
' @(#) $Id: make.vbs,v 1.8 2003/12/26 03:50:06 honda Exp $
'

dim model
dim msdev
dim rootdir

rootdir = left(Wscript.ScriptFullName, len(Wscript.scriptfullname) - len(wscript.scriptname))

if msgbox("TOPPERS/JSP Windows �f�o�C�X�}�l�[�W�� ����� ATL�f�o�C�X�R���g���[���𐶐����܂��D�������J�n���Ă���낵���ł���?", vbYesno) = vbyes then

	if msgbox("�����[�X�r���h���܂���? (�u�������v��I�Ԃƃf�o�b�O�\�Ȏ��s�t�@�C���𐶐����܂�)",vbyesno) = vbyes then
		model = " - Win32 Unicode Release MinDependency"
	else
		model = " - Win32 Debug"
	end if

		'Visual C++ �̋N��
	set msdev = CreateObject("MSDEV.APPLICATION")
	msdev.visible = true

		'�f�o�C�X�}�l�[�W���̐���
	msdev.documents.open rootdir + "devicemanager\devicemanager.dsw"
	set msdev.activeproject = msdev.projects("devicemanager")
	set msdev.activeconfiguration = msdev.activeproject.configurations("devicemanager" + model)
	msdev.build

		'�f�o�C�X�R���g���[���̐���
	msdev.documents.open rootdir + "devicecontrol\device.dsw"
	set msdev.activeproject = msdev.projects("device")
	set msdev.activeconfiguration = msdev.activeproject.configurations("device" + model)
	msdev.build

		'cmdwatch�̐���
	msdev.documents.open rootdir + "cmdwatch\cmdwatch.dsw"
	set msdev.activeproject = msdev.projects("cmdwatch")
	set msdev.activeconfiguration = msdev.activeproject.configurations("cmdwatch" + model)
	msdev.build

		'�E�H�b�`���R���g���[���̐���
	msdev.documents.open rootdir + "watcher\watcher.dsw"
	set msdev.activeproject = msdev.projects("watcher")
	set msdev.activeconfiguration = msdev.activeproject.configurations("watcher" + model)
	msdev.build


msdev.quit
set msdev = nothing

msgbox "�S�Ă̏������I�����܂���"
end if
