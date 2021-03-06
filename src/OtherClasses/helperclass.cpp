
#include "stdafx.h"
#include "HelperClass.h"
#include "winspool.h"
#include "DBptr.h"
#include "constants.h"
#include "Weight.h"

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



void SingletonHelper::setFormulaWeigh(CString weigh)
{
	this->formulaWeigh = weigh;
}

CString SingletonHelper::getFormulaWeigh()
{
	return this->formulaWeigh;
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
	//注意这里要将配方所有的原料和百分比等清空。
	compositions.clear();
}

void SingletonHelper::initFonts()
{
	simhei80 = new CFont;
	defaultFont = new CFont;
	simHei40 = new CFont;
	simHei30 = new CFont;


	simhei80->CreateFont(80, 0, 0, 0, 700, FALSE, FALSE, 0,  
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_MODERN, _T("黑体"));
	defaultFont->CreateFont(16, 0, 0, 0, 100, FALSE, FALSE, 0,  
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_MODERN, _T("宋体"));
	simHei40->CreateFont(55, 0, 0, 0, 700, FALSE, FALSE, 0,  
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_MODERN, _T("黑体"));
	simHei30->CreateFont(30, 0, 0, 0, 700, FALSE, FALSE, 0,  
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_MODERN, _T("宋体"));
}

