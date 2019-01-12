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

RecView::RecView()	: CRecordView(RecView::IDD)
{
	CString section(_T("Print"));
	numPages = AfxGetApp()->GetProfileInt(section, _T("NumPages"), 4);
	fontSize = AfxGetApp()->GetProfileInt(section, _T("FontSize"), 36);
	fontName = AfxGetApp()->GetProfileString(section, _T("FontName"), _T("Times New Roman"));
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
	pInfo->SetMaxPage(numPages);
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
	int h_res = pDC->GetDeviceCaps(HORZRES);
	CSize fontSize = pDC->GetTextExtent("A");
	int newRow = fontSize.cy;
	int x_id = h_res / 12;
	int x_name = x_id * 3;
	int x_manager = x_id * 6;
	pDC->TextOut(x_id, newRow, "ID");
	pDC->TextOut(x_name,newRow , "NAME");
	pDC->TextOut(x_manager,newRow , "MANAGER");
	newRow += newRow;
	pDC->MoveTo(x_id, newRow);
	pDC->LineTo(x_manager + (fontSize.cx * 8),newRow);
	Set rs;
	rs.Open();
	while (!rs.IsEOF()) {
		CString id;
		id.Format("%d", rs.m_id);
		pDC->TextOut(x_id, newRow+=fontSize.cy, id);
		pDC->TextOut(x_name, newRow, rs.m_name);
		if (rs.m_manager)
			pDC->TextOut(x_manager + (fontSize.cx * 3), newRow, "X");
		// draw current record
		rs.MoveNext();
	}
}
