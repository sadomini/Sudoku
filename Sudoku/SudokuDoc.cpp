
// SudokuDoc.cpp : implementation of the CSudokuDoc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Sudoku.h"
#endif

#include "SudokuDoc.h"
#include "SudokuView.h"
#include <propkey.h>
#include<vector>
#include<array>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
using namespace std;
// CSudokuDoc

IMPLEMENT_DYNCREATE(CSudokuDoc, CDocument)

BEGIN_MESSAGE_MAP(CSudokuDoc, CDocument)
END_MESSAGE_MAP()


// CSudokuDoc construction/destruction

CSudokuDoc::CSudokuDoc() noexcept
{
	// TODO: add one-time construction code here
	vector <vector < int> > psekcija(9, vector <int>(9));
	vector <vector <int> > npredlozak(9, vector <int>(9));
	sekcija = psekcija;
	predlozak = npredlozak;
	tezinaIgre = 5;
	izradaSekcije();
	izradaPredloska();
	randomKolona();
	zamjenaKolRed();
	randomRed();
	postaviZaIgru();
}

CSudokuDoc::~CSudokuDoc()
{
	
}

BOOL CSudokuDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CSudokuDoc serialization

void CSudokuDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CSudokuDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CSudokuDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CSudokuDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CSudokuDoc diagnostics

#ifdef _DEBUG
void CSudokuDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSudokuDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CSudokuDoc commands
void CSudokuDoc::izradaSekcije() {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {

			if (i / 3 == 0)
				sekcija[i][j] = i / 3 + j / 3 + 1;
			if (i / 3 == 1)
				sekcija[i][j] = i / 3 + j / 3 + 3;
			if (i / 3 == 2)
				sekcija[i][j] = i / 3 + j / 3 + 5;
		}
	}
}
void CSudokuDoc::izradaPredloska() {

	array<int, 9>arr;
	for (int i = 0; i != 9; i++)
		arr[i] = i + 1;

	copy(arr.begin(), arr.end(), predlozak[0].begin());
	   
	for (int i = 1, k = 3; i < 9; i++) {
		if (i % 3 == 0)
			rotate_copy(predlozak[i - 1].begin(), predlozak[i - 1].begin() + k - 1, predlozak[i - 1].end(), predlozak[i].begin());
		else
			rotate_copy(predlozak[i - 1].begin(), predlozak[i - 1].begin() + k, predlozak[i - 1].end(), predlozak[i].begin());
	}
}
bool CSudokuDoc::provjeraSekcije(int i, int ir, int is) {
	int index_1 = sekcija[i][ir];
	int index_2 = sekcija[i][is];
	int index_1red = sekcija[ir][i];
	int index_2red = sekcija[is][i];

	if (index_1 == index_2)
		return true;
	if (index_1red == index_2red)
		return true;
	return false;
}

void CSudokuDoc::randomKolona() {
	srand(time(NULL));

	int brojObrtaja = 10;
	for (int p = 0; p < brojObrtaja; p++) {
		int kolona_1 = rand() % 9;
		int kolona_2 = rand() % 9;


		if (kolona_1 == kolona_2)
			continue;
		if (sekcija[0][kolona_1] == sekcija[0][kolona_2]) {
			for (int i = 0; i < 9; i++)
				swap(predlozak[i][kolona_1], predlozak[i][kolona_2]);
		}
	}
}
void CSudokuDoc::zamjenaKolRed() {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (j <= i)
				continue;
			swap(predlozak[i][j], predlozak[j][i]);
		}
	}
}
void CSudokuDoc::randomRed() {

	int brojObrtaja = 10;
	for (int p = 0; p < brojObrtaja; p++) {
		int red_1 = rand() % 9;
		int red_2 = rand() % 9;
		
		if (red_1 == red_2)
			continue;
		if (sekcija[red_1][0] == sekcija[red_2][0])
			swap_ranges(predlozak[red_1].begin(), predlozak[red_1].end(), predlozak[red_2].begin());


	}
}
void CSudokuDoc::postaviZaIgru() {

	for (int i = 0; i < 9; i++) {
		int k = 0;

		if (i / 3 == 0) {
			do {
				replace(predlozak[i].begin(), predlozak[i].end(), predlozak[i][rand() % 9], 0);
			} while (++k < tezinaIgre);
		}
		if (i / 3 == 1) {
			do {
				replace(predlozak[i].begin(), predlozak[i].end(), predlozak[i][rand() % 9], 0);
			} while (++k < tezinaIgre);
		}
		if (i / 3 == 2) {
			do {
				replace(predlozak[i].begin(), predlozak[i].end(), predlozak[i][rand() % 9], 0);
			} while (++k < tezinaIgre);
		}
	}
}
int CSudokuDoc::getIndex(int i, int j) {
	return sekcija[i][j];
}
