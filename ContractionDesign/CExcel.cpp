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
