#include <cctype>
#include "stdafx.h"
#include "RealBX_ModelEditor.h"
#include "DialogBar_Panel.h"
#include "RBX_Data.h"
#include "ChildView.h"
#include "MainFrm.h"
#include "RBX_DataManager.h"

#define WEAPON_LIST() m_DataManager->weapon_list_
#define BULLET_LIST() m_DataManager->bullet_list_
#define PARTICLE_LIST() m_DataManager->particle_list_
#define SOUND_LIST() m_DataManager->sound_list_
#define MODEL_LIST() m_DataManager->model_list_

IMPLEMENT_DYNAMIC(CDialogBar_Panel, CDialogBar)

CDialogBar_Panel::CDialogBar_Panel()
{
	
}

CDialogBar_Panel::~CDialogBar_Panel()
{
}

void CDialogBar_Panel::DoDataExchange(CDataExchange* pDX)
{
	CDialogBar::DoDataExchange(pDX);
}

void CDialogBar_Panel::init()
{
	
	//m_ctrlGridControl => Control 변수 // Header Column Size 설정
	m_wndPropList = ((CMFCPropertyGridCtrl*)GetDlgItem(IDC_MFCPROPERTYGRID1)) ;
	HDITEM item;
	item.cxy = 200;  // Size 
	item.mask = HDI_WIDTH;
	m_wndPropList->GetHeaderCtrl().SetItem(0, &HDITEM(item)); 

	//@ First group(select weapon)
	CMFCPropertyGridProperty* pAddGroupWeapon = new CMFCPropertyGridProperty(_T("Weapon"));
	pAddPropWeapon = new CMFCPropertyGridProperty(_T("Index"), _T(""),
		_T("Select Weapon"));

	for(map<CString, RBX_Weapon*>::iterator Iter_Pos = WEAPON_LIST().begin(); 
		Iter_Pos != WEAPON_LIST().end(); ++Iter_Pos) {
			pAddPropWeapon->AddOption(Iter_Pos->second->weapon_name_);
	}
	
	pAddPropWeapon->AllowEdit(true);
	pAddPropWeapon->SetData(DATA_TYPE::WEAPON_NAME);
	pAddGroupWeapon->AddSubItem(pAddPropWeapon);
	m_wndPropList->AddProperty(pAddGroupWeapon);

	//@ Property set
	//@ Bullet
	pAddGroupBullet = new CMFCPropertyGridProperty(_T("Bullet"));
	CMFCPropertyGridProperty* pAddPropBullet_name = new CMFCPropertyGridProperty(_T("Bullet Name"), _T(""),
		_T("Enter Bullet Name"));
	CMFCPropertyGridProperty* pAddPropBullet_size = new CMFCPropertyGridProperty(_T("Bullet Size"), _T(""),
		_T("Enter Bullet Size"));

	for(map<CString, RBX_Bullet*>::iterator Iter_Pos = BULLET_LIST().begin(); 
			Iter_Pos != BULLET_LIST().end(); ++Iter_Pos) {
		pAddPropBullet_name->AddOption(Iter_Pos->second->bullet_name_);
		CString bullet_size;
		bullet_size.Format(_T("%d"), Iter_Pos->second->bullet_size_);
		pAddPropBullet_size->AddOption(bullet_size);
	}
	pAddPropBullet_name->AllowEdit(true);
	pAddPropBullet_name->SetData(DATA_TYPE::BULLET_NAME);
	pAddGroupBullet->AddSubItem(pAddPropBullet_name);

	pAddPropBullet_size->AllowEdit(true);
	pAddPropBullet_size->SetData(DATA_TYPE::BULLET_SIZE);
	pAddGroupBullet->AddSubItem(pAddPropBullet_size);
	
	m_wndPropList->AddProperty(pAddGroupBullet);//

	//@ Particle
	pAddGroupParticle = new CMFCPropertyGridProperty(_T("Particle"));
	CMFCPropertyGridProperty* pAddPropParticle_name = new CMFCPropertyGridProperty(_T("Particle Name"), _T(""),
		_T("Enter Particle Name"));
	CMFCPropertyGridProperty* pAddPropParticle_path = new CMFCPropertyGridProperty(_T("Particle Path"), _T(""),
		_T("Enter Particle Path"));

	for(map<CString, RBX_Particle*>::iterator Iter_Pos = PARTICLE_LIST().begin(); 
			Iter_Pos != PARTICLE_LIST().end(); ++Iter_Pos) {
		pAddPropParticle_name->AddOption(Iter_Pos->second->particle_name_);
		pAddPropParticle_path->AddOption(Iter_Pos->second->particle_path_);
	}
	pAddPropParticle_name->AllowEdit(true);
	pAddPropParticle_name->SetData(DATA_TYPE::PARTICLE_NAME);
	pAddGroupParticle->AddSubItem(pAddPropParticle_name);

	pAddPropParticle_path->AllowEdit(true);
	pAddPropParticle_path->SetData(DATA_TYPE::PARTICLE_PATH);
	pAddGroupParticle->AddSubItem(pAddPropParticle_path);
	
	m_wndPropList->AddProperty(pAddGroupParticle);//

	//@ Sound
	pAddGroupSound = new CMFCPropertyGridProperty(_T("Sound"));
	CMFCPropertyGridProperty* pAddPropSound_name = new CMFCPropertyGridProperty(_T("Sound Name"), _T(""),
		_T("Enter Sound Name"));
	CMFCPropertyGridProperty* pAddPropSound_path = new CMFCPropertyGridProperty(_T("Sound Path"), _T(""),
		_T("Enter Sound Path"));

	for(map<CString, RBX_Sound*>::iterator Iter_Pos = SOUND_LIST().begin(); 
			Iter_Pos != SOUND_LIST().end(); ++Iter_Pos) {
		pAddPropSound_name->AddOption(Iter_Pos->second->sound_name_);
		pAddPropSound_path->AddOption(Iter_Pos->second->sound_path_);
	}
	pAddPropSound_name->AllowEdit(true);
	pAddPropSound_name->SetData(DATA_TYPE::SOUND_NAME);
	pAddGroupSound->AddSubItem(pAddPropSound_name);

	pAddPropSound_path->AllowEdit(true);
	pAddPropSound_path->SetData(DATA_TYPE::SOUND_PATH);
	pAddGroupSound->AddSubItem(pAddPropSound_path);
	
	m_wndPropList->AddProperty(pAddGroupSound);//

	//@ Model
	pAddGroupModel = new CMFCPropertyGridProperty(_T("Model"));
	CMFCPropertyGridProperty* pAddPropModel_name = new CMFCPropertyGridProperty(_T("Model Name"), _T(""),
		_T("Enter Model Name"));
	CMFCPropertyGridProperty* pAddPropModel_2dPath = new CMFCPropertyGridProperty(_T("Model 2D File Path"), _T(""),
		_T("Enter Model 2D File Path"));
	CMFCPropertyGridProperty* pAddPropModel_3dPath = new CMFCPropertyGridProperty(_T("Model 3D File Path"), _T(""),
		_T("Enter Model 3D File Path"));

	for(map<CString, RBX_Model*>::iterator Iter_Pos = MODEL_LIST().begin(); 
			Iter_Pos != MODEL_LIST().end(); ++Iter_Pos) {
		pAddPropModel_name->AddOption(Iter_Pos->second->model_name_);
		pAddPropModel_2dPath->AddOption(Iter_Pos->second->model_path_2d_);
		pAddPropModel_3dPath->AddOption(Iter_Pos->second->model_path_3d_);
	}
	pAddPropModel_name->AllowEdit(true);
	pAddPropModel_name->SetData(DATA_TYPE::MODEL_NAME);
	pAddGroupModel->AddSubItem(pAddPropModel_name);

	pAddPropModel_2dPath->AllowEdit(true);
	pAddPropModel_2dPath->SetData(DATA_TYPE::MODEL_2D_PATH);
	pAddGroupModel->AddSubItem(pAddPropModel_2dPath);

	pAddPropModel_3dPath->AllowEdit(true);
	pAddPropModel_3dPath->SetData(DATA_TYPE::MODEL_3D_PATH);
	pAddGroupModel->AddSubItem(pAddPropModel_3dPath);
	
	m_wndPropList->AddProperty(pAddGroupModel);//
}

