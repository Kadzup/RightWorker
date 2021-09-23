
// RightWorkerMFCDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "RightWorkerMFC.h"
#include "RightWorkerMFCDlg.h"
#include "afxdialogex.h"
#include <fstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRightWorkerMFCDlg dialog



CRightWorkerMFCDlg::CRightWorkerMFCDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_RIGHTWORKERMFC_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRightWorkerMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

void CRightWorkerMFCDlg::Example()
{
	auto text = L"S: ab | aC\r\nC: abba | e";
	
	CEdit* inputField = (CEdit*)GetDlgItem(IDC_EDIT2);
	
	inputField->SetWindowText(text);

	GetDlgItem(IDC_BUTTON2)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON3)->EnableWindow(TRUE);
	GetDlgItem(IDC_LIST2)->EnableWindow(TRUE);
}

void CRightWorkerMFCDlg::OpenFile()
{
	const TCHAR szFilter[] = _T("Text Files (*.txt)|*.txt|All Files (*.*)|*.*||");
	CFileDialog dlg(FALSE, _T("txt"), NULL, OFN_HIDEREADONLY, szFilter, this);
	if (dlg.DoModal() == IDOK)
	{
		CString sFilePath = dlg.GetPathName();
		std::ifstream inFile(sFilePath);

		if (!inFile.is_open())
		{
			return;
		}

		std::string line;
		std::string baseTemp;

		while (std::getline(inFile, line))
		{
			baseTemp += line + "\r\n";
		}

		inFile.close();

		if(baseTemp.empty())
		{
			GetDlgItem(IDC_BUTTON2)->EnableWindow(FALSE);
			GetDlgItem(IDC_BUTTON3)->EnableWindow(FALSE);
			GetDlgItem(IDC_LIST2)->EnableWindow(FALSE);
		}else
		{
			CEdit* inputField = (CEdit*)GetDlgItem(IDC_EDIT2);

			std::wstring stemp = std::wstring(baseTemp.begin(), baseTemp.end());
			LPCWSTR sw = stemp.c_str();
			
			inputField->SetWindowText(sw);
			
			GetDlgItem(IDC_BUTTON2)->EnableWindow(TRUE);
			GetDlgItem(IDC_BUTTON3)->EnableWindow(TRUE);
			GetDlgItem(IDC_LIST2)->EnableWindow(TRUE);

		}
	}
}

void CRightWorkerMFCDlg::Parse()
{
	Refresh();
	
	CListBox* m_ListBox = (CListBox*)GetDlgItem(IDC_LIST2);

	auto list =	mpRightWorker->ToList();

	m_ListBox->ResetContent();
	
	for(auto item : list)
	{
		CString  itemStr(item.c_str());
		m_ListBox->AddString(itemStr);
	}
	
}

void CRightWorkerMFCDlg::Refresh()
{
	delete mpRightWorker;
	mpRightWorker = new RightWorker();

	CEdit* inputField = (CEdit*)GetDlgItem(IDC_EDIT2);
	CString text;
	inputField->GetWindowTextW(text);

	CT2CA pszConvertedAnsiString(text);
	// construct a std::string using the LPCSTR input
	std::string strStd(pszConvertedAnsiString);

	mpRightWorker->SetBase(strStd);
	mpRightWorker->Convert();
}


void CRightWorkerMFCDlg::Validate()
{
	Refresh();

	if (mpRightWorker->IsValid()) {
		MessageBox(L"This grammar is valid", L"Grammar validation");
	}
	else {
		MessageBox(L"This grammar is not valid (not right-regular grammar)", L"Grammar validation");
	}
}

void CRightWorkerMFCDlg::OnChange()
{
	CEdit* inputField = (CEdit*)GetDlgItem(IDC_EDIT2);
	CString text;
	inputField->GetWindowTextW(text);

	// disable controls
	if(text.IsEmpty())
	{
		GetDlgItem(IDC_BUTTON2)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON3)->EnableWindow(FALSE);
		GetDlgItem(IDC_LIST2)->EnableWindow(FALSE);
	}
	// enable controls
	else{
		GetDlgItem(IDC_BUTTON2)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON3)->EnableWindow(TRUE);
		GetDlgItem(IDC_LIST2)->EnableWindow(TRUE);
	}
}

BEGIN_MESSAGE_MAP(CRightWorkerMFCDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OpenFile)
	ON_BN_CLICKED(IDC_BUTTON2, Parse)
	ON_BN_CLICKED(IDC_BUTTON3, Validate)
	ON_BN_CLICKED(IDC_BUTTON4, Example)
	ON_EN_CHANGE(IDC_EDIT2, OnChange)
END_MESSAGE_MAP()


// CRightWorkerMFCDlg message handlers

BOOL CRightWorkerMFCDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	// mpRightWorker = new RightWorker();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CRightWorkerMFCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CRightWorkerMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

