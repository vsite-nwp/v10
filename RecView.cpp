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

void RecView::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
	const int height = pDC->GetDeviceCaps(VERTRES);
	const int width = pDC->GetDeviceCaps(HORZRES);
	CSize fontSize = pDC->GetTextExtent(_T("O"));
	//fontSize.cy = 100;
	int vspace = fontSize.cy;
	pDC->TextOut(width * 0.1, vspace, _T("ID"));
	pDC->TextOut(width * 0.3, vspace, _T("Ime"));
	pDC->TextOut(width * 0.5, vspace, _T("Manager"));
	vspace += fontSize.cy * 2;
	pDC->MoveTo(width * 0.1, vspace);
	pDC->LineTo(width * 0.6, vspace);
	
	Set rs;
	rs.Open();
	while (!rs.IsEOF()) {
		CString id;
		id.Format(_T("%d"), rs.m_id);
		pDC->TextOut(width * 0.1, vspace += fontSize.cy, id);
		pDC->TextOut(width * 0.3, vspace, _T(rs.m_name));
		if (rs.m_manager)
			pDC->TextOut(width * 0.5, vspace, "X");
		vspace += fontSize.cy;
		rs.MoveNext();
	}
	rs.Close();
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

