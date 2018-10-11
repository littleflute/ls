#if !defined(AFX_DLGKBMIDI_H__FF929DB7_953F_408C_B99A_03518A165EDF__INCLUDED_)
#define AFX_DLGKBMIDI_H__FF929DB7_953F_408C_B99A_03518A165EDF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgKBMidi.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgKBMidi dialog

class CDlgKBMidi : public CDialog
{
// Construction
public:
	CDlgKBMidi(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgKBMidi)
	enum { IDD = IDD_DLG_KBMIDI };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgKBMidi)
	public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgKBMidi)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGKBMIDI_H__FF929DB7_953F_408C_B99A_03518A165EDF__INCLUDED_)
