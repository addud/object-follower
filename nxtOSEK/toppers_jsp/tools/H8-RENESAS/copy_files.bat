echo off
rem ���Ӂ@HEW�Ńr���h����O�ɁA���̃o�b�`�t�@�C����\�ߎ��s���Ă����B

rem �ˑ����Ɣ�ˑ����̃\�[�X�t�@�C����
rem jsp\tools\H8-RENESAS\libkernel\kernel_source�ɃR�s�[

cd libkernel\kernel_source
xcopy /Q /I /D /S ..\..\..\..\config\h8-renesas h8-renesas
xcopy /Q /I /D ..\..\..\..\kernel kernel
xcopy /Q /I /D ..\..\..\..\library library
xcopy /Q /I /D ..\..\..\..\systask systask

rem �J�[�l���\�[�X�t�@�C���̃R�s�[
rem �֐��P�ʂŃ����N���邽�߁A�J�[�l���̃\�[�X�R�[�h��#define����ǉ�����
rem �R�s�[����B

mkdir kernel_api
perl ../../../../utils/h8-renesas/copy_kernel_source.pl ../../../../kernel kernel_api
cd ..\..
