
#pragma once
#include <RightWorker.h>

class CRightWorkerWinView : public CView
{
protected: // create from serialization only
	CRightWorkerWinView() noexcept;
	DECLARE_DYNCREATE(CRightWorkerWinView)

	RightWorker* m_pRightWorker;

	// Attributes
public:
	CRightWorkerWinDoc* GetDocument() const;

	// text field
	CEdit* m_pInputField;
	// list view
	CListBox* m_pParsedList;
	// text
	CStatic* m_pInputLabel;
	CStatic* m_pListLabel;
	// buttons
	CButton* m_pParseBtn;
	CButton* m_pValidateBtn;

private:
	CRightWorkerWinDoc* m_Document;

	// Operations
public:

	// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	virtual void OnUpdate(CView*, LPARAM, CObject*);

	void ParseText();
	void Validate();
	void OnTextChange();

	void UpdateDocument(const CString&);
	void UpdateButtonsState(const bool&);
	void InitDocumentData();

	void Ex1();
	void Ex2();
	void Ex3();
	void Ex4();
	void Ex5();

protected:

	// Implementation
public:
	virtual ~CRightWorkerWinView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	void InitUIItems();
	void DestroyUIItems();

	// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in RightWorkerWinView.cpp
inline CRightWorkerWinDoc* CRightWorkerWinView::GetDocument() const
{
	return reinterpret_cast<CRightWorkerWinDoc*>(m_pDocument);
}
#endif

