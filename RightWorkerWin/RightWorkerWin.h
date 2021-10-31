
// RightWorkerWin.h : main header file for the RightWorkerWin application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CRightWorkerWinApp:
// See RightWorkerWin.cpp for the implementation of this class
//

class CRightWorkerWinApp : public CWinApp
{
public:
	CRightWorkerWinApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CRightWorkerWinApp theApp;
