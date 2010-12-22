VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Begin VB.Form FrmPreview 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Project Preview"
   ClientHeight    =   4365
   ClientLeft      =   45
   ClientTop       =   435
   ClientWidth     =   5865
   Icon            =   "FrmPreview.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   4365
   ScaleWidth      =   5865
   StartUpPosition =   1  'CenterOwner
   Begin MSComctlLib.Toolbar TBPreview 
      Align           =   2  'Align Bottom
      Height          =   360
      Left            =   0
      TabIndex        =   1
      Top             =   4005
      Width           =   5865
      _ExtentX        =   10345
      _ExtentY        =   635
      ButtonWidth     =   2381
      ButtonHeight    =   582
      Appearance      =   1
      Style           =   1
      TextAlignment   =   1
      ImageList       =   "ImageList1"
      _Version        =   393216
      BeginProperty Buttons {66833FE8-8583-11D1-B16A-00C0F0283628} 
         NumButtons      =   2
         BeginProperty Button1 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Caption         =   "Stop Preview"
            ImageIndex      =   1
         EndProperty
         BeginProperty Button2 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Style           =   3
         EndProperty
      EndProperty
      BorderStyle     =   1
      Begin VB.PictureBox Picture1 
         Height          =   300
         Left            =   1455
         ScaleHeight     =   240
         ScaleWidth      =   4305
         TabIndex        =   2
         Top             =   15
         Width           =   4365
         Begin MSComctlLib.ProgressBar ProgressBar 
            Height          =   255
            Left            =   0
            TabIndex        =   3
            Top             =   0
            Width           =   4320
            _ExtentX        =   7620
            _ExtentY        =   450
            _Version        =   393216
            Appearance      =   0
            Scrolling       =   1
         End
      End
   End
   Begin VB.PictureBox PicScreen 
      Appearance      =   0  'Flat
      BackColor       =   &H00000000&
      ForeColor       =   &H80000008&
      Height          =   3975
      Left            =   15
      ScaleHeight     =   263
      ScaleMode       =   3  'Pixel
      ScaleWidth      =   386
      TabIndex        =   0
      Top             =   15
      Width           =   5820
      Begin VB.Timer TimerProgress 
         Enabled         =   0   'False
         Interval        =   1000
         Left            =   3975
         Top             =   2580
      End
      Begin MSComctlLib.ImageList ImageList1 
         Left            =   2805
         Top             =   2685
         _ExtentX        =   1005
         _ExtentY        =   1005
         BackColor       =   -2147483643
         ImageWidth      =   16
         ImageHeight     =   16
         MaskColor       =   16777215
         _Version        =   393216
         BeginProperty Images {2C247F25-8591-11D1-B16A-00C0F0283628} 
            NumListImages   =   1
            BeginProperty ListImage1 {2C247F27-8591-11D1-B16A-00C0F0283628} 
               Picture         =   "FrmPreview.frx":014A
               Key             =   ""
            EndProperty
         EndProperty
      End
   End
End
Attribute VB_Name = "FrmPreview"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub Form_Unload(Cancel As Integer)
    FrmMain.VideoEditor.Stop
End Sub

Private Sub TBPreview_ButtonClick(ByVal Button As MSComctlLib.Button)
    FrmMain.VideoEditor.Stop
End Sub

Private Sub TimerProgress_Timer()
    On Error Resume Next
    ProgressBar.Max = FrmMain.VideoEditor.Duration
    ProgressBar.Value = FrmMain.VideoEditor.Progress
End Sub

Public Sub ConversionComplete()
    TimerProgress.Enabled = False
    TimerProgress_Timer
End Sub
