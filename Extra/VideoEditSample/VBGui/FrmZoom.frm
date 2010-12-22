VERSION 5.00
Begin VB.Form FrmZoom 
   BorderStyle     =   1  'Fest Einfach
   Caption         =   "Zoom Effect"
   ClientHeight    =   5625
   ClientLeft      =   45
   ClientTop       =   435
   ClientWidth     =   6570
   Icon            =   "FrmZoom.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   5625
   ScaleWidth      =   6570
   StartUpPosition =   1  'Fenstermitte
   Begin VB.TextBox TxtFramerate 
      Height          =   315
      Left            =   3315
      TabIndex        =   11
      Text            =   "15"
      Top             =   1035
      Width           =   450
   End
   Begin VB.TextBox TxtDuration 
      Height          =   315
      Left            =   1830
      TabIndex        =   9
      Text            =   "5"
      Top             =   1035
      Width           =   450
   End
   Begin VB.CommandButton CmdZoom 
      Caption         =   "Apply Zoom"
      Height          =   345
      Left            =   3840
      TabIndex        =   7
      Top             =   600
      Width           =   1665
   End
   Begin VB.TextBox TxtTop 
      Height          =   315
      Left            =   2340
      TabIndex        =   6
      Text            =   "0"
      Top             =   615
      Width           =   450
   End
   Begin VB.TextBox TxtWidth 
      Height          =   315
      Left            =   2820
      TabIndex        =   5
      Text            =   "100"
      Top             =   615
      Width           =   450
   End
   Begin VB.TextBox TxtHeight 
      Height          =   315
      Left            =   3315
      TabIndex        =   4
      Text            =   "100"
      Top             =   615
      Width           =   450
   End
   Begin VB.TextBox TxtLeft 
      Height          =   315
      Left            =   1845
      TabIndex        =   3
      Text            =   "0"
      Top             =   615
      Width           =   450
   End
   Begin VB.PictureBox Picture1 
      Appearance      =   0  '2D
      AutoSize        =   -1  'True
      BackColor       =   &H80000005&
      BorderStyle     =   0  'Kein
      ForeColor       =   &H80000008&
      Height          =   4095
      Left            =   75
      ScaleHeight     =   4095
      ScaleWidth      =   6420
      TabIndex        =   1
      Top             =   1485
      Width           =   6420
      Begin VB.Shape ShapeZoomOut 
         BorderColor     =   &H00FF0000&
         Height          =   1455
         Left            =   750
         Top             =   390
         Width           =   1410
      End
      Begin VB.Shape ShapeZoom 
         BorderColor     =   &H000000FF&
         Height          =   1455
         Left            =   525
         Top             =   585
         Width           =   1410
      End
   End
   Begin VB.Label Label4 
      Alignment       =   1  'Rechts
      Caption         =   "Framerate:"
      Height          =   195
      Left            =   2490
      TabIndex        =   10
      Top             =   1080
      Width           =   750
   End
   Begin VB.Label Label2 
      Alignment       =   1  'Rechts
      Caption         =   "Duration:"
      Height          =   195
      Left            =   660
      TabIndex        =   8
      Top             =   1080
      Width           =   1035
   End
   Begin VB.Label Label3 
      Alignment       =   1  'Rechts
      Caption         =   "Zoom End Rectangle (x, y, w,h):"
      Height          =   390
      Left            =   105
      TabIndex        =   2
      Top             =   585
      Width           =   1665
   End
   Begin VB.Image Image1 
      Height          =   480
      Left            =   135
      Picture         =   "FrmZoom.frx":038A
      Top             =   75
      Width           =   480
   End
   Begin VB.Label Label1 
      Caption         =   $"FrmZoom.frx":0C54
      Height          =   495
      Left            =   720
      TabIndex        =   0
      Top             =   60
      Width           =   5790
   End
End
Attribute VB_Name = "FrmZoom"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Public m_file As MediaFile

Sub DrawZoomRectangle()
    On Error Resume Next
    ShapeZoom.Left = Val(TxtLeft.Text * Screen.TwipsPerPixelX)
    ShapeZoom.Top = Val(TxtTop.Text * Screen.TwipsPerPixelY)
    ShapeZoom.Width = Val(TxtWidth.Text * Screen.TwipsPerPixelX)
    ShapeZoom.Height = Val(TxtHeight.Text * Screen.TwipsPerPixelY)
    
    
    Dim rcSource As New VideoRect
    rcSource.Left = 0
    rcSource.Top = 0
    rcSource.Width = Picture1.Width / Screen.TwipsPerPixelX
    rcSource.Height = Picture1.Height / Screen.TwipsPerPixelY
    
    Dim rcZoomIn As New VideoRect
    rcZoomIn.Left = Val(TxtLeft.Text)
    rcZoomIn.Top = Val(TxtTop.Text)
    rcZoomIn.Width = Val(TxtWidth.Text)
    rcZoomIn.Height = Val(TxtHeight.Text)
   
    Dim rcResult As New VideoRect
    Call m_file.GetZoomOutRect(rcSource, rcZoomIn, rcResult)
    
    ShapeZoomOut.Left = rcResult.Left * Screen.TwipsPerPixelX
    ShapeZoomOut.Top = rcResult.Top * Screen.TwipsPerPixelY
    ShapeZoomOut.Width = rcResult.Width * Screen.TwipsPerPixelX
    ShapeZoomOut.Height = rcResult.Height * Screen.TwipsPerPixelY
    
End Sub

Sub UpdateMe()
    Dim nExtra As Long
    
    Picture1.Picture = LoadPicture(m_file.FilePath)
    
    nExtra = Me.Width - Me.ScaleWidth
    Me.Width = Picture1.Width + 100 + nExtra
    
    nExtra = Me.Height - Me.ScaleHeight
    Me.Height = Picture1.Height + Picture1.Top + nExtra + 100
    
    DrawZoomRectangle
End Sub

Private Sub CmdZoom_Click()
    m_file.ApplyZoomEffect CDbl(TxtDuration.Text), CDbl(TxtFramerate.Text), Val(TxtLeft.Text), Val(TxtTop.Text), Val(TxtWidth.Text), Val(TxtHeight.Text)
    Unload Me
End Sub

Private Sub Form_Activate()
    DrawZoomRectangle
End Sub


Private Sub TxtHeight_Change()
    DrawZoomRectangle
End Sub

Private Sub TxtLeft_Change()
    DrawZoomRectangle
End Sub

Private Sub TxtTop_Change()
    DrawZoomRectangle
End Sub

Private Sub TxtWidth_Change()
    DrawZoomRectangle
End Sub
