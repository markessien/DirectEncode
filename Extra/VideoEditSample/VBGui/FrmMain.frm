VERSION 5.00
Object = "{939B0CFC-B68F-48FE-85E9-0200E9367B0B}#1.0#0"; "VideoEdit.dll"
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "comdlg32.ocx"
Begin VB.Form FrmMain 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Video Editor"
   ClientHeight    =   7080
   ClientLeft      =   150
   ClientTop       =   840
   ClientWidth     =   9135
   Icon            =   "FrmMain.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   7080
   ScaleWidth      =   9135
   StartUpPosition =   3  'Windows Default
   Begin VB.Frame Frame1 
      Caption         =   "Audio Tracks"
      Height          =   1185
      Left            =   15
      TabIndex        =   3
      Top             =   5625
      Width           =   9120
      Begin VB.Timer TimerLoad 
         Enabled         =   0   'False
         Interval        =   1000
         Left            =   7965
         Top             =   705
      End
      Begin MSComctlLib.ImageList ImageListPreview 
         Left            =   4995
         Top             =   630
         _ExtentX        =   1005
         _ExtentY        =   1005
         BackColor       =   -2147483643
         ImageWidth      =   80
         ImageHeight     =   60
         MaskColor       =   16777215
         _Version        =   393216
         BeginProperty Images {2C247F25-8591-11D1-B16A-00C0F0283628} 
            NumListImages   =   1
            BeginProperty ListImage1 {2C247F27-8591-11D1-B16A-00C0F0283628} 
               Picture         =   "FrmMain.frx":2372
               Key             =   ""
            EndProperty
         EndProperty
      End
      Begin MSComDlg.CommonDialog CommonDialog 
         Left            =   6930
         Top             =   690
         _ExtentX        =   847
         _ExtentY        =   847
         _Version        =   393216
      End
      Begin MSComctlLib.ImageList ImageList1 
         Left            =   5865
         Top             =   615
         _ExtentX        =   1005
         _ExtentY        =   1005
         BackColor       =   -2147483643
         ImageWidth      =   16
         ImageHeight     =   16
         MaskColor       =   12632256
         _Version        =   393216
         BeginProperty Images {2C247F25-8591-11D1-B16A-00C0F0283628} 
            NumListImages   =   6
            BeginProperty ListImage1 {2C247F27-8591-11D1-B16A-00C0F0283628} 
               Picture         =   "FrmMain.frx":26F1
               Key             =   ""
            EndProperty
            BeginProperty ListImage2 {2C247F27-8591-11D1-B16A-00C0F0283628} 
               Picture         =   "FrmMain.frx":3743
               Key             =   ""
            EndProperty
            BeginProperty ListImage3 {2C247F27-8591-11D1-B16A-00C0F0283628} 
               Picture         =   "FrmMain.frx":4795
               Key             =   ""
            EndProperty
            BeginProperty ListImage4 {2C247F27-8591-11D1-B16A-00C0F0283628} 
               Picture         =   "FrmMain.frx":57E7
               Key             =   ""
            EndProperty
            BeginProperty ListImage5 {2C247F27-8591-11D1-B16A-00C0F0283628} 
               Picture         =   "FrmMain.frx":5941
               Key             =   ""
            EndProperty
            BeginProperty ListImage6 {2C247F27-8591-11D1-B16A-00C0F0283628} 
               Picture         =   "FrmMain.frx":6993
               Key             =   ""
            EndProperty
         EndProperty
      End
      Begin VB.Label LabelAudioBlock 
         Alignment       =   2  'Center
         BackStyle       =   0  'Transparent
         Caption         =   "Unspecified song"
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   6.75
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H000000FF&
         Height          =   180
         Index           =   0
         Left            =   225
         TabIndex        =   5
         Top             =   345
         Visible         =   0   'False
         Width           =   8085
      End
      Begin VB.Shape ShapeAudioBlock 
         BackColor       =   &H00000080&
         BackStyle       =   1  'Opaque
         BorderColor     =   &H00404040&
         FillColor       =   &H0000C000&
         Height          =   240
         Index           =   0
         Left            =   180
         Shape           =   4  'Rounded Rectangle
         Top             =   330
         Visible         =   0   'False
         Width           =   8715
      End
      Begin VIDEOEDITLibCtl.VideoEdit VideoEditor 
         Left            =   6405
         OleObjectBlob   =   "FrmMain.frx":6D2D
         Top             =   645
      End
      Begin VB.Label Label1 
         Caption         =   $"FrmMain.frx":6D51
         BeginProperty Font 
            Name            =   "Tahoma"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   435
         Left            =   525
         TabIndex        =   4
         Top             =   675
         Width           =   7890
      End
      Begin VB.Image Image1 
         Height          =   240
         Left            =   180
         Picture         =   "FrmMain.frx":6E14
         Top             =   750
         Width           =   240
      End
      Begin VB.Shape ShapeAudioTimeline 
         Height          =   345
         Left            =   105
         Top             =   270
         Width           =   8835
      End
   End
   Begin MSComctlLib.StatusBar StatusBar1 
      Align           =   2  'Align Bottom
      Height          =   285
      Left            =   0
      TabIndex        =   2
      Top             =   6795
      Width           =   9135
      _ExtentX        =   16113
      _ExtentY        =   503
      Style           =   1
      _Version        =   393216
      BeginProperty Panels {8E3867A5-8586-11D1-B16A-00C0F0283628} 
         NumPanels       =   1
         BeginProperty Panel1 {8E3867AB-8586-11D1-B16A-00C0F0283628} 
         EndProperty
      EndProperty
   End
   Begin MSComctlLib.ListView LVVideo 
      Height          =   5235
      Left            =   -45
      TabIndex        =   1
      Top             =   360
      Width           =   9165
      _ExtentX        =   16166
      _ExtentY        =   9234
      Arrange         =   2
      LabelEdit       =   1
      LabelWrap       =   -1  'True
      HideSelection   =   -1  'True
      _Version        =   393217
      Icons           =   "ImageListPreview"
      SmallIcons      =   "ImageListPreview"
      ForeColor       =   -2147483640
      BackColor       =   -2147483643
      BorderStyle     =   1
      Appearance      =   1
      NumItems        =   0
   End
   Begin MSComctlLib.Toolbar TBMain 
      Align           =   1  'Align Top
      Height          =   360
      Left            =   0
      TabIndex        =   0
      Top             =   0
      Width           =   9135
      _ExtentX        =   16113
      _ExtentY        =   635
      ButtonWidth     =   2328
      ButtonHeight    =   582
      Wrappable       =   0   'False
      Appearance      =   1
      Style           =   1
      TextAlignment   =   1
      ImageList       =   "ImageList1"
      _Version        =   393216
      BeginProperty Buttons {66833FE8-8583-11D1-B16A-00C0F0283628} 
         NumButtons      =   11
         BeginProperty Button1 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Caption         =   "Add Video..."
            ImageIndex      =   1
         EndProperty
         BeginProperty Button2 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Caption         =   "Add Audio..."
            ImageIndex      =   2
         EndProperty
         BeginProperty Button3 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Style           =   3
         EndProperty
         BeginProperty Button4 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Caption         =   "Preview    "
            ImageIndex      =   4
         EndProperty
         BeginProperty Button5 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Style           =   3
         EndProperty
         BeginProperty Button6 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Style           =   4
            Object.Width           =   1500
         EndProperty
         BeginProperty Button7 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Caption         =   "Properties"
            ImageIndex      =   5
            Style           =   3
         EndProperty
         BeginProperty Button8 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Caption         =   "Properties..."
            ImageIndex      =   5
         EndProperty
         BeginProperty Button9 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Style           =   3
         EndProperty
         BeginProperty Button10 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Caption         =   "Compile...  "
            ImageIndex      =   6
         EndProperty
         BeginProperty Button11 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Style           =   3
         EndProperty
      EndProperty
      Begin VB.PictureBox Picture1 
         Appearance      =   0  'Flat
         BorderStyle     =   0  'None
         ForeColor       =   &H80000008&
         Height          =   300
         Left            =   4185
         ScaleHeight     =   300
         ScaleWidth      =   1530
         TabIndex        =   7
         Top             =   30
         Width           =   1530
         Begin VB.TextBox TxtDuration 
            Height          =   285
            Left            =   1020
            TabIndex        =   9
            Text            =   "0"
            Top             =   0
            Width           =   465
         End
         Begin VB.Label Label3 
            Caption         =   "Image Duration:"
            BeginProperty Font 
               Name            =   "Small Fonts"
               Size            =   6.75
               Charset         =   0
               Weight          =   400
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   180
            Left            =   0
            TabIndex        =   8
            Top             =   60
            Width           =   1050
         End
      End
      Begin VB.Label Label2 
         Caption         =   "Label2"
         Height          =   180
         Left            =   4230
         TabIndex        =   6
         Top             =   105
         Width           =   930
      End
   End
   Begin VB.Menu mnuFile 
      Caption         =   "File"
      Begin VB.Menu mnuOpen 
         Caption         =   "Open Project..."
      End
      Begin VB.Menu mnuSave 
         Caption         =   "Save Project..."
      End
      Begin VB.Menu dash1 
         Caption         =   "-"
      End
      Begin VB.Menu mnuAddVideo 
         Caption         =   "Add Video File..."
      End
      Begin VB.Menu mnuAddFoto 
         Caption         =   "Add Photo File..."
      End
      Begin VB.Menu mnuAddAudio 
         Caption         =   "Add Audio File..."
      End
      Begin VB.Menu dash2 
         Caption         =   "-"
      End
      Begin VB.Menu mnuExit 
         Caption         =   "Exit"
      End
   End
   Begin VB.Menu mnuView 
      Caption         =   "Actions"
      Begin VB.Menu mnuClipProperties 
         Caption         =   "View Clip Properties..."
      End
      Begin VB.Menu dash5 
         Caption         =   "-"
         Index           =   0
      End
      Begin VB.Menu mnuPreview 
         Caption         =   "Preview"
      End
      Begin VB.Menu dash74 
         Caption         =   "-"
      End
      Begin VB.Menu mnuCompile 
         Caption         =   "Compile Project..."
      End
      Begin VB.Menu dash 
         Caption         =   "-"
      End
      Begin VB.Menu mnuSpace 
         Caption         =   "Space Images To Audio"
      End
      Begin VB.Menu dashg 
         Caption         =   "-"
      End
      Begin VB.Menu mnuIntro 
         Caption         =   "Select Intro Bitmap..."
      End
      Begin VB.Menu mnuSelOutroBmp 
         Caption         =   "Select Outro Bitmap..."
      End
      Begin VB.Menu dash76 
         Caption         =   "-"
      End
      Begin VB.Menu mnuRefresh 
         Caption         =   "Refresh"
      End
      Begin VB.Menu dash36 
         Caption         =   "-"
      End
      Begin VB.Menu mnuTemplate 
         Caption         =   "Insert Template..."
      End
   End
   Begin VB.Menu mnuEffects 
      Caption         =   "Effects"
      Visible         =   0   'False
      Begin VB.Menu mnuZoomEffect 
         Caption         =   "Apply Zoom Effect On Selected Clip..."
      End
      Begin VB.Menu mnuPanEffect 
         Caption         =   "Apply Pan Effect On Selected Clip..."
      End
   End
   Begin VB.Menu mnuHelp 
      Caption         =   "?"
      Begin VB.Menu mnuAbout 
         Caption         =   "About..."
      End
   End
