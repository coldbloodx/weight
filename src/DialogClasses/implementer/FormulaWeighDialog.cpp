// For mulaWeighDialog.cpp : implementation file

#include "stdafx.h"
#include "Weight.h"
#include "FormulaWeighDialog.h"
#include "FormulaSepWeighDialog.h"
#include "HelperClass.h"
#include "DatabaseConnector.h"
#include "RecordSetPointer.h"
#include "uiFunctions.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFormulaWeighDialog dialog


CFormulaWeighDialog::CFormulaWeighDialog(CWnd* pParent /*=NULL*/)
: CDialog(CFormulaWeighDialog::IDD, pParent),totalWeigh(0.0),m_FocusedID(0)
{
	//{{AFX_DATA_INIT(CFormulaWeighDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CFormulaWeighDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_ButtonOK);
	DDX_Control(pDX, IDC_MISSION_STATIC, m_MissionStatic);
	DDX_Control(pDX, IDCANCEL, m_ButtonCancel);
	DDX_Control(pDX, IDC_BUTTON9, m_Button9);
	DDX_Control(pDX, IDC_BUTTON8, m_Button8);
	DDX_Control(pDX, IDC_BUTTON7, m_Button7);
	DDX_Control(pDX, IDC_BUTTON6, m_Button6);
	DDX_Control(pDX, IDC_BUTTON5, m_Button5);
	DDX_Control(pDX, IDC_BUTTON4, m_Button4);
	DDX_Control(pDX, IDC_BUTTON3, m_Button3);
	DDX_Control(pDX, IDC_BUTTON2, m_Button2);
	DDX_Control(pDX, IDC_BUTTON1, m_Button1);
	DDX_Control(pDX, IDC_BUTTON0, m_Button0);
	DDX_Control(pDX, IDC_BUTTON_COMMA, m_ButtonComma);
	DDX_Control(pDX, IDC_BUTTON_BACK, m_ButtonBack);
	DDX_Control(pDX, IDC_WEIGHT_STATIC, m_WeightStatic);
	DDX_Control(pDX, IDC_PRINTERCHECK, m_PrintCheck);
}


BEGIN_MESSAGE_MAP(CFormulaWeighDialog, CDialog)
//{{AFX_MSG_MAP(CFormulaWeighDialog)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_BN_CLICKED(IDC_BUTTON5, OnButton5)
	ON_BN_CLICKED(IDC_BUTTON6, OnButton6)
	ON_BN_CLICKED(IDC_BUTTON7, OnButton7)
	ON_BN_CLICKED(IDC_BUTTON8, OnButton8)
	ON_BN_CLICKED(IDC_BUTTON9, OnButton9)
	ON_BN_CLICKED(IDC_BUTTON0, OnButton0)
	ON_BN_CLICKED(IDC_BUTTON_COMMA, OnButtonComma)
	ON_BN_CLICKED(IDC_BUTTON_BACK, OnButtonBack)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDOK, &CFormulaWeighDialog::OnBnClickedOk)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFormulaWeighDialog message handlers

