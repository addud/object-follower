' 
'   TOPPERS/JSP Kernel
'       Toyohashi Open Platform for Embedded Real-Time Systems/
'       Just Standard Profile Kernel
'  
'   Copyright (C) 2000-2002 by Embedded and Real-Time Systems Laboratory
'                               Toyohashi Univ. of Technology, JAPAN
'  
'   ��L���쌠�҂́C�ȉ��� (1)�`(4) �̏������CFree Software Foundation 
'   �ɂ���Č��\����Ă��� GNU General Public License �� Version 2 �ɋL
'   �q����Ă�������𖞂����ꍇ�Ɍ���C�{�\�t�g�E�F�A�i�{�\�t�g�E�F�A
'   �����ς������̂��܂ށD�ȉ������j���g�p�E�����E���ρE�Ĕz�z�i�ȉ��C
'   ���p�ƌĂԁj���邱�Ƃ𖳏��ŋ�������D
'   (1) �{�\�t�g�E�F�A���\�[�X�R�[�h�̌`�ŗ��p����ꍇ�ɂ́C��L�̒���
'       ���\���C���̗��p��������щ��L�̖��ۏ؋K�肪�C���̂܂܂̌`�Ń\�[
'       �X�R�[�h���Ɋ܂܂�Ă��邱�ƁD
'   (2) �{�\�t�g�E�F�A���C���C�u�����`���ȂǁC���̃\�t�g�E�F�A�J���Ɏg
'       �p�ł���`�ōĔz�z����ꍇ�ɂ́C�Ĕz�z�ɔ����h�L�������g�i���p
'       �҃}�j���A���Ȃǁj�ɁC��L�̒��쌠�\���C���̗��p��������щ��L
'       �̖��ۏ؋K����f�ڂ��邱�ƁD
'   (3) �{�\�t�g�E�F�A���C�@��ɑg�ݍ��ނȂǁC���̃\�t�g�E�F�A�J���Ɏg
'       �p�ł��Ȃ��`�ōĔz�z����ꍇ�ɂ́C���̂����ꂩ�̏����𖞂�����
'       �ƁD
'     (a) �Ĕz�z�ɔ����h�L�������g�i���p�҃}�j���A���Ȃǁj�ɁC��L�̒�
'         �쌠�\���C���̗��p��������щ��L�̖��ۏ؋K����f�ڂ��邱�ƁD
'     (b) �Ĕz�z�̌`�Ԃ��C�ʂɒ�߂���@�ɂ���āCTOPPERS�v���W�F�N�g��
'         �񍐂��邱�ƁD
'   (4) �{�\�t�g�E�F�A�̗��p�ɂ�蒼�ړI�܂��͊ԐړI�ɐ����邢���Ȃ鑹
'       �Q������C��L���쌠�҂����TOPPERS�v���W�F�N�g��Ɛӂ��邱�ƁD
'  
'   �{�\�t�g�E�F�A�́C���ۏ؂Œ񋟂���Ă�����̂ł���D��L���쌠�҂�
'   ���TOPPERS�v���W�F�N�g�́C�{�\�t�g�E�F�A�Ɋւ��āC���̓K�p�\����
'   �܂߂āC�����Ȃ�ۏ؂��s��Ȃ��D�܂��C�{�\�t�g�E�F�A�̗��p�ɂ�蒼
'   �ړI�܂��͊ԐړI�ɐ����������Ȃ鑹�Q�Ɋւ��Ă��C���̐ӔC�𕉂�Ȃ��D
'  
'   @(' ) $Id: make.vbs,v 1.11 2003/12/26 03:49:46 honda Exp $
'  

dim model
dim msdev

if msgbox("TOPPERS/JSP �J�[�l���R���t�B�M�����[�^ ����� �\���`�F�b�J�𐶐����܂��D�������J�n���Ă���낵���ł���?", vbYesno) = vbyes then

	if msgbox("�����[�X�r���h���܂���? (�u�������v��I�Ԃƃf�o�b�O�\�Ȏ��s�t�@�C���𐶐����܂�)",vbyesno) = vbyes then
		model = " - Win32 Release"
	else
		model = " - Win32 Debug"
	end if

		'Visual C++ �̋N��
	set msdev = CreateObject("MSDEV.APPLICATION")
	msdev.visible = true

	msdev.documents.open left(Wscript.ScriptFullName, len(Wscript.scriptfullname) - len(wscript.scriptname)) + "configurator.dsw"

		'�`�F�b�J�̐���
	set msdev.activeproject = msdev.projects("checker")
	set msdev.activeconfiguration = msdev.activeproject.configurations("checker" + model)

	if msgbox("�`�F�b�J��Windows�p�ł���?" & vbcr & "(�u�������v��I�Ԃ�cygwin/MinGW�p�̃`�F�b�J�𐶐����܂�)", vbyesno) = vbno then
		msdev.activeconfiguration.removetoolsettings "cl.exe","/D " & chr(34) & "FILECONTAINER_WINDOWS" & chr(34)
		msdev.activeconfiguration.addtoolsettings "cl.exe","/D " & chr(34) & "FILECONTAINER_BINUTILS" & chr(34)
	else
		msdev.activeconfiguration.removetoolsettings "cl.exe","/D " & chr(34) & "FILECONTAINER_BINUTILS" & chr(34)
		msdev.activeconfiguration.addtoolsettings "cl.exe","/D " & chr(34) & "FILECONTAINER_WINDOWS" & chr(34)
	end if

	msdev.rebuildall

		'�R���t�B�M�����[�^�̐���
	set msdev.activeproject = msdev.projects("configurator")
	set msdev.activeconfiguration = msdev.activeproject.configurations("configurator" + model)
	msdev.build

msdev.quit
set msdev = nothing

msgbox "�S�Ă̏������I�����܂���"
end if
