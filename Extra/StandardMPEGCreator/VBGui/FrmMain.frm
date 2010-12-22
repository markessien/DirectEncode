VERSION 5.00
Object = "{37FAD0EE-EFE5-4A2F-ABDA-F595ECD72E02}#1.0#0"; "STANDA~1.DLL"
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "comdlg32.ocx"
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Begin VB.Form FrmMain 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Standard MPEG Encoder 6 Test Bench"
   ClientHeight    =   5985
   ClientLeft      =   45
   ClientTop       =   435
   ClientWidth     =   5850
   Icon            =   "FrmMain.frx":0000
   LinkTopic       =   "FrmMain"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   5985
   ScaleWidth      =   5850
   StartUpPosition =   3  'Windows Default
   Begin STANDARDMPEGCREATORLibCtl.MPEGConverter MPEGConverter 
      Height          =   975
      Left            =   4800
      OleObjectBlob   =   "FrmMain.frx":1042
      TabIndex        =   19
      Top             =   4080
      Width           =   975
   End
   Begin VB.CommandButton CmdFormat 
      Caption         =   "Format Info..."
      BeginProperty Font 
         Name            =   "Tahoma"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   330
      Left            =   4365
      TabIndex        =   18
      Top             =   3330
      Visible         =   0   'False
      Width           =   1215
   End
   Begin MSComctlLib.StatusBar StatusBar 
      Align           =   2  'Align Bottom
      Height          =   225
      Left            =   0
      TabIndex        =   17
      Top             =   5760
      Width           =   5850
      _ExtentX        =   10319
      _ExtentY        =   397
      Style           =   1
      _Version        =   393216
      BeginProperty Panels {8E3867A5-8586-11D1-B16A-00C0F0283628} 
         NumPanels       =   1
         BeginProperty Panel1 {8E3867AB-8586-11D1-B16A-00C0F0283628} 
         EndProperty
      EndProperty
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "Tahoma"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
   End
   Begin VB.Timer TimerProgress 
      Enabled         =   0   'False
      Interval        =   1000
      Left            =   2490
      Top             =   5145
   End
   Begin VB.CheckBox ChkShowPreview 
      Caption         =   "Enable Conversion Preview"
      BeginProperty Font 
         Name            =   "Tahoma"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   225
      Left            =   180
      TabIndex        =   15
      Top             =   5265
      Value           =   1  'Checked
      Width           =   2295
   End
   Begin VB.ComboBox CmbFormats 
      Height          =   315
      ItemData        =   "FrmMain.frx":1066
      Left            =   540
      List            =   "FrmMain.frx":10AC
      Style           =   2  'Dropdown List
      TabIndex        =   13
      Top             =   2925
      Width           =   3645
   End
   Begin VB.CommandButton CmdCustom 
      Caption         =   "Custom..."
      BeginProperty Font 
         Name            =   "Tahoma"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   330
      Left            =   4365
      TabIndex        =   12
      Top             =   2895
      Visible         =   0   'False
      Width           =   1215
   End
   Begin VB.CommandButton CmbStartConversion 
      Caption         =   "Start Conversion"
      BeginProperty Font 
         Name            =   "Tahoma"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   360
      Left            =   3825
      TabIndex        =   11
      Top             =   5160
      Width           =   1755
   End
   Begin VB.CommandButton CmdBrowseTarget 
      Caption         =   "Browse..."
      BeginProperty Font 
         Name            =   "Tahoma"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   330
      Left            =   4365
      TabIndex        =   10
      Top             =   2160
      Width           =   1215
   End
   Begin VB.CommandButton CmdBrowseSource 
      Caption         =   "Browse..."
      BeginProperty Font 
         Name            =   "Tahoma"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   330
      Left            =   4365
      TabIndex        =   9
      Top             =   1500
      Width           =   1215
   End
   Begin VB.TextBox TxtSource 
      Height          =   300
      Left            =   555
      TabIndex        =   4
      Text            =   "c:\test_in.mpg"
      Top             =   1530
      Width           =   3645
   End
   Begin VB.TextBox TxtTarget 
      Height          =   300
      Left            =   555
      TabIndex        =   3
      Text            =   "c:\test_out.mpg"
      Top             =   2175
      Width           =   3645
   End
   Begin VB.Frame Frame3 
      Caption         =   "Conversion"
      BeginProperty Font 
         Name            =   "Tahoma"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   1095
      Left            =   195
      TabIndex        =   0
      Top             =   3885
      Width           =   4395
      Begin VB.Label Label6 
         Alignment       =   1  'Right Justify
         Caption         =   "Status:"
         BeginProperty Font 
            Name            =   "Tahoma"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   165
         Left            =   120
         TabIndex        =   8
         Top             =   795
         Width           =   675
      End
      Begin VB.Label LabelStatus 
         Caption         =   "---"
         BeginProperty Font 
            Name            =   "Tahoma"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   195
         Left            =   930
         TabIndex        =   7
         Top             =   795
         Width           =   3210
      End
      Begin VB.Label Label4 
         Alignment       =   1  'Right Justify
         Caption         =   "Progress:"
         BeginProperty Font 
            Name            =   "Tahoma"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   195
         Left            =   105
         TabIndex        =   2
         Top             =   450
         Width           =   705
      End
      Begin VB.Shape Shape1 
         Height          =   255
         Left            =   870
         Top             =   405
         Width           =   3345
      End
      Begin VB.Label LabelPercent 
         Alignment       =   2  'Center
         BackStyle       =   0  'Transparent
         Caption         =   "0%"
         BeginProperty Font 
            Name            =   "Small Fonts"
            Size            =   6.75
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H00000000&
         Height          =   180
         Left            =   1620
         TabIndex        =   1
         Top             =   450
         Width           =   1575
      End
      Begin VB.Shape ShapeHilite 
         BackColor       =   &H000080FF&
         BackStyle       =   1  'Opaque
         BorderStyle     =   0  'Transparent
         Height          =   30
         Left            =   930
         Tag             =   "1635"
         Top             =   450
         Width           =   3240
      End
      Begin VB.Shape ShapeProgress 
         BackColor       =   &H000040C0&
         BackStyle       =   1  'Opaque
         Height          =   195
         Left            =   915
         Tag             =   "3255"
         Top             =   435
         Width           =   3255
      End
   End
   Begin MSComDlg.CommonDialog CommonDialog 
      Left            =   3210
      Top             =   5130
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
   End
   Begin VB.Image Image4 
      Appearance      =   0  'Flat
      Height          =   1140
      Left            =   720
      Picture         =   "FrmMain.frx":127B
      Top             =   45
      Width           =   3945
   End
   Begin VB.Label LabelDescription 
      Height          =   555
      Left            =   510
      TabIndex        =   16
      Top             =   3300
      Width           =   3675
   End
   Begin VB.Image Image3 
      Height          =   240
      Left            =   210
      Picture         =   "FrmMain.frx":1FC9
      Top             =   2940
      Width           =   240
   End
   Begin VB.Label Label3 
      Caption         =   "Select the output format:"
      BeginProperty Font 
         Name            =   "Tahoma"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   210
      Left            =   120
      TabIndex        =   14
      Top             =   2655
      Width           =   1950
   End
   Begin VB.Label Label1 
      Caption         =   "Select a source file:"
      BeginProperty Font 
         Name            =   "Tahoma"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   180
      Left            =   135
      TabIndex        =   6
      Top             =   1275
      Width           =   2505
   End
   Begin VB.Label Label2 
      Caption         =   "Select a target file:"
      BeginProperty Font 
         Name            =   "Tahoma"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Left            =   120
      TabIndex        =   5
      Top             =   1920
      Width           =   2505
   End
   Begin VB.Image Image1 
      Height          =   240
      Left            =   210
      Picture         =   "FrmMain.frx":2353
      Top             =   1560
      Width           =   240
   End
   Begin VB.Image Image2 
      Height          =   240
      Left            =   210
      Picture         =   "FrmMain.frx":28DD
      Top             =   2190
      Width           =   240
   End
   Begin VB.Shape Shape2 
      BackStyle       =   1  'Opaque
      BorderColor     =   &H00FFFFFF&
      Height          =   1140
      Left            =   -90
      Top             =   0
      Width           =   6570
   End
