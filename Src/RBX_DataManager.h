#ifndef RBX_DATAMANAGER_H
#define RBX_DATAMANAGER_H

class RBX_Weapon;
class RBX_Bullet;
class RBX_Particle;
class RBX_Sound;
class RBX_Model;

#include <iostream>
#include <map>
#include <atlstr.h>

#include "mysql.h"

using namespace std;

#define CSTRING_TO_CHAR(n) LPSTR(LPCTSTR(n)) 

class RBX_DataManager
{
public:
	RBX_DataManager();
	~RBX_DataManager();

	void LoadDataFromMySQL();
	bool InsertData(RBX_Weapon* weapon);
	bool UpdateData(RBX_Weapon* weapon);
	bool DeleteData(RBX_Weapon* weapon);

//@ fuck you encapsulation
public:
	map<CString, RBX_Weapon*> weapon_list_;
	map<CString, RBX_Bullet*> bullet_list_;
	map<CString, RBX_Particle*> particle_list_;
	map<CString, RBX_Sound*> sound_list_;
	map<CString, RBX_Model*> model_list_;

private:
	MYSQL* pDB_Connection;
	MYSQL DB_Conn;
};

#endif