//在对话框的初始函数中做一些空间的创建工作
BOOL CFormulaWeighDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	//HelperFunctions::showStatus(m_StatusStatic);
	// TODO: Add extra initialization here
	std::vector<std::string> materialVector;
	std::string separator(",;");

	HelperFunctions::ParseKeywords(
	SingletonHelper::getInstance()->getMaterials(),
		separator,
		materialVector);

	
	totalWeigh = atof(SingletonHelper::getInstance()->getFormulaWeigh().GetBuffer(SingletonHelper::getInstance()->getFormulaWeigh().GetLength()));
	
	m_MissionStatic.SetWindowText(SingletonHelper::getInstance()->getFormulaName());



	m_WeightStatic.SetWindowText(SingletonHelper::getInstance()->getFormulaWeigh() + "公斤");

	composition *tempComposition = NULL;
	CString manufacture;
	for (size_t i = 0; i < (materialVector.size() / 2); ++i)
	{
		tempComposition = new composition;
		tempComposition->material = materialVector[i*2];
		CString tempMaterialName(materialVector[i*2].c_str()) ;
		
		//这里取出材料的条码，并放到条码容器中（lineNumberOld）
		CString sqlState("SELECT BATCHNUMBER,MANUFACTURE FROM MATERIALS WHERE NAME = '");
		sqlState += tempMaterialName + "'";
		
		RecordSetPointer::getInstanceRef().setDatabaseConnection(DBConnector::getInstanceRef().getdbcon());
		RecordSetPointer::getInstanceRef().setSqlState(sqlState);

		CString oldLineNumber;
		try
		{
			RecordSetPointer::getInstanceRef().execSQL() ;
		}
		catch (_com_error& e)
		{
			AfxMessageBox(e.Description());
		}
		_RecordsetPtr& m_pRecordset = RecordSetPointer::getInstanceRef().getRecordPtr();

		try
		{
			while(!m_pRecordset->adoEOF)
			{
				_variant_t vDataField = m_pRecordset->GetCollect(_variant_t("BATCHNUMBER"));
				_variant_t vManufacture = m_pRecordset->GetCollect(_variant_t("MANUFACTURE"));
				if (vDataField.vt != VT_NULL)
				{
					oldLineNumber = (LPCTSTR)(_bstr_t)vDataField;
				}
				lineNumberOld.push_back(oldLineNumber);
				if(vManufacture.vt != VT_NULL)
				{
					manufacture = (LPCTSTR)(_bstr_t)vManufacture;
				}
				manufactures.push_back(manufacture);
				m_pRecordset->MoveNext();
			}
		}
		catch (_com_error& e)
		{
			throw e;
		}
		//取出条码完毕

		std::string percentage = materialVector[i*2+1];
		tempComposition->percentage = atof(percentage.c_str());
		tempComposition->isWeigh = FALSE;
		if (tempComposition)
		{
			SingletonHelper::getInstance()->compositions.push_back(tempComposition);
		}
		else
		{
			AfxMessageBox("称量出错！请返回重试！");
			return FALSE;
		}
		tempComposition = NULL;
	}
	
	int materialNameStaticID = 10000;
	int materialWeighStaticID = 20000;
	int weighButtonID = 30000;
	int sepWeighButtonID = 40000;
	int materialWeighedFlagID = 50000;
	int batchNumberEditID = 60000;
	int lineNumberEditID = 61000;
	
	int controlTop = 150;
	int controlLeft = 80;
	int controlWidth = 150;
	int controlHeight = 25;
	int rowSpace = 10;
    
	int nameWidth = 50;
	int weightWidth = 120;
	int buttonWidth = 60;
	int flagWidth = 90;
	int editWidth = 250;
    int splitorWidth = 3;
	
	CRect rect(controlLeft, controlTop, (controlLeft + nameWidth), (controlTop + controlHeight) );
	for (size_t j = 0; j < SingletonHelper::getInstance()->compositions.size(); ++j)
	{
		CStatic* materialNameStatic = NULL;
		CStatic* materialWeighStatic = NULL;
		CButton* sepWeightButton = NULL;
		CStatic* weighedFlagStatic = NULL;
		CEdit*   batchNumberEdit = NULL;
		CEdit*   lineNumberEdit = NULL;

		
		//创建材料名字static控件
		materialNameStatic = new CStatic;
		SingletonHelper* sPointer =NULL;
		sPointer	= SingletonHelper::getInstance();
		composition newComposition = *(sPointer->compositions[j]);

		materialNameStatic->Create(newComposition.material.c_str(),
			WS_VISIBLE | ES_CENTER,
			rect,
			this,
			materialNameStaticID++);
		//materialNameStatic->SetFont(SingletonHelper::getInstance()->simSong20);
		materialNameStatic->ShowWindow(SW_SHOW);
		materialNameVector.push_back(materialNameStatic);
		
		//调整控件位置
		rect.left = controlLeft + nameWidth + splitorWidth;
		rect.right = rect.left + weightWidth + splitorWidth;
		

		//创建材料重量static控件
		materialWeighStatic = new CStatic;
		//std::string test(gcvt((newComposition.percentage * totalWeigh / 100), 8, buffer));
		CString test1 = HelperFunctions::doubleToCString(newComposition.percentage * totalWeigh / 100);
		test1 += "Kg";
		materialWeighStatic->Create(test1,
			WS_VISIBLE | ES_CENTER,
			rect,
			this,
			materialWeighStaticID++);
		//materialWeighStatic->SetFont(SingletonHelper::getInstance()->simSong20);
		materialWeighStatic->ShowWindow(SW_SHOW);
		materialWeighVector.push_back(materialWeighStatic);
		
		//调整控件位置
		rect.left = rect.right + 2;
		rect.right = rect.left + buttonWidth + splitorWidth;
		
		//创建分次称量按钮
		CRect buttonRect = rect;

		sepWeightButton = new CButton;
		sepWeightButton->Create("", 
			BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD | ES_CENTER, 
			buttonRect, 
			this,  
			sepWeighButtonID++);


		//HelperFunctions::setButtonStyle(*sepWeightButton, RGB(55,71,158), SingletonHelper::getInstance()->simSong20);
        sepWeightButton->SetWindowText("称重");
		sepWeightButton->ShowWindow(SW_SHOW);
		sepWeightButtonVector.push_back(sepWeightButton);
		
		//调整控件位置
		rect.left = rect.right + splitorWidth;
		rect.right =  rect.left  + flagWidth + splitorWidth;
		
		//创建称量标志
		weighedFlagStatic = new CStatic;
		CString weighedFlag;
		
		weighedFlag = newComposition.material == "其他" ? "已称重" : "未称重";
		
		if (sPointer->compositions[j]->material == "其他")
		{
			sPointer->compositions[j]->isWeigh = TRUE;
		}

		weighedFlagStatic->Create(weighedFlag,
			WS_VISIBLE | ES_CENTER,
			rect,
			this,
			materialWeighedFlagID++);
		weighedFlagStatic->ShowWindow(SW_SHOW);
		weighedFlagVector.push_back(weighedFlagStatic);
		
		//调整控件位置
		rect.left = rect.right + splitorWidth ;
		rect.right = rect.left + editWidth / 2 - splitorWidth;
		
		//创建批号输入editbox
		CRect batchNumerRect(rect);
		//batchNumerRect.right += 150;
		batchNumberEdit = new CEdit;
		batchNumberEdit->CreateEx(
			WS_EX_CLIENTEDGE,
			"Edit",
			"",
			WS_VISIBLE | WS_CHILD | ES_LEFT ,
			batchNumerRect,
			this,
			batchNumberEditID++);
		batchNumberEdit->ShowWindow(SW_SHOW);
		batchNumberEditVector.push_back(batchNumberEdit);
		
		//创建条码输入editbox
		rect.left = rect.right + splitorWidth;
		rect.right = rect.left + editWidth / 2 ;
		
		CRect lineNumerRect(rect);
		//batchNumerRect.right += 150;
		lineNumberEdit = new CEdit;
		lineNumberEdit->CreateEx(
			WS_EX_CLIENTEDGE,
			"Edit",
			"",
			WS_VISIBLE | WS_CHILD | ES_LEFT ,
			lineNumerRect,
			this,
			lineNumberEditID++);
		lineNumberEdit->ShowWindow(SW_SHOW);
		lineNumberEditVector.push_back(lineNumberEdit);

		//调整两行之间的间隔
		rect.left = controlLeft;
		rect.right = controlLeft + nameWidth;
		
		rect.top += rowSpace + controlHeight;
		rect.bottom += rowSpace + controlHeight;
	}
	
	CButton* buttonArray[14] = {&m_Button1,&m_Button2,&m_Button3,&m_Button4,&m_Button5,&m_Button6,&m_Button7,
		&m_Button8,&m_Button9,&m_Button0,&m_ButtonComma,&m_ButtonBack,&m_ButtonOK,&m_ButtonCancel};


	std::vector<CButton*> buttonVector(buttonArray, buttonArray+14);
	uiFunctions::setdlgsize(this, &m_ButtonCancel, &m_ButtonOK);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

