VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "mscomctl.ocx"
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "COMDLG32.OCX"
Begin VB.Form FrmCompile 
   BorderStyle     =   1  'Fest Einfach
   Caption         =   "Create Output Media..."
   ClientHeight    =   3855
   ClientLeft      =   45
   ClientTop       =   435
   ClientWidth     =   5595
   Icon            =   "FrmCompile.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   3855
   ScaleWidth      =   5595
   StartUpPosition =   1  'Fenstermitte
   Begin VB.CommandButton CmdCompile 
      Caption         =   "Start Compile"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   570
      Left            =   105
      TabIndex        =   4
      Top             =   3165
      Width           =   5460
   End
   Begin VB.Frame FrmFiles 
      Caption         =   "Output File"
      Height          =   780
      Left            =   120
      TabIndex        =   1
      Top             =   105
      Width           =   5415
      Begin VB.CommandButton CmdBrowse 
         Caption         =   "Browse...."
         Height          =   315
         Left            =   3915
         TabIndex        =   3
         Top             =   300
         Width           =   1395
      End
      Begin VB.TextBox TxtFile 
         Height          =   285
         Left            =   150
         TabIndex        =   2
         Top             =   315
         Width           =   3600
      End
   End
   Begin VB.Frame FrmProgress 
      Caption         =   "Compilation Progress"
      Height          =   1365
      Left            =   105
      TabIndex        =   8
      Top             =   1710
      Width           =   5415
      Begin VB.Timer TimerProgress 
         Enabled         =   0   'False
         Interval        =   1000
         Left            =   4785
         Top             =   840
      End
      Begin MSComctlLib.ProgressBar ProgressBar 
         Height          =   270
         Left            =   1890
         TabIndex        =   9
         Top             =   315
         Width           =   3405
         _ExtentX        =   6006
         _ExtentY        =   476
         _Version        =   393216
         BorderStyle     =   1
         Appearance      =   0
         Scrolling       =   1
      End
      Begin VB.Label LabTimeElapsed 
         AutoSize        =   -1  'True
         Caption         =   "00:00"
         Height          =   195
         Left            =   1245
         TabIndex        =   17
         Top             =   690
         Width           =   405
      End
      Begin VB.Label Label7 
         Alignment       =   1  'Rechts
         AutoSize        =   -1  'True
         Caption         =   "Time Elapsed:"
         Height          =   195
         Left            =   180
         TabIndex        =   16
         Top             =   690
         Width           =   1005
      End
      Begin VB.Label LabelTimes 
         AutoSize        =   -1  'True
         Caption         =   "0"
         Height          =   195
         Left            =   4140
         TabIndex        =   15
         Top             =   705
         Width           =   90
      End
      Begin VB.Label LabProgress 
         AutoSize        =   -1  'True
         Caption         =   "0%"
         Height          =   195
         Left            =   1260
         TabIndex        =   14
         Top             =   360
         Width           =   210
      End
      Begin VB.Label Label4 
         Alignment       =   1  'Rechts
         AutoSize        =   -1  'True
         Caption         =   "Progress:"
         Height          =   195
         Left            =   510
         TabIndex        =   13
         Top             =   345
         Width           =   660
      End
      Begin VB.Label Label3 
         Alignment       =   1  'Rechts
         AutoSize        =   -1  'True
         Caption         =   "Media Times:"
         Height          =   195
         Left            =   3120
         TabIndex        =   12
         Top             =   705
         Width           =   945
      End
      Begin VB.Label LabStatus 
         Caption         =   "Idle"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   225
         Left            =   1275
         TabIndex        =   11
         Top             =   1035
         Width           =   3990
      End
      Begin VB.Label Label1 
         Alignment       =   1  'Rechts
         Caption         =   "Encode Status:"
         Height          =   165
         Left            =   45
         TabIndex        =   10
         Top             =   1035
         Width           =   1155
      End
   End
   Begin VB.Frame FrmFormat 
      Caption         =   "Output MPEG Format"
      Height          =   720
      Left            =   105
      TabIndex        =   0
      Top             =   930
      Width           =   5415
      Begin MSComDlg.CommonDialog CommonDialog 
         Left            =   4695
         Top             =   165
         _ExtentX        =   847
         _ExtentY        =   847
         _Version        =   393216
      End
      Begin VB.OptionButton OptNTSC 
         Alignment       =   1  'Rechts ausgerichtet
         Appearance      =   0  '2D
         Caption         =   "NTSC"
         ForeColor       =   &H80000008&
         Height          =   195
         Left            =   4515
         TabIndex        =   7
         Top             =   360
         Width           =   735
      End
      Begin VB.OptionButton OptPal 
         Alignment       =   1  'Rechts ausgerichtet
         Appearance      =   0  '2D
         Caption         =   "PAL"
         ForeColor       =   &H80000008&
         Height          =   210
         Left            =   3840
         TabIndex        =   6
         Top             =   360
         Value           =   -1  'True
         Width           =   600
      End
      Begin VB.ComboBox CmbOutput 
         Height          =   315
         ItemData        =   "FrmCompile.frx":038A
         Left            =   150
         List            =   "FrmCompile.frx":0397
         Style           =   2  'Dropdown-Liste
         TabIndex        =   5
         Top             =   300
         Width           =   3660
      End
   End
