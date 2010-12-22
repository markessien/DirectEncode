VERSION 5.00
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "comdlg32.ocx"
Begin VB.Form FrmMain 
   Caption         =   "Standard Mpeg Encoder VB6 TestBench"
   ClientHeight    =   4560
   ClientLeft      =   120
   ClientTop       =   420
   ClientWidth     =   5775
   Icon            =   "FrmMain.frx":0000
   LinkTopic       =   "Form1"
   ScaleHeight     =   4560
   ScaleWidth      =   5775
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton CmdStop 
      Caption         =   "Stop"
      Height          =   735
      Left            =   1680
      TabIndex        =   2
      Top             =   1200
      Width           =   2535
   End
   Begin VB.Timer Timer1 
      Enabled         =   0   'False
      Interval        =   1000
      Left            =   840
      Top             =   3720
   End
   Begin MSComDlg.CommonDialog CommonDialog1 
      Left            =   120
      Top             =   3840
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
   End
   Begin VB.CommandButton CmdLoad 
      Caption         =   "Load File to Encode..."
      Height          =   735
      Left            =   120
      TabIndex        =   0
      Top             =   360
      Width           =   5535
   End
   Begin VB.Label LabelProgress 
      Height          =   615
      Left            =   240
      TabIndex        =   1
      Top             =   2640
      Width           =   5415
   End
End
Attribute VB_Name = "FrmMain"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

' 1. Add a reference to the DirectEncode.TLB file in the SDK install
' directory.
' 2. Include a reference in your project to "ActiveMovie control type library" (Quartz.dll).
' 3. Add a reference to 'DirectEncodeVB.TLB'

' Standard Mpeg Encoder VB6 Sample. Developed by Mark Essien in his first and favorite language
' (c) 2008 Standard Mpeg.

' More info on DirectShow and VB6 is available here: http://msdn.microsoft.com/en-us/library/ms787852(VS.85).aspx

' Filter graph manager
Dim g_objMC As FilgraphManager
Dim g_objRegFilters As Object
Dim g_standardMpegVB As New StandardMPEGEncoderVB
Dim g_position As IMediaPosition

' This function is required for registering the library
Private Declare Function GetTickCount Lib "kernel32" () As Long

Private Sub CmdLoad_Click()
    Set g_objMC = New FilgraphManager  ' create the new filter graph
    Set g_objRegFilters = g_objMC.RegFilterCollection
    
    ' Show the browse for file dialog
    CommonDialog1.ShowOpen  ' get the name of the source or filter graph file

    ' Let's add a file writer filter to the graph
    Dim fileWriter As IFilterInfo
    Set fileWriter = AddFileWriter

    ' Add the mpeg encoder filter & connect to file writer
    Dim mpegEncoder As IFilterInfo
    Set mpegEncoder = AddStandardMpegEncoder(fileWriter)
    
    ' Get position object
    Set g_position = g_objMC
    Timer1.Enabled = True
            
    ' Do the configuration
    ConfigureStandardMpegEncoder mpegEncoder
    
    ' Render the selected file. This file has to be willing to connect to the
    ' Mpeg Encoder. Otherwise you have to connect the pins individually.
    ' See here: http://msdn.microsoft.com/en-us/library/ms782270(VS.85).aspx
    g_objMC.RenderFile CommonDialog1.FileName
    
    
    ' Use this to spy on the graph
    'g_standardMpegVB.PromptForGraph fileWriter.filter
    
    ' Start the graph
    g_objMC.Run
    
End Sub

Private Sub Authenticate(mpegEncoderInterface As StandardMpegEncoder)

End Sub



Private Sub ConfigureStandardMpegEncoder(mpegEncoder As IFilterInfo)

    ' Now we want to access the formats of the mpeg encoder
    Dim mpegEncoderInterface As StandardMpegEncoder
    Set mpegEncoderInterface = mpegEncoder.filter
    
    ' Select flash video
    mpegEncoderInterface.SelectFormat SYSTEMSFORMAT_FLV, CONSTRAINT_NONE
    
    ' Make the output file very small
    Dim mpegEncoderProfile As StandardMpegEncoderProfile
    Set mpegEncoderProfile = mpegEncoder.filter
    
    mpegEncoderProfile.SetWidth 160
    mpegEncoderProfile.SetHeight 120
    
    Authenticate mpegEncoderInterface
    
End Sub

Private Function AddStandardMpegEncoder(fileWriter As IFilterInfo) As IFilterInfo
    Dim filter As IRegFilterInfo
    ' find the selected filter and add it to the graph
    ' g_objRegFilters is the FilgraphManager object's RegFilterCollection property
    For Each filter In g_objRegFilters
        If filter.Name = "Standard MPEG Encoder v6" Then  ' Standard mpeg?
            Dim f As IFilterInfo  ' yes
            filter.filter f   ' add to the filter graph, return IFilterInfo f
            
            ' Get the output pin of the mpeg encoder
            Dim pinOut As IPinInfo
            f.FindPin "Systems Output", pinOut
            
            ' Get the input pin of the file writer
            Dim pinIn As IPinInfo
            fileWriter.FindPin "in", pinIn
            
            pinOut.Connect pinIn
                        
            ' Set return value
            Set AddStandardMpegEncoder = f
            Exit For
        End If
    Next filter
End Function

Private Function AddFileWriter() As IFilterInfo
    Dim filter As IRegFilterInfo
    ' find the selected filter and add it to the graph
    ' g_objRegFilters is the FilgraphManager object's RegFilterCollection property
    For Each filter In g_objRegFilters
        If filter.Name = "File writer" Then
            Dim f As IFilterInfo
            filter.filter f   ' add to the filter graph, return IFilterInfo f
            
            ' If you get an error 'cannot create object', the directencodevb.dll is not registered
            g_standardMpegVB.SetOutputFileOnFileWriter f.filter, "z:\vb6_output_file.mpg"
            Set AddFileWriter = f
            Exit For
        End If
    Next filter
End Function

Private Sub CmdStop_Click()
    g_objMC.Stop
End Sub

Private Sub Timer1_Timer()
    LabelProgress.Caption = "Positon: " & g_position.CurrentPosition & "  /   Duration: " & g_position.Duration
End Sub
