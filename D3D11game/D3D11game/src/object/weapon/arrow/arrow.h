/**
* @file arrow.h
* @brief 遠距離武器クラスの宣言
* @author 石山　悠
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
* @brief 遠距離武器クラス
*/
class Arrow :public WeaponBase
{
	bool bullet_flg = false;
	bool bullet_right = false;
	Vec3 bullet_pos;
	bool enabled = true;
	//次の攻撃をするまでのディレイ
	static constexpr int delay = 15;
	int current_delay = 0;
	//弾
	std::list<Bullet> bullet;
	//音
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