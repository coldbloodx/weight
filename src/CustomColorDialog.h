#pragma once


// CCustomColorDialog dialog

class CCustomColorDialog : public CDialog
{
	DECLARE_DYNAMIC(CCustomColorDialog)

public:
	CCustomColorDialog(CWnd* pParent = NULL);   // standard constructor
	explicit CCustomColorDialog(UINT nIDTemplate, CWnd* pParentWnd = NULL);
	virtual ~CCustomColorDialog();
	HBRUSH hBrush;
// Dialog Data
	enum { IDD = IDD_COLORDIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
