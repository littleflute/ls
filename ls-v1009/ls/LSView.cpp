// LSView.cpp : implementation of the CLSView class
//

#include "stdafx.h"
#include "LS.h"

#include "LSDoc.h"
#include "LSView.h" 
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif 

/////////////////////////////////////////////////////////////////////////////
// CLSView

IMPLEMENT_DYNCREATE(CLSView, CScrollView)

BEGIN_MESSAGE_MAP(CLSView, CScrollView)
	//{{AFX_MSG_MAP(CLSView)
	ON_WM_CHAR()
	ON_COMMAND(ID_VIEW_FONT, OnViewFont)
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_SETCURSOR()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	ON_COMMAND(ID_XD_LYRICS, OnXdLyrics)
	ON_UPDATE_COMMAND_UI(ID_XD_LYRICS, OnUpdateXdLyrics)
	ON_COMMAND(ID_XD_NOTE, OnXdNote)
	ON_UPDATE_COMMAND_UI(ID_XD_NOTE, OnUpdateXdNote)
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_XD_LYRICS_SCRIPT, OnXdLyricsScript)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_COMMAND(ID_BMP_SAVE, OnBmpSave)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLSView construction/destruction

CLSView::CLSView()
{
	// TODO: add construction code here
	Xd_Init();

	m_clrText=RGB(0,0,0);
	xddbg=0;
	m_idxN_SX1=0;
	m_idxN_SY1=0;
	m_idxN_SX2=0;
	m_idxN_SY2=0;
	m_bNtLBntDown=FALSE;
	m_ScrlSize=CSize(0,0);

	m_Type=XD_TYPE_NOTE;

//	m_SL_L.AddTail("");
	m_LidxY=0;
	m_bLyrLBntDown=FALSE;
	m_bLSel=FALSE;
	m_xSel1=m_xSel2=m_ySel1=m_ySel2=0;
	pFont=NULL;
}

CLSView::~CLSView()
{
	if(pFont!=NULL)	{
		delete pFont;
		TRACE("delete pFont;  --- ~CLSView().");
	}
}

BOOL CLSView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CLSView drawing

void CLSView::OnDraw(CDC* pDC)
{
	CLSDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here	
	pDC->Rectangle(0,0,m_ScrlSize.cx,m_ScrlSize.cy);	
	Xd_Nt_Draw_List(pDC);
	Xd_Lyr_Draw(pDC);	
	Xd_Update_Scrl_Size();
}

void CLSView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CDC *pDC=GetDC();
	if(!pFont){
		pFont=new CFont();	
		TRACE("pFont=new CFont();  --- OnInitialUpdate().");
		if(!(pFont->CreateFont(-27,0,
			0,0,FW_NORMAL,FALSE,FALSE,FALSE,		
			ANSI_CHARSET,OUT_TT_PRECIS,CLIP_TT_ALWAYS,		
			DEFAULT_QUALITY,DEFAULT_PITCH,"宋体")))		
		{		
			pFont->CreateStockObject(SYSTEM_FONT);		
		}		
	}
	ReleaseDC(pDC);
	
	SetScrollSizes(MM_TEXT, m_ScrlSize);
	
	Xd_Nt_MakeCaret(10,10);
}

/////////////////////////////////////////////////////////////////////////////
// CLSView printing

BOOL CLSView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CLSView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CLSView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CLSView diagnostics

#ifdef _DEBUG
void CLSView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CLSView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CLSDoc* CLSView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLSDoc)));
	return (CLSDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLSView message handlers

void CLSView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default

	switch(m_Type) {


	case XD_TYPE_NOTE:
		Xd_Nt_Char_To_List(nChar);
		Xd_Update_Scrl_Size();
		break;
	case XD_TYPE_LYRICS:
		Xd_Lyr_Char(nChar);
		break;
	default:
		break;
	}
//	Invalidate();
	CScrollView::OnChar(nChar, nRepCnt, nFlags);
}

void CLSView::OnViewFont() 
{
	// TODO: Add your command handler code here
	CFontDialog dlg;
	if(dlg.DoModal()==IDOK)		
	{		
		LOGFONT LF;			
		dlg.GetCurrentFont(&LF);//获取所选字体的信息	
		//在选择字体时并没有选出颜色
		m_clrText=dlg.GetColor();//通过这一句代码可选出颜色.		
		pFont->DeleteObject();		
		pFont->CreateFontIndirect(&LF);//建立新的字体		
	}	
	switch(m_Type) {
	case XD_TYPE_NOTE:
		Xd_Nt_MakeCaret(m_idxN_X,m_idxN_Y);
		break;
	case XD_TYPE_LYRICS:
		Xd_Lyr_MakeCaret(0,0);
		break;
	default:
		break;
	}
	Invalidate();

}

void CLSView::Xd_Nt_Char(UINT nChar)//本函数已经不用
{
	char cTone=m_strN.GetAt(2);
	char cTime=m_strN.GetAt(1);
	char c;
	switch(nChar) {
	case VK_BACK:
		c=m_strN.GetAt(0);
		if(c==' '){
			m_strLineOfNt=m_strLineOfNt.Left(m_strLineOfNt.GetLength()-3);
		}
		else
			m_strN=" 03";
		break;
	case VK_RETURN:
		m_strN="n03";
		m_strLineOfNt+=m_strN;
		m_strN=" 03";
		break;
	case VK_SPACE:
		m_strLineOfNt+=m_strN;
		m_strN=" 03";
		break;

	case 'i':
	case 'I':
		cTone++;
		TRACE("cTone=%c",cTone);
		if(cTone>'5') cTone='5';
		m_strN.SetAt(2,cTone);
		break;
	case 'm':
	case 'M':
		cTone--;
		TRACE("cTone=%c",cTone);
		if(cTone<'1') cTone='1';
		m_strN.SetAt(2,cTone);
		break;
	case '/':
		cTime++;		
		if(cTime>'2') cTime='0';
		m_strN.SetAt(1,cTime);
		break;		
	case '.':
	case '|':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '0':
		m_strN.SetAt(0,nChar);
		break;
	default:
		break;
	}
}

