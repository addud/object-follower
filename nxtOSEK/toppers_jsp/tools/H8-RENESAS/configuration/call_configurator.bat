echo off
rem �V�X�e���E�R���t�B�M�����[�V�����ƃx�N�^�e�[�u���̎�������

rem HEW�ł́A���΃p�X�w��ŊO���c�[�����Ăяo���Ȃ����߁A
rem �o�b�`�t�@�C�����o�R���āA�R���t�B�M�����[�^���Ăяo���Ă���
rem
rem �V�X�e���E�R���t�B�M�����[�V�����E�t�@�C�����v���v���Z�X���ꂽ
rem ���ʂ̃t�@�C�������A����%1�Ƃ���HEW���炱�̃o�b�`�t�@�C���ɓn�����B

rem �ȉ��̕����͈ڐA�̍ۂɕύX����K�v������
rem �V�X�e���ˑ����̃f�B���N�g����
rem cfg.exe -s %1 -c -obj -cpu h8 -system xxxxxxxx

rem �x�N�^�e�[�u���̃T�C�Y
rem genvector.pl -s xxx

rem �V�X�e���E�R���t�B�M�����[�V����
..\..\..\..\cfg\cfg.exe -s %1 -c -obj -cpu h8 -system hsb8f3048bf25
if errorlevel 1 exit 1
type kernel_cfg.c > debug_kernel_cfg.c
type kernel_cfg.c > release_kernel_cfg.c
del kernel_cfg.c

rem �x�N�^�e�[�u���̎�������
perl ..\..\..\..\utils\h8\grep_def_inh.pl %1 > tmp_script.pl
if errorlevel 1 exit 1
type ..\..\..\..\config\h8-renesas\vector_header.src > vector.src
perl ..\..\..\..\utils\h8-renesas\genvector.pl -s 61 >> vector.src
if errorlevel 1 exit 1
perl ..\..\..\..\utils\h8-renesas\gen_intentry.pl >> vector.src
if errorlevel 1 exit 1
del tmp_script.pl
type vector.src > debug_vector.src
type vector.src > release_vector.src
del vector.src
