
// SudokuDoc.h : interface of the CSudokuDoc class
//


#pragma once
#include<vector>	
#include<algorithm>


class CSudokuDoc : public CDocument
{
protected: // create from serialization only
	CSudokuDoc() noexcept;
	DECLARE_DYNCREATE(CSudokuDoc)

// Attributes
private:
	std::vector <std::vector <int> >sekcija;
	
	int tezinaIgre;
public:
	std::vector <std::vector <int> >predlozak;

// Operations
private:
	bool provjeraSekcije(int i, int ir, int is);
	void izradaSekcije();
	void randomKolona();
	void zamjenaKolRed();
	void randomRed();
	void postaviZaIgru();
	void izradaPredloska();

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CSudokuDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
