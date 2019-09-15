
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
	ON_WM_LBUTTONUP()
	ON_WM_CREATE()
	/*ON_BN_CLICKED(IDC_BUTTON1, OnBnClicked1)
	ON_BN_CLICKED(IDC_BUTTON2, OnBnClicked2)
	ON_BN_CLICKED(IDC_BUTTON3, OnBnClicked3)
	ON_BN_CLICKED(IDC_BUTTON4, OnBnClicked4)
	ON_BN_CLICKED(IDC_BUTTON5, OnBnClicked5)
	ON_BN_CLICKED(IDC_BUTTON6, OnBnClicked6)
	ON_BN_CLICKED(IDC_BUTTON7, OnBnClicked7)
	ON_BN_CLICKED(IDC_BUTTON8, OnBnClicked8)
	ON_BN_CLICKED(IDC_BUTTON9, OnBnClicked9)*/
END_MESSAGE_MAP()

// CSudokuView construction/destruction

CSudokuView::CSudokuView() noexcept
{
	// TODO: add construction code here
	yell = RGB(255, 255, 204);
	green = RGB(204, 255, 204);
	m_color = RGB(255, 204, 153);

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
	
	CFont font;
	font.CreatePointFont(160, _T("Times New Roman"));
	CFont *oldFont = pDC->SelectObject(&font);


	CBrush brushYell;
	brushYell.CreateSolidBrush(yell);

	CBrush brushGreen;
	brushGreen.CreateSolidBrush(green);
	CBrush brushGray;
	brushGray.CreateSolidBrush(RGB(153, 153, 102));
	CBrush m_brush;

	m_brush.CreateSolidBrush(m_color);

	CRect rect;
	GetClientRect(&rect);
	widthRect = rect.Width() / 25;
	hightRect = rect.Height() / 12;
	pDC->TextOutW(widthRect, hightRect, _T("Sudoku"));

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {

			int x1 = widthRect * (j + 1);
			int y1 = hightRect * (i + 2);
			int x2 = x1 + widthRect;
			int y2 = y1 + hightRect;

			CRect miniRect(CPoint(x1, y1), CPoint(x2, y2));
			pDC->Rectangle(miniRect);

			if (pDoc->getIndex(i, j) % 2 == 0) {
				pDC->FillRect(miniRect, &brushYell);
				pDC->FrameRect(miniRect, &brushGray);

			}
			if (pDoc->getIndex(i, j) % 2 == 1) {
				pDC->FillRect(miniRect, &brushGreen);
				pDC->FrameRect(miniRect, &brushGray);
			}
			if (miniRect.EqualRect(m_rect)) {
				pDC->FillRect(miniRect, &m_brush);
				pDC->FrameRect(miniRect, &brushGray);
			}

			CString string;
			if (pDoc->predlozak[i][j] == 0)
				string.Format(_T(" "), pDoc->predlozak[i][j]);
			else
				string.Format(_T("%d "), pDoc->predlozak[i][j]);

			pDC->SetBkMode(TRANSPARENT);
			pDC->DrawText(string, -1, &miniRect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			}
			for (int i = 0; i < 4; i++) {
				pDC->MoveTo(widthRect*(3 * i + 1), 2 * (hightRect + 1));
				pDC->LineTo(widthRect*(3 * i + 1), hightRect * 11);
				pDC->MoveTo(widthRect, hightRect*(2 + 3 * i));
				pDC->LineTo(widthRect * 10, hightRect*(2 + 3 * i));
			}
	}
	pDC->UpdateColors();
	DeleteObject(pDC->SelectObject(oldFont));
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


void CSudokuView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CSudokuDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	int i = point.y / hightRect - 2;
	int j = point.x / widthRect - 1;

	if ((i < 0 || i>8) || (j < 0 || j>8))
		return;
	if (pDoc->predlozak[i][j] != 0)
		return;

	int x1 = widthRect * (j + 1);
	int y1 = hightRect * (i + 2);
	int x2 = x1 + widthRect;
	int y2 = y1 + hightRect;

	m_rect.SetRect(x1, y1, x2, y2);
	Invalidate();
	
	CView::OnLButtonUp(nFlags, point);
}


int CSudokuView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	button_1.Create(_T("1"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(700, 100, 745, 147), this, IDC_BUTTON1);
	button_2.Create(_T("2"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(700, 152, 745, 199), this, IDC_BUTTON2);
	button_3.Create(_T("3"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(700, 204, 745, 251), this, IDC_BUTTON3);
	button_4.Create(_T("4"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(700, 256, 745, 303), this, IDC_BUTTON4);
	button_5.Create(_T("5"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(700, 308, 745, 355), this, IDC_BUTTON5);
	button_6.Create(_T("6"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(700, 360, 745, 407), this, IDC_BUTTON6);
	button_7.Create(_T("7"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(700, 415, 745, 462), this, IDC_BUTTON7);
	button_8.Create(_T("8"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(700, 467, 745, 514), this, IDC_BUTTON8);
	button_9.Create(_T("9"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(700, 519, 745, 566), this, IDC_BUTTON9);
	return 0;

	return 0;
}
