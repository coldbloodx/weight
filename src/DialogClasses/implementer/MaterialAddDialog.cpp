// MaterialAddDialgo.cpp : implementation file
//

#include "stdafx.h"
#include "Weight.h"
#include "MaterialAddDialog.h"
#include "MaterialManagementDialog.h"
#include "HelperClass.h"
#include "DatabaseConnector.h"
#include "RecordSetPointer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMaterialAddDialog dialog


CMaterialAddDialog::CMaterialAddDialog(CWnd* pParent /*=NULL*/)
: CDialog(CMaterialAddDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMaterialAddDialog)
	//}}AFX_DATA_INIT
}


void CMaterialAddDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMaterialAddDialog)
	DDX_Control(pDX, IDOK, m_ButtonOK);
	DDX_Control(pDX, IDCANCEL, m_ButtonCancel);
	DDX_Control(pDX, IDC_MATERIALNAME_EDIT, m_MaterialName);
	DDX_Control(pDX, IDC_MATERIALID_EDIT, m_MaterialID);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_MATERIALNAME_EDIT2, m_BatchNumber);
	DDX_Control(pDX, IDC_MANUFACTURE, m_Manufacture);
}


BEGIN_MESSAGE_MAP(CMaterialAddDialog, CDialog)
//{{AFX_MSG_MAP(CMaterialAddDialog)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CMaterialAddDialog::OnBnClickedOk)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMaterialAddDialog message handlers

void CMaterialAddDialog::OnOK() 
{
	// TODO: Add extra validation here
	CString materialName, materialID, materialBatchNumber, materialManufacture;
	
	m_MaterialID.GetWindowText(materialID);
	m_MaterialName.GetWindowText(materialName);
	m_BatchNumber.GetWindowText(materialBatchNumber);
	m_Manufacture.GetWindowText(materialManufacture);
	
	if (materialID.IsEmpty() || materialName.IsEmpty())
	{
		CString msg("���ϱ�ţ���������Ϊ����ѡ�");
		AfxMessageBox(msg);
		return;
	}
///���ӳ��̿�ʼ

	//���ӳ���
	RecordSetPointer::getInstanceRef().setSqlState(CString("SELECT * FROM MANUFACTURES"));

	try
	{
		RecordSetPointer::getInstanceRef().execSQL() ;
	}
	catch (_com_error& e)
	{
		AfxMessageBox("�������Ѿ����ڣ���������Ƿ���");
		return;
	}

	_RecordsetPtr& m_pRecordset = RecordSetPointer::getInstanceRef().getRecordPtr();	
	
	try
	{
		if (!m_pRecordset->adoEOF)
		{
			m_pRecordset->MoveLast();
		}
		m_pRecordset->AddNew();
		m_pRecordset->PutCollect("BATCHNUMBER", _variant_t(materialBatchNumber));
		m_pRecordset->PutCollect("MATERIALNAME", _variant_t(materialName));
		m_pRecordset->PutCollect("MANUFACTURE", _variant_t(materialManufacture));
	}
	catch(_com_error &e)
	{
		AfxMessageBox("�����ظ����������ţ��Լ���Ӧ����������");
		return;
	}

	//�������ݿ�
	try
	{
		m_pRecordset->Update();
	}
	catch(_com_error &e)
	{
		AfxMessageBox("�����ظ����������ţ��Լ���Ӧ����������");
		return;
	}
///	���ӳ������

	///���Ӳ��Ͽ�ʼ
	//init recordset pointer
	RecordSetPointer::getInstanceRef().setSqlState(CString("SELECT * FROM MATERIALS"));

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

	//get the result data set
	m_pRecordset = RecordSetPointer::getInstanceRef().getRecordPtr();

	try
	{
		if (!m_pRecordset->adoEOF)
		{
			m_pRecordset->MoveLast();
		}
		m_pRecordset->AddNew();
		m_pRecordset->PutCollect("ID", _variant_t(materialID));
		m_pRecordset->PutCollect("NAME", _variant_t(materialName));
		m_pRecordset->PutCollect("BATCHNUMBER", _variant_t(materialBatchNumber));
		m_pRecordset->PutCollect("MANUFACTURE", _variant_t(materialManufacture));
	}
	catch(_com_error &e)
	{
		AfxMessageBox(e.Description());
		return;
	}
	


	//�������ݿ�
	try
	{
		m_pRecordset->Update();
	}
	catch(_com_error &e)
	{
		AfxMessageBox(e.Description());
		return;
	}
//���Ӳ������

	m_MaterialManageWindow->m_MaterialList.DeleteAllItems();
	m_MaterialManageWindow->initList();

	CDialog::OnOK();
}

BOOL CMaterialAddDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	CBitmap   bmp;   
	bmp.LoadBitmap(IDB_MATERIALCOUNTINPUT);//����ͼƬ   
	m_brBk.CreatePatternBrush(&bmp); 
	bmp.DeleteObject();   

	CRect wndRect((1024 - 640) / 2, (768 - 385) / 2, (1024 - 640) / 2 + 640, (768 - 385) / 2 + 400);
	this->MoveWindow(wndRect);

	CRect okRect(404, 339, 503, 374);
	CRect cancelRect(520, 339, 618, 374);

	m_ButtonOK.MoveWindow(okRect);

	m_ButtonCancel.MoveWindow(cancelRect);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

CMaterialAddDialog::~CMaterialAddDialog()
{

}
void CMaterialAddDialog::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	OnOK();
}

HBRUSH CMaterialAddDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here
	if   (pWnd == this)   
	{   
		return m_brBk;   
	}   
	if   (nCtlColor   ==   CTLCOLOR_STATIC)   
	{     
		pDC->SetBkMode(TRANSPARENT);	//͸��   
		return (HBRUSH)::GetStockObject(HOLLOW_BRUSH);   
	}  
	// TODO:  Return a different brush if the default is not desired
	return hbr;
}