//对话框析构函数，用来做一些清理工作
CFormulaWeighDialog::~CFormulaWeighDialog()
{
	if (!materialWeighVector.empty())
	{
		for (size_t i = 0; i < materialWeighVector.size(); ++i)
		{
			delete materialWeighVector[i];
			materialWeighVector[i] = NULL;
			delete materialNameVector[i];
			materialNameVector[i] = NULL;
			delete sepWeightButtonVector[i];
			sepWeightButtonVector[i] = NULL;
			delete weighedFlagVector[i];
			weighedFlagVector[i] = NULL;
			delete batchNumberEditVector[i];
			batchNumberEditVector[i] = NULL;
			delete lineNumberEditVector[i];
			lineNumberEditVector[i] = NULL;
		}
	}
}

//用来相应动态创建的按钮的消息
BOOL CFormulaWeighDialog::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	//这里处理动态创建的按钮！
	int constrolID =LOWORD(wParam);
	TRACE("controlID: %d \n", constrolID);
	SingletonHelper::getInstance()->setPtrData((void*)this);
	if (constrolID >= 40000 && constrolID <50000)
	{
		if (SingletonHelper::getInstance()->compositions[constrolID - 40000]->isWeigh  == TRUE)
		{
			AfxMessageBox("注意：这种材料已经称量过!!");
		}

		int nVectorIndex = constrolID - 40000;
		CString batchNumber, lineNumber;
		batchNumberEditVector[nVectorIndex]->GetWindowText(batchNumber);
		lineNumberEditVector[nVectorIndex]->GetWindowText(lineNumber);
		if (batchNumber.IsEmpty() || lineNumber.IsEmpty())
		{
			AfxMessageBox("批号，或者条码为空！");
			return true;
		}
		if (lineNumber != lineNumberOld[nVectorIndex])
		{
			AfxMessageBox("条码不匹配，请检查条码输入");
			return true;
		}
		SingletonHelper::getInstance()->setIntData(constrolID - 40000);
		SingletonHelper::getInstance()->setLineNumber(lineNumber);
		CFormulaSepWeighDialog formulaSepWeighDialog;
		formulaSepWeighDialog.DoModal();
	}
	if (constrolID >= 60000 && constrolID < 61000)
	{
		m_FocusedID = constrolID;
	}
	if (constrolID >= 61000)
	{
		m_FocusedID = constrolID;
	}
	return CDialog::OnCommand(wParam, lParam);
}

