
#include "stdafx.h"
#include "HelperClass.h"
#include "winspool.h"
#include "DBptr.h"

SingletonHelper* SingletonHelper::m_instance = NULL;

SingletonHelper::~SingletonHelper(){}

SingletonHelper* SingletonHelper::getInstance()
{
	if (NULL == m_instance)
	{
		m_instance = new SingletonHelper;
		return m_instance;
	}
	return m_instance;
}

void* SingletonHelper::getPtrData()
{
	return this->ptrData;
}

void SingletonHelper::setPtrData(void *data)
{
	this->ptrData = data;
}

int SingletonHelper::getIntData()
{
	return this->intData;
}

void SingletonHelper::setIntData(int data)
{
	this->intData = data;
}

void SingletonHelper::setUserName(CString &userName)
{
	this->userName = userName;
}

CString SingletonHelper::getUsername()
{
	return this->userName;
}

void SingletonHelper::setUserPass(CString &pass)
{
	this->userPass = pass;
}

CString SingletonHelper::getUserPass()
{
	return this->userPass;
}

void SingletonHelper::setUserRight(CString &right)
{
	userRight = right;
}

CString SingletonHelper::getUserRight()
{
	return userRight;
}

void SingletonHelper::setTableName(CString &talbeName)
{
	this->tableName = tableName;
}

CString SingletonHelper::getTableName()
{
	return this->tableName;
}

void SingletonHelper::setIndexName(CString &indexName)
{
	this->indexName = indexName;
}

CString SingletonHelper::getIndexName()
{
	return this->indexName;
}

void SingletonHelper::setKeyWord(CString &keyWord)
{
	this->keyWord = keyWord;
}

CString SingletonHelper::getKeyWord()
{
	return this->keyWord;
}

void SingletonHelper::setFormulaWeigh(CString weigh)
{
	this->formulaWeigh = weigh;
}

CString SingletonHelper::getFormulaWeigh()
{
	return this->formulaWeigh;
}

void SingletonHelper::setWeighPerPack(double weigh)
{
	this->weighPerPack = weigh;
}

double SingletonHelper::getWeighPerPack()
{
	return this->weighPerPack;
}

void SingletonHelper::setUserID(CString id)
{
	this->userID = id;
}

CString SingletonHelper::getUserID()
{
	return this->userID;
}

void SingletonHelper::setFormulaID(CString id)
{
	this->formulaID = id;
}

CString SingletonHelper::getFormulaID()
{
	return this->formulaID;
}

void SingletonHelper::setMaterials(CString &materials)
{
	this->materials = materials.GetBuffer(materials.GetLength());
}

std::string SingletonHelper::getMaterials()
{
	return this->materials;
}

void SingletonHelper::setFormulaName(CString formulaName)
{
	this->formulaName = formulaName;
}

CString SingletonHelper::getFormulaName()
{
	return this->formulaName;
}

void SingletonHelper::setSepWeighWindowPtr(void* ptr)
{
	this->sepWeighWindowPtr = ptr;
}

void* SingletonHelper::getSepWieghWindowPtr()
{
	return this->sepWeighWindowPtr;
}

void SingletonHelper::setCom1BaudRate(CString rate)
{
	this->com1BaudRate = rate;
}

CString SingletonHelper::getCom1BaudRate()
{
	return this->com1BaudRate;
}

void SingletonHelper::setCom2BaudRate(CString rate)
{
	this->com2BaudRate = rate;
}

CString SingletonHelper::getCom2BaudRate()
{
	return this->com2BaudRate;
}

void SingletonHelper::setRecordID(CString id)
{
	this->recordID = id;
}

CString SingletonHelper::getRecordID()
{
	return this->recordID;
}

CString SingletonHelper::getLineNumber()
{
	return this->lineNumber;
}

void SingletonHelper::setLineNumber(CString lineNumber)
{
	this->lineNumber = lineNumber;
}

void SingletonHelper::clearCompositions()
{
	for (size_t j = 0; j < compositions.size(); ++j)
	{
		delete compositions[j];
		compositions[j] = NULL;
	}
	//ע������Ҫ���䷽���е�ԭ�ϺͰٷֱȵ���ա�
	compositions.clear();
}

