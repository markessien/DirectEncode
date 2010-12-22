		
		RMDir  /r "$SMPROGRAMS\${PRODUCT_NAME}"
			
; includes
		SetOutPath "$INSTDIR\Include\"
		File "..\StandardMPEGEncoderUIDs.h"
		File "..\Release\DirectEncode.tlb"
		File "..\..\erdmpeg\erdmpglib\erdmpglib.h"
        File "headers.txt"
        File "..\DirectEncode.idl"
        File "NETLibs\DirectEncodeNET.dll"
        File "Z:\Development\DirectEncode\Samples\DirectEncodeVB\ReleaseMinDependency\DirectEncodeVB.dll"

; system dependencies 
		StrCpy $ALREADY_INSTALLED 0
		!insertmacro InstallLib REGDLL $ALREADY_INSTALLED REBOOT_NOTPROTECTED "redist\msvbvm60.dll" "$SYSDIR\msvbvm60.dll" "$SYSDIR"
		!insertmacro InstallLib REGDLL $ALREADY_INSTALLED REBOOT_PROTECTED    "redist\oleaut32.dll" "$SYSDIR\oleaut32.dll" "$SYSDIR"
		!insertmacro InstallLib REGDLL $ALREADY_INSTALLED REBOOT_PROTECTED    "redist\olepro32.dll" "$SYSDIR\olepro32.dll" "$SYSDIR"
		!insertmacro InstallLib REGDLL $ALREADY_INSTALLED REBOOT_PROTECTED    "redist\comcat.dll"   "$SYSDIR\comcat.dll"   "$SYSDIR"
		!insertmacro InstallLib DLL    $ALREADY_INSTALLED REBOOT_PROTECTED    "redist\asycfilt.dll" "$SYSDIR\asycfilt.dll" "$SYSDIR"
		!insertmacro InstallLib TLB    $ALREADY_INSTALLED REBOOT_PROTECTED    "redist\stdole2.tlb"  "$SYSDIR\stdole2.tlb"  "$SYSDIR"
		!insertmacro InstallLib REGDLL $ALREADY_INSTALLED REBOOT_PROTECTED    "redist\MSCOMCTL.OCX"  "$SYSDIR\MSCOMCTL.OCX"  "$SYSDIR"
		!insertmacro InstallLib REGDLL $ALREADY_INSTALLED REBOOT_PROTECTED    "redist\COMDLG32.OCX"  "$SYSDIR\COMDLG32.OCX"  "$SYSDIR"
		!insertmacro InstallLib REGDLL $ALREADY_INSTALLED REBOOT_PROTECTED    "redist\TABCTL32.OCX"  "$SYSDIR\TABCTL32.OCX"  "$SYSDIR"

; redistribute
		SetOutPath "$INSTDIR\Redistributables\"
		File "..\Release\DirectEncode.dll"
   		File "Z:\Development\erdmpeg\erdmpglib\erdmpg-6.dll"

; Text files
		SetOutPath "$INSTDIR\Text"
		File "gettingstarted.txt"
		File "whatsnew.txt"
		File "order.txt"
		File "headers.txt"
        File "redistribute.txt"
				
; Shortcuts
		SetOutPath "$SMPROGRAMS\${PRODUCT_NAME}"
		
		CreateShortCut "$SMPROGRAMS\${PRODUCT_NAME}\Uninstall ${PRODUCT_NAME}.lnk" "$INSTDIR\uninstall.exe"
		CreateShortCut "$SMPROGRAMS\${PRODUCT_NAME}\Start MPEGCreator.lnk" "$INSTDIR\bin\mpegcreator.exe"
		CreateShortCut "$SMPROGRAMS\${PRODUCT_NAME}\C++ Include Files.lnk" \
									 "$INSTDIR\Include\"
		
		CreateShortCut "$SMPROGRAMS\${PRODUCT_NAME}\Getting Started.lnk" \
									 "$INSTDIR\Text\gettingstarted.txt"
		
		CreateShortCut "$SMPROGRAMS\${PRODUCT_NAME}\Whats New.lnk" \
									 "$INSTDIR\Text\whatsnew.txt"
		
		CreateShortCut "$SMPROGRAMS\${PRODUCT_NAME}\Order Info.lnk" \
									 "$INSTDIR\Text\order.txt"
  
		SetOutPath "$SMPROGRAMS\${PRODUCT_NAME}"
		CreateShortCut "$SMPROGRAMS\${PRODUCT_NAME}\Uninstall ${PRODUCT_NAME}.lnk" "$INSTDIR\Uninstall.exe"
		
		WriteINIStr "$SMPROGRAMS\${PRODUCT_NAME}\${PRODUCT_NAME} Home Page.url" "InternetShortcut" "URL" "${PRODUCT_PAGE}"
		
   		 WriteINIStr "$SMPROGRAMS\${PRODUCT_NAME}\Online Documentation [Internet].url" "InternetShortcut" "URL" "http://www.standardmpeg.com/documentation/"

		;Store install folder
		WriteRegStr HKCU "Software\${PRODUCT_NAME}" "" $INSTDIR
		
; MPEG Filter
   	SetOutPath "$INSTDIR\Bin"
   	File "..\Release\directencode.dll"
    File "Z:\Development\DirectEncode\Samples\StandardMPEGCreator\Release\StandardMPEGCreator.dll"
    File "Z:\Development\DirectEncode\Samples\StandardMPEGCreator\VBGui\MPEGCreator.exe"

	
    SetOutPath "$SYSDIR"
	Delete "$SYSDIR\erdmpg-6.dll"
   	File "Z:\Development\erdmpeg\erdmpglib\erdmpg-6.dll"

; WMV Creator
   	SetOutPath "$INSTDIR\Extras"
   	SetOutPath "$INSTDIR\Extras\WMVCreator"
    File "Z:\Development\DirectEncode\Samples\WMVCreator\Release\WMVCreator.dll"
	File "Z:\Development\DirectEncode\Samples\WMVCreator\VBGui\WMVCreator.exe"
	SetOutPath "$INSTDIR\Extras\WMVCreator\Code"
    File "Z:\Development\DirectEncode\Samples\WMVCreator\VBGui\*.*"

; Write start menu shortcuts
