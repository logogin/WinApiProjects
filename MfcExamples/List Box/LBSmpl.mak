# Microsoft Developer Studio Generated NMAKE File, Format Version 4.10
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=LBSmpl - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to LBSmpl - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "LBSmpl - Win32 Release" && "$(CFG)" != "LBSmpl - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "LBSmpl.mak" CFG="LBSmpl - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "LBSmpl - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "LBSmpl - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "LBSmpl - Win32 Debug"
RSC=rc.exe
MTL=mktyplib.exe
CPP=cl.exe

!IF  "$(CFG)" == "LBSmpl - Win32 Release"

# PROP BASE Use_MFC 0
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

ALL : ".\Release\LBSmpl.exe"

CLEAN : 
	-@erase ".\Release\LBDlg.obj"
	-@erase ".\Release\LBSmpl.exe"
	-@erase ".\Release\LBSmpl.obj"
	-@erase ".\Release\LBSmpl.pch"
	-@erase ".\Release\LBSmpl.res"
	-@erase ".\Release\StdAfx.obj"
	-@erase ".\Release\VListBox.obj"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/LBSmpl.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /c\
 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/LBSmpl.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/LBSmpl.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/LBSmpl.pdb" /machine:I386 /out:"$(OUTDIR)/LBSmpl.exe" 
LINK32_OBJS= \
	".\Release\LBDlg.obj" \
	".\Release\LBSmpl.obj" \
	".\Release\LBSmpl.res" \
	".\Release\StdAfx.obj" \
	".\Release\VListBox.obj"

".\Release\LBSmpl.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "LBSmpl - Win32 Debug"

# PROP BASE Use_MFC 0
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

ALL : ".\Debug\LBSmpl.exe"

CLEAN : 
	-@erase ".\Debug\LBDlg.obj"
	-@erase ".\Debug\LBSmpl.exe"
	-@erase ".\Debug\LBSmpl.ilk"
	-@erase ".\Debug\LBSmpl.obj"
	-@erase ".\Debug\LBSmpl.pch"
	-@erase ".\Debug\LBSmpl.pdb"
	-@erase ".\Debug\LBSmpl.res"
	-@erase ".\Debug\StdAfx.obj"
	-@erase ".\Debug\vc40.idb"
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\VListBox.obj"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/LBSmpl.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/LBSmpl.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/LBSmpl.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/LBSmpl.pdb" /debug /machine:I386 /out:"$(OUTDIR)/LBSmpl.exe" 
LINK32_OBJS= \
	".\Debug\LBDlg.obj" \
	".\Debug\LBSmpl.obj" \
	".\Debug\LBSmpl.res" \
	".\Debug\StdAfx.obj" \
	".\Debug\VListBox.obj"

".\Debug\LBSmpl.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "LBSmpl - Win32 Release"
# Name "LBSmpl - Win32 Debug"

!IF  "$(CFG)" == "LBSmpl - Win32 Release"

!ELSEIF  "$(CFG)" == "LBSmpl - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\LBSmpl.rc
DEP_RSC_LBSMP=\
	".\LBSmpl.ico"\
	
NODEP_RSC_LBSMP=\
	".\res\LBSmpl.rc2"\
	

!IF  "$(CFG)" == "LBSmpl - Win32 Release"


".\Release\LBSmpl.res" : $(SOURCE) $(DEP_RSC_LBSMP) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "LBSmpl - Win32 Debug"


".\Debug\LBSmpl.res" : $(SOURCE) $(DEP_RSC_LBSMP) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\LBSmpl.cpp
DEP_CPP_LBSMPL=\
	".\LBDlg.h"\
	".\LBSmpl.h"\
	".\stdafx.h"\
	".\VListBox.h"\
	

!IF  "$(CFG)" == "LBSmpl - Win32 Release"


".\Release\LBSmpl.obj" : $(SOURCE) $(DEP_CPP_LBSMPL) "$(INTDIR)"\
 ".\Release\LBSmpl.pch"


!ELSEIF  "$(CFG)" == "LBSmpl - Win32 Debug"


".\Debug\LBSmpl.obj" : $(SOURCE) $(DEP_CPP_LBSMPL) "$(INTDIR)"\
 ".\Debug\LBSmpl.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\stdafx.h"\
	

!IF  "$(CFG)" == "LBSmpl - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/LBSmpl.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /c\
 $(SOURCE) \
	

".\Release\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

".\Release\LBSmpl.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "LBSmpl - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/LBSmpl.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE) \
	

".\Debug\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

".\Debug\LBSmpl.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\VListBox.cpp
DEP_CPP_VLIST=\
	".\LBSmpl.h"\
	".\stdafx.h"\
	".\VListBox.h"\
	

!IF  "$(CFG)" == "LBSmpl - Win32 Release"


".\Release\VListBox.obj" : $(SOURCE) $(DEP_CPP_VLIST) "$(INTDIR)"\
 ".\Release\LBSmpl.pch"


!ELSEIF  "$(CFG)" == "LBSmpl - Win32 Debug"


".\Debug\VListBox.obj" : $(SOURCE) $(DEP_CPP_VLIST) "$(INTDIR)"\
 ".\Debug\LBSmpl.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\LBDlg.cpp
DEP_CPP_LBDLG=\
	".\LBDlg.h"\
	".\LBSmpl.h"\
	".\stdafx.h"\
	".\VListBox.h"\
	

!IF  "$(CFG)" == "LBSmpl - Win32 Release"


".\Release\LBDlg.obj" : $(SOURCE) $(DEP_CPP_LBDLG) "$(INTDIR)"\
 ".\Release\LBSmpl.pch"


!ELSEIF  "$(CFG)" == "LBSmpl - Win32 Debug"


".\Debug\LBDlg.obj" : $(SOURCE) $(DEP_CPP_LBDLG) "$(INTDIR)"\
 ".\Debug\LBSmpl.pch"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
