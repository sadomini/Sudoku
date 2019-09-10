
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

void CSudokuView::OnDraw(CDC* pDC)
{
	CSudokuDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	
	CRect rect;
	GetClientRect(&rect);
	int  widthRect = rect.Width() / 20;
	int hightRect = rect.Height() / 12;
	pDC->TextOutW(widthRect, hightRect, _T("Sudoku"));

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {

			int x1 = widthRect * (j + 1);
			int y1 = hightRect * (i + 2);
			int x2 = x1 + widthRect;
			int y2 = y1 + hightRect;

			CRect miniRect(CPoint(x1, y1), CPoint(x2, y2));
			pDC->Rectangle(x1, y1, x2, y2);

			CString string;
			if (pDoc->predlozak[i][j] == 0)
				string.Format(_T(" "), pDoc->predlozak[i][j]);
			else
				string.Format(_T("%d "), pDoc->predlozak[i][j]);


			pDC->DrawText(string, -1, &miniRect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		}

	}
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
