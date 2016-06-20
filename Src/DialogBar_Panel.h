#ifndef CDIALOGBAR_PANEL_H
#define CDIALOGBAR_PANEL_H
#include "afxwin.h"

class CChildView;
class RBX_DataManager;

class CDialogBar_Panel : public CDialogBar
{
	DECLARE_DYNAMIC(CDialogBar_Panel)

public:
	CDialogBar_Panel();   // standard constructor
	virtual ~CDialogBar_Panel();
	void init();
	void ReInit();
	void SetDataManager(RBX_DataManager* dataManager) { m_DataManager = dataManager; }
	void InitWeaponDisplayNameOption();
	void SetChildView(CChildView* childview){ childview_ = childview; }
// Dialog Data
	enum { IDD = IDD_DIALOGBAR_PANEL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

private:
	CMFCPropertyGridCtrl* m_wndPropList;
	RBX_DataManager* m_DataManager;

	CMFCPropertyGridProperty* pAddPropWeapon;
	CMFCPropertyGridProperty* pAddGroupBullet;
	CMFCPropertyGridProperty* pAddGroupParticle;
	CMFCPropertyGridProperty* pAddGroupSound;
	CMFCPropertyGridProperty* pAddGroupModel;

	CChildView* childview_;
	
public:
	afx_msg LRESULT OnPropertyChanged (WPARAM,LPARAM);
	afx_msg void OnUpdateCmdUI(CCmdUI* pCmdUI);//다이얼로그바 버튼활성화
	afx_msg void OnBnClickedSave();

	afx_msg void OnBnClickedDelete();
};
#endif
