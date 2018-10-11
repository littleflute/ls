; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CLSView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "LS.h"
LastPage=0

ClassCount=7
Class1=CLSApp
Class2=CLSDoc
Class3=CLSView
Class4=CMainFrame

ResourceCount=4
Resource1=IDD_ABOUTBOX
Class5=CAboutDlg
Resource2=IDR_MAINFRAME
Class6=CXDScriptDlg
Resource3=IDD_DLG_SCRIPT
Class7=CDlgKBMidi
Resource4=IDD_DLG_KBMIDI

[CLS:CLSApp]
Type=0
HeaderFile=LS.h
ImplementationFile=LS.cpp
Filter=N
LastObject=CLSApp
BaseClass=CWinApp
VirtualFilter=AC

[CLS:CLSDoc]
Type=0
HeaderFile=LSDoc.h
ImplementationFile=LSDoc.cpp
Filter=N
BaseClass=CDocument
VirtualFilter=DC
LastObject=CLSDoc

[CLS:CLSView]
Type=0
HeaderFile=LSView.h
ImplementationFile=LSView.cpp
Filter=C
BaseClass=CScrollView
VirtualFilter=VWC
LastObject=ID_BMP_SAVE


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=CMainFrame
BaseClass=CFrameWnd
VirtualFilter=fWC




[CLS:CAboutDlg]
Type=0
HeaderFile=LS.cpp
ImplementationFile=LS.cpp
Filter=D
LastObject=CAboutDlg
BaseClass=CDialog
VirtualFilter=dWC

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=8
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_BUTTON_TIMER,button,1342242816
Control6=IDC_STATIC_TIMER3,static,1342312448
Control7=IDC_STATIC_TIMER,static,1342312448
Control8=IDC_STATIC_TIMER2,static,1342312448

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_SAVE_AS_HTML
Command6=ID_BMP_SAVE
Command7=ID_FILE_PRINT
Command8=ID_FILE_PRINT_PREVIEW
Command9=ID_FILE_PRINT_SETUP
Command10=ID_FILE_MRU_FILE1
Command11=ID_APP_EXIT
Command12=ID_EDIT_UNDO
Command13=ID_EDIT_CUT
Command14=ID_EDIT_COPY
Command15=ID_EDIT_PASTE
Command16=ID_VIEW_TOOLBAR
Command17=ID_VIEW_STATUS_BAR
Command18=ID_VIEW_FONT
Command19=ID_APP_ABOUT
Command20=ID_XDTOOLS_KBMIDI
Command21=ID_XDTOOLS_TEST
CommandCount=21

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
Command9=ID_XD_NOTE
Command10=ID_XD_LYRICS
Command11=ID_XD_LYRICS_SCRIPT
CommandCount=11

[DLG:IDD_DLG_SCRIPT]
Type=1
Class=CXDScriptDlg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT_SCRIPT,edit,1353781444

[CLS:CXDScriptDlg]
Type=0
HeaderFile=XDScriptDlg.h
ImplementationFile=XDScriptDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CXDScriptDlg
VirtualFilter=dWC

[DLG:IDD_DLG_KBMIDI]
Type=1
Class=CDlgKBMidi
ControlCount=0

[CLS:CDlgKBMidi]
Type=0
HeaderFile=DlgKBMidi.h
ImplementationFile=DlgKBMidi.cpp
BaseClass=CDialog
Filter=D
LastObject=CDlgKBMidi
VirtualFilter=dWC

