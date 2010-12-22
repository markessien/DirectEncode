VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Object = "{BDC217C8-ED16-11CD-956C-0000C04E4C0A}#1.1#0"; "TABCTL32.OCX"
Begin VB.Form FrmPicture 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Image Manipulation"
   ClientHeight    =   7305
   ClientLeft      =   45
   ClientTop       =   435
   ClientWidth     =   7590
   Icon            =   "FrmPicture.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   7305
   ScaleWidth      =   7590
   StartUpPosition =   3  'Windows Default
   Begin MSComctlLib.StatusBar StatusBar 
      Align           =   2  'Align Bottom
      Height          =   255
      Left            =   0
      TabIndex        =   8
      Top             =   7050
      Width           =   7590
      _ExtentX        =   13388
      _ExtentY        =   450
      _Version        =   393216
      BeginProperty Panels {8E3867A5-8586-11D1-B16A-00C0F0283628} 
         NumPanels       =   2
         BeginProperty Panel1 {8E3867AB-8586-11D1-B16A-00C0F0283628} 
            AutoSize        =   2
         EndProperty
         BeginProperty Panel2 {8E3867AB-8586-11D1-B16A-00C0F0283628} 
            AutoSize        =   2
         EndProperty
      EndProperty
   End
   Begin VB.CommandButton Command2 
      Caption         =   "Apply && Close"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   1230
      Left            =   6105
      Picture         =   "FrmPicture.frx":1042
      Style           =   1  'Graphical
      TabIndex        =   2
      Top             =   5790
      Width           =   1335
   End
   Begin TabDlg.SSTab SSTab1 
      Height          =   1215
      Left            =   120
      TabIndex        =   1
      Top             =   5775
      Width           =   5895
      _ExtentX        =   10398
      _ExtentY        =   2143
      _Version        =   393216
      Tabs            =   2
      TabsPerRow      =   2
      TabHeight       =   520
      TabCaption(0)   =   "Zoom/Pan Effect"
      TabPicture(0)   =   "FrmPicture.frx":2084
      Tab(0).ControlEnabled=   -1  'True
      Tab(0).Control(0)=   "Image3"
      Tab(0).Control(0).Enabled=   0   'False
      Tab(0).Control(1)=   "FrameZoom"
      Tab(0).Control(1).Enabled=   0   'False
      Tab(0).Control(2)=   "OptStart"
      Tab(0).Control(2).Enabled=   0   'False
      Tab(0).Control(3)=   "OptEnd"
      Tab(0).Control(3).Enabled=   0   'False
      Tab(0).ControlCount=   4
      TabCaption(1)   =   "Text Overlay Effect"
      TabPicture(1)   =   "FrmPicture.frx":20A0
      Tab(1).ControlEnabled=   0   'False
      Tab(1).ControlCount=   0
      Begin VB.OptionButton OptEnd 
         Caption         =   "End"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H000000FF&
         Height          =   255
         Left            =   735
         TabIndex        =   5
         Top             =   780
         Value           =   -1  'True
         Width           =   735
      End
      Begin VB.OptionButton OptStart 
         Caption         =   "Start"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H00FF0000&
         Height          =   255
         Left            =   735
         TabIndex        =   4
         Top             =   435
         Width           =   735
      End
      Begin VB.Frame FrameZoom 
         Caption         =   "Start"
         Height          =   735
         Left            =   1515
         TabIndex        =   3
         Top             =   360
         Width           =   4260
         Begin MSComctlLib.Slider SliderShapeSize 
            Height          =   450
            Left            =   555
            TabIndex        =   6
            Top             =   180
            Width           =   3480
            _ExtentX        =   6138
            _ExtentY        =   794
            _Version        =   393216
            SmallChange     =   10
            Max             =   100
            SelStart        =   100
            TickFrequency   =   5
            Value           =   100
         End
         Begin VB.Label Label2 
            Alignment       =   1  'Right Justify
            Caption         =   "Size:"
            Height          =   240
            Left            =   75
            TabIndex        =   7
            Top             =   300
            Width           =   420
         End
      End
      Begin VB.Image Image3 
         Height          =   480
         Left            =   120
         Picture         =   "FrmPicture.frx":20BC
         Top             =   480
         Width           =   480
      End
   End
   Begin VB.Shape ShapeStartPan 
      BackColor       =   &H00000000&
      BorderColor     =   &H00C00000&
      BorderStyle     =   4  'Dash-Dot
      FillColor       =   &H00FF8080&
      Height          =   4950
      Left            =   90
      Top             =   705
      Width           =   7335
   End
   Begin VB.Label LabelPanEnd 
      Alignment       =   1  'Right Justify
      AutoSize        =   -1  'True
      BackStyle       =   0  'Transparent
      Caption         =   "Pan End"
      ForeColor       =   &H00000080&
      Height          =   195
      Left            =   6750
      TabIndex        =   10
      Top             =   720
      Width           =   615
   End
   Begin VB.Label LabelPanBegin 
      AutoSize        =   -1  'True
      BackStyle       =   0  'Transparent
      Caption         =   "Pan Begin"
      ForeColor       =   &H00800000&
      Height          =   195
      Left            =   150
      TabIndex        =   9
      Top             =   735
      Width           =   735
   End
   Begin VB.Shape ShapeEndPan 
      BorderColor     =   &H000000FF&
      BorderStyle     =   3  'Dot
      Height          =   4950
      Left            =   90
      Top             =   705
      Width           =   7335
   End
   Begin VB.Image ImgPreview 
      Appearance      =   0  'Flat
      BorderStyle     =   1  'Fixed Single
      Height          =   4980
      Left            =   75
      Stretch         =   -1  'True
      Top             =   690
      Width           =   7365
   End
   Begin VB.Image Image4 
      Height          =   240
      Left            =   6990
      Picture         =   "FrmPicture.frx":2D86
      Top             =   195
      Width           =   240
   End
   Begin VB.Label Label1 
      Caption         =   $"FrmPicture.frx":3110
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   840
      TabIndex        =   0
      Top             =   120
      Width           =   5940
   End
   Begin VB.Image Image1 
      Height          =   480
      Left            =   120
      Picture         =   "FrmPicture.frx":31B7
      Top             =   120
      Width           =   480
   End
