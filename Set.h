// Set.h : interface of the Set class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SET_H__B64A9F02_E3ED_422B_8EDD_3311D57DDDC9__INCLUDED_)
#define AFX_SET_H__B64A9F02_E3ED_422B_8EDD_3311D57DDDC9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Set : public CRecordset
{
public:
	Set(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(Set)

// Field/Param Data
	//{{AFX_FIELD(Set, CRecordset)
	long	m_id;
	CString	m_name;
	BOOL	m_manager;
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Set)
	public:
	virtual CString GetDefaultConnect();	// Default connection string
	virtual CString GetDefaultSQL(); 	// default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);	// RFX support
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SET_H__B64A9F02_E3ED_422B_8EDD_3311D57DDDC9__INCLUDED_)

