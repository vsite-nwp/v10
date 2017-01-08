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
		DDX_FieldText(pDX,IDC_EDIT1 , m_pSet->m_id, m_pSet);
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

void RecView::OnPrint(CDC * pDC, CPrintInfo * pInfo)
{
	int vertical = pDC->GetDeviceCaps(VERTRES);
	int horizontal = pDC->GetDeviceCaps(HORZRES);
	CSize text_high = pDC->GetTextExtent("ABC");
	int y_pos = text_high.cy;
	int pomakID = int(horizontal*0.1);
	int pomakIme = int(horizontal*0.3);
	int pomakManager = int(horizontal*0.6);

	pDC->TextOut(pomakID, y_pos, _T("id"));
	pDC->TextOut(pomakIme, y_pos, _T("name"));
	pDC->TextOut(pomakManager, y_pos, _T("manager"));

	y_pos += 2 * text_high.cy;
	pDC->MoveTo(pomakID, y_pos);
	pDC->LineTo(pomakManager*1.5, y_pos);
	y_pos += text_high.cy;

	Set rs;
	rs.Open();
	while (!rs.IsEOF()) {
		CString s;
		s.Format(_T("%d"), rs.m_id);
		pDC->TextOut(pomakID, y_pos, s);
		pDC->TextOut(pomakIme, y_pos, rs.m_name);
		if (rs.m_manager)
			pDC->TextOutA(pomakManager, y_pos, "x");
		y_pos += text_high.cy;
		rs.MoveNext();
	}
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










