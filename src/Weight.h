// Weight.h : main header file for the WEIGHT application
//

#if !defined(AFX_WEIGHT_H__A071A098_078B_4082_820F_A616C325BEDC__INCLUDED_)
#define AFX_WEIGHT_H__A071A098_078B_4082_820F_A616C325BEDC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
#endif

#include "resource.h"		
#include "users.h"

class CWeightApp : public CWinApp
{
public:
	CWeightApp();
	~CWeightApp();

	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	static CWeightApp* getapp();

	static CString getuserid();
	static CString getuserpass();
	static CString getusername();
	static USERPERM getuserperm();

	// for current login user
	User* puser;

	DECLARE_MESSAGE_MAP()
private:
	BOOL m_bATLInited;
private:
	BOOL InitATL();
};

#endif
