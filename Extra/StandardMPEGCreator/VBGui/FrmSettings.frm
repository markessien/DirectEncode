VERSION 5.00
Object = "{BDC217C8-ED16-11CD-956C-0000C04E4C0A}#1.1#0"; "TABCTL32.OCX"
Begin VB.Form FrmSettings 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "MPEG Settings"
   ClientHeight    =   7170
   ClientLeft      =   45
   ClientTop       =   435
   ClientWidth     =   6540
   Icon            =   "FrmSettings.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   7170
   ScaleWidth      =   6540
   StartUpPosition =   1  'CenterOwner
   Begin VB.Frame Frame4 
      Caption         =   "Load Preset"
      Height          =   645
      Left            =   210
      TabIndex        =   39
      Top             =   120
      Width           =   6120
      Begin VB.ComboBox CmbPreset 
         Height          =   315
         ItemData        =   "FrmSettings.frx":1042
         Left            =   75
         List            =   "FrmSettings.frx":106D
         TabIndex        =   40
         Top             =   225
         Width           =   5955
      End
   End
   Begin VB.CommandButton CmdOK 
      Caption         =   "OK"
      Height          =   480
      Left            =   3120
      TabIndex        =   18
      Top             =   6510
      Width           =   1530
   End
   Begin VB.CommandButton CmdCancel 
      Caption         =   "Cancel"
      Height          =   480
      Left            =   4830
      TabIndex        =   17
      Top             =   6495
      Width           =   1530
   End
   Begin TabDlg.SSTab SSTab1 
      Height          =   5445
      Left            =   195
      TabIndex        =   0
      Top             =   870
      Width           =   6150
      _ExtentX        =   10848
      _ExtentY        =   9604
      _Version        =   393216
      Style           =   1
      Tabs            =   4
      TabsPerRow      =   4
      TabHeight       =   520
      TabCaption(0)   =   "Video"
      TabPicture(0)   =   "FrmSettings.frx":1168
      Tab(0).ControlEnabled=   -1  'True
      Tab(0).Control(0)=   "Label1"
      Tab(0).Control(0).Enabled=   0   'False
      Tab(0).Control(1)=   "Label2"
      Tab(0).Control(1).Enabled=   0   'False
      Tab(0).Control(2)=   "Label3"
      Tab(0).Control(2).Enabled=   0   'False
      Tab(0).Control(3)=   "Label4"
      Tab(0).Control(3).Enabled=   0   'False
      Tab(0).Control(4)=   "Label5"
      Tab(0).Control(4).Enabled=   0   'False
      Tab(0).Control(5)=   "Label6"
      Tab(0).Control(5).Enabled=   0   'False
      Tab(0).Control(6)=   "Label7"
      Tab(0).Control(6).Enabled=   0   'False
      Tab(0).Control(7)=   "Label8"
      Tab(0).Control(7).Enabled=   0   'False
      Tab(0).Control(8)=   "Label11"
      Tab(0).Control(8).Enabled=   0   'False
      Tab(0).Control(9)=   "Label16"
      Tab(0).Control(9).Enabled=   0   'False
      Tab(0).Control(10)=   "Label22"
      Tab(0).Control(10).Enabled=   0   'False
      Tab(0).Control(11)=   "Line1"
      Tab(0).Control(11).Enabled=   0   'False
      Tab(0).Control(12)=   "Line2"
      Tab(0).Control(12).Enabled=   0   'False
      Tab(0).Control(13)=   "Line3"
      Tab(0).Control(13).Enabled=   0   'False
      Tab(0).Control(14)=   "Label13"
      Tab(0).Control(14).Enabled=   0   'False
      Tab(0).Control(15)=   "Label23"
      Tab(0).Control(15).Enabled=   0   'False
      Tab(0).Control(16)=   "Label24"
      Tab(0).Control(16).Enabled=   0   'False
      Tab(0).Control(17)=   "CmbVideoFormat"
      Tab(0).Control(17).Enabled=   0   'False
      Tab(0).Control(18)=   "CmbAspectRatio"
      Tab(0).Control(18).Enabled=   0   'False
      Tab(0).Control(19)=   "CmbFramerate"
      Tab(0).Control(19).Enabled=   0   'False
      Tab(0).Control(20)=   "CmbInterlace"
      Tab(0).Control(20).Enabled=   0   'False
      Tab(0).Control(21)=   "CmbRateControl"
      Tab(0).Control(21).Enabled=   0   'False
      Tab(0).Control(22)=   "CmbWidth"
      Tab(0).Control(22).Enabled=   0   'False
      Tab(0).Control(23)=   "CmbHeight"
      Tab(0).Control(23).Enabled=   0   'False
      Tab(0).Control(24)=   "TxtVBVBuffer"
      Tab(0).Control(24).Enabled=   0   'False
      Tab(0).Control(25)=   "CmbBitrate"
      Tab(0).Control(25).Enabled=   0   'False
      Tab(0).Control(26)=   "CmbBitrateMin"
      Tab(0).Control(26).Enabled=   0   'False
      Tab(0).Control(27)=   "CmbBitrateMax"
      Tab(0).Control(27).Enabled=   0   'False
      Tab(0).ControlCount=   28
      TabCaption(1)   =   "Audio"
      TabPicture(1)   =   "FrmSettings.frx":1184
      Tab(1).ControlEnabled=   0   'False
      Tab(1).Control(0)=   "Check5"
      Tab(1).Control(0).Enabled=   0   'False
      Tab(1).Control(1)=   "Check4"
      Tab(1).Control(1).Enabled=   0   'False
      Tab(1).Control(2)=   "Check3"
      Tab(1).Control(2).Enabled=   0   'False
      Tab(1).Control(3)=   "Check1"
      Tab(1).Control(3).Enabled=   0   'False
      Tab(1).Control(4)=   "CmbAudioBitrate"
      Tab(1).Control(4).Enabled=   0   'False
      Tab(1).Control(5)=   "CmbChannels"
      Tab(1).Control(5).Enabled=   0   'False
      Tab(1).Control(6)=   "CmbSamplingFreq"
      Tab(1).Control(6).Enabled=   0   'False
      Tab(1).Control(7)=   "CmbAudioFormat"
      Tab(1).Control(7).Enabled=   0   'False
      Tab(1).Control(8)=   "Line4"
      Tab(1).Control(8).Enabled=   0   'False
      Tab(1).Control(9)=   "Label10"
      Tab(1).Control(9).Enabled=   0   'False
      Tab(1).Control(10)=   "Label21"
      Tab(1).Control(10).Enabled=   0   'False
      Tab(1).Control(11)=   "Label20"
      Tab(1).Control(11).Enabled=   0   'False
      Tab(1).Control(12)=   "Label19"
      Tab(1).Control(12).Enabled=   0   'False
      Tab(1).Control(13)=   "Label18"
      Tab(1).Control(13).Enabled=   0   'False
      Tab(1).ControlCount=   14
      TabCaption(2)   =   "System"
      TabPicture(2)   =   "FrmSettings.frx":11A0
      Tab(2).ControlEnabled=   0   'False
      Tab(2).Control(0)=   "ChkMux"
      Tab(2).Control(0).Enabled=   0   'False
      Tab(2).Control(1)=   "CmbSystemsFormat"
      Tab(2).Control(1).Enabled=   0   'False
      Tab(2).Control(2)=   "Label17"
      Tab(2).Control(2).Enabled=   0   'False
      Tab(2).ControlCount=   3
      TabCaption(3)   =   "Advanced"
      TabPicture(3)   =   "FrmSettings.frx":11BC
      Tab(3).ControlEnabled=   0   'False
      Tab(3).Control(0)=   "Frame2"
      Tab(3).Control(0).Enabled=   0   'False
      Tab(3).Control(1)=   "Frame1"
      Tab(3).Control(1).Enabled=   0   'False
      Tab(3).ControlCount=   2
      Begin VB.Frame Frame2 
         Caption         =   "Encode Parameters"
         Height          =   1515
         Left            =   -74835
         TabIndex        =   51
         Top             =   2085
         Width           =   5820
         Begin VB.ComboBox CmbProfileLevel 
            Enabled         =   0   'False
            Height          =   315
            ItemData        =   "FrmSettings.frx":11D8
            Left            =   1875
            List            =   "FrmSettings.frx":11E2
            Style           =   2  'Dropdown List
            TabIndex        =   55
            Top             =   420
            Width           =   3660
         End
         Begin VB.ComboBox CmbMotionSearch 
            Enabled         =   0   'False
            Height          =   315
            ItemData        =   "FrmSettings.frx":121B
            Left            =   1860
            List            =   "FrmSettings.frx":122E
            Style           =   2  'Dropdown List
            TabIndex        =   53
            Top             =   915
            Width           =   3720
         End
         Begin VB.Label Label14 
            AutoSize        =   -1  'True
            Caption         =   "Motion Search:"
            Enabled         =   0   'False
            Height          =   195
            Left            =   255
            TabIndex        =   54
            Top             =   960
            Width           =   1080
         End
         Begin VB.Label Label25 
            Caption         =   "Profile && Level:"
            Enabled         =   0   'False
            Height          =   285
            Left            =   255
            TabIndex        =   52
            Top             =   510
            Width           =   1230
         End
      End
      Begin VB.ComboBox CmbBitrateMax 
         Height          =   315
         Left            =   3900
         TabIndex        =   49
         Text            =   "3000"
         Top             =   3697
         Width           =   1050
      End
      Begin VB.ComboBox CmbBitrateMin 
         Height          =   315
         Left            =   2145
         TabIndex        =   47
         Text            =   "0"
         Top             =   3697
         Width           =   1050
      End
      Begin VB.ComboBox CmbBitrate 
         Height          =   315
         ItemData        =   "FrmSettings.frx":1256
         Left            =   2145
         List            =   "FrmSettings.frx":1258
         TabIndex        =   46
         Text            =   "1140"
         Top             =   3206
         Width           =   2790
      End
      Begin VB.Frame Frame1 
         Caption         =   "GOP Settings"
         Height          =   1305
         Left            =   -74835
         TabIndex        =   41
         Top             =   495
         Width           =   5820
         Begin VB.CheckBox ChkClosedGOP 
            Caption         =   "Closed GOP"
            Enabled         =   0   'False
            Height          =   240
            Left            =   1770
            TabIndex        =   44
            Top             =   780
            Width           =   3930
         End
         Begin VB.TextBox TxtGOPStructure 
            Enabled         =   0   'False
            Height          =   315
            Left            =   1770
            TabIndex        =   43
            Top             =   345
            Width           =   2850
         End
         Begin VB.Label Label12 
            Caption         =   "GOP Structure:"
            Enabled         =   0   'False
            Height          =   210
            Left            =   135
            TabIndex        =   42
            Top             =   390
            Width           =   1245
         End
      End
      Begin VB.TextBox TxtVBVBuffer 
         Height          =   315
         Left            =   2145
         TabIndex        =   37
         Text            =   "0 (Automatic)"
         Top             =   4170
         Width           =   2775
      End
      Begin VB.CheckBox ChkMux 
         Caption         =   "Multiplex Audio and Video"
         Height          =   225
         Left            =   -72810
         TabIndex        =   35
         Top             =   1275
         Value           =   1  'Checked
         Width           =   3705
      End
      Begin VB.ComboBox CmbHeight 
         Height          =   315
         ItemData        =   "FrmSettings.frx":125A
         Left            =   3570
         List            =   "FrmSettings.frx":126D
         TabIndex        =   34
         Text            =   "240"
         Top             =   1215
         Width           =   1035
      End
      Begin VB.ComboBox CmbWidth 
         Height          =   315
         ItemData        =   "FrmSettings.frx":128A
         Left            =   2145
         List            =   "FrmSettings.frx":129D
         TabIndex        =   33
         Text            =   "320"
         Top             =   1230
         Width           =   1035
      End
      Begin VB.ComboBox CmbSystemsFormat 
         Height          =   315
         ItemData        =   "FrmSettings.frx":12BA
         Left            =   -72810
         List            =   "FrmSettings.frx":12D6
         Style           =   2  'Dropdown List
         TabIndex        =   32
         Top             =   660
         Width           =   3720
      End
      Begin VB.CheckBox Check5 
         Caption         =   "Original Flag"
         Height          =   210
         Left            =   -72810
         TabIndex        =   30
         Top             =   3180
         Width           =   1995
      End
      Begin VB.CheckBox Check4 
         Caption         =   "Copyright Flag"
         Height          =   210
         Left            =   -72810
         TabIndex        =   29
         Top             =   3630
         Width           =   1995
      End
      Begin VB.CheckBox Check3 
         Caption         =   "Private Flag"
         Height          =   210
         Left            =   -72810
         TabIndex        =   28
         Top             =   4065
         Width           =   1995
      End
      Begin VB.CheckBox Check1 
         Caption         =   "Error Protection"
         Height          =   210
         Left            =   -72810
         TabIndex        =   27
         Top             =   2775
         Width           =   1995
      End
      Begin VB.ComboBox CmbAudioBitrate 
         Height          =   315
         ItemData        =   "FrmSettings.frx":134A
         Left            =   -72810
         List            =   "FrmSettings.frx":135D
         TabIndex        =   22
         Text            =   "192"
         Top             =   2115
         Width           =   2685
      End
      Begin VB.ComboBox CmbChannels 
         Height          =   315
         ItemData        =   "FrmSettings.frx":1379
         Left            =   -72810
         List            =   "FrmSettings.frx":1383
         Style           =   2  'Dropdown List
         TabIndex        =   21
         Top             =   1620
         Width           =   3720
      End
      Begin VB.ComboBox CmbSamplingFreq 
         Height          =   315
         ItemData        =   "FrmSettings.frx":1395
         Left            =   -72810
         List            =   "FrmSettings.frx":13A2
         Style           =   2  'Dropdown List
         TabIndex        =   20
         Top             =   1140
         Width           =   3720
      End
      Begin VB.ComboBox CmbAudioFormat 
         Height          =   315
         ItemData        =   "FrmSettings.frx":13BB
         Left            =   -72810
         List            =   "FrmSettings.frx":13D1
         Style           =   2  'Dropdown List
         TabIndex        =   19
         Top             =   660
         Width           =   3720
      End
      Begin VB.ComboBox CmbRateControl 
         Height          =   315
         ItemData        =   "FrmSettings.frx":13F4
         Left            =   2145
         List            =   "FrmSettings.frx":1404
         Style           =   2  'Dropdown List
         TabIndex        =   16
         Top             =   2715
         Width           =   3720
      End
      Begin VB.ComboBox CmbInterlace 
         Enabled         =   0   'False
         Height          =   315
         ItemData        =   "FrmSettings.frx":1499
         Left            =   2145
         List            =   "FrmSettings.frx":14A9
         Style           =   2  'Dropdown List
         TabIndex        =   15
         Top             =   4785
         Width           =   3720
      End
      Begin VB.ComboBox CmbFramerate 
         Height          =   315
         ItemData        =   "FrmSettings.frx":14EB
         Left            =   2145
         List            =   "FrmSettings.frx":1507
         TabIndex        =   9
         Text            =   "25"
         Top             =   2085
         Width           =   3720
      End
      Begin VB.ComboBox CmbAspectRatio 
         Height          =   315
         ItemData        =   "FrmSettings.frx":1535
         Left            =   2145
         List            =   "FrmSettings.frx":1545
         Style           =   2  'Dropdown List
         TabIndex        =   6
         Top             =   1635
         Width           =   3720
      End
      Begin VB.ComboBox CmbVideoFormat 
         Height          =   315
         ItemData        =   "FrmSettings.frx":157D
         Left            =   2130
         List            =   "FrmSettings.frx":158A
         Style           =   2  'Dropdown List
         TabIndex        =   2
         Top             =   660
         Width           =   3720
      End
      Begin VB.Label Label24 
         Caption         =   "kbits/sec"
         Height          =   240
         Left            =   5055
         TabIndex        =   50
         Top             =   3735
         Width           =   720
      End
      Begin VB.Label Label23 
         Caption         =   "to"
         Height          =   225
         Left            =   3375
         TabIndex        =   48
         Top             =   3750
         Width           =   300
      End
      Begin VB.Label Label13 
         Caption         =   "Bitrate Range:"
         Height          =   195
         Left            =   330
         TabIndex        =   45
         Top             =   3741
         Width           =   1095
      End
      Begin VB.Line Line4 
         BorderColor     =   &H00808080&
         X1              =   -74715
         X2              =   -69165
         Y1              =   2610
         Y2              =   2610
      End
      Begin VB.Line Line3 
         BorderColor     =   &H00808080&
         X1              =   345
         X2              =   5895
         Y1              =   4635
         Y2              =   4635
      End
      Begin VB.Line Line2 
         BorderColor     =   &H00808080&
         X1              =   345
         X2              =   5895
         Y1              =   2520
         Y2              =   2520
      End
      Begin VB.Line Line1 
         BorderColor     =   &H00808080&
         X1              =   345
         X2              =   5895
         Y1              =   1110
         Y2              =   1110
      End
      Begin VB.Label Label10 
         Caption         =   "kbits/sec"
         Height          =   195
         Left            =   -69990
         TabIndex        =   38
         Top             =   2175
         Width           =   825
      End
      Begin VB.Label Label22 
         Caption         =   "kbits/sec"
         Height          =   240
         Left            =   5040
         TabIndex        =   36
         Top             =   3255
         Width           =   720
      End
      Begin VB.Label Label17 
         Caption         =   "Stream Type:"
         Height          =   300
         Left            =   -74670
         TabIndex        =   31
         Top             =   705
         Width           =   1395
      End
      Begin VB.Label Label21 
         AutoSize        =   -1  'True
         Caption         =   "Audio Stream Type:"
         Height          =   195
         Left            =   -74670
         TabIndex        =   26
         Top             =   705
         Width           =   1395
      End
      Begin VB.Label Label20 
         AutoSize        =   -1  'True
         Caption         =   "Bitrate:"
         Height          =   195
         Left            =   -74670
         TabIndex        =   25
         Top             =   2175
         Width           =   495
      End
      Begin VB.Label Label19 
         AutoSize        =   -1  'True
         Caption         =   "Channel Mode:"
         Height          =   195
         Left            =   -74670
         TabIndex        =   24
         Top             =   1680
         Width           =   1080
      End
      Begin VB.Label Label18 
         AutoSize        =   -1  'True
         Caption         =   "Sampling Frequency:"
         Height          =   195
         Left            =   -74670
         TabIndex        =   23
         Top             =   1185
         Width           =   1485
      End
      Begin VB.Label Label16 
         Caption         =   "pixels"
         Height          =   195
         Left            =   4710
         TabIndex        =   14
         Top             =   1245
         Width           =   855
      End
      Begin VB.Label Label11 
         AutoSize        =   -1  'True
         Caption         =   "Encode Mode:"
         Height          =   195
         Left            =   330
         TabIndex        =   12
         Top             =   4860
         Width           =   1050
      End
      Begin VB.Label Label8 
         AutoSize        =   -1  'True
         Caption         =   "VBV Buffer Size:"
         Height          =   195
         Left            =   330
         TabIndex        =   11
         Top             =   4200
         Width           =   1170
      End
      Begin VB.Label Label7 
         AutoSize        =   -1  'True
         Caption         =   "Target Bitrate:"
         Height          =   195
         Left            =   330
         TabIndex        =   10
         Top             =   3258
         Width           =   1005
      End
      Begin VB.Label Label6 
         AutoSize        =   -1  'True
         Caption         =   "Rate control mode:"
         Height          =   195
         Left            =   330
         TabIndex        =   8
         Top             =   2775
         Width           =   1350
      End
      Begin VB.Label Label5 
         AutoSize        =   -1  'True
         Caption         =   "Frame Rate:"
         Height          =   195
         Left            =   330
         TabIndex        =   7
         Top             =   2115
         Width           =   870
      End
      Begin VB.Label Label4 
         AutoSize        =   -1  'True
         Caption         =   "Aspect Ratio:"
         Height          =   195
         Left            =   330
         TabIndex        =   5
         Top             =   1680
         Width           =   960
      End
      Begin VB.Label Label3 
         Caption         =   "x"
         Height          =   195
         Left            =   3300
         TabIndex        =   4
         Top             =   1260
         Width           =   195
      End
      Begin VB.Label Label2 
         AutoSize        =   -1  'True
         Caption         =   "Size:"
         Height          =   195
         Left            =   330
         TabIndex        =   3
         Top             =   1275
         Width           =   345
      End
      Begin VB.Label Label1 
         AutoSize        =   -1  'True
         Caption         =   "Video Stream Type:"
         Height          =   195
         Left            =   330
         TabIndex        =   1
         Top             =   705
         Width           =   1395
      End
   End
   Begin VB.Label Label15 
      Caption         =   "YUV Format"
      Height          =   300
      Left            =   2100
      TabIndex        =   13
      Top             =   3210
      Width           =   1395
   End