End
Attribute VB_Name = "FrmMain"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

' MPEGConverter sample application. Written by Mark Essien
' (c) 2008 Standard MPEG - Modern MPEG Encoding Solutions
' This sample shows how to transcode video to various MPEG formats

Private Sub CmbFormats_Click()
    'When the format is changed, we make the mpeg creator activex control switch to
    'the selected profile by calling the select format function
    SelectFormat
End Sub


Private Sub CmdFormat_Click()
    Load FrmInfo
    FrmInfo.Show 1, Me
End Sub

Private Sub Form_Load()
    
    'Make the progress bar nice
    ShapeProgress.width = 0
    ShapeHilite.width = 0

    'Select mpeg-1 as output format
    CmbFormats.ListIndex = 0
    CmbFormats_Click

    
End Sub

Private Sub SelectFormat()
    ' Get the appropriate output format. The loadpreset
    ' function is going to pre-configure the MPEGConverter
    ' with the settings neccesary for that particular format
    ' You can modify the MPEGConverter after loading the preset

    Select Case CmbFormats.ListIndex
    Case 0 ' Standard MPEG-1
        MPEGConverter.LoadPreset "mpeg1-standard"
    Case 1
        MPEGConverter.LoadPreset "mpeg1-vcd-ntsc"
    Case 2
        MPEGConverter.LoadPreset "mpeg1-vcd-pal"
    Case 3
        MPEGConverter.LoadPreset "mpeg2-standard"
    Case 4
        MPEGConverter.LoadPreset "dvb"
    Case 5
        MPEGConverter.LoadPreset "mpeg2-svcd-ntsc"
    Case 6
        MPEGConverter.LoadPreset "mpeg2-svcd-pal"
    Case 7
        MPEGConverter.LoadPreset "mpeg2-dvd-ntsc"
    Case 8
        MPEGConverter.LoadPreset "mpeg2-dvd-pal"
    Case 9
        MPEGConverter.LoadPreset "mpeg2-hd"
    Case 10
        MPEGConverter.LoadPreset "mpeg4-standard"
    Case 11
        MPEGConverter.LoadPreset "mpeg4-ipod"
    Case 12
        MPEGConverter.LoadPreset "mpeg4-ipod-nano"
    Case 13
        MPEGConverter.LoadPreset "mpeg4-iphone"
    Case 14
        MPEGConverter.LoadPreset "mpeg4-qt"
    Case 15
        MPEGConverter.LoadPreset "mpeg1-vcd-still-ntsc"
    Case 16
        MPEGConverter.LoadPreset "mpeg1-vcd-still-pal"
    Case 17
        MPEGConverter.LoadPreset "mpeg2-svcd-still-ntsc"
    Case 18
        MPEGConverter.LoadPreset "mpeg2-svcd-still-pal"
    Case 19
        MPEGConverter.LoadPreset "flv"
    Case 20
        MPEGConverter.LoadPreset "rm"
    Case 21
        ' The custom profile setting just means that whatever is
        ' currently in the MPEGConverter should be used.
    End Select
    
