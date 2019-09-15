
// SudokuView.h : interface of the CSudokuView class
//

#pragma once


class CSudokuView : public CView
{
protected: // create from serialization only
	CSudokuView() noexcept;
	DECLARE_DYNCREATE(CSudokuView)

// Attributes
public:
	CSudokuDoc* GetDocument() const;
	
	int widthRect;
	int hightRect;

	COLORREF yell;
	COLORREF green;
	COLORREF m_color;

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
	/*afx_msg void OnBnClicked1();
	afx_msg void OnBnClicked2();
	afx_msg void OnBnClicked3();
	afx_msg void OnBnClicked4();
	afx_msg void OnBnClicked5();
	afx_msg void OnBnClicked6();
	afx_msg void OnBnClicked7();
	afx_msg void OnBnClicked8();
	afx_msg void OnBnClicked9();*/
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
private:
	CButton button_1;
	CButton button_2;
	CButton button_3;
	CButton button_4;
	CButton button_5;
	CButton button_6;
	CButton button_7;
	CButton button_8;
	CButton button_9;
};

#ifndef _DEBUG  // debug version in SudokuView.cpp
inline CSudokuDoc* CSudokuView::GetDocument() const
   { return reinterpret_cast<CSudokuDoc*>(m_pDocument); }
#endif

