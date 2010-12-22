;Essien Research & Development Installer
;Written by Mark Essien

;--------------------------------
; Product specific variables

!define VERSION_MAJOR 3
!define VERSION_MINOR 60
!define PRODUCT_NAME "DirectEncode"
!define PRODUCT_FILE "convertwizard.exe"
!define PRODUCT_PAGE "http://www.essien.de/products/directencode"
!ifndef INSTALL_FILE
!define INSTALL_FILE "DirectEncodeSetup_${VERSION_MAJOR}${VERSION_MINOR}.exe"
!endif
!define BRAND_TXT "Essien Research && Development"


;--------------------------------
;Include Modern UI

  !include "MUI.nsh"

;--------------------------------
;Configuration
  
  ;General
  Name "${PRODUCT_NAME}"
  OutFile "${INSTALL_FILE}"

  ;Folder selection page
  InstallDir "$PROGRAMFILES\${PRODUCT_NAME}"
  
  ;Get install folder from registry if available
  InstallDirRegKey HKCU "Software\${PRODUCT_NAME}" ""
  
;--------------------------------
;Interface Settings

  !define MUI_ABORTWARNING
  !define MUI_WELCOMEFINISHPAGE_BITMAP sideimage.bmp

  !define MUI_ICON setup.ico
  !define MUI_UNICON setup.ico

  !define MUI_HEADERIMAGE
    !define MUI_HEADERIMAGE_BITMAP toplogo.bmp
    !define MUI_HEADERIMAGE_RIGHT

  !define MUI_COMPONENTSPAGE_SMALLDESC

  BrandingText /TRIMRIGHT "${BRAND_TXT}"

;--------------------------------
;Pages
  !define MUI_WELCOMEPAGE_TITLE "Welcome to the ${PRODUCT_NAME} Installation!"
  !define MUI_WELCOMEPAGE_TEXT  "This setup program will install ${PRODUCT_NAME} on your computer. Click Cancel if you don't want to install this application. Click Next to continue the installation.\r\n\r\nIt is recommended that you close all other applications before starting Setup. This will make it possible to update relevant system files without having to reboot your computer.\r\n\r\nClick Next to continue."
  
  !define MUI_LICENSEPAGE_CHECKBOX "I agree with the above terms and conditions"
  !define MUI_LICENSEPAGE_TEXT_TOP ""

  !insertmacro MUI_PAGE_WELCOME

  !define MUI_PAGE_HEADER_SUBTEXT "To proceed with the installation, you must accept this license agreement. Please read it carefully."
  !insertmacro MUI_PAGE_LICENSE "License.rtf"

  !insertmacro MUI_PAGE_COMPONENTS
  !insertmacro MUI_PAGE_DIRECTORY
  !insertmacro MUI_PAGE_INSTFILES
  !insertmacro MUI_UNPAGE_CONFIRM
  !insertmacro MUI_UNPAGE_INSTFILES

;  !define MUI_FINISHPAGE_RUN "$INSTDIR\${PRODUCT_FILE}"
;  !define MUI_FINISHPAGE_RUN_TEXT "Run ${PRODUCT_NAME}"
  !define MUI_FINISHPAGE_SHOWREADME "$INSTDIR\whatsnew.txt"
  !define MUI_FINISHPAGE_SHOWREADME_TEXT "View WhatsNew.txt file"
;  !define MUI_FINISHPAGE_SHOWREADME_NOTCHECKED

  !insertmacro MUI_PAGE_FINISH

;--------------------------------
;Languages
 
  !insertmacro MUI_LANGUAGE "English"

;--------------------------------
;Installer Sections

Section "DirectEncode Core Files" SecMain
  SectionIn RO
  SetOutPath "$INSTDIR"

  File "gettingstarted.txt"
  File "whatsnew.txt"
  File "order.txt"

; includes
  SetOutPath "$INSTDIR\MPEGFilter\"
  File "..\IMPEGFilter.h"
  File "..\MPEGFilteruids.h"
 
