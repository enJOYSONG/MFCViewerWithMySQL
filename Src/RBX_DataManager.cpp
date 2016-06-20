#include <WinSock2.h>
#include "RBX_DataManager.h"
#include "RBX_Data.h"

RBX_DataManager::RBX_DataManager() {
	mysql_init(&DB_Conn);

	pDB_Connection = mysql_real_connect(&DB_Conn,
		"127.0.0.1", "root", "", "test", 3306, 
		(char*)NULL, 0);
};

RBX_DataManager::~RBX_DataManager() {
	for(map<CString, RBX_Weapon*>::iterator Iter_Pos = weapon_list_.begin(); Iter_Pos != weapon_list_.end(); ++Iter_Pos) {
		delete Iter_Pos->second;
	}

	for(map<CString, RBX_Bullet*>::iterator Iter_Pos = bullet_list_.begin(); Iter_Pos != bullet_list_.end(); ++Iter_Pos) {
		delete Iter_Pos->second;
	}

	for(map<CString, RBX_Particle*>::iterator Iter_Pos = particle_list_.begin(); Iter_Pos != particle_list_.end(); ++Iter_Pos) {
		delete Iter_Pos->second;
	}

	for(map<CString, RBX_Sound*>::iterator Iter_Pos = sound_list_.begin(); Iter_Pos != sound_list_.end(); ++Iter_Pos) {
		delete Iter_Pos->second;
	}

	for(map<CString, RBX_Model*>::iterator Iter_Pos = model_list_.begin(); Iter_Pos != model_list_.end(); ++Iter_Pos) {
		delete Iter_Pos->second;
	}

	mysql_close(pDB_Connection);
};

void RBX_DataManager::LoadDataFromMySQL() {
	for(map<CString, RBX_Weapon*>::iterator Iter_Pos = weapon_list_.begin(); Iter_Pos != weapon_list_.end(); ++Iter_Pos) {
		delete Iter_Pos->second;
	}

	for(map<CString, RBX_Bullet*>::iterator Iter_Pos = bullet_list_.begin(); Iter_Pos != bullet_list_.end(); ++Iter_Pos) {
		delete Iter_Pos->second;
	}

	for(map<CString, RBX_Particle*>::iterator Iter_Pos = particle_list_.begin(); Iter_Pos != particle_list_.end(); ++Iter_Pos) {
		delete Iter_Pos->second;
	}

	for(map<CString, RBX_Sound*>::iterator Iter_Pos = sound_list_.begin(); Iter_Pos != sound_list_.end(); ++Iter_Pos) {
		delete Iter_Pos->second;
	}

	for(map<CString, RBX_Model*>::iterator Iter_Pos = model_list_.begin(); Iter_Pos != model_list_.end(); ++Iter_Pos) {
		delete Iter_Pos->second;
	}

	MYSQL_RES* pSQL_Result;
	MYSQL_ROW SQL_ROW;

	int iSQL_Stat;
	char strSQL[512];

	//@ load bullet
	strcpy(strSQL, "select * from bullet");

	iSQL_Stat = mysql_query(pDB_Connection, strSQL);

	if(!iSQL_Stat) {
		pSQL_Result = mysql_store_result(pDB_Connection);
		int index = 0;
		while((SQL_ROW = mysql_fetch_row(pSQL_Result)) != NULL) {
			RBX_Bullet* bullet = new RBX_Bullet(SQL_ROW[0], atoi(SQL_ROW[1]));
			bullet_list_[SQL_ROW[0]] = bullet;
		}
	}//

	//@ load particle
	strcpy(strSQL, "select * from particle");

	iSQL_Stat = mysql_query(pDB_Connection, strSQL);

	if(!iSQL_Stat) {
		pSQL_Result = mysql_store_result(pDB_Connection);
		int index = 0;
		while((SQL_ROW = mysql_fetch_row(pSQL_Result)) != NULL) {
			RBX_Particle* particle = new RBX_Particle(SQL_ROW[0], SQL_ROW[1]);
			particle_list_[SQL_ROW[0]] = particle;
		}
	}//

	//@ load sound
	strcpy(strSQL, "select * from sound");

	iSQL_Stat = mysql_query(pDB_Connection, strSQL);

	if(!iSQL_Stat) {
		pSQL_Result = mysql_store_result(pDB_Connection);
		int index = 0;
		while((SQL_ROW = mysql_fetch_row(pSQL_Result)) != NULL) {
			RBX_Sound* sound = new RBX_Sound(SQL_ROW[0], SQL_ROW[1]);
			sound_list_[SQL_ROW[0]] = sound;
		}
	}//

	//@ load model
	strcpy(strSQL, "select * from model");

	iSQL_Stat = mysql_query(pDB_Connection, strSQL);

	if(!iSQL_Stat) {
		pSQL_Result = mysql_store_result(pDB_Connection);
		int index = 0;
		while((SQL_ROW = mysql_fetch_row(pSQL_Result)) != NULL) {
			RBX_Model* model = new RBX_Model(SQL_ROW[0], SQL_ROW[1], SQL_ROW[2]);
			model_list_[SQL_ROW[0]] = model;
		}
	}//

	//@ load weapon
	strcpy(strSQL, "select * from weapon");

	iSQL_Stat = mysql_query(pDB_Connection, strSQL);

	if(!iSQL_Stat) {
		pSQL_Result = mysql_store_result(pDB_Connection);
		while((SQL_ROW = mysql_fetch_row(pSQL_Result)) != NULL) {
			RBX_Weapon* weapon = new RBX_Weapon(SQL_ROW[0], SQL_ROW[1],
				SQL_ROW[2], SQL_ROW[3], SQL_ROW[4]);
			
			//@ search bullet by bullet_name_ and insert weapon object
			for(map<CString, RBX_Bullet*>::iterator Iter_Pos = bullet_list_.begin(); 
			Iter_Pos != bullet_list_.end(); ++Iter_Pos) {
				RBX_Bullet* bullet = Iter_Pos->second;
				USES_CONVERSION;
				if(!strcmp(T2A(weapon->bullet_name_), 
					T2A(bullet->bullet_name_))) {
					weapon->bullet_ = bullet;
				}
			}

			//@ search particle by particle_name_ and insert weapon object
			for(map<CString, RBX_Particle*>::iterator Iter_Pos = particle_list_.begin(); 
			Iter_Pos != particle_list_.end(); ++Iter_Pos) {
				RBX_Particle* particle = Iter_Pos->second;
				USES_CONVERSION;
				if(!strcmp(T2A(weapon->particle_name_), 
					T2A(particle->particle_name_))) {
						weapon->particle_ = particle;
				}
			}

			//@ search sound by sound_name_ and insert weapon object
			for(map<CString, RBX_Sound*>::iterator Iter_Pos = sound_list_.begin(); 
			Iter_Pos != sound_list_.end(); ++Iter_Pos) {
				RBX_Sound* sound = Iter_Pos->second;
				USES_CONVERSION;
				if(!strcmp(T2A(weapon->sound_name_), 
					T2A(sound->sound_name_))) {
						weapon->sound_ = sound;
				}
			}

			//@ search model by model_name_ and insert weapon object
			for(map<CString, RBX_Model*>::iterator Iter_Pos = model_list_.begin(); 
			Iter_Pos != model_list_.end(); ++Iter_Pos) {
				RBX_Model* model = Iter_Pos->second;
				USES_CONVERSION;
				if(!strcmp(T2A(weapon->model_name_), 
					T2A(model->model_name_))) {
						weapon->model_ = model;
				}
			}

			weapon_list_[SQL_ROW[0]] = weapon;
		}
	}//
};