End
Attribute VB_Name = "FrmMain"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Public m_TransitionNames As New Collection
Public m_TrasitionGuids As New Collection
Public m_clip As New VideoClip

Private Sub Form_Load()
    Me.Show
    Screen.MousePointer = vbHourglass
    DoEvents
    VideoEditor.EnumerateTransitions
    
    TimerLoad.Enabled = True
    
    Screen.MousePointer = 0
End Sub

Private Sub Form_Unload(Cancel As Integer)
    Unload FrmCompile
    Unload FrmIntroBitmaps
    Unload FrmPreview
    Unload FrmProperties
End Sub

Private Sub LVVideo_DblClick()
    If Not LVVideo.SelectedItem Is Nothing Then
        Load FrmPicture
        Set FrmPicture.m_file = m_clip.MediaFile(formatVideo, LVVideo.SelectedItem.Index - 1)
        FrmPicture.RefreshForm
        FrmPicture.Show 1, Me
    End If
End Sub

Private Sub mnuAbout_Click()
    MsgBox "Video Editor Demo Application by Mark Essien for Essien Research & Development", vbInformation Or vbOKOnly, "About Application"
End Sub

Private Sub mnuAddAudio_Click()
    BrowseForSource False
End Sub

Private Sub mnuAddFoto_Click()
    BrowseForSource True