void CLSView::Xd_Nt_Draw_One(CDC* pDC,int x,int y,CString strN)
{
	char cTone=strN.GetAt(2);
	char cTime=strN.GetAt(1);
	char cNt=strN.GetAt(0);

	TEXTMETRIC tm;
	pDC->GetTextMetrics(&tm);
	int tmY=tm.tmHeight;
	int tmX=tm.tmAveCharWidth;
	int yL1=y-tmY/2;
	int xL1=x,xL2=x+tmX;
	if(cNt=='#'||cNt=='b'){
		pDC->TextOut(x,y-tmY*1/5,cNt);
	}
	else if(cNt=='='){
		pDC->MoveTo(x+tmX/2,y-tmY/4);
		pDC->LineTo(x+tmX/2,y+tmY/2);
		pDC->LineTo(x+tmX/2+tmX/4,y+tmY/3);
		pDC->MoveTo(x+tmX/2,y+tmY/4);
		pDC->LineTo(x+tmX/2+tmX/4,y+tmY/4-tmY/4);
		pDC->LineTo(x+tmX/2+tmX/4,y+tmY/4+tmY/2);
	}
	else if(cNt=='{'){
		pDC->MoveTo(x+tmX*2,y-tmY*3/4);
		pDC->LineTo(x+tmX*3/2,y-tmY*3/4);
		pDC->LineTo(x+tmX*5/4,y-tmY/2);
	}
	else if(cNt=='/'){
		pDC->MoveTo(x-tmX/2,y-tmY/3);
		pDC->LineTo(x,y-tmY/2);		
	}
	else if(cNt=='\\'){	
		pDC->MoveTo(x+tmX,y-tmY/2);
		pDC->LineTo(x+tmX*3/2,y-tmY/3);
	}
	else if(cNt=='w'){
		pDC->MoveTo(x+tmX*2-tmX/2,y-tmY/3);
		pDC->LineTo(x+tmX*2,y-tmY/2);		
		pDC->LineTo(x+tmX*2+tmX*(cTone-'3'+1),y-tmY/2);
		pDC->LineTo(x+tmX*2+tmX*(cTone-'3'+1)+tmX/2,y-tmY/3);		
	}
	else if(cNt=='W'){
		pDC->MoveTo(x+tmX*2-tmX/2,y-tmY/3-tmY/4);
		pDC->LineTo(x+tmX*2,y-tmY/2-tmY/4);		
		pDC->LineTo(x+tmX*2+tmX*(cTone-'3'+1),y-tmY/2-tmY/4);
		pDC->LineTo(x+tmX*2+tmX*(cTone-'3'+1)+tmX/2,y-tmY/3-tmY/4);		
	}
	
	else if(cNt=='f'){
		pDC->MoveTo(x+tmX*2-tmX/2,y-tmY/3-tmY/4);
		pDC->LineTo(x+tmX*2,y-tmY/2-tmY/4);		
		pDC->LineTo(x+tmX*2+tmX*(cTone-'2'+1),y-tmY/2-tmY/4);
		pDC->LineTo(x+tmX*2+tmX*(cTone-'2'+1)+tmX/2,y-tmY/3-tmY/4);	
		switch(cTime)
		{
		case '0':
			pDC->TextOut(x+tmX*3,y-tmY*5/4,"1");   
			break;
		case '1':
			pDC->TextOut(x+tmX*3,y-tmY*5/4,"2");   
			break;
		case '2':
			pDC->TextOut(x+tmX*3,y-tmY*5/4,"3");   
			break;
		case '3':
			pDC->TextOut(x+tmX*3,y-tmY*5/4,"4");   
			break;
		}		
	}
	else if(cNt=='T'){//三连音连线
		pDC->MoveTo(x+tmX*2-tmX/2,y-tmY/3-tmY/4);
		pDC->LineTo(x+tmX*2,y-tmY/2-tmY/4);		
		pDC->LineTo(x+tmX*(5),y-tmY/2-tmY/4);
		pDC->LineTo(x+tmX*(5)+tmX/2,y-tmY/3-tmY/4);
		pDC->TextOut(x+tmX*3,y-tmY*5/4,"3");		
	}
	else if(cNt=='t'){//三连音连线
		pDC->MoveTo(x+tmX*2-tmX/2,y-tmY/3);
		pDC->LineTo(x+tmX*2,y-tmY/2);		
		pDC->LineTo(x+tmX*(5),y-tmY/2);
		pDC->LineTo(x+tmX*(5)+tmX/2,y-tmY/3);
		pDC->TextOut(x+tmX*3,y-tmY,"3");		
	}
	else if(cNt=='['){
		pDC->TextOut(x-tmY*1/10,y,"|");
		pDC->TextOut(x+tmY*1/10,y,"|");
	}
	else if(cNt=='o'||cNt=='O'){	
		int dy,dx;
		dy=y-tmY*(cTime-'0'+1);
		dx=x+tmX*(cTone-'3');
	//	pDC->TextOut(dx,dy,cNt);	
		pDC->Rectangle(dx,dy,dx+tmX,dy+tmX);
		pDC->Ellipse(dx,dy,dx+tmX,dy+tmX);
		pDC->MoveTo(dx-tmX/4,dy+tmX/2);
		pDC->LineTo(dx+tmX+tmX/4,dy+tmX/2);
		pDC->MoveTo(dx+tmX/2,dy-tmX/4);
		pDC->LineTo(dx+tmX/2,dy+tmX+tmX/4);
	}
	else if(cNt=='s'||cNt=='S'){	
		int dy,dx;
		dy=(int)(y-tmY*(cTime-'0'+1.5));
		dx=x+tmX*(cTone-'3');
		pDC->TextOut(dx,dy,cNt);	
		pDC->TextOut(dx-tmX/2,dy-tmY/4,".");
		pDC->TextOut(dx+tmX,dy-tmY/4,".");
		pDC->MoveTo(dx-tmX/4,dy+tmY);
		pDC->LineTo(dx+tmX,dy+tmY/4);
	}
	else if(cNt=='d'||cNt=='D'){	
		int dy,dx;
		dy=y+tmY;
		dx=x+tmX*(cTone-'3');
		pDC->TextOut(dx,dy,"D.S.");
	}
	else
		pDC->TextOut(x,y,cNt);

	if(cNt=='o'||cNt=='O'||'f'==cNt) return;//不再画音高和时值
	if(cNt=='d'||cNt=='D') return;//不再画音高和时值
	if(cNt=='s'||cNt=='S') return;//不再画音高和时值
	
	int dTime=y+tmY*4/5;
	
	if(cTime=='1'){
		dTime+=tmY/5;
		pDC->TextOut(x,dTime-tmY*1/2,'-');
		/*
		pDC->MoveTo(x,dTime);
		pDC->LineTo(x+tmX,dTime);
		//*/
	}
	else if(cTime=='2'){
		dTime+=tmY/5;
		pDC->TextOut(x,dTime-tmY*1/2,'-');
		/*
		pDC->MoveTo(x,dTime);
		pDC->LineTo(x+tmX,dTime);
		//*/
		dTime+=tmY/5;
		pDC->TextOut(x,dTime-tmY*1/2,'-');
		/*
		pDC->MoveTo(x,dTime);
		pDC->LineTo(x+tmX,dTime);
		//*/
	}
	else if(cTime=='3'){
		dTime+=tmY/5;
		pDC->TextOut(x,dTime-tmY*1/2,'-');
		dTime+=tmY/5;
		pDC->TextOut(x,dTime-tmY*1/2,'-');
		dTime+=tmY/5;
		pDC->TextOut(x,dTime-tmY*1/2,'-');

	}

	if(cNt=='w'||cNt=='t'||cNt=='W'||cNt=='T') return;//不再画音高
	
	CSize sz=pDC->GetTextExtent(cNt);
	x+=sz.cy*1/8;
	int dTnUnder=dTime-tmY*3/5;
	if(cTone=='1'){
		pDC->TextOut(x,dTnUnder,".");
		dTnUnder+=tmY/5;
		pDC->TextOut(x,dTnUnder,".");
	}
	else if(cTone=='2'){
		pDC->TextOut(x,dTnUnder,".");
	}
	else if(cTone=='4'){
		dTnUnder=y-tmY*4/5;
		pDC->TextOut(x,dTnUnder,".");
	}
	else if(cTone=='5'){
		dTnUnder=y-tmY*4/5;
		pDC->TextOut(x,dTnUnder,".");
		dTnUnder=y-tmY;
		pDC->TextOut(x,dTnUnder,".");
	}
	if(cTone=='1'+5){
		pDC->TextOut(x,dTnUnder,".");
		dTnUnder+=tmY/5;
		pDC->TextOut(x,dTnUnder,".");

		pDC->MoveTo(xL1,yL1);
		pDC->LineTo(xL2,yL1);
	}
	else if(cTone=='2'+5){
		pDC->TextOut(x,dTnUnder,".");
		pDC->MoveTo(xL1,yL1);
		pDC->LineTo(xL2,yL1);
	}
	else if(cTone=='3'+5){
		pDC->MoveTo(xL1,yL1);
		pDC->LineTo(xL2,yL1);
	}
	else if(cTone=='4'+5){
		dTnUnder=y-tmY*4/5;
		pDC->TextOut(x,dTnUnder,".");
		pDC->MoveTo(xL1,yL1);
		pDC->LineTo(xL2,yL1);
	}
	else if(cTone=='5'+5){
		dTnUnder=y-tmY*4/5;
		pDC->TextOut(x,dTnUnder,".");
		dTnUnder=y-tmY;
		pDC->TextOut(x,dTnUnder,".");
		pDC->MoveTo(xL1,yL1);
		pDC->LineTo(xL2,yL1);
	}
}


void CLSView::Xd_Nt_Char_To_List(UINT nChar)
{	
	CLSDoc *pDoc=GetDocument();

	POSITION pos = pDoc->m_SL_N.FindIndex(m_idxN_Y);
	if(pos)	m_strLineOfNt=pDoc->m_SL_N.GetAt(pos);

	char cTone=m_strN.GetAt(2);
	char cTime=m_strN.GetAt(1);
	char c=m_strN.GetAt(0);
	
	switch(nChar) {
	case VK_BACK:
		if(c==' '&&!(m_strN.GetAt(0)!=' '||m_strN.GetAt(1)=='1'||m_strN.GetAt(1)=='2'||
			m_strN.GetAt(2)=='1'||
			m_strN.GetAt(2)=='2'||
			m_strN.GetAt(2)=='4'||
			m_strN.GetAt(2)=='5'))
		{
			if(m_strLeftOfCaret.GetLength()>0){
			//	m_strRightOfCaret=m_strLeftOfCaret.Right(3)+m_strRightOfCaret;
				m_strLeftOfCaret=m_strLeftOfCaret.Left(m_strLeftOfCaret.GetLength()-3);
				m_strLineOfNt=m_strLeftOfCaret+m_strRightOfCaret;
				pDoc->m_SL_N.SetAt(pos,m_strLineOfNt);
			}
			else if(m_idxN_Y>0){
				pDoc->m_SL_N.RemoveAt(pos);				
				m_idxN_Y--;
				pos=pDoc->m_SL_N.FindIndex(m_idxN_Y);
				m_strLeftOfCaret=pDoc->m_SL_N.GetAt(pos);
				m_strLineOfNt=m_strLeftOfCaret+m_strRightOfCaret;
				pDoc->m_SL_N.SetAt(pos,m_strLineOfNt);
			}
		}
		else
			m_strN=" 03";
		break;
	case VK_RETURN:
		pDoc->m_SL_N.SetAt(pos,m_strLeftOfCaret);
		pDoc->m_SL_N.InsertAfter(pos,m_strRightOfCaret);
		m_strLeftOfCaret="";
		m_idxN_Y++;
		m_strN=" 03";
		xddbg=1;
		break;
	case VK_SPACE:
		m_strLeftOfCaret+=m_strN;
		m_strN=" 03";
		m_strLineOfNt=m_strLeftOfCaret+m_strRightOfCaret;
		pDoc->m_SL_N.SetAt(pos,m_strLineOfNt);
		break;
	case 'i':
	case 'I':
		cTone++;
		if((c!='W'&&c!='w')&&cTone>'5') cTone='5';
		
		m_strN.SetAt(2,cTone);
		break;
	case 'm':
	case 'M':
		cTone--;
		if((c!='W'&&c!='w')&&cTone<'1') cTone='1';
		m_strN.SetAt(2,cTone);
		break;
	case 'l':
	case 'L':
		cTime++;		
		if(cTime>'3') cTime='0';
		m_strN.SetAt(1,cTime);
		break;
	case '{':
		if(cTone<='5'&&cTone>='1'){
			cTone+=5;
		}
		else{
			cTone-=5;
		}
		m_strN.SetAt(2,cTone);
		break;

	case 'D':
	case 'd':
	case 'o':
	case 'O':
	case 's':
	case 'S':
	case 'X':
	case 'x':
	case '/':
	case '\\':
	case 'w':
	case 'W':
	case 'f':
	case 't':
	case 'T':
	case '(':
	case ')':
	case '[':
	case ']':
	case ':':
	case '#':
	case '=':
	case 'b':
	case '-':
	case '.':
	case '|':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '0':
		
		m_strN.SetAt(0,nChar);
		
		break;
	default:
		break;
	}	
}

