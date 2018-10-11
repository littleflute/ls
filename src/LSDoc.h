// LSDoc.h : interface of the CLSDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_LSDOC_H__2C1F056E_0163_48BB_8424_56A73D59ED67__INCLUDED_)
#define AFX_LSDOC_H__2C1F056E_0163_48BB_8424_56A73D59ED67__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CLSDoc : public CDocument
{
protected: // create from serialization only
	CLSDoc();
	DECLARE_DYNCREATE(CLSDoc)

// Attributes
public:
	CStringList			m_SL_N,m_SL_L;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLSDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual void DeleteContents();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CLSDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CLSDoc)
	afx_msg void OnFileSaveAsHtml();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CString v_Get_Base_Htm_File();
	void Xd_Lyr_Save2Html(FILE* fp);
	void Xd_Nt_Save2Html(FILE* fp);
	void Xd_Serialize_Notes(CArchive &ar);
	void Xd_Serialize_Lyrics(CArchive &ar);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LSDOC_H__2C1F056E_0163_48BB_8424_56A73D59ED67__INCLUDED_)
