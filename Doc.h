// Doc.h : interface of the Doc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DOC_H__667BC424_D221_4413_A921_D549C94C0DC6__INCLUDED_)
#define AFX_DOC_H__667BC424_D221_4413_A921_D549C94C0DC6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Set.h"


class Doc : public CDocument
{
protected: // create from serialization only
	Doc();
	DECLARE_DYNCREATE(Doc)

// Attributes
public:
	CDatabase* m_db;
	Set* m_set;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Doc)
	public:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(Doc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DOC_H__667BC424_D221_4413_A921_D549C94C0DC6__INCLUDED_)
