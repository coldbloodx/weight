#include "stdafx.h"
#include "users.h"
#include "helperclass.h"
#include "DBptr.h"

User::User(){}
User::~User() {}

CString User::getname()
{
	return this->username;
}

CString User::getid()
{
	return this->userid;
}

CString User::getpass()
{
	return this->password;
}

USERPERM User::getperm()
{
	return this->permission;
}


void User::setpass(CString password)
{
	this->password = password;
}

bool User::isadmin()
{
	return permission == UTYPE_ADMIN;
}

bool User::adduser(CString name, CString pass, USERPERM perm)
{

	if(name.IsEmpty() || pass.IsEmpty()) return false;
	if(perm != UTYPE_ADMIN || perm != UTYPE_NONADMIN) return false;

	CString sql;
	sql.Format("insert into users(name, password, permission) values( '%s', '%s', '%s') " ,
		name, pass, perm == UTYPE_ADMIN ? "管理员" : "普通用户" );
	
	SQLExecutor::getInstanceRef().execquery(sql);
	
	return true;
}

User* User::getuserbyid(CString userid)
{
	if(!utils::isnumber(userid)) return NULL;
	User* puser = new User();
	CString sql;
	sql.Format("select id, name, password, permission from users where id = %s ", userid);

	_RecordsetPtr dbptr;
	try
	{
		dbptr = SQLExecutor::getInstanceRef().execquery(sql);
	}
	catch(_com_error& e)
	{
		CString errmsg((LPCTSTR)(_bstr_t)e.Description());
		return NULL;
	}

	if(dbptr->adoEOF) return NULL;

	_variant_t dbname = dbptr->GetCollect(_variant_t("name"));
	_variant_t dbpass = dbptr->GetCollect(_variant_t("password"));
	_variant_t dbperm = dbptr->GetCollect(_variant_t("permission"));
	

	if (dbname .vt == VT_NULL || dbperm.vt == VT_NULL || dbpass.vt == VT_NULL) return NULL;

	puser->userid =  userid;
	puser->username = (LPCTSTR)(_bstr_t)dbname;
	puser->password = (LPCTSTR)(_bstr_t)dbpass;
	CString csperm = (LPCTSTR)(_bstr_t)dbperm;
	
	puser->permission = (csperm == "管理员" ? UTYPE_ADMIN : UTYPE_NONADMIN);
	
	return puser;
}
