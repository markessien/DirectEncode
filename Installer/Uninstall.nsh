  DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_NAME}"
  DeleteRegKey HKLM "SOFTWARE\${PRODUCT_NAME}"
  DeleteRegKey HKLM "SOFTWARE\Essien R&D\${PRODUCT_NAME}"
  
	Delete "$SYSDIR\avcodec-51.dll"
	Delete "$SYSDIR\avformat-52.dll"
	Delete "$SYSDIR\avutil-49.dll"
	Delete "$SYSDIR\erdmpg-6.dll"
			
  Delete "$SMPROGRAMS\${PRODUCT_NAME}\*.lnk"
  Delete "$SMPROGRAMS\${PRODUCT_NAME}\*.url"
  Delete "$SMPROGRAMS\${PRODUCT_NAME}\*.*"
  RMDir  /r "$SMPROGRAMS\${PRODUCT_NAME}"

  Delete "$DESKTOP\Start ${PRODUCT_NAME}.lnk"
  Delete "$INSTDIR\*.*"
  RMDir /r $INSTDIR
  Delete "$INSTDIR\Uninstall.exe"
  RMDir "$INSTDIR"

  DeleteRegKey /ifempty HKCU "Software\${PRODUCT_NAME}"