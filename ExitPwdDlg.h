#if !defined(AFX_EXITPWDDLG_H__A18C523F_178F_41DF_8C5C_B1AAD041977F__INCLUDED_)
#define AFX_EXITPWDDLG_H__A18C523F_178F_41DF_8C5C_B1AAD041977F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ExitPwdDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CExitPwdDlg dialog

class CExitPwdDlg : public CDialog
{
// Construction
public:
	CExitPwdDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CExitPwdDlg)
	enum { IDD = IDD_DIALOGExitConfirm };
	CString	m_ExitPwd;
	int pwd;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExitPwdDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CExitPwdDlg)
	virtual void OnOK();
	afx_msg void OnChangeEDITExitPwd();
	afx_msg void OnBUTTONConfirmPwd();
	afx_msg void OnBUTTONCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXITPWDDLG_H__A18C523F_178F_41DF_8C5C_B1AAD041977F__INCLUDED_)
