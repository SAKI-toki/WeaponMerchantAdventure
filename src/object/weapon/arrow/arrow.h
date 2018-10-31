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
#include "../../../sound/sound.h"
#include <list>
class Bullet;
/**
* @brief ����������N���X
*/
class Arrow :public WeaponBase
{
	//���̍U��������܂ł̃f�B���C
	static constexpr int delay = /*3*/0;
	int current_delay = 0;
	//���
	Sprite sprite;
	//�e
	std::list<Bullet> bullet;
	//��
	std::vector<Sound> sound;
	//�X�e�B�b�N�̊p�x
	float stick_angle = 0.0f;

public:
	void CollisionBullet();
	Arrow();
	void Attack(bool, const VEC2&);
	void WeaponStart();
	void WeaponUpdate(const VEC2&, bool = true);
	void WeaponRender(const Transform& = NULL);
	void WeaponDestroy();
};