void CLSView::Xd_Nt_Draw_List(CDC *pDC)
{
	CLSDoc *pDoc=GetDocument();

	pDC->SetBkMode(TRANSPARENT);
	COLORREF clrOld=pDC->SetTextColor(m_clrText); //设置字体颜色
	CFont *oldFont=pDC->SelectObject(pFont);//选择新字体

	int x=0;
	int y=0;
	CSize sz;
	POSITION pos;
	
	pos=pDoc->m_SL_N.GetHeadPosition();
	int count=0;
	int x1=m_idxN_SX1 ,y1=m_idxN_SY1,x2=m_idxN_SX2,y2=m_idxN_SY2;
	if(y1>y2){		
		y1=m_idxN_SY2;
		y2=m_idxN_SY1;
		x1=m_idxN_SX2;
		x2=m_idxN_SX1;
	}
	if(y1==y2&&x1>x2){
		x1=m_idxN_SX2;
		x2=m_idxN_SX1;
	}
	int idxX=0;
	int idxY=1;
	sz=pDC->GetTextExtent('M');
	
	
	while (pos) {
		
		CString str=pDoc->m_SL_N.GetNext(pos);
		if(count==m_idxN_Y&&(m_strN.GetAt(0)!=' '||m_strN.GetAt(1)=='1'||m_strN.GetAt(1)=='2'||
			m_strN.GetAt(2)=='1'||
			m_strN.GetAt(2)=='2'||
			m_strN.GetAt(2)=='4'||
			m_strN.GetAt(2)=='5')
			)
		{
			str=m_strLeftOfCaret+m_strN+m_strRightOfCaret;
		}
		int l=str.GetLength();
		idxX=1;
		while (str.GetLength())
		{
			CString s=str.Left(3);
			str=str.Right(str.GetLength()-3);
			
			if(idxY>y1&&idxY<y2||y1!=y2&&idxY==y1&&idxX>=x1
				||y1!=y2&&idxY==y2&&idxX<x2
				||x1!=x2&&y1==y2&&idxY==y2&&idxX<x2&&idxX>=x1
				)
			{
				COLORREF clr=pDC->SetTextColor(RGB(0,0,255));
				pDC->Rectangle(x,y,x+sz.cx,y+sz.cy);
				Xd_Nt_Draw_One(pDC,x,y,s);
				pDC->SetTextColor(clr);				
			}
		
			else
				Xd_Nt_Draw_One(pDC,x,y,s);
			x+=sz.cx;
			idxX++;
		}
		y+=sz.cy*2;
		x=0;

		count++;
		idxY++;
	}		

	pDC->SetTextColor(clrOld);//恢复原来DC所用的字体颜色
	COLORREF clrRed=RGB(255,0,0);
	clrOld=pDC->SetTextColor(clrRed);
	sz=pDC->GetTextExtent(m_strN);	
	
	CPen pRed(PS_SOLID,1,RGB(255,0,0));
	CPen* pOP=pDC->SelectObject(&pRed);
	char c=m_strN.GetAt(0);
	y=m_idxN_Y*sz.cy*2;
	x=sz.cx*m_strLeftOfCaret.GetLength()/3/3;
	
	if(m_Type==XD_TYPE_NOTE)	
	{
		Xd_Nt_SetCaret(x,y);
		TRACE("[%d,%d]",x,y);
	}

	Xd_Nt_Draw_One(pDC,x,y,m_strN);
	
	pDC->SelectObject(pOP);
	pDC->SetTextColor(clrOld);
	pDC->SelectObject(oldFont);	//恢复原来DC所用的字体	

}

void CLSView::Xd_Nt_MakeCaret(int x, int y)
{
	CFont* pOF;
	CDC* pDC=GetDC();

	pOF=pDC->SelectObject(pFont);
	pDC->SetTextColor(m_clrText);
	TEXTMETRIC tm;
	pDC->GetTextMetrics(&tm);
	int nLineHeight = tm.tmHeight;
	
	int xc=x*tm.tmAveCharWidth;
	int yc=y*nLineHeight*2;

	CreateSolidCaret(1,nLineHeight);
	Xd_Nt_SetCaret(xc,yc);
	ShowCaret();
	
	pDC->SelectObject(pOF);
	ReleaseDC(pDC);
}

void CLSView::Xd_Nt_SetCaret(int x, int y)
{
	CPoint p=GetScrollPosition();
	CPoint point=CPoint(x-p.x,y-p.y);

	SetCaretPos(point);
//*
	char PositionString[50];
	CMainFrame* pMFrm=(CMainFrame*) AfxGetMainWnd();
	sprintf(PositionString,"CX: %d",point.x);
	pMFrm->m_wndStatusBar.SetPaneText(3,PositionString);
	sprintf(PositionString,"CY: %d",point.y);
	pMFrm->m_wndStatusBar.SetPaneText(4,PositionString);
//*/

}

void CLSView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	CLSDoc*pDoc=GetDocument();
	switch(m_Type) {
	case XD_TYPE_NOTE:
		XD_Nt_KeyDown(nChar);
		Xd_Update_Scrl_Size();
		break;
	case XD_TYPE_LYRICS:
		XD_Lyr_KeyDown(nChar);
		break;
	default:
		break;
	}
	Invalidate();
	CScrollView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CLSView::XD_Nt_KeyDown(UINT nChar)
{
	CLSDoc*pDoc=GetDocument();

	POSITION pos;
	switch(nChar) {
	case VK_LEFT:
		if(m_strLeftOfCaret.GetLength()>0){
			m_strRightOfCaret=m_strLeftOfCaret.Right(3)+m_strRightOfCaret;
			m_strLeftOfCaret=m_strLeftOfCaret.Left(m_strLeftOfCaret.GetLength()-3);
			m_strLineOfNt=m_strLeftOfCaret+m_strRightOfCaret;
			}
		else if(m_idxN_Y>0){
			m_idxN_Y--;
			pos = pDoc->m_SL_N.FindIndex(m_idxN_Y);
			if(pos)	{
				m_strLeftOfCaret=pDoc->m_SL_N.GetAt(pos);
				m_strRightOfCaret="";
				m_strLineOfNt=m_strLeftOfCaret+m_strRightOfCaret;
			}
		}
		break;
	case VK_RIGHT:
		if(m_strRightOfCaret.GetLength()>0){
			m_strLeftOfCaret=m_strLeftOfCaret+m_strRightOfCaret.Left(3);
			m_strRightOfCaret=m_strRightOfCaret.Right(m_strRightOfCaret.GetLength()-3);			
			m_strLineOfNt=m_strLeftOfCaret+m_strRightOfCaret;
		}
		else if(m_idxN_Y<pDoc->m_SL_N.GetCount()-1){
			m_idxN_Y++;
			pos = pDoc->m_SL_N.FindIndex(m_idxN_Y);
			if(pos)	{
				m_strRightOfCaret=pDoc->m_SL_N.GetAt(pos);
				m_strLeftOfCaret="";
				m_strLineOfNt=m_strLeftOfCaret+m_strRightOfCaret;
			}
		}
		break;
	case VK_UP:
		if(m_idxN_Y>0){
			m_idxN_Y--;
			pos = pDoc->m_SL_N.FindIndex(m_idxN_Y);
			if(pos)	{
				m_strLineOfNt=pDoc->m_SL_N.GetAt(pos);
				if(m_strLeftOfCaret.GetLength()<=m_strLineOfNt.GetLength()){
					m_strLeftOfCaret=m_strLineOfNt.Left(m_strLeftOfCaret.GetLength());
					m_strRightOfCaret=m_strLineOfNt.Right(m_strLineOfNt.GetLength()-m_strLeftOfCaret.GetLength());
				}
				else{
					m_strLeftOfCaret=m_strLineOfNt;
					m_strRightOfCaret="";
				}
			}
		}
		break;
	case VK_DOWN:
		if(m_idxN_Y<pDoc->m_SL_N.GetCount()-1){
			m_idxN_Y++;
			pos=pDoc->m_SL_N.FindIndex(m_idxN_Y);
			if(pos){
				m_strLineOfNt=pDoc->m_SL_N.GetAt(pos);
				if(m_strLeftOfCaret.GetLength()<=m_strLineOfNt.GetLength()){
					m_strLeftOfCaret=m_strLineOfNt.Left(m_strLeftOfCaret.GetLength());
					m_strRightOfCaret=m_strLineOfNt.Right(m_strLineOfNt.GetLength()-m_strLeftOfCaret.GetLength());
				}
				else{
					m_strLeftOfCaret=m_strLineOfNt;
					m_strRightOfCaret="";
				}
			}
		}
		break;
	case VK_HOME:
		m_strLeftOfCaret="";
		m_strRightOfCaret=m_strLineOfNt;
		break;
	case VK_END:
		m_strLeftOfCaret=m_strLineOfNt;
		m_strRightOfCaret="";
		break;
	case VK_DELETE:
		if(m_strN.GetAt(0)!=' '||(m_strN.GetAt(0)==' '&&
			(m_strN.GetAt(1)=='1'||m_strN.GetAt(1)=='2'||
			m_strN.GetAt(2)=='1'||
			m_strN.GetAt(2)=='2'||
			m_strN.GetAt(2)=='4'||
			m_strN.GetAt(2)=='5'))){
			m_strN=" 03";
			break;
		}
		if(m_strRightOfCaret.GetLength()>0){			
			m_strRightOfCaret=m_strRightOfCaret.Right(m_strRightOfCaret.GetLength()-3);
			m_strLineOfNt=m_strLeftOfCaret+m_strRightOfCaret;
			pos=pDoc->m_SL_N.FindIndex(m_idxN_Y);
			pDoc->m_SL_N.SetAt(pos,m_strLineOfNt);
		}
		else if(m_idxN_Y<pDoc->m_SL_N.GetCount()-1){
			pos=pDoc->m_SL_N.FindIndex(m_idxN_Y+1);
			m_strRightOfCaret=pDoc->m_SL_N.GetAt(pos);
			m_strLineOfNt=m_strLeftOfCaret+m_strRightOfCaret;
			pos=pDoc->m_SL_N.FindIndex(m_idxN_Y);
			pDoc->m_SL_N.SetAt(pos,m_strLineOfNt);
			pos=pDoc->m_SL_N.FindIndex(m_idxN_Y+1);
			pDoc->m_SL_N.RemoveAt(pos);
		}
		break;
	default:
		break;
	}
}

