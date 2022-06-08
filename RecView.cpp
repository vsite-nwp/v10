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
	// TODO: Add your specialized code here and/or call the base class
	int horizontal = pDC->GetDeviceCaps(HORZRES); //5100
	int vertical = pDC->GetDeviceCaps(VERTRES);   //6600
	CSize fontSize = pDC->GetTextExtent("Font");
	//int pageSize = pInfo->m_rectDraw.Width();


	int columns = horizontal / 7;
	//int rows = fontSize.cy;
	int row = fontSize.cy;


	/*pDC->DrawText(_T("ID"),pInfo->m_rectDraw,DT_LEFT|DT_TOP);
	pDC->DrawText(_T("Name"),pInfo->m_rectDraw,DT_CENTER|DT_TOP);
	pDC->DrawText(_T("Menager"),pInfo->m_rectDraw,DT_RIGHT|DT_TOP);*/

	pDC->TextOut(columns*2, row, _T("ID"));
	pDC->TextOut(columns*4, row, _T("Name"));
	pDC->TextOut(columns*6, row, _T("Menager"));

	row += row*2;
	pDC->MoveTo(0,row);
	pDC->LineTo(horizontal,row);
	

	//CRecordView::OnPrint(pDC, pInfo); // to mi ne treba

	//pDC->MoveTo(0, rows);
	row += fontSize.cy;
	Set rs;
	rs.Open();
	while (!rs.IsEOF()) {
		// draw current record
		CString id;
		id.Format("%d", rs.m_id);


		pDC->TextOut(columns*2,row,id);
		pDC->TextOut(columns*4,row,rs.m_name);

		if (rs.m_manager) {
			pDC->TextOut(columns*6, row, 'X');
		}
		
		row += fontSize.cy;
		rs.MoveNext();
	}

	//OnBeginPrinting izra�una koliko pixela zauzima svaki red
	//u pInfo imamo visinu svake stranice CRect m_rectDraw
}