void SingletonHelper::initFonts()
{
	simhei80 = new CFont;
	simSong20 = new CFont;
	simSong32 = new CFont;
	simHei40 = new CFont;

	simhei80->CreateFont(80, 0, 0, 0, 700, FALSE, FALSE, 0,  
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_MODERN, _T("����"));
	simSong20->CreateFont(20, 0, 0, 0, 700, FALSE, FALSE, 0,  
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_MODERN, _T("����"));
	simSong32->CreateFont(32, 0, 0, 0, 700, FALSE, FALSE, 0,  
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_MODERN, _T("����"));
	simHei40->CreateFont(55, 0, 0, 0, 700, FALSE, FALSE, 0,  
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_MODERN, _T("����"));
}

void SingletonHelper::deleteFonts()
{
	if (simHei40)
	{
		delete simHei40;
		simHei40 = NULL;
	}

	if (simSong32)
	{
		delete simSong32;
		simSong32 = NULL;
	}

	if (simSong20)
	{
		delete simSong20;
		simSong20 = NULL;
	}

	if (simhei80)
	{
		delete simhei80;
		simhei80 = NULL;
	}
}


void SingletonHelper::removeInstance()
{
	if (NULL == m_instance)
	{
		return;
	}
	if (!(m_instance->compositions.empty()))
	{
		for (size_t i = 0; i < (m_instance->compositions.size()); ++i)
		{
			delete m_instance->compositions[i];
			m_instance->compositions[i] = NULL;
		}
	}
	m_instance->deleteFonts();
	delete m_instance;
	m_instance = NULL;
	
}

bool utils::isDouble(CEdit* editControl)
{
	int dotFlag=0;
	CString str;
	editControl->GetWindowText(str);
	//�Ƿ�Ϊ������
	for(int i = 0; i < str.GetLength(); i++) 
	{ 
		if(str[i] == '.')
		{
			++dotFlag;
		}
		if ((dotFlag>1 )//С�������һ��
			|| !((str[i] == '.') 
			|| (str[i] >= '0' && str[i] <= '9'))//�������������.0-9
			)
		{ 
			return false;
		} 
	}
	return true;
}

void utils::ParseKeywords(const std::string& keyword,const std::string& separators, std::vector<std::string>& keywords)
{
	char* temp = strdup(keyword.c_str());
	
	char* token;
    token = strtok(temp,separators.c_str());
	while(token != NULL)
	{
		if (NULL != token)
		{
			keywords.push_back(std::string(token));
		}
		token = strtok(NULL,separators.c_str());
	}
	free(temp);
	return;
}

int utils::initCom(HANDLE& com, CString port, int rate)
{
	com = CreateFile(port,
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		0,
		NULL
		);
	
	if (com == (HANDLE)(-1))
	{
		return -1;
	}
	
	//make buffer for input and output, both of them are set to 1024 bytes.
	SetupComm(com, 100, 100);
	
	COMMTIMEOUTS timeOuts;
	//setting up reading timeout
	timeOuts.ReadIntervalTimeout = MAXDWORD;
	timeOuts.ReadTotalTimeoutMultiplier = 0;
	timeOuts.ReadTotalTimeoutConstant = 0;
	
	//read buffer once and return;
	//whatever have read the need content or not
	timeOuts.WriteTotalTimeoutMultiplier = 100;
	timeOuts.WriteTotalTimeoutConstant = 500;
	SetCommTimeouts(com, &timeOuts);
	
	DCB dcb;
	
	GetCommState(com, &dcb);
	dcb.BaudRate = rate;
	dcb.ByteSize = 8;
	dcb.Parity = NOPARITY;
	dcb.StopBits = TWOSTOPBITS;
	SetCommState(com, &dcb);
	
	PurgeComm(com, PURGE_TXCLEAR | PURGE_RXCLEAR);
	return 0;
}

int utils::closeCom(HANDLE &com)
{
	return CloseHandle(com);
}

CString utils::readCom(HANDLE comPort)
{
	char str[8];
	memset(str, 0, 8);
	CString testStr;
	
	DWORD wCount = 7;
	BOOL bReadStat;
	HANDLE com = comPort;
	bReadStat = ReadFile(com, str, wCount, &wCount, NULL);
	if (!bReadStat)
	{
		return CString("");
	}
	PurgeComm(comPort,PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR);
	str[7] = '\0';
	
	char result[7];

	for (int i = 0; i < 6; ++i)
	{
		result[i] = str[6-i];
	}
	result[6] = '\0';
	CString returnValue(result);
	return returnValue;
}

