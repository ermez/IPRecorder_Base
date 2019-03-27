// IPRecorderDlg.cpp : implementation file
//

#include "stdafx.h"
#include "IPRecorder.h"
#include "IPRecorderDlg.h"
#include "winsock2.h"
#include "ExitPwdDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

int g_dwLanguageID = 0;

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIPRecorderDlg dialog

CIPRecorderDlg::CIPRecorderDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIPRecorderDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CIPRecorderDlg)
	m_strIP = _T("");
	m_strPort = _T("");
	m_nInitThreadPairs = 0;
	m_nInitTotalResources = 0;
	m_nThreadPairs = 0;
	m_nTotalResources = 0;
	m_nUsedResources = 0;
	m_szSlaverState = _T("");
	m_bShowEvent = FALSE;
	m_bAutoClearEvent = TRUE;
	m_nRecCodec = 0;
	m_lTotalStatistics = 0;
	m_strSelectedFolder = _T("E:\\RECORDERFILES");
	m_bRecOverWrite = FALSE;
	m_nTotalFile = 0;
	m_nRecordError = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	IsWork = FALSE;
}

void CIPRecorderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIPRecorderDlg)
	DDX_Control(pDX, IDC_TREE_ERRDISPLAY, m_TreeCtrlErrDisplay);
	DDX_Control(pDX, IDC_TREE_EVENTDISPLAY, m_TreeCtrlEventDisplay);
	DDX_Control(pDX, IDC_COMBO_SLAVERID, m_cbSlaverID);
	DDX_Control(pDX, IDC_LIST1, m_ChannelList);
	DDX_Text(pDX, IDC_EDIT_IP, m_strIP);
	DDX_Text(pDX, IDC_EDIT_PORT, m_strPort);
	DDX_Text(pDX, IDC_EDIT_INIT_THREADPAIRS, m_nInitThreadPairs);
	DDX_Text(pDX, IDC_EDIT_INIT_TOTALRESOURCES, m_nInitTotalResources);
	DDX_Text(pDX, IDC_EDIT_THREADPAIRS, m_nThreadPairs);
	DDX_Text(pDX, IDC_EDIT_TOTALRESOURCES, m_nTotalResources);
	DDX_Text(pDX, IDC_EDIT_USEDRESOURCES, m_nUsedResources);
	DDX_Text(pDX, IDC_EDIT_RUNNINGSTATE, m_szSlaverState);
	DDX_Check(pDX, IDC_CHECK_SHOWEVENT, m_bShowEvent);
	DDX_Check(pDX, IDC_CHECK_AUTOCLEAREVENT, m_bAutoClearEvent);
	DDX_Radio(pDX, IDC_RADIO1, m_nRecCodec);
	DDX_Text(pDX, IDC_EDIT_TOTALSTATISTICS, m_lTotalStatistics);
	DDX_Text(pDX, IDC_EDIT_SELECTEDFOLDER, m_strSelectedFolder);
	DDX_Check(pDX, IDC_CHECK_REC_SAME, m_bRecOverWrite);
	DDX_Text(pDX, IDC_EDITTOTALFILE, m_nTotalFile);
	DDX_Text(pDX, IDC_EDITRECORDERROR, m_nRecordError);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CIPRecorderDlg, CDialog)
	//{{AFX_MSG_MAP(CIPRecorderDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_STARTSLAVER, OnButtonStartslaver)
	ON_BN_CLICKED(IDC_BUTTON_CLOSESLAVER, OnButtonCloseslaver)
	ON_CBN_SELCHANGE(IDC_COMBO_SLAVERID, OnSelchangeComboSlaverid)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CHECK_SHOWEVENT, OnCheckShowevent)
	ON_BN_CLICKED(IDC_BUTTON_CLEAREVENT, OnButtonClearevent)
	ON_BN_CLICKED(IDC_CHECK_AUTOCLEAREVENT, OnCheckAutoclearevent)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_BN_CLICKED(IDC_RADIO3, OnRadio3)
	ON_BN_CLICKED(IDC_RADIO4, OnRadio4)
	ON_BN_CLICKED(IDC_RADIO5, OnRadio5)
	ON_BN_CLICKED(IDC_RADIO6, OnRadio6)
	ON_BN_CLICKED(IDC_RADIO7, OnRadio7)
	ON_BN_CLICKED(IDC_RADIO8, OnRadio8)
	ON_BN_CLICKED(IDC_RADIO9, OnRadio9)
	ON_BN_CLICKED(IDC_RADIO10, OnRadio10)
	ON_BN_CLICKED(IDC_BUTTON_CLEARERROR, OnButtonClearerror)
	ON_BN_CLICKED(IDC_BUTTON_FOLDERSELECT, OnButtonFolderselect)
	ON_WM_HSCROLL()
	ON_WM_SIZE()
	ON_WM_VSCROLL()
	ON_BN_CLICKED(IDC_CHECK_REC_SAME, OnCheckRecSame)
	ON_EN_CHANGE(IDC_EDIT_INIT_THREADPAIRS, OnChangeEditInitThreadpairs)
	ON_EN_CHANGE(IDC_EDIT_INIT_TOTALRESOURCES, OnChangeEditInitTotalresources)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTONExitIPR, OnBUTTONExitIPR)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIPRecorderDlg message handlers

BOOL CIPRecorderDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	if(InitCtiSystem() == FALSE)
	{
		PostQuitMessage(0);
		return FALSE;
	}

	/*
	if(SsmGetInterEventType() != 1)
	{
		AfxMessageBox("Set EventInterfaceType=1 to ShConfig.ini file first!", MB_ICONWARNING, 0);
		PostQuitMessage(0);
		return FALSE;
	}*/


	int nTotalBoards;
	nTotalBoards = SsmGetMaxUsableBoard();
	nIPRBoardId = -1;
	for(int i=0; i < nTotalBoards; i++)
	{
		if(SsmGetBoardModel(i) == 0xfd)	//IPRecorder card type is 0xfd
		{
			nIPRBoardId = i;
			break;
		}
	}

	nIPABoardId = -1;
	for(i=0; i < nTotalBoards; i++)
	{
		if(SsmGetBoardModel(i) == 0xfe)	//IPAnalyzer card type is 0xfe
		{
			nIPABoardId = i;
			break;
		}
	}

	if(nIPRBoardId == -1)	//If not find IPRecorder card, show error message.
	{
		AfxMessageBox("No IPRecorder card, please check!", MB_OK, 0);
		return FALSE;
	}

	if(nIPABoardId == -1)	//If not find IPRecorder card, show error message.
	{
		AfxMessageBox("No IPAnalyzer card, please check!", MB_OK, 0);
		return FALSE;
	}

	InitChannelState();
	InitUI();

	nRecCodec = A_LAW;

	/*
	EVENT_SET_INFO EventMode;
	EventMode.dwWorkMode = EVENT_CALLBACKA;
	EventMode.lpHandlerParam = EventCallback;
	EventMode.dwUser = (DWORD)this;
	SsmSetEvent(0xffff,-1,true, &EventMode);
	*/

	//GetCurrentDirectory(MAX_PATH, (LPTSTR)szCurrentDir);
//	sprintf(szCurrentDir, "E:\\");
//	m_strSelectedFolder.Format("%s", szCurrentDir);
//	UpdateData(FALSE);

	SetTimer(1, 200, NULL);

	InitScroll();
	InitSuitSizeDialog();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CIPRecorderDlg::InitUI()
{
	InitChannelList();
}