void CDialogBar_Panel::ReInit()
{
	
	//Remove all property
	m_wndPropList->RemoveAll();

	//@ First group(select weapon)
	CMFCPropertyGridProperty* pAddGroupWeapon = new CMFCPropertyGridProperty(_T("Weapon"));
	pAddPropWeapon = new CMFCPropertyGridProperty(_T("Index"), _T(""),
		_T("Select Weapon"));

	for(map<CString, RBX_Weapon*>::iterator Iter_Pos = WEAPON_LIST().begin(); 
		Iter_Pos != WEAPON_LIST().end(); ++Iter_Pos) {
			pAddPropWeapon->AddOption(Iter_Pos->second->weapon_name_);
	}
	
	pAddPropWeapon->AllowEdit(true);
	pAddPropWeapon->SetData(DATA_TYPE::WEAPON_NAME);
	pAddGroupWeapon->AddSubItem(pAddPropWeapon);
	m_wndPropList->AddProperty(pAddGroupWeapon);

	//@ Property set
	//@ Bullet
	pAddGroupBullet = new CMFCPropertyGridProperty(_T("Bullet"));
	CMFCPropertyGridProperty* pAddPropBullet_name = new CMFCPropertyGridProperty(_T("Bullet Name"), _T(""),
		_T("Enter Bullet Name"));
	CMFCPropertyGridProperty* pAddPropBullet_size = new CMFCPropertyGridProperty(_T("Bullet Size"), _T(""),
		_T("Enter Bullet Size"));

	for(map<CString, RBX_Bullet*>::iterator Iter_Pos = BULLET_LIST().begin(); 
			Iter_Pos != BULLET_LIST().end(); ++Iter_Pos) {
		pAddPropBullet_name->AddOption(Iter_Pos->second->bullet_name_);
		CString bullet_size;
		bullet_size.Format(_T("%d"), Iter_Pos->second->bullet_size_);
		pAddPropBullet_size->AddOption(bullet_size);
	}
	pAddPropBullet_name->AllowEdit(true);
	pAddPropBullet_name->SetData(DATA_TYPE::BULLET_NAME);
	pAddGroupBullet->AddSubItem(pAddPropBullet_name);

	pAddPropBullet_size->AllowEdit(true);
	pAddPropBullet_size->SetData(DATA_TYPE::BULLET_SIZE);
	pAddGroupBullet->AddSubItem(pAddPropBullet_size);
	
	m_wndPropList->AddProperty(pAddGroupBullet);//

	//@ Particle
	pAddGroupParticle = new CMFCPropertyGridProperty(_T("Particle"));
	CMFCPropertyGridProperty* pAddPropParticle_name = new CMFCPropertyGridProperty(_T("Particle Name"), _T(""),
		_T("Enter Particle Name"));
	CMFCPropertyGridProperty* pAddPropParticle_path = new CMFCPropertyGridProperty(_T("Particle Path"), _T(""),
		_T("Enter Particle Path"));

	for(map<CString, RBX_Particle*>::iterator Iter_Pos = PARTICLE_LIST().begin(); 
			Iter_Pos != PARTICLE_LIST().end(); ++Iter_Pos) {
		pAddPropParticle_name->AddOption(Iter_Pos->second->particle_name_);
		pAddPropParticle_path->AddOption(Iter_Pos->second->particle_path_);
	}
	pAddPropParticle_name->AllowEdit(true);
	pAddPropParticle_name->SetData(DATA_TYPE::PARTICLE_NAME);
	pAddGroupParticle->AddSubItem(pAddPropParticle_name);

	pAddPropParticle_path->AllowEdit(true);
	pAddPropParticle_path->SetData(DATA_TYPE::PARTICLE_PATH);
	pAddGroupParticle->AddSubItem(pAddPropParticle_path);
	
	m_wndPropList->AddProperty(pAddGroupParticle);//

	//@ Sound
	pAddGroupSound = new CMFCPropertyGridProperty(_T("Sound"));
	CMFCPropertyGridProperty* pAddPropSound_name = new CMFCPropertyGridProperty(_T("Sound Name"), _T(""),
		_T("Enter Sound Name"));
	CMFCPropertyGridProperty* pAddPropSound_path = new CMFCPropertyGridProperty(_T("Sound Path"), _T(""),
		_T("Enter Sound Path"));

	for(map<CString, RBX_Sound*>::iterator Iter_Pos = SOUND_LIST().begin(); 
			Iter_Pos != SOUND_LIST().end(); ++Iter_Pos) {
		pAddPropSound_name->AddOption(Iter_Pos->second->sound_name_);
		pAddPropSound_path->AddOption(Iter_Pos->second->sound_path_);
	}
	pAddPropSound_name->AllowEdit(true);
	pAddPropSound_name->SetData(DATA_TYPE::SOUND_NAME);
	pAddGroupSound->AddSubItem(pAddPropSound_name);

	pAddPropSound_path->AllowEdit(true);
	pAddPropSound_path->SetData(DATA_TYPE::SOUND_PATH);
	pAddGroupSound->AddSubItem(pAddPropSound_path);
	
	m_wndPropList->AddProperty(pAddGroupSound);//

	//@ Model
	pAddGroupModel = new CMFCPropertyGridProperty(_T("Model"));
	CMFCPropertyGridProperty* pAddPropModel_name = new CMFCPropertyGridProperty(_T("Model Name"), _T(""),
		_T("Enter Model Name"));
	CMFCPropertyGridProperty* pAddPropModel_2dPath = new CMFCPropertyGridProperty(_T("Model 2D File Path"), _T(""),
		_T("Enter Model 2D File Path"));
	CMFCPropertyGridProperty* pAddPropModel_3dPath = new CMFCPropertyGridProperty(_T("Model 3D File Path"), _T(""),
		_T("Enter Model 3D File Path"));

	for(map<CString, RBX_Model*>::iterator Iter_Pos = MODEL_LIST().begin(); 
			Iter_Pos != MODEL_LIST().end(); ++Iter_Pos) {
		pAddPropModel_name->AddOption(Iter_Pos->second->model_name_);
		pAddPropModel_2dPath->AddOption(Iter_Pos->second->model_path_2d_);
		pAddPropModel_3dPath->AddOption(Iter_Pos->second->model_path_3d_);
	}
	pAddPropModel_name->AllowEdit(true);
	pAddPropModel_name->SetData(DATA_TYPE::MODEL_NAME);
	pAddGroupModel->AddSubItem(pAddPropModel_name);

	pAddPropModel_2dPath->AllowEdit(true);
	pAddPropModel_2dPath->SetData(DATA_TYPE::MODEL_2D_PATH);
	pAddGroupModel->AddSubItem(pAddPropModel_2dPath);

	pAddPropModel_3dPath->AllowEdit(true);
	pAddPropModel_3dPath->SetData(DATA_TYPE::MODEL_3D_PATH);
	pAddGroupModel->AddSubItem(pAddPropModel_3dPath);
	
	m_wndPropList->AddProperty(pAddGroupModel);//
}


