// BatchNumberChage.cpp : implementation file
//

#include "stdafx.h"
#include "Weight.h"
#include "BatchNumberChange.h"
#include "HelperClass.h"
#include "DBConnector.h"
#include "DBptr.h"
#include "MaterialManagementDialog.h"
#include "uiFunctions.h"

IMPLEMENT_DYNAMIC(CBatchNumberChange, CDialog)

CBatchNumberChange::CBatchNumberChange(CWnd* pParent /*=NULL*/)
	: CDialog(CBatchNumberChange::IDD, pParent){}

CBatchNumberChange::~CBatchNumberChange(){}

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


void CBatchNumberChange::OnBnClickedOk()
{
	CString batchNumber, manufacture;
	m_BatchNumber.GetWindowText(batchNumber);

	if (batchNumber.IsEmpty())
	{
		AfxMessageBox("请输入批号！");
		return;
	}
	
	CString materialID = SingletonHelper::getInstance()->getFormulaID();

	CString sql;
	sql.Format("select manufacture from manufactures where batchnumber = '%s'", batchNumber);

	_RecordsetPtr& m_pRecordset = SQLExecutor::getInstanceRef().execquery(sql);


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

	//修改条码和生产厂家！！！
	sql.Format("update materials set batchnumber = '%s' , manufacture = '%s' where id = %s ", 
		batchNumber, manufacture, materialID);

	SQLExecutor::getInstanceRef().execquery(sql);

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

    uiutils::setdlgsize(this, &m_ButtonCancel, &m_ButtonOK);

	return TRUE;
}
