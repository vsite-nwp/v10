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

void RecView::OnPrint(CDC* pDC, CPrintInfo* PInfo)
{
	int width = pDC->GetDeviceCaps(HORZRES);
	int height = pDC->GetDeviceCaps(VERTRES);
	int xPos = width / 10;
	int yPos = height / 10;
	CSize fontSize = pDC->GetTextExtent("ID");
	pDC->TextOut(xPos, yPos, "Id");
	pDC->TextOut(xPos * 2, yPos, "Name");
	pDC->TextOut(xPos * 4, yPos, "Manager");
	yPos += fontSize.cy * 2;
	pDC->MoveTo(xPos, yPos);
	pDC->LineTo(xPos * 6, yPos);

	Set rs;
	rs.Open();

	while (!rs.IsEOF()) 
	{
		CString id;	
		id.Format("%d", rs.m_id);	
		CString footer;
		footer.Format("Page %d of %d", PInfo->m_nCurPage, PInfo->GetMaxPage());
		pDC->DrawText(footer, PInfo->m_rectDraw, DT_RIGHT | DT_BOTTOM | DT_SINGLELINE);
		yPos += fontSize.cy;
		pDC->TextOut(xPos, yPos, id);
		pDC->TextOut(xPos * 2, yPos, rs.m_name);
		
		if (rs.m_manager)
		{
			pDC->TextOut(xPos * 4, yPos, 'x');
		}

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

