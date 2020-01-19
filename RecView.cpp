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
	ON_EN_CHANGE(IDC_EDIT1, &RecView::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, &RecView::OnEnChangeEdit2)
	ON_BN_CLICKED(IDC_CHECK1, &RecView::OnBnClickedCheck1)
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
	DDX_FieldCheck(pDX, IDC_CHECK1, m_pSet->m_manager, m_pSet);
	DDX_FieldText(pDX, IDC_EDIT1, m_pSet->m_id, m_pSet);
	DDX_FieldText(pDX, IDC_EDIT2, m_pSet->m_name, m_pSet);

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
	int horiz=pDC->GetDeviceCaps(HORZRES)/8;
	int vert=pDC->GetDeviceCaps(VERTRES)/12;
	CSize textht = pDC->GetTextExtent("Mj");
	double namespacing = 1.5;
	int mngspacing = 4;
	int rowht = textht.cy + vert*1.1;
	pDC->TextOut(horiz, vert, "ID");
	pDC->TextOut(horiz*namespacing, vert, "NAME");
	pDC->TextOut(horiz * mngspacing, vert, "STATUS");
	pDC->MoveTo(horiz,rowht);
	pDC->LineTo(horiz * 8,rowht);
	while (!rs.IsEOF()) {
		CString id;
		rowht +=textht.cy;
		id.Format("%d", rs.m_id);
		pDC->TextOut(horiz, rowht,id);
		pDC->TextOut(horiz*namespacing, rowht, rs.m_name);
		if (rs.m_manager) {
			pDC->TextOut(horiz*mngspacing, rowht,"Manager");
		}
		else {
			pDC->TextOut(horiz*mngspacing, rowht, "Peasant");
		}
		rs.MoveNext();
		pDC->MoveTo(horiz, rowht);
		pDC->LineTo(horiz * 8, rowht);
	}
	rowht += textht.cy;
	pDC->MoveTo(horiz*namespacing*0.95, vert);
	pDC->LineTo(horiz*namespacing*0.95, rowht);
	pDC->MoveTo(horiz*mngspacing*0.97, vert);
	pDC->LineTo(horiz*mngspacing*0.97, rowht);
}


void RecView::OnEnChangeEdit1()
{
	//IDEA: send data to base somehow
}
void RecView::OnEnChangeEdit2()
{
	OnEnChangeEdit1();
}
void RecView::OnBnClickedCheck1()
{
	OnEnChangeEdit1();
}