void CLSView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CStringList   strL;
	POSITION p = strL.FindIndex(0);

	TRACE("0: p=0x%d",p);
	p = strL.FindIndex(1);
	TRACE("1: p=0x%d",p);

	strL.AddTail("1111");
	p = strL.FindIndex(0);
	TRACE("i0: p=0x%d",p);
	p = strL.FindIndex(1);
	TRACE("i1: p=0x%d",p);

	switch(m_Type) {
	case XD_TYPE_NOTE:
		Xd_Nt_LBtnDown(point);
		break;
	case XD_TYPE_LYRICS:
		Xd_Lyr_LBtnDown(point);
		break;
	default:
		break;
	}
	CScrollView::OnLButtonDown(nFlags, point);
}

void CLSView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	switch(m_Type) {
	case XD_TYPE_NOTE:
		Xd_Nt_MouseMove(point);
		break;
	case XD_TYPE_LYRICS:
		Xd_Lyr_MouseMove(point);
		break;
	default:
		break;
	}

	CScrollView::OnMouseMove(nFlags, point);
}

BOOL CLSView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	// TODO: Add your message handler code here and/or call default
//	SetCursor (LoadCursor(NULL,IDC_IBEAM));
//	return CScrollView::OnSetCursor(pWnd, nHitTest, message);
	return 1;
}

void CLSView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	switch(m_Type) {
	case XD_TYPE_NOTE:
		Xd_Nt_LBtnUp(point);
		break;
	case XD_TYPE_LYRICS:
		Xd_Lyr_LBtnUp(point);
		break;
	default:
		break;
	}
	CScrollView::OnLButtonUp(nFlags, point);
}

void CLSView::OnEditCopy() 
{
	// TODO: Add your command handler code here	

	switch(m_Type) {
	case XD_TYPE_NOTE:
		Xd_Get_Sel_Nt(m_SL_N_CPY);
	case XD_TYPE_LYRICS:
		Xd_Lyr_EditCOPY();
		break;
	default:
		break;
	}
	
}

void CLSView::OnUpdateEditCopy(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CLSView::Xd_Get_Sel_Nt(CStringList &strList)
{
	CLSDoc*pDoc=GetDocument();
	strList.RemoveAll();
	int x1=m_idxN_SX1,y1=m_idxN_SY1,x2=m_idxN_SX2,y2=m_idxN_SY2;
	if(y1!=y2){	
		if(y1>y2){
			y1=m_idxN_SY2;
			y2=m_idxN_SY1;
			x1=m_idxN_SX2;
			x2=m_idxN_SX1;
		}
		POSITION pos=pDoc->m_SL_N.FindIndex(y1-1);
		CString s=pDoc->m_SL_N.GetAt(pos);
		s=s.Right(s.GetLength()-(x1-1)*3);
		strList.AddTail(s);
		for(int i=y1+1;i<y2;i++){
			pos=pDoc->m_SL_N.FindIndex(i-1);
			s=pDoc->m_SL_N.GetAt(pos);
			strList.AddTail(s);
		}
		pos=pDoc->m_SL_N.FindIndex(y2-1);
		s=pDoc->m_SL_N.GetAt(pos);
		s=s.Left((x2-1)*3);
		strList.AddTail(s);
	}
	if(y1==y2){
		if(x1>x2){
			x1=m_idxN_SX2;
			x2=m_idxN_SX1;
		}
		POSITION pos=pDoc->m_SL_N.FindIndex(y1-1);
		CString s=pDoc->m_SL_N.GetAt(pos);
		s=s.Left((x2-1)*3);
		s=s.Right(s.GetLength()-(x1-1)*3);
		strList.AddTail(s);
	}
}

void CLSView::OnEditPaste() 
{
	// TODO: Add your command handler code here
	
	switch(m_Type) {
	case XD_TYPE_NOTE:
		Xd_Nt_EditPast();
	case XD_TYPE_LYRICS:
		Xd_Lyr_EditPast();
		break;
	default:
		break;
	}
}

void CLSView::OnUpdateEditPaste(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CLSView::Xd_Insert_StrNt(CString str)
{
	CLSDoc*pDoc=GetDocument();
	POSITION pos = pDoc->m_SL_N.FindIndex(m_idxN_Y);

	m_strLeftOfCaret+=str;
	m_strLineOfNt=m_strLeftOfCaret+m_strRightOfCaret;
	pDoc->m_SL_N.SetAt(pos,m_strLineOfNt);

}

void CLSView::Xd_Insert_Nt_Return()
{
	CLSDoc*pDoc=GetDocument();
	POSITION pos = pDoc->m_SL_N.FindIndex(m_idxN_Y);
	pDoc->m_SL_N.SetAt(pos,m_strLeftOfCaret);
	pDoc->m_SL_N.InsertAfter(pos,m_strRightOfCaret);
	m_strLeftOfCaret="";
	m_idxN_Y++;
	m_strN=" 03";
}

void CLSView::Xd_Update_Scrl_Size()
{
	CLSDoc*pDoc=GetDocument();

	CFont* pOF;
	CDC* pDC=GetDC();
	pOF=pDC->SelectObject(pFont);
	TEXTMETRIC tm;
	pDC->GetTextMetrics(&tm);
	int nLineHeight=tm.tmHeight*2;
	CSize size;
	POSITION pos=pDoc->m_SL_N.GetHeadPosition();
	while (pos) {
		CString str=pDoc->m_SL_N.GetNext(pos);
		size=pDC->GetTextExtent(str,str.GetLength());
		if(size.cx/3>m_ScrlSize.cx-tm.tmMaxCharWidth*2){
			m_ScrlSize.cx=size.cx/3+tm.tmMaxCharWidth*2;			
		}
		int tempY=nLineHeight*pDoc->m_SL_N.GetCount();
		if(tempY>m_ScrlSize.cy){
			m_ScrlSize.cy=tempY+nLineHeight;			
		}	
	}
	SetScrollSizes(MM_TEXT, m_ScrlSize);	
	pDC->SelectObject(pOF);
	ReleaseDC(pDC);
}

void CLSView::OnXdLyrics() 
{
	// TODO: Add your command handler code here
	m_Type=XD_TYPE_LYRICS;
	Xd_Lyr_MakeCaret(0,0);
	Invalidate();
}

void CLSView::OnUpdateXdLyrics(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_Type==XD_TYPE_LYRICS);
}

void CLSView::OnXdNote() 
{
	// TODO: Add your command handler code here
	m_Type=XD_TYPE_NOTE;
	
	Xd_Nt_MakeCaret(0,0);
	Invalidate();
}

void CLSView::OnUpdateXdNote(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_Type==XD_TYPE_NOTE);
}

void CLSView::Xd_Nt_LBtnDown(CPoint point)
{
	CLSDoc*pDoc=GetDocument();
	CPoint p=GetScrollPosition();
	point.x+=p.x;point.y+=p.y;

	CDC* pDC=GetDC();
	CFont *oldFont=pDC->SelectObject(pFont);//选择新字体
	CSize sz;
	sz=pDC->GetTextExtent("M");

	//确定行位置
	int ny=((point.y-10)/sz.cy/2);
	int count=pDoc->m_SL_N.GetCount()-1;
	if(ny>count) ny=count;
//* 
	POSITION pos = pDoc->m_SL_N.FindIndex(ny);
	if(pos){
		m_strLineOfNt=pDoc->m_SL_N.GetAt(pos);
		m_idxN_Y=ny;
	}

//*/
	
	//确定列位置
	int nx=(point.x-10)/sz.cx;
	m_idxN_X=nx;
	m_strLeftOfCaret=m_strLineOfNt.Left(m_idxN_X*3);
	m_strRightOfCaret=m_strLineOfNt.Right(m_strLineOfNt.GetLength()-m_strLeftOfCaret.GetLength());

	m_idxN_SX1=	m_idxN_SX2=nx+1;
	m_idxN_SY1= m_idxN_SY2=ny+1;
	
	Invalidate();
	m_bNtLBntDown=TRUE;

	pDC->SelectObject(oldFont);
	ReleaseDC(pDC);
}

