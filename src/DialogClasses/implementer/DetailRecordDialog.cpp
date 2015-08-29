// DetailRecordDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Weight.h"
#include "DetailRecordDialog.h"
#include "HelperClass.h"
#include "DBConnector.h"
#include "DBptr.h"
#include "uifunctions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDetailRecordDialog dialog


CDetailRecordDialog::CDetailRecordDialog(CWnd* pParent /*=NULL*/)
: CDialog(CDetailRecordDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDetailRecordDialog)
	//}}AFX_DATA_INIT
}

void CDetailRecordDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDetailRecordDialog)
	DDX_Control(pDX, IDC_PRINT, m_Print);
	DDX_Control(pDX, IDC_STATUS_STATIC, m_StatusStatic);
	DDX_Control(pDX, IDOK, m_ButtonOK);
	DDX_Control(pDX, IDC_DATE_STATIC, m_Date);
	DDX_Control(pDX, IDC_FORMULAID_STATIC, m_FormulaID);
	DDX_Control(pDX, IDC_FORMULANAME_STATIC, m_FormulaName);
	DDX_Control(pDX, IDC_TIME_STATIC, m_Time);
	DDX_Control(pDX, IDC_USERNAME_STATIC, m_UserName);
	DDX_Control(pDX, IDC_USERID_STATIC, m_UserID);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDetailRecordDialog, CDialog)
//{{AFX_MSG_MAP(CDetailRecordDialog)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_PRINT, OnPrint)
	//}}AFX_MSG_MAP
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDetailRecordDialog message handlers

