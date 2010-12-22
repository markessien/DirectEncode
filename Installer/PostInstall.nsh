  SetOutPath $INSTDIR
  RegDLL "$SYSDIR\comdlg32.ocx"
  RegDLL "$INSTDIR\Bin\DirectEncode.dll"
  RegDLL "$INSTDIR\Bin\StandardMPEGCreator.dll"
 
  WriteRegStr HKLM "SOFTWARE\${PRODUCT_NAME}" "" $INSTDIR
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_NAME}" \
                   "DisplayName" "${PRODUCT_NAME}"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_NAME}" \
                   "UninstallString" '"$INSTDIR\uninstall.exe"'

  IfFileExists "$SMPROGRAMS\${PRODUCT_NAME}" "" nofunshit
    ExecShell open '$SMPROGRAMS\${PRODUCT_NAME}'
   Sleep 500
   BringToFront
  nofunshit:

  Delete "$INSTDIR\uninstall.exe"
  WriteUninstaller "$INSTDIR\uninstall.exe"