VERSION 5.00
Begin VB.Form FrmProperties 
   BorderStyle     =   1  'Fest Einfach
   Caption         =   "Clip Properties"
   ClientHeight    =   2550
   ClientLeft      =   45
   ClientTop       =   435
   ClientWidth     =   5550
   Icon            =   "FrmProperties.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   2550
   ScaleWidth      =   5550
   StartUpPosition =   1  'Fenstermitte
   Begin VB.TextBox TxtDuration 
      Height          =   285
      Left            =   2520
      TabIndex        =   7
      Text            =   "0"
      Top             =   480
      Width           =   1230
   End
   Begin VB.CommandButton CmdSave 
      Caption         =   "Save"
      Default         =   -1  'True
      Height          =   450
      Left            =   4005
      TabIndex        =   5
      Top             =   2010
      Width           =   1470
   End
   Begin VB.Frame Frame1 
      Caption         =   "Transition into next clip"
      Height          =   660
      Left            =   90
      TabIndex        =   2
      Top             =   1275
      Width           =   5400
      Begin VB.ComboBox CmbTransition 
         Height          =   315
         Left            =   450
         TabIndex        =   3
         Text            =   "None"
         Top             =   240
         Width           =   4830
      End
      Begin VB.Image Image1 
         Height          =   240
         Left            =   150
         Picture         =   "FrmProperties.frx":1042
         Top             =   270
         Width           =   240
      End
   End
   Begin VB.PictureBox PicPreview 
      BackColor       =   &H00000000&
      Height          =   1020
      Left            =   120
      ScaleHeight     =   960
      ScaleWidth      =   1365
      TabIndex        =   0
      Top             =   120
      Width           =   1425
   End
   Begin VB.Label Label3 
      Alignment       =   1  'Rechts
      Caption         =   "Duration:"
      Height          =   240
      Left            =   1710
      TabIndex        =   6
      Top             =   510
      Width           =   690
   End
   Begin VB.Label LabName 
      Caption         =   "Unknown file"
      Height          =   225
      Left            =   2520
      TabIndex        =   4
      Top             =   195
      Width           =   2550
   End
   Begin VB.Label Label1 
      Alignment       =   1  'Rechts
      Caption         =   "Name:"
      Height          =   240
      Left            =   1785
      TabIndex        =   1
      Top             =   195
      Width           =   600
   End
End
Attribute VB_Name = "FrmProperties"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Public m_currentFile As MediaFile

Private Sub CmdSave_Click()
    m_currentFile.Duration = Val(TxtDuration.Text)
    m_currentFile.Transition = FrmMain.m_TrasitionGuids(CmbTransition.ListIndex + 1)
    Unload Me
End Sub

Private Sub Form_Load()
    LabName.Caption = m_currentFile.FileTitle
    PicPreview.Picture = m_currentFile.PosterFrame
    TxtDuration.Text = m_currentFile.Duration
    
    Dim i As Integer
    For i = 1 To FrmMain.m_TransitionNames.Count
        CmbTransition.AddItem FrmMain.m_TransitionNames(i)
        
        If m_currentFile.Transition = FrmMain.m_TrasitionGuids(i) Then
            CmbTransition.ListIndex = i - 1
        End If
    Next i
    
End Sub
