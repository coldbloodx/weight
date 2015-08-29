// UserAddDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Weight.h"
#include "UserAddDialog.h"
#include "UserManageDialog.h"
#include "HelperClass.h"
#include "DBConnector.h"
#include "DBptr.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUserAddDialog dialog

CUserAddDialog::CUserAddDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CUserAddDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUserAddDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CUserAddDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUserAddDialog)
	DDX_Control(pDX, IDOK, m_ButtonOK);
	DDX_Control(pDX, IDCANCEL, m_ButtonCancel);
	DDX_Control(pDX, IDC_USERRIGHT_DROPDOWN, m_UserRight);
	DDX_Control(pDX, IDC_USERNAME_EDIT, m_UserName);
	DDX_Control(pDX, IDC_USERID_EDIT, m_UserID);
	//}}AFX_DATA_MAP
}

CUserAddDialog::~CUserAddDialog()
{

}

BEGIN_MESSAGE_MAP(CUserAddDialog, CDialog)
	//{{AFX_MSG_MAP(CUserAddDialog)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CUserAddDialog::OnBnClickedOk)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUserAddDialog message handlers



void CUserAddDialog::OnOK() 
{
	// TODO: Add extra validation here
	
	CString userID, userName, userRight;
	
	m_UserID.GetWindowText(userID);
	m_UserName.GetWindowText(userName);
	m_UserRight.GetWindowText(userRight);


	
	if (userID.IsEmpty() || userName.IsEmpty() || userRight.IsEmpty())
	{
		CString msg("人员编号，人员姓名，人员权限为必填选项！");
		AfxMessageBox(msg);
		return;
	}
	
	//init recordset pointer
	SQLExecutor::getInstanceRef().setSqlState(CString("SELECT * FROM USERS"));

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

	//get the result data set
	_RecordsetPtr& m_pRecordset = SQLExecutor::getInstanceRef().getRecordPtr();

	try
	{
		if (! m_pRecordset->adoEOF)
		{		
			m_pRecordset->MoveLast();
		}

		m_pRecordset->AddNew();
		m_pRecordset->PutCollect("id", _variant_t(userID));
		m_pRecordset->PutCollect("name", _variant_t(userName));
		m_pRecordset->PutCollect("password", _variant_t("123456"));
		m_pRecordset->PutCollect("permission", _variant_t(userRight));
		
	}
	catch(_com_error &e)
	{
		AfxMessageBox(e.Description());
	}
	
	//更新数据库
	try
	{
		m_pRecordset->Update();	
	}
	catch(_com_error)
	{
		AfxMessageBox("添加用户出现错误，请确认用户ID是否重复");
		return;
	}

	AfxMessageBox("添加用户成功，默认密码为123456，\r请退出系统，用心用户登录修改密码！");
	m_UserManagementWindow->m_UserList.DeleteAllItems();
	m_UserManagementWindow->initList();

	CDialog::OnOK();
}

BOOL CUserAddDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	CBitmap   bmp;   
	bmp.LoadBitmap(IDB_MATERIALCOUNTINPUT);//载入图片   
	m_brBk.CreatePatternBrush(&bmp); 
	bmp.DeleteObject();   

	CRect wndRect((1024 - 640) / 2, (768 - 385) / 2, (1024 - 640) / 2 + 640, (768 - 385) / 2 + 400);
	this->MoveWindow(wndRect);

	CRect okRect(404, 339, 503, 374);
	CRect cancelRect(520, 339, 618, 374);

	m_ButtonOK.MoveWindow(okRect);


	m_ButtonCancel.MoveWindow(cancelRect);


	/*buttonVector.push_back(&m_ButtonCancel);
	buttonVector.push_back(&m_ButtonOK);

	for(size_t i = 0; i < buttonVector.size(); ++i)
	{
		HelperFunctions::setButtonStyle(*buttonVector[i], RGB(55,71,158), SingletonHelper::getInstance()->simSong20);
	}*/
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CUserAddDialog::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	OnOK();
}

HBRUSH CUserAddDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
