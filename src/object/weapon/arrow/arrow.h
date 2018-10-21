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
#include <list>

/**
* @brief 遠距離武器クラス
*/
class Arrow :public WeaponBase
{
	//矢印
	Sprite sprite;
	//弾
	std::list<Bullet> bullet;
	//スティックの角度
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