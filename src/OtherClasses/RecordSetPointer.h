#include "StdAfx.h"


class RecordSetPointer :public SingletonTemplateBase<RecordSetPointer>
{
public:
	RecordSetPointer();
	void execSQL();
	void setSqlState(CString& sqlState);
	void setDatabaseConnection(_ConnectionPtr& connection);
	void closeRecordSet();
	_RecordsetPtr& getRecordPtr();

    _RecordsetPtr& execquery(CString sqlstr);

private:
	_RecordsetPtr resultptr;
	CString sqlstr;
	_ConnectionPtr dbcon;

};