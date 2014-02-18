# Microsoft Developer Studio Project File - Name="CCLib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=CCLib - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "CCLib.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "CCLib.mak" CFG="CCLib - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "CCLib - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "CCLib - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "CCLib - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\bin"
# PROP Intermediate_Dir "obj"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "CCLIB_EXPORTS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /Zi /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "UNICODE" /D "_UNICODE" /D "CCLIB_BUILD" /D "_USRDLL" /D "CCLIB_EXPORTS" /D _WIN32_WINNT=0x0500 /D _WIN32_IE=0x0500 /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib shlwapi.lib ws2_32.lib rpcrt4.lib /nologo /dll /debug /machine:I386 /opt:nowin98
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "CCLib - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\bin"
# PROP Intermediate_Dir "obj"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "CCLIB_EXPORTS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "UNICODE" /D "_UNICODE" /D "CCLIB_BUILD" /D "_USRDLL" /D "CCLIB_EXPORTS" /D _WIN32_WINNT=0x0500 /D _WIN32_IE=0x0500 /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 rpcrt4.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib shlwapi.lib ws2_32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "CCLib - Win32 Release"
# Name "CCLib - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\CCLib.rc
# End Source File
# Begin Source File

SOURCE=.\CCLog.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\CCString.cpp
# End Source File
# Begin Source File

SOURCE=.\Global.cpp
# End Source File
# Begin Source File

SOURCE=.\main.cpp
# End Source File
# Begin Source File

SOURCE=.\TraceErrorSys.cpp
# End Source File
# Begin Source File

SOURCE=.\Utilities.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\winSocket.cpp
# PROP Exclude_From_Build 1
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\CCLog.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\CCString.h
# End Source File
# Begin Source File

SOURCE=.\Container.h
# End Source File
# Begin Source File

SOURCE=.\Global.h
# End Source File
# Begin Source File

SOURCE=.\linkedlist.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TraceErrorSys.h
# End Source File
# Begin Source File

SOURCE=.\Utilities.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\winSocket.h
# PROP Exclude_From_Build 1
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\checks.bmp
# End Source File
# End Group
# Begin Group "Controls"

# PROP Default_Filter ""
# Begin Group "comctl32"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\CCImageList.cpp
# End Source File
# Begin Source File

SOURCE=.\CCImageList.h
# End Source File
# Begin Source File

SOURCE=.\CCListBox.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\CCListBox.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\CCTab.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\CCTab.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\CCToolTip.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\CCToolTip.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\CCTreeView2s.cpp
# End Source File
# Begin Source File

SOURCE=.\CCTreeView2s.h
# End Source File
# Begin Source File

SOURCE=.\CCTreeView3s.cpp
# End Source File
# Begin Source File

SOURCE=.\CCTreeView3s.h
# End Source File
# End Group
# Begin Group "custom"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\CCCustomWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\CCCustomWnd.h
# End Source File
# Begin Source File

SOURCE=.\CCFader.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\CCFader.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\CCPot.cpp
# End Source File
# Begin Source File

SOURCE=.\CCPot.h
# End Source File
# Begin Source File

SOURCE=.\CCProgressbar.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\CCProgressbar.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\Splash.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\Splash.h
# PROP Exclude_From_Build 1
# End Source File
# End Group
# Begin Group "user32"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\CCButton.cpp
# End Source File
# Begin Source File

SOURCE=.\CCButton.h
# End Source File
# Begin Source File

SOURCE=.\CCEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\CCEdit.h
# End Source File
# Begin Source File

SOURCE=.\CCMDIChild.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\CCMDIChild.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\CCMDIClient.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\CCMDIClient.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\CCStatic.cpp
# End Source File
# Begin Source File

SOURCE=.\CCStatic.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\CCControl.cpp
# End Source File
# Begin Source File

SOURCE=.\CCControl.h
# End Source File
# Begin Source File

SOURCE=.\CCControls.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\CCTreeView.cpp
# End Source File
# Begin Source File

SOURCE=.\CCTreeView.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Target
# End Project
