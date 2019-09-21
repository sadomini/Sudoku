
// SudokuView.h : interface of the CSudokuView class
//

#pragma once
#include <vector>
#include<algorithm>
#include<iterator>
using namespace std;

class CSudokuView : public CView
{
protected: // create from serialization only
	CSudokuView() noexcept;
	DECLARE_DYNCREATE(CSudokuView)

// Attributes
public:
	CSudokuDoc* GetDocument() const;
private:
	CPoint position;
	vector <CRect> vm_colorRect;
	int widthRect;
	int hightRect;

	COLORREF yell;
	COLORREF green;
	COLORREF m_color;
	CRect m_redRect;
	CRect m_rect;


// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CSudokuView();
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
public:
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	
private:
	
public:
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
};

#ifndef _DEBUG  // debug version in SudokuView.cpp
inline CSudokuDoc* CSudokuView::GetDocument() const
   { return reinterpret_cast<CSudokuDoc*>(m_pDocument); }
#endif

