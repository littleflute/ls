// LSDoc.cpp : implementation of the CLSDoc class
//

#include "stdafx.h"
#include "LS.h"

#include "LSDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLSDoc

IMPLEMENT_DYNCREATE(CLSDoc, CDocument)

BEGIN_MESSAGE_MAP(CLSDoc, CDocument)
	//{{AFX_MSG_MAP(CLSDoc)
	ON_COMMAND(ID_FILE_SAVE_AS_HTML, OnFileSaveAsHtml)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLSDoc construction/destruction

CLSDoc::CLSDoc()
{
	// TODO: add one-time construction code here
	
}

CLSDoc::~CLSDoc()
{
}
#include "LSView.h"
BOOL CLSDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CLSDoc serialization

void CLSDoc::Serialize(CArchive& ar)
{
	Xd_Serialize_Notes(ar);
	Xd_Serialize_Lyrics(ar);
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CLSDoc diagnostics

#ifdef _DEBUG
void CLSDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CLSDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLSDoc commands

void CLSDoc::Xd_Serialize_Lyrics(CArchive &ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
		int c=m_SL_L.GetCount();
		ar<<c;
		POSITION pos=m_SL_L.GetHeadPosition();
		while (pos) {
			CString str=m_SL_L.GetNext(pos);
			ar<<str;			
		}
	}
	else
	{
		// TODO: add loading code here
		POSITION pos=m_SL_L.GetHeadPosition();
		m_SL_L.RemoveAt(pos);
		int c;
		CString str,sl="";
		ar>>c;
		while(c){
			ar>>str;
			/*
			if(str!="\r\n"){
							sl+=str;
						}
						else {
							m_SL_L.AddTail(sl);
							sl="";
						}
						//*/
			
			m_SL_L.AddTail(str);
			c--;
		}
		m_SL_L.AddTail("  ***更多乐谱,请访问东方吉他网(http://www.dfguitar.com)，桶子鼓乐队官方网站(http://www.tongzigu.com)***");
	}

}

void CLSDoc::Xd_Serialize_Notes(CArchive &ar)
{	
	if (ar.IsStoring())
	{
		// TODO: add storing code here
		int c=m_SL_N.GetCount();
		ar<<c;
		POSITION pos=m_SL_N.GetHeadPosition();
		while (pos) {
			CString str=m_SL_N.GetNext(pos);
			ar<<str;			
		}
	}
	else
	{
		// TODO: add loading code here
		POSITION pos=m_SL_N.GetHeadPosition();
		m_SL_N.RemoveAt(pos);

		int c;
		CString str;
		CString sl="";
		ar>>c;
		while(c){
			ar>>str;
		/*
			if(str!=" \r\n"){
						sl+=str;
					}
					else {
						m_SL_N.AddTail(sl);
						sl="";
					}//*/
		
			m_SL_N.AddTail(str);
			c--;
		}
	}
}


void CLSDoc::OnFileSaveAsHtml() 
{
	// TODO: Add your command handler code here
	
	CString s;
	FILE* fp=NULL;
	CFileDialog dlg(false,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		"简谱文件(*.htm)|*.htm|",
		NULL);
	if (dlg.DoModal()!= IDOK) return;
	CString strFileName = dlg.GetFileName() + ".htm";
	char szFileName[256];
	strcpy(szFileName,strFileName.GetBuffer(strFileName.GetLength()));
	
	
	if((fp=fopen(szFileName,"w"))==NULL)
	{	
		s.Format("打开文件出错!\n");
		AfxMessageBox(s);
		return ;
	}
	//---------
	s="<html><head><script language=\"JavaScript\"><!-- ";
	s+="\nvar strnt=\"";
	fprintf(fp,"%s",s.GetBuffer(s.GetLength()));
	Xd_Nt_Save2Html(fp);
	fprintf(fp,"\"\nvar strly=\"");	
	Xd_Lyr_Save2Html(fp);
	fprintf(fp,"\";");


	FILE* fpBase=NULL;
	//
	char szTempFileName[1000];  //"base.htm"
	CString strBaseHtmFile = v_Get_Base_Htm_File();

	strcpy(szTempFileName,strBaseHtmFile.GetBuffer(strBaseHtmFile.GetLength()));
	TRACE("szTempFileName = %s",szTempFileName);
	//

	if((fpBase=fopen(szTempFileName,"r"))==NULL)
	{
		s.Format("打开文件 base.htm 出错!\n");
		AfxMessageBox(s);
		return ;
	}
	
	// 将base.htm的内容copy 到新文件中
	while(1){
		char c=fgetc(fpBase);
		if(feof(fpBase)) break;
		fputc(c,fp);
	}
	fclose(fpBase);	

	if(fp) fclose(fp);
}

void CLSDoc::Xd_Nt_Save2Html(FILE *fp)
{
	POSITION pos=m_SL_N.GetHeadPosition();
	CString s="";	
	
	CString sl;
	while (pos) {
		s=m_SL_N.GetNext(pos);
		int c=s.GetLength();	
		for(int i=0;i<(c/3);i++){
			sl=s.Left(3)+";";
			fprintf(fp,"%s",sl.GetBuffer(sl.GetLength()));
			s=s.Right(s.GetLength()-3);
		}
		fprintf(fp,"9");
	}
}

void CLSDoc::Xd_Lyr_Save2Html(FILE *fp)
{
	POSITION pos=m_SL_L.GetHeadPosition();
	CString s="";
	
	CString sl;
	while (pos) {
		s=m_SL_L.GetNext(pos);
		LPTSTR lpszRoot = s.GetBuffer(s.GetLength());
		for (LPTSTR lpsz = lpszRoot; *lpsz != '\0'; lpsz = _tcsinc(lpsz))
		{
			CString sz;
			sz=lpsz;
			LPTSTR psz=_tcsinc(lpsz);
			CString s2=psz;
			sl=sz.Left(sz.GetLength()-s2.GetLength());
			TRACE(sl);
			fprintf(fp,"%s;",sl.GetBuffer(sl.GetLength()));
		}
		fprintf(fp,"|");
	}
}

CString CLSDoc::v_Get_Base_Htm_File()
{
	char szFileNames[260]; 
	
	char szCurDir[100]; 
	DWORD dwLen = GetCurrentDirectory(MAX_PATH,szCurDir);
	dwLen = GetModuleFileName(NULL, szFileNames, sizeof(szFileNames));
	for(DWORD offset=dwLen; offset>=0; offset--)
	{
		if(szFileNames[offset] == '\\')
		{
			szFileNames[offset] = 0;
			break;
		}
	}
	CString str;
	str.Format("%s\\Base.htm",szFileNames);
	return str;

}

void CLSDoc::DeleteContents() 
{
	// TODO: Add your specialized code here and/or call the base class
		
	m_SL_N.RemoveAll();
	m_SL_L.RemoveAll();
	m_SL_N.AddTail("");
	m_SL_L.AddTail("");
	
	CMainFrame* pMFrm=(CMainFrame*) AfxGetMainWnd();
	if(pMFrm){
		CLSView* pView = (CLSView*) pMFrm->GetActiveView();
	//	pView->Xd_Nt_SetCaret(0,0);
		pView->Xd_Init();
	}

	CDocument::DeleteContents();
}