bool RBX_DataManager::InsertData(RBX_Weapon* weapon) {
	MYSQL_RES* pSQL_Result;

	int iSQL_Stat;
	char strSQL[512];

	if(bullet_list_.find(weapon->bullet_->bullet_name_) 
		== bullet_list_.end()) {
		//@ insert bullet data
		strcpy(strSQL, "insert into bullet(bulletname, size) values('");
		CString bullet_name = weapon->bullet_->bullet_name_;
		CString bullet_size;
		bullet_size.Format(_T("%d"),weapon->bullet_->bullet_size_);

		USES_CONVERSION;
		char* bullet_name_str = T2A(bullet_name);
		char* bullet_size_str = T2A(bullet_size);

		strcat(strSQL, bullet_name_str);
		strcat(strSQL, "',");
		
		
		strcat(strSQL, bullet_size_str);
		strcat(strSQL, ")");
	}

	iSQL_Stat = mysql_query(pDB_Connection, strSQL);

	strSQL[0] = '\0';
	if(particle_list_.find(weapon->particle_->particle_name_) 
		== particle_list_.end()) {
		//@ insert particle data
		strcpy(strSQL, "insert into particle(particlename, particlepath) values('");
		CString particle_name = weapon->particle_->particle_name_;
		CString particle_path = weapon->particle_->particle_path_;
		
		USES_CONVERSION;
		char* particle_name_str = T2A(particle_name);
		char* particle_path_str = T2A(particle_path);

		strcat(strSQL, particle_name_str);
		strcat(strSQL, "','");
		
		strcat(strSQL, particle_path_str);
		strcat(strSQL, "')");
	}

	iSQL_Stat = mysql_query(pDB_Connection, strSQL);
	
	strSQL[0] = '\0';
	if(sound_list_.find(weapon->sound_->sound_name_) 
		== sound_list_.end()) {
		//@ insert sound data
		strcpy(strSQL, "insert into sound(soundname, soundpath) values('");
		CString sound_name = weapon->sound_->sound_name_;
		CString sound_path = weapon->sound_->sound_path_;
		
		USES_CONVERSION;
		char* sound_name_str = T2A(sound_name);
		char* sound_path_str = T2A(sound_path);

		strcat(strSQL, sound_name_str);
		strcat(strSQL, "','");
		
		strcat(strSQL, sound_path_str);
		strcat(strSQL, "')");
	}

	iSQL_Stat = mysql_query(pDB_Connection, strSQL);

	strSQL[0] = '\0';
	if(model_list_.find(weapon->model_->model_name_) 
		== model_list_.end()) {
		//@ insert model data
		strcpy(strSQL, "insert into model(modelname, 2Dimagepath, 3Dmodelpath) values('");
		CString model_name = weapon->model_->model_name_;
		CString model_2dpath = weapon->model_->model_path_2d_;
		CString model_3dpath = weapon->model_->model_path_3d_;
		
		USES_CONVERSION;
		char* model_name_str = T2A(model_name);
		char* model_2dpath_str = T2A(model_2dpath);
		char* model_3dpath_str = T2A(model_3dpath);

		strcat(strSQL, model_name_str);
		strcat(strSQL, "','");
		
		strcat(strSQL, model_2dpath_str);
		strcat(strSQL, "','");

		strcat(strSQL, model_3dpath_str);
		strcat(strSQL, "')");
	}

	iSQL_Stat = mysql_query(pDB_Connection, strSQL);

	strSQL[0] = '\0';
	//@ insert new weapon data
	strcpy(strSQL, "insert into weapon(weaponname, particlename, soundname, bulletname, modelname) values('");
	CString weaponname = weapon->weapon_name_;
	CString particlename = weapon->particle_name_;
	CString soundname = weapon->sound_name_;
	CString bulletname = weapon->bullet_name_;
	CString modelname = weapon->model_name_;
		
	USES_CONVERSION;
	char* weaponname_str = T2A(weapon->weapon_name_);
	char* particlename_str = T2A(weapon->particle_name_);
	char* soundname_str = T2A(weapon->sound_name_);
	char* bulletname_str = T2A(weapon->bullet_name_);
	char* modelname_str = T2A(weapon->model_name_);

	strcat(strSQL, weaponname_str);
	strcat(strSQL, "','");
		
	strcat(strSQL, particlename_str);
	strcat(strSQL, "','");

	strcat(strSQL, soundname_str);
	strcat(strSQL, "','");

	strcat(strSQL, bulletname_str);
	strcat(strSQL, "','");

	strcat(strSQL, modelname_str);
	strcat(strSQL, "')");

	iSQL_Stat = mysql_query(pDB_Connection, strSQL);

	return !iSQL_Stat;
};

