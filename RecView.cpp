// RecView.cpp : implementation of the RecView class
//

#include "stdafx.h"
#include "v10.h"

#include "Set.h"
#include "Doc.h"
#include "RecView.h"

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
	DDX_FieldCheck(pDX, IDC_CHECK1, m_pSet->m_manager, m_pSet);
	DDX_FieldText(pDX, IDC_EDIT1, m_pSet->m_id, m_pSet);
	DDX_FieldText(pDX, IDC_EDIT2, m_pSet->m_name, m_pSet);
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
	CSize cSize = pDC->GetTextExtent("Renato");
	int horRes = pDC->GetDeviceCaps(HORZRES);
	int verRes = pDC->GetDeviceCaps(VERTRES);
	int margin = horRes * 0.01;
	int colID = margin;
	int colName = (horRes / 3);
	int colMng = ((horRes / 3) * 2);
	int yOs = cSize.cy * 2;

	pDC->TextOut(colID + margin, cSize.cy, _T("id"));
	pDC->TextOut(colName + margin, cSize.cy, _T("Name"));
	pDC->TextOut(colMng + margin, cSize.cy, _T("Manager"));

	//horizontal lines
	pDC->MoveTo(margin, yOs);
	pDC->LineTo(horRes - margin, yOs);

	//vertical lines
	pDC->MoveTo(margin, cSize.cy);
	pDC->LineTo(margin, verRes);
	pDC->MoveTo(colName, cSize.cy);
	pDC->LineTo(colName, verRes);
	pDC->MoveTo(colMng, cSize.cy);
	pDC->LineTo(colMng, verRes);
	
	Set rs;
	rs.Open();

	while (!rs.IsEOF()) {

		CString str;
		str.Format(_T("%d"), rs.m_id);
		
		pDC->TextOut(colID + margin, yOs, str);
		pDC->TextOut(colName + margin, yOs, rs.m_name);
		if (rs.m_manager)
			pDC->TextOut(colMng + margin, yOs, _T("x"));

		pDC->MoveTo(margin, yOs);
		pDC->LineTo(horRes - margin, yOs);

		yOs += cSize.cy;
		rs.MoveNext();
	}

	CRecordView::OnPrint(pDC, pInfo);
}