BEGIN_MESSAGE_MAP(CDialogBar_Panel, CDialogBar)
	ON_REGISTERED_MESSAGE(AFX_WM_PROPERTY_CHANGED, OnPropertyChanged)
	ON_BN_CLICKED(IDC_SAVE, &CDialogBar_Panel::OnBnClickedSave)
	ON_BN_CLICKED(IDC_DELETE, &CDialogBar_Panel::OnBnClickedDelete)
	ON_UPDATE_COMMAND_UI(IDC_SAVE, CDialogBar_Panel::OnUpdateCmdUI)
	ON_UPDATE_COMMAND_UI(IDC_DELETE, CDialogBar_Panel::OnUpdateCmdUI) // 이부분 직접코딩(버튼 Enable을 위하여)
END_MESSAGE_MAP()

// 다이얼로그바 버튼 활성화 위해 추가
void CDialogBar_Panel::OnUpdateCmdUI(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(TRUE);
}

//무기 그룹 Display Name Option추가(혹은 Reinit)
void CDialogBar_Panel::InitWeaponDisplayNameOption()
{
	/*pAddGroupWeapon_DisplayName->RemoveAllOptions();
	for( int i = 0 ; i < m_pModelManager->m_pModelWeaponList.GetLength() ; i++)
	{
		VArray<CRBX_Model*> modellist = m_pModelManager->m_pModelWeaponList;
		CRBX_ModelWeapon* model = (CRBX_ModelWeapon*)(modellist.GetAt(i));
		if(pAddGroupWeapon_DisplayName != NULL) pAddGroupWeapon_DisplayName->AddOption(model->DisplayName);
	}*/
}

