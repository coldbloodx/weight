#include "..\StdAfx.h"

#ifndef _UIFUNCTIONS_HEADER_
#define _UIFUNCTIONS_HEADER_
namespace uiFunctions
{
	void initListHeader(std::vector<CString>& headerList, CListCtrl& listCtrl);
	void updateList(_RecordsetPtr& pRecordset, CListCtrl& listCtrl, std::vector<CString>& headerList);
	void clearList(CListCtrl& listCtrl);
	void setdlgsize(CDialog* pdlg, CButton* pback = NULL, CButton* pok = NULL, bool hasborder = false);
};
#endif