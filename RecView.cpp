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
	DDX_FieldCheck(pDX, IDC_CHECK1, m_pSet->m_manager, m_pSet);
	DDX_FieldText(pDX, IDC_EDIT1, m_pSet->m_id, m_pSet);
	DDX_FieldText(pDX, IDC_EDIT2, m_pSet->m_name, m_pSet);
	//}}AFX_DATA_MAP
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
	// Add your specialized code here and/or call the base class

	int horizontal_res = pDC->GetDeviceCaps(HORZRES);
	int vertical_res = pDC->GetDeviceCaps(VERTRES);

	CSize size = pDC->GetTextExtent("T");
	int position_y = size.cy;

	int hor_size = horizontal_res / 10;

	pDC->TextOut(hor_size, position_y, _T("ID"));
	pDC->TextOut(3* hor_size, position_y, _T("Name"));
	pDC->TextOut(5.5*hor_size, position_y, _T("Manager"));

	position_y *= 2.5;

	pDC->MoveTo(hor_size, position_y);
	pDC->LineTo(6.5*hor_size, position_y);

	Set rs;
	rs.Open();
	while (!rs.IsEOF()) {
		CString txt;
		txt.Format(_T("%d"), rs.m_id);
		position_y += size.cy;

		pDC->TextOut(hor_size, position_y,txt);
		pDC->TextOut(3 * hor_size, position_y, rs.m_name);

		if (rs.m_manager) pDC->TextOut(5.5 * hor_size, position_y, _T("X"));
		
		rs.MoveNext();
	}

	//CRecordView::OnPrint(pDC, pInfo);
}
