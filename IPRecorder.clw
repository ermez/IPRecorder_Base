; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CExitPwdDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "iprecorder.h"
LastPage=0

ClassCount=4
Class1=CIPRecorderApp
Class2=CAboutDlg
Class3=CIPRecorderDlg

ResourceCount=4
Resource1=IDD_ABOUTBOX
Resource2=IDD_IPRECORDER_DIALOG
Resource3=IDD_DIALOGExitConfirm
Class4=CExitPwdDlg
Resource4=IDR_MENU1

[CLS:CIPRecorderApp]
Type=0
BaseClass=CWinApp
HeaderFile=IPRecorder.h
ImplementationFile=IPRecorder.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=IPRecorderDlg.cpp
ImplementationFile=IPRecorderDlg.cpp

[CLS:CIPRecorderDlg]
Type=0
BaseClass=CDialog
HeaderFile=IPRecorderDlg.h
ImplementationFile=IPRecorderDlg.cpp
Filter=D
VirtualFilter=dWC
LastObject=CIPRecorderDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_IPRECORDER_DIALOG]
Type=1
Class=CIPRecorderDlg
ControlCount=50
Control1=IDC_STATIC,static,1342308352
Control2=IDC_RADIO1,button,1342308361
Control3=IDC_RADIO2,button,1342177289
Control4=IDC_RADIO3,button,1342177289
Control5=IDC_RADIO4,button,1342177289
Control6=IDC_RADIO5,button,1342177289
Control7=IDC_RADIO6,button,1342177289
Control8=IDC_RADIO7,button,1342177289
Control9=IDC_RADIO8,button,1342177289
Control10=IDC_RADIO9,button,1342177289
Control11=IDC_RADIO10,button,1342177289
Control12=IDC_STATIC,static,1342308352
Control13=IDC_COMBO_SLAVERID,combobox,1344340226
Control14=IDC_STATIC,static,1342308352
Control15=IDC_EDIT_IP,edit,1350633600
Control16=IDC_STATIC,static,1342308352
Control17=IDC_EDIT_PORT,edit,1350633600
Control18=IDC_STATIC,static,1342308352
Control19=IDC_EDIT_RUNNINGSTATE,edit,1350633600
Control20=IDC_STATIC,static,1342308352
Control21=IDC_EDIT_THREADPAIRS,edit,1350633600
Control22=IDC_STATIC,static,1342308352
Control23=IDC_EDIT_TOTALRESOURCES,edit,1350633600
Control24=IDC_STATIC,static,1342308352
Control25=IDC_STATIC,static,1342308352
Control26=IDC_EDIT_INIT_THREADPAIRS,edit,1484849280
Control27=IDC_STATIC,static,1342308352
Control28=IDC_EDIT_INIT_TOTALRESOURCES,edit,1484849280
Control29=IDC_CHECK_SHOWEVENT,button,1342242819
Control30=IDC_CHECK_AUTOCLEAREVENT,button,1342242819
Control31=IDC_BUTTON_CLEAREVENT,button,1342242816
Control32=IDC_BUTTON_CLEARERROR,button,1342242816
Control33=IDC_BUTTON_STARTSLAVER,button,1342242816
Control34=IDC_BUTTON_CLOSESLAVER,button,1342242816
Control35=IDC_LIST1,SysListView32,1350631425
Control36=IDC_EDIT_USEDRESOURCES,edit,1350633600
Control37=IDC_TREE_EVENTDISPLAY,SysTreeView32,1350631431
Control38=IDC_TREE_ERRDISPLAY,SysTreeView32,1350631424
Control39=IDC_STATIC,static,1342308352
Control40=IDC_STATIC,static,1342308352
Control41=IDC_EDIT_TOTALSTATISTICS,edit,1350633600
Control42=IDC_STATIC,static,1342308352
Control43=IDC_BUTTON_FOLDERSELECT,button,1342242816
Control44=IDC_EDIT_SELECTEDFOLDER,edit,1350631552
Control45=IDC_CHECK_REC_SAME,button,1342242819
Control46=IDC_STATIC,static,1342308352
Control47=IDC_EDITTOTALFILE,edit,1350641792
Control48=IDC_STATIC,static,1342308352
Control49=IDC_EDITRECORDERROR,edit,1350641792
Control50=IDC_BUTTONExitIPR,button,1342242816

[MNU:IDR_MENU1]
Type=1
Class=?
Command1=ID_MENUITEM32773
CommandCount=1

[DLG:IDD_DIALOGExitConfirm]
Type=1
Class=CExitPwdDlg
ControlCount=4
Control1=IDC_STATIC,static,1342308352
Control2=IDC_EDITExitPwd,edit,1350631552
Control3=IDC_BUTTONConfirmPwd,button,1342242816
Control4=IDC_BUTTONCancel,button,1342242816

[CLS:CExitPwdDlg]
Type=0
HeaderFile=ExitPwdDlg.h
ImplementationFile=ExitPwdDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_EDITExitPwd

