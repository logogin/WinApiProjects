# Microsoft Developer Studio Generated NMAKE File, Format Version 4.10
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=MDI - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to MDI - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "MDI - Win32 Release" && "$(CFG)" != "MDI - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Mdi.mak" CFG="MDI - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MDI - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "MDI - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "MDI - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "MDI - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\Debug\MDI"
# PROP Intermediate_Dir "..\Debug\MDI"
# PROP Target_Dir ""
OUTDIR=.\..\Debug\MDI
INTDIR=.\..\Debug\MDI

ALL : "$(OUTDIR)\Mdi.exe"

CLEAN : 
	-@erase "$(INTDIR)\AppAbout.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\MDI.obj"
	-@erase "$(INTDIR)\Mdi.pch"
	-@erase "$(INTDIR)\MDI.res"
	-@erase "$(INTDIR)\Mdichild.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(OUTDIR)\Mdi.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Mdi.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\..\Debug\MDI/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x419 /fo"$(INTDIR)/MDI.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Mdi.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/Mdi.pdb" /machine:I386 /out:"$(OUTDIR)/Mdi.exe" 
LINK32_OBJS= \
	"$(INTDIR)\AppAbout.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\MDI.obj" \
	"$(INTDIR)\MDI.res" \
	"$(INTDIR)\Mdichild.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\Mdi.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "MDI - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\Debug\MDI"
# PROP Intermediate_Dir "..\Debug\MDI"
# PROP Target_Dir ""
OUTDIR=.\..\Debug\MDI
INTDIR=.\..\Debug\MDI

ALL : "$(OUTDIR)\Mdi.exe"

CLEAN : 
	-@erase "$(INTDIR)\AppAbout.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\MDI.obj"
	-@erase "$(INTDIR)\Mdi.pch"
	-@erase "$(INTDIR)\MDI.res"
	-@erase "$(INTDIR)\Mdichild.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\Mdi.exe"
	-@erase "$(OUTDIR)\Mdi.ilk"
	-@erase "$(OUTDIR)\Mdi.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Mdi.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\..\Debug\MDI/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x419 /fo"$(INTDIR)/MDI.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Mdi.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/Mdi.pdb" /debug /machine:I386 /out:"$(OUTDIR)/Mdi.exe" 
LINK32_OBJS= \
	"$(INTDIR)\AppAbout.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\MDI.obj" \
	"$(INTDIR)\MDI.res" \
	"$(INTDIR)\Mdichild.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\Mdi.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "MDI - Win32 Release"
# Name "MDI - Win32 Debug"

!IF  "$(CFG)" == "MDI - Win32 Release"

!ELSEIF  "$(CFG)" == "MDI - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\MDI.cpp
DEP_CPP_MDI_C=\
	".\AppAbout.h"\
	".\MainFrm.h"\
	".\MDI.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\MDI.obj" : $(SOURCE) $(DEP_CPP_MDI_C) "$(INTDIR)"\
 "$(INTDIR)\Mdi.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "MDI - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Mdi.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Mdi.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "MDI - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Mdi.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Mdi.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MainFrm.cpp
DEP_CPP_MAINF=\
	".\MainFrm.h"\
	".\MDI.h"\
	".\MDIChild.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\Mdi.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\MDI.rc
DEP_RSC_MDI_R=\
	".\res\MDI.ico"\
	".\res\MDI.rc2"\
	".\res\MDIText.ico"\
	".\res\text.cur"\
	

"$(INTDIR)\MDI.res" : $(SOURCE) $(DEP_RSC_MDI_R) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\AppAbout.cpp
DEP_CPP_APPAB=\
	".\AppAbout.h"\
	".\MDI.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\AppAbout.obj" : $(SOURCE) $(DEP_CPP_APPAB) "$(INTDIR)"\
 "$(INTDIR)\Mdi.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Mdichild.cpp
DEP_CPP_MDICH=\
	".\MDI.h"\
	".\MDIChild.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\Mdichild.obj" : $(SOURCE) $(DEP_CPP_MDICH) "$(INTDIR)"\
 "$(INTDIR)\Mdi.pch"


# End Source File
# End Target
# End Project
################################################################################
