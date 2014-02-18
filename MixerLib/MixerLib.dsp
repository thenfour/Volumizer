# Microsoft Developer Studio Project File - Name="MixerLib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=MixerLib - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "MixerLib.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "MixerLib.mak" CFG="MixerLib - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MixerLib - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "MixerLib - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "MixerLib - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "MixerLib___Win32_Debug"
# PROP BASE Intermediate_Dir "MixerLib___Win32_Debug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\bin"
# PROP Intermediate_Dir "obj"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D _WIN32_WINNT=0x0500 /D _WIN32_IE=0x0500 /Yu"stdafx.h" /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib winmm.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib winmm.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept

!ELSEIF  "$(CFG)" == "MixerLib - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "MixerLib___Win32_Release"
# PROP BASE Intermediate_Dir "MixerLib___Win32_Release"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\bin"
# PROP Intermediate_Dir "obj"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /Zi /O1 /D "NDEBUG" /D "_ATL_DLL" /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D _WIN32_WINNT=0x0500 /D _WIN32_IE=0x0500 /Yu"stdafx.h" /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib winmm.lib /nologo /subsystem:windows /dll /machine:I386 /opt:nowin98
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib winmm.lib /nologo /subsystem:windows /dll /debug /machine:I386 /opt:nowin98
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "MixerLib - Win32 Debug"
# Name "MixerLib - Win32 Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\MixerLib.cpp
# End Source File
# Begin Source File

SOURCE=.\MixerLib.def
# End Source File
# Begin Source File

SOURCE=.\MixerLib.idl
# ADD BASE MTL /tlb ".\MixerLib.tlb" /h "MixerLib.h" /iid "MixerLib_i.c" /Oicf
# ADD MTL /tlb ".\MixerLib.tlb" /h "MixerLib.h" /iid "MixerLib_i.c" /Oicf
# End Source File
# Begin Source File

SOURCE=.\MixerLib.rc
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\MixerErr.h
# End Source File
# Begin Source File

SOURCE=.\MixerLibCP.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\EnumMixer.rgs
# End Source File
# Begin Source File

SOURCE=.\EnumMixerControls.rgs
# End Source File
# Begin Source File

SOURCE=.\EnumMixerDestinations.rgs
# End Source File
# Begin Source File

SOURCE=.\EnumMixerLines.rgs
# End Source File
# Begin Source File

SOURCE=.\Mixer.rgs
# End Source File
# Begin Source File

SOURCE=.\MixerControl.rgs
# End Source File
# Begin Source File

SOURCE=.\MixerControls.rgs
# End Source File
# Begin Source File

SOURCE=.\MixerDestination.rgs
# End Source File
# Begin Source File

SOURCE=.\MixerDestinations.rgs
# End Source File
# Begin Source File

SOURCE=.\MixerLibrary.rgs
# End Source File
# Begin Source File

SOURCE=.\MixerLine.rgs
# End Source File
# Begin Source File

SOURCE=.\MixerLines.rgs
# End Source File
# Begin Source File

SOURCE=.\Mixers.rgs
# End Source File
# Begin Source File

SOURCE=.\Ph33r.rgs
# End Source File
# Begin Source File

SOURCE=.\ph33r1.bin
# End Source File
# End Group
# Begin Group "Objects"

# PROP Default_Filter ""
# Begin Group "Mixers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Mixer.cpp
# End Source File
# Begin Source File

SOURCE=.\Mixer.h
# End Source File
# Begin Source File

SOURCE=.\Mixers.cpp
# End Source File
# Begin Source File

SOURCE=.\Mixers.h
# End Source File
# End Group
# Begin Group "Lines"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\MixerLine.cpp
# End Source File
# Begin Source File

SOURCE=.\MixerLine.h
# End Source File
# Begin Source File

SOURCE=.\MixerLines.cpp
# End Source File
# Begin Source File

SOURCE=.\MixerLines.h
# End Source File
# End Group
# Begin Group "Controls"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\MixerControl.cpp
# End Source File
# Begin Source File

SOURCE=.\MixerControl.h
# End Source File
# Begin Source File

SOURCE=.\MixerControls.cpp
# End Source File
# Begin Source File

SOURCE=.\MixerControls.h
# End Source File
# End Group
# Begin Group "Destinations"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\MixerDestination.cpp
# End Source File
# Begin Source File

SOURCE=.\MixerDestination.h
# End Source File
# Begin Source File

SOURCE=.\MixerDestinations.cpp
# End Source File
# Begin Source File

SOURCE=.\MixerDestinations.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\MixerLibrary.cpp
# End Source File
# Begin Source File

SOURCE=.\MixerLibrary.h
# End Source File
# End Group
# Begin Group "Utils"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\CollectionBase.h
# End Source File
# Begin Source File

SOURCE=.\CollectionNode.h
# End Source File
# Begin Source File

SOURCE=.\CollEnum.h
# End Source File
# Begin Source File

SOURCE=.\Utils.cpp
# End Source File
# Begin Source File

SOURCE=.\Utils.h
# End Source File
# End Group
# End Target
# End Project
