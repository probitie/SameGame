// OptionDialog.cpp : implementation file
//

#include "pch.h"
#include "SameGame.h"
#include "afxdialogex.h"
#include "OptionDialog.h"


// COptionDialog dialog

IMPLEMENT_DYNAMIC(COptionDialog, CDialog)

COptionDialog::COptionDialog(bool bRowColumn, CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG_OPTIONS, pParent)
	, m_nValue1(0)
	, m_nValue2(0)
	, m_bRowColumnDialog(bRowColumn)
{

}

COptionDialog::~COptionDialog()
{
}

void COptionDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_TEXT_1, m_ctrlStaticText1);
	DDX_Control(pDX, IDC_STATIC_TEXT_2, m_ctrlStaticText2);
	DDX_Text(pDX, IDC_EDIT_VALUE_1, m_nValue1);
	DDX_Text(pDX, IDC_EDIT_VALUE_2, m_nValue2);
}


BEGIN_MESSAGE_MAP(COptionDialog, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_DEFAULTS, &COptionDialog::OnBnClickedButtonDefaults)
END_MESSAGE_MAP()


// COptionDialog message handlers


void COptionDialog::OnBnClickedButtonDefaults()
{
	// дефолтные значения завезти с CSameGameBoard
	// Отдельно рассматриваем два варианта
	if (m_bRowColumnDialog)
		m_nValue1 = m_nValue2 = 15; // размер доски 15x15
	else
		m_nValue1 = m_nValue2 = 35; // размер блоков 35x35

	  // Обновляем параметры элементов до новых значений
	UpdateData(false);
}


BOOL COptionDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	if (m_bRowColumnDialog)
	{
		// Сначала обновляем заголовок диалогового окна
		SetWindowText(_T("Update Block Count"));

		// Затем обновляем элементы «Static Text»
		m_ctrlStaticText1.SetWindowText(_T("rows"));
		m_ctrlStaticText2.SetWindowText(_T("columns"));
	}
	else
	{
		// Сначала обновляем заголовок диалогового окна
		SetWindowText(_T("Update Block Size"));

		// Затем обновляем элементы «Static Text»
		m_ctrlStaticText1.SetWindowText(_T("block width"));
		m_ctrlStaticText2.SetWindowText(_T("block height"));
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}