End
Attribute VB_Name = "FrmSettings"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Public mMPEGCreator As MPEGConverter
Public mOKClicked As Boolean

' THIS FUNCIONALITY HAS NOT YET BEEN UPDATED FOR THE ENCODER V6
' PLEASE CHECK OUR SITE FOR UPDATES - http://www.standardmpeg.com

Public Sub ApplySettings()

    mMPEGCreator.MPEGVideoOutputFormat = CmbVideoFormat.ListIndex
    
    'Set the height, width and framerate of the output file
    'Set the height or width to 0 to use the source height or width
    mMPEGCreator.MPEGOutputWidth = CmbWidth.Text
    mMPEGCreator.MPEGOutputHeight = CmbHeight.Text
    
    mMPEGCreator.MPEGAspectRatio = CmbAspectRatio.ListIndex
    mMPEGCreator.MPEGOutputFramerate = CmbFramerate.Text
    mMPEGCreator.MPEGBitrateMode = CmbRateControl.ListIndex
    mMPEGCreator.MPEGVideoBitrate = Val(CmbBitrate.Text) * 1000
    mMPEGCreator.MPEGVideoBitrateMin = Val(CmbBitrateMin.Text) * 1000
    mMPEGCreator.MPEGVideoBitrateMax = Val(CmbBitrateMax.Text) * 1000
    mMPEGCreator.AdvancedSettings.VBVBufferSize = TxtVBVBuffer.Text
    mMPEGCreator.AdvancedSettings.ProfileAndLevel = CmbProfileLevel.Text
    
    ' audio tab
    mMPEGCreator.MPEGAudioOutputFormat = CmbAudioFormat.ListIndex
    mMPEGCreator.MPEGAudioSampleRate = CmbSamplingFreq.Text
    mMPEGCreator.MPEGAudioChannels = CmbChannels.ListIndex + 1
    mMPEGCreator.MPEGAudioBitrate = CmbAudioBitrate.Text * 1000
    
    'Systems
    mMPEGCreator.MPEGSystemsOutputFormat = CmbSystemsFormat.ListIndex
    mMPEGCreator.AdvancedSettings.MultiplexStreams = ChkMux.Value
    
    'advanced
    mMPEGCreator.AdvancedSettings.MPEGGOPStructure = TxtGOPStructure.Text
    mMPEGCreator.AdvancedSettings.MPEGClosedGOP = ChkClosedGOP.Value
