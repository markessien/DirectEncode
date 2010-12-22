VERSION 5.00
Begin VB.Form FrmPan 
   BorderStyle     =   1  'Fest Einfach
   Caption         =   "Pan Effect"
   ClientHeight    =   5265
   ClientLeft      =   45
   ClientTop       =   435
   ClientWidth     =   6810
   Icon            =   "FrmPan.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   Picture         =   "FrmPan.frx":1042
   ScaleHeight     =   5265
   ScaleWidth      =   6810
   StartUpPosition =   3  'Windows-Standard
   Begin VB.Frame Frame1 
      Caption         =   "Pan Settings"
      Height          =   1365
      Left            =   30
      TabIndex        =   2
      Top             =   525
      Width           =   5715
      Begin VB.TextBox TxtFramerate 
         Height          =   315
         Left            =   3420
         TabIndex        =   10
         Text            =   "15"
         Top             =   960
         Width           =   450
      End
      Begin VB.TextBox TxtDuration 
         Height          =   315
         Left            =   1950
         TabIndex        =   9
         Text            =   "5"
         Top             =   960
         Width           =   450
      End
      Begin VB.CommandButton CmdPan 
         Caption         =   "Apply Effect"
         Height          =   330
         Left            =   3975
         TabIndex        =   8
         Top             =   960
         Width           =   1665
      End
      Begin VB.TextBox TxtTop 
         Height          =   315
         Left            =   2445
         TabIndex        =   7
         Text            =   "10"
         Top             =   255
         Width           =   450
      End
      Begin VB.TextBox TxtWidth 
         Height          =   315
         Left            =   2925
         TabIndex        =   6
         Text            =   "100"
         Top             =   255
         Width           =   450
      End
      Begin VB.TextBox TxtHeight 
         Height          =   315
         Left            =   3420
         TabIndex        =   5
         Text            =   "100"
         Top             =   255
         Width           =   450
      End
      Begin VB.TextBox TxtLeft 
         Height          =   315
         Left            =   1950
         TabIndex        =   4
         Text            =   "10"
         Top             =   255
         Width           =   450
      End
      Begin VB.TextBox TxtEnd 
         Height          =   315
         Left            =   1935
         TabIndex        =   3
         Text            =   "200"
         Top             =   600
         Width           =   450
      End
      Begin VB.Label Label4 
         Alignment       =   1  'Rechts
         Caption         =   "Framerate:"
         Height          =   195
         Left            =   2625
         TabIndex        =   14
         Top             =   1005
         Width           =   750
      End
      Begin VB.Label Label2 
         Alignment       =   1  'Rechts
         Caption         =   "Duration:"
         Height          =   195
         Left            =   870
         TabIndex        =   13
         Top             =   1005
         Width           =   1035
      End
      Begin VB.Label Label3 
         Alignment       =   1  'Rechts
         Caption         =   "Pan Rectangle(x, y, w,h):"
         Height          =   300
         Left            =   75
         TabIndex        =   12
         Top             =   300
         Width           =   1830
      End
      Begin VB.Label Label5 
         Alignment       =   1  'Rechts
         Caption         =   "Pan end middle (x):"
         Height          =   195
         Left            =   105
         TabIndex        =   11
         Top             =   630
         Width           =   1770
      End
   End
   Begin VB.PictureBox Picture1 
      Appearance      =   0  '2D
      AutoSize        =   -1  'True
      BackColor       =   &H80000005&
      BorderStyle     =   0  'Kein
      ForeColor       =   &H80000008&
      Height          =   3270
      Left            =   45
      ScaleHeight     =   3270
      ScaleWidth      =   6705
      TabIndex        =   0
      Top             =   1935
      Width           =   6705
      Begin VB.Shape ShapeEndPan 
         BorderColor     =   &H000000FF&
         BorderStyle     =   2  'Strich
         Height          =   1455
         Left            =   3195
         Top             =   540
         Width           =   1410
      End
      Begin VB.Shape ShapeStartPan 
         BorderColor     =   &H00C00000&
         Height          =   1455
         Left            =   525
         Top             =   585
         Width           =   1410
      End
   End
   Begin VB.Label Label1 
      Caption         =   $"FrmPan.frx":1D0C
      Height          =   495
      Left            =   630
      TabIndex        =   1
      Top             =   30
      Width           =   5790
   End
End
Attribute VB_Name = "FrmPan"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Public m_file As MediaFile


Private Sub CmdPan_Click()
    m_file.ApplyPanEffect CDbl(TxtDuration.Text), Val(TxtFramerate.Text), Val(TxtLeft.Text), Val(TxtTop.Text), Val(TxtWidth.Text), Val(TxtHeight.Text), Val(TxtEnd.Text)
    Unload Me
End Sub

Private Sub Form_Load()
    DrawZoomRectangle
End Sub

Sub DrawZoomRectangle()
    On Error Resume Next
    ShapeStartPan.Left = Val(TxtLeft.Text * Screen.TwipsPerPixelX)
    ShapeStartPan.Top = Val(TxtTop.Text * Screen.TwipsPerPixelY)
    ShapeStartPan.Width = Val(TxtWidth.Text * Screen.TwipsPerPixelX)
    ShapeStartPan.Height = Val(TxtHeight.Text * Screen.TwipsPerPixelY)
    
    ShapeEndPan.Width = Val(TxtWidth.Text * Screen.TwipsPerPixelX)
    ShapeEndPan.Height = Val(TxtHeight.Text * Screen.TwipsPerPixelY)
    ShapeEndPan.Left = Val(TxtEnd.Text * Screen.TwipsPerPixelX) - (ShapeEndPan.Width / 2)
    ShapeEndPan.Top = Val(TxtTop.Text * Screen.TwipsPerPixelY)
   
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

Private Sub TxtEnd_Change()
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
