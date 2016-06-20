#include "RBX_StdAfx.h"
#include "RBX_ModelView.h"
#include "RBX_ModelViewCtrl.h"

CRBX_ModelView::CRBX_ModelView(VGUIMainContext* pContext)
{
	InitDialog(pContext,NULL,NULL);
	OnInitDialog();

	//ShowDialog
	pContext->ShowDialog(this);
	
}

CRBX_ModelView::~CRBX_ModelView()
{
}

void CRBX_ModelView::OnInitDialog()
{
	VDialog::OnInitDialog();
	SetPosition(0,0);
	SetSize(Vision::Video.GetXRes(),Vision::Video.GetYRes());

	m_pModelViewCtrl = new CRBX_ModelViewCtrl();
	m_pModelViewCtrl->SetSize(Vision::Video.GetXRes(),Vision::Video.GetYRes());
	AddControl(m_pModelViewCtrl);
}

void CRBX_ModelView::UpdateViewSize()
{
	int SizeX = Vision::Video.GetXRes();
	int SizeY = Vision::Video.GetYRes();
	SetSize(SizeX,SizeY);
	m_pModelViewCtrl->SetSize(SizeX,SizeY);
	m_pModelViewCtrl->SetFitModel();
}