# Microsoft Developer Studio Generated NMAKE File, Format Version 4.10
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=RichEdit - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to RichEdit - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "RichEdit - Win32 Release" && "$(CFG)" !=\
 "RichEdit - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "RichEdit.mak" CFG="RichEdit - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "RichEdit - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "RichEdit - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "RichEdit - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "RichEdit - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\Debug\RichEdit"
# PROP Intermediate_Dir "..\Debug\RichEdit"
# PROP Target_Dir ""
OUTDIR=.\..\Debug\RichEdit
INTDIR=.\..\Debug\RichEdit

ALL : "$(OUTDIR)\RichEdit.exe"

CLEAN : 
	-@erase "$(INTDIR)\REditCtrl.obj"
	-@erase "$(INTDIR)\RichEdit.obj"
	-@erase "$(INTDIR)\RichEdit.pch"
	-@erase "$(INTDIR)\RichEdit.res"
	-@erase "$(INTDIR)\RichEditFrm.obj"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(OUTDIR)\RichEdit.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/RichEdit.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/"\
 /c 
CPP_OBJS=.\..\Debug\RichEdit/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x419 /fo"$(INTDIR)/RichEdit.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/RichEdit.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/RichEdit.pdb" /machine:I386 /out:"$(OUTDIR)/RichEdit.exe" 
LINK32_OBJS= \
	"$(INTDIR)\REditCtrl.obj" \
	"$(INTDIR)\RichEdit.obj" \
	"$(INTDIR)\RichEdit.res" \
	"$(INTDIR)\RichEditFrm.obj" \
	"$(INTDIR)\stdafx.obj"

"$(OUTDIR)\RichEdit.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "RichEdit - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\Debug\RichEdit"
# PROP Intermediate_Dir "..\Debug\RichEdit"
# PROP Target_Dir ""
OUTDIR=.\..\Debug\RichEdit
INTDIR=.\..\Debug\RichEdit

ALL : "$(OUTDIR)\RichEdit.exe"

CLEAN : 
	-@erase "$(INTDIR)\REditCtrl.obj"
	-@erase "$(INTDIR)\RichEdit.obj"
	-@erase "$(INTDIR)\RichEdit.pch"
	-@erase "$(INTDIR)\RichEdit.res"
	-@erase "$(INTDIR)\RichEditFrm.obj"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\RichEdit.exe"
	-@erase "$(OUTDIR)\RichEdit.ilk"
	-@erase "$(OUTDIR)\RichEdit.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/RichEdit.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\..\Debug\RichEdit/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x419 /fo"$(INTDIR)/RichEdit.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/RichEdit.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/RichEdit.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/RichEdit.exe" 
LINK32_OBJS= \
	"$(INTDIR)\REditCtrl.obj" \
	"$(INTDIR)\RichEdit.obj" \
	"$(INTDIR)\RichEdit.res" \
	"$(INTDIR)\RichEditFrm.obj" \
	"$(INTDIR)\stdafx.obj"

"$(OUTDIR)\RichEdit.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "RichEdit - Win32 Release"
# Name "RichEdit - Win32 Debug"

!IF  "$(CFG)" == "RichEdit - Win32 Release"

!ELSEIF  "$(CFG)" == "RichEdit - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\RichEdit.cpp
DEP_CPP_RICHE=\
	".\REditCtrl.h"\
	".\RichEdit.h"\
	".\RichEditFrm.h"\
	".\stdafx.h"\
	

"$(INTDIR)\RichEdit.obj" : $(SOURCE) $(DEP_CPP_RICHE) "$(INTDIR)"\
 "$(INTDIR)\RichEdit.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\RichEdit.rc
DEP_RSC_RICHED=\
	".\res\RichEdit.ico"\
	

"$(INTDIR)\RichEdit.res" : $(SOURCE) $(DEP_RSC_RICHED) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\RichEditFrm.cpp
DEP_CPP_RICHEDI=\
	".\REditCtrl.h"\
	".\RichEdit.h"\
	".\RichEditFrm.h"\
	".\stdafx.h"\
	

"$(INTDIR)\RichEditFrm.obj" : $(SOURCE) $(DEP_CPP_RICHEDI) "$(INTDIR)"\
 "$(INTDIR)\RichEdit.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\stdafx.cpp
DEP_CPP_STDAF=\
	".\stdafx.h"\
	

!IF  "$(CFG)" == "RichEdit - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/RichEdit.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/"\
 /c $(SOURCE) \
	

"$(INTDIR)\stdafx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\RichEdit.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "RichEdit - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/RichEdit.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\stdafx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\RichEdit.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\REditCtrl.cpp
DEP_CPP_REDIT=\
	".\REditCtrl.h"\
	".\RichEdit.h"\
	".\stdafx.h"\
	

"$(INTDIR)\REditCtrl.obj" : $(SOURCE) $(DEP_CPP_REDIT) "$(INTDIR)"\
 "$(INTDIR)\RichEdit.pch"


# End Source File
# End Target
# End Project
################################################################################