//处理对话框的ok按钮，这一部分逻辑比较复杂，验证的内容比较多，要注意
void CFormulaWeighDialog::OnOK() 
{
	// TODO: Add extra validation here
	//首先判断批号输入的合法性，如果批号输入不合法，则直接退出到称量界面。
	CString batchNumber;
	std::vector<CString> batchNumberVector;

	CString lineNumber;
	std::vector<CString> lineNumberVector;


	for (size_t i = 0; i < batchNumberEditVector.size(); ++i)
	{
		//输入批号验证
		batchNumberEditVector[i]->GetWindowText(batchNumber);
		if (batchNumber.IsEmpty() || !HelperFunctions::isBatchNumber(batchNumberEditVector[i]))
		{
			batchNumberVector.clear();
			AfxMessageBox("批号只能是数字和逗号的组合");
			return;
		}
		batchNumberVector.push_back(batchNumber);
		//输入批号验证结束

		//输入条码验证
		lineNumberEditVector[i]->GetWindowText(lineNumber);
		if (lineNumber.IsEmpty())
		{
			lineNumberVector.clear();
			AfxMessageBox("条码输入有错，请检查！");
			return;
		}
		if (lineNumber != lineNumberOld[i] )
		{
			AfxMessageBox("第"+HelperFunctions::intToCString(i+1)+"个材料的条码不匹配，请检查！");
		}
		lineNumberVector.push_back(lineNumber);
		//输入条码验证结束
	}
	
	//判断称量的完成情况，如果称量没有完成则直接放弃称量结果
	bool isFinished = isWeighFinished();
	if (!isFinished)
	{
		//清空称量过程中的临时数据。
		AfxMessageBox("注意！称量过程没有完成！");
		return;
	}
	
	//将称量的结果存入输入据库，两个部分，
	//称量记录存到历史记录表里面，
	//另外要更新配方表中的成品重量
	
	//首先取得系统时间
	CTime currentTime = CTime::GetCurrentTime();
	CString date = currentTime.Format("%Y-%m-%d");
	CString time = currentTime.Format("%X");
	
	CString comment,tempMaterialName,tempMaterialBatchNumer,separator;

	SingletonHelper* sPointer =NULL;
	sPointer	= SingletonHelper::getInstance();

	for (size_t k = 0; k < materialNameVector.size(); ++k)
	{

		composition newComposition = *(sPointer->compositions[k]);
		tempMaterialName = newComposition.material.c_str();
		separator = ((materialNameVector.size() - k) == 1) ? "" : ";";
		comment += tempMaterialName + "," +batchNumberVector[k] +"," +lineNumberVector[k]+ "," + manufactures[k] + separator;
	}

	//下面开始处理数据，完成一个一个表的数据插入，一个表的数据修改。	
	//首先修改配方表，将配方的成品量增加。

	//增加成品的SQL语句	
	CString sqlState("UPDATE FORMULAS SET TOTAL = TOTAL + ");
	sqlState +=  SingletonHelper::getInstance()->getFormulaWeigh() + " WHERE ID = " + SingletonHelper::getInstance()->getFormulaID() ;
	
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

	//get the result data set
	_RecordsetPtr& m_pRecordset = RecordSetPointer::getInstanceRef().getRecordPtr();

	//init recordset pointer
	RecordSetPointer::getInstanceRef().setSqlState(CString("SELECT * FROM WEIGHT"));

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

	CString weighID;

 	try
 	{
 		if (! m_pRecordset->adoEOF)
 		{		
 			m_pRecordset->MoveLast();
 		}

		 m_pRecordset->AddNew();
		_variant_t ID = m_pRecordset->GetCollect(_variant_t("ID"));
		if (ID.vt != VT_NULL)
		{
			weighID = (LPCTSTR)(_bstr_t)ID;
		}

 		m_pRecordset->PutCollect("FORMULAID", _variant_t(SingletonHelper::getInstance()->getFormulaID()));
 		m_pRecordset->PutCollect("FORMULANAME", _variant_t(SingletonHelper::getInstance()->getFormulaName()));
 		m_pRecordset->PutCollect("USERID", _variant_t(SingletonHelper::getInstance()->getUserID()));
 		m_pRecordset->PutCollect("USERNAME", _variant_t(SingletonHelper::getInstance()->getUsername()));
 		m_pRecordset->PutCollect("AMOUNT",_variant_t(SingletonHelper::getInstance()->getFormulaWeigh()));
 		m_pRecordset->PutCollect("DATE", _variant_t(date));
 		m_pRecordset->PutCollect("TIME", _variant_t(time));
 		m_pRecordset->PutCollect("COMMENT", _variant_t(comment));
 	}
 	catch(_com_error &e)
 	{
 		AfxMessageBox(e.Description());
		SingletonHelper::getInstance()->clearCompositions();
		return;
 	}
 	
 	//更新数据库
 	try
 	{
 		m_pRecordset->Update();	
 	}
 	catch(_com_error &e)
 	{
 		AfxMessageBox("增加记录出现错误：" + e.Description());
		SingletonHelper::getInstance()->clearCompositions();
 		return;
 	}	

	if (m_PrintCheck.GetCheck())
	{
		printVector.push_back(weighID);
		printVector.push_back(SingletonHelper::getInstance()->getFormulaName());
		printVector.push_back(SingletonHelper::getInstance()->getFormulaWeigh() + "Kg");
		printVector.push_back(SingletonHelper::getInstance()->getUsername());
		printVector.push_back(date);
		printVector.push_back(time);
		printVector.push_back(CString(""));
		printVector.push_back(CString(""));

		CString headerArray[8] ={"生产批号:","配方名称:","称量重量:","用户姓名:","称重日期:","称重时间:","检验:","检验日期:"};
		std::vector<CString> headerList(headerArray, headerArray + 8);
		
		HelperFunctions::printVector(CString("山西东睦华晟混合粉"),headerList, printVector);

		printVector.clear();
	}

	//清空称量过程中的临时数据。
	SingletonHelper::getInstance()->clearCompositions();
	CDialog::OnOK();
}

