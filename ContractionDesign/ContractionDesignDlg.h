
// ContractionDesignDlg.h: 헤더 파일
//

#pragma once
#include "Grid_Area.h"
#include "CExcel.h"

// CContractionDesignDlg 대화 상자
class CContractionDesignDlg : public CDialogEx
{
private:
	Grid_Area m_grid_area;
	CExcel m_excel;

public:
	CComboBox m_sheetName_combo;

// 생성입니다.
public:
	CContractionDesignDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONTRACTIONDESIGN_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.

// 구현입니다.
private: 
	void Set_combo();
	bool Load_Excel_Sheet(CString a_sheetName);

protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedFindExcelBtn();
	void On_ComboChange();
	
	afx_msg HBRUSH OnCtlColor(CDC *pDC, CWnd *pWnd, UINT nCtlColor);
	virtual BOOL PreTranslateMessage(MSG *pMsg);
};
