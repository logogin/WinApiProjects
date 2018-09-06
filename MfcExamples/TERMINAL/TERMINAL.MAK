# Microsoft Developer Studio Generated NMAKE File, Format Version 4.10
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=Terminal - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Terminal - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Terminal - Win32 Release" && "$(CFG)" !=\
 "Terminal - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Terminal.mak" CFG="Terminal - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Terminal - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Terminal - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 
################################################################################
# Begin Project
# PROP Target_Last_Scanned "Terminal - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "Terminal - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Release

ALL : "$(OUTDIR)\Terminal.exe"

CLEAN : 
	-@erase "$(INTDIR)\Buffer.obj"
	-@erase "$(INTDIR)\Modem.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\Terminal.obj"
	-@erase "$(INTDIR)\Terminal.pch"
	-@erase "$(INTDIR)\Terminal.res"
	-@erase "$(INTDIR)\TerminalDlg.obj"
	-@erase "$(INTDIR)\TermWnd.obj"
	-@erase "$(OUTDIR)\Terminal.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Terminal.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/"\
 /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x419 /fo"$(INTDIR)/Terminal.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Terminal.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/Terminal.pdb" /machine:I386 /out:"$(OUTDIR)/Terminal.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Buffer.obj" \
	"$(INTDIR)\Modem.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Terminal.obj" \
	"$(INTDIR)\Terminal.res" \
	"$(INTDIR)\TerminalDlg.obj" \
	"$(INTDIR)\TermWnd.obj"

"$(OUTDIR)\Terminal.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Terminal - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "$(OUTDIR)\Terminal.exe"

CLEAN : 
	-@erase "$(INTDIR)\Buffer.obj"
	-@erase "$(INTDIR)\Modem.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\Terminal.obj"
	-@erase "$(INTDIR)\Terminal.pch"
	-@erase "$(INTDIR)\Terminal.res"
	-@erase "$(INTDIR)\TerminalDlg.obj"
	-@erase "$(INTDIR)\TermWnd.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\Terminal.exe"
	-@erase "$(OUTDIR)\Terminal.ilk"
	-@erase "$(OUTDIR)\Terminal.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Terminal.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x419 /fo"$(INTDIR)/Terminal.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Terminal.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/Terminal.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/Terminal.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Buffer.obj" \
	"$(INTDIR)\Modem.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Terminal.obj" \
	"$(INTDIR)\Terminal.res" \
	"$(INTDIR)\TerminalDlg.obj" \
	"$(INTDIR)\TermWnd.obj"

"$(OUTDIR)\Terminal.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

################################################################################
# Begin Target

# Name "Terminal - Win32 Release"
# Name "Terminal - Win32 Debug"

!IF  "$(CFG)" == "Terminal - Win32 Release"

!ELSEIF  "$(CFG)" == "Terminal - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\ReadMe.txt

!IF  "$(CFG)" == "Terminal - Win32 Release"

!ELSEIF  "$(CFG)" == "Terminal - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Terminal.cpp
DEP_CPP_TERMI=\
	".\Buffer.h"\
	".\Modem.h"\
	".\StdAfx.h"\
	".\Terminal.h"\
	".\TerminalDlg.h"\
	".\TermWnd.h"\
	

"$(INTDIR)\Terminal.obj" : $(SOURCE) $(DEP_CPP_TERMI) "$(INTDIR)"\
 "$(INTDIR)\Terminal.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\TerminalDlg.cpp
DEP_CPP_TERMIN=\
	".\Buffer.h"\
	".\Modem.h"\
	".\StdAfx.h"\
	".\Terminal.h"\
	".\TerminalDlg.h"\
	".\TermWnd.h"\
	

"$(INTDIR)\TerminalDlg.obj" : $(SOURCE) $(DEP_CPP_TERMIN) "$(INTDIR)"\
 "$(INTDIR)\Terminal.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "Terminal - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Terminal.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/"\
 /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Terminal.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Terminal - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Terminal.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Terminal.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Terminal.rc
DEP_RSC_TERMINA=\
	".\res\Terminal.ico"\
	".\res\Terminal.rc2"\
	

"$(INTDIR)\Terminal.res" : $(SOURCE) $(DEP_RSC_TERMINA) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\TermWnd.cpp
DEP_CPP_TERMW=\
	".\Buffer.h"\
	".\Modem.h"\
	".\StdAfx.h"\
	".\Terminal.h"\
	".\TerminalDlg.h"\
	".\TermWnd.h"\
	

"$(INTDIR)\TermWnd.obj" : $(SOURCE) $(DEP_CPP_TERMW) "$(INTDIR)"\
 "$(INTDIR)\Terminal.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Modem.cpp
DEP_CPP_MODEM=\
	".\Buffer.h"\
	".\Modem.h"\
	".\StdAfx.h"\
	".\Terminal.h"\
	

"$(INTDIR)\Modem.obj" : $(SOURCE) $(DEP_CPP_MODEM) "$(INTDIR)"\
 "$(INTDIR)\Terminal.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Buffer.cpp
DEP_CPP_BUFFE=\
	".\Buffer.h"\
	".\StdAfx.h"\
	".\Terminal.h"\
	

"$(INTDIR)\Buffer.obj" : $(SOURCE) $(DEP_CPP_BUFFE) "$(INTDIR)"\
 "$(INTDIR)\Terminal.pch"


# End Source File
# End Target
# End Project
################################################################################
