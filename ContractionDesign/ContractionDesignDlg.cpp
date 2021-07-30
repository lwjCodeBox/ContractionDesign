
// ContractionDesignDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "ContractionDesign.h"
#include "ContractionDesignDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CContractionDesignDlg 대화 상자



CContractionDesignDlg::CContractionDesignDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CONTRACTIONDESIGN_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CContractionDesignDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EXCEL_SHEET_COMBO, m_sheetName_combo);	
}

BEGIN_MESSAGE_MAP(CContractionDesignDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDCANCEL, &CContractionDesignDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &CContractionDesignDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_FIND_EXCEL_BTN, &CContractionDesignDlg::OnBnClickedFindExcelBtn)
	ON_CBN_SELCHANGE(IDC_EXCEL_SHEET_COMBO, &CContractionDesignDlg::On_ComboChange)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_CELL_CLEAR_EXCEL_BTN, &CContractionDesignDlg::OnBnClickedCellClearExcelBtn)
END_MESSAGE_MAP()


// CContractionDesignDlg 메시지 처리기

BOOL CContractionDesignDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// 버전 정보
	SetDlgItemText(IDC_VERSION_STATIC, L"[Version : 2.0]");

	// 대화상자 배경색 변경
	SetBackgroundColor(RGB(50, 50, 50));

	// 콤보 박스 세팅
	m_sheetName_combo.AddString(L"Cubic");
	m_sheetName_combo.AddString(L"Cosine");
	m_sheetName_combo.AddString(L"Morel");
	m_sheetName_combo.AddString(L"2-Cubic");
	m_sheetName_combo.AddString(L"4th-order");
	m_sheetName_combo.AddString(L"5th-order");
	m_sheetName_combo.SetCurSel(0);
	m_grid_area.m_cur_combo_pos = 0;

	// picture contorl과 그리드 생성 그리고 연결
	m_grid_area.CreateGridArea(IDC_EXCEL_AREA, this, 31000); //IDC_TOOL_BAR_RECT은 picture control의 ID 이름.
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CContractionDesignDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

BOOL CContractionDesignDlg::PreTranslateMessage(MSG *pMsg)
{
	if (pMsg->message == WM_KEYDOWN) {
		//if (pMsg->wParam == VK_ESCAPE)
		//{
		//	return true; // true면 동작을 안먹게 함. false면 동작을 먹게 함.
		//}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

HBRUSH CContractionDesignDlg::OnCtlColor(CDC *pDC, CWnd *pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	if (pWnd->GetDlgCtrlID() == IDC_VERSION_STATIC) {
		// 첫번째 스태틱 컨트롤을 위해 OnCtlColor 함수가 호출된 경우.
		// 스태틱 컨트롤의 텍스트 색상을 설정한다.
		pDC->SetTextColor(RGB(0, 255, 0));
	}
	return hbr;
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CContractionDesignDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CContractionDesignDlg::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnCancel();
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

void CContractionDesignDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//CDialogEx::OnOK();
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

void CContractionDesignDlg::OnBnClickedFindExcelBtn()
{
	wchar_t szFilter[] = L"Excel(*.xlsx, *.xlsm)|*.xlsx;*xlsm|All Files(*.*)|*.*||";

	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, szFilter);
	if (IDOK == dlg.DoModal())
	{
		// 선택 파일정보 얻기
		// strPathName      "C:/Images/Picture1.jpg"
		// strFileName      "Picture1.jpg"
		// strFolderPath    "C:/Images"

		CString strPathName = dlg.GetPathName();
		//CString strFileName = dlg.GetFileName();
		//CString strFolderPath = dlg.GetFolderPath();

		m_excel.ExcelCertified(strPathName);
		Set_combo();
	}
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

void CContractionDesignDlg::Set_combo()
{
	int count = m_excel.Get_Sheet_Count();
	for (int i = 0; i < count; ++i) {
		m_sheetName_combo.AddString(m_excel.GetExcelSheetName(i));
	}

	m_sheetName_combo.SetCurSel(0);
	On_ComboChange();	
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

void CContractionDesignDlg::On_ComboChange()
{
	m_grid_area.m_cur_combo_pos = m_sheetName_combo.GetCurSel();
	m_grid_area.Cell_Clear();
	m_grid_area.Translate_Value(m_grid_area.m_cur_combo_pos);

#if 0 // 엑셀을 읽어오는 버전으로 사용한다면 이 주석을 풀어야 한다.
	CString buf;
	int combo_index = m_sheetName_combo.GetCurSel();
	int len = m_sheetName_combo.GetLBTextLen(combo_index);

	m_sheetName_combo.GetLBText(combo_index, buf.GetBuffer(len));

	if (!Load_Excel_Sheet(buf))
		MessageBox(L"해당 엑셀 시트를 읽어올 수 없습니다.", NULL, MB_ICONERROR);

	buf.ReleaseBuffer();
#endif
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

bool CContractionDesignDlg::Load_Excel_Sheet(CString a_sheetName)
{
	if (m_excel.Get_Sheet(a_sheetName)) {
		const wchar_t *str = NULL;

		int row_start = 1; // (행 시작 위치)
		int row_end = 202;

		int col_start = 0; // (열 시작 위치)
		int col_end = 6;
		
		for (int i = row_start; i <= row_end; ++i) {
			for (int j = col_start; j <= col_end; ++j) {
				str = m_excel.Get_Sheet(a_sheetName)->readStr(i, j); // row(행), col(열) readStr(1, 0);
				m_grid_area.Write_text_on_the_grid(i-1, j, str);
			}
		}

		m_grid_area.Invalidate();

		return true;
	}

	return false;
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

void CContractionDesignDlg::OnBnClickedCellClearExcelBtn()
{
	m_grid_area.Cell_Clear();
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+