// ExitPwdDlg.cpp : implementation file
//

#include "stdafx.h"
#include "iprecorder.h"
#include "ExitPwdDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExitPwdDlg dialog


CExitPwdDlg::CExitPwdDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CExitPwdDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CExitPwdDlg)
	m_ExitPwd = _T("");
	//}}AFX_DATA_INIT
}


void CExitPwdDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CExitPwdDlg)
	DDX_Text(pDX, IDC_EDITExitPwd, m_ExitPwd);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CExitPwdDlg, CDialog)
	//{{AFX_MSG_MAP(CExitPwdDlg)
	ON_EN_CHANGE(IDC_EDITExitPwd, OnChangeEDITExitPwd)
	ON_BN_CLICKED(IDC_BUTTONConfirmPwd, OnBUTTONConfirmPwd)
	ON_BN_CLICKED(IDC_BUTTONCancel, OnBUTTONCancel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExitPwdDlg message handlers

void CExitPwdDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

void CExitPwdDlg::OnChangeEDITExitPwd() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
}

void CExitPwdDlg::OnBUTTONConfirmPwd() 
{
	// TODO: Add your control notification handler code here
	if (m_ExitPwd=="12345")
	{
		pwd=1;
		CDialog::OnOK();

	}
	else 
	{
		MessageBox("The password is not correct, please confirm!");
		pwd=2;

	}
	
}

void CExitPwdDlg::OnBUTTONCancel() 
{
	// TODO: Add your control notification handler code here
	CExitPwdDlg::OnCancel();
	
}