bool utils::isBatchNumber(CEdit* editControl)
{
	int dotFlag=0;
	CString str;
	editControl->GetWindowText(str);
	//�Ƿ�Ϊ������
	for(int i = 0; i < str.GetLength(); i++) 
	{ 
		if(str[i] == ',')
		{
			++dotFlag;
		}
		if ((dotFlag>1 )//С�������һ��
			|| !((str[i] == ',') 
			|| (str[i] >= '0' && str[i] <= '9'))//�������������.0-9
			)
		{ 
			//editControl->SetWindowText(""); 
			return false;
		} 
	}
	return true;
}

CString utils::doubleToCString(double aDouble)
{
	CString temp;
	temp.Format("%lf", aDouble);
	return temp;
}

CString utils::intToCString(int aInt)
{
	CString temp;
	temp.Format("%d", aInt);
	return temp;
}

void utils::showStatus(CStatic& statusStatic)
{
	CTime curTime;
	curTime = CTime::GetCurrentTime();
	CString date, time;
	date = curTime.Format("�����ǣ�%Y��%m��%d�գ�");
	time = curTime.Format("��ǰʱ�䣺%X��");
	statusStatic.SetWindowText(date + time + "��ǰ�����û��ǣ�" + SingletonHelper::getInstance()->getUsername());
	RECT rect;
	statusStatic.GetWindowRect(&rect);   
	statusStatic.GetParent()->ScreenToClient(&rect);
	statusStatic.GetParent()->InvalidateRect(&rect, TRUE);
}

void utils::setButtonStyle(CButton& button, COLORREF bgColor, CFont* pFont, bool reDraw /* = TRUE  */, bool blFlat /* = FALSE */)
{
	button.SetFont(pFont, reDraw);

}

CString utils::getCurrentDate()
{
	CTime curDate =  CTime::GetCurrentTime();
	CString date = curDate.Format("%Y��%m��%d��");
	return date;
}

CString utils::getCurrentTime()
{
	CTime curTime =  CTime::GetCurrentTime();
	CString time = curTime.Format("%X");
	return time;
}

void utils::updateRecordValueVector(_RecordsetPtr& pRecordset, std::vector<CString>& valueList, std::vector<CString>& headerList)
{
	int itemIndex = 0;
	int subItemIndex = 0;
	try
	{
		while(!pRecordset->adoEOF)
		{
			for (size_t i = 0; i < headerList.size(); ++i )
			{
				_variant_t vDataField = pRecordset->GetCollect(_variant_t(headerList[i]));
				CString dataField;
				//ȡ��ĳ���ֶε�����
				if (vDataField.vt != VT_NULL)
				{
					dataField = (LPCTSTR)(_bstr_t)vDataField;
				}
				//insert or modify by the value of i
				//i == 0 ? (listCtrl.InsertItem(itemIndex,dataField)):(listCtrl.SetItemText(itemIndex, subItemIndex, dataField));
				//++subItemIndex;
				valueList.push_back(dataField);
			}
			subItemIndex = 0;
			++itemIndex;
			pRecordset->MoveNext();
		}
	}
	catch (_com_error& e)
	{
		throw e;
	}
	return;
}