LRESULT CDialogBar_Panel::OnPropertyChanged (WPARAM,LPARAM lParam)
{
	CMFCPropertyGridProperty* pProp = (CMFCPropertyGridProperty*) lParam;
	CString bullet_size;
	map<CString, RBX_Weapon*>::iterator Iter_Weapon;
	map<CString, RBX_Bullet*>::iterator Iter_Bullet;
	map<CString, RBX_Particle*>::iterator Iter_Particle;
	map<CString, RBX_Sound*>::iterator Iter_Sound;
	map<CString, RBX_Model*>::iterator Iter_Model;
	RBX_Weapon* weapon;
	RBX_Bullet* bullet;
	RBX_Particle* particle;
	RBX_Sound* sound;
	RBX_Model* model;

	switch ((DATA_TYPE) pProp->GetData()) {
		case WEAPON_NAME:
			
			Iter_Weapon = WEAPON_LIST().find(pProp->GetValue());
			if(Iter_Weapon == WEAPON_LIST().end())
				return FALSE;

			//@ set bullet
			weapon = Iter_Weapon->second;
			pAddGroupBullet->GetSubItem(0)->SetValue(weapon->bullet_->bullet_name_);
			
			bullet_size.Format(_T("%d"), weapon->bullet_->bullet_size_);
			pAddGroupBullet->GetSubItem(1)->SetValue(bullet_size);//

			//@ set particle
			pAddGroupParticle->GetSubItem(0)->SetValue(weapon->particle_->particle_name_);
			pAddGroupParticle->GetSubItem(1)->SetValue(weapon->particle_->particle_path_);//

			//@ set sound
			pAddGroupSound->GetSubItem(0)->SetValue(weapon->sound_->sound_name_);
			pAddGroupSound->GetSubItem(1)->SetValue(weapon->sound_->sound_path_);//

			//@ set model
			pAddGroupModel->GetSubItem(0)->SetValue(weapon->model_->model_name_);
			pAddGroupModel->GetSubItem(1)->SetValue(weapon->model_->model_path_2d_);
			pAddGroupModel->GetSubItem(2)->SetValue(weapon->model_->model_path_3d_);//
			
			childview_->SetModel2Dimage(weapon->model_->model_path_2d_);
			break;

		case BULLET_NAME:
			//@ set bullet size by bullet name
			Iter_Bullet = BULLET_LIST().find(pProp->GetValue());
			if(Iter_Bullet == BULLET_LIST().end())
				return FALSE;

			bullet = Iter_Bullet->second;
			bullet_size.Format(_T("%d"), bullet->bullet_size_);
			pAddGroupBullet->GetSubItem(1)->SetValue(bullet_size);//
			break;

		case PARTICLE_NAME:
			//@ set particle path by particle name
			Iter_Particle = PARTICLE_LIST().find(pProp->GetValue());
			if(Iter_Particle == PARTICLE_LIST().end())
				return FALSE;

			particle = Iter_Particle->second;
			pAddGroupParticle->GetSubItem(1)->SetValue(particle->particle_path_);//
			break;

		case SOUND_NAME:
			//@ set sound path by sound name
			Iter_Sound = SOUND_LIST().find(pProp->GetValue());
			if(Iter_Sound == SOUND_LIST().end())
				return FALSE;

			sound = Iter_Sound->second;
			pAddGroupSound->GetSubItem(1)->SetValue(sound->sound_path_);//
			break;

		case MODEL_NAME:
			//@ set sound path by sound name
			Iter_Model = MODEL_LIST().find(pProp->GetValue());
			if(Iter_Model == MODEL_LIST().end())
				return FALSE;

			model = Iter_Model->second;
			pAddGroupModel->GetSubItem(1)->SetValue(model->model_path_2d_);
			pAddGroupModel->GetSubItem(2)->SetValue(model->model_path_3d_);//
			break;
	}

	return 0;
}

