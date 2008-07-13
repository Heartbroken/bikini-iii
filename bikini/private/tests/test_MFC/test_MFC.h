// test_MFC.h : main header file for the test_MFC application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// Ctest_MFCApp:
// See test_MFC.cpp for the implementation of this class
//

class Ctest_MFCApp : public CWinApp
{
public:
	Ctest_MFCApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern Ctest_MFCApp theApp;