End Sub

Public Sub LoadSettings()
    'video tab
    CmbVideoFormat.ListIndex = mMPEGCreator.MPEGVideoOutputFormat
    CmbWidth.Text = mMPEGCreator.MPEGOutputWidth
    CmbHeight.Text = mMPEGCreator.MPEGOutputHeight
    CmbAspectRatio.ListIndex = mMPEGCreator.MPEGAspectRatio
    CmbFramerate.Text = mMPEGCreator.MPEGOutputFramerate
    CmbRateControl.ListIndex = mMPEGCreator.MPEGBitrateMode
    CmbBitrate.Text = mMPEGCreator.MPEGVideoBitrate / 1000
    CmbBitrateMin.Text = mMPEGCreator.MPEGVideoBitrateMin / 1000
    CmbBitrateMax.Text = mMPEGCreator.MPEGVideoBitrateMax / 1000
    TxtVBVBuffer.Text = mMPEGCreator.AdvancedSettings.VBVBufferSize
    'CmbProfileLevel.Text = mMPEGCreator.AdvancedSettings.ProfileAndLevel
    
    ' audio tab
    CmbAudioFormat.ListIndex = mMPEGCreator.MPEGAudioOutputFormat
    CmbSamplingFreq.Text = mMPEGCreator.MPEGAudioSampleRate
    CmbChannels.ListIndex = mMPEGCreator.MPEGAudioChannels - 1
    CmbAudioBitrate.Text = mMPEGCreator.MPEGAudioBitrate / 1000
    
    'Systems
    CmbSystemsFormat.ListIndex = mMPEGCreator.MPEGSystemsOutputFormat
    ChkMux.Value = IIf(mMPEGCreator.AdvancedSettings.MultiplexStreams, 1, 0)
    
    'Advanced
    TxtGOPStructure.Text = mMPEGCreator.AdvancedSettings.MPEGGOPStructure
    ChkClosedGOP.Value = mMPEGCreator.AdvancedSettings.MPEGClosedGOP
    
    CmbMotionSearch.ListIndex = 2
    CmbInterlace.ListIndex = 0
    CmbProfileLevel.ListIndex = 1