End Sub

Private Sub mnuAddVideo_Click()
    BrowseForSource True
End Sub

Private Sub mnuClipProperties_Click()
        If LVVideo.SelectedItem Is Nothing Then
            MsgBox "Please select a clip"
            Exit Sub
        End If
        
        Set FrmProperties.m_currentFile = Nothing
        Set FrmProperties.m_currentFile = m_clip.MediaFile(formatVideo, LVVideo.SelectedItem.Index - 1)
        
        Load FrmProperties
        FrmProperties.Show 0, Me
        DoEvents
End Sub

Private Sub mnuCompile_Click()
    Load FrmCompile
    FrmCompile.Show 1, Me
End Sub

Private Sub mnuExit_Click()
    Unload Me
End Sub

Private Sub mnuIntro_Click()
    Load FrmIntroBitmaps
    FrmIntroBitmaps.Show 1, Me
    
    If (FrmIntroBitmaps.m_bCancelled = False) Then
    
        'Insert file at first position
        Dim mediaClip As MediaFile
        Set mediaClip = m_clip.AddVideo(0, FrmIntroBitmaps.m_strSourceFile)
                        
        If Not mediaClip Is Nothing Then
        
            'Write text on the file
            mediaClip.OverlayText FrmIntroBitmaps.m_strText, FrmIntroBitmaps.m_xPos, FrmIntroBitmaps.m_yPos, _
                                  FrmIntroBitmaps.m_nWidth, FrmIntroBitmaps.m_nHeight, FrmIntroBitmaps.m_strFontFace, _
                                  FrmIntroBitmaps.m_nFontHeight
                
            'Set duration of foto display
            'Insert poster frame to listview
            Dim item As ListItem
            Dim previewListImage As ListImage
            Set previewListImage = ImageListPreview.ListImages.Add(, , mediaClip.PosterFrame)
            Set item = LVVideo.ListItems.Add(, , mediaClip.FileTitle, previewListImage.Index)
                        
            Me.Refresh
            LVVideo.Refresh
            DoEvents
        End If
    End If
