; SndVolEx.nsi
;
; It will install notepad.exe into a directory that the user selects,
;

; The name of the installer
Name "One Light Volumizer"

; The file to write
OutFile "Setup.exe"

; The default installation directory
InstallDir "$PROGRAMFILES\One Light Volumizer"

; Registry key to check for directory (so if you install again, it will 
; overwrite the old one automatically)
InstallDirRegKey HKLM SOFTWARE\OneLightVolumizer "Install_Dir"

; The text to prompt the user to enter a directory
ComponentText "This will install One Light Volumizer on your computer. Select which components you want installed."

; The text to prompt the user to enter a directory
DirText "Choose a directory to install in to:"

LicenseText "Please review the End User License Agreement before installing One Light Volumizer."
LicenseData "eula.txt"

; The stuff to install
Section "One Light Volumizer Program Files (required)"

  ;-------------------------
  ; First thing's first, check the windows version.
  ReadRegStr $0 HKLM "SOFTWARE\Microsoft\Windows NT\CurrentVersion" CurrentVersion
  StrCmp $0 "" lbl_VersionError 0

  ; We're in NT, but make sure we're 5.0 or later.
  StrCpy $9 $0 1 ; Copy the first digit of the version - this is the major version.
  IntCmp $9 5 0 lbl_VersionError 0
  Goto lbl_VersionOK

  lbl_VersionError:
  ; ERROR!
  MessageBox MB_OK|MB_ICONSTOP "This application requires Windows 2000 or later."
  Abort "This application requires Windows 2000 or later."

  lbl_VersionOK:
  ;-------------------------

  ; Set output path to the installation directory.
  SetOutPath $INSTDIR

  ; Put files there
  File /r "cream"
  File /r "default"
  File "atl70.dll"
  File "themes.xml"
  File "ccres.dll"
  File "mixerlib.dll"
  File "volumizer.exe"
  File "eula.txt"
  File "order.rtf"

  WriteUninstaller "uninstall.exe"

  ; Register the dll.
  RegDLL "MixerLib.dll"

  ; Other installation tasks
  CallInstDLL olinst.dll ninstall

SectionEnd

; optional section
Section "Start Menu Shortcuts"
  CreateDirectory "$SMPROGRAMS\One Light Volumizer"
  CreateShortCut "$SMPROGRAMS\One Light Volumizer\Uninstall.lnk" "$INSTDIR\uninstall.exe" "" "$INSTDIR\uninstall.exe" 0
  CreateShortCut "$SMPROGRAMS\One Light Volumizer\Volumizer.lnk" "$INSTDIR\Volumizer.exe" "" "$INSTDIR\Volumizer.exe" 0
SectionEnd

; uninstall stuff

UninstallText "This will uninstall One Light Volumizer. Hit next to continue."

; special uninstall section.
Section "Uninstall"

  SetOutPath $INSTDIR
  UnRegDLL "$INSTDIR\MixerLib.dll"

  ; remove files
  Delete MixerLib.dll
  Delete CCRes.dll
  Delete OneLightVolumizer.log
  Delete volumizer.exe
  Delete Unregister.exe
  Delete themes.xml
  Delete eula.txt
  Delete atl70.dll
  Delete order.rtf
  RMDir /r $INSTDIR\blue
  RMDir /r $INSTDIR\default

  ; MUST REMOVE UNINSTALLER, too
  Delete $INSTDIR\uninstall.exe

  ; remove shortcuts, if any.
  Delete "$SMPROGRAMS\One Light Volumizer\*.*"

  ; remove directories used.
  RMDir "$SMPROGRAMS\One Light Volumizer"

  RMDir "$INSTDIR"

SectionEnd

; eof
