#ifndef RBX_VIEW3D_H
#define RBX_VIEW3D_H

class CRBX_ModelViewCtrl;
class CRBX_ModelView:public VDialog
{
public:
	CRBX_ModelView(VGUIMainContext* pContextr);
	virtual ~CRBX_ModelView();
	void OnInitDialog();
	CRBX_ModelViewCtrl* GetModelViewCtrl() { return m_pModelViewCtrl;}
	void UpdateViewSize();
private:
	void InitControls();
	CRBX_ModelViewCtrl* m_pModelViewCtrl;
};

#endif