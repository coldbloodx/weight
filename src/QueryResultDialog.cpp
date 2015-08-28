// QueryResultDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Weight.h"
#include "QueryResultDialog.h"


// CQueryResultDialog dialog

IMPLEMENT_DYNAMIC(CQueryResultDialog, CDialog)

CQueryResultDialog::CQueryResultDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CQueryResultDialog::IDD, pParent)
{

}

CQueryResultDialog::~CQueryResultDialog()
{
}

void CQueryResultDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CQueryResultDialog, CDialog)
END_MESSAGE_MAP()


// CQueryResultDialog message handlers
