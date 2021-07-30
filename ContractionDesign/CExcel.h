#pragma once

#include "libxl.h"

using namespace libxl;

class CExcel 
{
private:
	Book *m_Book;
	Sheet *m_pSheet; // logical_port_adrs Sheet

private:
	Sheet *GetSheetByName(Book *book, const wchar_t *name);
		
public:
	bool ExcelCertified(CString a_path);

	int Get_Sheet_Count() { return m_Book->sheetCount(); }	
	CString GetExcelSheetName(int a_Sheet) { return m_Book->getSheet(a_Sheet)->name(); }
	
	Sheet *Get_Sheet(CString a_sheetName);	
};