//刷新各种材料的称重标志
void CFormulaWeighDialog::refreshWeighedFlag()
{
	CString weighedFlag("未称重");
	for (size_t i = 0; i < SingletonHelper::getInstance()->compositions.size(); ++i)
	{
		weighedFlag = SingletonHelper::getInstance()->compositions[i]->isWeigh ? "已称重" : "未称重";
		weighedFlagVector[i]->SetWindowText(weighedFlag);
		RECT rect;
		weighedFlagVector[i]->GetWindowRect(&rect);   
		weighedFlagVector[i]->GetParent()->ScreenToClient(&rect);
		weighedFlagVector[i]->GetParent()->InvalidateRect(&rect, TRUE);
	}
}


//检查是否称重完毕
bool CFormulaWeighDialog::isWeighFinished()
{
	for (size_t i = 0; i < SingletonHelper::getInstance()->compositions.size(); ++i)
	{
		if (SingletonHelper::getInstance()->compositions[i]->isWeigh == FALSE)
		{
			return FALSE;
		}
	}
	return true;
}

//处理对话框的cancel按钮
void CFormulaWeighDialog::OnCancel() 
{
	// TODO: Add extra cleanup here
	//给出提示，要不要放弃任务
	CString msg("您确定要放弃这次称重任务？");
	CString caption("放弃称重任务");
	//选择cancel则返回
	if (IDCANCEL == MessageBox(msg, caption, MB_OKCANCEL))
	{
		return;
	}
	//清空称重时所用的临时数据
	SingletonHelper::getInstance()->clearCompositions();
	CDialog::OnCancel();
}

