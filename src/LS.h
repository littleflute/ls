// LS.h : main header file for the LS application
//

#if !defined(AFX_LS_H__1459EA76_79FA_4A8C_8994_4D9A7A9647B2__INCLUDED_)
#define AFX_LS_H__1459EA76_79FA_4A8C_8994_4D9A7A9647B2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CLSApp:
// See LS.cpp for the implementation of this class
//

class CLSApp : public CWinApp
{
public:
	CLSApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLSApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CLSApp)
	afx_msg void OnAppAbout();
	afx_msg void OnFileOpen();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LS_H__1459EA76_79FA_4A8C_8994_4D9A7A9647B2__INCLUDED_)
