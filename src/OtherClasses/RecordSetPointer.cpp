#include "stdafx.h"
#include "RecordSetPointer.h"


RecordSetPointer::RecordSetPointer():m_SqlSate("")
{
	//init m_SqlSate as empty
}

void RecordSetPointer::closeRecordSet()
{
	if (m_RecordPointer == NULL)
	{
		return;
	}
	ASSERT(m_RecordPointer);
	try
	{
		m_RecordPointer->Close();
		m_RecordPointer = NULL;
	}
	catch (_com_error& e)
	{
		throw e;
		return;
	}
	
	return;
}

void RecordSetPointer::execSQL()
{
	try
	{
		m_RecordPointer.CreateInstance("ADODB.Recordset");
		m_RecordPointer->Open(_variant_t(m_SqlSate),
			_variant_t((IDispatch*)m_DatabaseConnection,true),
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
	this->m_SqlSate = sqlState;
	return;
}

void RecordSetPointer::setDatabaseConnection(_ConnectionPtr& connection)
{
	this->m_DatabaseConnection = connection;
}

_RecordsetPtr& RecordSetPointer::getRecordPtr()
{
	return m_RecordPointer;
}