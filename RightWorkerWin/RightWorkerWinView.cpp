
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
	ON_COMMAND(ID_EXAMPLE_EXAMPLE1, &CRightWorkerWinView::Ex1)
	ON_COMMAND(ID_EXAMPLE_EXAMPLE2, &CRightWorkerWinView::Ex2)
	ON_COMMAND(ID_EXAMPLE_EXAMPLE3, &CRightWorkerWinView::Ex3)
	ON_COMMAND(ID_EXAMPLE_EXAMPLE4, &CRightWorkerWinView::Ex4)
	ON_COMMAND(ID_EXAMPLE_EXAMPLE5, &CRightWorkerWinView::Ex5)
	ON_BN_CLICKED(IDC_VALIDATE, Validate)
	ON_BN_CLICKED(IDC_PARSE, ParseText)
	ON_EN_CHANGE(IDC_INPUT_FIELD, OnTextChange)
END_MESSAGE_MAP()

// CRightWorkerWinView construction/destruction

CRightWorkerWinView::CRightWorkerWinView() noexcept
{
	m_pRightWorker = new RightWorker();

	InitUIItems();
}

CRightWorkerWinView::~CRightWorkerWinView()
{
	DestroyUIItems();
}

BOOL CRightWorkerWinView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}

void CRightWorkerWinView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	m_pInputLabel = new CStatic; 
	m_pListLabel = new CStatic;

	m_pInputField = new CEdit;

	m_pParsedList = new CListBox;

	m_pParseBtn = new CButton;
	m_pValidateBtn = new CButton;

	m_pInputLabel->Create(
		_T("Input"), 
		WS_CHILD | WS_VISIBLE, 
		CRect(10, 10, 200, 30), 
		this
	);
	m_pListLabel->Create(
		_T("Parsed"), 
		WS_CHILD | WS_VISIBLE, 
		CRect(220, 10, 420, 30), 
		this
	);

	
	m_pInputField->Create(
		ES_MULTILINE | WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER,
		CRect(10, 30, 200, 250), 
		this, 
		IDC_INPUT_FIELD
	);

	
	m_pParsedList->Create(
		WS_CHILD | WS_VISIBLE | LBS_STANDARD | WS_HSCROLL,
		CRect(220, 30, 420, 250), 
		this, 
		IDC_PARSED_LIST
	);

	m_pParseBtn->Create(
		_T("Parse"), 
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		CRect(440, 10, 520, 42), 
		this, 
		IDC_PARSE
	);

	m_pValidateBtn->Create(
		_T("Validate"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		CRect(440, 55, 520, 87),
		this,
		IDC_VALIDATE
	);
}

void CRightWorkerWinView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	CView::OnUpdate(pSender, lHint, pHint);
}

void CRightWorkerWinView::ParseText()
{
	CString cText;

	m_pInputField->GetWindowTextW(cText);

	CT2CA pszConvertedAnsiString(cText);
	// construct a std::string using the LPCSTR input
	std::string text(pszConvertedAnsiString);

	if (m_pRightWorker == nullptr) {
		m_pRightWorker = new RightWorker(text);
	}
	else {
		m_pRightWorker->SetBase(text);
	}

	m_pRightWorker->Convert();

	std::list<std::string> list = m_pRightWorker->ToList();

	m_pParsedList->ResetContent();

	for (auto item : list)
	{
		CString  itemStr(item.c_str());
		m_pParsedList->AddString(itemStr);
	}
}

void CRightWorkerWinView::Validate()
{
	CString cText;
	CT2CA pszConvertedAnsiString(cText);
	// construct a std::string using the LPCSTR input
	std::string text(pszConvertedAnsiString);

	if (m_pRightWorker == nullptr) {
		m_pRightWorker = new RightWorker(text);
	}
	else {
		m_pRightWorker->SetBase(text);
	}

	if (m_pRightWorker->IsValid()) {
		MessageBox(L"This grammar is valid", L"Grammar validation");
	}
	else {
		MessageBox(L"This grammar is not valid (not right-regular grammar)", L"Grammar validation");
	}
}

