# Microsoft Developer Studio Generated NMAKE File, Format Version 4.10
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=DragList - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to DragList - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "DragList - Win32 Release" && "$(CFG)" !=\
 "DragList - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "DragList.mak" CFG="DragList - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "DragList - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "DragList - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "DragList - Win32 Debug"
RSC=rc.exe
MTL=mktyplib.exe
CPP=cl.exe

!IF  "$(CFG)" == "DragList - Win32 Release"

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

ALL : ".\Release\DragList.exe"

CLEAN : 
	-@erase ".\Release\DragBox.obj"
	-@erase ".\Release\DragList.exe"
	-@erase ".\Release\DragList.obj"
	-@erase ".\Release\DragList.pch"
	-@erase ".\Release\DragList.res"
	-@erase ".\Release\DragListDlg.obj"
	-@erase ".\Release\StdAfx.obj"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/DragList.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/"\
 /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/DragList.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/DragList.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/DragList.pdb" /machine:I386 /out:"$(OUTDIR)/DragList.exe" 
LINK32_OBJS= \
	".\Release\DragBox.obj" \
	".\Release\DragList.obj" \
	".\Release\DragList.res" \
	".\Release\DragListDlg.obj" \
	".\Release\StdAfx.obj"

".\Release\DragList.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "DragList - Win32 Debug"

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

ALL : ".\Debug\DragList.exe"

CLEAN : 
	-@erase ".\Debug\DragBox.obj"
	-@erase ".\Debug\DragList.exe"
	-@erase ".\Debug\DragList.ilk"
	-@erase ".\Debug\DragList.obj"
	-@erase ".\Debug\DragList.pch"
	-@erase ".\Debug\DragList.pdb"
	-@erase ".\Debug\DragList.res"
	-@erase ".\Debug\DragListDlg.obj"
	-@erase ".\Debug\StdAfx.obj"
	-@erase ".\Debug\vc40.idb"
	-@erase ".\Debug\vc40.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/DragList.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/DragList.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/DragList.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/DragList.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/DragList.exe" 
LINK32_OBJS= \
	".\Debug\DragBox.obj" \
	".\Debug\DragList.obj" \
	".\Debug\DragList.res" \
	".\Debug\DragListDlg.obj" \
	".\Debug\StdAfx.obj"

".\Debug\DragList.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "DragList - Win32 Release"
# Name "DragList - Win32 Debug"

!IF  "$(CFG)" == "DragList - Win32 Release"

!ELSEIF  "$(CFG)" == "DragList - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\ReadMe.txt

!IF  "$(CFG)" == "DragList - Win32 Release"

!ELSEIF  "$(CFG)" == "DragList - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DragList.cpp
DEP_CPP_DRAGL=\
	".\DragBox.h"\
	".\DragList.h"\
	".\DragListDlg.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "DragList - Win32 Release"


".\Release\DragList.obj" : $(SOURCE) $(DEP_CPP_DRAGL) "$(INTDIR)"\
 ".\Release\DragList.pch"


!ELSEIF  "$(CFG)" == "DragList - Win32 Debug"


".\Debug\DragList.obj" : $(SOURCE) $(DEP_CPP_DRAGL) "$(INTDIR)"\
 ".\Debug\DragList.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DragListDlg.cpp
DEP_CPP_DRAGLI=\
	".\DragBox.h"\
	".\DragList.h"\
	".\DragListDlg.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "DragList - Win32 Release"


".\Release\DragListDlg.obj" : $(SOURCE) $(DEP_CPP_DRAGLI) "$(INTDIR)"\
 ".\Release\DragList.pch"


!ELSEIF  "$(CFG)" == "DragList - Win32 Debug"


".\Debug\DragListDlg.obj" : $(SOURCE) $(DEP_CPP_DRAGLI) "$(INTDIR)"\
 ".\Debug\DragList.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "DragList - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/DragList.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/"\
 /c $(SOURCE) \
	

".\Release\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

".\Release\DragList.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "DragList - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/DragList.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

".\Debug\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

".\Debug\DragList.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DragList.rc
DEP_RSC_DRAGLIS=\
	".\DragList.ico"\
	".\DragList.rc2"\
	

!IF  "$(CFG)" == "DragList - Win32 Release"


".\Release\DragList.res" : $(SOURCE) $(DEP_RSC_DRAGLIS) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "DragList - Win32 Debug"


".\Debug\DragList.res" : $(SOURCE) $(DEP_RSC_DRAGLIS) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DragBox.cpp
DEP_CPP_DRAGB=\
	".\DragBox.h"\
	".\DragList.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "DragList - Win32 Release"


".\Release\DragBox.obj" : $(SOURCE) $(DEP_CPP_DRAGB) "$(INTDIR)"\
 ".\Release\DragList.pch"


!ELSEIF  "$(CFG)" == "DragList - Win32 Debug"


".\Debug\DragBox.obj" : $(SOURCE) $(DEP_CPP_DRAGB) "$(INTDIR)"\
 ".\Debug\DragList.pch"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
