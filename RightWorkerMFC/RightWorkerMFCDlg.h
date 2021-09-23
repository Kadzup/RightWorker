
// RightWorkerMFCDlg.h : header file
//

#pragma once
#include <RightWorker.h>

// CRightWorkerMFCDlg dialog
class CRightWorkerMFCDlg : public CDialog
{
// Construction
public:
	CRightWorkerMFCDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RIGHTWORKERMFC_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

public:
	RightWorker* mpRightWorker;

	void Example();
	void OpenFile();
	void Parse();
	void Validate();
	void OnChange();
	void Refresh();
	
// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};