End Sub

Private Sub CmbStartConversion_Click()
    'Start or stop the conversion

    If (CmbStartConversion.Caption = "Abort Conversion") Then
        'Stop the conversion
        MPEGConverter.StopConversion
    Else
        'Start the conversion

        ' Specify the source and output file. These files are not validated
        ' till the conversion starts
        MPEGConverter.SourceFile = TxtSource.Text
        MPEGConverter.TargetFile = TxtTarget.Text

        SelectFormat

        'Enable the progress timer
        TimerProgress.Enabled = True
        CmbStartConversion.Caption = "Abort Conversion"

        'start the conversion
        MPEGConverter.StartConversion

    End If

End Sub


Private Sub CmdCustom_Click()
    Load FrmSettings
    Set FrmSettings.mMPEGCreator = Me.MPEGConverter
    FrmSettings.Show 1, Me
    
    If FrmSettings.mOKClicked = True Then
        CmbFormats.ListIndex = 12
    End If
    
    Unload FrmSettings
End Sub

Private Sub CmdBrowseSource_Click()
    'Browse for source file
    Dim sPattern As String
    sPattern = "All supported media files|*.mpg;*.mpeg;*.avi|" & _
               "AVI files (*.avi)|*.avi|" & _
               "MPEG files (*.mpeg; *.mpg)|*.mpg;*.mpeg|" & _
               "All Files (*.*)|*.*"

    CommonDialog.Filter = sPattern

    CommonDialog.FileName = ""

    Dim sFilename As String
    CommonDialog.ShowOpen
    sFilename = CommonDialog.FileName
    If (sFilename > "") Then
        TxtSource.Text = sFilename
    End If

