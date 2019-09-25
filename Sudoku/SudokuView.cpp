
#include "stdafx.h"

#ifndef SHARED_HANDLERS
#include "Sudoku.h"
#endif

#include "SudokuDoc.h"
#include "SudokuView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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
	ON_BN_CLICKED(IDC_BUTTON_EASY, &CSudokuView::OnBnClicked1)
	ON_BN_CLICKED(IDC_BUTTON_MEDIUM, &CSudokuView::OnBnClicked2)
	ON_BN_CLICKED(IDC_BUTTON_HARD, &CSudokuView::OnBnClicked3)
END_MESSAGE_MAP()



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
	
	return CView::PreCreateWindow(cs);
}

void CSudokuView::OnDraw(CDC* pDC)
{
	CSudokuDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	
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

void CSudokuView::OnLButtonUp(UINT nFlags, CPoint point)
{
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

void CSudokuView::ToolbarButton(int a)
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
	int number = a;

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
	if (pDoc->IsCorrectNumber(position, number) && pDoc->IsFull()) {
		CString string;
		string.LoadStringW(IDS_STRING_SOLVED);
		AfxMessageBox(string);
	}	
}


void CSudokuView::OnTbButton1()
{
	ToolbarButton(1);	
}


void CSudokuView::OnTbButton2()
{
	ToolbarButton(2);	
}


void CSudokuView::OnTbButton3()
{
	ToolbarButton(3);	
}


void CSudokuView::OnTbButton4()
{
	ToolbarButton(4);	
}


void CSudokuView::OnTbButton5()
{
	ToolbarButton(5);
}


void CSudokuView::OnTbButton6()
{
	ToolbarButton(6);	
}


void CSudokuView::OnTbButton7()
{
	ToolbarButton(7);
}


void CSudokuView::OnTbButton8()
{
	ToolbarButton(8);	
}


void CSudokuView::OnTbButton9()
{
	ToolbarButton(9);	
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


int CSudokuView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	CString string1;
	CString string2;
	CString string3;
	string1.LoadStringW(IDS_STRING_EASY);
	string2.LoadStringW(IDS_STRING_MEDIUM);
	string3.LoadStringW(IDS_STRING_HARD);
	btnEasy.Create(string1, WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(700, 200, 850, 250), this,IDC_BUTTON_EASY);
	btnMedium.Create(string2, WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(700, 255, 850, 305), this, IDC_BUTTON_MEDIUM);
	btnHard.Create(string3, WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(700, 310, 850, 360), this, IDC_BUTTON_HARD);

	return 0;
}
void CSudokuView::buttonTezina(int tzn)
{
	vm_colorRect.erase(vm_colorRect.begin(), vm_colorRect.end());
	position.x = -1;
	position.y = -1;
	CSudokuDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	pDoc->postaviTezinu(tzn);
	Invalidate();
}

void CSudokuView::OnBnClicked1() {
	buttonTezina(5);
}

void CSudokuView::OnBnClicked2() {
	buttonTezina(8);
}
void CSudokuView::OnBnClicked3() {
	buttonTezina(11);
}