int CIPRecorderDlg::EventCallback(PSSM_EVENT pEvent)
{
	BOOL bFind = FALSE;
	UCHAR uc;
	int i, nPtlType, nStationId, nSlaverId, nSlaverIndex;
	CIPRecorderDlg *pIPRecorderDlg = (CIPRecorderDlg *)pEvent->dwUser;
	char szEvtName[100], szIPP_Rec[50], szIPS_Rec[50], szErrMsgDisplay[500];
	pIPR_SessionInfo pSessionInfo;
	PIPR_CISCO_SCCP_CALL_INFO pSCCPInfo;
	PIPR_CALL_INFO pCallInfo;
	SYSTEMTIME time;

	pIPRecorderDlg->bErrorOccurred = FALSE;
	switch(pEvent->wEventCode)
	{
	case E_CHG_ChState:
		wsprintf(szEvtName, "E_CHG_ChState");
		pIPRecorderDlg->ChannelInfo[pEvent->nReference].nWorkState = SsmGetChState(pEvent->nReference);
		break;
	case E_RCV_IPR_DChannel:
		wsprintf(szEvtName, "E_RCV_IPR_DChannel - 0x%x", pEvent->dwParam);
		if(pEvent->dwParam == DE_CISCO_SCCP_CALL_INFO)
		{
			nPtlType = pEvent->dwXtraInfo >> 16;
			nStationId = pEvent->dwXtraInfo & 0xffff;
			pSCCPInfo = (PIPR_CISCO_SCCP_CALL_INFO)pEvent->pvBuffer;
			for(i=0; i<pIPRecorderDlg->MaxLine; i++)
			{
				if(pIPRecorderDlg->ChannelInfo[i].nPtlType == nPtlType && pIPRecorderDlg->ChannelInfo[i].nStationId == nStationId)
				{
					strcpy(pIPRecorderDlg->ChannelInfo[i].szCallerID, (char *)pSCCPInfo->CallingParty);
					strcpy(pIPRecorderDlg->ChannelInfo[i].szCalledID, (char *)pSCCPInfo->CalledParty);
					break;
				}
			}
		}
		else if(pEvent->dwParam >= DE_CALL_IN_PROGRESS && pEvent->dwParam <= DE_CALL_REJECTED)
		{
			nPtlType = pEvent->dwXtraInfo >> 16;
			nStationId = pEvent->dwXtraInfo & 0xffff;
			pCallInfo = (PIPR_CALL_INFO)pEvent->pvBuffer;
			bFind = FALSE;
			for(i=0; i<pIPRecorderDlg->MaxLine; i++)
			{
				if(pIPRecorderDlg->ChannelInfo[i].nChType == IPR_CH)
				{
					if(pIPRecorderDlg->ChannelInfo[i].nCallRef == pCallInfo->CallRef)
					{
						bFind = TRUE;
						if(pEvent->dwParam == DE_CALL_RELEASED || pEvent->dwParam == DE_CALL_SUSPENDED || pEvent->dwParam == DE_CALL_REJECTED || pEvent->dwParam == DE_CALL_ABANDONED)
						{
							pIPRecorderDlg->ChannelInfo[i].bCallActive = FALSE;
							if(pIPRecorderDlg->ChannelInfo[i].bRecording)
							{
								pIPRecorderDlg->ChannelInfo[i].nPtlType = -1;
								pIPRecorderDlg->ChannelInfo[i].nStationId = -1;
								pIPRecorderDlg->ChannelInfo[i].nRecSlaverId = -1;
								if(SsmIPRDeActiveAndStopRecToFile(i) != 0)
								{
									SsmGetLastErrMsg(pIPRecorderDlg->szErrMsg);
									GetLocalTime(&time);
									wsprintf(szErrMsgDisplay, "%02d/%02d/%d %02d:%02d:%02d.%03d: ch = %d, ", time.wMonth, time.wDay, time.wYear, 
										time.wHour, time.wMinute, time.wSecond, time.wMilliseconds, i);
									strcat(szErrMsgDisplay, pIPRecorderDlg->szErrMsg);
									pIPRecorderDlg->bErrorOccurred = TRUE;
									pIPRecorderDlg->m_nRecordError++;
								}
								pIPRecorderDlg->ChannelInfo[i].bRecording = FALSE;
							}
							pIPRecorderDlg->ChannelInfo[i].nCallRef = -1;
						}
						else
						{
							pIPRecorderDlg->ChannelInfo[i].bCallActive = TRUE;
						}
						break;
					}
				}
			}

			if(!bFind)
			{
				for(i=0; i<pIPRecorderDlg->MaxLine; i++)
				{
					if(pIPRecorderDlg->ChannelInfo[i].nChType == IPR_CH)
					{
						pIPRecorderDlg->ChannelInfo[i].nWorkState 
							= SsmGetChState(i);
						if(pIPRecorderDlg->ChannelInfo[i].nWorkState == S_CALL_STANDBY
							&& pIPRecorderDlg->ChannelInfo[i].bCallActive != TRUE)
						{
							if(pEvent->dwParam == DE_CALL_IN_PROGRESS || pEvent->dwParam == DE_CALL_ALERTING || pEvent->dwParam == DE_CALL_CONNECTED)
							{
								pIPRecorderDlg->ChannelInfo[i].bCallActive = TRUE;
								pIPRecorderDlg->ChannelInfo[i].nCallRef = pCallInfo->CallRef;
								pIPRecorderDlg->ChannelInfo[i].nPtlType = nPtlType;
								break;
							}
						}
					}
				}
			}
			
			if(pEvent->dwParam == DE_CALL_CONNECTED || pEvent->dwParam == DE_CALL_SUSPENDED || pEvent->dwParam == DE_CALL_RELEASED || pEvent->dwParam == DST_CALL_HELD)
			{
				for(i=0; i<pIPRecorderDlg->MaxLine; i++)
				{
					if(pIPRecorderDlg->ChannelInfo[i].nPtlType == nPtlType 
						&& pIPRecorderDlg->ChannelInfo[i].nCallRef == (int)pCallInfo->CallRef)
					{
						strcpy(pIPRecorderDlg->ChannelInfo[i].szCallerID, pCallInfo->szCallerId);
						strcpy(pIPRecorderDlg->ChannelInfo[i].szCalledID, pCallInfo->szCalledId);
						break;
					}
				}
			}
		}
		break;
	case E_RCV_IPR_DONGLE_ADDED:
		wsprintf(szEvtName, "E_RCV_IPR_DONGLE_ADDED");
		break;
	case E_RCV_IPR_DONGLE_REMOVED:
		wsprintf(szEvtName, "E_RCV_IPR_DONGLE_REMOVED");
		break;
	case E_RCV_IPA_DONGLE_ADDED:
		wsprintf(szEvtName, "E_RCV_IPA_DONGLE_ADDED");
		break;
	case E_RCV_IPA_DONGLE_REMOVED:
		wsprintf(szEvtName, "E_RCV_IPA_DONGLE_REMOVED");
		break;
	case E_RCV_IPA_APPLICATION_PENDING:
		wsprintf(szEvtName, "E_RCV_IPA_APPLICATION_PENDING");
		break;
	case E_RCV_IPR_STATION_ADDED:
		wsprintf(szEvtName, "E_RCV_IPR_STATION_ADDED");
		break;
	case E_RCV_IPR_STATION_REMOVED:
		wsprintf(szEvtName, "E_RCV_IPR_STATION_REMOVED");
		break;
	case E_RCV_IPR_AUTH_OVERFLOW:
		wsprintf(szEvtName, "E_RCV_IPR_AUTH_OVERFLOW");
		GetLocalTime(&time);
		wsprintf(szErrMsgDisplay, "%02d/%02d/%d %02d:%02d:%02d.%03d: authorization overflow, the call will not be recorded!", time.wMonth, time.wDay, time.wYear, 
			time.wHour, time.wMinute, time.wSecond, time.wMilliseconds);
		pIPRecorderDlg->bErrorOccurred = TRUE;
		pIPRecorderDlg->m_nRecordError++;
		break;
	case E_IPR_SLAVER_INIT_CB:
		wsprintf(szEvtName, "E_IPR_SLAVER_INIT_CB");;
		pIPRecorderDlg->ScanSlaver();
		pIPRecorderDlg->bSlaverConnectChanged = TRUE;
		pIPRecorderDlg->bUpdateSlaverDisplay = TRUE;
		break;
	case E_IPR_START_SLAVER_CB:
		wsprintf(szEvtName, "E_IPR_START_SLAVER_CB");
		pIPRecorderDlg->ScanSlaver();
		pIPRecorderDlg->bSlaverConnectChanged = TRUE;
		pIPRecorderDlg->bUpdateSlaverDisplay = TRUE;
		break;
	case E_IPR_CLOSE_SLAVER_CB:
		wsprintf(szEvtName, "E_IPR_CLOSE_SLAVER_CB");
		pIPRecorderDlg->ScanSlaver();
		pIPRecorderDlg->bSlaverConnectChanged = TRUE;
		pIPRecorderDlg->bUpdateSlaverDisplay = TRUE;
		break;
	case E_RCV_IPR_MEDIA_SESSION_STARTED:
		wsprintf(szEvtName, "E_RCV_IPR_MEDIA_SESSION_STARTED");
		pSessionInfo = (pIPR_SessionInfo)pEvent->pvBuffer;
		pIPRecorderDlg->ChannelInfo[pEvent->nReference].dwSessionId = pSessionInfo->dwSessionId;
		pIPRecorderDlg->m_lTotalStatistics++;
		pIPRecorderDlg->bUpdateSlaverDisplay = TRUE;

		pIPRecorderDlg->ScanSlaver();
		if(pIPRecorderDlg->nSlaverCount > 0)
		{
			bFind = FALSE;
			for(i=0; i<pIPRecorderDlg->MaxLine; i++)
			{
				if(pIPRecorderDlg->ChannelInfo[i].nChType == IPR_CH)
				{
//					pIPRecorderDlg->ChannelInfo[i].nWorkState 
//						= SsmGetChState(i);
//					if(pIPRecorderDlg->ChannelInfo[i].nWorkState == S_CALL_STANDBY)
					if(pIPRecorderDlg->ChannelInfo[i].nCallRef == pSessionInfo->nCallRef)
					{
//						wsprintf(pIPRecorderDlg->ChannelInfo[i].szCallerID, "");
//						wsprintf(pIPRecorderDlg->ChannelInfo[i].szCalledID, "");
						wsprintf(pIPRecorderDlg->ChannelInfo[i].szIPP, "");
						wsprintf(pIPRecorderDlg->ChannelInfo[i].szIPS, "");
						bFind = TRUE;
						break;
					}
				}
			}
			if(!bFind)
			{
				break;
			}

			wsprintf(pIPRecorderDlg->ChannelInfo[i].szIPP, "%d.%d.%d.%d", pSessionInfo->PrimaryAddr.S_un_b.s_b1, pSessionInfo->PrimaryAddr.S_un_b.s_b2, 
				pSessionInfo->PrimaryAddr.S_un_b.s_b3, pSessionInfo->PrimaryAddr.S_un_b.s_b4);
			wsprintf(pIPRecorderDlg->ChannelInfo[i].szIPS, "%d.%d.%d.%d", pSessionInfo->SecondaryAddr.S_un_b.s_b1, pSessionInfo->SecondaryAddr.S_un_b.s_b2, 
				pSessionInfo->SecondaryAddr.S_un_b.s_b3, pSessionInfo->SecondaryAddr.S_un_b.s_b4);

			GetLocalTime(&time);
			if (pIPRecorderDlg->m_bRecOverWrite)
			{
				wsprintf(pIPRecorderDlg->szRecFilePath, "%s\\ch%03d.mp3", pIPRecorderDlg->m_strSelectedFolder, i);
			}
			else
			{
//				wsprintf(pIPRecorderDlg->szRecFilePath, "%s\\recorderfiles\\%d_%02d_%02d_%02d\\ch%d_%02d_%02d_%02d_%03d(%d.%d.%d.%d-%d.%d.%d.%d).wav", pIPRecorderDlg->m_strSelectedFolder, 
//					time.wYear, time.wMonth, time.wDay, time.wHour, i, time.wHour, time.wMinute, time.wSecond, time.wMilliseconds,
//					pSessionInfo->PrimaryAddr.S_un_b.s_b1, pSessionInfo->PrimaryAddr.S_un_b.s_b2, pSessionInfo->PrimaryAddr.S_un_b.s_b3, pSessionInfo->PrimaryAddr.S_un_b.s_b4,
//					pSessionInfo->SecondaryAddr.S_un_b.s_b1, pSessionInfo->SecondaryAddr.S_un_b.s_b2, pSessionInfo->SecondaryAddr.S_un_b.s_b3, pSessionInfo->SecondaryAddr.S_un_b.s_b4);
				wsprintf(pIPRecorderDlg->szRecFilePath, "%s\\%02d%02d%04d-%02d%02d%02d%03d-%s-%s.wav", pIPRecorderDlg->m_strSelectedFolder, 
					time.wDay, time.wMonth, time.wYear, time.wHour, time.wMinute, time.wSecond,time.wMilliseconds,
					pIPRecorderDlg->ChannelInfo[i].szCallerID,pIPRecorderDlg->ChannelInfo[i].szCalledID);
			}
			nSlaverIndex = -1;
			for(int j=0; j<pIPRecorderDlg->nSlaverCount; j++)
			{
				if(pIPRecorderDlg->IPR_SlaverAddr[j].nTotalResources - pIPRecorderDlg->IPR_SlaverAddr[j].nUsedResources > 0)
				{
					nSlaverIndex = j;
					break;
				}
			}
			if(nSlaverIndex < 0)
				break;

			if(pIPRecorderDlg->ChannelInfo[i].bRecording == FALSE)
			{
				if(SsmIPRActiveAndRecToFile(i, pIPRecorderDlg->IPR_SlaverAddr[nSlaverIndex].nRecSlaverID, pSessionInfo->dwSessionId,
					pSessionInfo->nPrimaryCodec, &pSessionInfo->nFowardingPPort, &pSessionInfo->nFowardingSPort, 
					pIPRecorderDlg->szRecFilePath, pIPRecorderDlg->nRecCodec, 0, -1, -1, 0) != 0)
				{
					SsmGetLastErrMsg(pIPRecorderDlg->szErrMsg);
					wsprintf(szErrMsgDisplay, "%02d/%02d/%d %02d:%02d:%02d.%03d: ch = %d, ", time.wMonth, time.wDay, time.wYear, 
						time.wHour, time.wMinute, time.wSecond, time.wMilliseconds, i);
					strcat(szErrMsgDisplay, pIPRecorderDlg->szErrMsg);
					pIPRecorderDlg->bErrorOccurred = TRUE;
					pIPRecorderDlg->m_nRecordError++;
				}
				pIPRecorderDlg->ChannelInfo[i].bRecording = TRUE;
				pIPRecorderDlg->ChannelInfo[pEvent->nReference].nFowardingPPort = pSessionInfo->nFowardingPPort;
				pIPRecorderDlg->ChannelInfo[pEvent->nReference].nFowardingSPort = pSessionInfo->nFowardingSPort;
				pIPRecorderDlg->ChannelInfo[i].nFowardingPPort = pIPRecorderDlg->ChannelInfo[pEvent->nReference].nFowardingPPort;
				pIPRecorderDlg->ChannelInfo[i].nFowardingSPort = pIPRecorderDlg->ChannelInfo[pEvent->nReference].nFowardingSPort;
				pIPRecorderDlg->ChannelInfo[i].nRecSlaverId = pIPRecorderDlg->IPR_SlaverAddr[nSlaverIndex].nRecSlaverID;
				pIPRecorderDlg->ChannelInfo[i].nCallRef = pSessionInfo->nCallRef;
				pIPRecorderDlg->ChannelInfo[i].nPtlType = pEvent->dwXtraInfo >> 16;
				pIPRecorderDlg->ChannelInfo[i].nStationId = pEvent->dwXtraInfo & 0xffff;
			}
			else
			{
				wsprintf(szIPP_Rec, "%d.%d.%d.%d", pIPRecorderDlg->IPR_SlaverAddr[nSlaverIndex].ipAddr.S_un_b.s_b1, 
					pIPRecorderDlg->IPR_SlaverAddr[nSlaverIndex].ipAddr.S_un_b.s_b2, 
					pIPRecorderDlg->IPR_SlaverAddr[nSlaverIndex].ipAddr.S_un_b.s_b3, 
					pIPRecorderDlg->IPR_SlaverAddr[nSlaverIndex].ipAddr.S_un_b.s_b4);
				wsprintf(szIPS_Rec, "%d.%d.%d.%d", pIPRecorderDlg->IPR_SlaverAddr[nSlaverIndex].ipAddr.S_un_b.s_b1, 
					pIPRecorderDlg->IPR_SlaverAddr[nSlaverIndex].ipAddr.S_un_b.s_b2, 
					pIPRecorderDlg->IPR_SlaverAddr[nSlaverIndex].ipAddr.S_un_b.s_b3, 
					pIPRecorderDlg->IPR_SlaverAddr[nSlaverIndex].ipAddr.S_un_b.s_b4);
				if(SsmIPRSendSession(pEvent->nReference, szIPP_Rec, pIPRecorderDlg->ChannelInfo[i].nFowardingPPort, 
					szIPS_Rec, pIPRecorderDlg->ChannelInfo[i].nFowardingSPort) != 0)
				{
					SsmGetLastErrMsg(pIPRecorderDlg->szErrMsg);
					GetLocalTime(&time);
					wsprintf(szErrMsgDisplay, "%02d/%02d/%d %02d:%02d:%02d.%03d: ch = %d, ", time.wMonth, time.wDay, time.wYear, 
						time.wHour, time.wMinute, time.wSecond, time.wMilliseconds, i);
					strcat(szErrMsgDisplay, pIPRecorderDlg->szErrMsg);
					pIPRecorderDlg->bErrorOccurred = TRUE;
					pIPRecorderDlg->m_nRecordError++;
				}
			}
			pIPRecorderDlg->ChannelInfo[i].dwSessionId = pSessionInfo->dwSessionId;
			

			pIPRecorderDlg->bUpdateSlaverDisplay = TRUE;
		}
		break;
	case E_RCV_IPR_AUX_MEDIA_SESSION_STARTED:
		wsprintf(szEvtName, "E_RCV_IPR_AUX_MEDIA_SESSION_STARTED");
		break;
	case E_RCV_IPR_MEDIA_SESSION_STOPED:
		wsprintf(szEvtName, "E_RCV_IPR_MEDIA_SESSION_STOPED");
		pSessionInfo = (pIPR_SessionInfo)pEvent->pvBuffer;

		bFind = FALSE;
		for(i=0; i<pIPRecorderDlg->MaxLine; i++)
		{
			if(pIPRecorderDlg->ChannelInfo[i].dwSessionId == pSessionInfo->dwSessionId 
				&& pIPRecorderDlg->ChannelInfo[i].nChType == IPA_CH)
			{
				bFind = TRUE;
				break;
			}
		}
		if(!bFind)
			break;
		//SsmIPRStopSendSession(i);
		pIPRecorderDlg->ChannelInfo[i].dwSessionId = 0;

		bFind = FALSE;
		for(i=0; i<pIPRecorderDlg->MaxLine; i++)
		{
			if(pIPRecorderDlg->ChannelInfo[i].dwSessionId == pSessionInfo->dwSessionId 
				&& pIPRecorderDlg->ChannelInfo[i].nChType == IPR_CH)
			{
				pIPRecorderDlg->ChannelInfo[i].dwSessionId = 0;
//				pIPRecorderDlg->ChannelInfo[i].nPtlType = -1;
//				pIPRecorderDlg->ChannelInfo[i].nStationId = -1;
//				pIPRecorderDlg->ChannelInfo[i].nRecSlaverId = -1;
				bFind = TRUE;
				break;
			}
		} 
		if(!bFind)
			break;
		if(pIPRecorderDlg->ChannelInfo[i].bCallActive == FALSE && pIPRecorderDlg->ChannelInfo[i].bRecording)
		{
			pIPRecorderDlg->ChannelInfo[i].nPtlType = -1;
			pIPRecorderDlg->ChannelInfo[i].nStationId = -1;
			pIPRecorderDlg->ChannelInfo[i].nRecSlaverId = -1;
			if(SsmIPRDeActiveAndStopRecToFile(i) != 0)
			{
				SsmGetLastErrMsg(pIPRecorderDlg->szErrMsg);
				GetLocalTime(&time);
				wsprintf(szErrMsgDisplay, "%02d/%02d/%d %02d:%02d:%02d.%03d: ch = %d, ", time.wMonth, time.wDay, time.wYear, 
					time.wHour, time.wMinute, time.wSecond, time.wMilliseconds, i);
				strcat(szErrMsgDisplay, pIPRecorderDlg->szErrMsg);
				pIPRecorderDlg->bErrorOccurred = TRUE;
				pIPRecorderDlg->m_nRecordError++;
			}
			pIPRecorderDlg->ChannelInfo[i].bRecording = FALSE;
		}
		break;
	case E_RCV_IPR_AUX_MEDIA_SESSION_STOPED:
		wsprintf(szEvtName, "E_RCV_IPR_AUX_MEDIA_SESSION_STOPED");
		break;
	case E_IPR_ACTIVE_AND_REC_CB:
		wsprintf(szEvtName, "E_IPR_ACTIVE_AND_REC_CB");
		if(pEvent->dwParam & 0xffff)	//error occurred
		{
			GetLocalTime(&time);
			wsprintf(szErrMsgDisplay, "%02d/%02d/%d %02d:%02d:%02d.%03d: ch = %d, recorder slaver return error, code = %d.", time.wMonth, time.wDay, time.wYear, 
				time.wHour, time.wMinute, time.wSecond, time.wMilliseconds, pEvent->nReference, pEvent->dwParam & 0xffff);
			pIPRecorderDlg->bErrorOccurred = TRUE;
			PCHANNEL_INFO pChannelInfo;
			pChannelInfo = &(pIPRecorderDlg->ChannelInfo[pEvent->nReference]);
			pChannelInfo->dwSessionId = 0;
			pChannelInfo->nCallRef = -1;
			pChannelInfo->nPtlType = -1;
			pIPRecorderDlg->m_nRecordError++;
			break;
		}
		bFind = FALSE;
		for(i=0; i<pIPRecorderDlg->MaxLine; i++)
		{
			if(pIPRecorderDlg->ChannelInfo[i].dwSessionId == pIPRecorderDlg->ChannelInfo[pEvent->nReference].dwSessionId 
				&& pIPRecorderDlg->ChannelInfo[i].nChType == IPA_CH)
			{
				if(pIPRecorderDlg->ChannelInfo[i].dwSessionId)
				{
					bFind = TRUE;
					break;
				}
			}
		}
		if(!bFind)
			break;
		nSlaverIndex = -1;
		nSlaverId = pEvent->dwParam >> 16;
		for(uc = 0; uc < pIPRecorderDlg->nSlaverCount; uc++)
		{
			if(pIPRecorderDlg->IPR_SlaverAddr[uc].nRecSlaverID == nSlaverId)
			{
				nSlaverIndex = uc;
				break;
			}
		}
		if(nSlaverIndex < 0)
			break;
		
		wsprintf(szIPP_Rec, "%d.%d.%d.%d", pIPRecorderDlg->IPR_SlaverAddr[nSlaverIndex].ipAddr.S_un_b.s_b1, 
			pIPRecorderDlg->IPR_SlaverAddr[nSlaverIndex].ipAddr.S_un_b.s_b2, 
			pIPRecorderDlg->IPR_SlaverAddr[nSlaverIndex].ipAddr.S_un_b.s_b3, 
			pIPRecorderDlg->IPR_SlaverAddr[nSlaverIndex].ipAddr.S_un_b.s_b4);
		wsprintf(szIPS_Rec, "%d.%d.%d.%d", pIPRecorderDlg->IPR_SlaverAddr[nSlaverIndex].ipAddr.S_un_b.s_b1, 
			pIPRecorderDlg->IPR_SlaverAddr[nSlaverIndex].ipAddr.S_un_b.s_b2, 
			pIPRecorderDlg->IPR_SlaverAddr[nSlaverIndex].ipAddr.S_un_b.s_b3, 
			pIPRecorderDlg->IPR_SlaverAddr[nSlaverIndex].ipAddr.S_un_b.s_b4);
		if(SsmIPRSendSession(i, szIPP_Rec, pIPRecorderDlg->ChannelInfo[i].nFowardingPPort, 
			szIPS_Rec, pIPRecorderDlg->ChannelInfo[i].nFowardingSPort) != 0)
		{
			SsmGetLastErrMsg(pIPRecorderDlg->szErrMsg);
			GetLocalTime(&time);
			wsprintf(szErrMsgDisplay, "%02d/%02d/%d %02d:%02d:%02d.%03d: ch = %d, ", time.wMonth, time.wDay, time.wYear, 
				time.wHour, time.wMinute, time.wSecond, time.wMilliseconds, i);
			strcat(szErrMsgDisplay, pIPRecorderDlg->szErrMsg);
			pIPRecorderDlg->bErrorOccurred = TRUE;
			pIPRecorderDlg->m_nRecordError++;
		}
		pIPRecorderDlg->m_nTotalFile++;

		if((int)(pEvent->dwParam >> 16) == pIPRecorderDlg->IPR_SlaverAddr[pIPRecorderDlg->nSlaverSelectedIndex].nRecSlaverID)
		{
			pIPRecorderDlg->ScanSlaver();
			pIPRecorderDlg->bUpdateSlaverDisplay = TRUE;
		}
		break;
	case E_IPR_DEACTIVE_AND_STOPREC_CB:
		wsprintf(szEvtName, "E_IPR_DEACTIVE_AND_STOPREC_CB");
		if(pEvent->dwParam & 0xffff)	//error occurred
		{
			GetLocalTime(&time);
			wsprintf(szErrMsgDisplay, "%02d/%02d/%d %02d:%02d:%02d.%03d: ch = %d, recorder slaver return error, code = %d.", time.wMonth, time.wDay, time.wYear, 
				time.wHour, time.wMinute, time.wSecond, time.wMilliseconds, pEvent->nReference, pEvent->dwParam & 0xffff);
			pIPRecorderDlg->bErrorOccurred = TRUE;
			pIPRecorderDlg->m_nRecordError++;
			break;
		}
		
		pIPRecorderDlg->ChannelInfo[pEvent->nReference].nStatistics++;
		if((int)(pEvent->dwParam >> 16) == pIPRecorderDlg->IPR_SlaverAddr[pIPRecorderDlg->nSlaverSelectedIndex].nRecSlaverID)
		{
			pIPRecorderDlg->ScanSlaver();
			pIPRecorderDlg->bUpdateSlaverDisplay = TRUE;
		}
		break;
	case E_IPR_LINK_REC_SLAVER_CONNECTED:
		wsprintf(szEvtName, "E_IPR_LINK_REC_SLAVER_CONNECTED");
		pIPRecorderDlg->ScanSlaver();
		pIPRecorderDlg->bSlaverConnectChanged = TRUE;
		pIPRecorderDlg->bUpdateSlaverDisplay = TRUE;
		break;
	case E_IPR_LINK_REC_SLAVER_DISCONNECTED:
		wsprintf(szEvtName, "E_IPR_LINK_REC_SLAVER_DISCONNECTED");
		pIPRecorderDlg->ScanSlaver();
		pIPRecorderDlg->bSlaverConnectChanged = TRUE;
		pIPRecorderDlg->bUpdateSlaverDisplay = TRUE;
		break;
	case E_IPR_RCV_DTMF:
		wsprintf(szEvtName, "E_IPR_RCV_DTMF");
		break;
	case E_PROC_RecordEnd:
		wsprintf(szEvtName, "E_PROC_RecordEnd");
		break;
	case E_RCV_IPR_MEDIA_SESSION_FOWARDING:
		wsprintf(szEvtName, "E_RCV_IPR_MEDIA_SESSION_FOWARDING");
		break;
	case E_RCV_IPR_MEDIA_SESSION_FOWARD_STOPED:
		wsprintf(szEvtName, "E_RCV_IPR_MEDIA_SESSION_FOWARD_STOPED");
		break;
	default:
		wsprintf(szEvtName, "0x%x", pEvent->wEventCode);
		break;
	}

	if(pIPRecorderDlg->m_bShowEvent)
	{
		pIPRecorderDlg->EventDisplay(szEvtName, pEvent);
	}

	if(pIPRecorderDlg->bErrorOccurred)
	{
		pIPRecorderDlg->m_TreeCtrlErrDisplay.InsertItem(szErrMsgDisplay, TVI_ROOT, TVI_FIRST);
	}

	return 0;
}

