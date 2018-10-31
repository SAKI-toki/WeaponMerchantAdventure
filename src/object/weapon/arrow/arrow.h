/**
* @file arrow.h
* @brief 遠距離武器クラスの宣言
* @author 石山　悠
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
* @brief 遠距離武器クラス
*/
class Arrow :public WeaponBase
{
	//次の攻撃をするまでのディレイ
	static constexpr int delay = /*3*/0;
	int current_delay = 0;
	//矢印
	Sprite sprite;
	//弾
	std::list<Bullet> bullet;
	//音
	std::vector<Sound> sound;
	//スティックの角度
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