; Shortcuts
  SetOutPath "$SMPROGRAMS\${PRODUCT_NAME}"

    CreateShortCut "$SMPROGRAMS\${PRODUCT_NAME}\Uninstall ${PRODUCT_NAME}.lnk" \
                   "$INSTDIR\uninstall.exe"

    CreateShortCut "$SMPROGRAMS\${PRODUCT_NAME}\C++ Include Files.lnk" \
                   "$INSTDIR\MPEGFilter\"

    CreateShortCut "$SMPROGRAMS\${PRODUCT_NAME}\Getting Started.lnk" \
                   "$INSTDIR\gettingstarted.txt"

    CreateShortCut "$SMPROGRAMS\${PRODUCT_NAME}\Whats New.lnk" \
                   "$INSTDIR\whatsnew.txt"

    CreateShortCut "$SMPROGRAMS\${PRODUCT_NAME}\Order Info.lnk" \
                   "$INSTDIR\order.txt"

;    CreateShortCut "$SMPROGRAMS\${PRODUCT_NAME}\Start Convert Wizard.lnk" \
;                   "$INSTDIR\ConvertWizard.exe"
  
; overlay filter
  SetOutPath "$INSTDIR\"
  File "..\..\OverlayFilter\Release\OverlayFilter.ax"
 
; MPEG Filter
    SetOutPath "$INSTDIR\MPEGFilter"
    File "..\Release\mpgfiltr.ax"
    File ".\redist\ac3encode.dll"

    SetOutPath "$SYSDIR"
    File "..\CustomMCL\erdmpg-hi.dll"
    File "..\MPEGLib\Release\erdmpg-lo.dll"

    SetOutPath "$INSTDIR\MPEGFilter"
    File "..\CustomMCL\erdmpg-hi.dll"
    File "..\MPEGLib\Release\erdmpg-lo.dll"

; AVI Creator
    SetOutPath "$INSTDIR\AVICreator"
    File "..\..\Converters\AVICreator\ReleaseMinDependency\AVICreator.dll"

; MPEG Creator
    SetOutPath "$INSTDIR\MPEGCreator"
    File "..\..\Converters\MPEGCreator\ReleaseMinDependency\MPEGCreator.dll"
    File "..\..\Converters\MPEGCreator\StillImageGui\StillGen.exe"

; WMV Creator
    SetOutPath "$INSTDIR\WMVCreator"
    File "..\..\Converters\WMVCreator\ReleaseMinDependency\WMVCreator.dll"
   
; Still image generator
; Write start menu shortcuts
  SetOutPath "$SMPROGRAMS\${PRODUCT_NAME}"

  CreateShortCut "$SMPROGRAMS\${PRODUCT_NAME}\Uninstall ${PRODUCT_NAME}.lnk" "$INSTDIR\Uninstall.exe"

  WriteINIStr "$SMPROGRAMS\${PRODUCT_NAME}\${PRODUCT_NAME} Home Page.url" "InternetShortcut" "URL" "${PRODUCT_PAGE}"
  
  ;Store install folder
  WriteRegStr HKCU "Software\${PRODUCT_NAME}" "" $INSTDIR
  
SectionEnd


Section "${PRODUCT_NAME} Sample Code" SampleCode

    SetOutPath "$SMPROGRAMS\${PRODUCT_NAME}\Visual Basic Samples"

; C++ filter console sample    
    SetOutPath "$INSTDIR\MPEGFilter\ConsoleEncodeSample"
    File "..\EncodeSample\*.*"

    SetOutPath "$SMPROGRAMS\${PRODUCT_NAME}\Visual C++ Samples"
    CreateShortCut "$SMPROGRAMS\${PRODUCT_NAME}\Visual C++ Samples\DES Console Convert.lnk" \
                   "$INSTDIR\MPEGFilter\ConsoleEncodeSample\EncodeSample.dsw"

    
; Avi creator sample
    SetOutPath "$INSTDIR\AVICreator\VBSample"
    File "..\..\Converters\AVICreator\VBGui\*.*"

    CreateShortCut "$SMPROGRAMS\${PRODUCT_NAME}\Visual Basic Samples\AVI Creator Demo Source.lnk" \
                   "$INSTDIR\AVICreator\VBSample\PrjAviCreator.vbp"

; wmv creator sample
    SetOutPath "$INSTDIR\WMVCreator\VBSample"
    File "..\..\Converters\WMVCreator\VBGui\*.*"

    CreateShortCut "$SMPROGRAMS\${PRODUCT_NAME}\Visual Basic Samples\WMV Creator Demo Source.lnk" \
                   "$INSTDIR\WMVCreator\VBSample\PrjWMVCreator.vbp"

