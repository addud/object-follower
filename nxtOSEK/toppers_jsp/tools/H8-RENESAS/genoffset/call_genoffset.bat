echo off
rem TCB�\���̂̃I�t�Z�b�g�Z�o

rem HEW�ł́A���΃p�X�w��ŊO���c�[�����Ăяo���Ȃ����߁A
rem �o�b�`�t�@�C�����o�R���āA�R���t�B�M�����[�^���Ăяo���Ă���
rem
rem jsp/config/h8-renessas/makeoffset.c���R���p�C�����ꂽ
rem ���ʂ̃t�@�C�������A����%1�Ƃ���HEW���炱�̃o�b�`�t�@�C���ɓn�����B
rem
rem Perl�̌Ăяo���Ɏ��s����ꍇ�̓p�X��ʂ����ƁB

echo on

perl ..\..\..\..\utils\h8-renesas\genoffset %1 > offset.inc
if errorlevel 1 exit 1
