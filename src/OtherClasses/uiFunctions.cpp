#include "stdafx.h"
#include "uiFunctions.h"

void uiFunctions::updateList(_RecordsetPtr& pRecordset, CListCtrl& listCtrl, std::vector<CString>& headerList)
{
	int itemIndex = 0;
	int subItemIndex = 0;
	try
	{
		while(!pRecordset->adoEOF)
		{
			for (size_t i = 0; i < headerList.size(); ++i )
			{
				_variant_t vDataField = pRecordset->GetCollect(_variant_t(headerList[i]));
				CString dataField;
				//取出某个字段的数据
				if (vDataField.vt != VT_NULL)
				{
					dataField = (LPCTSTR)(_bstr_t)vDataField;
				}
				//insert or modify by the value of i
				i == 0 ? (listCtrl.InsertItem(itemIndex,dataField)):(listCtrl.SetItemText(itemIndex, subItemIndex, dataField));
				++subItemIndex;
			}
			subItemIndex = 0;
			++itemIndex;
			pRecordset->MoveNext();
		}
	}
	catch (_com_error& e)
	{
		throw e;
	}
	return;
}

void uiFunctions::initListHeader(std::vector<CString>& headerList, CListCtrl& listCtrl)
{
	for (size_t i = 0; i < headerList.size(); ++i)
	{
		listCtrl.InsertColumn(i, headerList[i], 0, 160);
	}
	return;
}

void uiFunctions::clearList(CListCtrl& listCtrl)
{
	listCtrl.DeleteAllItems();
	return;
}

void uiFunctions::setdlgsize(CDialog* pdlg, CButton* pback, CButton* pok, bool hasBorder)
{
	if(hasBorder)
	{
		pdlg->ModifyStyleEx(0, WS_EX_APPWINDOW | WS_EX_CONTROLPARENT, SWP_NOSIZE);
		pdlg->ModifyStyle(WS_BORDER | WS_DLGFRAME | WS_THICKFRAME, WS_POPUP, SWP_NOSIZE);  
	}

	if(pback)
	{
		int bxstart = 768;
		int bystart = 650;
		int bwidth  = 200;
		int bheight = 60;
		CRect brect(bxstart, bystart, bxstart + bwidth, bystart + bheight);
		pback->MoveWindow(&brect, false);
	}

	if(pok)
	{
		int bxstart = 768 - 200 - 20;
		int bystart = 650;
		int bwidth = 200;
		int bheight = 60;
		CRect brect(bxstart, bystart, bxstart + bwidth, bystart + bheight);
		pok->MoveWindow(&brect, false);
	}

	int width = GetSystemMetrics(SM_CXSCREEN);
	int height = GetSystemMetrics(SM_CYSCREEN);
	int wndWidth = 1024;
	int wndHeight = 768;
	int xstart = ((width - wndWidth) / 2) + 1;
	int ystart = ((height - wndHeight) / 2) + 1;

	CRect   newRect(xstart, ystart, xstart + wndWidth, ystart + wndHeight);
	pdlg->MoveWindow(&newRect,false);   
}