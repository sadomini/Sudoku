
#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "Sudoku.h"
#include "MainFrm.h"

#include "SudokuDoc.h"
#include "SudokuView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


BEGIN_MESSAGE_MAP(CSudokuApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CSudokuApp::OnAppAbout)
	
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
END_MESSAGE_MAP()



CSudokuApp::CSudokuApp() noexcept
{
	m_bHiColorIcons = TRUE;


	SetAppID(_T("Sudoku.AppID.NoVersion"));

	
}


CSudokuApp theApp;




BOOL CSudokuApp::InitInstance()
{
	CWinAppEx::InitInstance();


	EnableTaskbarInteraction(FALSE);

	
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	LoadStdProfileSettings(4); 


	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CSudokuDoc),
		RUNTIME_CLASS(CMainFrame),       
		RUNTIME_CLASS(CSudokuView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);


	
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	
	m_pMainWnd->DragAcceptFiles();
	return TRUE;
}



class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg() noexcept;


#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);   


protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() noexcept : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


void CSudokuApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}



void CSudokuApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
}

void CSudokuApp::LoadCustomState()
{
}

void CSudokuApp::SaveCustomState()
{
}





