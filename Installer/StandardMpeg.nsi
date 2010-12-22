;Essien Research & Development Installer
;Written by Mark Essien

;--------------------------------
; Product specific variables

!define VERSION_MAJOR 6
!define VERSION_MINOR 1
!define PRODUCT_BUILD 1631
!define PRODUCT_NAME "Standard MPEG Encoder"
!define PRODUCT_PAGE "http://www.standardmpeg.com"
!define INSTALL_FILE "StandardMPEGEncoderSetup${VERSION_MAJOR}.Build${PRODUCT_BUILD}.exe"
!define BRAND_TXT    "Standard MPEG"

Var ALREADY_INSTALLED

;--------------------------------
;Include Modern UI

  !include "MUI.nsh"
  !include Library.nsh

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
  !define MUI_FINISHPAGE_SHOWREADME "$INSTDIR\text\whatsnew.txt"
  !define MUI_FINISHPAGE_SHOWREADME_TEXT "View WhatsNew.txt file"
;  !define MUI_FINISHPAGE_SHOWREADME_NOTCHECKED

  !insertmacro MUI_PAGE_FINISH

;--------------------------------
;Languages
 
  !insertmacro MUI_LANGUAGE "English"

;--------------------------------
;Installer Sections

Section "Standard Mpeg Encoder Core Files" SecMain
  SectionIn RO
  !include "Files.nsh"
SectionEnd


Section "${PRODUCT_NAME} Sample Code" SampleCode
   !include "Samples.nsh"
SectionEnd

;--------------------------------
;Descriptions

  !insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN
    !insertmacro MUI_DESCRIPTION_TEXT ${SecMain} "The files required to run ${PRODUCT_NAME}."
    !insertmacro MUI_DESCRIPTION_TEXT ${SampleCode} "Sample Code for ${PRODUCT_NAME}."
  !insertmacro MUI_FUNCTION_DESCRIPTION_END
 
;--------------------------------
;Uninstaller Section

Section -post
   !include "PostInstall.nsh"
SectionEnd

Section "Uninstall"
   !include "Uninstall.nsh"
SectionEnd