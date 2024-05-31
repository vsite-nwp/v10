// Doc.cpp : implementation of the Doc class
//

#include "stdafx.h"
#include "v10.h"

#include "Set.h"
#include "Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Doc

IMPLEMENT_DYNCREATE(Doc, CDocument)

BEGIN_MESSAGE_MAP(Doc, CDocument)
	//{{AFX_MSG_MAP(Doc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Doc construction/destruction

Doc::Doc()
{
}

Doc::~Doc()
{
	if(m_db!=NULL)
	if (m_db->IsOpen())
		m_db->Close();
	delete m_db;

}

BOOL Doc::OnNewDocument()
{
	m_db = new CDatabase();
	m_db->OpenEx(_T("DSN=User;UID"));


	m_set = new Set(m_db);
	m_set->Open();
	if (!CDocument::OnNewDocument())
		return FALSE;

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// Doc diagnostics

#ifdef _DEBUG
void Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// Doc commands
