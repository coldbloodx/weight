//. FormulaAddDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Weight.h"
#include "FormulaAddDialog.h"
#include "FormulaDialog.h"
#include "HelperClass.h"
#include <numeric>
#include <functional>
#include "DBConnector.h"
#include "DBptr.h"
#include "uiFunctions.h"

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
}


void CFormulaAddDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_ButtonOK);
	DDX_Control(pDX, IDCANCEL, m_ButtonCancel);
	DDX_Control(pDX, IDC_FORMULANAME_EDIT, m_FormulaName);
	DDX_Control(pDX, IDC_FORMULAID_EDIT, m_FormulaID);
}


BEGIN_MESSAGE_MAP(CFormulaAddDialog, CDialog)
	ON_BN_CLICKED(IDOK, &CFormulaAddDialog::OnBnClickedOk)
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
		if (!utils::isdouble(editVector[i]))
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
	
	//为了东睦增加搞笑配方，配料总和能超过100%
	//if (percentage > (double)(100) || percentage < (double)(100))
	//{
	//	AfxMessageBox("配料百分比有误，请检查材料百分比输入！");
	//	return;
	//}

	CString sql;
	sql.Format("insert into formulas(id, name, material) values (%s, '%s', '%s') ", formulaID, formulaName, formulaMaterials);

	//get the result data set
	SQLExecutor::getInstanceRef().execquery(sql);


	CFormulaDialog *formulaDialog = (CFormulaDialog *)(SingletonHelper::getInstance()->getPtrData());
	formulaDialog->m_FormulaListCtrl.DeleteAllItems();
	formulaDialog->initList();
	CDialog::OnOK();
}

BOOL CFormulaAddDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();

    uiutils::setdlgsize(this, &m_ButtonCancel, &m_ButtonOK);

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
			CRect(comboLeft,comboTop,comboLeft + comboWidth,comboBottom),  this, comboboxID++);
		
		for (size_t j = 0; j < materialVector.size(); ++j)
		{
			testCombox->AddString(materialVector[j]);
		}

		testCombox->SetFont(SingletonHelper::getInstance()->defaultFont, TRUE);
		testCombox->SetCurSel(0);
		testCombox->ShowWindow(SW_SHOW);
		comboboxVector.push_back(testCombox);
		
		CEdit* testEdit = new CEdit;
		testEdit->CreateEx(WS_EX_CLIENTEDGE, "Edit", "", WS_CHILD|WS_VISIBLE|ES_LEFT,   
			CRect(editLeft,editTop,editLeft + editWidth,editTop + editHeigh), this, editID);
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
	//get the result data set
	_RecordsetPtr& recordSetPtr = SQLExecutor::getInstanceRef().execquery("select name from materials");

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

void CFormulaAddDialog::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	OnOK();
}