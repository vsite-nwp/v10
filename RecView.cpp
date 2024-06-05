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

void RecView::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
	UINT const height = pDC->GetDeviceCaps(VERTRES);
	UINT const width = pDC->GetDeviceCaps(HORZRES);
	Set rs;
	rs.Open();
	CSize size = pDC->GetTextExtent(rs.m_name);
	UINT lheight = size.cy;
	UINT yPos = 20;
	UINT xPosID = width / 50;
	UINT xPosName = width / 20;
	UINT xPosManager = width / 3;

	pDC->TextOut(xPosID, yPos, _T("ID"));
	pDC->MoveTo(xPosID *2, 0);
	pDC->LineTo(xPosID *2, height);

	pDC->TextOut(xPosName, yPos, _T("Name"));
	pDC->MoveTo(xPosName * 6, 0);
	pDC->LineTo(xPosName * 6, height);

	pDC->TextOut(xPosManager, yPos, _T("Manager"));

	yPos += lheight;
	
	while (!rs.IsEOF())
	{
		pDC->MoveTo(0, yPos - 5);
		pDC->LineTo(width, yPos - 5);
		CString id;
		id.Format(_T("%d"), rs.m_id);
		pDC->TextOut(xPosID, yPos, id);
		pDC->TextOut(xPosName, yPos, rs.m_name);
		CString isManager = rs.m_manager ? _T("X") : _T("");
		pDC->TextOut(xPosManager, yPos, isManager);
		
		yPos += lheight;		
		rs.MoveNext();
	}
}

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