End
Attribute VB_Name = "FrmPicture"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Public m_file As MediaFile
Dim m_xClick As Long
Dim m_yClick As Long
Dim m_xDistance As Long
Dim m_yDistance As Long
Dim m_bMouseDown As Boolean

Public Sub RefreshForm()
    ImgPreview.Picture = LoadPicture(m_file.FilePath)
End Sub

Private Sub Command1_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
    Screen.MousePointer = 0
End Sub

Private Sub Command2_Click()
    Dim rcPos As New VideoRect
    rcPos.Left = 0
    rcPos.Width = ImgPreview.Width / Screen.TwipsPerPixelX
    rcPos.Top = 0
    rcPos.Height = ImgPreview.Height / Screen.TwipsPerPixelY

    Dim rcStart As New VideoRect
    rcStart.Left = (ShapeStartPan.Left - ImgPreview.Left) / Screen.TwipsPerPixelX
    rcStart.Width = ShapeStartPan.Width / Screen.TwipsPerPixelX
    rcStart.Top = (ShapeStartPan.Top - ImgPreview.Top) / Screen.TwipsPerPixelY
    rcStart.Height = ShapeStartPan.Height / Screen.TwipsPerPixelY

    Dim rcEnd As New VideoRect
    rcEnd.Left = (ShapeEndPan.Left - ImgPreview.Left) / Screen.TwipsPerPixelX
    rcEnd.Width = ShapeEndPan.Width / Screen.TwipsPerPixelX
    rcEnd.Top = (ShapeEndPan.Top - ImgPreview.Top) / Screen.TwipsPerPixelY
    rcEnd.Height = ShapeEndPan.Height / Screen.TwipsPerPixelY

'    Dim rcOriginal As New VideoRect
'    rcOriginal.Left = 0
'    rcOriginal.Top = 0
'    rcOriginal.Width = ScaleX(ImgPreview.Picture.Width) / Screen.TwipsPerPixelX
'    rcOriginal.Height = ScaleY(ImgPreview.Picture.Height) / Screen.TwipsPerPixelY
'
'    Dim fScaleWidth As Double
'    Dim fScaleHeight As Double
'    fScaleWidth = rcPos.Width / rcOriginal.Width
'    fScaleHeight = rcPos.Height / rcOriginal.Height
'
'    'Rescale the start rectangle to the picture pixel dimensions
'    Dim nWidth As Long: nWidth = rcStart.Width
'    Dim nHeight As Long: nHeight = rcStart.Height
'    rcStart.Left = rcStart.Left / fScaleWidth
'    rcStart.Top = rcStart.Top / fScaleHeight
'    rcStart.Right = rcStart.Left + (nWidth / fScaleWidth)
'    rcStart.Bottom = rcStart.Top + (nHeight / fScaleHeight)
'
'    'Rescale the end rectangle to the picture pixel dimensions
'    nWidth = rcEnd.Width
'    nHeight = rcEnd.Height
'    rcEnd.Left = rcEnd.Left / fScaleWidth
'    rcEnd.Top = rcEnd.Top / fScaleHeight
'    rcEnd.Right = rcEnd.Left + (nWidth / fScaleWidth)
'    rcEnd.Bottom = rcEnd.Top + (nHeight / fScaleHeight)
    
    m_file.ApplyMotionEffect Me.hWnd, rcPos, rcStart, rcEnd, 15, 5
    
    Unload Me
End Sub

Private Sub Command2_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
    Screen.MousePointer = 0
End Sub

