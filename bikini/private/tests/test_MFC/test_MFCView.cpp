// test_MFCView.cpp : implementation of the Ctest_MFCView class
//

#include "stdafx.h"
#include "test_MFC.h"

#include "test_MFCDoc.h"
#include "test_MFCView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Ctest_MFCView

IMPLEMENT_DYNCREATE(Ctest_MFCView, CView)

BEGIN_MESSAGE_MAP(Ctest_MFCView, CView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()

// Ctest_MFCView construction/destruction

Ctest_MFCView::Ctest_MFCView() :
	m_update_task(*this, &Ctest_MFCView::update)
{
	// TODO: add construction code here

}

Ctest_MFCView::~Ctest_MFCView()
{
}

BOOL Ctest_MFCView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// Ctest_MFCView drawing

void Ctest_MFCView::OnDraw(CDC* /*pDC*/)
{
	Ctest_MFCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// Ctest_MFCView diagnostics

#ifdef _DEBUG
void Ctest_MFCView::AssertValid() const
{
	CView::AssertValid();
}

void Ctest_MFCView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

Ctest_MFCDoc* Ctest_MFCView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Ctest_MFCDoc)));
	return (Ctest_MFCDoc*)m_pDocument;
}
#endif //_DEBUG


// Ctest_MFCView message handlers

int Ctest_MFCView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	if(!m_window.create(m_hWnd)) return -1;
	if(!m_video.create()) return -1;

	return 0;
}

void Ctest_MFCView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	if(cx > 0 && cy > 0) {
		if(&m_video.get_device() == 0) {
			m_video.activate(m_hWnd);
			m_run = true;
			m_update_task.run();
		} else {
			m_update_section.enter();
			m_video.reset();
			m_update_section.leave();
		}
	}
}

void Ctest_MFCView::OnDestroy()
{
	CView::OnDestroy();

	// TODO: Add your message handler code here
	m_run = false;
	m_update_task.wait();
	m_video.destroy();
}

void Ctest_MFCView::update() {
	bk::ticker l_ticker(1.f / 30.f);
	while(m_run) {
		m_update_section.enter();
		m_video.begin_scene();
		m_video.clear_viewport();
		m_video.end_scene();
		m_video.present();
		m_update_section.leave();
		l_ticker.sync();
	}
}
