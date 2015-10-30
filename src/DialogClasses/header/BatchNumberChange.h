#pragma once
#include "afxwin.h"


class CBatchNumberChange : public CDialog
{
	DECLARE_DYNAMIC(CBatchNumberChange)

public:
	CBatchNumberChange(CWnd* pParent = NULL);   // standard constructor
	virtual ~CBatchNumberChange();

// Dialog Data
	enum { IDD = IDD_BATCHNUMBERCHANGE };
	
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	
	DECLARE_MESSAGE_MAP()
public:
	CButton m_ButtonOK;
	CButton m_ButtonCancel;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();

	CEdit m_BatchNumber;
};
