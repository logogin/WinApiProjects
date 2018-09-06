# Microsoft Developer Studio Generated NMAKE File, Format Version 4.10
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=Child - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Child - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Parent - Win32 Release" && "$(CFG)" != "Parent - Win32 Debug"\
 && "$(CFG)" != "Child - Win32 Release" && "$(CFG)" != "Child - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Parent.mak" CFG="Child - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Parent - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Parent - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "Child - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Child - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "Child - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "Parent - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Intermediate\Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Intermediate\Release

ALL : "Child - Win32 Release" "$(OUTDIR)\Parent.exe"

CLEAN : 
	-@erase "$(INTDIR)\Parent.obj"
	-@erase "$(INTDIR)\Parent.pch"
	-@erase "$(INTDIR)\Parent.res"
	-@erase "$(INTDIR)\ParentDlg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(OUTDIR)\Parent.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Parent.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /c\
 
CPP_OBJS=.\Intermediate\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x419 /fo"$(INTDIR)/Parent.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Parent.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/Parent.pdb" /machine:I386 /out:"$(OUTDIR)/Parent.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Parent.obj" \
	"$(INTDIR)\Parent.res" \
	"$(INTDIR)\ParentDlg.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\Parent.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Parent - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Intermediate\Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Intermediate\Debug

ALL : "Child - Win32 Debug" "$(OUTDIR)\Parent.exe"

CLEAN : 
	-@erase "$(INTDIR)\Parent.obj"
	-@erase "$(INTDIR)\Parent.pch"
	-@erase "$(INTDIR)\Parent.res"
	-@erase "$(INTDIR)\ParentDlg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\Parent.exe"
	-@erase "$(OUTDIR)\Parent.ilk"
	-@erase "$(OUTDIR)\Parent.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Parent.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Intermediate\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x419 /fo"$(INTDIR)/Parent.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Parent.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/Parent.pdb" /debug /machine:I386 /out:"$(OUTDIR)/Parent.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Parent.obj" \
	"$(INTDIR)\Parent.res" \
	"$(INTDIR)\ParentDlg.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\Parent.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Child - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Child\Release"
# PROP BASE Intermediate_Dir "Child\Release"
# PROP BASE Target_Dir "Child"
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Intermediate\Child\Release"
# PROP Target_Dir "Child"
OUTDIR=.\Release
INTDIR=.\Intermediate\Child\Release

ALL : "$(OUTDIR)\Child.exe"

CLEAN : 
	-@erase "$(INTDIR)\Child.obj"
	-@erase "$(INTDIR)\Child.pch"
	-@erase "$(INTDIR)\Child.res"
	-@erase "$(INTDIR)\ChildDlg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(OUTDIR)\Child.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Child.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Intermediate\Child\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x419 /fo"$(INTDIR)/Child.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Child.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/Child.pdb" /machine:I386 /out:"$(OUTDIR)/Child.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Child.obj" \
	"$(INTDIR)\Child.res" \
	"$(INTDIR)\ChildDlg.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\Child.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Child - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Child\Debug"
# PROP BASE Intermediate_Dir "Child\Debug"
# PROP BASE Target_Dir "Child"
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Intermediate\Child\Debug"
# PROP Target_Dir "Child"
OUTDIR=.\Debug
INTDIR=.\Intermediate\Child\Debug

ALL : "$(OUTDIR)\Child.exe"

CLEAN : 
	-@erase "$(INTDIR)\Child.obj"
	-@erase "$(INTDIR)\Child.pch"
	-@erase "$(INTDIR)\Child.res"
	-@erase "$(INTDIR)\ChildDlg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\Child.exe"
	-@erase "$(OUTDIR)\Child.ilk"
	-@erase "$(OUTDIR)\Child.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Child.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Intermediate\Child\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x419 /fo"$(INTDIR)/Child.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Child.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/Child.pdb" /debug /machine:I386 /out:"$(OUTDIR)/Child.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Child.obj" \
	"$(INTDIR)\Child.res" \
	"$(INTDIR)\ChildDlg.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\Child.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "Parent - Win32 Release"
# Name "Parent - Win32 Debug"

!IF  "$(CFG)" == "Parent - Win32 Release"

!ELSEIF  "$(CFG)" == "Parent - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\ReadMe.txt

!IF  "$(CFG)" == "Parent - Win32 Release"

