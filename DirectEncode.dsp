# Microsoft Developer Studio Project File - Name="DirectEncode" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=DirectEncode - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "DirectEncode.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "DirectEncode.mak" CFG="DirectEncode - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "DirectEncode - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "DirectEncode - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/WriterFilter", BAAAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "DirectEncode - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Bin/Release"
# PROP Intermediate_Dir "Bin/Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "DirectEncode_EXPORTS" /YX /FD /c
# ADD CPP /nologo /Gz /MT /W3 /GR /GX /O2 /Ob0 /D "INC_OLE2" /D "STRICT" /D _WIN32_WINNT=0x0400 /D "WIN32" /D "_WIN32" /D "_MT" /D "_DLL" /D _X86_=1 /D WINVER=0x0400 /D "NDEBUG" /D try=__try /D except=__except /D leave=__leave /D finally=__finally /D "STATIC_LINK" /D "LAYER2" /D "VS6" /FR /YX"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /i "..\..\BaseClasses" /d "NDEBUG" /d "WIN32"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 strmbase.lib strmiids.lib shlwapi.lib quartz.lib winmm.lib msacm32.lib dxguid.lib strmbase.lib quartz.lib winmm.lib msvcrt.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib advapi32.lib ole32.lib oleaut32.lib uuid.lib /nologo /stack:0x200000,0x200000 /entry:"DllEntryPoint@12" /dll /machine:I386 /nodefaultlib:"libc" /nodefaultlib:"libcmt" /OPT:NOREF /OPT:ICF
# SUBTRACT LINK32 /pdb:none /nodefaultlib

!ELSEIF  "$(CFG)" == "DirectEncode - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Bin/Debug"
# PROP Intermediate_Dir "Bin/Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "DirectEncode_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /Gz /MDd /W3 /GX /Zi /Od /D "INC_OLE2" /D "STRICT" /D _WIN32_WINNT=0x0400 /D "WIN32" /D "_WIN32" /D "_MT" /D "_DLL" /D _X86_=1 /D WINVER=0x0400 /D DBG=1 /D "DEBUG" /D "_DEBUG" /D "STATIC_LINK" /D "LAYER2" /D "_WINDOWS" /D "VERBOSE" /D "VS6" /FR /YX"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /i "..\..\BaseClasses" /d "_DEBUG" /d "WIN32"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 strmbasd.lib strmiids.lib shlwapi.lib dsound.lib msacm32.lib dxguid.lib strmbasd.lib quartz.lib winmm.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib advapi32.lib ole32.lib oleaut32.lib uuid.lib /nologo /stack:0x200000,0x200000 /dll /debug /machine:I386 /nodefaultlib:"LIBCMT" /nodefaultlib:"LIBC" /nodefaultlib:"LIBCMTD" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none /nodefaultlib

!ENDIF 

# Begin Target

# Name "DirectEncode - Win32 Release"
# Name "DirectEncode - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\DirectEncode.cpp
# End Source File
# Begin Source File

SOURCE=.\DirectEncode.def
# End Source File
# Begin Source File

SOURCE=.\DirectEncode.idl
# ADD MTL /h "DirectEncode_h.h"
# SUBTRACT MTL /mktyplib203
# End Source File
# Begin Source File

SOURCE=.\DirectEncode.rc
# End Source File
# Begin Source File

SOURCE=.\DirectEncode_i.c
# End Source File
# Begin Source File

SOURCE=.\DirectEncodeVB.cpp
# End Source File
# Begin Source File

SOURCE=.\Encode.cpp
# End Source File
# Begin Source File

SOURCE=.\EncodeErdLib.cpp
# End Source File
# Begin Source File

SOURCE=.\License.cpp
# End Source File
# Begin Source File

SOURCE=.\LogoOverlay.cpp
# End Source File
# Begin Source File

SOURCE=.\MPEGFilter.cpp
# End Source File
# Begin Source File

SOURCE=.\MPEGFilterInterface.cpp
# End Source File
# Begin Source File

SOURCE=.\MPEGInputPin.cpp
# End Source File
# Begin Source File

SOURCE=.\MPEGObj.cpp
# End Source File
# Begin Source File

SOURCE=.\MPEGOutputPin.cpp
# End Source File
# Begin Source File

SOURCE=.\MPEGSeeking.cpp
# End Source File
# Begin Source File

SOURCE=.\Profile.cpp
# End Source File
# Begin Source File

SOURCE=.\PropPage.cpp
# End Source File
# Begin Source File

SOURCE=.\SequenceHeaders.cpp
# End Source File
# Begin Source File

SOURCE=.\stdafx.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\DirectEncodeVB.h
# End Source File
# Begin Source File

SOURCE=.\Encode.h
# End Source File
# Begin Source File

SOURCE=.\EncodeErdLib.h
# End Source File
# Begin Source File

SOURCE=.\License.h
# End Source File
# Begin Source File

SOURCE=.\LogoOverlay.h
# End Source File
# Begin Source File

SOURCE=.\MPEGFilter.h
# End Source File
# Begin Source File

SOURCE=.\MPEGFilterInterface.h
# End Source File
# Begin Source File

SOURCE=.\MPEGInputPin.h
# End Source File
# Begin Source File

SOURCE=.\MPEGObj.h
# End Source File
# Begin Source File

SOURCE=.\MPEGOutputPin.h
# End Source File
# Begin Source File

SOURCE=.\MPEGSeeking.h
# End Source File
# Begin Source File

SOURCE=.\Profile.h
# End Source File
# Begin Source File

SOURCE=.\PropPage.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\SequenceHeaders.h
# End Source File
# Begin Source File

SOURCE=.\StandardMPEGEncoderUIDs.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\Images\demo.bmp
# End Source File
# Begin Source File

SOURCE=.\DirectEncodeVB.rgs
# End Source File
# Begin Source File

SOURCE=.\Images\info_16.ico
# End Source File
# Begin Source File

SOURCE=.\Images\logo.ico
# End Source File
# Begin Source File

SOURCE=.\Images\reel.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\dd.txt
# End Source File
# Begin Source File

SOURCE=.\tt.asp
# End Source File
# End Target
# End Project
