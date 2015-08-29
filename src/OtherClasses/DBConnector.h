#include "StdAfx.h"

class DBConnector : public SingletonTemplateBase<DBConnector>
{
public:
	DBConnector();
	_ConnectionPtr& getdbcon();
	void openDatabaseConnection() ;
	void closeDatabaseConnection();
	void setConnectString(std::string& connectString);

private:
	_ConnectionPtr m_ConnectionPtr;
	std::string m_ConnectString;
};