; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=uLoad
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "utetris.h"
LastPage=0

ClassCount=5
Class1=SDialog
Class2=CMainWindow

ResourceCount=6
Resource1=IDA_TABLE
Resource2=IDM_MENU
Resource3=IDD_LOAD
Class3=uOptions
Resource4=IDD_SAVE
Class4=uSave
Resource5=IDD_ABOUTBOX
Class5=uLoad
Resource6=IDD_GAMEOPTIONS

[CLS:SDialog]
Type=0
BaseClass=CDialog
HeaderFile=SDialog.h
ImplementationFile=SDialog.cpp

[CLS:CMainWindow]
Type=0
BaseClass=CFrameWnd
HeaderFile=uTetris.h
ImplementationFile=uTetris.cpp
LastObject=CMainWindow

[DLG:IDD_SDIALOG]
Type=1
Class=SDialog

[MNU:IDM_MENU]
Type=1
Class=?
Command1=ID_NEWGAME
Command2=ID_LOADGAME
Command3=ID_SAVEGAME
Command4=ID_OPTIONS
Command5=ID_EXIT
Command6=ID_PAUSE
Command7=ID_APP_ABOUT
CommandCount=7

[ACL:IDA_TABLE]
Type=1
Class=?
Command1=ID_PAUSE
Command2=ID_EXIT
Command3=ID_APP_ABOUT
Command4=ID_NEWGAME
Command5=ID_LOADGAME
Command6=ID_SAVEGAME
Command7=ID_OPTIONS
CommandCount=7

[DLG:IDD_ABOUTBOX]
Type=1
Class=?
ControlCount=4
Control1=IDOK,button,1342373889
Control2=IDC_STATIC,static,1342308353
Control3=IDC_STATIC,static,1342308353
Control4=IDC_STATIC,static,1342177294

[CLS:uOptions]
Type=0
HeaderFile=uOptions.h
ImplementationFile=uOptions.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_NEXTSHAPEEDIT

[DLG:IDD_GAMEOPTIONS]
Type=1
Class=uOptions
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,button,1342210055
Control4=IDC_SPEEDEDIT,edit,1350631552
Control5=IDC_STATIC,button,1342210055
Control6=IDC_NEXTSHAPEEDIT,edit,1350631552

[DLG:IDD_SAVE]
Type=1
Class=uSave
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDC_FILENAMEEDIT,edit,1350631552
Control3=IDC_STATIC,button,1342177287

[CLS:uSave]
Type=0
HeaderFile=uSave.h
ImplementationFile=uSave.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_FILENAMEEDIT

[DLG:IDD_LOAD]
Type=1
Class=uLoad
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDC_FILENAMEEDIT,edit,1350631552
Control3=IDC_STATIC,button,1342177287

[CLS:uLoad]
Type=0
HeaderFile=uLoad.h
ImplementationFile=uLoad.cpp
BaseClass=CDialog
Filter=D

