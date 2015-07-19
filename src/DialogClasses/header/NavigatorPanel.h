#if !defined(AFX_NAVIGATORPANEL_H__FDE7B6ED_D869_4B90_BEDE_8A0663714100__INCLUDED_)
#define AFX_NAVIGATORPANEL_H__FDE7B6ED_D869_4B90_BEDE_8A0663714100__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NavigatorPanel.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNavigatorPanel dialog
#include "..\..\CustomColorDialog.h"


class CNavigatorPanel : public CCustomColorDialog
{
	// Construction
public:
	CNavigatorPanel(CWnd* pParent = NULL);   // standard constructor

	//interface for set job string and user name
	void setJobString(const CString& jobString);
	void setUserName(const CString& userName);		

	//make the global access interface
	static CNavigatorPanel* getNavigatorPanelPtr();
	static void removeInstance();
	// Dialog Data
	//{{AFX_DATA(CNavigatorPanel)
	enum { IDD = IDD_NAVIGATOR_PANEL };

	//}}AFX_DATA
	
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNavigatorPanel)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
private:
	CStatic	m_User;
	CStatic	m_Time;
	CStatic	m_Job;
	CStatic	m_Date;
	
	//the only instance
	static CNavigatorPanel* m_Instance;

	//timer ID
	static const int TIMERID;
	// Implementation
protected:
	
	// Generated message map functions
	//{{AFX_MSG(CNavigatorPanel)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NAVIGATORPANEL_H__FDE7B6ED_D869_4B90_BEDE_8A0663714100__INCLUDED_)
