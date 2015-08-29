// BatchNumberChage.cpp : implementation file
//

#include "stdafx.h"
#include "Weight.h"
#include "BatchNumberChange.h"
#include "HelperClass.h"
#include "DBConnector.h"
#include "RecordSetPointer.h"
#include "MaterialManagementDialog.h"
#include "uiFunctions.h"
// CBatchNumberChage dialog

IMPLEMENT_DYNAMIC(CBatchNumberChange, CDialog)

CBatchNumberChange::CBatchNumberChange(CWnd* pParent /*=NULL*/)
	: CDialog(CBatchNumberChange::IDD, pParent)
{

}

CBatchNumberChange::~CBatchNumberChange()
{
}

void CBatchNumberChange::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_ButtonOK);
	DDX_Control(pDX, IDCANCEL, m_ButtonCancel);
	DDX_Control(pDX, IDC_BATCHNUMBER, m_BatchNumber);
}


BEGIN_MESSAGE_MAP(CBatchNumberChange, CDialog)
	ON_BN_CLICKED(IDOK, &CBatchNumberChange::OnBnClickedOk)
END_MESSAGE_MAP()


// CBatchNumberChage message handlers

void CBatchNumberChange::OnBnClickedOk()
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
	SQLExecutor::getInstanceRef().setDatabaseConnection(DBConnector::getInstanceRef().getdbcon());
	SQLExecutor::getInstanceRef().setSqlState(sqlState);

	try
	{
		SQLExecutor::getInstanceRef().execSQL() ;
	}
	catch (_com_error& e)
	{
		AfxMessageBox(e.Description());
		return;
	}

	_RecordsetPtr& m_pRecordset = SQLExecutor::getInstanceRef().getRecordPtr();

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

	SQLExecutor::getInstanceRef().setDatabaseConnection(DBConnector::getInstanceRef().getdbcon());
	SQLExecutor::getInstanceRef().setSqlState(sqlState);

	//exec SQL state
	try
	{
		SQLExecutor::getInstanceRef().execSQL() ;
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

BOOL CBatchNumberChange::OnInitDialog()
{
	CDialog::OnInitDialog();

    uiFunctions::setdlgsize(this, &m_ButtonCancel, &m_ButtonOK);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