End Sub

Private Sub CmbPreset_Click()
    SelectFormat
    LoadSettings
End Sub

Private Sub SelectFormat()
    ' Get the appropriate output format. The loadpreset
    ' function is going to pre-configure the mpegcreator
    ' with the settings neccesary for that particular format
    ' You can modify the mpegcreator after loading the preset
    Select Case CmbPreset.ListIndex
    Case 0 ' Standard MPEG-1
        mMPEGCreator.LoadPreset "mpeg1-standard"
    Case 1
        mMPEGCreator.LoadPreset "mpeg1-vcd-ntsc"
    Case 2
        mMPEGCreator.LoadPreset "mpeg1-vcd-pal"
    Case 3
        mMPEGCreator.LoadPreset "mpeg2-standard"
    Case 4
        mMPEGCreator.LoadPreset "mpeg2-svcd-ntsc"
    Case 5
        mMPEGCreator.LoadPreset "mpeg2-svcd-pal"
    Case 6
        mMPEGCreator.LoadPreset "mpeg2-dvd-ntsc"
    Case 7
        mMPEGCreator.LoadPreset "mpeg2-dvd-pal"
    Case 8
        mMPEGCreator.LoadPreset "mpeg1-vcd-still-ntsc"
    Case 9
        mMPEGCreator.LoadPreset "mpeg-1-vcd-still-pal"
    Case 10
        mMPEGCreator.LoadPreset "mpeg-2-svcd-still-ntsc"
    Case 11
        mMPEGCreator.LoadPreset "mpeg-2-svcd-still-pal"
    Case 12
        ' The custom profile setting just means that whatever is
        ' currently in the mpegcreator should be used.
    End Select
