#pragma once


// ChangeManufactureNameDialog dialog

#include "afxwin.h"

class ChangeManufactureNameDialog : public CDialog
{
	DECLARE_DYNAMIC(ChangeManufactureNameDialog)

public:
	ChangeManufactureNameDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~ChangeManufactureNameDialog();
	CBrush   m_brBk;//��public�ж���  


// Dialog Data
	enum { IDD = IDD_CHANGEMANUFACTURENAME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CButton m_ButtonOK;
	CButton m_ButtonCancel;
};
