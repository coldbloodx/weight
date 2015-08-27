#include "stdafx.h"
#include "RecordSetPointer.h"
#include "DatabaseConnector.h"


RecordSetPointer::RecordSetPointer():sqlstr("")
{
	//init m_SqlSate as empty
}

void RecordSetPointer::closeRecordSet()
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

_RecordsetPtr& RecordSetPointer::execquery(CString sqlstr)
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

void RecordSetPointer::execSQL()
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

void RecordSetPointer::setSqlState(CString& sqlState)
{
	this->sqlstr = sqlState;
	return;
}

void RecordSetPointer::setDatabaseConnection(_ConnectionPtr& connection)
{
	this->dbcon = connection;
}

_RecordsetPtr& RecordSetPointer::getRecordPtr()
{
	return resultptr;
}