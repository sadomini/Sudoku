
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

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CSudokuDoc

IMPLEMENT_DYNCREATE(CSudokuDoc, CDocument)

BEGIN_MESSAGE_MAP(CSudokuDoc, CDocument)
END_MESSAGE_MAP()


// CSudokuDoc construction/destruction

CSudokuDoc::CSudokuDoc() noexcept
{
	// TODO: add one-time construction code here
	tezinaIgre =10;
	sekcija = new int*[9];
	predlozak = new int*[9];

	for (int i = 0; i < 9; i++) {
		sekcija[i] = new int[9];
		predlozak[i] = new int[9];
	}
	izradaPredloska();
	izradaSekcije();
	randomKolona();
	zamjenaKolRed();
	randomRed();
	postaviZaIgru();
}

CSudokuDoc::~CSudokuDoc()
{
	for (int i = 0; i < 9; i++) {
		delete[] sekcija[i];
		delete[] predlozak[i];
	}
	delete[] sekcija;
	delete[] predlozak;
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

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			int var[2][3];

			if (i / 3 == 0) {
				if (3 * i + j + 1 < 10)
					predlozak[i][j] = 3 * i + j + 1;
				else
					predlozak[i][j] = 3 * i + j - 8;
				var[0][i] = predlozak[i][8];
			}
			if (i / 3 == 1) {
				if (j + var[0][i % 3] < 10)
					predlozak[i][j] = j + var[0][i % 3];
				else
					predlozak[i][j] = j + var[0][i % 3] - 9;
				var[1][i % 3] = predlozak[i][8];
			}
			if (i / 3 == 2) {
				if (j + var[1][i % 3] < 10)
					predlozak[i][j] = j + var[1][i % 3];
				else
					predlozak[i][j] = j + var[1][i % 3] - 9;
			}
		}
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
	int brojObrtaja = 100;
	for (int p = 0; p < brojObrtaja; p++) {
		int kolona_1 = rand() % 9;
		int kolona_2 = rand() % 9;

		if (kolona_1 == kolona_2)
			continue;
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				if (provjeraSekcije(i, kolona_1, kolona_2) && provjeraSekcije(i, kolona_2, kolona_1)) {
					predlozak[i][kolona_1] += predlozak[i][kolona_2];
					predlozak[i][kolona_2] = predlozak[i][kolona_1] - predlozak[i][kolona_2];
					predlozak[i][kolona_1] -= predlozak[i][kolona_2];
				}
				else break;
			}
		}
	}
}
void CSudokuDoc::zamjenaKolRed() {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (j <= i)
				continue;
			predlozak[i][j] += predlozak[j][i];
			predlozak[j][i] = predlozak[i][j] - predlozak[j][i];
			predlozak[i][j] -= predlozak[j][i];
		}
	}
}
void CSudokuDoc::randomRed() {

	int brojObrtaja = 100;
	for (int p = 0; p < brojObrtaja; p++) {
		int red_1 = rand() % 9;
		int red_2 = rand() % 9;

		if (red_1 == red_2)
			continue;
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				if (provjeraSekcije(j, red_1, red_2) && provjeraSekcije(j, red_2, red_1)) {
					predlozak[red_1][j] += predlozak[red_2][j];
					predlozak[red_2][j] = predlozak[red_1][j] - predlozak[red_2][j];
					predlozak[red_1][j] -= predlozak[red_2][j];
				}
				else break;
			}
		}
	}
}
void CSudokuDoc::postaviZaIgru() {

	for (int i = 0; i < 9; i++) {
		int k = 0;

		if (i / 3 == 0) {
			do {

				int jr = rand() % 9;
				predlozak[i][jr] = 0;
			} while (++k < tezinaIgre);
		}
		if (i / 3 == 1) {
			do {
				int jr = rand() % 9;
				predlozak[i][jr] = 0;
			} while (++k < tezinaIgre);
		}
		if (i / 3 == 2) {
			do {
				int jr = rand() % 9;
				predlozak[i][jr] = 0;
			} while (++k < tezinaIgre);
		}
	}
}
