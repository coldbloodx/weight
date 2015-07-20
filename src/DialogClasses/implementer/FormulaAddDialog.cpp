//. FormulaAddDialog.cpp : implementation file
//

#include "stdafx.h"
#include "..\..\Weight.h"
#include "..\..\DialogClasses\header\FormulaAddDialog.h"
#include "..\..\DialogClasses\header\FormulaDialog.h"
#include "..\..\OtherClasses\HelperClass.h"
#include <numeric>
#include <functional>
#include "..\..\OtherClasses\DatabaseConnector.h"
#include "..\..\OtherClasses\RecordSetPointer.h"
#include "..\..\OtherClasses\uiFunctions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFormulaAddDialog dialog


CFormulaAddDialog::CFormulaAddDialog(CWnd* pParent /*=NULL*/)
: CDialog(CFormulaAddDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFormulaAddDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CFormulaAddDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFormulaAddDialog)
	//DDX_Control(pDX, IDC_STATUSSTATIC1111, m_StatusStatic);
	DDX_Control(pDX, IDOK, m_ButtonOK);
	DDX_Control(pDX, IDCANCEL, m_ButtonCancel);
	//DDX_Control(pDX, IDC_PERCENTAGESECOND_STATIC, m_PercentageSecond);
	//DDX_Control(pDX, IDC_MATERIALSECOND_STATIC, m_MaterialSecond);
	DDX_Control(pDX, IDC_FORMULANAME_EDIT, m_FormulaName);
	DDX_Control(pDX, IDC_FORMULAID_EDIT, m_FormulaID);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFormulaAddDialog, CDialog)
//{{AFX_MSG_MAP(CFormulaAddDialog)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CFormulaAddDialog::OnBnClickedOk)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFormulaAddDialog message handlers

void CFormulaAddDialog::OnOK() 
{
	// TODO: Add extra validation here
	CString formulaID;
	m_FormulaID.GetWindowText(formulaID);
	
	CString formulaName;
	m_FormulaName.GetWindowText(formulaName);
	
	if (formulaID.IsEmpty() || formulaName.IsEmpty())
	{
		AfxMessageBox("配方编号和配方名字为必填选项！");
		return;
	}
	
	int id = atoi(formulaID.GetBuffer(0));
	if (id > 32767)
	{
		AfxMessageBox("配方编号不能超过32767！");
		return;
	}

	CString formulaMaterials;
	CString materialName;
	CString materialRatio;
	
	std::vector<double> doubleVector;
	std::vector<CString> nameVector;
	double tempDouble;
	for (size_t i = 0; i < comboboxVector.size(); ++i)
	{
		comboboxVector[i]->GetWindowText(materialName);
		formulaMaterials += materialName + ",";
		nameVector.push_back(materialName);
		if (!HelperFunctions::isDouble(editVector[i]))
		{
			AfxMessageBox("请检查材料百分比输入！");
			return;
		}
		editVector[i]->GetWindowText(materialRatio);
		tempDouble = atof(materialRatio.GetBuffer(materialRatio.GetLength()));
		if (tempDouble != 0.0)
		{
			doubleVector.push_back(tempDouble);
		}
		else
		{
			AfxMessageBox("数据转换出错，请检查材料百分比输入！");
			return;
		}
		formulaMaterials += materialRatio + ";";
	}
	
	std::vector<CString>::iterator it = std::unique(nameVector.begin(), nameVector.end());
	if (it != nameVector.end())
	{
		AfxMessageBox("材料有重复，请检查！");
		return;
	}

	double percentage = 0;
	percentage = std::accumulate(doubleVector.begin(), doubleVector.end(), 0.0);
	
	//为了东睦增加搞笑配方，配料总和能超过100%，晕
	//if (percentage > (double)(100) || percentage < (double)(100))
	//{
	//	AfxMessageBox("配料百分比有误，请检查材料百分比输入！");
	//	return;
	//}

	RecordSetPointer::getInstanceRef().setSqlState(CString("SELECT * FROM FORMULAS"));

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
	_RecordsetPtr& m_pRecordset = RecordSetPointer::getInstanceRef().getRecordPtr();
	
	try
	{
		if (!m_pRecordset->adoEOF)
		{
			m_pRecordset->MoveLast();
		}
		
		m_pRecordset->AddNew();
		m_pRecordset->PutCollect("ID", _variant_t(formulaID));
		m_pRecordset->PutCollect("NAME", _variant_t(formulaName));
		m_pRecordset->PutCollect("MATERIAL", _variant_t(formulaMaterials));
		
	}
	catch(_com_error &e)
	{
		AfxMessageBox(e.Description());
		return;
	}
	
	//更新数据库
	try
	{
		m_pRecordset->Update();
	}
	catch(_com_error& e)
	{
		e;
	}

	CFormulaDialog *formulaDialog = (CFormulaDialog *)(SingletonHelper::getInstance()->getPtrData());
	formulaDialog->m_FormulaListCtrl.DeleteAllItems();
	formulaDialog->initList();
	CDialog::OnOK();
}

