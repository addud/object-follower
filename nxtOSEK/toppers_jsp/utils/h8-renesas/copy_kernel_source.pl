#! /usr/bin/perl
#
#  TOPPERS/JSP Kernel
#      Toyohashi Open Platform for Embedded Real-Time Systems/
#      Just Standard Profile Kernel
# 
#  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
#                              Toyohashi Univ. of Technology, JAPAN
#  Copyright (C) 2004 by Embedded and Real-Time Systems Laboratory
#              Graduate School of Information Science, Nagoya Univ., JAPAN
#  Copyright (C) 2005-2007 by Industrial Technology Institute,
#                              Miyagi Prefectural Government, JAPAN
# 
#  �嵭����Ԥϡ��ʲ��� (1)��(4) �ξ�狼��Free Software Foundation 
#  �ˤ�äƸ�ɽ����Ƥ��� GNU General Public License �� Version 2 �˵�
#  �Ҥ���Ƥ���������������˸¤ꡤ�ܥ��եȥ��������ܥ��եȥ�����
#  ����Ѥ�����Τ�ޤࡥ�ʲ�Ʊ���ˤ���ѡ�ʣ�������ѡ������ۡʰʲ���
#  ���ѤȸƤ֡ˤ��뤳�Ȥ�̵���ǵ������롥
#  (1) �ܥ��եȥ������򥽡��������ɤη������Ѥ�����ˤϡ��嵭������
#      ��ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ��꤬�����Τޤޤη��ǥ���
#      ����������˴ޤޤ�Ƥ��뤳�ȡ�
#  (2) �ܥ��եȥ������򡤥饤�֥������ʤɡ�¾�Υ��եȥ�������ȯ�˻�
#      �ѤǤ�����Ǻ����ۤ�����ˤϡ������ۤ�ȼ���ɥ�����ȡ�����
#      �ԥޥ˥奢��ʤɡˤˡ��嵭�����ɽ�����������Ѿ�浪��Ӳ���
#      ��̵�ݾڵ����Ǻܤ��뤳�ȡ�
#  (3) �ܥ��եȥ������򡤵�����Ȥ߹���ʤɡ�¾�Υ��եȥ�������ȯ�˻�
#      �ѤǤ��ʤ����Ǻ����ۤ�����ˤϡ����Τ����줫�ξ�����������
#      �ȡ�
#    (a) �����ۤ�ȼ���ɥ�����ȡ����Ѽԥޥ˥奢��ʤɡˤˡ��嵭����
#        �ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ����Ǻܤ��뤳�ȡ�
#    (b) �����ۤη��֤��̤�������ˡ�ˤ�äơ�TOPPERS�ץ������Ȥ�
#        ��𤹤뤳�ȡ�
#  (4) �ܥ��եȥ����������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������뤤���ʤ�»
#      ������⡤�嵭����Ԥ����TOPPERS�ץ������Ȥ����դ��뤳�ȡ�
# 
#  �ܥ��եȥ������ϡ�̵�ݾڤ��󶡤���Ƥ����ΤǤ��롥�嵭����Ԥ�
#  ���TOPPERS�ץ������Ȥϡ��ܥ��եȥ������˴ؤ��ơ�����Ŭ�Ѳ�ǽ����
#  �ޤ�ơ������ʤ��ݾڤ�Ԥ�ʤ����ޤ����ܥ��եȥ����������Ѥˤ��ľ
#  ��Ū�ޤ��ϴ���Ū�������������ʤ�»���˴ؤ��Ƥ⡤������Ǥ�����ʤ���
# 

#����������
#  ����jsp/kernel�ˤ��륽���������ɤ�API��˥��ԡ����롣
#  �����ʴؿ�ñ�̤ǥ�󥯤Ǥ���褦�ˤ����
#  �������ԡ�����ݤˡ��ե�������Ƭ��#define __tskini�ʤɤΥޥ���������ɲä��롣
#  ��
#  �Ȥ���
#  ����perl copy_kernel_source.pl src_path dst_path
#  ����������
#  ��������src_path��jsp/kernel�ؤ����Хѥ�
#  ��������dst_path���ե�����Υ��ԡ���ؤ����Хѥ�


