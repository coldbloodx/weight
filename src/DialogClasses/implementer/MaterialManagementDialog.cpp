// MaterialManagementDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Weight.h"
#include "MaterialManagementDialog.h"
#include <string>
#include <vector>
#include "MaterialAddDialog.h"
#include "HelperClass.h"
#include "DBConnector.h"
#include "DBptr.h"
#include "uiFunctions.h"
#include "BatchNumberChange.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CMaterialManagementDialog::CMaterialManagementDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CMaterialManagementDialog::IDD, pParent)
{
}


void CMaterialManagementDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMaterialManagementDialog)
	DDX_Control(pDX, IDC_STATUS_STATIC, m_StatusStatic);
	DDX_Control(pDX, IDOK, m_ButtonOK);
	DDX_Control(pDX, IDC_MATERIALDEL, m_Del);
	DDX_Control(pDX, IDC_MATERIALADD, m_Add);
	DDX_Control(pDX, IDC_MATERIALLIST, m_MaterialList);
	DDX_Control(pDX, IDC_BATCHNUMBERCHANGE, m_BatchNumberChange);
}

BEGIN_MESSAGE_MAP(CMaterialManagementDialog, CDialog)
	ON_BN_CLICKED(IDC_MATERIALADD, OnMaterialadd)
	ON_BN_CLICKED(IDC_MATERIALDEL, OnMaterialdel)
	ON_BN_CLICKED(IDC_BATCHNUMBERCHANGE, &CMaterialManagementDialog::OnBnClickedBatchnumberchange)
END_MESSAGE_MAP()

BOOL CMaterialManagementDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	initListHeader();
	initList();
    uiutils::setdlgsize(this, &m_ButtonOK);

	return TRUE;  
}

CMaterialManagementDialog::~CMaterialManagementDialog()
{
}

void CMaterialManagementDialog::initListHeader()
{
	std::vector<std::string> headerList;
	headerList.push_back("材料编号");
	headerList.push_back("材料名称");
	headerList.push_back("材料条码");
	headerList.push_back("制造厂商");
	for (int i = 0; i< (int)headerList.size(); ++i)
	{
		m_MaterialList.InsertColumn(i,headerList[i].c_str(), 0, 160);
	}
}

void CMaterialManagementDialog::initList()
{
	_RecordsetPtr dbptr = SQLExecutor::getInstanceRef().execquery(CString("select * from materials order by id"));
	
	CString headerArray[4] = {"id", "name","batchnumber","manufacture"};
	std::vector<CString> headerList(headerArray, headerArray + 4);

	uiutils::updatelist(dbptr, m_MaterialList, headerList);
}

void CMaterialManagementDialog::OnMaterialadd() 
{
	// TODO: Add your control notification handler code here
	CMaterialAddDialog materialAddDialog;
	materialAddDialog.m_MaterialManageWindow = this;
	materialAddDialog.DoModal();
}

void CMaterialManagementDialog::OnMaterialdel() 
{
	// TODO: Add your control notification handler code here

	POSITION pos = m_MaterialList.GetFirstSelectedItemPosition() - 1;

	CString mid = m_MaterialList.GetItemText((int)pos, 0);

	if (mid.IsEmpty())
	{
		AfxMessageBox("请在下表中选择要删除的材料!");
		return;
	}

	CString msg("您确定要删除这种材料？");
	CString caption("删除材料");
	//选择cancel则返回
	if (IDCANCEL == MessageBox(msg, caption, MB_OKCANCEL))
	{
		return;
	}

	CString sql;
	sql.Format("delete from materials where id = %s ", mid);

	SQLExecutor::getInstanceRef().execquery(sql);

	m_MaterialList.DeleteAllItems();
	initList();
}

void CMaterialManagementDialog::OnBnClickedBatchnumberchange()
{
	// TODO: Add your control notification handler code here
	POSITION pos = m_MaterialList.GetFirstSelectedItemPosition() - 1;

	CString ID = m_MaterialList.GetItemText((int)pos, 0);

	if (ID.IsEmpty())
	{
		AfxMessageBox("请在下表中选择修的材料!");
		return;
	}
	
	SingletonHelper::getInstance()->setFormulaID(ID);
	SingletonHelper::getInstance()->setPtrData((void*)this);
	CBatchNumberChange batchNumberchange;
	batchNumberchange.DoModal();
}