void CLSView::Xd_Lyr_MouseMove(CPoint point)
{
	CLSDoc *pDoc=GetDocument();
	CPoint p=GetScrollPosition();
	point.x+=p.x;point.y+=p.y;
	
	char PositionString[50];
	CMainFrame* pMFrm=(CMainFrame*) AfxGetMainWnd();
	sprintf(PositionString,"X: %d",point.x);
	pMFrm->m_wndStatusBar.SetPaneText(1,PositionString);
	sprintf(PositionString,"Y: %d",point.y);
	pMFrm->m_wndStatusBar.SetPaneText(2,PositionString);	
	
	if(m_bLyrLBntDown){
		
		BOOL b=FALSE;
		CSize size;
		
		CFont* pOF;
		CDC* pDC=GetDC();
		pOF=pDC->SelectObject(pFont);
		pDC->SetTextColor(m_clrText);
		TEXTMETRIC tm;
		pDC->GetTextMetrics(&tm);
		int nLineHeight = tm.tmHeight ;
		
		//	pDC->SelectObject(pOF);
		
		//确定行位置
		int temp=(point.y/nLineHeight);
		if(temp>pDoc->m_SL_L.GetCount()-1) temp=pDoc->m_SL_L.GetCount()-1;
		POSITION pos = pDoc->m_SL_L.FindIndex(temp);
		if(pos){
			m_L_StrLine=pDoc->m_SL_L.GetAt(pos);
			m_LidxY=temp;
		}
		else{
			return;
		}
		
		//确定列位置
		m_L_LC_Str="";
		int n=m_L_StrLine.GetLength()+1;
		char *ps=new char[n];
		
		for(;m_L_LC_Str.GetLength()<m_L_StrLine.GetLength();){
			//前进一个字符,，...
			strcpy(ps,m_L_StrLine.GetBuffer(m_L_StrLine.GetLength()));
			
			char* pLastChar;
			pLastChar= &ps[m_L_LC_Str.GetLength()];
			
			// Now move it forward one double-byte character.
			pLastChar = CharNext (pLastChar );
			pLastChar[0]='\0';			
			m_L_LC_Str.Format("%s",ps);

			//前进一个字符;
			
			size=pDC->GetTextExtent(m_L_LC_Str,m_L_LC_Str.GetLength());
			if(point.x<size.cx){
				// Now move it back one double-byte character.
				pLastChar = CharPrev ( ps, pLastChar );
				pLastChar[0]='\0';			
				m_L_LC_Str.Format("%s",ps);
				b=TRUE;
				break;
			}
		}
		
		delete ps;
		
		if(!b){
			m_L_LC_Str=m_L_StrLine;
		}
		size=pDC->GetTextExtent (m_L_LC_Str,m_L_LC_Str.GetLength());
		
		pDC->SelectObject(pOF);
		ReleaseDC(pDC);

		m_xSel2=size.cx;
		m_ySel2=m_LidxY;
	
		m_bLSel=TRUE;
		Invalidate();
	}

}
void CLSView::Xd_Nt_MouseMove(CPoint point)
{
	CLSDoc*pDoc=GetDocument();
	CPoint p=GetScrollPosition();
	point.x+=p.x;point.y+=p.y;
	
	char PositionString[50];
	CMainFrame* pMFrm=(CMainFrame*) AfxGetMainWnd();
	sprintf(PositionString,"X: %d",point.x);
	pMFrm->m_wndStatusBar.SetPaneText(1,PositionString);
	sprintf(PositionString,"Y: %d",point.y);
	pMFrm->m_wndStatusBar.SetPaneText(2,PositionString);	
	
	if(m_bNtLBntDown){
		CDC* pDC=GetDC();
		CFont *oldFont=pDC->SelectObject(pFont);//选择新字体
		CSize sz;
		sz=pDC->GetTextExtent("M");

		//确定行位置
		int ny=((point.y-10)/sz.cy/2);
		int count=pDoc->m_SL_N.GetCount()-1;
		if(ny>count) ny=count;
		//* 
		POSITION pos = pDoc->m_SL_N.FindIndex(ny);
		if(pos){
			m_strLineOfNt=pDoc->m_SL_N.GetAt(pos);
			m_idxN_Y=ny;
		}		
		
		//确定列位置
		int nx=(point.x-10)/sz.cx;
		m_idxN_X=nx;
		m_strLeftOfCaret=m_strLineOfNt.Left(m_idxN_X*3);
		m_strRightOfCaret=m_strLineOfNt.Right(m_strLineOfNt.GetLength()-m_strLeftOfCaret.GetLength());
		
		m_idxN_SX2=nx+1;
		m_idxN_SY2=ny+1;
			
		pDC->SelectObject(oldFont);
		ReleaseDC(pDC);
		Invalidate();
	}
}

void CLSView::Xd_Nt_LBtnUp (CPoint point)
{
	CPoint p=GetScrollPosition();
	point.x+=p.x;point.y+=p.y;
	m_bNtLBntDown=FALSE;
}

void CLSView::Xd_Lyr_Char(UINT nChar)
{
	CLSDoc *pDoc=GetDocument();	
	CFont* pOF;
	CDC* pDC=GetDC();
	pOF=pDC->SelectObject(pFont);
	pDC->SetTextColor(m_clrText);
	TEXTMETRIC tm;
	pDC->GetTextMetrics(&tm);
	int nLineHeight = tm.tmHeight;

	POSITION pos = pDoc->m_SL_L.FindIndex(m_LidxY);
	if(pos)	m_L_StrLine=pDoc->m_SL_L.GetAt(pos);
	
	switch(nChar) {
	case VK_RETURN:
		m_LidxY++;
		
		m_L_StrLine=m_L_StrLine.Right(m_L_StrLine.GetLength()-m_L_LC_Str.GetLength());
		
		pDoc->m_SL_L.InsertAfter(pos,m_L_StrLine);
		pDoc->m_SL_L.SetAt(pos,m_L_LC_Str);	
		m_L_LC_Str="";
			
		break;
	case VK_BACK:
		if(m_L_LC_Str.GetLength()==0){
			if(m_LidxY>0){
				pDoc->m_SL_L.RemoveAt(pos);
				m_LidxY--;
				pos = pDoc->m_SL_L.FindIndex(m_LidxY);
				if(pos) m_L_LC_Str=pDoc->m_SL_L.GetAt(pos);
				m_L_StrLine=m_L_LC_Str+m_L_StrLine;
				pDoc->m_SL_L.SetAt(pos,m_L_StrLine);
				break;
			}
		}
		if(m_L_LC_Str.GetLength()<m_L_StrLine.GetLength()){
			m_L_StrLine=m_L_StrLine.Right(m_L_StrLine.GetLength()-m_L_LC_Str.GetLength());
			//回退一个字符...
			int n=m_L_LC_Str.GetLength()+1;
			char *ps=new char[n];
			
			strcpy(ps,m_L_LC_Str.GetBuffer(m_L_LC_Str.GetLength()));
			
			char* pLastChar;
			pLastChar= &ps[m_L_LC_Str.GetLength()];
			
			// Now move it back one double-byte character.
			pLastChar = CharPrev ( ps, pLastChar );
			pLastChar[0]='\0';			
			m_L_LC_Str.Format("%s",ps);
			delete ps;
			//回退一个字符;
			m_L_StrLine=m_L_LC_Str+m_L_StrLine;
		}
		else if(m_L_StrLine.GetLength()>0){
			//回退一个字符...
			int n=m_L_StrLine.GetLength()+1;
			char *ps=new char[n];
			
			strcpy(ps,m_L_StrLine.GetBuffer(m_L_StrLine.GetLength()));
			
			char* pLastChar;
			pLastChar= &ps[m_L_StrLine.GetLength()];
			
			// Now move it back one double-byte character.
			pLastChar = CharPrev ( ps, pLastChar );
			pLastChar[0]='\0';			
			m_L_StrLine.Format("%s",ps);
			delete ps;
			//回退一个字符;
			m_L_LC_Str=m_L_StrLine;
		}
		else{
			if(m_LidxY>0){
				pDoc->m_SL_L.RemoveAt(pos);
				m_LidxY--;
				pos = pDoc->m_SL_L.FindIndex(m_LidxY);
				m_L_LC_Str=m_L_StrLine=pDoc->m_SL_L.GetAt(pos);
				break;
			}
		}
		pDoc->m_SL_L.SetAt(pos,m_L_StrLine);	
		break;
	default:
		if(m_L_LC_Str.GetLength()<m_L_StrLine.GetLength()){
			m_L_StrLine=m_L_StrLine.Right(m_L_StrLine.GetLength()-m_L_LC_Str.GetLength());
			CString s;
			s.Format("%c",nChar);
			m_L_LC_Str += s;
			m_L_StrLine=m_L_LC_Str+m_L_StrLine;
		}
		else{CString s;
			s.Format("%c",nChar);
			m_L_StrLine+=s;
			m_L_LC_Str=m_L_StrLine;
		}
		pDoc->m_SL_L.SetAt(pos,m_L_StrLine);	
		

		break;
	}
	
	CSize size;
	
	size=pDC->GetTextExtent (m_L_LC_Str,m_L_LC_Str.GetLength ());
	
	Xd_Lyr_SetCaret(size.cx,m_LidxY*nLineHeight);
	
	pDC->SelectObject(pOF);
	ReleaseDC(pDC);
	Xd_Update_Scrl_Size();

}

