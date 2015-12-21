// v10.h : main header file for the V10 application
//

#if !defined(AFX_V10_H__A6E1AFE0_1E36_4348_BC72_B81084FE302D__INCLUDED_)
#define AFX_V10_H__A6E1AFE0_1E36_4348_BC72_B81084FE302D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// App:
// See v10.cpp for the implementation of this class
//

class App : public CWinApp
{
public:
	App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(App)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_V10_H__A6E1AFE0_1E36_4348_BC72_B81084FE302D__INCLUDED_)
