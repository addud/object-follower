echo off
rem �J�[�l���\�[�X�t�@�C���̃R�s�[

rem �֐��P�ʂŃ����N���邽�߁A�J�[�l���̃\�[�X�R�[�h��#define����ǉ�����
rem �R�s�[����B

rem jsp\tools\H8S-RENESAS\libkernel\source���猩�����΃p�X�Ŏw�肷��B

perl ../../../../utils/h8-renesas/copy_kernel_source.pl ../../../../kernel .
if errorlevel 1 exit 1
