VERSION 5.00
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "COMDLG32.OCX"
Object = "{F7AFF85C-AC68-44F5-AE03-1896B27E423E}#1.0#0"; "WMVCreator.dll"
Begin VB.Form FrmMain 
   Caption         =   "Essien QuickConvert WMV"
   ClientHeight    =   5775
   ClientLeft      =   60
   ClientTop       =   450
   ClientWidth     =   5745
   Icon            =   "Form1.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   5775
   ScaleWidth      =   5745
   StartUpPosition =   3  'Windows Default
   Begin VB.Timer TimerProgress 
      Enabled         =   0   'False
      Interval        =   1000
      Left            =   5970
      Top             =   3630
   End
   Begin VB.CommandButton BtnStartConversion 
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
      Height          =   405
      Left            =   3900
      TabIndex        =   10
      Top             =   5160
      Width           =   1725
   End
   Begin VB.Frame Frame1 
      Caption         =   "Output Parameters"
      Height          =   2025
      Left            =   225
      TabIndex        =   9
      Top             =   1620
      Width           =   5385
      Begin VB.ComboBox CCmbVideoFramerate 
         Height          =   315
         Left            =   4020
         Style           =   1  'Simple Combo
         TabIndex        =   21
         Top             =   1560
         Width           =   1125
      End
      Begin VB.ComboBox CmbVidDim 
         Height          =   315
         Left            =   1440
         Style           =   1  'Simple Combo
         TabIndex        =   19
         Top             =   1575
         Width           =   1140
      End
      Begin VB.ComboBox CmbAudioCodecs 
         Height          =   315
         Left            =   1425
         Style           =   2  'Dropdown List
         TabIndex        =   17
         Top             =   1185
         Width           =   3735
      End
      Begin VB.ComboBox CmbVideoCodecs 
         Height          =   315
         Left            =   1440
         Style           =   2  'Dropdown List
         TabIndex        =   15
         Top             =   765
         Width           =   3705
      End
      Begin VB.ComboBox CmbProfiles 
         Height          =   315
         Left            =   825
         Style           =   2  'Dropdown List
         TabIndex        =   13
         Top             =   315
         Width           =   4320
      End
      Begin VB.Label Label9 
         Alignment       =   1  'Right Justify
         Caption         =   "Video Framerate:"
         Height          =   240
         Left            =   2730
         TabIndex        =   22
         Top             =   1605
         Width           =   1215
      End
      Begin VB.Label Label8 
         Alignment       =   1  'Right Justify
         Caption         =   "Dimensions:"
         Height          =   240
         Left            =   255
         TabIndex        =   20
         Top             =   1635
         Width           =   1095
      End
      Begin VB.Label Label17 
         Alignment       =   1  'Right Justify
         Caption         =   "Audio Codec:"
         Height          =   240
         Left            =   285
         TabIndex        =   18
         Top             =   1215
         Width           =   1020
      End
      Begin VB.Label Label5 
         Alignment       =   1  'Right Justify
         Caption         =   "Video Codec:"
         Height          =   240
         Left            =   240
         TabIndex        =   16
         Top             =   795
         Width           =   1050
      End
      Begin VB.Label Label3 
         Alignment       =   1  'Right Justify
         Caption         =   "Profiles:"
         BeginProperty Font 
            Name            =   "Tahoma"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   300
         Left            =   105
         TabIndex        =   14
         Top             =   375
         Width           =   675
      End
   End
   Begin VB.Frame Frame3 
      Caption         =   "Conversion"
      Height          =   1215
      Left            =   180
      TabIndex        =   6
      Top             =   3840
      Width           =   5460
      Begin VB.Label Label7 
         Alignment       =   1  'Right Justify
         Caption         =   "Status:"
         Height          =   165
         Left            =   90
         TabIndex        =   12
         Top             =   855
         Width           =   675
      End
      Begin VB.Label LabelStatus 
         Caption         =   "---"
         Height          =   225
         Left            =   855
         TabIndex        =   11
         Top             =   855
         Width           =   4440
      End
      Begin VB.Shape ShapeHilite 
         BackColor       =   &H000080FF&
         BackStyle       =   1  'Opaque
         BorderStyle     =   0  'Transparent
         Height          =   30
         Left            =   930
         Tag             =   "1635"
         Top             =   450
         Width           =   4395
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
         Left            =   2295
         TabIndex        =   8
         Top             =   450
         Width           =   1575
      End
      Begin VB.Shape Shape1 
         Height          =   255
         Left            =   870
         Top             =   405
         Width           =   4515
      End
      Begin VB.Label Label4 
         Alignment       =   1  'Right Justify
         Caption         =   "Progress:"
         Height          =   225
         Left            =   75
         TabIndex        =   7
         Top             =   420
         Width           =   705
      End
      Begin VB.Shape ShapeProgress 
         BackColor       =   &H000040C0&
         BackStyle       =   1  'Opaque
         Height          =   195
         Left            =   915
         Tag             =   "4425"
         Top             =   435
         Width           =   4425
      End
   End
   Begin VB.TextBox TxtTarget 
      Height          =   300
      Left            =   510
      TabIndex        =   3
      Top             =   1005
      Width           =   3525
   End
   Begin VB.TextBox TxtSource 
      Height          =   300
      Left            =   525
      TabIndex        =   2
      Top             =   360
      Width           =   3525
   End
   Begin VB.CommandButton CmdBrowseSource 
      Caption         =   "Browse..."
      Height          =   330
      Left            =   4290
      TabIndex        =   1
      Top             =   345
      Width           =   1200
   End
   Begin VB.CommandButton CmdBrowseTarget 
      Caption         =   "Browse..."
      Height          =   330
      Left            =   4290
      TabIndex        =   0
      Top             =   990
      Width           =   1215
   End
   Begin MSComDlg.CommonDialog CommonDialog 
      Left            =   5910
      Top             =   2790
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
   End
   Begin WMVCreatorLibCtl.WMVCreator WMVCreator 
      Left            =   6255
      OleObjectBlob   =   "Form1.frx":038A
      Top             =   4425
   End
   Begin VB.Image Image2 
      Height          =   240
      Left            =   180
      Picture         =   "Form1.frx":03AE
      Top             =   1020
      Width           =   240
   End
   Begin VB.Image Image1 
      Height          =   240
      Left            =   180
      Picture         =   "Form1.frx":0938
      Top             =   390
      Width           =   240
   End
   Begin VB.Label Label2 
      Caption         =   "Please select a target file:"
      Height          =   240
      Left            =   90
      TabIndex        =   5
      Top             =   750
      Width           =   2505
   End
   Begin VB.Label Label1 
      Caption         =   "Please select a source file:"
      Height          =   165
      Left            =   105
      TabIndex        =   4
      Top             =   105
      Width           =   2505
   End
