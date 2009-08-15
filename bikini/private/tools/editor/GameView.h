
// GameView.h : interface of the CGameView class
//


#pragma once


class CGameView : public CView
{
protected: // create from serialization only
	CGameView();
	DECLARE_DYNCREATE(CGameView)

// Attributes
public:
	CGameDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CGameView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in GameView.cpp
inline CGameDoc* CGameView::GetDocument() const
   { return reinterpret_cast<CGameDoc*>(m_pDocument); }
#endif