bool RBX_DataManager::UpdateData(RBX_Weapon* weapon) {
	
	MYSQL_RES* pSQL_Result;

	int iSQL_Stat;
	char strSQL[512];

	if(bullet_list_.find(weapon->bullet_->bullet_name_) 
		== bullet_list_.end()) {
		//@ insert bullet data
		strcpy(strSQL, "insert into bullet(bulletname, size) values('");
		CString bullet_name = weapon->bullet_->bullet_name_;
		CString bullet_size;
		bullet_size.Format(_T("%d"),weapon->bullet_->bullet_size_);

		USES_CONVERSION;
		char* bullet_name_str = T2A(bullet_name);
		char* bullet_size_str = T2A(bullet_size);

		strcat(strSQL, bullet_name_str);
		strcat(strSQL, "',");
		
		
		strcat(strSQL, bullet_size_str);
		strcat(strSQL, ")");
		
		iSQL_Stat = mysql_query(pDB_Connection, strSQL);
	}

	else {
		//@ update bullet data
		strcpy(strSQL, "update bullet set size = ");
		CString bullet_name = weapon->bullet_->bullet_name_;
		CString bullet_size;
		bullet_size.Format(_T("%d"),weapon->bullet_->bullet_size_);

		USES_CONVERSION;
		char* bullet_name_str = T2A(bullet_name);
		char* bullet_size_str = T2A(bullet_size);

		strcat(strSQL, bullet_size_str);
		strcat(strSQL, " where bulletname = '");

		strcat(strSQL, bullet_name_str);

		strcat(strSQL, "'");
		
		iSQL_Stat = mysql_query(pDB_Connection, strSQL);
	}

	strSQL[0] = '\0';
	if(particle_list_.find(weapon->particle_->particle_name_) 
		== particle_list_.end()) {
		//@ insert particle data
		strcpy(strSQL, "insert into particle(particlename, particlepath) values('");
		CString particle_name = weapon->particle_->particle_name_;
		CString particle_path = weapon->particle_->particle_path_;
		
		USES_CONVERSION;
		char* particle_name_str = T2A(particle_name);
		char* particle_path_str = T2A(particle_path);

		strcat(strSQL, particle_name_str);
		strcat(strSQL, "','");
		
		strcat(strSQL, particle_path_str);
		strcat(strSQL, "')");

		iSQL_Stat = mysql_query(pDB_Connection, strSQL);
	}

	else {
		//@ update particle data
		strcpy(strSQL, "update particle set particlepath = '");
		CString particle_name = weapon->particle_->particle_name_;
		CString particle_path = weapon->particle_->particle_path_;
		
		USES_CONVERSION;
		char* particle_name_str = T2A(particle_name);
		char* particle_path_str = T2A(particle_path);

		strcat(strSQL, particle_path_str);
		strcat(strSQL, "' where particlename = '");
		
		strcat(strSQL, particle_name_str);
		strcat(strSQL, "'");

		iSQL_Stat = mysql_query(pDB_Connection, strSQL);
	}
	
	strSQL[0] = '\0';
	if(sound_list_.find(weapon->sound_->sound_name_) 
		== sound_list_.end()) {
		//@ insert sound data
		strcpy(strSQL, "insert into sound(soundname, soundpath) values('");
		CString sound_name = weapon->sound_->sound_name_;
		CString sound_path = weapon->sound_->sound_path_;
		
		USES_CONVERSION;
		char* sound_name_str = T2A(sound_name);
		char* sound_path_str = T2A(sound_path);

		strcat(strSQL, sound_name_str);
		strcat(strSQL, "','");
		
		strcat(strSQL, sound_path_str);
		strcat(strSQL, "')");

		iSQL_Stat = mysql_query(pDB_Connection, strSQL);
	}

	else  {
		//@ update sound data
		strcpy(strSQL, "update sound set soundpath = '");
		CString sound_name = weapon->sound_->sound_name_;
		CString sound_path = weapon->sound_->sound_path_;
		
		USES_CONVERSION;
		char* sound_name_str = T2A(sound_name);
		char* sound_path_str = T2A(sound_path);

		strcat(strSQL, sound_path_str);
		strcat(strSQL, "' where soundname = '");
		
		strcat(strSQL, sound_name_str);
		strcat(strSQL, "'");

		iSQL_Stat = mysql_query(pDB_Connection, strSQL);
	}

	

	strSQL[0] = '\0';
	if(model_list_.find(weapon->model_->model_name_) 
		== model_list_.end()) {
		//@ insert model data
		strcpy(strSQL, "insert into model(modelname, 2Dimagepath, 3Dmodelpath) values('");
		CString model_name = weapon->model_->model_name_;
		CString model_2dpath = weapon->model_->model_path_2d_;
		CString model_3dpath = weapon->model_->model_path_3d_;
		
		USES_CONVERSION;
		char* model_name_str = T2A(model_name);
		char* model_2dpath_str = T2A(model_2dpath);
		char* model_3dpath_str = T2A(model_3dpath);

		strcat(strSQL, model_name_str);
		strcat(strSQL, "','");
		
		strcat(strSQL, model_2dpath_str);
		strcat(strSQL, "','");

		strcat(strSQL, model_3dpath_str);
		strcat(strSQL, "')");

		iSQL_Stat = mysql_query(pDB_Connection, strSQL);
	}

	else  {
		//@ update model data
		strcpy(strSQL, "update model set 2Dimagepath = '");
		CString model_name = weapon->model_->model_name_;
		CString model_2dpath = weapon->model_->model_path_2d_;
		CString model_3dpath = weapon->model_->model_path_3d_;
		
		USES_CONVERSION;
		char* model_name_str = T2A(model_name);
		char* model_2dpath_str = T2A(model_2dpath);
		char* model_3dpath_str = T2A(model_3dpath);

		strcat(strSQL, model_2dpath_str);
		strcat(strSQL, "', 3Dmodelpath = '");

		strcat(strSQL, model_3dpath_str);
		strcat(strSQL, "' where modelname = '");

		strcat(strSQL, model_name_str);
		strcat(strSQL, "'");

		iSQL_Stat = mysql_query(pDB_Connection, strSQL);
	}

	return !iSQL_Stat;
};

bool RBX_DataManager::DeleteData(RBX_Weapon* weapon){
	MYSQL_RES* pSQL_Result;

	int iSQL_Stat;
	char strSQL[512];

	strcpy(strSQL, "delete from weapon where weaponname = '");
	CString weapon_name = weapon->weapon_name_;
	USES_CONVERSION;
	char* weapon_name_str = T2A(weapon_name);

	strcat(strSQL, weapon_name_str);
	strcat(strSQL, "'");
		
	iSQL_Stat = mysql_query(pDB_Connection, strSQL);

	return !iSQL_Stat;
};