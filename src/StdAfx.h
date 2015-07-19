// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__2B702DE7_A9D8_4F63_AE5A_685C9D82DD51__INCLUDED_)
#define AFX_STDAFX_H__2B702DE7_A9D8_4F63_AE5A_685C9D82DD51__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers
#define WINVER      0x0502
#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include "OtherClasses\SingletonTemplateBase.h"

#import "c:\program files\common files\system\ado\msado15.dll" no_namespace rename("EOF","adoEOF")

#endif // _AFX_NO_AFXCMN_SUPPORT


	#define _ATL_APARTMENT_THREADED
#include <atlbase.h>
//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
class CWeightModule : public CComModule
{
public:
	LONG Unlock();
	LONG Lock();
	DWORD dwThreadID;
};
extern CWeightModule _Module;
#include <atlcom.h>

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__2B702DE7_A9D8_4F63_AE5A_685C9D82DD51__INCLUDED_)
