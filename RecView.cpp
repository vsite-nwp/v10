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

	RECT rect = pInfo->m_rectDraw;
	POINT a;
	int numOfColumns = 3;
	a.y = rect.bottom / 10;
	a.x = 0;
	
	pDC->MoveTo(a);
	a.x = rect.right;
	pDC->LineTo(a);
	rect.top = rect.bottom / 15;
	CFont font; font.CreateFont(-20*pDC->GetDeviceCaps(LOGPIXELSY)/72, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, TEXT("Times New Roman"));
	pDC->SelectObject(&font);
	CString str = TEXT("ID");	
	pDC->DrawText(str, &rect, DT_LEFT);
	rect.left = pInfo->m_rectDraw.right / numOfColumns;
	str = "Name";
	pDC->DrawText(str, &rect, DT_LEFT);
	rect.left = 2 * (pInfo->m_rectDraw.right / numOfColumns);
	str = "Manager";
	pDC->DrawText(str, &rect, DT_LEFT);
	int textSize = pDC->GetTextExtent(str).cy;
	rect.top += textSize;
	while ( !rs.IsEOF() ) {
		rect.left = pInfo->m_rectDraw.left;
		rect.top += textSize;
		str.Format(_T("%d"), rs.m_id);
		pDC->DrawText(str, &rect, DT_LEFT);
		rect.left = pInfo->m_rectDraw.right / numOfColumns;
		pDC->DrawText(rs.m_name, &rect, DT_LEFT);
		rect.left = 2 * (pInfo->m_rectDraw.right / numOfColumns);
		if(rs.m_manager)
			pDC->DrawText("x", &rect, DT_LEFT);
		rs.MoveNext();
	}

	CRecordView::OnPrint(pDC, pInfo);
}
