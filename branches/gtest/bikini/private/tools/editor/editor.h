
// editor.h : main header file for the editor application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CEditorApp:
// See editor.cpp for the implementation of this class
//

class CEditorApp : public CWinAppEx
{
public:
	CEditorApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual BOOL OnIdle(LONG lCount);

// Implementation
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()

// bikini
public:
	bk::video& get_video();

private:
	bk::video m_video;
	bk::real m_time;
	bk::ticker m_ticker;
};

extern CEditorApp theApp;