End Sub

Private Sub mnuOpen_Click()
    Dim sPattern As String
    Dim startStrg As String
    Dim sFilename As String
    Dim sFileDir As String
    Dim c As Integer

    sPattern = "XML files (*.xml)|*.xml|" & _
               "All Files (*.*)|*.*"
    
    CommonDialog.Flags = cdlOFNHideReadOnly Or cdlOFNExplorer Or cdlOFNNoChangeDir
    CommonDialog.MaxFileSize = 4096
    CommonDialog.Filter = sPattern
    CommonDialog.FileName = ""
    
    CommonDialog.ShowOpen
    
    If CommonDialog.FileName > "" Then
        m_clip.LoadClip CommonDialog.FileName
        RefreshListView
    End If
End Sub

'Private Sub mnuPanEffect_Click()
'
'    If LVVideo.SelectedItem Is Nothing Then
'        MsgBox "Please select a file"
'        Exit Sub
'    End If
'
'    Load FrmPan
'    Set FrmPan.m_file = m_clip.MediaFile(formatVideo, LVVideo.SelectedItem.Index - 1)
'    FrmPan.UpdateMe
'    FrmPan.Show 1, Me
'
'End Sub

Private Sub mnuPreview_Click()
    ApplyDurationToAllImages
    
    Load FrmPreview
    FrmPreview.Show 0, Me
    FrmPreview.TimerProgress.Enabled = True
    DoEvents
    VideoEditor.CurrentClip = m_clip
    VideoEditor.StartPreview FrmPreview.PicScreen.hWnd, 0, 0, FrmPreview.PicScreen.Width / Screen.TwipsPerPixelX, FrmPreview.PicScreen.Height / Screen.TwipsPerPixelY
    FrmPreview.TimerProgress.Enabled = True