void CIPRecorderDlg::EventDisplay(LPSTR lpStrEventName, PSSM_EVENT pEvent)
{
	int nItemCounts;
	HTREEITEM hParent;
	char szEventDisplay[500];
	SYSTEMTIME time;
	StationInfoEx StationInfoEx;
	PIPR_CISCO_SCCP_CALL_INFO pSCCPCallInfo;
	pIPR_SessionInfo pSessionInfo;
	PIPR_CALL_INFO pCallInfo;

	nItemCounts = m_TreeCtrlEventDisplay.GetCount();
	if(nItemCounts > 10000 && m_bAutoClearEvent)
	{
		m_TreeCtrlEventDisplay.DeleteAllItems();
	}
	
	GetLocalTime(&time);
	if(pEvent->wEventCode == E_CHG_ChState)
	{
		wsprintf(szEventDisplay, "%02d/%02d/%d %02d:%02d:%02d.%03d  %s, ch %d, param 0x%08x", time.wMonth, time.wDay, time.wYear, 
			time.wHour, time.wMinute, time.wSecond, time.wMilliseconds, lpStrEventName, pEvent->nReference, pEvent->dwParam);
	}
	else if(pEvent->wEventCode == E_IPR_ACTIVE_SESSION_CB
		|| pEvent->wEventCode == E_IPR_DEACTIVE_SESSION_CB
		|| pEvent->wEventCode == E_IPR_START_REC_CB
		|| pEvent->wEventCode == E_IPR_STOP_REC_CB
		|| pEvent->wEventCode == E_IPR_ACTIVE_AND_REC_CB
		|| pEvent->wEventCode == E_IPR_DEACTIVE_AND_STOPREC_CB
		|| pEvent->wEventCode == E_IPR_RCV_DTMF
		|| pEvent->wEventCode == E_PROC_RecordEnd
		)
	{
		wsprintf(szEventDisplay, "%02d/%02d/%d %02d:%02d:%02d.%03d  %s, ch %d, param 0x%08x, XtraInfo 0x%08x", time.wMonth, time.wDay, time.wYear, 
			time.wHour, time.wMinute, time.wSecond, time.wMilliseconds, lpStrEventName, pEvent->nReference, pEvent->dwParam, pEvent->dwXtraInfo);
	}
	else if(pEvent->wEventCode == E_RCV_IPR_MEDIA_SESSION_FOWARDING
		|| pEvent->wEventCode == E_RCV_IPR_MEDIA_SESSION_FOWARD_STOPED)
	{
		wsprintf(szEventDisplay, "%02d/%02d/%d %02d:%02d:%02d.%03d  %s sessionid = %d", 
			time.wMonth, time.wDay, time.wYear, time.wHour, time.wMinute, time.wSecond, time.wMilliseconds, 
			lpStrEventName, pEvent->dwParam);
	}
	else
	{
		wsprintf(szEventDisplay, "%02d/%02d/%d %02d:%02d:%02d.%03d  %s SubReason 0x%08x, XtraInfo 0x%08x", 
			time.wMonth, time.wDay, time.wYear, time.wHour, time.wMinute, time.wSecond, time.wMilliseconds, 
			lpStrEventName, pEvent->dwSubReason, pEvent->dwXtraInfo);
	}
	hParent = m_TreeCtrlEventDisplay.InsertItem(szEventDisplay, TVI_ROOT, TVI_FIRST);
	if(pEvent->wEventCode == E_RCV_IPR_DChannel && pEvent->dwParam == DE_CISCO_SCCP_CALL_INFO)
	{
		pSCCPCallInfo = (PIPR_CISCO_SCCP_CALL_INFO)pEvent->pvBuffer;
		wsprintf(szEventDisplay, "CallingPartyName: %s", pSCCPCallInfo->CallingPartyName);
		m_TreeCtrlEventDisplay.InsertItem(szEventDisplay, hParent);
		wsprintf(szEventDisplay, "CallingParty: %s", pSCCPCallInfo->CallingParty);
		m_TreeCtrlEventDisplay.InsertItem(szEventDisplay, hParent);
		wsprintf(szEventDisplay, "CalledPartyName: %s", pSCCPCallInfo->CalledPartyName);
		m_TreeCtrlEventDisplay.InsertItem(szEventDisplay, hParent);
		wsprintf(szEventDisplay, "CalledParty: %s", pSCCPCallInfo->CalledParty);
		m_TreeCtrlEventDisplay.InsertItem(szEventDisplay, hParent);
		wsprintf(szEventDisplay, "LineInstance: %d", pSCCPCallInfo->LineInstance);
		m_TreeCtrlEventDisplay.InsertItem(szEventDisplay, hParent);
		wsprintf(szEventDisplay, "CallId: %d", pSCCPCallInfo->CallId);
		m_TreeCtrlEventDisplay.InsertItem(szEventDisplay, hParent);
		wsprintf(szEventDisplay, "CallType: %d", pSCCPCallInfo->CallType);
		m_TreeCtrlEventDisplay.InsertItem(szEventDisplay, hParent);
		wsprintf(szEventDisplay, "OrigCalledPartyName: %s", pSCCPCallInfo->OrigCalledPartyName);
		m_TreeCtrlEventDisplay.InsertItem(szEventDisplay, hParent);
		wsprintf(szEventDisplay, "OrigCalledParty: %s", pSCCPCallInfo->OrigCalledParty);
		m_TreeCtrlEventDisplay.InsertItem(szEventDisplay, hParent);
		wsprintf(szEventDisplay, "LastRedirectingPartyName: %s", pSCCPCallInfo->LastRedirectingPartyName);
		m_TreeCtrlEventDisplay.InsertItem(szEventDisplay, hParent);
		wsprintf(szEventDisplay, "LastRedirectingParty: %s", pSCCPCallInfo->LastRedirectingParty);
		m_TreeCtrlEventDisplay.InsertItem(szEventDisplay, hParent);
		wsprintf(szEventDisplay, "OrigCalledPartyRedirectReason: %d", pSCCPCallInfo->OrigCalledPartyRedirectReason);
		m_TreeCtrlEventDisplay.InsertItem(szEventDisplay, hParent);
		wsprintf(szEventDisplay, "LastRedirectReason: %d", pSCCPCallInfo->LastRedirectReason);
		m_TreeCtrlEventDisplay.InsertItem(szEventDisplay, hParent);
		wsprintf(szEventDisplay, "CallingPartyVoiceMailbox: %s", pSCCPCallInfo->CallingPartyVoiceMailbox);
		m_TreeCtrlEventDisplay.InsertItem(szEventDisplay, hParent);
		wsprintf(szEventDisplay, "CalledPartyVoiceMailbox: %s", pSCCPCallInfo->CalledPartyVoiceMailbox);
		m_TreeCtrlEventDisplay.InsertItem(szEventDisplay, hParent);
		wsprintf(szEventDisplay, "OriginalCalledPartyVoiceMailbox: %s", pSCCPCallInfo->OriginalCalledPartyVoiceMailbox);
		m_TreeCtrlEventDisplay.InsertItem(szEventDisplay, hParent);
		wsprintf(szEventDisplay, "LastRedirectVoiceMailbox: %s", pSCCPCallInfo->LastRedirectVoiceMailbox);
		m_TreeCtrlEventDisplay.InsertItem(szEventDisplay, hParent);
		wsprintf(szEventDisplay, "CallInstance: %d", pSCCPCallInfo->CallInstance);
		m_TreeCtrlEventDisplay.InsertItem(szEventDisplay, hParent);
	}
	else if(pEvent->wEventCode == E_RCV_IPR_MEDIA_SESSION_STARTED 
		|| pEvent->wEventCode == E_RCV_IPR_AUX_MEDIA_SESSION_STARTED
		|| pEvent->wEventCode == E_RCV_IPR_MEDIA_SESSION_STOPED
		|| pEvent->wEventCode == E_RCV_IPR_AUX_MEDIA_SESSION_STOPED)
	{
		pSessionInfo = (pIPR_SessionInfo)pEvent->pvBuffer;
		wsprintf(szEventDisplay, "CallRef: %d", pSessionInfo->nCallRef);
		m_TreeCtrlEventDisplay.InsertItem(szEventDisplay, hParent);
		wsprintf(szEventDisplay, "SessionId: %d", pSessionInfo->dwSessionId);
		m_TreeCtrlEventDisplay.InsertItem(szEventDisplay, hParent);
		wsprintf(szEventDisplay, "PrimaryIP: %d.%d.%d.%d", pSessionInfo->PrimaryAddr.S_un_b.s_b1,
			pSessionInfo->PrimaryAddr.S_un_b.s_b2, pSessionInfo->PrimaryAddr.S_un_b.s_b3, 
			pSessionInfo->PrimaryAddr.S_un_b.s_b4);
		m_TreeCtrlEventDisplay.InsertItem(szEventDisplay, hParent);
		wsprintf(szEventDisplay, "PrimaryPort: %d", pSessionInfo->PrimaryAddr.usPort);
		m_TreeCtrlEventDisplay.InsertItem(szEventDisplay, hParent);
		wsprintf(szEventDisplay, "PrimaryCodec: %d", pSessionInfo->nPrimaryCodec);
		m_TreeCtrlEventDisplay.InsertItem(szEventDisplay, hParent);
		wsprintf(szEventDisplay, "SecondaryIP: %d.%d.%d.%d", pSessionInfo->SecondaryAddr.S_un_b.s_b1,
			pSessionInfo->SecondaryAddr.S_un_b.s_b2, pSessionInfo->SecondaryAddr.S_un_b.s_b3, 
			pSessionInfo->SecondaryAddr.S_un_b.s_b4);
		m_TreeCtrlEventDisplay.InsertItem(szEventDisplay, hParent);
		wsprintf(szEventDisplay, "SecondaryPort: %d", pSessionInfo->SecondaryAddr.usPort);
		m_TreeCtrlEventDisplay.InsertItem(szEventDisplay, hParent);
		wsprintf(szEventDisplay, "SecondaryCodec: %d", pSessionInfo->nSecondaryCodec);
		m_TreeCtrlEventDisplay.InsertItem(szEventDisplay, hParent);
	}
	else if(pEvent->wEventCode == E_RCV_IPR_DChannel && pEvent->dwParam >= DE_CALL_IN_PROGRESS && pEvent->dwParam <= DE_CALL_REJECTED)
	{
		pCallInfo = (PIPR_CALL_INFO)pEvent->pvBuffer;
		wsprintf(szEventDisplay, "CallRef: %d", pCallInfo->CallRef);
		m_TreeCtrlEventDisplay.InsertItem(szEventDisplay, hParent);
		wsprintf(szEventDisplay, "CallSource: %d", pCallInfo->CallSource);
		m_TreeCtrlEventDisplay.InsertItem(szEventDisplay, hParent);
		wsprintf(szEventDisplay, "Cause: %d", pCallInfo->Cause);
		m_TreeCtrlEventDisplay.InsertItem(szEventDisplay, hParent);
		wsprintf(szEventDisplay, "CallerId: %s", pCallInfo->szCallerId);
		m_TreeCtrlEventDisplay.InsertItem(szEventDisplay, hParent);
		wsprintf(szEventDisplay, "CalledId: %s", pCallInfo->szCalledId);
		m_TreeCtrlEventDisplay.InsertItem(szEventDisplay, hParent);
		wsprintf(szEventDisplay, "ReferredBy: %s", pCallInfo->szReferredBy);
		m_TreeCtrlEventDisplay.InsertItem(szEventDisplay, hParent);
		wsprintf(szEventDisplay, "ReferTo: %s", pCallInfo->szReferTo);
		m_TreeCtrlEventDisplay.InsertItem(szEventDisplay, hParent);
	}
	else if(pEvent->wEventCode == E_RCV_IPR_DChannel && pEvent->dwParam == DE_MSG_CHG)
	{
		wsprintf(szEventDisplay, "%s", pEvent->pvBuffer);
		m_TreeCtrlEventDisplay.InsertItem(szEventDisplay, hParent);
	}
	else if(pEvent->wEventCode == E_RCV_IPR_STATION_ADDED)
	{
		SsmIPRGetStationInfoEx(nIPABoardId, pEvent->dwXtraInfo & 0xffff, &StationInfoEx);
		wsprintf(szEventDisplay, "StationId: %d", StationInfoEx.nStationId);
		m_TreeCtrlEventDisplay.InsertItem(szEventDisplay, hParent);
		wsprintf(szEventDisplay, "Call Ctrl Protocal: %d", StationInfoEx.ucCallCtrlPtl);
		m_TreeCtrlEventDisplay.InsertItem(szEventDisplay, hParent);
		wsprintf(szEventDisplay, "IP: %d.%d.%d.%d", StationInfoEx.CallCtrlAddr.S_un_b.s_b1,
			StationInfoEx.CallCtrlAddr.S_un_b.s_b2,
			StationInfoEx.CallCtrlAddr.S_un_b.s_b3,
			StationInfoEx.CallCtrlAddr.S_un_b.s_b4);
		m_TreeCtrlEventDisplay.InsertItem(szEventDisplay, hParent);
		wsprintf(szEventDisplay, "Port: %d", StationInfoEx.CallCtrlAddr.usPort);
		m_TreeCtrlEventDisplay.InsertItem(szEventDisplay, hParent);
		wsprintf(szEventDisplay, "MAC: %02x-%02x-%02x-%02x-%02x-%02x", StationInfoEx.ucMacAddr[0],
			StationInfoEx.ucMacAddr[1],
			StationInfoEx.ucMacAddr[2],
			StationInfoEx.ucMacAddr[3],
			StationInfoEx.ucMacAddr[4],
			StationInfoEx.ucMacAddr[5]);
		m_TreeCtrlEventDisplay.InsertItem(szEventDisplay, hParent);
	}
}

void CIPRecorderDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CIPRecorderDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CIPRecorderDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

BOOL CIPRecorderDlg::InitCtiSystem()
{
	int i;
	//int nIsSsmStartCtiOK = SsmStartCti("ShConfig.ini", "ShIndex.ini");

	EVENT_SET_INFO EventMode;
	EventMode.dwWorkMode = EVENT_CALLBACKA;
	EventMode.lpHandlerParam = EventCallback;
	EventMode.dwUser = (DWORD)this;
	int nIsSsmStartCtiOK = SsmStartCtiEx("ShConfig.ini", "ShIndex.ini", TRUE, &EventMode);

	if(nIsSsmStartCtiOK != 0)
	{
		SsmGetLastErrMsg(szErrMsg);
		AfxMessageBox(szErrMsg, MB_OK, 0);
		return FALSE;
	}
	if(SsmGetMaxUsableBoard() != SsmGetMaxCfgBoard())
	{
		SsmGetLastErrMsg(szErrMsg);
		AfxMessageBox(szErrMsg, MB_OK, 0);
	}
	
	MaxLine=SsmGetMaxCh();
	nIPRChNum = 0;
	nUsedIPRChNum = 0;
	nIPAChNum = 0;
	bUpdateSlaverDisplay = FALSE;
	for(i = 0; i < MaxLine; i++)
	{
		if(SsmGetChType(i) == IPR_CH)
		{
			nIPRChNum++;
		}
		else if(SsmGetChType(i) == IPA_CH)
		{
			nIPAChNum++;
		}
	}

	if(SsmGetUSBKeySerial(0) == 0x7fffffff)
	{
		bTrialEdition = TRUE;
		MessageBox("This is a 5 hours period trial edition, the application will face exception when time expires! you maybe will kill process by yourself!!", "Warning", MB_ICONWARNING);
	}
	else
	{
		bTrialEdition = FALSE;
	}
	dwStartTime = GetTickCount();
	
	return TRUE;
}