void utils::printLabel( CString name, CString weigh, CString lineNumber )
{
	CPrintDialog printDialog(FALSE);

	if (!printDialog.GetDefaults())
	{
		return;
	}

	LPDEVMODE pDM = printDialog.GetDevMode();
	::GlobalLock(pDM);
	pDM->dmOrientation = DMORIENT_LANDSCAPE;
	::GlobalUnlock(pDM);

	DWORD dwNeeded, dwReturned;
	EnumPrinters(PRINTER_ENUM_LOCAL, NULL, 4, NULL, 0, &dwNeeded, &dwReturned);

	PRINTER_INFO_4* printInfo4 = (PRINTER_INFO_4*)malloc(dwNeeded);
	EnumPrinters(PRINTER_ENUM_LOCAL, NULL, 4, (PBYTE)printInfo4, dwNeeded, &dwNeeded, &dwReturned);
	if (dwReturned < 1)
	{
		AfxMessageBox(CString("ϵͳû�а�װ��ӡ�������ߴ�ӡ����װ�������飡"));
		return;
	}

	PRINTER_INFO_2* paperInfo;

	DWORD paperNeed;
	HANDLE paperHandle;
	::OpenPrinter(printInfo4->pPrinterName, &paperHandle, NULL);
	if (!::GetPrinter(paperHandle, 2, NULL, 0, &paperNeed))
	{
		paperInfo = (PRINTER_INFO_2*)malloc(paperNeed);
		::GetPrinter(paperHandle, 2, (LPBYTE)paperInfo, paperNeed, &paperNeed);
	}

	if (paperInfo->Status == PRINTER_STATUS_PAPER_OUT)
	{
		free(paperInfo);
		AfxMessageBox(CString("��ӡ��ȱֽ�������ֽ�ţ�"));
		return;
	}
	::ClosePrinter(paperHandle);

	free(paperInfo);

	HDC hdc = CreateDC(NULL, printInfo4->pPrinterName, NULL, NULL);
	CDC dc;
	dc.Attach(hdc);//�Ѵ�ӡ�豸�������ӵ�DC����
	DOCINFO di; 

	//dc.ResetDC(pDM);
	di.cbSize = sizeof(DOCINFO);
	CString tilte("��ʶ��");
	di.lpszDocName = tilte.GetBuffer(0);
	di.lpszOutput = NULL;
	di.lpszDatatype = NULL;
	di.fwType = 0;
	dc.StartDoc(&di); //֪ͨ��ӡ����������ִ��һ�µĴ�ӡ����
	dc.StartPage();//֪ͨ��ӡ�����������ӡ��ҳ
	CFont* m_Font = new CFont;
	m_Font->CreateFont(50, 0, 0, 0, 700, FALSE, FALSE, 0,  
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_MODERN, _T("����"));

	CFont* titleFont = new CFont;
	titleFont->CreateFont(50, 0, 0, 0, 700, FALSE, FALSE, 0,  
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_MODERN, _T("����"));

	CFont* lineNumberFont = new CFont;
	lineNumberFont->CreateFont(50, 0, 0, 0, 700, FALSE, FALSE, 0,  
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_MODERN, _T("����"));

	CFont* headerFont = new CFont;
	headerFont->CreateFont(40, 0, 0, 0, 700, FALSE, FALSE, 0,  
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_MODERN, _T("����"));

	CFont* footerFont = new CFont;
	footerFont->CreateFont(20, 0, 0, 0, 700, FALSE, FALSE, 0,  
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_MODERN, _T("����"));

	//��ӡ��ͷ
	CFont* pFont = dc.SelectObject(titleFont);
	dc.TextOut(250, 0, CString("��ʾ��"));

	//��ӡǰ���ʾ
	dc.SelectObject(headerFont);
	dc.TextOut(50, 100, CString("���ƣ�") + name );
	dc.TextOut(350, 100, CString("���룺") + lineNumber);

	//��ӡ�ڶ��У�������Ϣ
	dc.TextOut(50, 170, CString("���أ�") + weigh);

	//��ӡ����
	dc.SelectObject(lineNumberFont);
	dc.TextOut(280,160 ,CString("�� ������  ��"));

	//��ӡҳ��
	dc.SelectObject(footerFont);
    ConfParser parser("config.xml");
    parser.load();
    CString poweredstr = parser.getpowered().c_str();
    dc.TextOut(50, 230, poweredstr);

	//���ĺ���
	dc.MoveTo(50, 270);
	dc.LineTo(1000, 270);

	//����
	int startYpos = 350;
	dc.TextOut(0,startYpos, CString("."));

	//��ԭGDI����
	dc.SelectObject(pFont);

	dc.EndPage(); //֪ͨ��ӡ����������ҳ����
	dc.EndDoc();//֪ͨ��ӡ�����������ӡ���
	DeleteDC(dc.Detach()); 
	free(printInfo4);


	delete m_Font;
	m_Font = NULL;
	delete lineNumberFont;
	delete titleFont;
	delete headerFont;
	delete footerFont;

}

