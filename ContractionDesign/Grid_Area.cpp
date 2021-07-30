// Grid_Area.cpp: 구현 파일
//

#include "pch.h"
#include "ContractionDesign.h"
#include "Grid_Area.h"

// Grid_Area

IMPLEMENT_DYNAMIC(Grid_Area, CWnd)

Grid_Area::Grid_Area()
{

}

Grid_Area::~Grid_Area()
{
}


BEGIN_MESSAGE_MAP(Grid_Area, CWnd)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_PAINT()

	ON_NOTIFY(GVN_BEGINLABELEDIT, GRID_ID_NUM, OnGridStartEdit)
	ON_NOTIFY(GVN_ENDLABELEDIT, GRID_ID_NUM, OnGridEndEdit)
END_MESSAGE_MAP()


// Grid_Area 메시지 처리기

void Grid_Area::CreateGridArea(int a_rect_id, CWnd *ap_parent, int a_ctrl_id)
{
	CRect r;
	// 대화상자에 추가된 a_rect_id 아이디의 컨트롤 위치를 계산한다.
	ap_parent->GetDlgItem(a_rect_id)->GetWindowRect(r);
	ap_parent->ScreenToClient(r);

	// 오른쪽으로 약간의 여백이 생기기 때문에 오른쪽으로 조금더 크게 보정한다.
	//r.right += 2;
	// picture control로 사용할 윈도우를 생성한다.
	Create(NULL, NULL, WS_CHILD | WS_VISIBLE, r, ap_parent, a_ctrl_id);
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

int Grid_Area::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// picture control 윈도우 클라이언트 전체 영역의 좌표를 얻는다.
	GetClientRect(m_pic_ctrl_rect);

	// picture control에서 사용할 폰트를 생성한다.
	m_pic_ctrl_font.CreateFont(15, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"맑은 고딕");

	// 등록된 버튼 정보를 가지고 각 버튼의 위치 정보를 구성한다.
	UpdateGridInfo();

	return 0;
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

void Grid_Area::UpdateGridInfo()
{
	m_pic_ctrl_rect.left += 2;
	m_pic_ctrl_rect.top += 2;
	m_pic_ctrl_rect.right -= 2;
	m_pic_ctrl_rect.bottom -= 2;
	
	CString s;
	if (m_grid.Create(m_pic_ctrl_rect, this, GRID_ID_NUM, WS_CHILD | WS_VISIBLE | WS_EX_CLIENTEDGE))
	{
		m_grid.SetRowCount(202);
		m_grid.SetColumnCount(8);				
	}
	m_grid.SetItemText(0, 0, L"Xm(A)");
	m_grid.SetItemText(0, 1, L"Hi(B)");
	m_grid.SetItemText(0, 2, L"Ho(C)");
	m_grid.SetItemText(0, 3, L"L (D)");
	m_grid.SetItemText(0, 4, L"X (E)");
	m_grid.SetItemText(0, 5, L"h (F)");
	m_grid.SetItemText(0, 6, L"  (G)");
	m_grid.SetItemText(0, 7, L"X/L =  (H)");

	m_grid.SetItemText(1, 0, L"0");
	m_grid.SetItemText(1, 1, L"3000");
	m_grid.SetItemText(1, 2, L"1000");
	m_grid.SetItemText(1, 3, L"6000");
	m_grid.SetItemText(1, 4, L"0");
	m_grid.SetItemText(1, 5, L"0");
	m_grid.SetItemText(1, 6, L"0");
	
	m_bRejectEditAttempts = TRUE;
	m_bRejectEditChanges = TRUE;

	m_grid.SetFixedRowCount(1);
	m_grid.SetBkColor(PIC_CTRL_BK_COLOR);
	//m_grid.SetBkColor(RGB(100, 100, 100));
	m_grid.SetFixedBkColor(RGB(0, 255, 255));

	// grid option	
	m_grid.SetTrackFocusCell(true);
	m_grid.SetEditable(true); // 셀 더블 클릭 하면 내용 수정할 수 없도록 막음.
	m_grid.EnableTitleTips(true);
	//m_grid.SetItemFormat(1, 1, 2);// 0:왼쪽 정렬, 1:가운데 정렬, 2:오른쪽정렬

	m_grid.SetColumnWidth(5, 155); // column width
	m_grid.SetColumnWidth(6, 170); // column width		
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

void Grid_Area::OnDestroy()
{
	CWnd::OnDestroy();

	m_grid.DestroyWindow();
	m_pic_ctrl_font.DeleteObject();
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

void Grid_Area::OnPaint()
{
	CPaintDC dc(this);

	dc.SelectStockObject(DC_BRUSH);  // 색상만 변경해서 사용하는 Brush 설정
	dc.SelectStockObject(DC_PEN);    // 색상만 변경해서 사용하는 Pen 설정

	dc.SetDCBrushColor(PIC_CTRL_BK_COLOR);  // picture control의 배경색 설정 
	dc.SetDCPenColor(PIC_CTRL_OUTER_BODER_COLOR);   // picture control의 테두리 색상 설정 

	dc.Rectangle(m_pic_ctrl_rect);  // picture control 전체 영역을 사각형으로 그린다.

	dc.SelectStockObject(NULL_BRUSH);  // Brush는 사용 안 함으로 설정
	dc.SetDCPenColor(PIC_CTRL_INNER_BODER_COLOR);  // picture control의 내부 테두리 색상 설정

	// picture control의 내부 테두리를 그린다.
	dc.Rectangle(m_pic_ctrl_rect.left + 1, m_pic_ctrl_rect.top + 1, m_pic_ctrl_rect.right - 1, m_pic_ctrl_rect.bottom - 1);
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

// GVN_BEGINLABELEDIT
void Grid_Area::OnGridStartEdit(NMHDR *pNotifyStruct, LRESULT *pResult)
{
	NM_GRIDVIEW *pItem = (NM_GRIDVIEW *)pNotifyStruct;
	//*pResult = (m_bRejectEditAttempts) ? -1 : 0;
}

// GVN_ENDLABELEDIT
void Grid_Area::OnGridEndEdit(NMHDR *pNotifyStruct, LRESULT *pResult)
{
	NM_GRIDVIEW *pItem = (NM_GRIDVIEW *)pNotifyStruct;
	//*pResult = (m_bRejectEditChanges) ? -1 : 0;	

	Translate_Value(m_cur_combo_pos);
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

void Grid_Area::Translate_Value(int a_select)
{	
	CString str;
	CString str_result;	
	double d_result;
	double value;
	const double _pi = 3.1415926;

	double A = _tstof(m_grid.GetItemText(1, 0));
	double B = _tstof(m_grid.GetItemText(1, 1));
	double C = _tstof(m_grid.GetItemText(1, 2));
	double D = _tstof(m_grid.GetItemText(1, 3));		
	
	for (int i = 1; i < ROW_MAX_COUNT; ++i) {
		// E열
		str = m_grid.GetItemText(i, 4);
		value = _tstof(str);

		d_result = value + (D / 200);
						  
		str_result.Format(L"%.1lf", floor(d_result * 10) / 10);
		m_grid.SetItemText(i + 1, 4, str_result);

		// F열
		str = m_grid.GetItemText(i, 4);
		value = _tstof(str);

		// Cubic
		if (a_select == 0)  
			d_result = (B / 2) - ((B - C) / 2) * ((3 * pow((value / D), 2)) - (2 * pow((value / D), 3)));
		// Cosine
		else if(a_select == 1)
			d_result = 0.25 * ((B + C) + (B - C) * cos(_pi * value / D));
		// Morel
		else if (a_select == 2)
			d_result = (C / 2) + ((B - C) / 2) * (1 - (pow((D / A), 2)) * (pow((value / D), 3)));
		// 2-Cubic
		else if (a_select == 3)
			d_result = ((B - C) * (1 - ((pow((1 / A), 2)) * (pow(value, 3) / D))) + C);
		// 4th-order
		else if (a_select == 4) {			
			
		}
		// 5th-order
		else if (a_select == 5) {
			// H열
			str = m_grid.GetItemText(i, 4);
			value = _tstof(str);

			d_result = value / D;
			str_result.Format(L"%.12lg", floor(d_result * 1000000000000) / 1000000000000);
			m_grid.SetItemText(i, 7, str_result);

			// F열
			str = m_grid.GetItemText(i, 7);
			value = _tstof(str);

			d_result = ((-10 * pow(value, 3) + 15 * pow(value, 4) - 6 * pow(value, 5)) * (B - C)) + B;
		}
		str_result.Format(L"%.12lg", floor(d_result * 1000000000000) / 1000000000000);
		m_grid.SetItemText(i, 5, str_result);

		// G열
		str_result.Format(L"SPLINE %s,%s", m_grid.GetItemText(i, 4), m_grid.GetItemText(i, 5));
		m_grid.SetItemText(i, 6, str_result);
	}
	m_grid.Invalidate();
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

void Grid_Area::OnRejectEditAttempts()
{
	m_bRejectEditAttempts = !m_bRejectEditAttempts;
	//UpdateMenuUI();
}

void Grid_Area::OnRejectEditChanges()
{
	m_bRejectEditChanges = !m_bRejectEditChanges;
	//UpdateMenuUI();
}