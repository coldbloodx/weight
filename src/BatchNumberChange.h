#pragma once
#include "afxwin.h"


// CBatchNumberChage dialog


class CBatchNumberChage : public CDialog
{
	DECLARE_DYNAMIC(CBatchNumberChage)

public:
	CBatchNumberChage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CBatchNumberChage();

// Dialog Data
	enum { IDD = IDD_BATCHNUMBERCHANGE };
	
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	
	DECLARE_MESSAGE_MAP()
public:
	CButton m_ButtonOK;
	CButton m_ButtonCancel;
	CBrush   m_brBk;//在public中定义   
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CEdit m_BatchNumber;
};
