#include "..\StdAfx.h"

class DatabaseConnector : public SingletonTemplateBase<DatabaseConnector>
{
public:
	DatabaseConnector();
	_ConnectionPtr& getDatabaseConnection();
	void openDatabaseConnection() ;
	void closeDatabaseConnection();
	void setConnectString(std::string& connectString);

private:
	_ConnectionPtr m_ConnectionPtr;
	std::string m_ConnectString;
};