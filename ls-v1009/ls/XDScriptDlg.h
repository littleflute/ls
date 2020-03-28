#if !defined(AFX_XDSCRIPTDLG_H__1E794973_C348_48E6_B363_A640DFB021C6__INCLUDED_)
#define AFX_XDSCRIPTDLG_H__1E794973_C348_48E6_B363_A640DFB021C6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// XDScriptDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CXDScriptDlg dialog

class CXDScriptDlg : public CDialog
{
// Construction
public:
	CXDScriptDlg(CWnd* pParent = NULL);   // standard constructor
	CLSDoc * m_pDoc;

// Dialog Data
	//{{AFX_DATA(CXDScriptDlg)
	enum { IDD = IDD_DLG_SCRIPT };
	CEdit	m_EditScript;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXDScriptDlg)
	public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CXDScriptDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XDSCRIPTDLG_H__1E794973_C348_48E6_B363_A640DFB021C6__INCLUDED_)
