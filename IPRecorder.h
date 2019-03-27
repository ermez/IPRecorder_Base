// IPRecorder.h : main header file for the IPRECORDER application
//

#if !defined(AFX_IPRECORDER_H__C3E6F367_4FB9_4CBA_B8A3_23B2B9F70B19__INCLUDED_)
#define AFX_IPRECORDER_H__C3E6F367_4FB9_4CBA_B8A3_23B2B9F70B19__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CIPRecorderApp:
// See IPRecorder.cpp for the implementation of this class
//

class CIPRecorderApp : public CWinApp
{
public:
	CIPRecorderApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIPRecorderApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CIPRecorderApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IPRECORDER_H__C3E6F367_4FB9_4CBA_B8A3_23B2B9F70B19__INCLUDED_)
