// For mulaWeighDialog.cpp : implementation file

#include "stdafx.h"
#include "Weight.h"
#include "FormulaWeighDialog.h"
#include "FormulaSepWeighDialog.h"
#include "HelperClass.h"
#include "DBConnector.h"
#include "DBptr.h"
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
	DDX_Control(pDX, IDC_EDIT1, editFBNumber);
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
	ON_BN_CLICKED(IDOK, &CFormulaWeighDialog::OnBnClickedOk)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFormulaWeighDialog message handlers

//�ڶԻ���ĳ�ʼ��������һЩ�ռ�Ĵ�������
BOOL CFormulaWeighDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	//HelperFunctions::showStatus(m_StatusStatic);
	// TODO: Add extra initialization here
	std::vector<std::string> materialVector;
	std::string separator(",;");

	utils::ParseKeywords(SingletonHelper::getInstance()->getMaterials(), separator, materialVector);

	totalWeigh = atof(SingletonHelper::getInstance()->getFormulaWeigh().GetBuffer(SingletonHelper::getInstance()->getFormulaWeigh().GetLength()));
	
	m_MissionStatic.SetWindowText(SingletonHelper::getInstance()->getFormulaName());

	m_WeightStatic.SetWindowText(SingletonHelper::getInstance()->getFormulaWeigh() + "����");

	composition *tempComposition = NULL;
	CString manufacture;
	for (size_t i = 0; i < (materialVector.size() / 2); ++i)
	{
		tempComposition = new composition;
		tempComposition->material = materialVector[i*2];
		CString tempMaterialName(materialVector[i*2].c_str()) ;
		
		//����ȡ�����ϵ����룬���ŵ����������У�lineNumberOld��
		CString sqlState("SELECT BATCHNUMBER,MANUFACTURE FROM MATERIALS WHERE NAME = '");
		sqlState += tempMaterialName + "'";
		
		SQLExecutor::getInstanceRef().setDatabaseConnection(DBConnector::getInstanceRef().getdbcon());
		SQLExecutor::getInstanceRef().setSqlState(sqlState);

		CString oldLineNumber;
		try
		{
			SQLExecutor::getInstanceRef().execSQL() ;
		}
		catch (_com_error& e)
		{
			AfxMessageBox(e.Description());
		}
		_RecordsetPtr& m_pRecordset = SQLExecutor::getInstanceRef().getRecordPtr();

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
		//ȡ���������

		std::string percentage = materialVector[i*2+1];
		tempComposition->percentage = atof(percentage.c_str());
		tempComposition->isWeigh = FALSE;
		if (tempComposition)
		{
			SingletonHelper::getInstance()->compositions.push_back(tempComposition);
		}
		else
		{
			AfxMessageBox("���������뷵�����ԣ�");
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

		//������������static�ؼ�
		materialNameStatic = new CStatic;
		SingletonHelper* sPointer =NULL;
		sPointer	= SingletonHelper::getInstance();
		composition newComposition = *(sPointer->compositions[j]);

		materialNameStatic->Create(newComposition.material.c_str(),
			WS_VISIBLE | ES_CENTER,
			rect,
			this,
			materialNameStaticID++);
		materialNameStatic->ShowWindow(SW_SHOW);
		materialNameVector.push_back(materialNameStatic);
		
		dbmname.push_back(newComposition.material.c_str());

		//�����ؼ�λ��
		rect.left = controlLeft + nameWidth + splitorWidth;
		rect.right = rect.left + weightWidth + splitorWidth;
		

		//������������static�ؼ�
		materialWeighStatic = new CStatic;
		CString test1 = utils::doubleToCString(newComposition.percentage * totalWeigh / 100);
		test1 += "Kg";
		materialWeighStatic->Create(test1,
			WS_VISIBLE | ES_CENTER,
			rect,
			this,
			materialWeighStaticID++);
		//materialWeighStatic->SetFont(SingletonHelper::getInstance()->simSong20);
		materialWeighStatic->ShowWindow(SW_SHOW);
		materialWeighVector.push_back(materialWeighStatic);

		dbmweigh.push_back(utils::doubleToCString(newComposition.percentage * totalWeigh / 100));

		//�����ؼ�λ��
		rect.left = rect.right + 2;
		rect.right = rect.left + buttonWidth + splitorWidth;
		
		//�����ִγ�����ť
		CRect buttonRect = rect;
		sepWeightButton = new CButton;
		sepWeightButton->Create("", 
			BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD | ES_CENTER, 
			buttonRect, 
			this,  
			sepWeighButtonID++);

        sepWeightButton->SetWindowText("����");
		sepWeightButton->ShowWindow(SW_SHOW);
		sepWeightButtonVector.push_back(sepWeightButton);
		
		//�����ؼ�λ��
		rect.left = rect.right + splitorWidth;
		rect.right =  rect.left  + flagWidth + splitorWidth;
		
		//����������־
		weighedFlagStatic = new CStatic;
		CString weighedFlag;
		
		weighedFlag = newComposition.material == "����" ? "�ѳ���" : "δ����";
		
		if (sPointer->compositions[j]->material == "����")
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
		
		//�����ؼ�λ��
		rect.left = rect.right + splitorWidth ;
		rect.right = rect.left + editWidth / 2 - splitorWidth;
		
		//������������editbox
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
		
		//������������editbox
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

		//��������֮��ļ��
		rect.left = controlLeft;
		rect.right = controlLeft + nameWidth;
		
		rect.top += rowSpace + controlHeight;
		rect.bottom += rowSpace + controlHeight;
	}
	
	uiutils::setdlgsize(this, &m_ButtonCancel, &m_ButtonOK);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

//�Ի�������������������һЩ������
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

//������Ӧ��̬�����İ�ť����Ϣ
BOOL CFormulaWeighDialog::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	//���ﴦ��̬�����İ�ť��
	int constrolID =LOWORD(wParam);
	TRACE("controlID: %d \n", constrolID);
	SingletonHelper::getInstance()->setPtrData((void*)this);
	if (constrolID >= 40000 && constrolID <50000)
	{
		if (SingletonHelper::getInstance()->compositions[constrolID - 40000]->isWeigh  == TRUE)
		{
			AfxMessageBox("ע�⣺���ֲ����Ѿ�������!!");
		}

		int nVectorIndex = constrolID - 40000;
		CString batchNumber, lineNumber;
		batchNumberEditVector[nVectorIndex]->GetWindowText(batchNumber);
		lineNumberEditVector[nVectorIndex]->GetWindowText(lineNumber);
		if (batchNumber.IsEmpty() || lineNumber.IsEmpty())
		{
			AfxMessageBox("���ţ���������Ϊ�գ�");
			return true;
		}
		if (lineNumber != lineNumberOld[nVectorIndex])
		{
			AfxMessageBox("���벻ƥ�䣬������������");
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

//����Ի����ok��ť����һ�����߼��Ƚϸ��ӣ���֤�����ݱȽ϶࣬Ҫע��
void CFormulaWeighDialog::OnOK() 
{
	// TODO: Add extra validation here
	//�����ж���������ĺϷ��ԣ�����������벻�Ϸ�����ֱ���˳����������档
	CString batchNumber;
	std::vector<CString> batchNumberVector;

	CString lineNumber;
	std::vector<CString> lineNumberVector;


	for (size_t i = 0; i < batchNumberEditVector.size(); ++i)
	{
		//����������֤
		batchNumberEditVector[i]->GetWindowText(batchNumber);
		if (batchNumber.IsEmpty() || !utils::isBatchNumber(batchNumberEditVector[i]))
		{
			batchNumberVector.clear();
			AfxMessageBox("����ֻ�������ֺͶ��ŵ����");
			return;
		}
		batchNumberVector.push_back(batchNumber);
		//����������֤����

		//����������֤
		lineNumberEditVector[i]->GetWindowText(lineNumber);
		if (lineNumber.IsEmpty())
		{
			lineNumberVector.clear();
			AfxMessageBox("���������д����飡");
			return;
		}
		if (lineNumber != lineNumberOld[i] )
		{
			AfxMessageBox("��"+utils::intToCString(i+1)+"�����ϵ����벻ƥ�䣬���飡");
		}
		lineNumberVector.push_back(lineNumber);
		//����������֤����
	}
	
	//�жϳ��������������������û�������ֱ�ӷ����������
	bool isFinished = isWeighFinished();
	if (!isFinished)
	{
		//��ճ��������е���ʱ���ݡ�
		AfxMessageBox("ע�⣡��������û����ɣ�");
		return;
	}

	CString fbatchnumber;
	editFBNumber.GetWindowText(fbatchnumber);
	if(fbatchnumber.IsEmpty())
	{
		AfxMessageBox("�������Ʒ����!");
		return;
	}
	
	//�������Ľ����������ݿ⣬�������֣�
	//������¼�浽��ʷ��¼�����棬
	//����Ҫ�����䷽���еĳ�Ʒ����
	
	//����ȡ��ϵͳʱ��
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

	//���濪ʼ�������ݣ����һ��������ݲ��룬һ����������޸ġ�	
	//�����޸��䷽�����䷽�ĳ�Ʒ�����ӡ�
	
	CString dbweigh, dbfid, dbfname, dbuserid, dbusername;

	dbweigh = SingletonHelper::getInstance()->getFormulaWeigh();
	dbfname = SingletonHelper::getInstance()->getFormulaName();
	dbfid = SingletonHelper::getInstance()->getFormulaID();
	dbusername = SingletonHelper::getInstance()->getUsername();
	dbuserid = SingletonHelper::getInstance()->getUserID();
	
	unsigned long gmttime = utils::time2gmt(currentTime);

	//update product total
	CString sql;
	sql.Format("update formulas set total = total + %s where id = %s", 
		SingletonHelper::getInstance()->getFormulaWeigh(),
		SingletonHelper::getInstance()->getFormulaID());

	SQLExecutor::getInstanceRef().execquery(sql);

	sql.Format("insert into weight(formulaid, formulaname, userid, username, amount, odate, otime, comment, fbatchnumber, gmt) values('%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%ld')", 
		dbfid, dbfname, dbuserid, dbusername,dbweigh, date, time, comment, fbatchnumber, gmttime);

	SQLExecutor::getInstanceRef().execquery(sql);	

	

	for (size_t i = 0; i < dbmweigh.size(); ++i)
	{
		sql.Format("insert into materialrecords(materialname, materialbatchnumber, formulaid, formulaname, formula_batch_number, \
			operatorid, operatorname, amount, operate_date, operate_time, gmt) values('%s', '%s', '%s', '%s', '%s', '%s', '%s', \
			%s, '%s', '%s', %ld)", 
			dbmname[i], batchNumberVector[i], dbfid, dbfname, fbatchnumber, 
			dbuserid, dbusername, dbmweigh[i], date, time, gmttime);
		SQLExecutor::getInstanceRef().execquery(sql);
	}

	if (m_PrintCheck.GetCheck())
	{	
		printVector.push_back(fbatchnumber);
		printVector.push_back(SingletonHelper::getInstance()->getFormulaName());
		printVector.push_back(SingletonHelper::getInstance()->getFormulaWeigh() + "Kg");
		printVector.push_back(SingletonHelper::getInstance()->getUsername());
		printVector.push_back(date);
		printVector.push_back(time);
		printVector.push_back(CString(""));
		printVector.push_back(CString(""));

		CString headerArray[8] ={"��������:","�䷽����:","��������:","�û�����:","��������:","����ʱ��:","����:","��������:"};
		std::vector<CString> headerList(headerArray, headerArray + 8);
		
		utils::printVector(CString("ɽ���������ɻ�Ϸ�"),headerList, printVector);

		printVector.clear();
	}

	//��ճ��������е���ʱ���ݡ�
	SingletonHelper::getInstance()->clearCompositions();
	CDialog::OnOK();
}

//ˢ�¸��ֲ��ϵĳ��ر�־
void CFormulaWeighDialog::refreshWeighedFlag()
{
	CString weighedFlag("δ����");
	for (size_t i = 0; i < SingletonHelper::getInstance()->compositions.size(); ++i)
	{
		weighedFlag = SingletonHelper::getInstance()->compositions[i]->isWeigh ? "�ѳ���" : "δ����";
		weighedFlagVector[i]->SetWindowText(weighedFlag);
		RECT rect;
		weighedFlagVector[i]->GetWindowRect(&rect);   
		weighedFlagVector[i]->GetParent()->ScreenToClient(&rect);
		weighedFlagVector[i]->GetParent()->InvalidateRect(&rect, TRUE);
	}
}

//����Ƿ�������
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

//����Ի����cancel��ť
void CFormulaWeighDialog::OnCancel() 
{
	// TODO: Add extra cleanup here
	//������ʾ��Ҫ��Ҫ��������
	CString msg("��ȷ��Ҫ������γ�������");
	CString caption("������������");
	//ѡ��cancel�򷵻�
	if (IDCANCEL == MessageBox(msg, caption, MB_OKCANCEL))
	{
		return;
	}
	//��ճ���ʱ���õ���ʱ����
	SingletonHelper::getInstance()->clearCompositions();
	CDialog::OnCancel();
}

void CFormulaWeighDialog::OnButton1() 
{
	CWnd * pWnd = GetDlgItem(m_FocusedID);
	::SetFocus(pWnd->GetSafeHwnd());
	keybd_event(VK_NUMPAD1, 0, 0, 0);
}

void CFormulaWeighDialog::OnButton2() 
{
	CWnd * pWnd = GetDlgItem(m_FocusedID);
	::SetFocus(pWnd->GetSafeHwnd());
	keybd_event(VK_NUMPAD2, 0, 0, 0);
}

void CFormulaWeighDialog::OnButton3() 
{
	CWnd * pWnd = GetDlgItem(m_FocusedID);
	::SetFocus(pWnd->GetSafeHwnd());
	keybd_event(VK_NUMPAD3, 0, 0, 0);
}

void CFormulaWeighDialog::OnButton4() 
{
	CWnd * pWnd = GetDlgItem(m_FocusedID);
	::SetFocus(pWnd->GetSafeHwnd());
	keybd_event(VK_NUMPAD4, 0, 0, 0);
}

void CFormulaWeighDialog::OnButton5() 
{
	CWnd * pWnd = GetDlgItem(m_FocusedID);
	::SetFocus(pWnd->GetSafeHwnd());
	keybd_event(VK_NUMPAD5, 0, 0, 0);
}

void CFormulaWeighDialog::OnButton6() 
{
	CWnd * pWnd = GetDlgItem(m_FocusedID);
	::SetFocus(pWnd->GetSafeHwnd());
	keybd_event(VK_NUMPAD6, 0, 0, 0);
}

void CFormulaWeighDialog::OnButton7() 
{
	CWnd * pWnd = GetDlgItem(m_FocusedID);
	::SetFocus(pWnd->GetSafeHwnd());
	keybd_event(VK_NUMPAD7, 0, 0, 0);
}

void CFormulaWeighDialog::OnButton8() 
{
	CWnd * pWnd = GetDlgItem(m_FocusedID);
	::SetFocus(pWnd->GetSafeHwnd());
	keybd_event(VK_NUMPAD8, 0, 0, 0);
}

void CFormulaWeighDialog::OnButton9() 
{
	CWnd * pWnd = GetDlgItem(m_FocusedID);
	::SetFocus(pWnd->GetSafeHwnd());
	keybd_event(VK_NUMPAD9, 0, 0, 0);
}

void CFormulaWeighDialog::OnButton0() 
{
	CWnd * pWnd = GetDlgItem(m_FocusedID);
	::SetFocus(pWnd->GetSafeHwnd());
	keybd_event(VK_NUMPAD0, 0, 0, 0);
}

void CFormulaWeighDialog::OnButtonComma() 
{
	CWnd * pWnd = GetDlgItem(m_FocusedID);
	::SetFocus(pWnd->GetSafeHwnd());
	keybd_event(188, 0, 0, 0);
}

void CFormulaWeighDialog::OnButtonBack() 
{
	CWnd * pWnd = GetDlgItem(m_FocusedID);
	::SetFocus(pWnd->GetSafeHwnd());
	keybd_event(VK_BACK, 0, 0, 0);
}

void CFormulaWeighDialog::OnBnClickedOk()
{
	OnOK();
}