End
Attribute VB_Name = "FrmMain"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
' WMV Creator sample. Sample that shows how to use the WMVCreator ActiveX control
' from the visual basic enviroment. Programmed by Mark Essien - mark@essien.de
' (c) 2005 Essien Research & Development. http://www.essien.de. All right reserved
Option Explicit

Dim arrVideoCodecs As New Collection
Dim arrAudioCodecs As New Collection

Private Sub BtnStartConversion_Click()
    If (BtnStartConversion.Caption = "Stop Conversion") Then
        WMVCreator.StopConversion
    Else
        BtnStartConversion.Caption = "Stop Conversion"
        
        ' Start the conversion
        TimerProgress.Enabled = True
        WMVCreator.InputFile = TxtSource.Text
        WMVCreator.OutputFile = TxtTarget.Text
        
        LabelStatus.Caption = "Initializing Conversion..."
        DoEvents
        
        Dim profile As WMVProfile
        Set profile = WMVCreator.SystemProfile(CmbProfiles.ListIndex)
        profile.VideoCodec = arrVideoCodecs.Item(CmbVideoCodecs.ListIndex + 1)
        profile.AudioCodec = arrAudioCodecs.Item(CmbAudioCodecs.ListIndex + 1)
        Set WMVCreator.ConversionProfile = profile
        WMVCreator.StartConversion
    End If
End Sub

Private Sub CmbAudioCodecs_Click()
    Dim aCodec As WMVCodec
    Set aCodec = arrAudioCodecs(CmbAudioCodecs.ListIndex + 1)
    
    ' Sample code
