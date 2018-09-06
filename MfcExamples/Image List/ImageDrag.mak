# Microsoft Developer Studio Generated NMAKE File, Format Version 4.10
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=ImageDrag - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to ImageDrag - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "ImageDrag - Win32 Release" && "$(CFG)" !=\
 "ImageDrag - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "ImageDrag.mak" CFG="ImageDrag - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ImageDrag - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "ImageDrag - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "ImageDrag - Win32 Debug"
RSC=rc.exe
MTL=mktyplib.exe
CPP=cl.exe

!IF  "$(CFG)" == "ImageDrag - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Release

ALL : ".\Release\ImageDrag.exe"

CLEAN : 
	-@erase ".\Release\ImageDrag.exe"
	-@erase ".\Release\ImageDrag.obj"
	-@erase ".\Release\ImageDrag.pch"
	-@erase ".\Release\ImageDrag.res"
	-@erase ".\Release\ImageDragFrm.obj"
	-@erase ".\Release\stdafx.obj"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/ImageDrag.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/"\
 /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/ImageDrag.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/ImageDrag.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/ImageDrag.pdb" /machine:I386 /out:"$(OUTDIR)/ImageDrag.exe" 
LINK32_OBJS= \
	".\Release\ImageDrag.obj" \
	".\Release\ImageDrag.res" \
	".\Release\ImageDragFrm.obj" \
	".\Release\stdafx.obj"

".\Release\ImageDrag.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "ImageDrag - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : ".\Debug\ImageDrag.exe"

CLEAN : 
	-@erase ".\Debug\ImageDrag.exe"
	-@erase ".\Debug\ImageDrag.ilk"
	-@erase ".\Debug\ImageDrag.obj"
	-@erase ".\Debug\ImageDrag.pch"
	-@erase ".\Debug\ImageDrag.pdb"
	-@erase ".\Debug\ImageDrag.res"
	-@erase ".\Debug\ImageDragFrm.obj"
	-@erase ".\Debug\stdafx.obj"
	-@erase ".\Debug\vc40.idb"
	-@erase ".\Debug\vc40.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/ImageDrag.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/ImageDrag.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/ImageDrag.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/ImageDrag.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/ImageDrag.exe" 
LINK32_OBJS= \
	".\Debug\ImageDrag.obj" \
	".\Debug\ImageDrag.res" \
	".\Debug\ImageDragFrm.obj" \
	".\Debug\stdafx.obj"

".\Debug\ImageDrag.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "ImageDrag - Win32 Release"
# Name "ImageDrag - Win32 Debug"

!IF  "$(CFG)" == "ImageDrag - Win32 Release"

!ELSEIF  "$(CFG)" == "ImageDrag - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\ImageDrag.cpp
DEP_CPP_IMAGE=\
	".\ImageDrag.h"\
	".\ImageDragFrm.h"\
	".\stdafx.h"\
	

!IF  "$(CFG)" == "ImageDrag - Win32 Release"


".\Release\ImageDrag.obj" : $(SOURCE) $(DEP_CPP_IMAGE) "$(INTDIR)"\
 ".\Release\ImageDrag.pch"


!ELSEIF  "$(CFG)" == "ImageDrag - Win32 Debug"


".\Debug\ImageDrag.obj" : $(SOURCE) $(DEP_CPP_IMAGE) "$(INTDIR)"\
 ".\Debug\ImageDrag.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ImageDrag.rc
DEP_RSC_IMAGED=\
	".\ImageDrag.ico"\
	

!IF  "$(CFG)" == "ImageDrag - Win32 Release"


".\Release\ImageDrag.res" : $(SOURCE) $(DEP_RSC_IMAGED) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ImageDrag - Win32 Debug"


".\Debug\ImageDrag.res" : $(SOURCE) $(DEP_RSC_IMAGED) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ImageDragFrm.cpp
DEP_CPP_IMAGEDR=\
	".\ImageDrag.h"\
	".\ImageDragFrm.h"\
	".\stdafx.h"\
	

!IF  "$(CFG)" == "ImageDrag - Win32 Release"


".\Release\ImageDragFrm.obj" : $(SOURCE) $(DEP_CPP_IMAGEDR) "$(INTDIR)"\
 ".\Release\ImageDrag.pch"


!ELSEIF  "$(CFG)" == "ImageDrag - Win32 Debug"


".\Debug\ImageDragFrm.obj" : $(SOURCE) $(DEP_CPP_IMAGEDR) "$(INTDIR)"\
 ".\Debug\ImageDrag.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\stdafx.cpp
DEP_CPP_STDAF=\
	".\stdafx.h"\
	

!IF  "$(CFG)" == "ImageDrag - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/ImageDrag.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/"\
 /c $(SOURCE) \
	

".\Release\stdafx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

".\Release\ImageDrag.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "ImageDrag - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/ImageDrag.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

".\Debug\stdafx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

".\Debug\ImageDrag.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
