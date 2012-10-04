'
'   TOPPERS/JSP Kernel
'       Toyohashi Open Platform for Embedded Real-Time Systems/
'       Just Standard Profile Kernel
'  
'   Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
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
'   @(#) $Id: configure.vbs,v 1.9 2007/04/19 07:11:32 honda Exp $
'

	'----------------------------------------------------------'
	' ���̃X�N���v�g�́CWScript.WshShell.Run���g�p���Ă���̂� '
	'  �s�̂̃E�B���X�`�F�b�J�������Ă���ƈ����Ɣ��f����܂�  '
	'----------------------------------------------------------'

dim ws
dim msdev
dim rootdir

rootdir = left(Wscript.ScriptFullName, len(Wscript.scriptfullname) - len(wscript.scriptname))

set ws = WScript.CreateObject("WScript.Shell")

msgbox "TOPPERS/JSP Windows ���g�p����̂ɕK�v�ȃv���O�������쐬���܂��D"

ws.run "..\..\cfg\vc_project\make.vbs",1,true
ws.run "..\..\windev\make.vbs",1,true
set ws = nothing

msgbox "�����͐���ɏI�����܂���"

if msgbox("Visual C++ ���N�����܂���?",vbokcancel) = vbok then
	set msdev = CreateObject("MSDev.Application")
	msdev.visible = true
	msdev.documents.open rootdir + "vc_project\toppers.dsw"
	msdev.documents.open rootdir + "..\..\doc\windows.txt", "text", true
	set msdev = nothing
end if
