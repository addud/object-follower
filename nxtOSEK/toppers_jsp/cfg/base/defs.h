/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 * 
 *  �嵭����Ԥϡ��ʲ��� (1)��(4) �ξ�狼��Free Software Foundation 
 *  �ˤ�äƸ�ɽ����Ƥ��� GNU General Public License �� Version 2 �˵�
 *  �Ҥ���Ƥ���������������˸¤ꡤ�ܥ��եȥ��������ܥ��եȥ�����
 *  ����Ѥ�����Τ�ޤࡥ�ʲ�Ʊ���ˤ���ѡ�ʣ�������ѡ������ۡʰʲ���
 *  ���ѤȸƤ֡ˤ��뤳�Ȥ�̵���ǵ������롥
 *  (1) �ܥ��եȥ������򥽡��������ɤη������Ѥ�����ˤϡ��嵭������
 *      ��ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ��꤬�����Τޤޤη��ǥ���
 *      ����������˴ޤޤ�Ƥ��뤳�ȡ�
 *  (2) �ܥ��եȥ������򡤥饤�֥������ʤɡ�¾�Υ��եȥ�������ȯ�˻�
 *      �ѤǤ�����Ǻ����ۤ�����ˤϡ������ۤ�ȼ���ɥ�����ȡ�����
 *      �ԥޥ˥奢��ʤɡˤˡ��嵭�����ɽ�����������Ѿ�浪��Ӳ���
 *      ��̵�ݾڵ����Ǻܤ��뤳�ȡ�
 *  (3) �ܥ��եȥ������򡤵�����Ȥ߹���ʤɡ�¾�Υ��եȥ�������ȯ�˻�
 *      �ѤǤ��ʤ����Ǻ����ۤ�����ˤϡ����Τ����줫�ξ�����������
 *      �ȡ�
 *    (a) �����ۤ�ȼ���ɥ�����ȡ����Ѽԥޥ˥奢��ʤɡˤˡ��嵭����
 *        �ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ����Ǻܤ��뤳�ȡ�
 *    (b) �����ۤη��֤��̤�������ˡ�ˤ�äơ�TOPPERS�ץ������Ȥ�
 *        ��𤹤뤳�ȡ�
 *  (4) �ܥ��եȥ����������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������뤤���ʤ�»
 *      ������⡤�嵭����Ԥ����TOPPERS�ץ������Ȥ����դ��뤳�ȡ�
 * 
 *  �ܥ��եȥ������ϡ�̵�ݾڤ��󶡤���Ƥ����ΤǤ��롥�嵭����Ԥ�
 *  ���TOPPERS�ץ������Ȥϡ��ܥ��եȥ������˴ؤ��ơ�����Ŭ�Ѳ�ǽ����
 *  �ޤ�ơ������ʤ��ݾڤ�Ԥ�ʤ����ޤ����ܥ��եȥ����������Ѥˤ��ľ
 *  ��Ū�ޤ��ϴ���Ū�������������ʤ�»���˴ؤ��Ƥ⡤������Ǥ�����ʤ���
 * 
 *  @(#) $Id: defs.h,v 1.10 2003/12/15 07:32:13 takayuki Exp $
 */


// $Header: /home/CVS/configurator/base/defs.h,v 1.10 2003/12/15 07:32:13 takayuki Exp $

#ifndef DEFS_H
#define DEFS_H

    /*
     *  �����Ϥ˰�¸������ʬ
     *      �ؿ�̾�� : mktemp, popen, pclose
     */

#ifdef CALL_EXTERNAL_PROGRAM

    /* Microsoft Visual C++ */
#if defined(_MSC_VER) || defined(__MINGW__)
#  include <io.h>
#  define   popen _popen
#  define   pclose _pclose
#  define   mktemp _mktemp

    /* GNU Compiler Collection on Linux environment*/
#elif defined(__GNUC__)
#  include  <stdlib.h>
#  define   mktemp mkstemp

    /* GNU Compiler Collection on Cygwin */
#elif defined(__CYGWIN__)
#  include  <stdlib.h>
#  define   mktemp mkstemp

    /* Borland C++ Compiler */
#elif defined(__BORLANDC__)
#  include <io.h>
#  include <stdio.h>
#  define   popen  ::std::_popen
#  define   pclose ::std::_pclose
#  define   mktemp ::std::_mktemp

#endif


    /*
     *  fc_binutils.cpp�����Ѥ���ץ��������
     */

#ifdef _MSC_VER
#  define   CMD_PREPROCESSOR "\"C:\\Program Files\\Microsoft Visual Studio\\VC98\\Bin\\cl.exe\" /E /nologo"
#  define   CMD_SYMBOLLISTER "nm.exe"
#  define   CMD_OBJDUMP      "objdump.exe"
#  define   CMD_OBJCOPY      "objcopy.exe"
#  define   CMD_GREP         "grep.exe"
#else
#  define   CMD_PREPROCESSOR "cpp -ansi"
#  define   CMD_SYMBOLLISTER "nm"
#  define   CMD_OBJDUMP      "objdump"
#  define   CMD_OBJCOPY      "objcopy"
#  define   CMD_GREP         "grep"
#endif

#endif /* CALL_EXTERNAL_PROGRAM */

#endif /* DEFS_H */