End Sub

Private Sub CmdBrowseTarget_Click()
    'Browse for output file
    Dim sPattern As String
    sPattern = "MPEG files (*.mpg; *.mp4; *.flv; *.rm)|*.mpg;*.mp4;*.flv;*.rm|" & _
               "All Files (*.*)|*.*"

    CommonDialog.Filter = sPattern
    CommonDialog.FileName = ""

    Dim sFilename As String
    CommonDialog.ShowSave
    sFilename = CommonDialog.FileName
    If (sFilename > "") Then
        TxtTarget.Text = sFilename
    End If
End Sub

' --- MPEG Creator events
Private Sub MPEGConverter_AboutToRun()
    'At this point, the graph is completely built up, and the conversion
    'is about to start
    LabelStatus.Caption = "Converting..."
End Sub


Private Sub MPEGConverter_OnComplete()
    TimerProgress.Enabled = False
    TimerProgress_Timer
    CmbStartConversion.Caption = "Start Conversion"
End Sub

' ---- End MPEG Creator events

Private Sub TimerProgress_Timer()

    ' This function is fired once a second to indicate that
    ' the progress has increased. Our nifty toolbar is moved
    ' by a bit

   ' On Error Resume Next
    Dim nPercent As Double
    Dim nDuration As Double
    Dim nProgress As Double

    nDuration = MPEGConverter.Statistics.duration
    nProgress = MPEGConverter.Statistics.Progress

    If (nDuration > 0) Then
        nPercent = (nProgress / nDuration) * 100
    Else
        nPercent = 0
    End If

    LabelStatus.Caption = Round(nProgress, 1) & "s of " & Round(nDuration, 1) & "s converted"
    LabelPercent.Caption = str(Round(nPercent, 2)) & "%"

    Dim nMaxWidth As Integer
    nMaxWidth = Val(ShapeProgress.Tag)

    ShapeProgress.width = (nPercent / 100) * nMaxWidth
    ShapeHilite.width = ShapeProgress.width - 6

    StatusBar.SimpleText = "Frames Encoded: " & MPEGConverter.Statistics.FramesEncoded & _
                           " \ FPS: " & MPEGConverter.Statistics.EncodeFramerate & _
                           " \ Time Elapsed: " & MPEGConverter.Statistics.TimeElapsed & "secs"
End Sub

Private Sub ChkShowPreview_Click()
    MPEGConverter.ShowPreview = ChkShowPreview.Value
End Sub


