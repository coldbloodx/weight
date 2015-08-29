#include "stdafx.h"
#include "DBptr.h"
#include "DBConnector.h"


SQLExecutor::SQLExecutor():sqlstr("")
{
	//init m_SqlSate as empty
}

void SQLExecutor::closeRecordSet()
{
	if (resultptr == NULL)
	{
		return;
	}
	ASSERT(resultptr);
	try
	{
		resultptr->Close();
		resultptr = NULL;
	}
	catch (_com_error& e)
	{
		throw e;
		return;
	}
	
	return;
}

_RecordsetPtr& SQLExecutor::execquery(CString sqlstr)
{
    this->dbcon = DBConnector::getInstanceRef().getdbcon();

    try
    {
        resultptr.CreateInstance("ADODB.Recordset");
        resultptr->Open(_variant_t(sqlstr),
            _variant_t((IDispatch*)dbcon,true),
            adOpenStatic,
            adLockOptimistic,
            adCmdText);
    }
    catch(_com_error &e)
    {
        throw e;
    }

    return this->resultptr;
}



void SQLExecutor::execSQL()
{

	try
	{
		resultptr.CreateInstance("ADODB.Recordset");
		resultptr->Open(_variant_t(sqlstr),
			_variant_t((IDispatch*)dbcon,true),
			adOpenStatic,
			adLockOptimistic,
			adCmdText);
	}
	catch(_com_error &e)
	{
		throw e;
		return;
	}
}

void SQLExecutor::setSqlState(CString& sqlState)
{
	this->sqlstr = sqlState;
	return;
}

void SQLExecutor::setDatabaseConnection(_ConnectionPtr& connection)
{
	this->dbcon = connection;
}

_RecordsetPtr& SQLExecutor::getRecordPtr()
{
	return resultptr;
}