
// RightWorkerWinView.cpp : implementation of the CRightWorkerWinView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "RightWorkerWin.h"
#endif

#include "RightWorkerWinDoc.h"
#include "RightWorkerWinView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRightWorkerWinView

IMPLEMENT_DYNCREATE(CRightWorkerWinView, CView)

BEGIN_MESSAGE_MAP(CRightWorkerWinView, CView)
END_MESSAGE_MAP()

// CRightWorkerWinView construction/destruction

CRightWorkerWinView::CRightWorkerWinView() noexcept
{
	// TODO: add construction code here

}

CRightWorkerWinView::~CRightWorkerWinView()
{
}

BOOL CRightWorkerWinView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CRightWorkerWinView drawing

void CRightWorkerWinView::OnDraw(CDC* /*pDC*/)
{
	CRightWorkerWinDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CRightWorkerWinView diagnostics

#ifdef _DEBUG
void CRightWorkerWinView::AssertValid() const
{
	CView::AssertValid();
}

void CRightWorkerWinView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CRightWorkerWinDoc* CRightWorkerWinView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CRightWorkerWinDoc)));
	return (CRightWorkerWinDoc*)m_pDocument;
}
#endif //_DEBUG


// CRightWorkerWinView message handlers
