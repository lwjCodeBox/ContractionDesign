
// ContractionDesign.cpp: 애플리케이션에 대한 클래스 동작을 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "ContractionDesign.h"
#include "ContractionDesignDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CContractionDesignApp

BEGIN_MESSAGE_MAP(CContractionDesignApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CContractionDesignApp 생성

CContractionDesignApp::CContractionDesignApp()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
}


// 유일한 CContractionDesignApp 개체입니다.

CContractionDesignApp theApp;


// CContractionDesignApp 초기화

BOOL CContractionDesignApp::InitInstance()
{
	CWinApp::InitInstance();

	CContractionDesignDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();
	
	return FALSE;
}