End Sub

Private Sub mnuRefresh_Click()
    RefreshListView
End Sub

Private Sub mnuSave_Click()
    Dim sPattern As String
    Dim startStrg As String
    Dim sFilename As String
    Dim sFileDir As String
    Dim c As Integer

    sPattern = "XML files (*.xml)|*.xml|" & _
                "All Files (*.*)|*.*"
    
    CommonDialog.Flags = cdlOFNHideReadOnly Or cdlOFNExplorer Or cdlOFNNoChangeDir
    CommonDialog.MaxFileSize = 4096
    CommonDialog.Filter = sPattern
    CommonDialog.FileName = ""
    
    CommonDialog.ShowSave
    
    If CommonDialog.FileName > "" Then
        m_clip.SaveClip CommonDialog.FileName
    End If
End Sub

Private Sub mnuSpace_Click()
    TxtDuration.Text = "0"
    m_clip.SpacePhotosToAudio 0, m_clip.AudioCount - 1
    RefreshListView
End Sub

Sub RefreshListView()
    If m_clip.VideoCount < 1 Then
        Exit Sub
    End If
    
    LVVideo.ListItems.Clear
    
    Set LVVideo.Icons = Nothing
    ImageListPreview.ListImages.Clear
    
    Dim i As Integer
    For i = 0 To m_clip.VideoCount - 1
        Dim li As ListImage
        Set li = ImageListPreview.ListImages.Add(, , m_clip.MediaFile(formatVideo, i).PosterFrame)
        
        If LVVideo.Icons Is Nothing Then
            Set LVVideo.Icons = ImageListPreview
        End If
        
        LVVideo.ListItems.Add , , m_clip.MediaFile(formatVideo, i).FileTitle, li.Index
        Set li = Nothing
    Next
End Sub

'Private Sub mnuZoomEffect_Click()
'
'    If LVVideo.SelectedItem Is Nothing Then
'        MsgBox "Please select a file"
'        Exit Sub
'    End If
'
'    Load FrmZoom
'    Set FrmZoom.m_file = m_clip.MediaFile(formatVideo, LVVideo.SelectedItem.Index - 1)
'    FrmZoom.UpdateMe
'    FrmZoom.Show 1, Me
'End Sub

Private Sub TBMain_ButtonClick(ByVal Button As MSComctlLib.Button)
    Select Case Button.Index
    Case 1
        BrowseForSource True
    Case 2
        BrowseForSource False
    Case 4
        mnuPreview_Click
    Case 8
        mnuClipProperties_Click
    Case 10
        mnuCompile_Click
    End Select
End Sub

Sub ApplyDurationToAllImages()
    If Val(TxtDuration.Text) = 0 Then Exit Sub
    m_clip.ForcePhotoDurations Val(TxtDuration.Text)
End Sub

