#pragma once
#include "GridCtrl_src/GridCtrl.h"

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

	CRect m_pic_ctrl_rect;  // ������ ���� ��ǥ
	CFont m_pic_ctrl_font;  // ���ٿ��� ����� �۲�

public:
	// ���ٸ� �����ϴ� �Լ�
	void CreateGridArea(int a_rect_id, CWnd *ap_parent, int a_ctrl_id);
	
	// ��ϵ� ��ư ������ ����ؼ� ��ư�� ��ġ�� ������ �����Ѵ�.
	void UpdateGridInfo();

	inline void Write_text_on_the_grid(int a_row, int a_col, const wchar_t *ap_text) 
	{
		m_grid.SetItemText(a_row, a_col, ap_text); 
	}

public:
	Grid_Area();
	virtual ~Grid_Area();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
};