'    If Not aCodec Is Nothing Then
'        CmbAudioPasses.Clear
'        Dim i As Integer
'        For i = 1 To aCodec.MaxPasses
'            CmbAudioPasses.AddItem Str(i)
'        Next i
'
'        CmbAudioPasses.ListIndex = CmbAudioPasses.ListCount - 1
'    End If
'
'    CmbAudioVBR.Clear
'    Dim bCBR1Pass As Boolean, bCBR2Pass As Boolean
'    Dim bVBR1Pass As Boolean, bVBR2Pass As Boolean, n As Long
'    Call aCodec.SupportedVBRModes(bCBR1Pass, bCBR2Pass, bVBR1Pass, bVBR2Pass, n)
'
'    If bCBR1Pass Then CmbAudioVBR.AddItem "CBR 1-Pass"
'    If bCBR2Pass Then CmbAudioVBR.AddItem "CBR 2-Pass"
'    If bVBR1Pass Then CmbAudioVBR.AddItem "VBR 1-Pass"
'    If bVBR2Pass Then CmbAudioVBR.AddItem "VBR 2-Pass"
'
'    CmbFormats.Clear
'    Dim k As Integer
'    For k = 0 To aCodec.FormatCount - 1
'        CmbFormats.AddItem aCodec.FormatName(k)
'    Next k
End Sub

Private Sub CmbProfiles_Click()
    LoadParamsFromProfile
End Sub

Private Function FindCodecIndex(strGuid As String, ByRef c As Collection) As Integer
    Dim i As Integer
    For i = 1 To c.Count
        If c.Item(i).CodecGuid = strGuid Then
            FindCodecIndex = i
            Exit Function
        End If
    Next i
End Function

Private Sub LoadParamsFromProfile()

    CmbVidDim.Text = WMVCreator.SystemProfile(CmbProfiles.ListIndex).StringEquivalent("dimensions")
    CCmbVideoFramerate.Text = WMVCreator.SystemProfile(CmbProfiles.ListIndex).Framerate
    
    Dim vCodec As WMVCodec
    Set vCodec = WMVCreator.SystemProfile(CmbProfiles.ListIndex).VideoCodec
    If Not vCodec Is Nothing Then
        CmbVideoCodecs.Enabled = True
        CmbVideoCodecs.ListIndex = FindCodecIndex(vCodec.CodecGuid, arrVideoCodecs) - 1
    Else
        CmbVideoCodecs.Enabled = False
    End If
    

    Dim aCodec As WMVCodec
    Set aCodec = WMVCreator.SystemProfile(CmbProfiles.ListIndex).AudioCodec
    If Not aCodec Is Nothing Then
        CmbAudioCodecs.Enabled = True
        CmbAudioCodecs.ListIndex = FindCodecIndex(aCodec.CodecGuid, arrAudioCodecs) - 1
    Else
        CmbAudioCodecs.Enabled = False
    End If

    ' Sample code on how to load retrive more properties about the profile
    
'    CCmbKeyframe.Text = WMVCreator.SysProfile(CmbProfiles.ListIndex).KeyFrameSpacing
'    CmbQuality.Text = WMVCreator.SysProfile(CmbProfiles.ListIndex).Quality
'    CmbVidBitrate.Text = WMVCreator.SysProfile(CmbProfiles.ListIndex).VideoBitrate
'    CmbAudioBitrate.Text = WMVCreator.SysProfile(CmbProfiles.ListIndex).AudioBitrate
'    TextDescription.Text = WMVCreator.SysProfile(CmbProfiles.ListIndex).ProfileDescription
'    Dim bAudio As Boolean: bAudio = WMVCreator.SysProfile(CmbProfiles.ListIndex).HasAudioStream
'    Dim bVideo As Boolean: bVideo = WMVCreator.SysProfile(CmbProfiles.ListIndex).HasVideoStream
'    CmbStreams.ListIndex = IIf(bAudio And bVideo, 2, IIf(bVideo, 1, 0))
'    CmbBitrate.Text = WMVCreator.SysProfile(CmbProfiles.ListIndex).Bitrate

End Sub

Private Sub CmbVideoCodecs_Click()
    Dim vCodec As WMVCodec
    Set vCodec = arrVideoCodecs(CmbVideoCodecs.ListIndex + 1)
    
    ' Get the allowed passes of the codecs