void CIPRecorderDlg::InitChannelList()
{
	static int ColumnWidth[13] = {30, 30, 80, 80, 100, 100, 60, 80, 80, 80, 120, 120, 100};
	int nChType;
	LV_COLUMN lvc;
	lvc.mask =  LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM | LVCF_FMT;

	lvc.iSubItem = 0;
	lvc.pszText = "Ch" ;
	lvc.cx = ColumnWidth[0];
	lvc.fmt = LVCFMT_LEFT;
	m_ChannelList.InsertColumn(0,&lvc);

	lvc.iSubItem = 1;
	lvc.pszText = "Type" ;
	lvc.cx = ColumnWidth[1];
	lvc.fmt = LVCFMT_RIGHT;
	m_ChannelList.InsertColumn(1,&lvc);

	lvc.iSubItem = 2;
	lvc.pszText = "State" ;
	lvc.cx = ColumnWidth[2];
	lvc.fmt = LVCFMT_RIGHT;
	m_ChannelList.InsertColumn(2,&lvc);

	lvc.iSubItem = 3;
	lvc.pszText = "Session ID";
	lvc.cx = ColumnWidth[3];
	lvc.fmt = LVCFMT_RIGHT;
	m_ChannelList.InsertColumn(3,&lvc);

	lvc.iSubItem = 4;
	lvc.pszText = "Caller Number" ;
	lvc.cx = ColumnWidth[4];
	lvc.fmt = LVCFMT_RIGHT;
	m_ChannelList.InsertColumn(4,&lvc);

	lvc.iSubItem = 5;
	lvc.pszText = "Called Number" ;
	lvc.cx = ColumnWidth[5];
	lvc.fmt = LVCFMT_RIGHT;
	m_ChannelList.InsertColumn(5,&lvc);

	lvc.iSubItem = 6;
	lvc.pszText = "Protocol" ;
	lvc.cx = ColumnWidth[6];
	lvc.fmt = LVCFMT_RIGHT;
	m_ChannelList.InsertColumn(6,&lvc);

	lvc.iSubItem = 7;
	lvc.pszText = "Station ID" ;
	lvc.cx = ColumnWidth[7];
	lvc.fmt = LVCFMT_RIGHT;
	m_ChannelList.InsertColumn(7,&lvc);

	lvc.iSubItem = 8;
	lvc.pszText = "Slaver ID" ;
	lvc.cx = ColumnWidth[8];
	lvc.fmt = LVCFMT_RIGHT;
	m_ChannelList.InsertColumn(8,&lvc);

	lvc.iSubItem = 9;
	lvc.pszText = "RecTime";
	lvc.cx = ColumnWidth[9];
	lvc.fmt = LVCFMT_RIGHT;
	m_ChannelList.InsertColumn(9,&lvc);

	lvc.iSubItem = 10;
	lvc.pszText = "IP 1" ;
	lvc.cx = ColumnWidth[10];
	lvc.fmt = LVCFMT_RIGHT;
	m_ChannelList.InsertColumn(10,&lvc);

	lvc.iSubItem = 11;
	lvc.pszText = "IP 2" ;
	lvc.cx = ColumnWidth[11];
	lvc.fmt = LVCFMT_RIGHT;
	m_ChannelList.InsertColumn(11,&lvc);

	lvc.iSubItem = 12;
	lvc.pszText = "statistics" ;
	lvc.cx = ColumnWidth[12];
	lvc.fmt = LVCFMT_RIGHT;
	m_ChannelList.InsertColumn(12,&lvc);

	char dig[3];
	for(int i = 0; i < MaxLine; i++)
	{
		nChType = SsmGetChType(i);
		if(nChType == IPR_CH)
		{
			m_ChannelList.InsertItem(i,_itoa(i,dig,10));
			m_ChannelList.SetItemText(i, 1, "IPR");
		}
		else if(nChType == IPA_CH)
		{
			m_ChannelList.InsertItem(i,_itoa(i,dig,10));
			m_ChannelList.SetItemText(i, 1, "IPA");
		}
		else
		{
			m_ChannelList.InsertItem(i,_itoa(i,dig,10));
			m_ChannelList.SetItemText(i, 1, _itoa(nChType,dig,10));
		}
	}
}

