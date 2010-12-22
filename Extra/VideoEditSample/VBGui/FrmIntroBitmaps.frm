VERSION 5.00
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "COMDLG32.OCX"
Begin VB.Form FrmIntroBitmaps 
   BorderStyle     =   1  'Fest Einfach
   Caption         =   "Add bitmap with overlay text..."
   ClientHeight    =   2985
   ClientLeft      =   45
   ClientTop       =   435
   ClientWidth     =   5295
   Icon            =   "FrmIntroBitmaps.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   2985
   ScaleWidth      =   5295
   StartUpPosition =   1  'Fenstermitte
   Begin MSComDlg.CommonDialog CommonDialog 
      Left            =   1545
      Top             =   2475
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
   End
   Begin VB.CommandButton CmdCancel 
      Caption         =   "Cancel"
      Height          =   420
      Left            =   4005
      TabIndex        =   15
      Top             =   2490
      Width           =   1215
   End
   Begin VB.CommandButton CmdOK 
      Caption         =   "OK"
      Height          =   420
      Left            =   2730
      TabIndex        =   14
      Top             =   2490
      Width           =   1215
   End
   Begin VB.Frame Frame1 
      Caption         =   "Introductory Message"
      Height          =   2355
      Left            =   60
      TabIndex        =   0
      Top             =   105
      Width           =   5160
      Begin VB.TextBox TxtFontHeight 
         Height          =   285
         Left            =   3675
         TabIndex        =   13
         Text            =   "24"
         Top             =   1980
         Width           =   375
      End
      Begin VB.TextBox TxtFontFace 
         Height          =   300
         Left            =   1980
         TabIndex        =   11
         Text            =   "Arial"
         Top             =   1965
         Width           =   915
      End
      Begin VB.TextBox TxtHeight 
         Height          =   300
         Left            =   3570
         TabIndex        =   9
         Text            =   "100"
         Top             =   1275
         Width           =   480
      End
      Begin VB.TextBox TxtWidth 
         Height          =   300
         Left            =   3045
         TabIndex        =   8
         Text            =   "100"
         Top             =   1275
         Width           =   480
      End
      Begin VB.TextBox TxtYPos 
         Height          =   300
         Left            =   2520
         TabIndex        =   7
         Text            =   "0"
         Top             =   1275
         Width           =   480
      End
      Begin VB.TextBox TxtXPos 
         Height          =   300
         Left            =   1980
         TabIndex        =   6
         Text            =   "0"
         Top             =   1275
         Width           =   480
      End
      Begin VB.CommandButton CmdBrowse 
         Caption         =   "Browse..."
         Height          =   330
         Left            =   4095
         TabIndex        =   4
         Top             =   1590
         Width           =   1020
      End
      Begin VB.TextBox TxtFile 
         Height          =   315
         Left            =   1980
         TabIndex        =   3
         Top             =   1605
         Width           =   2070
      End
      Begin VB.TextBox TxtMsg 
         Height          =   975
         Left            =   1980
         MultiLine       =   -1  'True
         TabIndex        =   1
         Top             =   255
         Width           =   3120
      End
      Begin VB.Image ImgPreview 
         BorderStyle     =   1  'Fest Einfach
         Height          =   960
         Left            =   135
         Stretch         =   -1  'True
         Top             =   270
         Width           =   1755
      End
      Begin VB.Label Label4 
         Alignment       =   1  'Rechts
         AutoSize        =   -1  'True
         Caption         =   "Font Pts:"
         Height          =   195
         Left            =   2970
         TabIndex        =   12
         Top             =   2025
         Width           =   630
      End
      Begin VB.Label Label2 
         Alignment       =   1  'Rechts
         Caption         =   "Font Face:"
         Height          =   255
         Left            =   825
         TabIndex        =   10
         Top             =   2010
         Width           =   1065
      End
      Begin VB.Label Label3 
         Alignment       =   1  'Rechts
         Caption         =   "Coordinates (x, y, w, h):"
         Height          =   195
         Left            =   60
         TabIndex        =   5
         Top             =   1335
         Width           =   1830
      End
      Begin VB.Label Label1 
         Alignment       =   1  'Rechts
         Caption         =   "Bitmap image:"
         Height          =   255
         Left            =   825
         TabIndex        =   2
         Top             =   1650
         Width           =   1065
      End
   End
End
Attribute VB_Name = "FrmIntroBitmaps"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Public m_bCancelled As Boolean
Public m_strText As String
Public m_strFontFace As String
Public m_nFontHeight As Long
Public m_xPos As Long
Public m_yPos As Long
Public m_nWidth As Long
Public m_nHeight As Long
Public m_strSourceFile As String

Private Sub CmdBrowse_Click()
    Dim sPattern As String
    Dim startStrg As String
    Dim sFilename As String
    Dim sFileDir As String
    Dim c As Integer

    sPattern = "Bitmap files (*.bmp)|*.bmp|" & _
                   "All Files (*.*)|*.*"
    
    CommonDialog.Flags = cdlOFNHideReadOnly Or cdlOFNExplorer Or cdlOFNNoChangeDir
    CommonDialog.MaxFileSize = 4096
    CommonDialog.Filter = sPattern
    CommonDialog.FileName = TxtFile.Text
    
    CommonDialog.ShowSave
    
    If CommonDialog.FileName > "" Then
        TxtFile.Text = CommonDialog.FileName
        ImgPreview.Picture = LoadPicture(TxtFile.Text)
    End If
End Sub

Private Sub CmdCancel_Click()
    m_bCancelled = True
    Unload Me
End Sub

Private Sub CmdOK_Click()

    m_strText = TxtMsg.Text
    m_strFontFace = TxtFontFace.Text
    m_nFontHeight = Val(TxtFontHeight.Text)
    m_xPos = Val(TxtXPos.Text)
    m_yPos = Val(TxtYPos.Text)
    m_nWidth = Val(TxtWidth.Text)
    m_nHeight = Val(TxtHeight.Text)
    m_strSourceFile = TxtFile.Text

    m_bCancelled = False
    Unload Me
End Sub

Private Sub Form_Load()
    m_bCancelled = False
End Sub
