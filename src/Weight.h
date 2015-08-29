// Weight.h : main header file for the WEIGHT application
//

#if !defined(AFX_WEIGHT_H__A071A098_078B_4082_820F_A616C325BEDC__INCLUDED_)
#define AFX_WEIGHT_H__A071A098_078B_4082_820F_A616C325BEDC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols


/////////////////////////////////////////////////////////////////////////////
// CWeightApp:
// See Weight.cpp for the implementation of this class
//

class CWeightApp : public CWinApp
{
public:
	CWeightApp();
	~CWeightApp();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWeightApp)
	public:
		virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CWeightApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL m_bATLInited;
private:
	BOOL InitATL();
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WEIGHT_H__A071A098_078B_4082_820F_A616C325BEDC__INCLUDED_)