void CIPRecorderDlg::InitChannelState()
{
	for(int i=0; i < MaxLine; i++)
	{
		ChannelInfo[i].nChType = SsmGetChType(i);
		ChannelInfo[i].nWorkState = SsmGetChState(i);
		ChannelInfo[i].nPtlType = -1;
		ChannelInfo[i].nCallRef = -1;
		ChannelInfo[i].dwSessionId = -1;
		ChannelInfo[i].nStationId = -1;
		ChannelInfo[i].nRecSlaverId = -1;
		ChannelInfo[i].nFowardingPPort = -1;
		ChannelInfo[i].nFowardingSPort = -1;
		wsprintf(ChannelInfo[i].szCallerID, "");
		wsprintf(ChannelInfo[i].szCalledID, "");
		wsprintf(ChannelInfo[i].szIPP, "");
		wsprintf(ChannelInfo[i].szIPS, "");
		ChannelInfo[i].nStatistics = 0;
	}
}

void CIPRecorderDlg::OnDestroy() 
{



		KillTimer(1);

		if(SsmCloseCti() == -1)									 
		{
			SsmGetLastErrMsg(szErrMsg);
			AfxMessageBox(szErrMsg, MB_OK, 0);
		}

		CDialog::OnDestroy();	

}

void CIPRecorderDlg::ScanSlaver() 
{
	// TODO: Add your control notification handler code here
	int nActualSlaverCount;

	nSlaverCount = SsmIPRGetRecSlaverCount(1);
	if(nSlaverCount)
	{
		SsmIPRGetRecSlaverList(1, nSlaverCount, &nActualSlaverCount, &IPR_SlaverAddr[0]);
	}
}