Sub BrowseForSource(IsVideo As Boolean)
    Dim sPattern As String
    Dim startStrg As String
    Dim sFilename As String
    Dim sFileDir As String
    Dim c As Integer

    If IsVideo = False Then
        sPattern = "All supported audio files|*.mp3;*.wav;*.avi;*.wma;*.mp1;*.mp2|" & _
                   "All Files (*.*)|*.*"
    Else
        sPattern = "All supported video files|*.mpg;*.asf;*.wmv;*.mpeg;*.avi;*.jpg;*.jpeg;*.bmp;*.gif|" & _
                   "All Files (*.*)|*.*"
    End If
    
    CommonDialog.Flags = cdlOFNAllowMultiselect Or cdlOFNFileMustExist Or cdlOFNHideReadOnly Or cdlOFNExplorer Or cdlOFNNoChangeDir
    CommonDialog.MaxFileSize = 4096
    CommonDialog.Filter = sPattern
    CommonDialog.FileName = ""
    
    CommonDialog.ShowOpen
    
    startStrg = CommonDialog.FileName & Chr(0)
    sFileDir = StripItem(startStrg, Chr(0))
    
    For c = 1 To Len(CommonDialog.FileName)
        'extract 1 item from the string
        
        If sFileDir = "" Then
            Exit For
        ElseIf sFileDir >= CommonDialog.FileName Then
            sFilename = sFileDir
            sFileDir = ""
        Else
            sFilename = sFileDir & "\" & StripItem(startStrg, Chr(0))
            If sFilename = "" Or Len(sFilename) = Len(sFileDir) + 1 Then Exit For
        End If

        If IsVideo = False Then
            Dim mediaClip As VIDEOEDITLibCtl.MediaFile
            Set mediaClip = m_clip.AddAudio(m_clip.AudioCount - 1, sFilename)
            
            If Not mediaClip Is Nothing Then
                Set mediaClip = Nothing
                
                Dim i As Integer
                For i = 0 To m_clip.AudioCount - 1
                    On Error Resume Next
                    Load ShapeAudioBlock(i)
                    Load LabelAudioBlock(i)
                    On Error GoTo 0
                    
                    LabelAudioBlock(i).Caption = m_clip.MediaFile(formatAudio, i).FileTitle
                    LabelAudioBlock(i).Caption = LabelAudioBlock(i).Caption & " (" & FormatTime(m_clip.MediaFile(formatAudio, i).Duration) & ")"
                    
                    LabelAudioBlock(i).Visible = True
                    ShapeAudioBlock(i).Visible = True
                    
                    Dim dStartFraction As Double: dStartFraction = m_clip.MediaFile(formatAudio, i).StartOffset
                    Dim dWidthFraction As Double
                    
                    If Not dStartFraction = 0 Then
                        dStartFraction = m_clip.MediaFile(formatAudio, i).StartOffset / m_clip.AudioLength
                    End If
                    
                    dWidthFraction = (m_clip.MediaFile(formatAudio, i).Duration / m_clip.AudioLength)
                    
                    ShapeAudioBlock(i).Left = ShapeAudioTimeline.Left + 30 + (dStartFraction * ShapeAudioTimeline.Width)
                    ShapeAudioBlock(i).Width = (dWidthFraction * ShapeAudioTimeline.Width) - 60
                    
                    LabelAudioBlock(i).Left = ShapeAudioBlock(i).Left
                    LabelAudioBlock(i).Width = ShapeAudioBlock(i).Width
                    LabelAudioBlock(i).ZOrder
                    
                    DoEvents
                Next i
                
            Else
                MsgBox "The selected file was not valid, and cannot be added"
            End If
        Else
            Set mediaClip = m_clip.AddVideo(m_clip.VideoCount - 1, sFilename)
            DoEvents
            
            If Not mediaClip Is Nothing Then
                
                'Set duration of foto display
                'Insert poster frame to listview
                Dim item As ListItem
                Dim previewListImage As ListImage
                Set previewListImage = ImageListPreview.ListImages.Add(, , mediaClip.PosterFrame)
                Set item = LVVideo.ListItems.Add(, , mediaClip.FileTitle, previewListImage.Index)
                                
                Me.Refresh
                LVVideo.Refresh
                DoEvents
            Else
                MsgBox "The selected file was not valid, and cannot be added"
            End If
        End If
        
        DoEvents
    Next c
    
End Sub

Private Sub VideoEditor_Complete()
    FrmCompile.ConversionComplete
    FrmPreview.ConversionComplete
End Sub

Private Sub VideoEditor_StageChanged(ByVal NewStageDescription As String)
    FrmCompile.LabStatus = NewStageDescription
    DoEvents
End Sub

Private Sub VideoEditor_TransitionListed(ByVal TransitionName As String, ByVal TransitionGuid As String)
    m_TransitionNames.Add TransitionName
    m_TrasitionGuids.Add TransitionGuid
    DoEvents
End Sub

