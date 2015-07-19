#include "..\StdAfx.h"


class RecordSetPointer :public SingletonTemplateBase<RecordSetPointer>
{
public:
	RecordSetPointer();
	void execSQL();
	void setSqlState(CString& sqlState);
	void setDatabaseConnection(_ConnectionPtr& connection);
	void closeRecordSet();
	_RecordsetPtr& getRecordPtr();
private:
	_RecordsetPtr m_RecordPointer;
	CString m_SqlSate;
	_ConnectionPtr m_DatabaseConnection;

};