void CLSView::Xd_Lyr_Draw(CDC *pDC)
{
	CLSDoc *pDoc=GetDocument();
	// TODO: add draw code for native data here

	CFont* pOF;
	pOF=pDC->SelectObject(pFont);
	pDC->SetTextColor(m_clrText);

//	pDC->Rectangle(0,0,m_ScrlSize.cx,m_ScrlSize.cy);

	int x=0,y=0;
	TEXTMETRIC tm;
	pDC->GetTextMetrics(&tm);
	int nLineHeight = tm.tmHeight;
   
	int curY=0;

	BOOL bSel=FALSE;
	m_SL_LSel.RemoveAll();
	POSITION pos=pDoc->m_SL_L.GetHeadPosition();
	while (pos) {
		CString str=m_SL_LSel.GetNext(pos);
		CString s1,s2;
		if(m_ySel1==curY&&m_bLSel){
			s1=Xd_GetStrByX(str,m_xSel1);			
		}
		if(m_ySel2==curY&&m_bLSel){
			s2=Xd_GetStrByX(str,m_xSel2);			
		}
		pDC->TextOut(x,y,str);
		
		//sel....
		pDC->SetTextColor(RGB(255,0,255));
		COLORREF co=pDC->SetBkColor(RGB(0,255,0));
		
		//  case1
		if(m_ySel1<m_ySel2&&m_bLSel){
			if(curY>m_ySel1&&curY<m_ySel2){
				pDC->TextOut(x,y,str);
				m_SL_LSel.AddTail(str);		
			}
			if(m_ySel1==curY)
			{			
				s1=str.Right(str.GetLength()-s1.GetLength());
				pDC->TextOut(m_xSel1,m_ySel1*nLineHeight,s1);
				m_SL_LSel.AddTail(s1);
			}
			if(m_ySel2==curY)
			{							
				pDC->TextOut(0,m_ySel2*nLineHeight,s2);
				m_SL_LSel.AddTail(s2);			
			}
		}
		//  case2
		if(m_ySel1>m_ySel2&&m_bLSel){
			if(curY>m_ySel2&&curY<m_ySel1){
				pDC->TextOut(x,y,str);			
				m_SL_LSel.AddTail(str);
			}
			if(m_ySel1==curY)
			{			
				pDC->TextOut(0,m_ySel1*nLineHeight,s1);				
				m_SL_LSel.AddTail(s1);
			}
			if(m_ySel2==curY)
			{						
				s2=str.Right(str.GetLength()-s2.GetLength());	
				pDC->TextOut(m_xSel2,m_ySel2*nLineHeight,s2);				
				m_SL_LSel.AddTail(s2);
			}
		}
		//  case3
		if(m_ySel2==curY&&m_ySel1==m_ySel2&&m_bLSel)
		{				
			if(m_xSel1<m_xSel2){	
				s2=s2.Right(s2.GetLength()-s1.GetLength());
				pDC->TextOut(m_xSel1,m_LidxY*nLineHeight,s2);
				m_SL_LSel.AddTail(s2);
			}
			else{
				s1=s1.Right(s1.GetLength()-s2.GetLength());
				pDC->TextOut(m_xSel2,m_LidxY*nLineHeight,s1);
				m_SL_LSel.AddTail(s1);
			}			
		}
		
		pDC->SetTextColor(m_clrText);
		pDC->SetBkColor(co);	
		//sel;
		
		y+=nLineHeight;
		curY++;
	}
	CSize sz=pDC->GetTextExtent(m_L_LC_Str);
	
	x=sz.cx;
	y=nLineHeight*m_LidxY;
	if(m_Type==XD_TYPE_LYRICS)	Xd_Lyr_SetCaret(x,y);

	pDC->SelectObject(pOF);
}

CString CLSView::Xd_GetStrByX(CString str, int x)
{	
	CString strReturn="";
	BOOL b=FALSE;
	int n=str.GetLength()+1;
	char *ps=new char[n];
	CDC* pDC=GetDC();
	CFont* pOF;
	
	pOF=pDC->SelectObject(pFont);
	pDC->SetTextColor(m_clrText);	
	
	for(;strReturn.GetLength()<str.GetLength();){
		//前进一个字符,，...
		strcpy(ps,str.GetBuffer(str.GetLength()));
		
		char* pLastChar;
		pLastChar= &ps[strReturn.GetLength()];
		
		// Now move it forward one double-byte character.
		pLastChar = CharNext (pLastChar );
		pLastChar[0]='\0';			
		strReturn.Format("%s",ps);
		//前进一个字符;
		
		CSize	size=pDC->GetTextExtent(strReturn,strReturn.GetLength());
		if(x<size.cx){
			// Now move it back one double-byte character.
			pLastChar = CharPrev ( ps, pLastChar );
			pLastChar[0]='\0';			
			strReturn.Format("%s",ps);
			b=TRUE;
			break;
		}
	}
		
	delete ps;

	if(!b){
		strReturn=str;
	}
	pDC->SelectObject(pOF);
	ReleaseDC(pDC);
	return strReturn;
}

void CLSView::XD_Lyr_KeyDown(UINT nChar)
{
	CLSDoc *pDoc=GetDocument();
	CPoint pS;
	CRect r;
	CFont* pOF;
	CDC* pDC=GetDC();
	pOF=pDC->SelectObject(pFont);
	pDC->SetTextColor(m_clrText);
	TEXTMETRIC tm;
	pDC->GetTextMetrics(&tm);
	int nLineHeight = tm.tmHeight + tm.tmExternalLeading;

//	pDC->SelectObject(pOF);

	CSize size;
	POSITION pos;
	
	
	switch(nChar) {
	case VK_LEFT:
		if(m_L_LC_Str.GetLength()==0){	
			pos=pDoc->m_SL_L.FindIndex(m_LidxY-1);
			if(pos){	
				OnKeyDown(VK_UP,1,328);//VK_UP
				OnKeyDown(VK_END,1,335);//VK_END
				break;//*注意不能漏这一句
			}
		}
		if(m_L_LC_Str.GetLength()>0){
			//回退一个字符,，...
			int n=m_L_LC_Str.GetLength()+1;
			char *ps=new char[n];
			
			strcpy(ps,m_L_LC_Str.GetBuffer(m_L_LC_Str.GetLength()));
			
			char* pLastChar;
			pLastChar= &ps[m_L_LC_Str.GetLength()];
			
			// Now move it back one double-byte character.
			pLastChar = CharPrev ( ps, pLastChar );
			pLastChar[0]='\0';			
			m_L_LC_Str.Format("%s",ps);

			delete ps;
			//回退一个字符;
		}
		break;
	case VK_RIGHT:
		if(m_L_LC_Str.GetLength()==m_L_StrLine.GetLength()){
			pos=pDoc->m_SL_L.FindIndex(m_LidxY+1);
			if(pos){
				OnKeyDown(VK_DOWN,1,336);//VK_DOWN
				OnKeyDown(VK_HOME,1,327);//VK_HOME
				break;//*注意不能漏这一句
			}
		}
		if(m_L_LC_Str.GetLength()<m_L_StrLine.GetLength()){
			//前进一个字符,，...
			int n=m_L_StrLine.GetLength()+1;
			char *ps=new char[n];
			
			strcpy(ps,m_L_StrLine.GetBuffer(m_L_StrLine.GetLength()));
			
			char* pLastChar;
			pLastChar= &ps[m_L_LC_Str.GetLength()];
			
			// Now move it forward one double-byte character.
			pLastChar = CharNext (pLastChar );
			pLastChar[0]='\0';			
			m_L_LC_Str.Format("%s",ps);

			delete ps;
			//前进一个字符;
		}
		break;
	case VK_HOME:
		m_L_LC_Str="";
		pS=this->GetScrollPosition();
		this->ScrollToPosition(CPoint(0,pS.y));
		break;
	case VK_END:
		m_L_LC_Str=m_L_StrLine;
		
		break;
	case VK_DELETE:
		if(m_bLSel){
			Xd_Lyr_EditDel();
			break;
		}
		if(m_L_LC_Str.GetLength()<m_L_StrLine.GetLength()){
			OnKeyDown(VK_RIGHT,1,333);//VK_RIGHT
			OnChar(8,1,14);
		}
		else {
			pos=pDoc->m_SL_L.FindIndex(m_LidxY+1);
			if(pos){
				OnKeyDown(VK_DOWN,1,336);//VK_DOWN
				OnKeyDown(VK_HOME,1,327);//VK_HOME
				OnChar(8,1,14);//VK_BACK
			}
		}
		break;
	case VK_UP:
		pos = pDoc->m_SL_L.FindIndex(m_LidxY-1);
		if(pos) {
			m_LidxY--;
			m_L_StrLine=pDoc->m_SL_L.GetAt(pos);
			m_L_LC_Str=m_L_StrLine.Left(m_L_LC_Str.GetLength());
		}
		break;
	case VK_DOWN:
		pos=pDoc->m_SL_L.FindIndex(m_LidxY+1);
		if(pos){
			m_LidxY++;
			m_L_StrLine=pDoc->m_SL_L.GetAt(pos);
			m_L_LC_Str=m_L_StrLine.Left(m_L_LC_Str.GetLength());
		}
		break;
	default:
		break;
	}
	size=pDC->GetTextExtent (m_L_LC_Str,m_L_LC_Str.GetLength ());

//	Xd_SetCaret(size.cx,m_LidxY*nLineHeight);
	pDC->SelectObject(pOF);
	ReleaseDC(pDC);
	Xd_Update_Scrl_Size();
	Invalidate();

}

