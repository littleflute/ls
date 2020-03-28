// LS.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "LS.h"

#include "MainFrm.h"
#include "LSDoc.h"
#include "LSView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLSApp

BEGIN_MESSAGE_MAP(CLSApp, CWinApp)
	//{{AFX_MSG_MAP(CLSApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLSApp construction

CLSApp::CLSApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CLSApp object

CLSApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CLSApp initialization

BOOL CLSApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CLSDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CLSView));
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it.
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

	m_pMainWnd->DragAcceptFiles();//拖放文件 Added by HYL 2006.12.22

	return TRUE;
}


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
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	afx_msg void OnButtonTimer();
	afx_msg void OnTimer(UINT nIDEvent);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL m_bStart;
	DWORD m_dwStart;
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
	m_bStart=FALSE;
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	ON_BN_CLICKED(IDC_BUTTON_TIMER, OnButtonTimer)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CLSApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CLSApp message handlers


void CLSApp::OnFileOpen() 
{
	// TODO: Add your command handler code here
	CWinApp::OnFileOpen();
}

void CAboutDlg::OnButtonTimer() 
{
	// TODO: Add your control notification handler code here
	CButton *pBtn=(CButton*)GetDlgItem(IDC_BUTTON_TIMER);
	if(m_bStart){
		m_bStart=FALSE;
		KillTimer(1);
		pBtn->SetWindowText("开始");
		
		CStatic *pStc=(CStatic*)GetDlgItem(IDC_STATIC_TIMER3);
					
		int t=::GetTickCount()-m_dwStart;
		CString str;
		str.Format("J=%d",60*10*1000/t);
		pStc->SetWindowText(str);

	}
	else{
		m_bStart=TRUE;
		SetTimer(1,100,NULL);
		pBtn->SetWindowText("停止");

		m_dwStart=::GetTickCount();
	}
}

void CAboutDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	CStatic *pStc=(CStatic*)GetDlgItem(IDC_STATIC_TIMER);
	CTime tm=CTime::GetCurrentTime();
	
	CString str;
	str.Format("%d-%d-%d %02d:%02d:%02d",
		tm.GetYear(),tm.GetMonth(),tm.GetDay(),
		tm.GetHour(),tm.GetMinute(),tm.GetSecond());
	pStc->SetWindowText(str);

	int t=::GetTickCount()-m_dwStart;
	pStc=(CStatic*)GetDlgItem(IDC_STATIC_TIMER2);
	str.Format("%d  :  %d",t/1000,t%1000);
	pStc->SetWindowText(str);

	CDialog::OnTimer(nIDEvent);
}

BOOL CAboutDlg::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	if(m_bStart){
		m_bStart=FALSE;
		KillTimer(1);
	}
	return CDialog::DestroyWindow();
}

BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
