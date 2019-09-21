
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
	
	ON_COMMAND(ID_TB_BUTTON1, &CSudokuView::OnTbButton1)
	ON_COMMAND(ID_TB_BUTTON2, &CSudokuView::OnTbButton2)
	ON_COMMAND(ID_TB_BUTTON3, &CSudokuView::OnTbButton3)
	ON_COMMAND(ID_TB_BUTTON4, &CSudokuView::OnTbButton4)
	ON_COMMAND(ID_TB_BUTTON5, &CSudokuView::OnTbButton5)
	ON_COMMAND(ID_TB_BUTTON6, &CSudokuView::OnTbButton6)
	ON_COMMAND(ID_TB_BUTTON7, &CSudokuView::OnTbButton7)
	ON_COMMAND(ID_TB_BUTTON8, &CSudokuView::OnTbButton8)
	ON_COMMAND(ID_TB_BUTTON9, &CSudokuView::OnTbButton9)
	ON_COMMAND(ID_TB_BUTTONX, &CSudokuView::OnTbButtonx)
END_MESSAGE_MAP()

// CSudokuView construction/destruction

CSudokuView::CSudokuView() noexcept
{	
	position.SetPoint(-1, -1);
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
	CBrush m_colorbrush;
	m_colorbrush.CreateSolidBrush(RGB(255, 102, 102));

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
			for (int z = 0; z < vm_colorRect.size(); z++) {
				if (miniRect.EqualRect(vm_colorRect[z])) {

					pDC->FillRect(miniRect, &m_colorbrush);
					pDC->FrameRect(miniRect, &brushGray);
				}
			}
			pDC->SetBkMode(TRANSPARENT);

			CString string;
			if (pDoc->dohvatiVrijednost(i, j) == 0)
				string.Format(_T(" "), pDoc->dohvatiVrijednost(i, j));
			else
				string.Format(_T("%d "), pDoc->dohvatiVrijednost(i, j));
			if (pDoc->zaZamjenu(i, j)) {
				pDC->SetTextColor(RGB(0, 0, 255));
				pDC->DrawText(string, -1, &miniRect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			}
			else {
				pDC->SetTextColor(RGB(0, 0, 0));
				pDC->DrawText(string, -1, &miniRect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			}
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
	if (!(pDoc->zaZamjenu(i, j)) && (pDoc->dohvatiVrijednost(i, j) != 0))
		return;
	if (!vm_colorRect.empty())
		return;
	position.x = i;
	position.y = j;

	int x1 = widthRect * (j + 1);
	int y1 = hightRect * (i + 2);
	int x2 = x1 + widthRect;
	int y2 = y1 + hightRect;

	m_rect.SetRect(x1, y1, x2, y2);

	Invalidate();

	CView::OnLButtonUp(nFlags, point);
}





void CSudokuView::OnTbButton1()
{
	CSudokuDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if (position.x < 0 && position.y < 0)
		return;
	if (pDoc->dohvatiVrijednost(position.x, position.y) != 0)
		return;
	vm_colorRect.erase(vm_colorRect.begin(), vm_colorRect.end());
	int number = 1;

	if (!pDoc->IsCorrectNumber(position, number)) {
		for (int i = 0; i != pDoc->neispravni.size(); i++) {
			for (int j = 0; j != 2; j++) {
				CPoint širina(widthRect *(pDoc->neispravni[i].y + 1), hightRect * (pDoc->neispravni[i].x + 2));
				CPoint visina(širina.x + widthRect, širina.y + hightRect);
				CRect m_redRect(širina, visina);
				vm_colorRect.push_back(m_redRect);
			}
		}
	}
	Invalidate();
}


void CSudokuView::OnTbButton2()
{
	CSudokuDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if (position.x < 0 && position.y < 0)
		return;
	if (pDoc->dohvatiVrijednost(position.x, position.y) != 0)
		return;
	vm_colorRect.erase(vm_colorRect.begin(), vm_colorRect.end());
	int number = 2;

	if (!pDoc->IsCorrectNumber(position, number)) {
		for (int i = 0; i != pDoc->neispravni.size(); i++) {
			for (int j = 0; j != 2; j++) {
				CPoint širina(widthRect *(pDoc->neispravni[i].y + 1), hightRect * (pDoc->neispravni[i].x + 2));
				CPoint visina(širina.x + widthRect, širina.y + hightRect);
				CRect m_redRect(širina, visina);
				vm_colorRect.push_back(m_redRect);
			}
		}
	}
	Invalidate();
}


void CSudokuView::OnTbButton3()
{
	CSudokuDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if (position.x < 0 && position.y < 0)
		return;
	if (pDoc->dohvatiVrijednost(position.x, position.y) != 0)
		return;
	vm_colorRect.erase(vm_colorRect.begin(), vm_colorRect.end());
	int number = 3;

	if (!pDoc->IsCorrectNumber(position, number)) {
		for (int i = 0; i != pDoc->neispravni.size(); i++) {
			for (int j = 0; j != 2; j++) {
				CPoint širina(widthRect *(pDoc->neispravni[i].y + 1), hightRect * (pDoc->neispravni[i].x + 2));
				CPoint visina(širina.x + widthRect, širina.y + hightRect);
				CRect m_redRect(širina, visina);
				vm_colorRect.push_back(m_redRect);
			}
		}
	}
	Invalidate();
}


void CSudokuView::OnTbButton4()
{
	CSudokuDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if (position.x < 0 && position.y < 0)
		return;
	if (pDoc->dohvatiVrijednost(position.x, position.y) != 0)
		return;
	vm_colorRect.erase(vm_colorRect.begin(), vm_colorRect.end());
	int number = 4;

	if (!pDoc->IsCorrectNumber(position, number)) {
		for (int i = 0; i != pDoc->neispravni.size(); i++) {
			for (int j = 0; j != 2; j++) {
				CPoint širina(widthRect *(pDoc->neispravni[i].y + 1), hightRect * (pDoc->neispravni[i].x + 2));
				CPoint visina(širina.x + widthRect, širina.y + hightRect);
				CRect m_redRect(širina, visina);
				vm_colorRect.push_back(m_redRect);
			}
		}
	}
	Invalidate();
}


void CSudokuView::OnTbButton5()
{
	CSudokuDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if (position.x < 0 && position.y < 0)
		return;
	if (pDoc->dohvatiVrijednost(position.x, position.y) != 0)
		return;
	vm_colorRect.erase(vm_colorRect.begin(), vm_colorRect.end());
	int number = 5;

	if (!pDoc->IsCorrectNumber(position, number)) {
		for (int i = 0; i != pDoc->neispravni.size(); i++) {
			for (int j = 0; j != 2; j++) {
				CPoint širina(widthRect *(pDoc->neispravni[i].y + 1), hightRect * (pDoc->neispravni[i].x + 2));
				CPoint visina(širina.x + widthRect, širina.y + hightRect);
				CRect m_redRect(širina, visina);
				vm_colorRect.push_back(m_redRect);
			}
		}
	}
	Invalidate();
}


void CSudokuView::OnTbButton6()
{
	CSudokuDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if (position.x < 0 && position.y < 0)
		return;
	if (pDoc->dohvatiVrijednost(position.x, position.y) != 0)
		return;
	vm_colorRect.erase(vm_colorRect.begin(), vm_colorRect.end());
	int number = 6;

	if (!pDoc->IsCorrectNumber(position, number)) {
		for (int i = 0; i != pDoc->neispravni.size(); i++) {
			for (int j = 0; j != 2; j++) {
				CPoint širina(widthRect *(pDoc->neispravni[i].y + 1), hightRect * (pDoc->neispravni[i].x + 2));
				CPoint visina(širina.x + widthRect, širina.y + hightRect);
				CRect m_redRect(širina, visina);
				vm_colorRect.push_back(m_redRect);
			}
		}
	}
	Invalidate();
}


void CSudokuView::OnTbButton7()
{
	CSudokuDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if (position.x < 0 && position.y < 0)
		return;
	if (pDoc->dohvatiVrijednost(position.x, position.y) != 0)
		return;
	vm_colorRect.erase(vm_colorRect.begin(), vm_colorRect.end());
	int number = 7;

	if (!pDoc->IsCorrectNumber(position, number)) {
		for (int i = 0; i != pDoc->neispravni.size(); i++) {
			for (int j = 0; j != 2; j++) {
				CPoint širina(widthRect *(pDoc->neispravni[i].y + 1), hightRect * (pDoc->neispravni[i].x + 2));
				CPoint visina(širina.x + widthRect, širina.y + hightRect);
				CRect m_redRect(širina, visina);
				vm_colorRect.push_back(m_redRect);
			}
		}
	}
	Invalidate();
}


void CSudokuView::OnTbButton8()
{
	CSudokuDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if (position.x < 0 && position.y < 0)
		return;
	if (pDoc->dohvatiVrijednost(position.x, position.y) != 0)
		return;
	vm_colorRect.erase(vm_colorRect.begin(), vm_colorRect.end());
	int number = 8;

	if (!pDoc->IsCorrectNumber(position, number)) {
		for (int i = 0; i != pDoc->neispravni.size(); i++) {
			for (int j = 0; j != 2; j++) {
				CPoint širina(widthRect *(pDoc->neispravni[i].y + 1), hightRect * (pDoc->neispravni[i].x + 2));
				CPoint visina(širina.x + widthRect, širina.y + hightRect);
				CRect m_redRect(širina, visina);
				vm_colorRect.push_back(m_redRect);
			}
		}
	}
	Invalidate();
}


void CSudokuView::OnTbButton9()
{
	CSudokuDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if (position.x < 0 && position.y < 0)
		return;
	if (pDoc->dohvatiVrijednost(position.x, position.y) != 0)
		return;
	vm_colorRect.erase(vm_colorRect.begin(), vm_colorRect.end());
	int number = 9;

	if (!pDoc->IsCorrectNumber(position, number)) {
		for (int i = 0; i != pDoc->neispravni.size(); i++) {
			for (int j = 0; j != 2; j++) {
				CPoint širina(widthRect *(pDoc->neispravni[i].y + 1), hightRect * (pDoc->neispravni[i].x + 2));
				CPoint visina(širina.x + widthRect, širina.y + hightRect);
				CRect m_redRect(širina, visina);
				vm_colorRect.push_back(m_redRect);
			}
		}
	}
	Invalidate();
}


void CSudokuView::OnTbButtonx()
{
	vm_colorRect.erase(vm_colorRect.begin(), vm_colorRect.end());
	CSudokuDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	if (position.x < 0 && position.y < 0)
		return;
	pDoc->SetNumber(0, position.x, position.y);


	Invalidate();
}