void utils::printVector(CString tilte, std::vector<CString>& headerList, std::vector<CString>& valueList)
{
	CPrintDialog printDialog(FALSE);

	if (!printDialog.GetDefaults())
	{
		return;
	}
	LPDEVMODE pDM = printDialog.GetDevMode();
	::GlobalLock(pDM);
	pDM->dmOrientation = DMORIENT_LANDSCAPE;
	::GlobalUnlock(pDM);

	DWORD dwNeeded, dwReturned;
	EnumPrinters(PRINTER_ENUM_LOCAL, NULL, 4, NULL, 0, &dwNeeded, &dwReturned);

	PRINTER_INFO_4* printInfo4 = (PRINTER_INFO_4*)malloc(dwNeeded);
	EnumPrinters(PRINTER_ENUM_LOCAL, NULL, 4, (PBYTE)printInfo4, dwNeeded, &dwNeeded, &dwReturned);
	if (dwReturned < 1)
	{
		AfxMessageBox(CString("ϵͳû�а�װ��ӡ�������ߴ�ӡ����װ�������飡"));
		return;
	}

	PRINTER_INFO_2* paperInfo;

	DWORD paperNeed;
	HANDLE paperHandle;
	::OpenPrinter(printInfo4->pPrinterName, &paperHandle, NULL);
	if (!::GetPrinter(paperHandle, 2, NULL, 0, &paperNeed))
	{
		paperInfo = (PRINTER_INFO_2*)malloc(paperNeed);
		::GetPrinter(paperHandle, 2, (LPBYTE)paperInfo, paperNeed, &paperNeed);
	}

	if (paperInfo->Status == PRINTER_STATUS_PAPER_OUT)
	{
		free(paperInfo);
		AfxMessageBox(CString("��ӡ��ȱֽ�������ֽ�ţ�"));
		return;
	}
	::ClosePrinter(paperHandle);

	free(paperInfo);

	HDC hdc = CreateDC(NULL, printInfo4->pPrinterName, NULL, NULL);
	CDC dc;
	dc.Attach(hdc);//�Ѵ�ӡ�豸�������ӵ�DC����
	DOCINFO di; 

	//dc.ResetDC(pDM);
	di.cbSize = sizeof(DOCINFO);
	di.lpszDocName = tilte.GetBuffer(0);
	di.lpszOutput = NULL;
	di.lpszDatatype = NULL;
	di.fwType = 0;
	dc.StartDoc(&di); //֪ͨ��ӡ����������ִ��һ�µĴ�ӡ����
	dc.StartPage();//֪ͨ��ӡ�����������ӡ��ҳ
	CFont* m_Font = new CFont;
	m_Font->CreateFont(50, 0, 0, 0, 700, FALSE, FALSE, 0,  
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_MODERN, _T("����"));

	CFont* titleFont = new CFont;
	titleFont->CreateFont(50, 0, 0, 0, 700, FALSE, FALSE, 0,  
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_MODERN, _T("����"));

	CFont* lineNumberFont = new CFont;
	lineNumberFont->CreateFont(50, 0, 0, 0, 700, FALSE, FALSE, 0,  
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_MODERN, _T("����"));

	CFont* headerFont = new CFont;
	headerFont->CreateFont(40, 0, 0, 0, 700, FALSE, FALSE, 0,  
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_MODERN, _T("����"));

	CFont* footerFont = new CFont;
	footerFont->CreateFont(20, 0, 0, 0, 700, FALSE, FALSE, 0,  
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_MODERN, _T("����"));

	//��ӡ��ͷ
	CFont* pFont = dc.SelectObject(headerFont);
	dc.TextOut(250, 0, tilte);

	int startYpos = 50;
	for (size_t i = 0; i < headerList.size(); ++i)
	{
		CString tempString = headerList[i] + CString("    ") + valueList[i];
		dc.TextOut(80, startYpos, tempString);
		startYpos += 60;
	}

	dc.TextOut(0, 520, CString("."));

	dc.SelectObject(pFont);

	dc.EndPage(); //֪ͨ��ӡ����������ҳ����
	dc.EndDoc();//֪ͨ��ӡ�����������ӡ���
	DeleteDC(dc.Detach()); 
	free(printInfo4);

	delete m_Font;
	m_Font = NULL;
	delete lineNumberFont;
	delete titleFont;
	delete headerFont;
	delete footerFont;
}

unsigned long utils::time2gmt(CTime& timeparam)
{
	tm mytm;
	timeparam.GetGmtTm(&mytm);
	time_t timeinsec = mktime(&mytm);
	return (long)timeinsec;
}
