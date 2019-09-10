
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
};

#ifndef _DEBUG  // debug version in SudokuView.cpp
inline CSudokuDoc* CSudokuView::GetDocument() const
   { return reinterpret_cast<CSudokuDoc*>(m_pDocument); }
#endif

