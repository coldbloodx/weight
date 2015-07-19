// CustomColorDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Weight.h"
#include "CustomColorDialog.h"
#include "OtherClasses/helperclass.h"


// CCustomColorDialog dialog

IMPLEMENT_DYNAMIC(CCustomColorDialog, CDialog)

CCustomColorDialog::CCustomColorDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CCustomColorDialog::IDD, pParent)
{

}

CCustomColorDialog::CCustomColorDialog(UINT nIDTemplate, CWnd* pParentWnd  /* = NULL */)
:CDialog(nIDTemplate,pParentWnd)
{

}

CCustomColorDialog::~CCustomColorDialog()
{
}

void CCustomColorDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCustomColorDialog, CDialog)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CCustomColorDialog message handlers

HBRUSH CCustomColorDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here
	pDC->SetTextColor(SingletonHelper::getInstance()->textColor);
	if (CTLCOLOR_STATIC == nCtlColor)
	{
		pDC->SetBkColor(SingletonHelper::getInstance()->backgroundColor);
		return hBrush;
	}

	if (CTLCOLOR_DLG == nCtlColor)
	{
		hBrush = CreateSolidBrush(SingletonHelper::getInstance()->backgroundColor);
		return hBrush;
	}
	// TODO:  Return a different brush if the default is not desired
	return hbr;
}
