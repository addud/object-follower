VERSION 5.00
Object = "{194B359F-594E-4EE4-A804-84723D1CF1C4}#1.0#0"; "ATLDevice.dll"
Begin VB.Form Form1 
   BorderStyle     =   3  '�Œ�_�C�A���O
   Caption         =   "Form1"
   ClientHeight    =   1140
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   3045
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   1140
   ScaleWidth      =   3045
   ShowInTaskbar   =   0   'False
   StartUpPosition =   3  'Windows �̊���l
   Begin ATLDEVICELibCtl.DeviceControl DeviceControl1 
      Height          =   375
      Left            =   2400
      OleObjectBlob   =   "Form1.frx":0000
      TabIndex        =   1
      Top             =   0
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label Label1 
      Alignment       =   2  '��������
      Caption         =   "Label1"
      Height          =   255
      Index           =   4
      Left            =   1920
      TabIndex        =   5
      Top             =   360
      Width           =   975
   End
   Begin VB.Label Label1 
      Alignment       =   2  '��������
      Caption         =   "Label1"
      Height          =   255
      Index           =   3
      Left            =   1560
      TabIndex        =   4
      Top             =   720
      Width           =   975
   End
   Begin VB.Label Label1 
      Alignment       =   2  '��������
      Caption         =   "Label1"
      Height          =   255
      Index           =   2
      Left            =   480
      TabIndex        =   3
      Top             =   720
      Width           =   975
   End
   Begin VB.Label Label1 
      Alignment       =   2  '��������
      Caption         =   "Label1"
      Height          =   255
      Index           =   1
      Left            =   0
      TabIndex        =   2
      Top             =   360
      Width           =   975
   End
   Begin VB.Label Label1 
      Alignment       =   2  '��������
      Caption         =   "Label1"
      Height          =   255
      Index           =   0
      Left            =   960
      TabIndex        =   0
      Top             =   0
      Width           =   975
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

'
'  TOPPERS/JSP Kernel
'      Toyohashi Open Platform for Embedded Real-Time Systems/
'      Just Standard Profile Kernel
' 
'  Copyright (C) 2000-2002 by Embedded and Real-Time Systems Laboratory
'                              Toyohashi Univ. of Technology, JAPAN
' 
'  ��L���쌠�҂́C�ȉ��� (1)�`(4) �̏������CFree Software Foundation 
'  �ɂ���Č��\����Ă��� GNU General Public License �� Version 2 �ɋL
'  �q����Ă�������𖞂����ꍇ�Ɍ���C�{�\�t�g�E�F�A�i�{�\�t�g�E�F�A
'  �����ς������̂��܂ށD�ȉ������j���g�p�E�����E���ρE�Ĕz�z�i�ȉ��C
'  ���p�ƌĂԁj���邱�Ƃ𖳏��ŋ�������D
'  (1) �{�\�t�g�E�F�A���\�[�X�R�[�h�̌`�ŗ��p����ꍇ�ɂ́C��L�̒���
'      ���\���C���̗��p��������щ��L�̖��ۏ؋K�肪�C���̂܂܂̌`�Ń\�[
'      �X�R�[�h���Ɋ܂܂�Ă��邱�ƁD
'  (2) �{�\�t�g�E�F�A���C���C�u�����`���ȂǁC���̃\�t�g�E�F�A�J���Ɏg
'      �p�ł���`�ōĔz�z����ꍇ�ɂ́C�Ĕz�z�ɔ����h�L�������g�i���p
'      �҃}�j���A���Ȃǁj�ɁC��L�̒��쌠�\���C���̗��p��������щ��L
'      �̖��ۏ؋K����f�ڂ��邱�ƁD
'  (3) �{�\�t�g�E�F�A���C�@��ɑg�ݍ��ނȂǁC���̃\�t�g�E�F�A�J���Ɏg
'      �p�ł��Ȃ��`�ōĔz�z����ꍇ�ɂ́C���̂����ꂩ�̏����𖞂�����
'      �ƁD
'    (a) �Ĕz�z�ɔ����h�L�������g�i���p�҃}�j���A���Ȃǁj�ɁC��L�̒�
'        �쌠�\���C���̗��p��������щ��L�̖��ۏ؋K����f�ڂ��邱�ƁD
'    (b) �Ĕz�z�̌`�Ԃ��C�ʂɒ�߂���@�ɂ���āCTOPPERS�v���W�F�N�g��
'        �񍐂��邱�ƁD
'  (4) �{�\�t�g�E�F�A�̗��p�ɂ�蒼�ړI�܂��͊ԐړI�ɐ����邢���Ȃ鑹
'      �Q������C��L���쌠�҂����TOPPERS�v���W�F�N�g��Ɛӂ��邱�ƁD
' 
'  �{�\�t�g�E�F�A�́C���ۏ؂Œ񋟂���Ă�����̂ł���D��L���쌠�҂�
'  ���TOPPERS�v���W�F�N�g�́C�{�\�t�g�E�F�A�Ɋւ��āC���̓K�p�\����
'  �܂߂āC�����Ȃ�ۏ؂��s��Ȃ��D�܂��C�{�\�t�g�E�F�A�̗��p�ɂ�蒼
'  �ړI�܂��͊ԐړI�ɐ����������Ȃ鑹�Q�Ɋւ��Ă��C���̐ӔC�𕉂�Ȃ��D
'
'  @(#) $Id: form1.frm,v 1.5 2004/09/09 03:40:51 honda Exp $
'

Private Sub SetLabelString(index As Integer, letter As String, color As ColorConstants)
    Label1(index) = letter
    Label1(index).ForeColor = color
End Sub

Private Sub DeviceControl1_OnKernelExit()
    Dim i As Integer
    
    For i = 0 To 4
        SetLabelString i, "�I��", vbBlue
    Next i
    
End Sub

Private Sub DeviceControl1_OnKernelStart()
    Dim i As Integer
    
    For i = 0 To 4
        SetLabelString i, "�擾�҂�", vbBlack
    Next i
End Sub

Private Sub DeviceControl1_OnWrite(ByVal address As Long, ByVal sz As Long)
    Dim i As Integer
    Dim work As Long
    work = DeviceControl1.Value
    i = work And &HF
        
    Select Case (work And &HF0)
    Case &H10
        SetLabelString i, "�擾�҂�", vbBlack
    Case &H20
        SetLabelString i, "�H��", vbRed
    Case &H40
        SetLabelString i, "�x�e", vbBlack
    End Select

End Sub

Private Sub Form_Load()
    Dim i As Integer
    
    For i = 0 To 4
        SetLabelString i, "�I��", vbBlue
    Next i
    
    DeviceControl1.Connect
    DeviceControl1.Map 100, 4
End Sub

Private Sub Form_Unload(Cancel As Integer)
    DeviceControl1.Close
End Sub
