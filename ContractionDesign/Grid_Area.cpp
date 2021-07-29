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
	if (m_grid.Create(m_pic_ctrl_rect, this, 32000, WS_CHILD | WS_VISIBLE | WS_EX_CLIENTEDGE))
	{
		m_grid.SetRowCount(202);
		m_grid.SetColumnCount(7);
		
		/*for (int i = 0; i < 7; i++)
		{
			s.Format(L"%d 열", i);
			m_grid.SetItemText(0, i, s);
		}

		for (int i = 1; i < ROW_MAX_COUNT; i++)
		{
			s.Format(L"SPLINE [%d] 500, 22", i);
			m_grid.SetItemText(i, 0, s);
		}
		*/

	}
	
	m_grid.SetFixedRowCount(1);
	m_grid.SetBkColor(PIC_CTRL_BK_COLOR);
	//m_grid.SetBkColor(RGB(100, 100, 100));
	m_grid.SetFixedBkColor(RGB(0, 255, 255));

	// grid option	
	m_grid.SetTrackFocusCell(true);
	m_grid.SetEditable(true); // 셀 더블 클릭 하면 내용 수정할 수 없도록 막음.
	m_grid.EnableTitleTips(true);

	m_grid.SetColumnWidth(5, 150); // column width
	
	int w = 0;
	for (int i = 0; i < m_grid.GetColumnCount() - 1; w += m_grid.GetColumnWidth(i++));
	
	w = m_pic_ctrl_rect.Width() - w - 22;
	m_grid.SetColumnWidth(6, w); // column width
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