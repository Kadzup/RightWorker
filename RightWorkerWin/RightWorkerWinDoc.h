
// RightWorkerWinDoc.h : interface of the CRightWorkerWinDoc class
//


#pragma once
#include <string>


class CRightWorkerWinDoc : public CDocument
{
protected: // create from serialization only
	CRightWorkerWinDoc() noexcept;
	DECLARE_DYNCREATE(CRightWorkerWinDoc)

// Attributes
public:
	CString m_sBody;

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//virtual BOOL DoSave(LPCTSTR lpszPathName, BOOL bReplace);

#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CRightWorkerWinDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
