#ifndef __LA_USER_HEADER_
#define __LA_USER_HEADER_

enum USERPERM
{
	UTYPE_ADMIN = 1,
	UTYPE_NONADMIN
};

class User
{
public:
	~User();
	// getters
	CString getid();
	CString getpass();
	USERPERM getperm();
	CString getname();
	void setpass(CString password);

	// functions
	bool isadmin();

	// query user from db by userid
	static User* getuserbyid(CString userid);

	// create user by username password and permission
	bool adduser(CString name, CString pass, USERPERM perm);

private:
	User();

	CString userid;
	CString password;
	CString username;
	USERPERM permission;

};



#endif