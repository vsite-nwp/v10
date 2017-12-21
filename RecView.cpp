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
	DDX_FieldText(pDX, IDC_EDIT1, m_pSet->m_id, m_pSet);
	DDX_FieldText(pDX, IDC_EDIT2, m_pSet->m_name, m_pSet);
	DDX_FieldCheck(pDX, IDC_CHECK1, m_pSet->m_manager, m_pSet);
	//{{AFX_DATA_MAP(RecView)
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

void RecView::OnPrint(CDC* pDC, CPrintInfo* pInfo) {
	
	Set rs;
	rs.Open(); 
	CRect page = pInfo->m_rectDraw;
	page.DeflateRect(1000, 1000, 2000, 1000);	// to be replaced with varibles for user-inputed margins
	int i = 0;									//counter for GetODBCFieldInfo
	int j = 1;									// counter for number of columns
	short k = rs.GetODBCFieldCount(); 
	CSize z = pDC->GetTextExtent(m_pSet->m_name); 
	CSize z2;
	int zcy = z.cy;
	int x = page.right / k; 
	
	
	while (k > i) {
		CODBCFieldInfo info; 
		rs.GetODBCFieldInfo(i, info);
		pDC->TextOut(j*x, z.cy * 4, info.m_strName);
		if(i == k-1)
			z2 = pDC->GetTextExtent(info.m_strName); // gets the width of the last column's name
		i++;  j++;
	}
	
	pDC->MoveTo(x, z.cy * 5);
	pDC->LineTo(page.right+z2.cx, z.cy * 5); //line to right edge of the rect + the width of the last column's name, *Saves Ink*
											 // and makes sure that the line is only as wide as the table
	
	z.cy *= 6;
	
	while (!rs.IsEOF()) {
		CString id;
		id.Format(_T("%d"), rs.m_id);				//if(z.cy == the height of the page)->move to the next page
		pDC->TextOut(x,  z.cy, id); 
		pDC->TextOut(x*(k-1), z.cy, rs.m_name);
		if (rs.m_manager)
			pDC->TextOut(x*k, z.cy, "x"); 
		z.cy += zcy; 
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