void CDialogBar_Panel::OnBnClickedSave()
{
	//@ set particle
	if((CString)(pAddGroupBullet->GetSubItem(0)->GetValue()) == "" ||
		(CString)(pAddGroupBullet->GetSubItem(1)->GetValue()) == "" ||
		(CString)(pAddGroupParticle->GetSubItem(0)->GetValue()) == "" ||
		(CString)(pAddGroupParticle->GetSubItem(1)->GetValue()) == "" ||
		(CString)(pAddGroupSound->GetSubItem(0)->GetValue()) == "" ||
		(CString)(pAddGroupSound->GetSubItem(1)->GetValue()) == "" ||
		(CString)(pAddGroupModel->GetSubItem(0)->GetValue()) == "" ||
		(CString)(pAddGroupModel->GetSubItem(1)->GetValue()) == "" ||
		(CString)(pAddGroupModel->GetSubItem(2)->GetValue()) == "") {
			AfxMessageBox(_T("Please enter data ALL property"));
			return;
	}

	map<CString, RBX_Weapon*>::iterator Iter_Pos = WEAPON_LIST().find(
		pAddPropWeapon->GetValue());

	//@ insert data
	if(Iter_Pos == WEAPON_LIST().end()) {
		RBX_Weapon* weapon = new RBX_Weapon;

		weapon->weapon_name_ = (CString)(pAddPropWeapon->GetValue());

		weapon->bullet_->bullet_name_ = (CString)(pAddGroupBullet->GetSubItem(0)->GetValue());
		weapon->bullet_name_ = (CString)(pAddGroupBullet->GetSubItem(0)->GetValue());
		CString bullet_size = (CString)(pAddGroupBullet->GetSubItem(1)->GetValue());
		USES_CONVERSION;
		char* bullet_size_str = T2A(bullet_size);
		weapon->bullet_->bullet_size_ = atoi(bullet_size_str);
		
		weapon->particle_name_ = (CString)(pAddGroupParticle->GetSubItem(0)->GetValue()); 
		weapon->particle_->particle_name_ = (CString)(pAddGroupParticle->GetSubItem(0)->GetValue());
		weapon->particle_->particle_path_ = (CString)(pAddGroupParticle->GetSubItem(1)->GetValue());
		
		weapon->sound_name_ = (CString)(pAddGroupSound->GetSubItem(0)->GetValue());
		weapon->sound_->sound_name_ = (CString)(pAddGroupSound->GetSubItem(0)->GetValue());
		weapon->sound_->sound_path_ = (CString)(pAddGroupSound->GetSubItem(1)->GetValue());
		
		weapon->model_name_ = (CString)(pAddGroupModel->GetSubItem(0)->GetValue());
		weapon->model_->model_name_ = (CString)(pAddGroupModel->GetSubItem(0)->GetValue());
		weapon->model_->model_path_2d_ = (CString)(pAddGroupModel->GetSubItem(1)->GetValue());
		weapon->model_->model_path_3d_ = (CString)(pAddGroupModel->GetSubItem(2)->GetValue());

		bool result = m_DataManager->InsertData(weapon);
		if(result) {
			m_DataManager->LoadDataFromMySQL();
			ReInit();
		}
	}
	//@ update data
	else {
		RBX_Weapon* weapon = new RBX_Weapon;
		weapon = Iter_Pos->second;

		weapon->weapon_name_ = (CString)(pAddPropWeapon->GetValue());

		weapon->bullet_->bullet_name_ = (CString)(pAddGroupBullet->GetSubItem(0)->GetValue());
		weapon->bullet_name_ = (CString)(pAddGroupBullet->GetSubItem(0)->GetValue());
		CString bullet_size = (CString)(pAddGroupBullet->GetSubItem(1)->GetValue());
		USES_CONVERSION;
		char* bullet_size_str = T2A(bullet_size);
		weapon->bullet_->bullet_size_ = atoi(bullet_size_str);
		
		weapon->particle_name_ = (CString)(pAddGroupParticle->GetSubItem(0)->GetValue()); 
		weapon->particle_->particle_name_ = (CString)(pAddGroupParticle->GetSubItem(0)->GetValue());
		weapon->particle_->particle_path_ = (CString)(pAddGroupParticle->GetSubItem(1)->GetValue());
		
		weapon->sound_name_ = (CString)(pAddGroupSound->GetSubItem(0)->GetValue());
		weapon->sound_->sound_name_ = (CString)(pAddGroupSound->GetSubItem(0)->GetValue());
		weapon->sound_->sound_path_ = (CString)(pAddGroupSound->GetSubItem(1)->GetValue());
		
		weapon->model_name_ = (CString)(pAddGroupModel->GetSubItem(0)->GetValue());
		weapon->model_->model_name_ = (CString)(pAddGroupModel->GetSubItem(0)->GetValue());
		weapon->model_->model_path_2d_ = (CString)(pAddGroupModel->GetSubItem(1)->GetValue());
		weapon->model_->model_path_3d_ = (CString)(pAddGroupModel->GetSubItem(2)->GetValue());

		bool result = m_DataManager->UpdateData(weapon);
		if(result) {
			m_DataManager->LoadDataFromMySQL();
			ReInit();
		}
	}
}


