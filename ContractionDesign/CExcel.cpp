#include "pch.h"
#include "CExcel.h"
#include "ContractionDesignDlg.h"

bool CExcel::ExcelCertified(CString a_path)
{
	//LPCTSTR pszPath = L"..\\Debug\\Config\\MFC_Excel.xlsx";
	LPCTSTR pszPath = a_path;
	m_Book = xlCreateXMLBook();
	if (m_Book) {
		m_Book->setKey(L"JungWook Son", L"windows-2124230806c1e30f66bf6365a7l1hdm8");
		if (m_Book->load(pszPath)) {
			return true;
		}
	}
	AfxMessageBox(L"Can not found excel file");

	return false;
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

Sheet *CExcel::GetSheetByName(Book *book, const wchar_t *name)
{
	int cnt = book->sheetCount();

	for (unsigned short i = 0; i < cnt; ++i)
	{
		if (wcscmp(book->getSheet(i)->name(), name) == 0)
		{
			return book->getSheet(i);
		}
	}
	return 0;
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

Sheet *CExcel::Get_Sheet(CString a_sheetName)
{
	libxl::Format *format = NULL;
	m_pSheet = GetSheetByName(m_Book, a_sheetName);
	return m_pSheet;
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+


//bool CExcel::Load_Excel_Sheet(CString a_sheetName)
//{
//	libxl::Format *format = NULL;
//
//	//m_pSheet = GetSheetByName(m_Book, a_sheetName);
//
//	//if (m_pSheet) {
//	//	const wchar_t *str = NULL;
//
//	//	int t_col_start = 4; // (열 시작 위치)
//	//	int t_col_end = 33;
//	//	int t_row_start = 1;//4; // (행 시작 위치)
//	//	int t_row_end = 16; //3칸
//
//	//	// 엑셀 행, 열 시작 위치를 mvb 주소(addr) 위치를 기준으로 잡음.
//	//	for (int i = t_col_start; i <= t_col_end; i++) {
//	//		for (int j = t_row_start; j * 4 <= t_row_end; j++) {
//	//			str = m_pSheet->readStr(i, j * 4, &format); // addr
//	//		}
//	//	}
//
//	//	return true;
//	//}
//	return false;
//}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
