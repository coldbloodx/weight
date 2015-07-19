#include "stdafx.h"
#include "DatabaseConnector.h"

DatabaseConnector::DatabaseConnector():m_ConnectString("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=weight.mdb")
{
	//empty constructor
}

void DatabaseConnector::closeDatabaseConnection()
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

void DatabaseConnector::openDatabaseConnection()
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

_ConnectionPtr& DatabaseConnector::getDatabaseConnection()
{
	return this->m_ConnectionPtr;
}

void DatabaseConnector::setConnectString(std::string& connectString)
{
	this->m_ConnectString = connectString;
	return;
}