BOOL CFormulaAddDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	//HelperFunctions::showStatus(m_StatusStatic);
	SetTimer(1000,1000,NULL);
	
	CBitmap   bmp;   
	bmp.LoadBitmap(IDB_FORMULAADD);//载入图片   
	m_brBk.CreatePatternBrush(&bmp); 
	bmp.DeleteObject();   

	CRect wndRect((1024 - 960) / 2, (768 - 695) / 2, (1024 - 960) / 2 + 960, (768 - 695) / 2 + 710);
	this->MoveWindow(wndRect);

	CRect okRect(681, 643,783, 679);
	CRect cancelRect(801, 643, 903, 679);

	m_ButtonOK.MoveWindow(okRect);
	m_ButtonCancel.MoveWindow(cancelRect);

	buttonVector.push_back(&m_ButtonCancel);
	buttonVector.push_back(&m_ButtonOK);


	
	queryMaterials();
	
	int mCount = this->materialCount;
	// TODO: Add extra initialization here
	int comboboxID = 1000;
	
	int comboLeft = 50;
	int comboTop = 100;
	int comboWidth =170;
	int comboBottom = 330;
	
	int editHeigh = 24;
	int editWidth = 100;
	int editID = 2000;
	int editLeft = 250;
	int editTop = 100;
	
	for(int i = 0; i < mCount ; ++i)
	{
		CString mTitle, pTitle;
		mTitle = (i >= 10) ? "材料名" : "";
		pTitle = (i >= 10) ? "百分比" : "";

		//m_MaterialSecond.SetWindowText(mTitle);
		//m_PercentageSecond.SetWindowText(pTitle);

		if (i == 10)
		{
			comboLeft = 400;
			editLeft = 620;
			comboTop = 100;
			editTop = 100;
		}
		
		CComboBox* testCombox = new CComboBox;
		testCombox->Create(CBS_DROPDOWNLIST|WS_VISIBLE |WS_VSCROLL ,
			CRect(comboLeft,comboTop,comboLeft + comboWidth,comboBottom), 
			this, 
			comboboxID++);
		
		for (size_t j = 0; j < materialVector.size(); ++j)
		{
			testCombox->AddString(materialVector[j]);
		}
		testCombox->SetCurSel(0);
		testCombox->ShowWindow(SW_SHOW);
		comboboxVector.push_back(testCombox);
		
		CEdit* testEdit = new CEdit;
		testEdit->CreateEx(WS_EX_CLIENTEDGE,   
			"Edit",   
			"",   
			WS_CHILD|WS_VISIBLE|ES_LEFT,   
			CRect(editLeft,editTop,editLeft + editWidth,editTop + editHeigh),   
			this,   
			editID);
		testEdit->ShowWindow(SW_SHOW);
		editVector.push_back(testEdit);

		comboTop += 50;
		comboBottom += 50;
		editTop += 50;
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

CFormulaAddDialog::~CFormulaAddDialog()
{
	if (comboboxVector.empty() || editVector.empty())
	{
		return;
	}
	
	for (size_t i = 0; i < comboboxVector.size(); ++i)
	{
		delete comboboxVector[i];
		comboboxVector[i] = NULL;
		delete editVector[i];
		editVector[i] = NULL;
	}
	
	comboboxVector.clear();
	editVector.clear();
}


void CFormulaAddDialog::queryMaterials()
{
	RecordSetPointer::getInstanceRef().setSqlState(CString("SELECT NAME FROM MATERIALS"));

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
	_RecordsetPtr& recordSetPtr = RecordSetPointer::getInstanceRef().getRecordPtr();

	try
	{
		_variant_t vName;
		while(!recordSetPtr->adoEOF)
		{
			vName = recordSetPtr->GetCollect("NAME");
			
			CString name;
			if (vName.vt != VT_NULL)
			{
				name =(LPCTSTR)(_bstr_t)vName;
			}
			
			materialVector.push_back(name);
			recordSetPtr->MoveNext();
		}
	}
	catch(_com_error &e)
	{
		AfxMessageBox(e.Description());
		return;
	}
}

void CFormulaAddDialog::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	//HelperFunctions::showStatus(m_StatusStatic);
	CDialog::OnTimer(nIDEvent);
}

void CFormulaAddDialog::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	OnOK();
}

HBRUSH CFormulaAddDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