void CDialogBar_Panel::OnBnClickedDelete()
{
	if((CString)(pAddPropWeapon->GetValue()) == "" ||
		(CString)(pAddGroupBullet->GetSubItem(0)->GetValue()) == "" ||
		(CString)(pAddGroupBullet->GetSubItem(1)->GetValue()) == "" ||
		(CString)(pAddGroupParticle->GetSubItem(0)->GetValue()) == "" ||
		(CString)(pAddGroupParticle->GetSubItem(1)->GetValue()) == "" ||
		(CString)(pAddGroupSound->GetSubItem(0)->GetValue()) == "" ||
		(CString)(pAddGroupSound->GetSubItem(1)->GetValue()) == "" ||
		(CString)(pAddGroupModel->GetSubItem(0)->GetValue()) == "" ||
		(CString)(pAddGroupModel->GetSubItem(1)->GetValue()) == "" ||
		(CString)(pAddGroupModel->GetSubItem(2)->GetValue()) == "") {
			AfxMessageBox(_T("Please enter data ALL property"));
			return;
	}

	map<CString, RBX_Weapon*>::iterator Iter_Pos = WEAPON_LIST().find(
		pAddPropWeapon->GetValue());

	if(Iter_Pos == WEAPON_LIST().end()) {
		AfxMessageBox(_T("Can't delete"));
		return;
	}

	//@ delete data
	else {
		RBX_Weapon* weapon = new RBX_Weapon;
		weapon = Iter_Pos->second;

		weapon->weapon_name_ = (CString)(pAddPropWeapon->GetValue());

		weapon->bullet_->bullet_name_ = (CString)(pAddGroupBullet->GetSubItem(0)->GetValue());
		weapon->bullet_name_ = (CString)(pAddGroupBullet->GetSubItem(0)->GetValue());
		CString bullet_size = (CString)(pAddGroupBullet->GetSubItem(1)->GetValue());
		USES_CONVERSION;
		char* bullet_size_str = T2A(bullet_size);
		weapon->bullet_->bullet_size_ = atoi(bullet_size_str);
		
		weapon->particle_name_ = (CString)(pAddGroupParticle->GetSubItem(0)->GetValue()); 
		weapon->particle_->particle_name_ = (CString)(pAddGroupParticle->GetSubItem(0)->GetValue());
		weapon->particle_->particle_path_ = (CString)(pAddGroupParticle->GetSubItem(1)->GetValue());
		
		weapon->sound_name_ = (CString)(pAddGroupSound->GetSubItem(0)->GetValue());
		weapon->sound_->sound_name_ = (CString)(pAddGroupSound->GetSubItem(0)->GetValue());
		weapon->sound_->sound_path_ = (CString)(pAddGroupSound->GetSubItem(1)->GetValue());
		
		weapon->model_name_ = (CString)(pAddGroupModel->GetSubItem(0)->GetValue());
		weapon->model_->model_name_ = (CString)(pAddGroupModel->GetSubItem(0)->GetValue());
		weapon->model_->model_path_2d_ = (CString)(pAddGroupModel->GetSubItem(1)->GetValue());
		weapon->model_->model_path_3d_ = (CString)(pAddGroupModel->GetSubItem(2)->GetValue());

		bool result = m_DataManager->DeleteData(weapon);
		if(result) {
			m_DataManager->LoadDataFromMySQL();
			ReInit();
		}
	}
}
