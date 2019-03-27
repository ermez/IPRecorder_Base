// IPRecorderDlg.h : header file
//

#if !defined(AFX_IPRECORDERDLG_H__9098ACCB_EF0C_4174_A7F3_903894F99919__INCLUDED_)
#define AFX_IPRECORDERDLG_H__9098ACCB_EF0C_4174_A7F3_903894F99919__INCLUDED_

#include "shpa3api.h"	//暂时先在当前工程中加上驱动头文件，升级时再统一

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MAX_SLAVER_COUNT 6

#define IPR_CH 25
#define IPA_CH 26

#define PCM_8	1
#define PCM_16	-2
#define A_LAW	6
#define U_LAW	7
#define ADPCM	17
#define VOX		23
#define GSM		49
#define MP3		85
#define GC8		131
#define G729A	65411

enum CH_RECORD //Record state
{
    UNRECORD			= 0,            //		Unrecord 
	RECORDING			= 1             //		Record
};

enum DIRECTION //call dir
{
	UNKNOWN				= 0,             //  Unknown 
	UP					= 1,             //  Call out
	DOWN				= 2,             //  Call in
};
#define  MAX_CALLID_LEN 50
#define  MAX_IP_LEN 30
#pragma pack(1)
typedef struct tagCHANNEL_INFO{
	int			nChType;					//		Channel type
	int			nPtlType;					//		Protocol type
	int			nStationId;					//		Station ID
	int			nWorkState;					//		Channel state
	int			nRecSlaverId;				//		Destination Slaver
	int			nCallRef;					//		Call reference
	BOOL		bCallActive;
	BOOL		bRecording;
	DWORD		dwSessionId;				//		Session ID
	int			nFowardingPPort;			//		Primary forwarding port
	int			nFowardingSPort;			//		Secondary forwarding port
	int			nIsRecord;					//		Record state
	char	    szCallerID[MAX_CALLID_LEN];	//		CallerID
	char	    szCalledID[MAX_CALLID_LEN];	//		CalledID
	char		szIPP[MAX_IP_LEN];			//		IP address of primary
	char		szIPS[MAX_IP_LEN];			//		IP address of slavery
	int			nDir;						//		Call dir 
	int			nStatistics;				//		Call Statistics
}CHANNEL_INFO, *PCHANNEL_INFO;				//		Channel structure
#pragma pack()

/////////////////////////////////////////////////////////////////////////////
// CIPRecorderDlg dialog

class CIPRecorderDlg : public CDialog
{
// Construction
private:
	CRect m_rect;       //取界面初始化时的大小，目前情况下与m_rectSample值相同。
	CRect m_rectSample; //参照的大小，即界面所有控件可以正常可视时的大小。
	CRect m_rectCurrent; //当前的大小
	int retCx;      //用于恢复到最初的大小
	int retCy;
	int IsWork;
	SCROLLINFO scrollinfo;
public:		
	void InitSuitSizeDialog();
	void InitScroll();
	void SetScrollValue(int type,int nPage,int nMax);
	void SetHideScroll(int type);
	BOOL bTrialEdition;
	DWORD dwStartTime;
	DWORD dwCurrentTime;
	int   nIPRBoardId;
	int	  nIPABoardId;
	int   nSlaverCount;
	IPR_SLAVERADDR IPR_SlaverAddr[MAX_SLAVER_COUNT];
	int   nSlaverSelectedIndex;
	CHANNEL_INFO ChannelInfo[1000];
	BOOL bErrorOccurred;
	char  szErrMsg[400];
	char szCurrentDir[MAX_PATH], szRecFilePath[MAX_PATH];
	int   MaxLine;
	int  nIPRChNum;
	int  nUsedIPRChNum;
	int  nIPAChNum;
	BOOL bSlaverConnectChanged;	//some slaver connected or disconnected happen
	BOOL bUpdateSlaverDisplay;
	int  nRecCodec;
	static int CALLBACK EventCallback(PSSM_EVENT pEvent);
	BOOL  InitCtiSystem();
	void  InitUI();
	void  InitChannelList();
	void  InitChannelState();
	void  UpdateSlaverDisplay();
	void  EventDisplay(LPSTR lpStr, PSSM_EVENT pEvent);
	void  ScanSlaver();

	CIPRecorderDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CIPRecorderDlg)
	enum { IDD = IDD_IPRECORDER_DIALOG };
	CTreeCtrl	m_TreeCtrlErrDisplay;
	CTreeCtrl	m_TreeCtrlEventDisplay;
	CComboBox	m_cbSlaverID;
	CListCtrl	m_ChannelList;
	CString	m_strIP;
	CString	m_strPort;
	int		m_nInitThreadPairs;
	int		m_nInitTotalResources;
	int		m_nThreadPairs;
	int		m_nTotalResources;
	int		m_nUsedResources;
	CString	m_szSlaverState;
	BOOL	m_bShowEvent;
	BOOL	m_bAutoClearEvent;
	int		m_nRecCodec;
	long	m_lTotalStatistics;
	CString	m_strSelectedFolder;
	BOOL	m_bRecOverWrite;
	UINT	m_nTotalFile;
	UINT	m_nRecordError;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIPRecorderDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CIPRecorderDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDestroy();
	afx_msg void OnButtonStartslaver();
	afx_msg void OnButtonCloseslaver();
	afx_msg void OnSelchangeComboSlaverid();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnCheckShowevent();
	afx_msg void OnButtonClearevent();
	afx_msg void OnCheckAutoclearevent();
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	afx_msg void OnRadio3();
	afx_msg void OnRadio4();
	afx_msg void OnRadio5();
	afx_msg void OnRadio6();
	afx_msg void OnRadio7();
	afx_msg void OnRadio8();
	afx_msg void OnRadio9();
	afx_msg void OnRadio10();
	afx_msg void OnButtonClearerror();
	afx_msg void OnButtonFolderselect();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnCheckRecSame();
	afx_msg void OnChangeEditInitThreadpairs();
	afx_msg void OnChangeEditInitTotalresources();
	afx_msg void OnClose();
	afx_msg void OnBUTTONExitIPR();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IPRECORDERDLG_H__9098ACCB_EF0C_4174_A7F3_903894F99919__INCLUDED_)