void CRightWorkerWinView::OnTextChange()
{
	if (m_pInputField == nullptr) {
		return;
	}

	CString cText;
	m_pInputField->GetWindowTextW(cText);

	UpdateButtonsState(!cText.IsEmpty());

	UpdateDocument(cText);
}

void CRightWorkerWinView::UpdateDocument(const CString& text)
{
	if (m_Document == nullptr) {
		return;
	}

	m_Document->m_sBody = text;
}

void CRightWorkerWinView::UpdateButtonsState(const bool& activate)
{
	if(activate){
		if (m_pParseBtn != nullptr) {
			m_pParseBtn->EnableWindow(TRUE);
		}
		if (m_pValidateBtn != nullptr) {
			m_pValidateBtn->EnableWindow(TRUE);
		}
	}
	else{
		if (m_pParseBtn != nullptr) {
			m_pParseBtn->EnableWindow(FALSE);
		}
		if (m_pValidateBtn != nullptr) {
			m_pValidateBtn->EnableWindow(FALSE);
		}
	}
}

void CRightWorkerWinView::InitDocumentData()
{
	if (m_pInputField != nullptr) {
		CString cText;
		m_pInputField->GetWindowTextW(cText);

		if (cText.IsEmpty() && !m_Document->m_sBody.IsEmpty()) {
			m_pInputField->SetWindowTextW(m_Document->m_sBody);
		}
	}
}

void CRightWorkerWinView::Ex1()
{
	CString example = _T("S: abba | bCa\r\nC: bbb | abKa | abbT\r\nK: abba\r\nT: abbba | e");

	UpdateDocument(example);

	UpdateButtonsState(true);

	m_pInputField->SetWindowTextW(example);
}

void CRightWorkerWinView::Ex2()
{
	CString example = _T("S: aaa | baC\r\nC: bba | e");

	UpdateDocument(example);

	UpdateButtonsState(true);

	m_pInputField->SetWindowTextW(example);
}

void CRightWorkerWinView::Ex3()
{
	CString example = _T("S: kabaC | abak\r\nC: kaka | bak | abH\r\nH: kabak");

	UpdateDocument(example);

	UpdateButtonsState(true);

	m_pInputField->SetWindowTextW(example);
}

void CRightWorkerWinView::Ex4()
{
	CString example = _T("S: ab | abba | aC | e\r\nC: ba | baba | baC");

	UpdateDocument(example);

	UpdateButtonsState(true);

	m_pInputField->SetWindowTextW(example);
}

void CRightWorkerWinView::Ex5()
{
	CString example = _T("S: aaaS | bbaSba | abbC\r\nC: abba | baC | e");

	UpdateDocument(example);

	UpdateButtonsState(true);

	m_pInputField->SetWindowTextW(example);
}

// CRightWorkerWinView drawing

void CRightWorkerWinView::OnDraw(CDC* /*pDC*/)
{
	m_Document = GetDocument();
	ASSERT_VALID(m_Document);
	if (!m_Document)
		return;

	// parse document, if it's not empty
	// check if input field empty
	// if true - and if doc body not empty - set body text
	InitDocumentData();

	UpdateButtonsState(!m_Document->m_sBody.IsEmpty());
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

void CRightWorkerWinView::InitUIItems()
{
	m_pInputField = NULL;
		
		//->Create(_T("Rearrange"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(0, 0, 128, 32), this, 999); // here will create a button
}

void CRightWorkerWinView::DestroyUIItems()
{
	m_pInputField = nullptr;
	m_pParsedList = nullptr;
	m_pInputLabel = nullptr;
	m_pListLabel = nullptr;
}

CRightWorkerWinDoc* CRightWorkerWinView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CRightWorkerWinDoc)));
	return (CRightWorkerWinDoc*)m_pDocument;
}
#endif //_DEBUG


// CRightWorkerWinView message handlers