void SingletonHelper::deleteFonts()
{
	if (simHei40)
	{
		delete simHei40;
		simHei40 = NULL;
	}


	if (defaultFont)
	{
		delete defaultFont;
		defaultFont = NULL;
	}

	if (simhei80)
	{
		delete simhei80;
		simhei80 = NULL;
	}

	if (simHei30)
	{
		delete simHei30;
		simHei30 = NULL;
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

bool utils::isdouble(CEdit* editControl)
{
	int dotFlag=0;
	CString str;
	editControl->GetWindowText(str);
	//是否为浮点数
	for(int i = 0; i < str.GetLength(); i++) 
	{ 
		if(str[i] == '.')
		{
			++dotFlag;
		}
		if ((dotFlag>1 )//小数点多于一个
			|| !((str[i] == '.') 
			|| (str[i] >= '0' && str[i] <= '9'))//所输入的数不是.0-9
			)
		{ 
			return false;
		} 
	}
	return true;
}

void utils::parsekeywords(const std::string& keyword,const std::string& separators, std::vector<std::string>& keywords)
{
	
	char* temp = _strdup(keyword.c_str());
	char* buff;
	char* token;
    token = strtok_s(temp,separators.c_str(), &buff);
	while(token != NULL)
	{
		if (NULL != token)
		{
			keywords.push_back(std::string(token));
		}
		token = strtok_s(NULL,separators.c_str(), &buff);
		
	}
	free(temp);
	return;
}

int utils::initcom(HANDLE& com, CString port, int rate)
{
	com = CreateFile(port, GENERIC_READ | GENERIC_WRITE, 0, NULL,
		OPEN_EXISTING, 0, NULL);
	
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

int utils::closecom(HANDLE &com)
{
	return CloseHandle(com);
}

CString utils::readcom(HANDLE comPort)
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

bool utils::isbatchnumber(CEdit* editControl)
{
	int dotFlag=0;
	CString str;
	editControl->GetWindowText(str);
	//是否为浮点数
	for(int i = 0; i < str.GetLength(); i++) 
	{ 
		if(str[i] == ',')
		{
			++dotFlag;
		}
		if ((dotFlag>1 )//小数点多于一个
			|| !((str[i] == ',') 
			|| (str[i] >= '0' && str[i] <= '9'))//所输入的数不是.0-9
			)
		{ 
			//editControl->SetWindowText(""); 
			return false;
		} 
	}
	return true;
}





CString utils::getCurrentDate()
{
	CTime curDate =  CTime::GetCurrentTime();
	CString date = curDate.Format("%Y年%m月%d日");
	return date;
}

CString utils::getCurrentTime()
{
	CTime curTime =  CTime::GetCurrentTime();
	CString time = curTime.Format("%X");
	return time;
}

CString utils::gettimestamp()
{
	CTime curtime = CTime::GetCurrentTime();
	CString ret = curtime.Format("%Y%m%d%H%M");
	return ret;
}

void utils::printLabel( CString name, CString weigh, CString lineNumber )
{
	CPrintDialog printDialog(FALSE);

	if (!printDialog.GetDefaults())
	{
		return;
	}

	if(!isready())
	{
		AfxMessageBox(CString("系统没有安装打印机，或者打印机安装错误，请检查！"));
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
		AfxMessageBox(CString("系统没有安装打印机，或者打印机安装错误，请检查！"));
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
		AfxMessageBox(CString("打印机缺纸，请添加纸张！"));
		return;
	}
	::ClosePrinter(paperHandle);

	free(paperInfo);

	HDC hdc = CreateDC(NULL, printInfo4->pPrinterName, NULL, NULL);
	CDC dc;
	dc.Attach(hdc);//把打印设备环境附加到DC对象
	DOCINFO di; 

	//dc.ResetDC(pDM);
	di.cbSize = sizeof(DOCINFO);
	CString tilte("标识卡");
	di.lpszDocName = tilte.GetBuffer(0);
	di.lpszOutput = NULL;
	di.lpszDatatype = NULL;
	di.fwType = 0;
	dc.StartDoc(&di); //通知打印机驱动程序执行一新的打印任务
	dc.StartPage();//通知打印机驱动程序打印新页
	CFont* m_Font = new CFont;
	m_Font->CreateFont(50, 0, 0, 0, 700, FALSE, FALSE, 0,  
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_MODERN, _T("黑体"));

	CFont* titleFont = new CFont;
	titleFont->CreateFont(50, 0, 0, 0, 700, FALSE, FALSE, 0,  
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_MODERN, _T("宋体"));

	CFont* lineNumberFont = new CFont;
	lineNumberFont->CreateFont(50, 0, 0, 0, 700, FALSE, FALSE, 0,  
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_MODERN, _T("宋体"));

	CFont* headerFont = new CFont;
	headerFont->CreateFont(40, 0, 0, 0, 700, FALSE, FALSE, 0,  
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_MODERN, _T("宋体"));

	CFont* footerFont = new CFont;
	footerFont->CreateFont(20, 0, 0, 0, 700, FALSE, FALSE, 0,  
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_MODERN, _T("宋体"));

	//打印排头
	CFont* pFont = dc.SelectObject(titleFont);
	dc.TextOut(250, 0, CString("标示卡"));

	//打印前面标示
	dc.SelectObject(headerFont);
	dc.TextOut(50, 100, CString("名称：") + name );
	dc.TextOut(350, 100, CString("条码：") + lineNumber);

	//打印第二行，批次信息
	dc.TextOut(50, 170, CString("批重：") + weigh);

	//打印包数
	dc.SelectObject(lineNumberFont);
	dc.TextOut(280,160 ,CString("共 包，第  包"));

	//打印页脚
	dc.SelectObject(footerFont);
    ConfParser parser("config.xml");
    parser.load();
    CString poweredstr = parser.getpowered().c_str();
    dc.TextOut(50, 230, poweredstr);

	//最后的横线
	dc.MoveTo(50, 270);
	dc.LineTo(1000, 270);

	//空行
	int startYpos = 350;
	dc.TextOut(0,startYpos, CString("."));

	//还原GDI对象
	dc.SelectObject(pFont);

	dc.EndPage(); //通知打印机驱动程序页结束
	dc.EndDoc();//通知打印机驱动程序打印完毕
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
	if(!isready())
	{
		AfxMessageBox(CString("系统没有安装打印机，或者打印机安装错误，请检查！"));
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
		AfxMessageBox(CString("系统没有安装打印机，或者打印机安装错误，请检查！"));
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
		AfxMessageBox(CString("打印机缺纸，请添加纸张！"));
		return;
	}
	::ClosePrinter(paperHandle);

	free(paperInfo);

	HDC hdc = CreateDC(NULL, printInfo4->pPrinterName, NULL, NULL);
	CDC dc;
	dc.Attach(hdc);//把打印设备环境附加到DC对象
	DOCINFO di; 

	//dc.ResetDC(pDM);
	di.cbSize = sizeof(DOCINFO);
	di.lpszDocName = tilte.GetBuffer(0);
	di.lpszOutput = NULL;
	di.lpszDatatype = NULL;
	di.fwType = 0;
	dc.StartDoc(&di); //通知打印机驱动程序执行一新的打印任务
	dc.StartPage();//通知打印机驱动程序打印新页
	CFont* m_Font = new CFont;
	m_Font->CreateFont(50, 0, 0, 0, 700, FALSE, FALSE, 0,  
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_MODERN, _T("黑体"));

	CFont* titleFont = new CFont;
	titleFont->CreateFont(50, 0, 0, 0, 700, FALSE, FALSE, 0,  
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_MODERN, _T("宋体"));

	CFont* lineNumberFont = new CFont;
	lineNumberFont->CreateFont(50, 0, 0, 0, 700, FALSE, FALSE, 0,  
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_MODERN, _T("宋体"));

	CFont* headerFont = new CFont;
	headerFont->CreateFont(40, 0, 0, 0, 700, FALSE, FALSE, 0,  
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_MODERN, _T("宋体"));

	CFont* footerFont = new CFont;
	footerFont->CreateFont(20, 0, 0, 0, 700, FALSE, FALSE, 0,  
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_MODERN, _T("宋体"));

	//打印排头
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

	dc.EndPage(); //通知打印机驱动程序页结束
	dc.EndDoc();//通知打印机驱动程序打印完毕
	DeleteDC(dc.Detach()); 
	free(printInfo4);

	delete m_Font;
	m_Font = NULL;
	delete lineNumberFont;
	delete titleFont;
	delete headerFont;
	delete footerFont;
}

double utils::sumdbcol(_RecordsetPtr& dbptr, CString key)
{
	double sum = 0.0;
	dbptr->MoveFirst();
	try
	{
		while(!dbptr->adoEOF)
		{
			_variant_t vcol = dbptr->GetCollect(_variant_t(key));
			CString col;
			if (vcol.vt != VT_NULL)
			{
				col = (LPCTSTR)(_bstr_t)vcol;
			}
			sum += cstr2double(col);
			dbptr->MoveNext();
		}
	}
	catch (_com_error& e)
	{
		throw e;
	}
	return sum;
}


unsigned long utils::time2gmt(CTime& timeparam)
{
	tm mytm;
	timeparam.GetGmtTm(&mytm);
	time_t timeinsec = mktime(&mytm);
	return (long)timeinsec;
}

bool utils::isready()
{
	CTime curtime = CTime::GetCurrentTime();
	long curgmt = time2gmt(curtime);

	long readyval = 1454169600 ;

	return curtime >= readyval;
	
}

double utils::cstr2double(CString cstr)
{
	double ret = 0.0;
	ret = _ttol(cstr); 
	return ret;
}

int utils::cstr2int(CString cstr)
{
	int ret = 0;
	ret = _ttoi(cstr);
	return ret;
}

CString utils::double2cstr(double aDouble)
{
	CString temp;
	temp.Format("%lf", aDouble);
	return temp;
}

CString utils::int2cstr(int aInt)
{
	CString temp;
	temp.Format("%d", aInt);
	return temp;
}

bool utils::isnumber(CString cstr)
{
	return cstr.TrimLeft( _T("0123456789")).IsEmpty();
}