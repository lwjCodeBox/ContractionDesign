#pragma once
#include "GridCtrl_src/GridCtrl.h"
#include <cmath>

#define GRID_ID_NUM						32000

#define PIC_CTRL_BK_COLOR				RGB(15, 55, 100) 
#define PIC_CTRL_OUTER_BODER_COLOR		RGB(0, 255, 255) 
#define PIC_CTRL_INNER_BODER_COLOR		RGB(0, 255, 255)

#define ROW_MAX_COUNT					203

// Grid_Area

class Grid_Area : public CWnd
{
	DECLARE_DYNAMIC(Grid_Area)

private:
	CGridCtrl m_grid;
	CCellRange m_cellrange;

	CRect m_pic_ctrl_rect;  // 툴바의 영역 좌표
	CFont m_pic_ctrl_font;  // 툴바에서 사용할 글꼴

	BOOL m_bRejectEditAttempts;
	BOOL m_bRejectEditChanges;
	int cnt = 0;
	int m_ddd = 0;
	
public:
	char m_cur_combo_pos;	

public:
	// 툴바를 생성하는 함수
	void CreateGridArea(int a_rect_id, CWnd *ap_parent, int a_ctrl_id);
	
	// 등록된 버튼 정보를 사용해서 버튼이 위치할 정보를 구성한다.
	void UpdateGridInfo();

	inline void Write_text_on_the_grid(int a_row, int a_col, const wchar_t *ap_text) 
	{
		m_grid.SetItemText(a_row, a_col, ap_text); 
	}

	inline void Grid_Area::Cell_Clear()
	{		
		//m_grid.ClearCells(CCellRange(2, 0, 201, 7));
		m_grid.ClearCells(CCellRange(1, 7, 201, 7));
	}
	inline void Grid_Area::Cell_All_Clear()
	{
		// row start pos = 0
		// row end pos = 201
		// col start pos = 0
		// col end pos = 7
		m_grid.ClearCells(CCellRange(1, 0, 201, 7));
	}

	void Translate_Value(int a_select);

public:
	Grid_Area();
	virtual ~Grid_Area();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnPaint();	

	afx_msg void OnGridStartEdit(NMHDR *pNotifyStruct, LRESULT *pResult);
	afx_msg void OnGridEndEdit(NMHDR *pNotifyStruct, LRESULT *pResult);
	void OnRejectEditAttempts();
	void OnRejectEditChanges();
};