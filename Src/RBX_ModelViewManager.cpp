#include "RBX_ModelViewManager.h"
#include "RBX_ModelView.h"
#include "RBX_ModelViewCtrl.h"

CRBX_ModelViewManager::CRBX_ModelViewManager()
{
}

CRBX_ModelViewManager::~CRBX_ModelViewManager()
{
	delete m_pModelView;
}

void CRBX_ModelViewManager::Init()
{
	m_pModelViewCtrl = m_pModelView->GetModelViewCtrl();
}
void CRBX_ModelViewManager::DeInit()
{

}

void CRBX_ModelViewManager::SetEntity(const char* strFileName)
{

}