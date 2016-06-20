#ifndef RBX_MODELVIEWMANAGER_H
#define RBX_MODELVIEWMANAGER_H


class CRBX_ModelView;
class CRBX_ModelViewCtrl;
class CRBX_ModelViewManager
{
public:
	CRBX_ModelViewManager();
	~CRBX_ModelViewManager();

	void Init();
	void DeInit();
	void SetEntity(const char* strFileName);
	void DeleteEntity();

private:
	CRBX_ModelView* m_pModelView;
	CRBX_ModelViewCtrl* m_pModelViewCtrl;
};

#endif