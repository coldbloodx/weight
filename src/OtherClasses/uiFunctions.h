#include "StdAfx.h"


#ifndef _UIFUNCTIONS_HEADER_
#define _UIFUNCTIONS_HEADER_

namespace uiutils
{
	void initlistheader(std::vector<CString>& headerList, CListCtrl& listCtrl);
	
    void initlistheader(CListCtrl& listCtrl, CString* strarray, int arraylen);

    void updatelist(_RecordsetPtr& pRecordset, CListCtrl& listCtrl, std::vector<CString>& headerList);
	
    void updatelist(_RecordsetPtr& pRecordset, CListCtrl& listCtrl, CString* headerptr, int headerlen);

    void clearList(CListCtrl& listCtrl);
	
    void setdlgsize(CDialog* pdlg, CButton* pback = NULL, CButton* pok = NULL, bool hasborder = false);
   
    void drawDlgBg(CDialog* pDlg, int bmpId);

	void init2rowbtns(CButton** btnarray, int arraysize);

    void fillcombo(_RecordsetPtr& dbptr, CComboBox& rcombo, CString& key);

};
#endif