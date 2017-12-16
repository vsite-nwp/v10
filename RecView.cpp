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
	Set rs;
	rs.Open();
	POINT margins{400, 300};
	long cellX = pDC->GetDeviceCaps(HORZRES) / rs.GetODBCFieldCount();
	CSize strSize = pDC->GetTextExtent(std::to_string(rs.m_id).c_str());
	RECT cell{ margins.x, margins.y,cellX, strSize.cy+margins.y};
	//header drawing
	pDC->DrawText(_T("ID"), &cell, DT_LEFT|DT_BOTTOM);
	cell = {cellX, margins.y, cellX*2, strSize.cy+margins.y};
	pDC->DrawText(_T("Name"), &cell, DT_LEFT | DT_BOTTOM);
	cell = { cellX*2, margins.y, cellX*3, strSize.cy+margins.y };
	pDC->DrawText(_T("Manager"), &cell, DT_LEFT | DT_BOTTOM);
	pDC->MoveTo(margins.x, strSize.cy+margins.y);
	pDC->LineTo(pDC->GetDeviceCaps(HORZRES) - margins.x, strSize.cy+margins.y);

	for (int movY = 2; !rs.IsEOF();movY+=2) {
		cell = { margins.x, strSize.cy * movY+margins.y, cellX, strSize.cy * (movY+2)+margins.y };
		pDC->DrawText(std::to_string(rs.m_id).c_str(), &cell, DT_LEFT | DT_BOTTOM);
		cell = { cellX, strSize.cy * movY+margins.y, cellX * 2, strSize.cy * (movY+2)+margins.y};
		pDC->DrawText(rs.m_name, &cell, DT_LEFT | DT_BOTTOM);
		if (rs.m_manager) {
			cell = { cellX * 2, strSize.cy * movY+margins.y, cellX * 3, strSize.cy * (movY+2)+margins.y };
			pDC->DrawText(_T("x"), &cell, DT_LEFT | DT_BOTTOM);
		}

		rs.MoveNext();
	}
	CRecordView::OnPrint(pDC, pInfo);
}
