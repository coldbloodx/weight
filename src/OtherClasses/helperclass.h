//here puts some helper class and functions

#include "PatternLoader.h"

//struct for material name and it's percentage
#ifndef _HELPCLASS_HEADER_
#define _HELPCLASS_HEADER_

struct composition
{
	std::string		material;
	double			percentage;
	bool			isWeigh;
};

//Singleton Recorder For Pointer, Integer, Etc...
class SingletonHelper
{
private:
	void* ptrData;
	void* sepWeighWindowPtr;
	int   intData;

	//用户的标识，用户ID，和用户的姓名
	CString userID;
	CString userName;
	CString userPass;
	CString userRight;

	//查询窗口用到
	CString tableName;
	CString indexName;
	CString keyWord;

	//配方ID，配方名字，配方重量
	CString formulaID;
	CString formulaName;
	CString formulaWeigh;

	//记录ID
	CString recordID;

	std::string materials;

	//全局配置用到
	CString		 com1BaudRate;
	CString		 com2BaudRate;

	double      weighPerPack;

	//条码
	CString lineNumber;

private:
	static  SingletonHelper* m_instance;
	
	//make the constructor private, so others can't create instances.
private:
	SingletonHelper():ptrData(NULL), intData(0),simhei80(NULL),simSong20(NULL), simSong32(NULL), simHei40(NULL){}	
	SingletonHelper(const SingletonHelper& rval){}
	~SingletonHelper();
	
public:
	//for get and remove the only instance
	static SingletonHelper* getInstance();
	static void removeInstance();

	void setPtrData(void *data);
	void* getPtrData();

	void setIntData(int data);
	int getIntData();

	void setUserID(CString ID);
	CString getUserID();

	void setUserName(CString &username);
	CString getUsername();
	
	void setUserPass(CString &pass);
	CString getUserPass();

	void setUserRight(CString &right);
	CString getUserRight();

	void setTableName(CString &talbeName);
	CString getTableName();

	void setIndexName(CString &indexName);
	CString getIndexName();

	void setKeyWord(CString &keyWord);
	CString getKeyWord();

	void setMaterials(CString &materials);
	std::string getMaterials();

	void setFormulaWeigh(CString weight);
	CString getFormulaWeigh();

	void setWeighPerPack(double weigh);
	double getWeighPerPack();

	void setSepWeighWindowPtr(void* ptr);
	void* getSepWieghWindowPtr();

	
	void setFormulaID(CString formulaID);
	CString getFormulaID();

	void setFormulaName(CString formulaName);
	CString getFormulaName();
	
	void setCom1BaudRate(CString rate);
	CString getCom1BaudRate();

	void setCom2BaudRate(CString rate);
	CString getCom2BaudRate();

	void setRecordID(CString id);
	CString getRecordID();

	void setLineNumber(CString lineNumber);
	CString getLineNumber();

	HANDLE com1;
	HANDLE com2;
	
	//public vector for the formula
	std::vector<composition*> compositions;
	void clearCompositions();
	
	//global fonts
	CFont*	    simhei80;
	CFont*		simSong20;
	CFont*		simSong32;
	CFont*		simHei40;
	
	//global COLORREF
	COLORREF backgroundColor;
	COLORREF textColor;
	COLORREF buttonColor;

	const static int screenWidth = 1024;
	const static int screenHeight = 768;

	void initFonts();

private:
	void deleteFonts();

};

namespace HelperFunctions
{
	bool isDouble(CEdit* editControl);
	bool isBatchNumber(CEdit* editControl);
	void ParseKeywords(const std::string& keyword,
					   const std::string& separators, 
					   std::vector<std::string>& keywords);
	void initListHeader(CListCtrl &listCtrl, 
						std::vector<std::string> &headerVector,
						std::vector<int> &headerLengthVector);
	void refreshList(CListCtrl &listCtrl,
					 CString &tableName);

	//communication related functions
	int initCom(HANDLE& com, CString port, int rate);
	CString readCom(HANDLE comPort);
	int closeCom(HANDLE &com);

	CString doubleToCString(double aDouble);
	CString intToCString(int aInt);
	void showStatus(CStatic& statusStatic);
	void setButtonStyle(CButton& button, COLORREF bgColor, CFont* pFont, bool reDraw = TRUE , bool blFlat = FALSE);

	CString getCurrentDate();
	CString getCurrentTime();

	void printLabel(CString name, CString weigh, CString lineNumber);
	void printVector(CString tilte, std::vector<CString>& headerList, std::vector<CString>& valueList);
	void updateRecordValueVector(_RecordsetPtr& pRecordset, std::vector<CString>& valueList, std::vector<CString>& headerList);

	unsigned long time2gmt(CTime& timeparam);

};
#endif