void CFormulaWeighDialog::OnButton1() 
{
	// TODO: Add your control notification handler code here
	CWnd * pWnd = GetDlgItem(m_FocusedID);
	::SetFocus(pWnd->GetSafeHwnd());
	keybd_event(VK_NUMPAD1, 0, 0, 0);
}

void CFormulaWeighDialog::OnButton2() 
{
	// TODO: Add your control notification handler code here
	CWnd * pWnd = GetDlgItem(m_FocusedID);
	::SetFocus(pWnd->GetSafeHwnd());
	keybd_event(VK_NUMPAD2, 0, 0, 0);
}

void CFormulaWeighDialog::OnButton3() 
{
	// TODO: Add your control notification handler code here
	CWnd * pWnd = GetDlgItem(m_FocusedID);
	::SetFocus(pWnd->GetSafeHwnd());
	keybd_event(VK_NUMPAD3, 0, 0, 0);
}

void CFormulaWeighDialog::OnButton4() 
{
	// TODO: Add your control notification handler code here
	CWnd * pWnd = GetDlgItem(m_FocusedID);
	::SetFocus(pWnd->GetSafeHwnd());
	keybd_event(VK_NUMPAD4, 0, 0, 0);
}

void CFormulaWeighDialog::OnButton5() 
{
	// TODO: Add your control notification handler code here
	CWnd * pWnd = GetDlgItem(m_FocusedID);
	::SetFocus(pWnd->GetSafeHwnd());
	keybd_event(VK_NUMPAD5, 0, 0, 0);
}

void CFormulaWeighDialog::OnButton6() 
{
	// TODO: Add your control notification handler code here
	CWnd * pWnd = GetDlgItem(m_FocusedID);
	::SetFocus(pWnd->GetSafeHwnd());
	keybd_event(VK_NUMPAD6, 0, 0, 0);
}

void CFormulaWeighDialog::OnButton7() 
{
	// TODO: Add your control notification handler code here
	CWnd * pWnd = GetDlgItem(m_FocusedID);
	::SetFocus(pWnd->GetSafeHwnd());
	keybd_event(VK_NUMPAD7, 0, 0, 0);
}

void CFormulaWeighDialog::OnButton8() 
{
	// TODO: Add your control notification handler code here
	CWnd * pWnd = GetDlgItem(m_FocusedID);
	::SetFocus(pWnd->GetSafeHwnd());
	keybd_event(VK_NUMPAD8, 0, 0, 0);
}

void CFormulaWeighDialog::OnButton9() 
{
	// TODO: Add your control notification handler code here
	CWnd * pWnd = GetDlgItem(m_FocusedID);
	::SetFocus(pWnd->GetSafeHwnd());
	keybd_event(VK_NUMPAD9, 0, 0, 0);
}

void CFormulaWeighDialog::OnButton0() 
{
	// TODO: Add your control notification handler code here
	CWnd * pWnd = GetDlgItem(m_FocusedID);
	::SetFocus(pWnd->GetSafeHwnd());
	keybd_event(VK_NUMPAD0, 0, 0, 0);
}

void CFormulaWeighDialog::OnButtonComma() 
{
	// TODO: Add your control notification handler code here
	CWnd * pWnd = GetDlgItem(m_FocusedID);
	::SetFocus(pWnd->GetSafeHwnd());
	keybd_event(188, 0, 0, 0);
}

void CFormulaWeighDialog::OnButtonBack() 
{
	// TODO: Add your control notification handler code here
	CWnd * pWnd = GetDlgItem(m_FocusedID);
	::SetFocus(pWnd->GetSafeHwnd());
	keybd_event(VK_BACK, 0, 0, 0);
}
void CFormulaWeighDialog::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	//HelperFunctions::showStatus(m_StatusStatic);
	CDialog::OnTimer(nIDEvent);
}

HBRUSH CFormulaWeighDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here
	if   (pWnd   ==   this)   
	{   
		return   m_brBk;   
	}   

	if   (nCtlColor   ==   CTLCOLOR_STATIC)   
	{     
		if ( pWnd->GetDlgCtrlID() == IDC_WEIGHT_STATIC || pWnd->GetDlgCtrlID() == IDC_MISSION_STATIC  )
		{
			pDC->SetTextColor(RGB(255,0,0));
		}

		pDC->SetBkMode(TRANSPARENT);	//透明   
		return (HBRUSH)::GetStockObject(HOLLOW_BRUSH);   
	}   

	
	// TODO:  Return a different brush if the default is not desired
	return hbr;
}

void CFormulaWeighDialog::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	OnOK();
}

