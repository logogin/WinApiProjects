# Microsoft Developer Studio Generated NMAKE File, Format Version 4.10
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=CheckBox - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to CheckBox - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "CheckBox - Win32 Release" && "$(CFG)" !=\
 "CheckBox - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "CheckBox.mak" CFG="CheckBox - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "CheckBox - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "CheckBox - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "CheckBox - Win32 Release"
RSC=rc.exe
MTL=mktyplib.exe
CPP=cl.exe

!IF  "$(CFG)" == "CheckBox - Win32 Release"

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

ALL : ".\Release\CheckBox.exe"

CLEAN : 
	-@erase ".\Release\CheckBox.exe"
	-@erase ".\Release\CheckBox.obj"
	-@erase ".\Release\CheckBox.pch"
	-@erase ".\Release\CheckBox.res"
	-@erase ".\Release\CheckBoxDlg.obj"
	-@erase ".\Release\ColorBox.obj"
	-@erase ".\Release\StdAfx.obj"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/CheckBox.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/"\
 /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/CheckBox.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/CheckBox.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/CheckBox.pdb" /machine:I386 /out:"$(OUTDIR)/CheckBox.exe" 
LINK32_OBJS= \
	".\Release\CheckBox.obj" \
	".\Release\CheckBox.res" \
	".\Release\CheckBoxDlg.obj" \
	".\Release\ColorBox.obj" \
	".\Release\StdAfx.obj"

".\Release\CheckBox.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "CheckBox - Win32 Debug"

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

ALL : ".\Debug\CheckBox.exe"

CLEAN : 
	-@erase ".\Debug\CheckBox.exe"
	-@erase ".\Debug\CheckBox.ilk"
	-@erase ".\Debug\CheckBox.obj"
	-@erase ".\Debug\CheckBox.pch"
	-@erase ".\Debug\CheckBox.pdb"
	-@erase ".\Debug\CheckBox.res"
	-@erase ".\Debug\CheckBoxDlg.obj"
	-@erase ".\Debug\ColorBox.obj"
	-@erase ".\Debug\StdAfx.obj"
	-@erase ".\Debug\vc40.idb"
	-@erase ".\Debug\vc40.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/CheckBox.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/CheckBox.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/CheckBox.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/CheckBox.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/CheckBox.exe" 
LINK32_OBJS= \
	".\Debug\CheckBox.obj" \
	".\Debug\CheckBox.res" \
	".\Debug\CheckBoxDlg.obj" \
	".\Debug\ColorBox.obj" \
	".\Debug\StdAfx.obj"

".\Debug\CheckBox.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "CheckBox - Win32 Release"
# Name "CheckBox - Win32 Debug"

!IF  "$(CFG)" == "CheckBox - Win32 Release"

!ELSEIF  "$(CFG)" == "CheckBox - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\ReadMe.txt

!IF  "$(CFG)" == "CheckBox - Win32 Release"

!ELSEIF  "$(CFG)" == "CheckBox - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CheckBox.cpp

!IF  "$(CFG)" == "CheckBox - Win32 Release"

DEP_CPP_CHECK=\
	".\CheckBox.h"\
	".\CheckBoxDlg.h"\
	".\ColorBox.h"\
	".\StdAfx.h"\
	

".\Release\CheckBox.obj" : $(SOURCE) $(DEP_CPP_CHECK) "$(INTDIR)"\
 ".\Release\CheckBox.pch"


!ELSEIF  "$(CFG)" == "CheckBox - Win32 Debug"

DEP_CPP_CHECK=\
	".\CheckBox.h"\
	".\CheckBoxDlg.h"\
	".\StdAfx.h"\
	

".\Debug\CheckBox.obj" : $(SOURCE) $(DEP_CPP_CHECK) "$(INTDIR)"\
 ".\Debug\CheckBox.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CheckBoxDlg.cpp
DEP_CPP_CHECKB=\
	".\CheckBox.h"\
	".\CheckBoxDlg.h"\
	".\ColorBox.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "CheckBox - Win32 Release"


".\Release\CheckBoxDlg.obj" : $(SOURCE) $(DEP_CPP_CHECKB) "$(INTDIR)"\
 ".\Release\CheckBox.pch"


!ELSEIF  "$(CFG)" == "CheckBox - Win32 Debug"


".\Debug\CheckBoxDlg.obj" : $(SOURCE) $(DEP_CPP_CHECKB) "$(INTDIR)"\
 ".\Debug\CheckBox.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "CheckBox - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/CheckBox.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/"\
 /c $(SOURCE) \
	

".\Release\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

".\Release\CheckBox.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "CheckBox - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/CheckBox.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

".\Debug\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

".\Debug\CheckBox.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CheckBox.rc

!IF  "$(CFG)" == "CheckBox - Win32 Release"

DEP_RSC_CHECKBO=\
	".\CheckBox.ico"\
	".\CheckBox.rc2"\
	

".\Release\CheckBox.res" : $(SOURCE) $(DEP_RSC_CHECKBO) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CheckBox - Win32 Debug"

DEP_RSC_CHECKBO=\
	".\res\CheckBox.ico"\
	".\res\CheckBox.rc2"\
	

".\Debug\CheckBox.res" : $(SOURCE) $(DEP_RSC_CHECKBO) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ColorBox.cpp
DEP_CPP_COLOR=\
	".\CheckBox.h"\
	".\ColorBox.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "CheckBox - Win32 Release"


".\Release\ColorBox.obj" : $(SOURCE) $(DEP_CPP_COLOR) "$(INTDIR)"\
 ".\Release\CheckBox.pch"


!ELSEIF  "$(CFG)" == "CheckBox - Win32 Debug"


".\Debug\ColorBox.obj" : $(SOURCE) $(DEP_CPP_COLOR) "$(INTDIR)"\
 ".\Debug\CheckBox.pch"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
