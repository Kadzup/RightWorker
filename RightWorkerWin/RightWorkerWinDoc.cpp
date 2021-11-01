
// RightWorkerWinDoc.cpp : implementation of the CRightWorkerWinDoc class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "RightWorkerWin.h"
#endif

#include "RightWorkerWinDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CRightWorkerWinDoc

IMPLEMENT_DYNCREATE(CRightWorkerWinDoc, CDocument)

BEGIN_MESSAGE_MAP(CRightWorkerWinDoc, CDocument)
	//ON_COMMAND(ID_FILE_SAVE, SaveDocument)
END_MESSAGE_MAP()


// CRightWorkerWinDoc construction/destruction

CRightWorkerWinDoc::CRightWorkerWinDoc() noexcept
{
	// TODO: add one-time construction code here

}

CRightWorkerWinDoc::~CRightWorkerWinDoc()
{
}

BOOL CRightWorkerWinDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CRightWorkerWinDoc serialization

void CRightWorkerWinDoc::Serialize(CArchive& ar)
{
	// save
	if (ar.IsStoring())
	{
		ar << m_sBody;
	}
	// load
	else
	{
		ar >> m_sBody;
	}
}

/*BOOL CRightWorkerWinDoc::DoSave(LPCTSTR lpszPathName, BOOL bReplace)
{
	CFileDialog fd(bReplace);

	fd.m_ofn.lpstrFilter = _T("RightWorker Files(*.rwk)\0*.rwk\0\0");
	fd.m_ofn.lpstrDefExt = _T("rwk");
	fd.m_ofn.lpstrTitle = _T("Save as RightWorker");

	if (fd.DoModal() == IDOK)
	{
		Serialize();
	}

	return TRUE;
}*/

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CRightWorkerWinDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CRightWorkerWinDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CRightWorkerWinDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CRightWorkerWinDoc diagnostics

#ifdef _DEBUG
void CRightWorkerWinDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CRightWorkerWinDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CRightWorkerWinDoc commands
