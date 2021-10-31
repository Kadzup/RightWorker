
// RightWorkerWinView.h : interface of the CRightWorkerWinView class
//

#pragma once


class CRightWorkerWinView : public CView
{
protected: // create from serialization only
	CRightWorkerWinView() noexcept;
	DECLARE_DYNCREATE(CRightWorkerWinView)

// Attributes
public:
	CRightWorkerWinDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CRightWorkerWinView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in RightWorkerWinView.cpp
inline CRightWorkerWinDoc* CRightWorkerWinView::GetDocument() const
   { return reinterpret_cast<CRightWorkerWinDoc*>(m_pDocument); }
#endif