void CIPRecorderDlg::UpdateSlaverDisplay()
{
	int i, nSlaverID;
	BOOL bStarted;
	char szTemp[50];
	CString strTemp;
	COMPUTER_INFO ComputerInfo;
	
	if(bSlaverConnectChanged)
		m_cbSlaverID.ResetContent();
	if(nSlaverCount)
	{
		if(bSlaverConnectChanged)
		{
			for(i=0; i<nSlaverCount; i++)
			{
				wsprintf(szTemp, "%d", IPR_SlaverAddr[i].nRecSlaverID);
				m_cbSlaverID.InsertString(i, szTemp);
			}
			nSlaverSelectedIndex = 0;
		}
		
		m_cbSlaverID.SetCurSel(nSlaverSelectedIndex);
		m_strIP.Format("%d.%d.%d.%d", IPR_SlaverAddr[nSlaverSelectedIndex].ipAddr.S_un_b.s_b1, IPR_SlaverAddr[nSlaverSelectedIndex].ipAddr.S_un_b.s_b2,
			IPR_SlaverAddr[nSlaverSelectedIndex].ipAddr.S_un_b.s_b3, IPR_SlaverAddr[nSlaverSelectedIndex].ipAddr.S_un_b.s_b4);
		m_strPort.Format("%d", IPR_SlaverAddr[nSlaverSelectedIndex].ipAddr.usPort);
		GetDlgItem(IDC_EDIT_IP)->SetWindowText(m_strIP);
		GetDlgItem(IDC_EDIT_PORT)->SetWindowText(m_strPort);
		
		nSlaverID = GetDlgItemInt(IDC_COMBO_SLAVERID);
		SsmIPRGetRecSlaverInfo(nIPRBoardId, nSlaverID, &bStarted, &m_nTotalResources, &m_nUsedResources, &m_nThreadPairs, &ComputerInfo);
		if(bStarted)
			m_szSlaverState.Format("running...");
		else
			m_szSlaverState.Format("pending...");
		GetDlgItem(IDC_EDIT_INIT_THREADPAIRS)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_INIT_TOTALRESOURCES)->EnableWindow(TRUE);
	}
	else
	{
		m_strIP.Format("");
		m_strPort.Format("");
		m_szSlaverState.Format("");
		GetDlgItem(IDC_EDIT_INIT_THREADPAIRS)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_INIT_TOTALRESOURCES)->EnableWindow(FALSE);
	}
	bSlaverConnectChanged = FALSE;
}

void CIPRecorderDlg::OnButtonStartslaver() 
{
	// TODO: Add your control notification handler code here
	int nSlaverID, nResult;

	UpdateData(TRUE);
	nSlaverID = GetDlgItemInt(IDC_COMBO_SLAVERID);
	nResult = SsmIPRStartRecSlaver(nIPRBoardId, nSlaverID, &m_nInitTotalResources, &m_nInitThreadPairs);
	if(nResult < 0)
	{
		SsmGetLastErrMsg(szErrMsg);
		AfxMessageBox(szErrMsg, MB_OK, 0);
		return;
	}
	GetDlgItem(IDC_BUTTON_CLOSESLAVER)->EnableWindow(TRUE);
}

void CIPRecorderDlg::OnButtonCloseslaver() 
{
	// TODO: Add your control notification handler code here
	int nSlaverID, nResult;
	
	UpdateData(FALSE);
	nSlaverID = GetDlgItemInt(IDC_COMBO_SLAVERID);
	nResult = SsmIPRCloseRecSlaver(nIPRBoardId, nSlaverID);
	if(nResult < 0)
	{
		return;
	}
//	GetDlgItem(IDC_BUTTON_STARTSLAVER)->EnableWindow(TRUE);
//	GetDlgItem(IDC_BUTTON_CLOSESLAVER)->EnableWindow(FALSE);
}

void CIPRecorderDlg::OnSelchangeComboSlaverid() 
{
	// TODO: Add your control notification handler code here
	int nCurSel;
	CString strTemp;

	nCurSel = m_cbSlaverID.GetCurSel();
	nSlaverSelectedIndex = nCurSel;
//	strTemp.Format("%d.%d.%d.%d", IPR_SlaverAddr[nCurSel].ipAddr.S_un_b.s_b1, IPR_SlaverAddr[nCurSel].ipAddr.S_un_b.s_b2,
//		IPR_SlaverAddr[nCurSel].ipAddr.S_un_b.s_b3, IPR_SlaverAddr[nCurSel].ipAddr.S_un_b.s_b4);
//	GetDlgItem(IDC_EDIT_IP)->SetWindowText(strTemp);
//	strTemp.Format("%d", IPR_SlaverAddr[nCurSel].ipAddr.usPort);
//	GetDlgItem(IDC_EDIT_PORT)->SetWindowText(strTemp);	
	ScanSlaver();

	UpdateData();
	bUpdateSlaverDisplay = TRUE;
}

void CIPRecorderDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	static BOOL bTip = FALSE;
	int i;
	LONG lRecTime;
	DWORD dw;
	int nHour, nMinute, nSecond;
	char szTemp[100], szOld[100], szCaption[100];

	for(i = 0; i < MaxLine; i++)
	{
		lRecTime = SsmGetRecTime(i);
		wsprintf(szTemp, "%d", lRecTime);
		m_ChannelList.SetItemText(i, 9, szTemp);

		switch(ChannelInfo[i].nWorkState)
		{
		case S_CALL_STANDBY:
			wsprintf(szTemp, "Idle");
			break;
		case S_CALL_UNAVAILABLE:
			wsprintf(szTemp, "Unavalable");
			break;
		case S_IPR_COMMUNICATING:
			wsprintf(szTemp, "Communicating");
			break;
		case S_IPR_USING:
			wsprintf(szTemp, "Using");
			break;
		default:
			wsprintf(szTemp, "Unknown");
			break;
		}
		m_ChannelList.GetItemText(i, 2, szOld, 100);
		if(szOld != szTemp)
		{
			m_ChannelList.SetItemText(i, 2, szTemp);
		}

		if(ChannelInfo[i].nChType == IPR_CH)
		{
			wsprintf(szTemp, "%d", ChannelInfo[i].dwSessionId);
			m_ChannelList.SetItemText(i, 3, szTemp);
			wsprintf(szTemp, "%s", ChannelInfo[i].szCallerID);
			m_ChannelList.SetItemText(i, 4, szTemp);
			wsprintf(szTemp, "%s", ChannelInfo[i].szCalledID);
			m_ChannelList.SetItemText(i, 5, szTemp);
			wsprintf(szTemp, "%d", ChannelInfo[i].nPtlType);
			m_ChannelList.SetItemText(i, 6, szTemp);
			wsprintf(szTemp, "%d", ChannelInfo[i].nStationId);
			m_ChannelList.SetItemText(i, 7, szTemp);
			wsprintf(szTemp, "%d", ChannelInfo[i].nRecSlaverId);
			m_ChannelList.SetItemText(i, 8, szTemp);
			wsprintf(szTemp, "%s", ChannelInfo[i].szIPP);
			m_ChannelList.SetItemText(i, 10, szTemp);
			wsprintf(szTemp, "%s", ChannelInfo[i].szIPS);
			m_ChannelList.SetItemText(i, 11, szTemp);
			wsprintf(szTemp, "%d", ChannelInfo[i].nStatistics);
			m_ChannelList.SetItemText(i, 12, szTemp);
		}
		else if(ChannelInfo[i].nChType == IPA_CH)
		{
			wsprintf(szTemp, "%d", ChannelInfo[i].dwSessionId);
			m_ChannelList.SetItemText(i, 3, szTemp);
		}
	}

	if(bUpdateSlaverDisplay)
	{
		bUpdateSlaverDisplay = FALSE;
		UpdateSlaverDisplay();
		UpdateData(FALSE);
	}
	else if(bErrorOccurred)
	{
		bErrorOccurred = FALSE;
		UpdateData(FALSE);
	}

	if(bTrialEdition)
	{
		dwCurrentTime = GetTickCount();
		dw = dwCurrentTime - dwStartTime;
		nHour = dw/3600000;
		dw %= 3600000;
		nMinute = dw/60000;
		dw %= 60000;
		nSecond = dw/1000;
		wsprintf(szCaption, "IPRecorder (trial edition elapsed time %02d:%02d:%02d)", nHour, nMinute, nSecond);
		SetWindowText(szCaption);
	}

	CDialog::OnTimer(nIDEvent);
}

void CIPRecorderDlg::OnCheckShowevent() 
{
	// TODO: Add your control notification handler code here	
	UpdateData(TRUE);
}

void CIPRecorderDlg::OnButtonClearevent() 
{
	// TODO: Add your control notification handler code here
	m_TreeCtrlEventDisplay.DeleteAllItems();
}

void CIPRecorderDlg::OnCheckAutoclearevent() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
}

void CIPRecorderDlg::OnRadio1() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	nRecCodec = A_LAW;
}

void CIPRecorderDlg::OnRadio2() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	nRecCodec = U_LAW;
}

void CIPRecorderDlg::OnRadio3() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	nRecCodec = ADPCM;
}

void CIPRecorderDlg::OnRadio4() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	nRecCodec = GSM;
}

void CIPRecorderDlg::OnRadio5() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	nRecCodec = MP3;
}

void CIPRecorderDlg::OnRadio6() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	nRecCodec = G729A;
}

void CIPRecorderDlg::OnRadio7() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	nRecCodec = VOX;
}

void CIPRecorderDlg::OnRadio8() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	nRecCodec = GC8;
}

void CIPRecorderDlg::OnRadio9() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	nRecCodec = PCM_8;
}

void CIPRecorderDlg::OnRadio10() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	nRecCodec = PCM_16;
}

void CIPRecorderDlg::OnButtonClearerror() 
{
	// TODO: Add your control notification handler code here
	m_TreeCtrlErrDisplay.DeleteAllItems();
}

void CIPRecorderDlg::OnButtonFolderselect() 
{
	// TODO: Add your control notification handler code here
	BROWSEINFO  bi;
	char lpszPath[MAX_PATH];
    ZeroMemory(lpszPath, MAX_PATH);
    bi.hwndOwner  =GetSafeHwnd();   
    bi.pidlRoot  = NULL;   
	bi.pszDisplayName  = lpszPath;   
    bi.lpszTitle  = NULL;   
    bi.ulFlags  =BIF_BROWSEFORCOMPUTER  &&  BIF_RETURNONLYFSDIRS;   
    bi.lpfn  =NULL;   
    bi.lParam =0;
    bi.iImage = 0;
	LPITEMIDLIST  pidl = NULL;   
    BOOL  bSuccess=FALSE;
	
	if(pidl = SHBrowseForFolder(&bi))
    {   
        if(pidl != NULL)
        {	
            if(::SHGetPathFromIDList(pidl,lpszPath))    //取得文件夹名       
            {	
				m_strSelectedFolder.Format("%s", lpszPath);
				UpdateData(FALSE);
				bSuccess = TRUE;
            }  
			else
			{
				return;
			}
        }
		else
		{
			return;
		}
	}
	else
	{
		return;
	}
}