BOOL CDetailRecordDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
		
	CString sqlState("SELECT ID, FORMULAID, FORMULANAME, USERID, USERNAME, AMOUNT, DATE, TIME, COMMENT FROM weight WHERE ID = ");
	sqlState += SingletonHelper::getInstance()->getRecordID();
	
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
		return TRUE;
	}

	//get the result data set
	_RecordsetPtr& m_pRecordset = SQLExecutor::getInstanceRef().getRecordPtr();

	CString recordID, formulaID, formulaName, userID, userName, amount, date, time, comment;
	
	try
	{
		_variant_t vID, vFormulaID, vFormulaName, vUserID, vUserName, vAmount, vDate, vTime, vComment;
		
		
		
		int i=0;
		int nIndex = 0;
		
		int count = m_pRecordset->GetRecordCount();
		for (int j = 0; j < count; ++j)
		{
			vID = m_pRecordset->GetCollect("ID");
			vFormulaID = m_pRecordset->GetCollect("FORMULAID");
			vFormulaName = m_pRecordset->GetCollect("FORMULANAME");
			vUserID = m_pRecordset->GetCollect("USERID");
			vUserName = m_pRecordset->GetCollect("USERNAME");
			vAmount = m_pRecordset->GetCollect("AMOUNT");
			vDate = m_pRecordset->GetCollect("DATE");
			vTime = m_pRecordset->GetCollect("TIME");
			vComment = m_pRecordset->GetCollect("COMMENT");
			
			if (vID.vt != VT_NULL)
			{
				recordID = (LPCTSTR)(_bstr_t)vID;
			}
			
			if (vUserName.vt != VT_NULL)
			{
				userName = (LPCTSTR)(_bstr_t)vUserName;
			}
			
			if (vUserID.vt != VT_NULL)
			{
				userID =(LPCTSTR)(_bstr_t)vUserID;
			}
			
			if (vFormulaID.vt != VT_NULL)
			{
				formulaID = (LPCTSTR)(_bstr_t)vFormulaID;
			}
			
			if (vFormulaName.vt != VT_NULL)
			{
				formulaName = (LPCTSTR)(_bstr_t)vFormulaName;
			}
			
			if (vAmount.vt != VT_NULL)
			{
				amount = (LPCTSTR)(_bstr_t)vAmount;
			}
			
			if (vDate.vt != VT_NULL)
			{
				date = (LPCTSTR)(_bstr_t)vDate;
			}
			
			if (vTime.vt != VT_NULL)
			{
				time = (LPCTSTR)(_bstr_t)vTime;
			}
			
			if (vComment.vt != VT_NULL)
			{
				comment= (LPCTSTR)(_bstr_t)vComment;
			}
		}
	}
	catch(_com_error &e)
	{
		AfxMessageBox(e.Description());
		return TRUE;
	}
	
	//对上面查询的结果做处理
	m_FormulaID.SetWindowText(formulaID);
	m_FormulaName.SetWindowText(formulaName);
	
	m_UserID.SetWindowText(userID);
	m_UserName.SetWindowText(userName);
	
	m_Date.SetWindowText(date);
	m_Time.SetWindowText(time);
	
	std::string materials = comment.GetBuffer(0);
	std::string separators(";+");
	std::vector<std::string> keywords;
	
	HelperFunctions::ParseKeywords(materials, separators, keywords);
	
	int materialNameStaticID = 2000;
	int batchNumberStaticID = 3000;
	
	CStatic* pMaterialNameStatic = NULL;
	CStatic* pBatchNumberStatic = NULL;
	
	int controlTop = 150;
	int controlHeight = 25;
	int nameLeft = 80;
	int nameWidth = 70;
	int batchNumberLeft = 150;
	int batchNumberWidth = 250;
	
	int spacer = 15;
	for (size_t i = 0; i < keywords.size(); ++i)
	{
		std::string materialName, batchNumber, materialInfo;
		materialInfo = keywords[i];
		divideMaterialInfo(materialInfo, materialName, batchNumber);
		//AfxMessageBox((materialName.append(":")+batchNumber).c_str());
		
		pMaterialNameStatic = new CStatic;
		CRect nameRect(nameLeft, controlTop, nameLeft + nameWidth, controlTop + controlHeight);
		pMaterialNameStatic->Create(materialName.c_str(), WS_VISIBLE, nameRect, this, materialNameStaticID);
		pMaterialNameStatic->ShowWindow(SW_SHOW);
		materialNameVector.push_back(pMaterialNameStatic);
		TRACE("Vector size: %d \n", materialNameVector.size());
		
		pBatchNumberStatic = new CStatic;
		CRect batchNumberRect(batchNumberLeft, controlTop, batchNumberLeft + batchNumberWidth, controlTop + controlHeight);
		pBatchNumberStatic->Create(batchNumber.c_str(), WS_VISIBLE, batchNumberRect, this, batchNumberStaticID);
		pBatchNumberStatic->ShowWindow(SW_SHOW);
		batchNumberVector.push_back(pBatchNumberStatic);
		
		controlTop += controlHeight + spacer;
	}
	

	
	
	HelperFunctions::setButtonStyle(m_ButtonOK, RGB(55,71,158), SingletonHelper::getInstance()->simSong20);
	HelperFunctions::setButtonStyle(m_Print, RGB(55,71,158), SingletonHelper::getInstance()->simSong20);


	HelperFunctions::showStatus(m_StatusStatic);
    uiutils::setdlgsize(this);
	SetTimer(1000, 1000, NULL);
	return TRUE;  
	// return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDetailRecordDialog::divideMaterialInfo(std::string& materialInfo, std::string& materialName, std::string& batchNumber)
{
	size_t pos = materialInfo.find_first_of(',');
	for (size_t i = 0; i < materialInfo.size(); ++i)
	{
		if (i < pos)
		{
			materialName += materialInfo[i];
		}
		if (i > pos)
		{
			batchNumber += materialInfo[i];
		}
	}
}

CDetailRecordDialog::~CDetailRecordDialog()
{
	TRACE("Vector size: %d \n", materialNameVector.size());
	for (size_t i = 0; i < materialNameVector.size(); ++i)
	{
		delete materialNameVector[i];
		materialNameVector[i] = NULL;
		
		delete batchNumberVector[i];
		batchNumberVector[i] = NULL;
		
	}
	materialNameVector.clear();
	batchNumberVector.clear();
}

void CDetailRecordDialog::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
		HelperFunctions::showStatus(m_StatusStatic);
	CDialog::OnTimer(nIDEvent);
}

void CDetailRecordDialog::OnPrint() 
{
	// TODO: Add your control notification handler code here
	AfxMessageBox("目前功能没有实现！");
	return;
}

