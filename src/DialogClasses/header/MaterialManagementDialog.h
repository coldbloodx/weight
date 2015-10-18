#if !defined(AFX_MATERIALMANAGEMENTDIALOG_H__2F86AEC9_59F6_4C07_9E03_85DB7926B3A2__INCLUDED_)
#define AFX_MATERIALMANAGEMENTDIALOG_H__2F86AEC9_59F6_4C07_9E03_85DB7926B3A2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "afxwin.h"

class CMaterialManagementDialog : public CDialog
{
// Construction
public:
	CMaterialManagementDialog(CWnd* pParent = NULL);   // standard constructor
	~CMaterialManagementDialog();
	void initList();

	enum { IDD = IDD_MATERIALMANAGEMENT_DIALOG };
	CStatic	m_StatusStatic;
	CButton	m_ButtonOK;
	CButton	m_Del;
	CButton	m_Add;
	CListCtrl m_MaterialList;

	std::vector<CButton*> buttonVector;


	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    

private:
	void initListHeader();

protected:
	virtual BOOL OnInitDialog();
	afx_msg void OnMaterialadd();
	afx_msg void OnMaterialdel();
	DECLARE_MESSAGE_MAP()
public:
	CButton m_BatchNumberChange;
	afx_msg void OnBnClickedBatchnumberchange();
};

#endif 