void CIPRecorderDlg::SetHideScroll(int type)
{
	scrollinfo.cbSize = sizeof(scrollinfo);
	scrollinfo.fMask = SIF_ALL;
	scrollinfo.nPage = 0;
	scrollinfo.nMax = 0;
	scrollinfo.nMin = 0;
	scrollinfo.nTrackPos = 0;
	SetScrollInfo(type,&scrollinfo);
}

void CIPRecorderDlg::SetScrollValue(int type, int nPage, int nMax)
{
	scrollinfo.cbSize = sizeof(scrollinfo);
	scrollinfo.fMask = SIF_ALL;
	scrollinfo.nPage = nPage/10;
	scrollinfo.nMax = nMax/10;
	scrollinfo.nMin = 0;
	scrollinfo.nTrackPos = 0;
	scrollinfo.nPos = 0;
	SetScrollInfo(type,&scrollinfo);
}

void CIPRecorderDlg::InitScroll()
{
	SetHideScroll(SB_VERT);
	SetHideScroll(SB_HORZ);
}

void CIPRecorderDlg::InitSuitSizeDialog()
{
	int cx,cy;
	CRect rect;

	GetWindowRect(&m_rect);
	m_rectCurrent = m_rectSample = m_rect;
	
    cx = GetSystemMetrics(SM_CXSCREEN);
	cy = GetSystemMetrics(SM_CYSCREEN);
	
	rect = m_rect;
	if(m_rect.Width() > cx)  //当对话框的宽度大于屏幕大小时，需要调整对话框宽度。
	{
		rect.left = 10;
		rect.right = cx - 10;
		SetScrollValue(SB_HORZ,100,m_rect.Width());
	}
	
	if(m_rect.Height() > cy)
	{
		rect.top = 10;
		rect.bottom = cy - 40;
		
		SetScrollValue(SB_VERT,100,m_rect.Height());
	}
	MoveWindow(&rect);
	m_rect = m_rectCurrent = rect;
	IsWork = TRUE;
}

void CIPRecorderDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	if(pScrollBar != NULL)   //=NULL表示是系统滚动条，否则为m_slider控件滚动条
	{
		CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
		return;
	}
	GetScrollInfo(SB_HORZ,&scrollinfo,SIF_ALL);
	switch(nSBCode)
	{
	case SB_LINERIGHT:
		scrollinfo.nPos +=1;
		retCx +=1;
		if(scrollinfo.nPos >scrollinfo.nMax)
		{
			scrollinfo.nPos = scrollinfo.nMax;
			break;
		}
		SetScrollInfo(SB_HORZ,&scrollinfo,SIF_ALL);
		ScrollWindow(-10,0);
		break;
	case SB_LINELEFT:
		scrollinfo.nPos -=1;
		retCx -= 1;
		if(scrollinfo.nPos < scrollinfo.nMin)
		{
			scrollinfo.nPos = scrollinfo.nMin;
			break;
		}
		SetScrollInfo(SB_HORZ,&scrollinfo,SIF_ALL);
		ScrollWindow(10,0);
		break;
	case SB_PAGELEFT:
		scrollinfo.nPos -=5;
		retCx -= 5;
		if(scrollinfo.nPos < scrollinfo.nMin)
		{
			scrollinfo.nPos = scrollinfo.nMin;
			break;
		}
		SetScrollInfo(SB_HORZ,&scrollinfo,SIF_ALL);
		ScrollWindow(10*5,0);
		break;
	case SB_PAGERIGHT:
		scrollinfo.nPos +=5;
		retCx += 5;
		if(scrollinfo.nPos >scrollinfo.nMax)
		{
			scrollinfo.nPos = scrollinfo.nMax;
			break;
		}
		SetScrollInfo(SB_HORZ,&scrollinfo,SIF_ALL);
		ScrollWindow(-10*5,0);
		break;
	case SB_THUMBPOSITION:
	case SB_ENDSCROLL:
		break;
	case SB_THUMBTRACK:
		ScrollWindow((scrollinfo.nPos - nPos)*10,0);
		scrollinfo.nPos = nPos;
		retCx = nPos;
		SetScrollInfo(SB_HORZ,&scrollinfo,SIF_ALL);
		break;
	}
	
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CIPRecorderDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	CRect rect,rect1;
	if(!IsWork)
		return;
	GetScrollInfo(SB_HORZ,&scrollinfo,SIF_ALL);
	
	if(m_rectSample.Width() > cx)
	{
		GetWindowRect(&rect1);
		GetDlgItem(IDC_LIST1)->GetWindowRect(&rect);
		ScrollWindow(rect1.left - rect.left + 20,0);
		//	SetScrollValue(SB_HORZ,(int)((cx-120)*(cx-120)/(double)m_rectSample.Width()),m_rectSample.Width());
		SetScrollValue(SB_HORZ,100,m_rectSample.Width());
	}
	else
	{
		GetWindowRect(&rect1);
		GetDlgItem(IDC_LIST1)->GetWindowRect(&rect);
		ScrollWindow(rect1.left - rect.left + 20,0);
		SetHideScroll(SB_HORZ);	
	}
	
	if(m_rectSample.Height() > cy)
	{
		GetWindowRect(&rect1);
		GetDlgItem(IDC_LIST1)->GetWindowRect(&rect);
		ScrollWindow(0,rect1.top - rect.top + 80);
		SetScrollValue(SB_VERT,100,m_rectSample.Height());
	}
	else
	{
		GetWindowRect(&rect1);
		GetDlgItem(IDC_LIST1)->GetWindowRect(&rect);
		ScrollWindow(0,rect1.top - rect.top + 80);
		
		SetHideScroll(SB_VERT);
	}
	GetWindowRect(&m_rectCurrent);
}

void CIPRecorderDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	CString str;
	int MaxLen=0;
	GetScrollInfo(SB_VERT,&scrollinfo,SIF_ALL);
	switch(nSBCode)
	{
	case SB_LINEDOWN:
		scrollinfo.nPos +=1;
		retCy += 1;
		if(scrollinfo.nPos >scrollinfo.nMax)
		{
			scrollinfo.nPos = scrollinfo.nMax;
			break;
		}
		SetScrollInfo(SB_VERT,&scrollinfo,SIF_ALL);
		ScrollWindow(0,-10);
		break;
	case SB_LINEUP:
		scrollinfo.nPos -=1;
		retCy -= 1;
		if(scrollinfo.nPos < scrollinfo.nMin)
		{
			scrollinfo.nPos = scrollinfo.nMin;
			break;
		}
		SetScrollInfo(SB_VERT,&scrollinfo,SIF_ALL);
		ScrollWindow(0,10);
		break;
	case SB_PAGEUP:
		scrollinfo.nPos -=5;
		retCy -= 5;
		if(scrollinfo.nPos < scrollinfo.nMin)
		{
			scrollinfo.nPos = scrollinfo.nMin;
			break;
		}
		SetScrollInfo(SB_VERT,&scrollinfo,SIF_ALL);
		ScrollWindow(0,10*5);
		break;
	case SB_PAGEDOWN:
		scrollinfo.nPos +=5;
		retCy += 5;
		if(scrollinfo.nPos >scrollinfo.nMax)
		{
			scrollinfo.nPos = scrollinfo.nMax;
			break;
		}
		SetScrollInfo(SB_VERT,&scrollinfo,SIF_ALL);
		ScrollWindow(0,-10*5);
		break;
	case SB_THUMBPOSITION:
	case SB_ENDSCROLL:
		break;
	case SB_THUMBTRACK:
		ScrollWindow(0,(scrollinfo.nPos - nPos)*10);
		scrollinfo.nPos = nPos;
		retCy = nPos;
		SetScrollInfo(SB_VERT,&scrollinfo,SIF_ALL);
		break;
	}

	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CIPRecorderDlg::OnCheckRecSame() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
}

void CIPRecorderDlg::OnChangeEditInitThreadpairs() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData();
}

void CIPRecorderDlg::OnChangeEditInitTotalresources() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData();
}

BOOL CIPRecorderDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
		return TRUE;
	
	return CDialog::PreTranslateMessage(pMsg);
}

void CIPRecorderDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
/*	    CExitPwdDlg  Exitdlg;
//	AfxGetApp()->m_pMainWnd = &Exitdlg;
	int nResponse = Exitdlg.DoModal();
	if (Exitdlg.pwd==1) //correct pwd 
	{
		Exitdlg.pwd=0;

		CDialog::OnClose();	
	}
	if (Exitdlg.pwd==2)
	{
		Exitdlg.pwd=0;
		return; 
	}*/
	CDialog::OnClose();	
		
}

void CIPRecorderDlg::OnBUTTONExitIPR() 
{
	// TODO: Add your control notification handler code here
		// TODO: Add your message handler code here and/or call default
	CExitPwdDlg  Exitdlg;
//	AfxGetApp()->m_pMainWnd = &Exitdlg;
	int nResponse = Exitdlg.DoModal();
	if (Exitdlg.pwd==1) //correct pwd 
	{
		Exitdlg.pwd=0;

		CDialog::OnClose();	
	//	CIPRecorderDlg::OnClose();
		PostQuitMessage(0);
	}
	if (Exitdlg.pwd==2)
	{
		Exitdlg.pwd=0;
		return; 
	}
	
}
