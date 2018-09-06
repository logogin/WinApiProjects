# Microsoft Developer Studio Generated NMAKE File, Format Version 4.10
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=NoteDraw - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to NoteDraw - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "NoteDraw - Win32 Release" && "$(CFG)" !=\
 "NoteDraw - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Notedraw.mak" CFG="NoteDraw - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "NoteDraw - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "NoteDraw - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "NoteDraw - Win32 Debug"
RSC=rc.exe
MTL=mktyplib.exe
CPP=cl.exe

!IF  "$(CFG)" == "NoteDraw - Win32 Release"

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

ALL : "$(OUTDIR)\Notedraw.exe"

CLEAN : 
	-@erase "$(INTDIR)\ChildFrm.obj"
	-@erase "$(INTDIR)\DrawDoc.obj"
	-@erase "$(INTDIR)\DrawView.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\NoteDoc.obj"
	-@erase "$(INTDIR)\NoteDraw.obj"
	-@erase "$(INTDIR)\Notedraw.pch"
	-@erase "$(INTDIR)\NoteDraw.res"
	-@erase "$(INTDIR)\NoteView.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(OUTDIR)\Notedraw.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Notedraw.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/"\
 /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/NoteDraw.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Notedraw.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/Notedraw.pdb" /machine:I386 /out:"$(OUTDIR)/Notedraw.exe" 
LINK32_OBJS= \
	"$(INTDIR)\ChildFrm.obj" \
	"$(INTDIR)\DrawDoc.obj" \
	"$(INTDIR)\DrawView.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\NoteDoc.obj" \
	"$(INTDIR)\NoteDraw.obj" \
	"$(INTDIR)\NoteDraw.res" \
	"$(INTDIR)\NoteView.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\Notedraw.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "NoteDraw - Win32 Debug"

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

ALL : "$(OUTDIR)\Notedraw.exe"

CLEAN : 
	-@erase "$(INTDIR)\ChildFrm.obj"
	-@erase "$(INTDIR)\DrawDoc.obj"
	-@erase "$(INTDIR)\DrawView.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\NoteDoc.obj"
	-@erase "$(INTDIR)\NoteDraw.obj"
	-@erase "$(INTDIR)\Notedraw.pch"
	-@erase "$(INTDIR)\NoteDraw.res"
	-@erase "$(INTDIR)\NoteView.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\Notedraw.exe"
	-@erase "$(OUTDIR)\Notedraw.ilk"
	-@erase "$(OUTDIR)\Notedraw.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Notedraw.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/NoteDraw.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Notedraw.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/Notedraw.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/Notedraw.exe" 
LINK32_OBJS= \
	"$(INTDIR)\ChildFrm.obj" \
	"$(INTDIR)\DrawDoc.obj" \
	"$(INTDIR)\DrawView.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\NoteDoc.obj" \
	"$(INTDIR)\NoteDraw.obj" \
	"$(INTDIR)\NoteDraw.res" \
	"$(INTDIR)\NoteView.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\Notedraw.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "NoteDraw - Win32 Release"
# Name "NoteDraw - Win32 Debug"

!IF  "$(CFG)" == "NoteDraw - Win32 Release"

!ELSEIF  "$(CFG)" == "NoteDraw - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\NoteDraw.cpp
DEP_CPP_NOTED=\
	".\ChildFrm.h"\
	".\DrawDoc.h"\
	".\DrawView.h"\
	".\MainFrm.h"\
	".\NoteDoc.h"\
	".\NoteDraw.h"\
	".\NoteView.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\NoteDraw.obj" : $(SOURCE) $(DEP_CPP_NOTED) "$(INTDIR)"\
 "$(INTDIR)\Notedraw.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "NoteDraw - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Notedraw.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/"\
 /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Notedraw.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "NoteDraw - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Notedraw.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Notedraw.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MainFrm.cpp
DEP_CPP_MAINF=\
	".\MainFrm.h"\
	".\NoteDraw.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\Notedraw.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\ChildFrm.cpp
DEP_CPP_CHILD=\
	".\ChildFrm.h"\
	".\DrawDoc.h"\
	".\DrawView.h"\
	".\MainFrm.h"\
	".\NoteDoc.h"\
	".\NoteDraw.h"\
	".\NoteView.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\ChildFrm.obj" : $(SOURCE) $(DEP_CPP_CHILD) "$(INTDIR)"\
 "$(INTDIR)\Notedraw.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\NoteDoc.cpp
DEP_CPP_NOTEDO=\
	".\NoteDoc.h"\
	".\NoteDraw.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\NoteDoc.obj" : $(SOURCE) $(DEP_CPP_NOTEDO) "$(INTDIR)"\
 "$(INTDIR)\Notedraw.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\NoteView.cpp
DEP_CPP_NOTEV=\
	".\NoteDoc.h"\
	".\NoteDraw.h"\
	".\NoteView.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\NoteView.obj" : $(SOURCE) $(DEP_CPP_NOTEV) "$(INTDIR)"\
 "$(INTDIR)\Notedraw.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\NoteDraw.rc
DEP_RSC_NOTEDR=\
	".\DrawDoc.ico"\
	".\NoteDoc.ico"\
	".\NoteDraw.ico"\
	".\NoteDraw.rc2"\
	".\Toolbar.bmp"\
	

"$(INTDIR)\NoteDraw.res" : $(SOURCE) $(DEP_RSC_NOTEDR) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DrawDoc.cpp
DEP_CPP_DRAWD=\
	".\DrawDoc.h"\
	".\NoteDraw.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\DrawDoc.obj" : $(SOURCE) $(DEP_CPP_DRAWD) "$(INTDIR)"\
 "$(INTDIR)\Notedraw.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DrawView.cpp
DEP_CPP_DRAWV=\
	".\DrawDoc.h"\
	".\DrawView.h"\
	".\NoteDraw.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\DrawView.obj" : $(SOURCE) $(DEP_CPP_DRAWV) "$(INTDIR)"\
 "$(INTDIR)\Notedraw.pch"


# End Source File
# End Target
# End Project
################################################################################
