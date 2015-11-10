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


	//�û��ı�ʶ���û�ID�����û�������
	CString userID;
	CString userName;
	CString userPass;
	CString userRight;


	//�䷽ID���䷽���֣��䷽����
	CString formulaID;
	CString formulaName;
	CString formulaWeigh;


	std::string materials;

	double      weighPerPack;

	//����
	CString lineNumber;

private:
	static  SingletonHelper* m_instance;
	
	//make the constructor private, so others can't create instances.
private:
	SingletonHelper():ptrData(NULL), intData(0),simhei80(NULL),defaultFont(NULL), simHei40(NULL){}	
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
	
	void setLineNumber(CString lineNumber);
	CString getLineNumber();

	HANDLE com1;
	HANDLE com2;
	
	//public vector for the formula
	std::vector<composition*> compositions;
	void clearCompositions();
	
	//global fonts
	CFont*	    simhei80;
	CFont*		defaultFont;
	CFont*		simHei40;
	CFont*		simHei30;
	
	void initFonts();

private:
	void deleteFonts();

};

namespace utils
{
	bool isDouble(CEdit* editControl);
	bool isBatchNumber(CEdit* editControl);
	void ParseKeywords(const std::string& keyword,
					   const std::string& separators, 
					   std::vector<std::string>& keywords);

	//communication related functions
	int initCom(HANDLE& com, CString port, int rate);
	CString readCom(HANDLE comPort);
	int closeCom(HANDLE &com);

	CString doubleToCString(double aDouble);
	CString intToCString(int aInt);
	double cstr2double(CString cstr);

	void showStatus(CStatic& statusStatic);

	CString getCurrentDate();
	CString getCurrentTime();
	CString gettimestamp();

	void printLabel(CString name, CString weigh, CString lineNumber);
	void printVector(CString tilte, std::vector<CString>& headerList, std::vector<CString>& valueList);
	
	unsigned long time2gmt(CTime& timeparam);
	bool isready();
	double sumdbcol(_RecordsetPtr& pRecordset, CString key);

};
#endif