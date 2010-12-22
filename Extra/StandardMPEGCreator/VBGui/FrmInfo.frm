VERSION 5.00
Begin VB.Form FrmInfo 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Format Info"
   ClientHeight    =   5520
   ClientLeft      =   45
   ClientTop       =   435
   ClientWidth     =   5565
   Icon            =   "FrmInfo.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   5520
   ScaleWidth      =   5565
   ShowInTaskbar   =   0   'False
   StartUpPosition =   1  'CenterOwner
   Begin VB.CommandButton CmdClose 
      Caption         =   "Close"
      Height          =   480
      Left            =   3585
      TabIndex        =   2
      Top             =   4875
      Width           =   1815
   End
   Begin VB.TextBox TextInfo 
      Height          =   3915
      Left            =   120
      MultiLine       =   -1  'True
      ScrollBars      =   2  'Vertical
      TabIndex        =   1
      Top             =   810
      Width           =   5295
   End
   Begin VB.Label Label1 
      Caption         =   $"FrmInfo.frx":1042
      Height          =   630
      Left            =   120
      TabIndex        =   0
      Top             =   105
      Width           =   5280
   End
End
Attribute VB_Name = "FrmInfo"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub CmdClose_Click()
    Unload Me
End Sub

Private Sub Form_Load()
    Dim mpeg As MPEGConverter
    Set mpeg = FrmMain.MPEGConverter
    
    AddInfoLF ("#----------------------------------------------------")
    AddInfoLF ("#DirectEncode MPEG Encoder [v4.5]")
    AddInfoLF ("#Essien Research & Development")
    AddInfoLF ("#DirectX Version: " & mpeg.DXVersion)
    
    AddInfo (vbCrLf)
    
    mpeg.InputFile = FrmMain.TxtSource.Text
    
    On Error Resume Next
    AddInfoLF ("#-- Input file information")
    AddInfoLF ("Path: " & mpeg.InputFile)
    Dim fps As Double, duration As Double
    Dim vid As Boolean, aud As Boolean
    Dim width As Long, height As Long, bitrate As Long
    Dim strposter As String
    Call mpeg.GetFileInfo(mpeg.InputFile, fps, duration, vid, aud, width, height, bitrate, strposter)
    AddInfoLF ("Dim: " & width & "x" & height & " / Duration: " & duration & " / vid: " & vid & " / aud: " & aud & " / bitrate: " & bitrate)
    On Error GoTo 0
    
    AddInfo (vbCrLf)
    
    AddInfoLF ("#-- Last encode timing information")
    
    AddInfoLF ("Frames Encoded: " & mpeg.FramesEncoded)
    AddInfoLF ("Frames Encoded per second (Average): " & mpeg.EncodeFramerate)
    AddInfoLF ("Time required for encode: " & mpeg.TimeElapsed & " secs")
    
    On Error Resume Next 'file may not be found
    AddInfoLF ("FileSize: " & FileLen(mpeg.OutputFile) / 1024 & " KB")
    On Error GoTo 0
    
    AddInfo (vbCrLf)
    
    AddInfoLF ("Container format: " & T("SystemsFormat", mpeg.MPEGSystemsOutputFormat))
    AddInfoLF "Video: " & T("VideoFormat", mpeg.MPEGVideoOutputFormat)
    AddInfoLF "Audio: " & T("AudioFormat", mpeg.MPEGAudioOutputFormat)
    AddInfoLF "Dimensions: " & T("Dimensions", 0)
    AddInfoLF "Framerate: " & T("Framerate", 0)
                                
    AddInfo (vbCrLf)
    
    AddInfoLF "Bitrate Mode: " & T("BitrateMode", mpeg.MPEGBitrateMode)
    AddInfoLF "Average Video Bitrate: " & mpeg.MPEGVideoBitrate / 1000 & " kbits/sec"
    AddInfoLF "Minimum Video Bitrate (only VBR): " & mpeg.MPEGVideoBitrateMin / 1000 & " kbits/sec"
    AddInfoLF "Maximum Video Bitrate (only VBR): " & mpeg.MPEGVideoBitrateMax / 1000 & " kbits/sec"
    AddInfoLF "Video Quality (only mode CQ/A_CQ): " & mpeg.MPEGVideoQuality
    
    AddInfoLF "Average Audio Bitrate: " & mpeg.MPEGAudioBitrate & " kbits/sec"
    
    AddInfoLF ("#+++-------------------------------------------------")
End Sub

Function T(str As String, i As Long) As String
    T = FrmMain.MPEGConverter.TranslateVal(str, i)
End Function

Sub AddInfo(str As String)
    TextInfo.Text = TextInfo.Text & str
End Sub

Sub AddInfoLF(str As String)
    TextInfo.Text = TextInfo.Text & str & vbCrLf
End Sub
