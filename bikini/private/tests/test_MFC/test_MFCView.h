// test_MFCView.h : interface of the Ctest_MFCView class
//


#pragma once


class Ctest_MFCView : public CView
{
protected: // create from serialization only
	Ctest_MFCView();
	DECLARE_DYNCREATE(Ctest_MFCView)

// Attributes
public:
	Ctest_MFCDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~Ctest_MFCView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// bikini-iii
private:
	bk::window m_window;
	bk::video m_video;
	bool m_run;
	bk::thread::task m_update_task;
	bk::thread::section m_update_section;
	void update();

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
public:
	afx_msg void OnDestroy();
};

#ifndef _DEBUG  // debug version in test_MFCView.cpp
inline Ctest_MFCDoc* Ctest_MFCView::GetDocument() const
   { return reinterpret_cast<Ctest_MFCDoc*>(m_pDocument); }
#endif

