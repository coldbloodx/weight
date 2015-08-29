#include "stdafx.h"
#include "DBConnector.h"

DBConnector::DBConnector():m_ConnectString("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=weight.mdb")
{
	//empty constructor
}

void DBConnector::closeDatabaseConnection()
{
	if (m_ConnectionPtr == NULL)
	{
		return;
	}
	try
	{
		m_ConnectionPtr->Close();
		m_ConnectionPtr = NULL;
	}
	catch (_com_error& e)
	{
		throw e;
		return;
	}

}

void DBConnector::openDatabaseConnection()
{
	try
	{
		m_ConnectionPtr.CreateInstance(__uuidof(Connection));
		m_ConnectionPtr->Open(m_ConnectString.c_str(),"","",adModeUnknown);
	}
	catch(_com_error &e)
	{
		throw e;
		return;
	}
	return;
}

_ConnectionPtr& DBConnector::getdbcon()
{
	return this->m_ConnectionPtr;
}

void DBConnector::setConnectString(std::string& connectString)
{
	this->m_ConnectString = connectString;
	return;
}