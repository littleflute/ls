// XDScriptDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LS.h"
#include "XDScriptDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXDScriptDlg dialog


CXDScriptDlg::CXDScriptDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CXDScriptDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CXDScriptDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CXDScriptDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CXDScriptDlg)
	DDX_Control(pDX, IDC_EDIT_SCRIPT, m_EditScript);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CXDScriptDlg, CDialog)
	//{{AFX_MSG_MAP(CXDScriptDlg)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXDScriptDlg message handlers

BOOL CXDScriptDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CString s="";
	POSITION pos=m_pDoc->m_SL_L.GetHeadPosition();
	while (pos) {
		s+=m_pDoc->m_SL_L.GetNext(pos);
		s+="\r\n";
	}
	SetDlgItemText(IDC_EDIT_SCRIPT,s);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CXDScriptDlg::OnOK() 
{
	// TODO: Add extra validation here
	int i, nLineCount = m_EditScript.GetLineCount();//得到行数
	CString strLine;
	char psz[1280];


	m_pDoc->m_SL_L.RemoveAll();
	for (i=0;i < nLineCount;i++)
	{
		int nIndex=m_EditScript.LineIndex(i);
		int nLength=m_EditScript.LineLength(nIndex);

		m_EditScript.GetLine(i, psz);
		psz[nLength]=0;
	
		strLine.Format(("%s"),psz);
//		afxDump << strLine;
		m_pDoc->m_SL_L.AddTail(strLine);
	}
	
	CDialog::OnOK();
}

int CXDScriptDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	
	return 0;
}

BOOL CXDScriptDlg::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CDialog::Create(IDD, pParentWnd);
}