void CLSView::Xd_Lyr_MakeCaret(int x, int y)
{
	CLSDoc *pDoc=GetDocument();
	CFont* pOF;
	CDC* pDC=GetDC();
	pOF=pDC->SelectObject(pFont);
	pDC->SetTextColor(m_clrText);
	TEXTMETRIC tm;
	pDC->GetTextMetrics(&tm);
	int nLineHeight = tm.tmHeight;


	CreateSolidCaret(1,nLineHeight);
	//SetCaretPos(CPoint(x,y));
	Xd_Lyr_SetCaret(x,y);
	ShowCaret();
	
	pDC->SelectObject(pOF);
	ReleaseDC(pDC);
}

void CLSView::Xd_Lyr_SetCaret(int x, int y)
{
	CLSDoc *pDoc=GetDocument();
	CPoint p=GetScrollPosition();
	CPoint point=CPoint(x-p.x,y-p.y);

	SetCaretPos(point);

	char PositionString[50];
	CMainFrame* pMFrm=(CMainFrame*) AfxGetMainWnd();
	sprintf(PositionString,"CX: %d",point.x);
	pMFrm->m_wndStatusBar.SetPaneText(3,PositionString);
	sprintf(PositionString,"CY: %d",point.y);
	pMFrm->m_wndStatusBar.SetPaneText(4,PositionString);

}

void CLSView::Xd_Lyr_LBtnDown(CPoint point)
{
	CLSDoc *pDoc=GetDocument();
	CPoint p=GetScrollPosition();
	point.x+=p.x;point.y+=p.y;
	BOOL b=FALSE;
	CSize size;
	
	CFont* pOF;
	CDC* pDC=GetDC();
	pOF=pDC->SelectObject(pFont);
	pDC->SetTextColor(m_clrText);
	TEXTMETRIC tm;
	pDC->GetTextMetrics(&tm);
	int nLineHeight = tm.tmHeight;
	
//	pDC->SelectObject(pOF);

	//确定行位置
	int temp=(point.y/nLineHeight);
	if(temp>pDoc->m_SL_L.GetCount()-1) temp=pDoc->m_SL_L.GetCount()-1;
	POSITION pos = pDoc->m_SL_L.FindIndex(temp);
	if(pos){
		m_L_StrLine=pDoc->m_SL_L.GetAt(pos);
		m_LidxY=temp;
	}
	else{
		return;
	}
	
	//确定列位置
	m_L_LC_Str="";
	int n=m_L_StrLine.GetLength()+1;
	char *ps=new char[n];
	
	for(;m_L_LC_Str.GetLength()<m_L_StrLine.GetLength();){
		//前进一个字符,，...
			strcpy(ps,m_L_StrLine.GetBuffer(m_L_StrLine.GetLength()));
			
			char* pLastChar;
			pLastChar= &ps[m_L_LC_Str.GetLength()];
			
			// Now move it forward one double-byte character.
			pLastChar = CharNext (pLastChar );
			pLastChar[0]='\0';			
			m_L_LC_Str.Format("%s",ps);

			//前进一个字符;

		size=pDC->GetTextExtent(m_L_LC_Str,m_L_LC_Str.GetLength());
		if(point.x<size.cx){
			// Now move it back one double-byte character.
			pLastChar = CharPrev ( ps, pLastChar );
			pLastChar[0]='\0';			
			m_L_LC_Str.Format("%s",ps);
			b=TRUE;
			break;
		}
	}
		
	delete ps;

	if(!b){
		m_L_LC_Str=m_L_StrLine;
	}
	size=pDC->GetTextExtent (m_L_LC_Str,m_L_LC_Str.GetLength());
	
	pDC->SelectObject(pOF);
	ReleaseDC(pDC);

	m_bLyrLBntDown=TRUE;
	SetCapture();
	m_xSel1=m_xSel2=size.cx;
	m_ySel1=m_ySel2=m_LidxY;
	Invalidate();

}


void CLSView::Xd_Lyr_LBtnUp(CPoint point)
{
	CLSDoc *pDoc=GetDocument();
	m_bLyrLBntDown=FALSE;
	ReleaseCapture();
}

void CLSView::Xd_Lyr_EditPast()
{
	
	POSITION pos1=m_SL_Cpy.GetHeadPosition();
	CString s="";
	int n=0;
	int Num=m_SL_Cpy.GetCount();
	while (pos1) {
		n++;
		CString str=m_SL_Cpy.GetNext(pos1);	
		if(n==1)
			Xd_Insert_Str(str);
		else 
		{
			Xd_Insert_Return();
			Xd_Insert_Str(str);			
		}
	}
		
	CFont* pOF;
	CDC* pDC=GetDC();
	pOF=pDC->SelectObject(pFont);
	pDC->SetTextColor(m_clrText);
	TEXTMETRIC tm;
	pDC->GetTextMetrics(&tm);
	int nLineHeight = tm.tmHeight + tm.tmExternalLeading;
	CSize size=pDC->GetTextExtent (m_L_LC_Str,m_L_LC_Str.GetLength ());
	
	pDC->SelectObject(pOF);
	ReleaseDC(pDC);

//	Xd_Update_Scrl_Size();
	Invalidate();
}
void CLSView::Xd_Nt_EditPast()
{
	
	POSITION pos1=m_SL_N_CPY.GetHeadPosition();
	CString s="";
	int n=0;
	int Num=m_SL_N_CPY.GetCount();
	while (pos1) {
		n++;
		CString str=m_SL_N_CPY.GetNext(pos1);	
		if(n==1)
			Xd_Insert_StrNt(str);
		else 
		{
			Xd_Insert_Nt_Return();
			Xd_Insert_StrNt(str);			
		}
	}
	Xd_Update_Scrl_Size();
	Invalidate();
}

void CLSView::Xd_Insert_Return()
{
	CLSDoc*pDoc=GetDocument();
	POSITION pos =pDoc->m_SL_L.FindIndex(m_LidxY);
	if(pos)	m_L_StrLine=pDoc->m_SL_L.GetAt(pos);
	
	m_LidxY++;
	
	m_L_StrLine=m_L_StrLine.Right(m_L_StrLine.GetLength()-m_L_LC_Str.GetLength());
	
	pDoc->m_SL_L.InsertAfter(pos,m_L_StrLine);
	pDoc->m_SL_L.SetAt(pos,m_L_LC_Str);	
	m_L_LC_Str="";
}

void CLSView::Xd_Insert_Str(CString str)
{
	CLSDoc*pDoc=GetDocument();
	POSITION pos = pDoc->m_SL_L.FindIndex(m_LidxY);
	if(pos)	m_L_StrLine=pDoc->m_SL_L.GetAt(pos);
	if(m_L_LC_Str.GetLength()<m_L_StrLine.GetLength())
	{
		m_L_StrLine=m_L_StrLine.Right(m_L_StrLine.GetLength()-m_L_LC_Str.GetLength());
		m_L_LC_Str+=str;
		m_L_StrLine=m_L_LC_Str+m_L_StrLine;
	}
	else{
		m_L_StrLine+=str;
		m_L_LC_Str=m_L_StrLine;
	}
	pDoc->m_SL_L.SetAt(pos,m_L_StrLine);
	
}

void CLSView::Xd_Lyr_EditCOPY()
{
	POSITION pos=m_SL_LSel.GetHeadPosition();
	CString s="";
	m_SL_Cpy.RemoveAll();
	while (pos) {
		CString str=m_SL_LSel.GetNext(pos);
		m_SL_Cpy.AddTail(str);
	}	

}

void CLSView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	Xd_Lyr_Save2File("lyr.txt");
	Xd_Nt_Save2File("nt.txt");


	CScrollView::OnRButtonDown(nFlags, point);
}

void CLSView::Xd_Nt_Save2File(CString strFileName)
{
	CLSDoc*pDoc=GetDocument();
	POSITION pos=pDoc->m_SL_N.GetHeadPosition();
	CString s="",s0;
	FILE *fp;
	fp=fopen(strFileName.GetBuffer(strFileName.GetLength()),"w" );
	CString sl;
	while (pos) {
		s0=s=pDoc->m_SL_N.GetNext(pos);
		int c=s.GetLength();	
		for(int i=0;i<(c/3);i++){
			sl=s.Left(3)+";";
			fprintf(fp,"%s",sl.GetBuffer(sl.GetLength()));
			s=s.Right(s.GetLength()-3);
		}
		fprintf(fp,"9");
	}
	fclose(fp);
}