Function GetCurrentShape() As Shape
    If OptStart.Value = True Then
        Set GetCurrentShape = ShapeStartPan
    Else
        Set GetCurrentShape = ShapeEndPan
    End If
End Function

Private Sub Form_Load()
  '  ImgPreview.Width = 352 * Screen.TwipsPerPixelX
   ' ImgPreview.Height = 288 * Screen.TwipsPerPixelY
End Sub

Private Sub Form_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
    Screen.MousePointer = 0
End Sub

Private Sub Form_MouseUp(Button As Integer, Shift As Integer, X As Single, Y As Single)
    m_bMouseDown = False
End Sub

Private Sub Form_Unload(Cancel As Integer)
    Screen.MousePointer = 0
End Sub

Private Sub ImgPreview_MouseDown(Button As Integer, Shift As Integer, X As Single, Y As Single)
    m_xClick = X
    m_yClick = Y
    
    If m_bMouseDown = False Then
        m_xDistance = X - GetCurrentShape.Left
        m_yDistance = Y - GetCurrentShape.Top
    End If
    
    m_bMouseDown = True
End Sub

Private Sub ImgPreview_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
    Screen.MousePointer = 5
    UpdateStatusInfo X, Y
    
    If m_bMouseDown Then
        Dim nNewLeft As Long: nNewLeft = X - m_xDistance
        Dim nNewHeight As Long: nNewHeight = Y - m_yDistance
        
        If nNewLeft > ImgPreview.Left And _
           (nNewLeft + GetCurrentShape.Width) < (ImgPreview.Left + ImgPreview.Width) Then
            GetCurrentShape.Left = nNewLeft
        End If
        
        If (nNewHeight) > ImgPreview.Top And _
            (nNewHeight + GetCurrentShape.Height) < (ImgPreview.Top + ImgPreview.Height) Then
            GetCurrentShape.Top = nNewHeight
        End If
        
        AlignLabels
        
    End If
End Sub

Sub UpdateStatusInfo(X As Single, Y As Single)
    If X = 0 And Y = 0 Then
        StatusBar.Panels(1).Text = ""
    Else
        StatusBar.Panels(1).Text = "mx=" & X & ", my=" & Y
    End If
    
    Dim xs As Long: xs = Screen.TwipsPerPixelX
    Dim ys As Long: ys = Screen.TwipsPerPixelY
    StatusBar.Panels(2).Text = "{" & Round(ShapeStartPan.Left / xs, 0) & _
                               "," & Round(ShapeStartPan.Top / ys, 0) & _
                               "," & Round((ShapeStartPan.Left + ShapeStartPan.Width) / xs, 0) & _
                               "," & Round((ShapeStartPan.Top + ShapeStartPan.Height) / ys, 0) & _
                               "} -> "
End Sub

Private Sub ImgPreview_MouseUp(Button As Integer, Shift As Integer, X As Single, Y As Single)
    m_bMouseDown = False
End Sub

Private Sub OptEnd_Click()
    OptStart_Click
End Sub

Private Sub OptStart_Click()
    If OptStart.Value = True Then
        FrameZoom.Caption = "Start"
    Else
        FrameZoom.Caption = "End"
    End If
End Sub

Sub ChangeShapeSize(ByRef theShape As Shape, percentValue As Long)
    Dim nMaxWidth As Long: nMaxWidth = ImgPreview.Width - 2
    Dim nMaxHeight As Long: nMaxHeight = ImgPreview.Height - 2
    Dim nCurWidth As Long: nCurWidth = nMaxWidth * (percentValue / 100)
    Dim nCurHeight As Long: nCurHeight = nMaxHeight * (percentValue / 100)
    Dim nCurCenterX As Long: nCurCenterX = theShape.Left + (theShape.Width / 2)
    Dim nCurCenterY As Long: nCurCenterY = theShape.Top + (theShape.Height / 2)
    
    theShape.Width = nCurWidth
    theShape.Left = nCurCenterX - (nCurWidth / 2)
    
    theShape.Height = nCurHeight
    theShape.Top = nCurCenterY - (nCurHeight / 2)
    
    AlignLabels
    UpdateStatusInfo 0, 0
End Sub

Sub AlignLabels()
    LabelPanBegin.Left = ShapeStartPan.Left + 50
    LabelPanBegin.Top = ShapeStartPan.Top + 50
    
    LabelPanEnd.Left = (ShapeEndPan.Left + ShapeEndPan.Width) - LabelPanEnd.Width - 50
    LabelPanEnd.Top = ShapeEndPan.Top + 50
End Sub

Private Sub SliderShapeSize_Scroll()
    If OptStart.Value = True Then
        Call ChangeShapeSize(ShapeStartPan, SliderShapeSize.Value)
    Else
        Call ChangeShapeSize(ShapeEndPan, SliderShapeSize.Value)
    End If
End Sub

Private Sub SSTab1_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
    Screen.MousePointer = 0
End Sub
