/**
* @file arrow.h
* @brief ����������N���X�̐錾
* @author �ΎR�@�I
* @date 2018/10/18
*/
#pragma once
#include "../base/weapon_base.h"
#include "../../../rendering/sprite/sprite.h"
#include "bullet/bullet.h"
#include <list>

/**
* @brief ����������N���X
*/
class Arrow :public WeaponBase
{
	//���
	Sprite sprite;
	//�e
	std::list<Bullet> bullet;
	//�X�e�B�b�N�̊p�x
	float stick_angle = 0.0f;

	bool arrow_rendering = false;
public:
	Arrow();
	void Attack(bool, const VEC2&);
	void WeaponStart() {};
	void WeaponUpdate(const VEC2&, bool = true);
	void WeaponRender(const Transform& = NULL);
	void WeaponDestroy();
};