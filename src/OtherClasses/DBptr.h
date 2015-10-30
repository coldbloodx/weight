#include "StdAfx.h"


class SQLExecutor :public SingletonTemplateBase<SQLExecutor>
{
public:
	SQLExecutor();
	void closeRecordSet();
    _RecordsetPtr& execquery(CString sqlstr);

private:
	_RecordsetPtr resultptr;
	CString sqlstr;
	_ConnectionPtr dbcon;

};