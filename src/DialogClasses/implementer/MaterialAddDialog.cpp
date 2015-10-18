// MaterialAddDialgo.cpp : implementation file
//

#include "stdafx.h"
#include "Weight.h"
#include "MaterialAddDialog.h"
#include "MaterialManagementDialog.h"
#include "HelperClass.h"
#include "DBConnector.h"
#include "DBptr.h"
#include "uiFunctions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CMaterialAddDialog::CMaterialAddDialog(CWnd* pParent /*=NULL*/)
: CDialog(CMaterialAddDialog::IDD, pParent)
{
}


void CMaterialAddDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_ButtonOK);
	DDX_Control(pDX, IDCANCEL, m_ButtonCancel);
	DDX_Control(pDX, IDC_MATERIALNAME_EDIT, m_MaterialName);
	DDX_Control(pDX, IDC_MATERIALID_EDIT, m_MaterialID);
	DDX_Control(pDX, IDC_MATERIALNAME_EDIT2, m_BatchNumber);
	DDX_Control(pDX, IDC_MANUFACTURE, m_Manufacture);
}


BEGIN_MESSAGE_MAP(CMaterialAddDialog, CDialog)
	ON_BN_CLICKED(IDOK, &CMaterialAddDialog::OnBnClickedOk)
END_MESSAGE_MAP()

void CMaterialAddDialog::OnOK() 
{
	CString materialName, materialID, materialBatchNumber, materialManufacture;
	
	m_MaterialID.GetWindowText(materialID);
	m_MaterialName.GetWindowText(materialName);
	m_BatchNumber.GetWindowText(materialBatchNumber);
	m_Manufacture.GetWindowText(materialManufacture);
	
	if (materialID.IsEmpty() || materialName.IsEmpty())
	{
		CString msg("材料编号，材料名字为必填选项！");
		AfxMessageBox(msg);
		return;
	}

	try
	{
		CString sql;
		sql.Format("insert into manufactures(batchnumber, materialname, manufacture) values('%s', '%s', '%s'); ", 
			materialBatchNumber, materialName, materialManufacture);
		SQLExecutor::getInstanceRef().execquery(sql);
	}
	catch(_com_error)
	{
		AfxMessageBox("批号重复！请检查批号，以及相应的生产厂商");
		return;
	}


	try
	{
		CString sql;
		sql.Format("insert into [materials] ([id], [name], [batchnumber], [manufacture]) values('%s', '%s', '%s', '%s'); ", 
			materialID, materialName, materialBatchNumber, materialManufacture);
		SQLExecutor::getInstanceRef().execquery(sql);
	}
	catch(_com_error &e)
	{
		AfxMessageBox(e.Description());
		return;
	}

	m_MaterialManageWindow->m_MaterialList.DeleteAllItems();
	m_MaterialManageWindow->initList();

	CDialog::OnOK();
}

BOOL CMaterialAddDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	uiutils::setdlgsize(this, &m_ButtonCancel, &m_ButtonOK);
	return TRUE;
}

CMaterialAddDialog::~CMaterialAddDialog(){}

void CMaterialAddDialog::OnBnClickedOk()
{
	OnOK();
}

