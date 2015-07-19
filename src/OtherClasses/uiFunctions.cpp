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