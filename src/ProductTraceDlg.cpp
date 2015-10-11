// ProductTraceDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Weight.h"
#include "ProductTraceDlg.h"
#include "DBptr.h"
#include "uiFunctions.h"

// CProductTraceDlg dialog

IMPLEMENT_DYNAMIC(CProductTraceDlg, CDialog)

CProductTraceDlg::CProductTraceDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CProductTraceDlg::IDD, pParent)
{
}

CProductTraceDlg::~CProductTraceDlg()
{
}

void CProductTraceDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO1, cbxProductBatch);
    DDX_Control(pDX, IDC_PRODUCT_LIST, listProduct);
    DDX_Control(pDX, IDC_MATERIAL_LIST, listMaterial);
}


BEGIN_MESSAGE_MAP(CProductTraceDlg, CDialog)
    ON_BN_CLICKED(IDOK, &CProductTraceDlg::OnBnClickedOk)
    ON_NOTIFY(NM_CLICK, IDC_PRODUCT_LIST, &CProductTraceDlg::OnNMClickProductList)
    ON_NOTIFY(NM_DBLCLK, IDC_PRODUCT_LIST, &CProductTraceDlg::OnNMDblclkProductList)
END_MESSAGE_MAP()


// CProductTraceDlg message handlers

void CProductTraceDlg::OnBnClickedOk()
{
    CString strBatchNumber;
    cbxProductBatch.GetWindowText(strBatchNumber);

    if(strBatchNumber.IsEmpty())
    {
        return;
    }

    CString sql;
    sql.Format("select formulaname, username, amount, odate, otime, fbatchnumber from weight where fbatchnumber = '%s';", strBatchNumber);
    
    _RecordsetPtr dbptr = SQLExecutor::getInstancePtr()->execquery(sql);
    listProduct.DeleteAllItems();
    
    CString weightdbfields[6] = {"fbatchnumber", "formulaname", "amount", "username", "odate", "otime"};

    uiutils::updatelist(dbptr, listProduct, weightdbfields, 6);
}

BOOL CProductTraceDlg::OnInitDialog()
{
    CDialog::OnInitDialog();
    
    CString sql;
    sql.Format("select formulaname, username, amount, odate, otime, fbatchnumber from weight;");
    _RecordsetPtr dbptr = SQLExecutor::getInstancePtr()->execquery(sql);

    CString pheaderarray[6] = {"成品批号", "配方名称", "用户名", "称重数量", "日期", "时间"};

    uiutils::initlistheader(listProduct, pheaderarray, 6);

    CString weightdbfields[6] = {"fbatchnumber", "formulaname", "username", "amount", "odate", "otime"};

    uiutils::updatelist(dbptr, listProduct, weightdbfields, 6);
    
    dbptr->MoveFirst();

    uiutils::fillcombo(dbptr, cbxProductBatch, CString("fbatchnumber"));

    CString mheaderarray [8] = {"材料名称", "材料批号", "配方名称", "配方批号", "用户名", "用量", "日期", "时间" };
    uiutils::initlistheader(listMaterial, mheaderarray, 8);

    return TRUE;
}

void CProductTraceDlg::OnNMClickProductList(NMHDR *pNMHDR, LRESULT *pResult)
{
    // TODO: Add your control notification handler code here
    updatemlist();

}

void CProductTraceDlg::updatemlist()
{
    POSITION pos = listProduct.GetFirstSelectedItemPosition() - 1;
    CString strbnumber = listProduct.GetItemText((int)pos, 0);

    CString sql;
    sql.Format("select materialname, materialbatchnumber, formulaname, formula_batch_number, operatorname, amount, operate_date, operate_time from materialrecords where formula_batch_number = '%s'", strbnumber);

    _RecordsetPtr dbptr = SQLExecutor::getInstanceRef().execquery(sql);

    CString mheaderarray[8] = {"materialname", "materialbatchnumber", "formulaname", "formula_batch_number", 
        "operatorname", "amount", "operate_date", "operate_time"};

    listMaterial.DeleteAllItems();
    uiutils::updatelist(dbptr, listMaterial, mheaderarray, 8 );
}

void CProductTraceDlg::OnNMDblclkProductList(NMHDR *pNMHDR, LRESULT *pResult)
{
    // TODO: Add your control notification handler code here
    //*pResult = 0;

    updatemlist();
}
