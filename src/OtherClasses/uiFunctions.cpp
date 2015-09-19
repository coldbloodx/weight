#include "stdafx.h"
#include "uiFunctions.h"

void uiutils::updatelist(_RecordsetPtr& pRecordset, CListCtrl& listCtrl, CString* headerptr, int headerlen)
{
    int itemIndex = 0;
    int subItemIndex = 0;
    try
    {
        while(!pRecordset->adoEOF)
        {
            for (int i = 0; i < headerlen; ++i )
            {
                _variant_t vDataField = pRecordset->GetCollect(_variant_t(headerptr[i]));
                CString dataField;
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


void uiutils::updatelist(_RecordsetPtr& pRecordset, CListCtrl& listCtrl, std::vector<CString>& headerList)
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

void uiutils::initlistheader(std::vector<CString>& headerList, CListCtrl& listCtrl)
{
	for (size_t i = 0; i < headerList.size(); ++i)
	{
		listCtrl.InsertColumn(i, headerList[i], 0, 160);
	}
	return;
}

void uiutils::initlistheader(CListCtrl& listCtrl, CString* strarray, int arraylen)
{
    for (int i = 0; i < arraylen; ++i)
    {
        listCtrl.InsertColumn(i, strarray[i], 0, 160);
    }
    return;
}


void uiutils::clearList(CListCtrl& listCtrl)
{
	listCtrl.DeleteAllItems();
	return;
}

void uiutils::setdlgsize(CDialog* pdlg, CButton* pback, CButton* pok, bool hasBorder)
{
    pdlg->ModifyStyleEx(0, WS_EX_APPWINDOW | WS_EX_CONTROLPARENT, SWP_NOSIZE |SWP_NOMOVE | SWP_FRAMECHANGED);
    pdlg->ModifyStyle( WS_DLGFRAME | WS_THICKFRAME | WS_POPUP , SWP_NOSIZE | SWP_NOMOVE | SWP_FRAMECHANGED);  
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


void uiutils::drawDlgBg(CDialog* pDlg, int bmpId)
{
    CPaintDC dc(pDlg);
    CRect rc;
    pDlg->GetClientRect(&rc);
    CDC dcMem;
    dcMem.CreateCompatibleDC(&dc);
    CBitmap bmpBackground;
    bmpBackground.LoadBitmap(bmpId);

    BITMAP bitmap;
    bmpBackground.GetBitmap(&bitmap);
    CBitmap* pbmpPri = dcMem.SelectObject(&bmpBackground);
    dc.StretchBlt(0,0,rc.Width(), rc.Height(), &dcMem,0,0,bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);
}

void uiutils::init2rowbtns(CButton** btnarray, int arraysize)
{
	int left = 30;
	int top = 180;
	int width = 320 - left;
	int height = 355 - top;
	int horiSpacer = 365 - 320;
	int vertSpacer = 400 - 355;

	for (int i = 0; i < arraysize; ++i)
	{
		CRect rect(left, top, left + width, top + height);
		btnarray[i]->MoveWindow(rect, TRUE);

		if (((i + 1) % 3) == 0)
		{
			left = 30;
			top = rect.bottom + vertSpacer;
		}
		else
		{
			left = rect.right + horiSpacer;
		}
	}

}

void uiutils::fillcombo( _RecordsetPtr& dbptr, CComboBox& rcombo, CString& key )
{
    try
    {
        while(!dbptr->adoEOF)
        {
                _variant_t vDataField = dbptr->GetCollect(_variant_t(key));
                if (vDataField.vt != VT_NULL)
                {
                    CString dataField = (LPCTSTR)(_bstr_t)vDataField;
                    rcombo.AddString(dataField);
                }

            dbptr->MoveNext();
        }
    }
    catch (_com_error& e)
    {
        throw e;
    }
}