// LSView.h : interface of the CLSView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_LSVIEW_H__CAE3C481_3BA1_4F75_B7D6_CB9CDCCAD1A1__INCLUDED_)
#define AFX_LSVIEW_H__CAE3C481_3BA1_4F75_B7D6_CB9CDCCAD1A1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef enum {
	XD_TYPE_NOTE,
	XD_TYPE_LYRICS,
}XDTYPE;

class CLSView : public CScrollView
{
public:
	
	void Xd_Nt_SetCaret(int x, int y);
	
private:
	void OnEditDel();
	void Xd_Lyr_EditDel();
	void Xd_Lyr_Save2File(CString strFileName);
	void Xd_Nt_Save2File(CString strFileName);
	void Xd_Lyr_EditCOPY();
	void Xd_Insert_Str(CString str);
	void Xd_Insert_Return();
	void Xd_Lyr_LBtnUp(CPoint point);
	void Xd_Lyr_MouseMove(CPoint point);
	void Xd_Lyr_LBtnDown(CPoint point);
	void Xd_Lyr_SetCaret(int x,int y);
	void Xd_Lyr_MakeCaret(int x,int y);
	void XD_Lyr_KeyDown(UINT nChar);
	CString Xd_GetStrByX(CString str, int x);
	void Xd_Lyr_Draw(CDC* pDC);
	void Xd_Lyr_Char(UINT nChar);
	void Xd_Nt_LBtnDown(CPoint point);
	void Xd_Nt_MouseMove(CPoint point);
	void Xd_Nt_LBtnUp(CPoint point);
	void Xd_Update_Scrl_Size();
	void Xd_Insert_Nt_Return();
	void Xd_Insert_StrNt(CString str);
	void Xd_Get_Sel_Nt(CStringList &strList);
	void XD_Nt_KeyDown(UINT nChar);
	void Xd_Nt_MakeCaret(int x,int y);
	void Xd_Nt_Draw_List(CDC* pDC);
//	void Xd_Nt_Char_Line(UINT nChar);
	void Xd_Nt_Char_To_List(UINT nChar);
	void Xd_Nt_Draw_One(CDC* pDC,int x,int y,CString strN);
	void Xd_Nt_Char(UINT nChar);
	int					m_idxN_Y,m_idxN_X;
	int					m_idxN_SX1;
	int					m_idxN_SY1;
	int					m_idxN_SX2;
	int					m_idxN_SY2;
	
	CString				m_strN,m_strLineOfNt,m_strLeftOfCaret,m_strRightOfCaret;

	COLORREF m_clrText;
	CFont* pFont;

	int xddbg;
	BOOL				m_bNtLBntDown,m_bLyrLBntDown;

	CStringList			m_SL_N_CPY;
	CSize				m_ScrlSize;

	XDTYPE				m_Type;

	CStringList			m_SL_LSel,m_SL_Cpy;

	CString				m_L_StrLine,m_L_LC_Str;
	int					m_LidxY;
	int					m_xSel1,m_ySel1,m_xSel2,m_ySel2;
	BOOL				m_bLSel;
	
protected: // create from serialization only
	CLSView();
	DECLARE_DYNCREATE(CLSView)

// Attributes
public:
	CLSDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLSView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	void Xd_Init();
	void Xd_Lyr_EditPast();
	void Xd_Nt_EditPast();
	virtual ~CLSView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CLSView)
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnViewFont();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnEditCopy();
	afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
	afx_msg void OnEditPaste();
	afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
	afx_msg void OnXdLyrics();
	afx_msg void OnUpdateXdLyrics(CCmdUI* pCmdUI);
	afx_msg void OnXdNote();
	afx_msg void OnUpdateXdNote(CCmdUI* pCmdUI);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnXdLyricsScript();
	afx_msg void OnEditCut();
	afx_msg void OnBmpSave();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in LSView.cpp
inline CLSDoc* CLSView::GetDocument()
   { return (CLSDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LSVIEW_H__CAE3C481_3BA1_4F75_B7D6_CB9CDCCAD1A1__INCLUDED_)
