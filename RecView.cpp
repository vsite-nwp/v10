// RecView.cpp : implementation of the RecView class
//

#include "stdafx.h"
#include "v10.h"

#include "Set.h"
#include "Doc.h"
#include "RecView.h"
#include "Math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// RecView

IMPLEMENT_DYNCREATE(RecView, CRecordView)

BEGIN_MESSAGE_MAP(RecView, CRecordView)
	//{{AFX_MSG_MAP(RecView)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CRecordView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CRecordView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CRecordView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// RecView construction/destruction

RecView::RecView()
	: CRecordView(RecView::IDD)
{
}

RecView::~RecView()
{
}

void RecView::DoDataExchange(CDataExchange* pDX)
{
	CRecordView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(RecView)
	//}}AFX_DATA_MAP
	DDX_FieldText(pDX, IDC_EDIT1, m_pSet->m_id, m_pSet);
	DDX_FieldText(pDX, IDC_EDIT2, m_pSet->m_name, m_pSet);
	DDX_FieldCheck(pDX, IDC_CHECK1, m_pSet->m_manager, m_pSet);
}

BOOL RecView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CRecordView::PreCreateWindow(cs);
}

void RecView::OnInitialUpdate()
{
	m_pSet = &GetDocument()->m_set;
	CRecordView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

}

/////////////////////////////////////////////////////////////////////////////
// RecView printing

BOOL RecView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}


void RecView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

void RecView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

/////////////////////////////////////////////////////////////////////////////
// RecView diagnostics

#ifdef _DEBUG
void RecView::AssertValid() const
{
	CRecordView::AssertValid();
}

void RecView::Dump(CDumpContext& dc) const
{
	CRecordView::Dump(dc);
}

Doc* RecView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Doc)));
	return (Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// RecView database support
CRecordset* RecView::OnGetRecordset()
{
	return m_pSet;
}


/////////////////////////////////////////////////////////////////////////////
// RecView message handlers

void RecView::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
	CString sID;
	int cHeight = pDC->GetTextExtent("A").cy;
	CRect rc = pInfo->m_rectDraw;

	//margins
	int lmargin = 500;
	int tmargin = 500;
	int rmargin = 1000;
	int bmargin = 500;
	int colID = 0;
	int colName = colID + 1000;
	int colManager = colName + 5000;
	rc.DeflateRect(lmargin,tmargin,rmargin,bmargin);
	pDC->SetViewportOrg(rc.left, rc.top);

	int i = 3;
	Set rs;
	rs.Open();

	//table columns
	pDC->MoveTo(0, cHeight * 2.5);
	pDC->LineTo(rc.right, cHeight * 2.5);
	pDC->TextOutA(colID,  cHeight, _T("id"));
	pDC->TextOutA(colName, cHeight, _T("name"));
	pDC->TextOutA(colManager, cHeight, _T("manager"));
	while (!rs.IsEOF()) {
		//rows
		if (i * cHeight > rc.bottom)
			break;
		sID.Format("%ld", rs.m_id);
		pDC->TextOutA(colID, cHeight * i, sID);
		pDC->TextOutA(colName, cHeight * i, rs.m_name);
		if(rs.m_manager) pDC->TextOutA(colManager, cHeight * i, _T("X"));
		++i;

		rs.MoveNext();
	}

	CRecordView::OnPrint(pDC, pInfo);

	
}


