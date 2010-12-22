Attribute VB_Name = "ModMain"
Option Explicit

Public Function FormatTime(Duration As Double) As String
    Dim strTime As String
    Dim dMins As Double
    Dim dSecs As Double
    
    Duration = Round(Duration, 0)
    
    dMins = Duration \ 60
    dSecs = Duration - (dMins * 60)
    
    strTime = Trim(Str(dMins)) & ":" & IIf(dSecs = 0, "00", IIf(dSecs < 10, "0" & Trim(Str(dSecs)), Trim(Str(dSecs))))
    
    FormatTime = strTime
End Function

Function StripItem(startStrg As String, parser As String) As String
'this takes a string separated by the chr passed in Parser,
'splits off 1 item, and shortens startStrg so that the next
'item is ready for removal.

    If Len(startStrg) < 1 Then Exit Function
    
   Dim c As Integer
   Dim item As String
   
   c = 1
   
   Do
   
      If Mid(startStrg, c, 1) = parser Then
      
         item = Mid(startStrg, 1, c - 1)
         startStrg = Mid(startStrg, c + 1, Len(startStrg))
         StripItem = item
         Exit Function
      End If
      
      c = c + 1
   
   Loop

End Function