End Sub

Private Sub CmbRateControl_Click()
    ' This is called when the bitrate control combo is changed
    ' We enable or disable the edit boxes, based on if the user
    ' requires those values or not
    
    Select Case CmbRateControl.ListIndex
        Case 0 ' Constant Bitrate
            CmbBitrate.Enabled = True
            CmbBitrateMin.Enabled = False
            CmbBitrateMax.Enabled = False
        Case 1 ' 2-Pass VBR
            CmbBitrate.Enabled = True
            CmbBitrateMin.Enabled = True
            CmbBitrateMax.Enabled = True
        Case 2 ' Manual VBR
            CmbBitrate.Enabled = False
            CmbBitrateMin.Enabled = True
            CmbBitrateMax.Enabled = True
        Case 3 ' Automatic VBR (constant quality VBR)
            CmbBitrate.Enabled = False
            CmbBitrateMin.Enabled = True
            CmbBitrateMax.Enabled = True
        Case 4 'Constant Quality
            CmbBitrate.Enabled = False
            CmbBitrateMin.Enabled = True
            CmbBitrateMax.Enabled = True
    End Select
    
End Sub

Private Sub CmdCancel_Click()
    mOKClicked = False
    Me.Hide
End Sub

Private Sub CmdOK_Click()
    ApplySettings
    mOKClicked = True
    Me.Hide
End Sub

Private Sub Form_Load()
    mOKClicked = False
    Set mMPEGCreator = FrmMain.MPEGConverter
    CmbPreset.ListIndex = FrmMain.CmbFormats.ListIndex
    LoadSettings
End Sub