'    If Not vCodec Is Nothing Then
'        CmbPasses.Clear
'        Dim i As Integer
'        For i = 1 To vCodec.MaxPasses
'            CmbPasses.AddItem Str(i)
'        Next i
'
'        CmbPasses.ListIndex = CmbPasses.ListCount - 1
'    End If
'
'    CmbVBRMode.Clear
'    Dim bCBR1Pass As Boolean, bCBR2Pass As Boolean
'    Dim bVBR1Pass As Boolean, bVBR2Pass As Boolean, n As Long
'    Call vCodec.SupportedVBRModes(bCBR1Pass, bCBR2Pass, bVBR1Pass, bVBR2Pass, n)
'
'    If bCBR1Pass Then CmbVBRMode.AddItem "CBR 1-Pass"
'    If bCBR2Pass Then CmbVBRMode.AddItem "CBR 2-Pass"
'    If bVBR1Pass Then CmbVBRMode.AddItem "VBR 1-Pass"
'    If bVBR2Pass Then CmbVBRMode.AddItem "VBR 2-Pass"
End Sub

Private Sub CmdBrowseSource_Click()
    
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

Private Sub TimerProgress_Timer()
    'When converting, we use this to get the progress
    On Error Resume Next
    Dim nPercent As Double
    Dim nDuration As Double
    Dim nProgress As Double
    
    nDuration = WMVCreator.Duration
    nProgress = WMVCreator.Progress
    
    If (nDuration > 0) Then
        nPercent = (nProgress / nDuration) * 100
        If nPercent > 100 Then nPercent = 100
    Else
        nPercent = 0
    End If
    
    LabelStatus.Caption = Round(nProgress, 1) & "s of " & Round(nDuration, 1) & "s converted"
    LabelStatus.Caption = LabelStatus.Caption & "  (Encode Framerate: " & WMVCreator.EncodeFramerate & ")"
    LabelPercent.Caption = Str(Round(nPercent, 2)) & "%"
    
    Dim nMaxWidth As Integer
    nMaxWidth = Val(ShapeProgress.Tag)
    
    ShapeProgress.Width = (nPercent / 100) * nMaxWidth
    If (ShapeProgress.Width - 16) < 0 Then
        ShapeHilite.Width = 0
    Else
        ShapeHilite.Width = ShapeProgress.Width - 16
    End If
End Sub

Private Sub CmdBrowseTarget_Click()
    Dim sPattern As String
    sPattern = "WMV/ASF files (*.wmv;*,*.asf)|*.asf;*.wmv|" & _
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

Private Sub Form_Load()
    
    'Initialise our UI elements
    Screen.MousePointer = vbHourglass
    ShapeProgress.Width = 0
    ShapeHilite.Width = 0
    ShapeHilite.Left = ShapeProgress.Left + 10
    
    
    ' Show status that profiles are being loaded
    'CmbProfiles.Enabled = False
    LabelStatus.Caption = "Listing profiles, please wait...."
    
    'Show window, so user knows something is happening
    Me.Show
    DoEvents 'so window gets painted once
    
    ' Load codecs before loading profiles, so the codecs ca
    ' be properly mapped to the profiles
    
    Dim c As WMVCodec
    
    WMVCreator.LoadSystemCodecs
    
    Dim i As Integer
    For i = 0 To WMVCreator.VideoCodecCount - 1
        Set c = WMVCreator.VideoCodec(i)
        CmbVideoCodecs.AddItem c.CodecName
        arrVideoCodecs.Add c
    Next i
    
    For i = 0 To WMVCreator.AudioCodecCount - 1
        Set c = WMVCreator.AudioCodec(i)
        CmbAudioCodecs.AddItem c.CodecName
        arrAudioCodecs.Add c
    Next i
    
    
    'Load the profiles. This will block the application for
    'a while. If you do not call this, the profiles will not be
    'available
    
    WMVCreator.LoadSystemProfiles

    For i = 0 To WMVCreator.SystemProfileCount - 1
        CmbProfiles.AddItem WMVCreator.SystemProfile(i).ProfileName
    Next i
    
    
    'Profile listing complete. Set the mouse pointer to normal
    Screen.MousePointer = vbDefault
    LabelStatus.Caption = ""
    
End Sub

