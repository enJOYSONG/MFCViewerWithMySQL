#ifndef RBX_DATA_H
#define RBX_DATA_H
#include <atlstr.h>

enum DATA_TYPE {
	NONE,
	WEAPON_NAME,
	BULLET_NAME,
	BULLET_SIZE,
	PARTICLE_NAME,
	PARTICLE_PATH,
	SOUND_NAME,
	SOUND_PATH,
	MODEL_NAME,
	MODEL_2D_PATH,
	MODEL_3D_PATH,
};

class RBX_Bullet {
public:
	RBX_Bullet(){};
	RBX_Bullet(CString bullet_name, int bullet_size) { 
		bullet_name_ = bullet_name;
		bullet_size_ = bullet_size;
	};
	~RBX_Bullet(){};
	
public:
	CString bullet_name_;
	int bullet_size_;
};

class RBX_Particle{
public:
	RBX_Particle(){};
	RBX_Particle(CString particle_name, CString particle_path) {
		particle_name_ = particle_name;
		particle_path_ = particle_path;
	};
	~RBX_Particle(){};
	
public:
	CString particle_name_;
	CString particle_path_;
};

class RBX_Sound {
public:
	RBX_Sound(){};
	RBX_Sound(CString sound_name, CString sound_path) {
		sound_name_ = sound_name;
		sound_path_ = sound_path;
	};
	~RBX_Sound(){}

public:
	CString sound_name_;
	CString sound_path_;
};

class RBX_Model {
public:
	RBX_Model(){};
	RBX_Model(CString model_name, CString model_path_2d, CString model_path_3d) {
		model_name_ = model_name;
		model_path_2d_ = model_path_2d;
		model_path_3d_ = model_path_3d;
	};
	~RBX_Model(){};

public:
	CString model_name_;
	CString model_path_2d_;
	CString model_path_3d_;
};

class RBX_Weapon {
public:
	RBX_Weapon(){
		bullet_ = new RBX_Bullet;
		particle_ = new RBX_Particle;
		sound_ = new RBX_Sound;
		model_ = new RBX_Model;
	};
	RBX_Weapon(CString weapon_name, 
		CString particle_name,
		CString sound_name,
		CString bullet_name,
		CString model_name) {
			weapon_name_ = weapon_name;
			bullet_name_ = bullet_name;
			particle_name_ = particle_name;
			sound_name_ = sound_name;
			model_name_ = model_name;
	}; 
	RBX_Weapon(CString weapon_name, 
		RBX_Bullet* bullet,
		RBX_Particle* particle,
		RBX_Sound* sound,
		RBX_Model* model) {
			weapon_name_ = weapon_name;
			bullet_ = bullet;
			particle_ = particle;
			sound_ = sound;
			model_ = model;
	}; 
	~RBX_Weapon(){};

//@ fuck you encapsulation
public:
	CString weapon_name_;
	CString bullet_name_;
	CString particle_name_;
	CString sound_name_;
	CString model_name_;

	RBX_Bullet* bullet_;
	RBX_Particle* particle_;
	RBX_Sound* sound_;
	RBX_Model* model_;
};

#endif