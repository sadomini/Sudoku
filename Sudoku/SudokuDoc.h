
#pragma once




class CSudokuDoc : public CDocument
{
protected: 
	CSudokuDoc() noexcept;
	DECLARE_DYNCREATE(CSudokuDoc)

// Attributes
private:
	std::vector <std::vector <int> >sekcija;
	std::vector <std::vector <int> >predlozak;
	std::vector <std::vector <int> >posjeta;
	int tezinaIgre;
	
public:

	std::vector< CPoint>neispravni;


private:
	void izradaSekcije();
	void randomKolona();
	void zamjenaKolRed();
	void randomRed();
	void postaviZaIgru();
	void brojPosjeta();
	void izradaPredloska();
	bool provjeraReda(CPoint a, int b);
	bool provjeraKolone(CPoint a, int b);
	bool provjeraSekcije(CPoint a, int b);
	void generiranje();
public:
	int getIndex(int i, int j);
	bool IsCorrectNumber(CPoint a, int b);
	int dohvatiVrijednost(int i, int j);
	void postaviTezinu(int tezina);
	bool IsFull();


public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif 

public:
	virtual ~CSudokuDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:


protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif
public:
	void SetNumber(int number, int i, int j);
	bool zaZamjenu(int i, int j);
};
