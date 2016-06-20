#ifndef RBX_MODELVIEWCTRL_H
#define RBX_MODELVIEWCTRL_H

class CRBX_ModelViewCtrl: public VDlgControlBase
{
public:
	CRBX_ModelViewCtrl();
	~CRBX_ModelViewCtrl();

	virtual void OnPaint(VGraphicsInfo &Graphics, const VItemRenderInfo &parentState);
	virtual void OnDragBegin(const hkvVec2 &vMousePos, int iButtonMask);
	virtual void OnDragging(const hkvVec2 &vMouseDelta);
	virtual void OnTick(float deltaTime);
	virtual void OnMouseEnter(VGUIUserInfo_t &user);
	virtual void OnMouseLeave(VGUIUserInfo_t &user);

	void SetEntity(VisBaseEntity_cl *pEntity);
	VisBaseEntity_cl* GetEntity() { return m_pEntity;}
	void SetFitModel();
	const hkvVec3& GetCamPos() { return m_vCamPos;}
	void DeleteEntity();
	
private:
	void SetBkgColor(UCHAR r, UCHAR g, UCHAR b);
	void UpdateWorldAxisSystem();
	float m_fFovH,m_fFovV;

	VisBaseEntity_cl* m_pEntity;
	VisBaseEntity_cl* m_pWorldAxisEntity;
	float m_fYawSpeed;
	hkvVec3 m_vCamPos;

	VisLightSource_cl* m_pLight;
};


#endif