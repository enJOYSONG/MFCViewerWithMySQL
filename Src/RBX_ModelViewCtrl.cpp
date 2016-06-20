#include "RBX_StdAfx.h"
#include "RBX_ModelViewCtrl.h"

CRBX_ModelViewCtrl::CRBX_ModelViewCtrl()
{
	m_pEntity = NULL;
	m_pLight = NULL;
	m_fYawSpeed = 10.f; 
	m_fFovH = 90.f;
	m_fFovV = 0.f;

	 // Load the axis-model for the global coordinate-system-axis representation
	m_pWorldAxisEntity = Vision::Game.CreateEntity("VisBaseEntity_cl", hkvVec3(0,0,0), "Models\\Models_Etc\\WorldAxis.model");
	m_pWorldAxisEntity->SetAlwaysInForeGround();  
	m_pWorldAxisEntity->SetAmbientColor(V_RGBA_WHITE);
	m_pWorldAxisEntity->SetScaling(0.5);

	SetBkgColor(120,120,120);
	UpdateWorldAxisSystem();
}

CRBX_ModelViewCtrl::~CRBX_ModelViewCtrl()
{
	V_SAFE_DISPOSEOBJECT(m_pEntity);
	V_SAFE_DISPOSEOBJECT(m_pWorldAxisEntity);
	V_SAFE_DISPOSEOBJECT(m_pLight);
}

void CRBX_ModelViewCtrl::OnPaint(VGraphicsInfo &Graphics, const VItemRenderInfo &parentState)
{
}
void CRBX_ModelViewCtrl::OnDragBegin(const hkvVec2 &vMousePos, int iButtonMask)
{
}
void CRBX_ModelViewCtrl::OnDragging(const hkvVec2 &vMouseDelta)
{
}
void CRBX_ModelViewCtrl::OnTick(float dtime)
{
	if (m_pEntity)
	{
		m_pEntity->IncOrientation(dtime*m_fYawSpeed,0,0);
		m_pEntity->HandleAnimations(dtime);
		m_pWorldAxisEntity->SetOrientation(m_pEntity->GetOrientation());
	}
}

void CRBX_ModelViewCtrl::OnMouseEnter(VGUIUserInfo_t &user)
{
}
void CRBX_ModelViewCtrl::OnMouseLeave(VGUIUserInfo_t &user)
{
}

void CRBX_ModelViewCtrl::SetEntity(VisBaseEntity_cl *pEntity)
{
	V_SAFE_DISPOSEOBJECT(m_pEntity);
	m_pEntity = pEntity;	
  
	hkvAlignedBBox modelbox;
	m_pEntity->GetMesh()->GetVisibilityBoundingBox(modelbox);
	
	hkvVec3 vPos = m_pEntity->GetPosition();

	vPos.z += -modelbox.m_vMin.z;
	m_pEntity->SetPosition(vPos);

	SetFitModel();
}

void CRBX_ModelViewCtrl::DeleteEntity()
{
	if(!m_pEntity) return;
	m_pEntity->DisposeObject();

}

void CRBX_ModelViewCtrl::SetFitModel()
{
	if(!m_pEntity) return;  
 
	m_fFovV = hkvMathHelpers::getFovY(m_fFovH, GetSize().x / GetSize().y);

	VisRenderContext_cl::GetMainRenderContext()->SetFOV(m_fFovH,m_fFovV);

	hkvAlignedBBox modelbox;
	m_pEntity->GetMesh()->GetVisibilityBoundingBox(modelbox);
	float fAngleH,fAngleV;
	VisRenderContext_cl::GetMainRenderContext()->GetFOV(fAngleH,fAngleV);

	float dx = hkvMath::Max(modelbox.getSizeX(),modelbox.getSizeY());
	float zx = 0.5f*dx / hkvMath::tanDeg (fAngleH*0.5f);
	float zy = 0.5f*modelbox.getSizeZ() / hkvMath::tanDeg (fAngleV*0.5f);
	
	float Dist = (hkvMath::Max(zx,zy) + dx*0.5f);

	VisContextCamera_cl* pMainCamera = Vision::Camera.GetMainCamera();
	hkvMat3 vMat;
	vMat.setFromEulerAngles(0,20,180);

	m_vCamPos.Set(Dist,0,modelbox.GetSizeZ());
	pMainCamera->Set(vMat,m_vCamPos);	
	
	if( m_pLight == NULL ) {
		m_pLight = new VisLightSource_cl( VisLightSourceType_e::VIS_LIGHT_DIRECTED , 10.0f );
	}

	m_pLight->SetPosition(pMainCamera->GetPosition());
	m_pLight->AttachToParent(pMainCamera);
	m_pLight->SetDirection(pMainCamera->GetDirection());
	m_pLight->SetIntensity(50.0f);		/// << 빛의 강도를 조절함.  나중에콜백이나 업데이트 함수에서 조절하시면됩니다.
	
	UpdateWorldAxisSystem();
}

void CRBX_ModelViewCtrl::UpdateWorldAxisSystem(void)
{
  hkvVec3 direction;
  hkvVec3 startPosition;

  // Set the pixelposition in screenspace.
  float xPos = 7.0f * (float)Vision::Video.GetXRes() / 100.0f;
  float yPos = (float)Vision::Video.GetYRes() - 10.0f * (float)Vision::Video.GetYRes() / 100.0f;

  // Get camera position and the direction at the calculated pixelposition.
  Vision::Contexts.GetCurrentContext()->GetTraceDirFromScreenPos(xPos, yPos,direction,10.f);
  Vision::Renderer.GetRendererNode(0)->GetReferenceContext()->GetCamera()->GetPosition(startPosition);

  // Update the position of the world axis representation.
  m_pWorldAxisEntity->SetPosition(startPosition + direction);
}

void CRBX_ModelViewCtrl::SetBkgColor(UCHAR r, UCHAR g, UCHAR b)
{
  VisionRenderLoop_cl *pRL = (VisionRenderLoop_cl *)VisRenderContext_cl::GetMainRenderContext()->GetRenderLoop();
  VColorRef clearColor = Vision::Renderer.GetDefaultClearColor();
  clearColor.SetNoAlpha(VColorRef(r,g,b));
  Vision::Renderer.SetDefaultClearColor(clearColor);
}