End
Attribute VB_Name = "FrmCompile"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Dim m_Elapsed As Long

Private Sub CmdBrowse_Click()
    Dim sPattern As String
    Dim startStrg As String
    Dim sFilename As String
    Dim sFileDir As String
    Dim c As Integer

    sPattern = "MPEG video files|*.mpg;*.mpeg|" & _
                   "All Files (*.*)|*.*"
    
    CommonDialog.Flags = cdlOFNHideReadOnly Or cdlOFNExplorer Or cdlOFNNoChangeDir
    CommonDialog.MaxFileSize = 4096
    CommonDialog.Filter = sPattern
    CommonDialog.FileName = TxtFile.Text
    
    CommonDialog.ShowSave
    
    If CommonDialog.FileName > "" Then
        TxtFile.Text = CommonDialog.FileName
    End If
End Sub

Sub ConversionComplete()

    LabStatus.Caption = "Conversion Complete"
    TimerProgress.Enabled = False
    TxtFile.Enabled = True
    CmdBrowse.Enabled = True
    CmdCompile.Caption = "Start Compile"
    
    ShowStat
    LabProgress.Caption = "100%"
    
End Sub

Private Sub CmdCompile_Click()

    If CmdCompile.Caption = "Stop Compile" Then
        FrmMain.VideoEditor.Stop
    Else
    
        Dim format As Long
        
        Select Case CmbOutput.ListIndex
        Case 0
            format = IIf(OptPal.Value = True, 1, 5)
        Case 1
            format = IIf(OptPal.Value = True, 3, 6)
        Case 2
            format = IIf(OptPal.Value = True, 4, 7)
        End Select
        
        FrmMain.VideoEditor.CurrentClip = FrmMain.m_clip
        
        TxtFile.Enabled = False
        CmdBrowse.Enabled = False
        LabStatus.Caption = "Initializing compile..."
        TimerProgress.Enabled = True
        CmdCompile.Caption = "Stop Compile"
        m_Elapsed = 0
        
        DoEvents
        Me.Refresh
        DoEvents
        
        If (FrmMain.VideoEditor.CompileToFile(TxtFile.Text, format) = False) Then
            ConversionComplete
            MsgBox "The conversion failed!", vbInformation
        Else
            
        End If
    End If
    
End Sub

Private Sub Form_Load()
    TxtFile.Text = App.Path & "\output.mpg"
    CmbOutput.ListIndex = 0
End Sub

Private Sub TimerProgress_Timer()
    If FrmMain.VideoEditor.Duration > 0 Then
        ShowStat
    End If
End Sub

Sub ShowStat()
    On Error Resume Next
    ProgressBar.Max = FrmMain.VideoEditor.Duration
    ProgressBar.Value = FrmMain.VideoEditor.Progress
    LabelTimes.Caption = FormatTime(FrmMain.VideoEditor.Progress) & " of " & FormatTime(FrmMain.VideoEditor.Duration)
    LabProgress.Caption = Round((FrmMain.VideoEditor.Progress / FrmMain.VideoEditor.Duration) * 100, 1) & "%"
    m_Elapsed = m_Elapsed + 1
    LabTimeElapsed.Caption = FormatTime(CDbl(m_Elapsed))
End Sub
