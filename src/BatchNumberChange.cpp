// BatchNumberChage.cpp : implementation file
//

#include "stdafx.h"
#include "Weight.h"
#include "BatchNumberChange.h"
#include "OtherClasses\HelperClass.h"
#include "OtherClasses\DatabaseConnector.h"
#include "OtherClasses\RecordSetPointer.h"
#include "DialogClasses\header\MaterialManagementDialog.h"
// CBatchNumberChage dialog

IMPLEMENT_DYNAMIC(CBatchNumberChage, CDialog)

CBatchNumberChage::CBatchNumberChage(CWnd* pParent /*=NULL*/)
	: CDialog(CBatchNumberChage::IDD, pParent)
{

}

CBatchNumberChage::~CBatchNumberChage()
{
}

void CBatchNumberChage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_ButtonOK);
	DDX_Control(pDX, IDCANCEL, m_ButtonCancel);
	DDX_Control(pDX, IDC_BATCHNUMBER, m_BatchNumber);
}


BEGIN_MESSAGE_MAP(CBatchNumberChage, CDialog)
	ON_BN_CLICKED(IDOK, &CBatchNumberChage::OnBnClickedOk)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CBatchNumberChage message handlers

void CBatchNumberChage::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CString batchNumber, manufacture;
	m_BatchNumber.GetWindowText(batchNumber);

	if (batchNumber.IsEmpty())
	{
		AfxMessageBox("请输入批号！");
		return;
	}
	
	//先拿过来用下
	CString materialID = SingletonHelper::getInstance()->getFormulaID();


	//查询出生产厂家
	CString sqlState ("SELECT MANUFACTURE FROM MANUFACTURES WHERE BATCHNUMBER = '");
	sqlState += batchNumber + "'";
	RecordSetPointer::getInstanceRef().setDatabaseConnection(DatabaseConnector::getInstanceRef().getDatabaseConnection());
	RecordSetPointer::getInstanceRef().setSqlState(sqlState);

	try
	{
		RecordSetPointer::getInstanceRef().execSQL() ;
	}
	catch (_com_error& e)
	{
		AfxMessageBox(e.Description());
		return;
	}

	_RecordsetPtr& m_pRecordset = RecordSetPointer::getInstanceRef().getRecordPtr();

	try
	{
		while(!m_pRecordset->adoEOF)
		{
			_variant_t vDataField = m_pRecordset->GetCollect(_variant_t("MANUFACTURE"));
			if (vDataField.vt != VT_NULL)
			{
				manufacture = (LPCTSTR)(_bstr_t)vDataField;
			}
			m_pRecordset->MoveNext();
		}
	}
	catch (_com_error& e)
	{
		throw e;
	}
	//查询生产厂家完毕！！！


	//修改条码和生产厂家！！！
	sqlState = ("UPDATE MATERIALS SET BATCHNUMBER = ");

	sqlState += batchNumber + ", MANUFACTURE = '" + manufacture + "' " ;
	sqlState += (" WHERE ID = ") + materialID;

	RecordSetPointer::getInstanceRef().setDatabaseConnection(DatabaseConnector::getInstanceRef().getDatabaseConnection());
	RecordSetPointer::getInstanceRef().setSqlState(sqlState);

	//exec SQL state
	try
	{
		RecordSetPointer::getInstanceRef().execSQL() ;
	}
	catch (_com_error& e)
	{
		AfxMessageBox(e.Description());
		return;
	}
	//条码和生产厂家修改完毕！！！

	CMaterialManagementDialog* mmDialog = (CMaterialManagementDialog*)(SingletonHelper::getInstance()->getPtrData());
	mmDialog->m_MaterialList.DeleteAllItems();
	mmDialog->initList();

	SingletonHelper::getInstance()->setPtrData(NULL);
	SingletonHelper::getInstance()->setFormulaID(CString(""));

	OnOK();
}

BOOL CBatchNumberChage::OnInitDialog()
{
	CDialog::OnInitDialog();
	CBitmap   bmp;   
	bmp.LoadBitmap(IDB_MATERIALINPUTCOUNT);//载入图片   
	m_brBk.CreatePatternBrush(&bmp); 
	bmp.DeleteObject();   

	CRect wndRect((1024 - 640) / 2, (768 - 236) / 2, (1024 - 640) / 2 + 640, (768 - 236) / 2 + 250);
	this->MoveWindow(wndRect);

	CRect okRect(404, 190, 503, 224);
	CRect cancelRect(520, 190, 618, 224);

	m_ButtonOK.MoveWindow(okRect);


	m_ButtonCancel.MoveWindow(cancelRect);

	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

HBRUSH CBatchNumberChage::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here
	if   (pWnd == this)   
	{   
		return m_brBk;   
	}   
	if   (nCtlColor   ==   CTLCOLOR_STATIC)   
	{     
		pDC->SetBkMode(TRANSPARENT);	//透明   
		return (HBRUSH)::GetStockObject(HOLLOW_BRUSH);   
	}   
	// TODO:  Return a different brush if the default is not desired
	return hbr;
}