; mpeg creator sample
    SetOutPath "$INSTDIR\MPEGCreator\VBSample"
    File "..\..\Converters\MPEGCreator\VBGui\*.*"
   
    CreateShortCut "$SMPROGRAMS\${PRODUCT_NAME}\Visual Basic Samples\MPEG Creator Demo Source.lnk" "$INSTDIR\MPEGCreator\VBSample\PrjMPEGCreator.vbp"

    CreateShortCut "$SMPROGRAMS\${PRODUCT_NAME}\Still Image Generator.lnk" "$INSTDIR\MPEGCreator\stillgen.exe"

    CreateShortCut "$SMPROGRAMS\${PRODUCT_NAME}\AVI Creator.lnk" \
                 "$INSTDIR\AVICreator\VBSample\AVICreator.exe"

    CreateShortCut "$SMPROGRAMS\${PRODUCT_NAME}\WMV Creator.lnk" \
                   "$INSTDIR\WMVCreator\VBSample\WMVCreator.exe"


    CreateShortCut "$SMPROGRAMS\${PRODUCT_NAME}\MPEG Creator.lnk" \
                   "$INSTDIR\MPEGCreator\VBSample\MPEGCreator.exe"

SectionEnd

Section "${PRODUCT_NAME} Documentation" Documentation
   
    SetOutPath "$INSTDIR\MPEGFilter\Docs"
    File "c:\personal\dev\help files\mpegfilter\*.html"

    SetOutPath "$INSTDIR\"
    File "c:\personal\dev\help files\directencode\directencode.chm"
    File "c:\personal\dev\help files\mpegfilter\mpegfilter.chm"
    File "c:\personal\dev\help files\mpegcreator\mpegcreator.chm"
    File "c:\personal\dev\help files\avicreator\avicreator.chm"
    File "c:\personal\dev\help files\wmvcreator\wmvcreator.chm"
 
    SetOutPath "$INSTDIR\WMVCreator\Docs"
    File "c:\personal\dev\help files\wmvcreator\*.html"

    SetOutPath "$INSTDIR\AVICreator\Docs"
    File "c:\personal\dev\help files\avicreator\*.html"

    SetOutPath "$INSTDIR\MPEGCreator\Docs"
    File "c:\personal\dev\help files\mpegcreator\*.html"

    SetOutPath "$SMPROGRAMS\${PRODUCT_NAME}\Documentation"
    CreateShortCut "$SMPROGRAMS\${PRODUCT_NAME}\Documentation\DirectEncode Help.lnk" "$INSTDIR\DirectEncode.chm"
    CreateShortCut "$SMPROGRAMS\${PRODUCT_NAME}\Documentation\MPEG Encoding Filter Help.lnk" "$INSTDIR\mpegfilter.chm"
    CreateShortCut "$SMPROGRAMS\${PRODUCT_NAME}\Documentation\MPEG Creator Help.lnk" "$INSTDIR\mpegcreator.chm"
    CreateShortCut "$SMPROGRAMS\${PRODUCT_NAME}\Documentation\AVI Creator Help.lnk" "$INSTDIR\avicreator.chm"
    CreateShortCut "$SMPROGRAMS\${PRODUCT_NAME}\Documentation\WMV Creator Help.lnk" "$INSTDIR\wmvcreator.chm"
SectionEnd

;--------------------------------
;Descriptions

  !insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN
    !insertmacro MUI_DESCRIPTION_TEXT ${SecMain} "The files required to run ${PRODUCT_NAME}."
    !insertmacro MUI_DESCRIPTION_TEXT ${Documentation} "Documentation on how to use ${PRODUCT_NAME}."
    !insertmacro MUI_DESCRIPTION_TEXT ${SampleCode} "Sample Code for ${PRODUCT_NAME}."
  !insertmacro MUI_FUNCTION_DESCRIPTION_END
 
;--------------------------------
;Uninstaller Section

Section -post

  SetOutPath $INSTDIR
 
  RegDLL "$INSTDIR\MPEGFilter\mpgfiltr.ax"
  RegDLL "$INSTDIR\AVICreator\avicreator.dll"
  RegDLL "$INSTDIR\WMVCreator\wmvcreator.dll"
  RegDLL "$INSTDIR\MPEGCreator\mpegcreator.dll"
  RegDLL "$INSTDIR\OverlayFilter.ax"

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
SectionEnd

Section "Uninstall"

  DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_NAME}"
  DeleteRegKey HKLM "SOFTWARE\${PRODUCT_NAME}"
  DeleteRegKey HKLM "SOFTWARE\Essien R&D\${PRODUCT_NAME}"
  
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

SectionEnd