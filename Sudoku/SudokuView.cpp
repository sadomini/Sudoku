
// SudokuView.cpp : implementation of the CSudokuView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Sudoku.h"
#endif

#include "SudokuDoc.h"
#include "SudokuView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSudokuView

IMPLEMENT_DYNCREATE(CSudokuView, CView)

BEGIN_MESSAGE_MAP(CSudokuView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CSudokuView construction/destruction

CSudokuView::CSudokuView() noexcept
{
	// TODO: add construction code here

}

CSudokuView::~CSudokuView()
{
}

BOOL CSudokuView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CSudokuView drawing

void CSudokuView::OnDraw(CDC* /*pDC*/)
{
	CSudokuDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}

void CSudokuView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CSudokuView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CSudokuView diagnostics

#ifdef _DEBUG
void CSudokuView::AssertValid() const
{
	CView::AssertValid();
}

void CSudokuView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSudokuDoc* CSudokuView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSudokuDoc)));
	return (CSudokuDoc*)m_pDocument;
}
#endif //_DEBUG


// CSudokuView message handlers
