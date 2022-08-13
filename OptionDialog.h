#pragma once
#include "afxdialogex.h"


// COptionDialog dialog

class COptionDialog : public CDialog
{
	DECLARE_DYNAMIC(COptionDialog)

public:
	COptionDialog(bool bRowColumn, CWnd* pParent = nullptr);   // standard constructor
	virtual ~COptionDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_OPTIONS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CStatic m_ctrlStaticText1;
	CStatic m_ctrlStaticText2;
	int m_nValue1;
	int m_nValue2;
	afx_msg void OnBnClickedButtonDefaults();
	virtual BOOL OnInitDialog();

private:
	bool m_bRowColumnDialog;
};