void CLSView::Xd_Lyr_Save2File(CString strFileName)
{
	CLSDoc*pDoc=GetDocument();
	POSITION pos=pDoc->m_SL_L.GetHeadPosition();
	CString s="",s0;
	FILE *fp;
	fp=fopen(strFileName.GetBuffer(strFileName.GetLength()),"w" );
	CString sl;
	while (pos) {
		s0=s=pDoc->m_SL_L.GetNext(pos);
		LPTSTR lpszRoot = s0.GetBuffer(s0.GetLength());
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
	fclose(fp);
}

void CLSView::Xd_Lyr_EditDel()
{
	CLSDoc*pDoc=GetDocument();
	int x1,y1,x2,y2;
	CString s,s1,s2;

	if(!m_bLSel){
		return;
	}
	if(m_ySel1==m_ySel2){
		POSITION pos = pDoc->m_SL_L.FindIndex(m_ySel1);
		if(pos){
			s=pDoc->m_SL_L.GetAt(pos);
			x1=m_xSel1;
			x2=m_xSel2;
			if(m_xSel1>m_xSel2){
				x1=m_xSel2;
				x2=m_xSel1;
			}
			s1=Xd_GetStrByX(s,x1);
			s2=Xd_GetStrByX(s,x2);
			
			s=s1+s.Right(s.GetLength()-s2.GetLength());
			pDoc->m_SL_L.SetAt(pos,s);
			TRACE("s1="+s1+ " s2="+s2+" s="+s);			
		}
	}
	else {
		y1=m_ySel1;
		y2=m_ySel2;
		x1=m_xSel1;
		x2=m_xSel2;
		if(m_ySel1>m_ySel2){
			y1=m_ySel2;
			y2=m_ySel1;
			x1=m_xSel2;
			x2=m_xSel1;
		}
		POSITION pos1 = pDoc->m_SL_L.FindIndex(y1);
		if(pos1){
			s=pDoc->m_SL_L.GetAt(pos1);
			s1=Xd_GetStrByX(s,x1);
		}
		POSITION pos2 = pDoc->m_SL_L.FindIndex(y2);
		if(pos2){
			s=pDoc->m_SL_L.GetAt(pos2);
			s2=Xd_GetStrByX(s,x2);
			s2=s.Right(s.GetLength()-s2.GetLength());
		}		
		pDoc->m_SL_L.SetAt(pos1,s1+s2);
		for(int i=y1+1;i<=y2;i++){
			POSITION pos=pDoc->m_SL_L.FindIndex(y1+1);
			if(pos) pDoc->m_SL_L.RemoveAt(pos);
		}
		m_LidxY=y1;
	}
	m_xSel1=m_xSel2=m_ySel1=m_ySel2=0;
	m_L_LC_Str=s1;
	m_bLSel=FALSE;
	Invalidate();
}

void CLSView::OnXdLyricsScript() 
{
	// TODO: Add your command handler code here
	CLSDoc*pDoc=GetDocument();
	CXDScriptDlg dlg;
	
	dlg.m_pDoc=pDoc;
	if(IDOK==dlg.DoModal()){
		Invalidate();
	}
	Xd_Lyr_MakeCaret(0,0);
}

void CLSView::OnEditCut() 
{
	// TODO: Add your command handler code here
	OnEditCopy();
	OnEditDel();
}

void CLSView::OnEditDel()
{
	switch(m_Type) {
	case XD_TYPE_NOTE:
	//	Xd_Get_Sel_Nt(m_SL_N_CPY);
	case XD_TYPE_LYRICS:
		Xd_Lyr_EditDel();
		break;
	default:
		break;
	}
}

void CLSView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
	CDC *dc = GetDC();
	int x = dc->GetDeviceCaps(LOGPIXELSX);
	int y = dc->GetDeviceCaps(LOGPIXELSY);
	int x1 = pDC->GetDeviceCaps(LOGPIXELSX);
	int y1 = pDC->GetDeviceCaps(LOGPIXELSY);
	
	pDC->SetMapMode(MM_ISOTROPIC);
	pDC->SetWindowExt(x,y);
	pDC->SetViewportExt(x1,y1);

	CScrollView::OnPrint(pDC, pInfo);
}

void CLSView::Xd_Init()
{
	
	m_strN=" 03";//3sps;
	m_strRightOfCaret=m_strLeftOfCaret=m_strLineOfNt="";
	m_idxN_Y=0;
	m_idxN_X=0;

	m_LidxY = 0;
	m_L_LC_Str = "";

}

void CLSView::OnBmpSave() 
{
	// TODO: Add your command handler code here
		CFileDialog dlg(FALSE, "bmp","hjz.bmp");
	if(dlg.DoModal() != IDOK){
		return ;
	}
	CString filePath = dlg.GetPathName();
	// TODO: Add your command handler code here
	CClientDC xdclient(this);//用于本控件的，楼主可以不用此句
	CDC cdc;
	CBitmap bitmap;
	RECT xdrect;CRect r;
//	GetClientRect(&xdrect);
	xdrect.left = 0;
	xdrect.right = m_ScrlSize.cx;
	xdrect.top = 0;
	xdrect.bottom = m_ScrlSize.cy; 
	int	cx = m_ScrlSize.cx;
	int cy = m_ScrlSize.cy;

	bitmap.CreateCompatibleBitmap(&xdclient, cx, cy);
	cdc.CreateCompatibleDC(NULL);
	CBitmap * oldbitmap = (CBitmap* ) cdc.SelectObject(&bitmap);
	cdc.FillRect(&xdrect, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));

	/*
	for(int i = 0; i < GetDocument()->m_strokeList.GetSize(); i ++){
		GetDocument()->m_strokeList.GetAt(i)->DrawStroke(&cdc);
	}
	*/
	Xd_Nt_Draw_List(&cdc);
	Xd_Lyr_Draw(&cdc);

	cdc.SelectObject(oldbitmap);
	::OpenClipboard(this->m_hWnd);
	::EmptyClipboard();
	::SetClipboardData(CF_BITMAP, bitmap);
	::CloseClipboard();
	
	
	HBITMAP hBitmap = (HBITMAP)bitmap;
	HDC hDC;
	int iBits;
	WORD wBitCount;
	DWORD dwPaletteSize=0, dwBmBitsSize=0, dwDIBSize=0, dwWritten=0;
	BITMAP Bitmap; 
	BITMAPFILEHEADER bmfHdr; 
	BITMAPINFOHEADER bi; 
	LPBITMAPINFOHEADER lpbi; 
	HANDLE fh, hDib, hPal,hOldPal=NULL;
	
	hDC = CreateDC("DISPLAY", NULL, NULL, NULL);
	iBits = GetDeviceCaps(hDC, BITSPIXEL) * GetDeviceCaps(hDC, PLANES);
	DeleteDC(hDC);
	if (iBits <= 1)  wBitCount = 1;
	else if (iBits <= 4)  wBitCount = 4;
	else if (iBits <= 8)  wBitCount = 8;
	else      wBitCount = 24;
	
	GetObject(hBitmap, sizeof(Bitmap), (LPSTR)&Bitmap);
	bi.biSize   = sizeof(BITMAPINFOHEADER);
	bi.biWidth   = Bitmap.bmWidth;
	bi.biHeight   = Bitmap.bmHeight;
	bi.biPlanes   = 1;
	bi.biBitCount  = wBitCount;
	bi.biCompression = BI_RGB;
	bi.biSizeImage  = 0;
	bi.biXPelsPerMeter = 0;
	bi.biYPelsPerMeter = 0;
	bi.biClrImportant = 0;
	bi.biClrUsed  = 0;
	
	dwBmBitsSize = ((Bitmap.bmWidth * wBitCount + 31) / 32) * 4 * Bitmap.bmHeight;
	
	hDib = GlobalAlloc(GHND,dwBmBitsSize + dwPaletteSize + sizeof(BITMAPINFOHEADER));
	lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDib);
	*lpbi = bi;
	
	hPal = GetStockObject(DEFAULT_PALETTE);
	if (hPal)
	{
		hDC = ::GetDC(NULL);
		hOldPal = ::SelectPalette(hDC, (HPALETTE)hPal, FALSE);
		RealizePalette(hDC);
	}
	
	GetDIBits(hDC, hBitmap, 0, (UINT) Bitmap.bmHeight,
		(LPSTR)lpbi + sizeof(BITMAPINFOHEADER) + dwPaletteSize, 
		(BITMAPINFO *)lpbi, DIB_RGB_COLORS);
	
	if (hOldPal)
	{
		::SelectPalette(hDC, (HPALETTE)hOldPal, TRUE);
		RealizePalette(hDC);
		::ReleaseDC(NULL, hDC);
	}
	
	fh = CreateFile(filePath, GENERIC_WRITE,0, NULL, CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, NULL);
	
	if (fh == INVALID_HANDLE_VALUE)  
		return 		;
	
	bmfHdr.bfType = 0x4D42; // "BM"
	dwDIBSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + dwPaletteSize + dwBmBitsSize; 
	bmfHdr.bfSize = dwDIBSize;
	bmfHdr.bfReserved1 = 0;
	bmfHdr.bfReserved2 = 0;
	bmfHdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + (DWORD)sizeof(BITMAPINFOHEADER) + dwPaletteSize;
	
	WriteFile(fh, (LPSTR)&bmfHdr, sizeof(BITMAPFILEHEADER), &dwWritten, NULL);
	WriteFile(fh, (LPSTR)lpbi, dwDIBSize, &dwWritten, NULL);
	
	GlobalUnlock(hDib);
	GlobalFree(hDib);
	CloseHandle(fh); 
}
