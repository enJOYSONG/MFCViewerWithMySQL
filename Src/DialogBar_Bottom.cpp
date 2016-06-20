// Bottom.cpp : implementation file
//

#include "stdafx.h"
#include "RealBX_ModelEditor.h"
#include "DialogBar_Bottom.h"
#include "RBX_Model.h"
#include "afxdialogex.h"


// Bottom dialog

IMPLEMENT_DYNAMIC(CDialogBar_Bottom, CDialogBar)

CDialogBar_Bottom::CDialogBar_Bottom()
: m_TypeValue(0)
{
}

CDialogBar_Bottom::~CDialogBar_Bottom()
{
}

void CDialogBar_Bottom::DoDataExchange(CDataExchange* pDX)
{
	CDialogBar::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO1, (int &)m_TypeValue);
}

void CDialogBar_Bottom::SetModel(CRBX_Model* model)
{
	 m_Model = model;
	 SetModelInfo();
}


void CDialogBar_Bottom::SetModelInfo() 
{
	//m_EditType = ((CEdit*)GetDlgItem(ID_TYPE)) ;
	m_EditDisplayName = ((CEdit*)GetDlgItem(IDC_DISNAME)) ;
	m_EditDisplayName->LimitText(29);
	m_EditFileName = ((CEdit*)GetDlgItem(IDC_FILE)) ;

	CString result ;//= m_Model->m_strType;
	//m_EditType->SetWindowText(result);
	
	m_TypeValue = m_Model->m_Type;
	UpdateData(FALSE);
	
	result = m_Model->m_strDisplayName;
	m_EditDisplayName->SetWindowText(result);

	result = m_Model->m_strFileName;
	m_EditFileName->SetWindowText(result);
}

void CDialogBar_Bottom::UpdateModelInfo() 
{
		//m_EditType = ((CEdit*)GetDlgItem(ID_TYPE)) ;
		m_EditDisplayName = ((CEdit*)GetDlgItem(IDC_DISNAME)) ;
		m_EditDisplayName->LimitText(29);
		m_EditFileName = ((CEdit*)GetDlgItem(IDC_FILE)) ;

		CString result;
		UpdateData(false);
//		m_EditType->GetWindowText(result);
		m_Model->m_Type = m_TypeValue;

		m_EditDisplayName->GetWindowText(result);
		m_Model->m_strDisplayName = result;

		m_EditFileName->GetWindowText(result);
		m_Model->m_strFileName = result;
}


void CDialogBar_Bottom::DeleteModel()
{
	m_Model = NULL;
	m_Model = new CRBX_Model;
	SetModelInfo();
}

void CDialogBar_Bottom::SetType(UINT value) 
{
	UpdateData(true);
	switch(value) 
	{
		case IDC_RADIO1:
			m_TypeValue = MODEL_TYPE_WEAPON;
			break;
		case IDC_RADIO2:
			m_TypeValue = MODEL_TYPE_VEHICLE;
			break;
		case IDC_RADIO3:
			m_TypeValue = MODEL_TYPE_SOLDIER;
			break;
		case IDC_RADIO4:
			m_TypeValue = MODEL_TYPE_BUILDING;
			break;
		case IDC_RADIO5:
			m_TypeValue = MODEL_TYPE_NONE;
			break;
		default:
			break;
	
	}
}

BEGIN_MESSAGE_MAP(CDialogBar_Bottom, CDialogBar)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_RADIO1, IDC_RADIO5, CDialogBar_Bottom::SetType)
	ON_EN_CHANGE(IDC_DISNAME, &CDialogBar_Bottom::OnEnChangeDisname)
END_MESSAGE_MAP()


// Bottom message handlers


void CDialogBar_Bottom::OnEnChangeDisname()
{
	m_EditDisplayName = ((CEdit*)GetDlgItem(IDC_DISNAME)) ;
	m_EditDisplayName->LimitText(29);

	UpdateData(true);
}
