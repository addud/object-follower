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

rem HEW�ł́A�����t�@�C�����Ńp�X�݈̂قȂ�\�[�X�t�@�C�����R���t�B
rem �M�����[�V����(Debug/Release)�ɂ���āA�r���h�Ώۂ��g�������邱��
rem ���ł��Ȃ��B
rem �����������邽�߁Avector.src��debug_vector.src��release_vector.
rem src�ɃR�s�[���A��x�A�������v���W�F�N�g�ɓo�^���A�R���t�B�M�����[
rem �V�������ɂ���Ȃ��t�@�C�����r���h�Ώۂ��珜�O����B
rem kernel_cfg.c�ɂ��Ă����l

rem Perl�̌Ăяo���Ɏ��s����ꍇ�̓p�X��ʂ����ƁB

echo on

..\..\..\..\cfg\cfg.exe -s %1 -c -obj -cpu h8s -system minet_h8s_2339f
type kernel_cfg.c > debug_kernel_cfg.c
type kernel_cfg.c > release_kernel_cfg.c
del kernel_cfg.c

perl ..\..\..\..\utils\h8\grep_def_inh.pl %1 > tmp_script.pl
type ..\..\..\..\config\h8s-renesas\vector_header.src > vector.src
perl ..\..\..\..\utils\h8-renesas\genvector.pl -s 92 >> vector.src
perl ..\..\..\..\utils\h8s-renesas\gen_intentry.pl >> vector.src
del tmp_script.pl
type vector.src > debug_vector.src
type vector.src > release_vector.src
del vector.src

