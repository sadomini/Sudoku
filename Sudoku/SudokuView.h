
#pragma once
#include <vector>
#include<algorithm>
#include<iterator>

class CSudokuView : public CView
{
protected: 
	CSudokuView() noexcept;
	DECLARE_DYNCREATE(CSudokuView)


public:
	CSudokuDoc* GetDocument() const;
private:
	CPoint position;
	std::vector <CRect> vm_colorRect;
	int widthRect;
	int hightRect;

	COLORREF yell;
	COLORREF green;
	COLORREF m_color;
	CRect m_redRect;
	CRect m_rect;
public:
	virtual void OnDraw(CDC* pDC);  
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

public:
	virtual ~CSudokuView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnTbButton1();
	afx_msg void OnTbButton2();
	afx_msg void OnTbButton3();
	afx_msg void OnTbButton4();
	afx_msg void OnTbButton5();
	afx_msg void OnTbButton6();
	afx_msg void OnTbButton7();
	afx_msg void OnTbButton8();
	afx_msg void OnTbButton9();
	afx_msg void OnTbButtonx();
	afx_msg void OnBnClicked1();
	afx_msg void OnBnClicked2();
	afx_msg void OnBnClicked3();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	
	DECLARE_MESSAGE_MAP()
public:
	CButton btnEasy;
	CButton btnMedium ;
	CButton btnHard;
	
private:
	void ToolbarButton(int a);
	void buttonTezina(int tzn);
};

#ifndef _DEBUG  
inline CSudokuDoc* CSudokuView::GetDocument() const
   { return reinterpret_cast<CSudokuDoc*>(m_pDocument); }
#endif

