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
	DDX_FieldText(pDX, IDC_EDIT1, m_pSet->m_id, m_pSet);
	DDX_FieldText(pDX, IDC_EDIT2, m_pSet->m_name, m_pSet);
	DDX_FieldCheck(pDX, IDC_CHECK1, m_pSet->m_manager, m_pSet);
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

void RecView::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
	int pageWidth = pDC->GetDeviceCaps(HORZRES);
	int pageHeight = pDC->GetDeviceCaps(VERTRES);

	CSize textSize = pDC->GetTextExtent(_T("Sample Text"));
	int lineHeight = textSize.cy;
	int borderHeight = textSize.cy + textSize.cy / 2;


	Set rs;
	rs.Open();
	int yPos = lineHeight;
	int leftMargin = 200;
	int rightMargin = pageWidth - leftMargin;


	pDC->TextOut(leftMargin, yPos, _T("id"));
	pDC->TextOut(pageWidth / 4, yPos, _T("name"));
	pDC->TextOut(2 * (pageWidth / 4), yPos, _T("manager"));


	yPos += borderHeight;
	pDC->MoveTo(leftMargin, yPos);
	pDC->LineTo(rightMargin, yPos);

	yPos += borderHeight;

	while (!rs.IsEOF())
	{
		CString id;
		id.Format(_T("%d"), rs.m_id);
		pDC->TextOut(leftMargin, yPos, id);
		pDC->TextOut(pageWidth / 4, yPos, rs.m_name);
		CString manager = rs.m_manager ? _T("x") : _T("");
		pDC->TextOut(2 * (pageWidth / 4), yPos, manager);

		yPos += borderHeight;
		/*pDC->MoveTo(leftMargin, yPos);*/
		for (int i = leftMargin; i <= rightMargin; i += 100) {
			pDC->MoveTo(i, yPos);
			pDC->LineTo(i + 30, yPos);
		}

		yPos += lineHeight;
		rs.MoveNext();
	}
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