!ELSEIF  "$(CFG)" == "Parent - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Parent.cpp
DEP_CPP_PAREN=\
	".\Parent.h"\
	".\ParentDlg.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\Parent.obj" : $(SOURCE) $(DEP_CPP_PAREN) "$(INTDIR)"\
 "$(INTDIR)\Parent.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\ParentDlg.cpp
DEP_CPP_PARENT=\
	".\Parent.h"\
	".\ParentDlg.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\ParentDlg.obj" : $(SOURCE) $(DEP_CPP_PARENT) "$(INTDIR)"\
 "$(INTDIR)\Parent.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "Parent - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Parent.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Parent.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Parent - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Parent.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Parent.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Parent.rc
DEP_RSC_PARENT_=\
	".\res\Parent.ico"\
	".\res\Parent.rc2"\
	

"$(INTDIR)\Parent.res" : $(SOURCE) $(DEP_RSC_PARENT_) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Project Dependency

# Project_Dep_Name "Child"

!IF  "$(CFG)" == "Parent - Win32 Release"

"Child - Win32 Release" : 
   $(MAKE) /$(MAKEFLAGS) /F ".\Parent.mak" CFG="Child - Win32 Release" 

!ELSEIF  "$(CFG)" == "Parent - Win32 Debug"

"Child - Win32 Debug" : 
   $(MAKE) /$(MAKEFLAGS) /F ".\Parent.mak" CFG="Child - Win32 Debug" 

!ENDIF 

# End Project Dependency
# End Target
################################################################################
# Begin Target

# Name "Child - Win32 Release"
# Name "Child - Win32 Debug"

!IF  "$(CFG)" == "Child - Win32 Release"

!ELSEIF  "$(CFG)" == "Child - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\Child\ReadMe.txt

!IF  "$(CFG)" == "Child - Win32 Release"

!ELSEIF  "$(CFG)" == "Child - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Child\Child.cpp

!IF  "$(CFG)" == "Child - Win32 Release"

DEP_CPP_CHILD=\
	".\Child\Child.h"\
	".\Child\ChildDlg.h"\
	".\Child\StdAfx.h"\
	

"$(INTDIR)\Child.obj" : $(SOURCE) $(DEP_CPP_CHILD) "$(INTDIR)"\
 "$(INTDIR)\Child.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Child - Win32 Debug"

DEP_CPP_CHILD=\
	".\Child\Child.h"\
	".\Child\ChildDlg.h"\
	".\Child\StdAfx.h"\
	

"$(INTDIR)\Child.obj" : $(SOURCE) $(DEP_CPP_CHILD) "$(INTDIR)"\
 "$(INTDIR)\Child.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Child\ChildDlg.cpp

!IF  "$(CFG)" == "Child - Win32 Release"

DEP_CPP_CHILDD=\
	".\Child\Child.h"\
	".\Child\ChildDlg.h"\
	".\Child\StdAfx.h"\
	

"$(INTDIR)\ChildDlg.obj" : $(SOURCE) $(DEP_CPP_CHILDD) "$(INTDIR)"\
 "$(INTDIR)\Child.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Child - Win32 Debug"

DEP_CPP_CHILDD=\
	".\Child\Child.h"\
	".\Child\ChildDlg.h"\
	".\Child\StdAfx.h"\
	

"$(INTDIR)\ChildDlg.obj" : $(SOURCE) $(DEP_CPP_CHILDD) "$(INTDIR)"\
 "$(INTDIR)\Child.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Child\StdAfx.cpp
DEP_CPP_STDAF=\
	".\Child\StdAfx.h"\
	

!IF  "$(CFG)" == "Child - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Child.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Child.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Child - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Child.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Child.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Child\Child.rc
DEP_RSC_CHILD_=\
	".\Child\res\Child.ico"\
	".\Child\res\Child.rc2"\
	

!IF  "$(CFG)" == "Child - Win32 Release"


"$(INTDIR)\Child.res" : $(SOURCE) $(DEP_RSC_CHILD_) "$(INTDIR)"
   $(RSC) /l 0x419 /fo"$(INTDIR)/Child.res" /i "Child" /d "NDEBUG" /d "_AFXDLL"\
 $(SOURCE)


!ELSEIF  "$(CFG)" == "Child - Win32 Debug"


"$(INTDIR)\Child.res" : $(SOURCE) $(DEP_RSC_CHILD_) "$(INTDIR)"
   $(RSC) /l 0x419 /fo"$(INTDIR)/Child.res" /i "Child" /d "_DEBUG" /d "_AFXDLL"\
 $(SOURCE)


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
