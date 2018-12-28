/**
* @file arrow.h
* @brief ����������N���X�̐錾
* @author �ΎR�@�I
* @date 2018/10/18
*/
#pragma once
#include "../base/weapon_base.h"
#include "../../../sprite/sprite.h"
#include "bullet/bullet.h"
#include "../../../sound/sound.h"
#include <list>
class Bullet;
/**
* @brief ����������N���X
*/
class Arrow :public WeaponBase
{
	bool bullet_flg = false;
	bool bullet_right = false;
	Vec3 bullet_pos;
	bool enabled = true;
	//���̍U��������܂ł̃f�B���C
	static constexpr int delay = 15;
	int current_delay = 0;
	//�e
	std::list<Bullet> bullet;
	//��
	std::vector<Sound> sound;

public:
	void CollisionBullet();
	bool Attack(bool, const Vec3&)final;
	void WeaponStart()final;
	void WeaponUpdate(const Vec3&, bool = true)final;
	void WeaponRender(const Transform& =
		Transform{ saki::vector3_zero<float>,saki::vector3_zero<float>,saki::vector3_zero<float> })final;
	void WeaponDestroy()final;
};