$src_path = $ARGV[0];
$dst_path = $ARGV[1];

# ���ˤʤ륽�����ե�����̾���ɲä���ޥ���̾�����
%hash_array = (
 "task.c"
	=> [qw(tskini tsksched tskrun tsknrun tskdmt tskact tskext tskpri tskrot tsktex)],
 "wait.c"
	=> [qw(waimake waicmp waitmo waitmook waican wairel wobjwai wobjwaitmo wobjpri)],
 "time_event.c"
	=> [qw(tmeini tmeup tmedown tmeins tmedel isig_tim)],
 "syslog.c"
	=> [qw(logini vwri_log vrea_log vmsk_log logter)],
 "task_manage.c"
	=> [qw(act_tsk iact_tsk can_act ext_tsk ter_tsk chg_pri get_pri)],
 "task_sync.c"
	=> [qw(slp_tsk tslp_tsk wup_tsk iwup_tsk can_wup rel_wai irel_wai sus_tsk rsm_tsk frsm_tsk dly_tsk)],
 "task_except.c"
	=> [qw(ras_tex iras_tex dis_tex ena_tex sns_tex)],
 "semaphore.c"
	=> [qw(semini sig_sem isig_sem wai_sem pol_sem twai_sem)],
 "eventflag.c"
	=> [qw(flgini flgcnd set_flg iset_flg clr_flg wai_flg pol_flg twai_flg)],
 "dataqueue.c"
	=> [qw(dtqini dtqenq dtqfenq dtqdeq dtqsnd dtqrcv snd_dtq psnd_dtq ipsnd_dtq tsnd_dtq fsnd_dtq ifsnd_dtq rcv_dtq prcv_dtq trcv_dtq)],
 "mailbox.c"
	=> [qw(mbxini snd_mbx rcv_mbx prcv_mbx trcv_mbx)],
 "mempfix.c"
	=> [qw(mpfini mpfget get_mpf pget_mpf tget_mpf rel_mpf)],
 "time_manage.c"
	=> [qw(set_tim get_tim vxget_tim)],
 "cyclic.c"
	=> [qw(cycini cycenq sta_cyc stp_cyc cyccal)],
 "sys_manage.c"
	=> [qw(rot_rdq irot_rdq get_tid iget_tid loc_cpu iloc_cpu unl_cpu iunl_cpu dis_dsp ena_dsp sns_ctx sns_loc sns_dsp sns_dpn vsns_ini)],
 "interrupt.c"
	=> [qw(inhini)],
 "exception.c"
	=> [qw(excini vxsns_ctx vxsns_loc vxsns_dsp vxsns_dpn vxsns_tex)]
);

#
#���ᥤ��ν���
#
foreach $file (keys(%hash_array)) {
	@array = @{$hash_array{$file}};
	foreach $api (@array) {
		&copy_file($file, $api);
	}
}


#
#����1���������ˤʤ륽���������ɤΥե�����̾�ʥѥ���ޤޤ���
#����2��������拾��ѥ����ѤΥޥ���������ɲä���API���ؿ�̾
#�����������������Ϥ���ե�����̾���ͤƤ��롣
#
sub copy_file {
	my($filename, $api) = @_;
	open(OUTFILE, ">$dst_path/$api.c") || die "Cannot open $dst_path/$api.c";
	
	# API��Υޥ���������ɲ�
	print OUTFILE "#define __$api\n";
	
	# jsp/kernel����ե�����򥳥ԡ�
	open(INFILE, "$src_path/$filename") || die "Cannot open $src_path/$filename";
	while ($line = <INFILE>) {
		print OUTFILE $line;
	}
	
	close(INFILE);
	close(OUTFILE);
}
