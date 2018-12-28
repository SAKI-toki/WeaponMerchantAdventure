/**
* @file sword.h
* @brief 剣クラスの宣言
* @author 石山　悠
* @date 2018/10/15
*/
#pragma once
#include "../base/weapon_base.h"
#include "../../base/object_base.h"
#include "../../../collider/square/square_collider.h"
#include "../../../sprite/sprite.h"
#include "../../../sound/sound.h"

/**
* @brief 剣クラス
*/
class Sword :public WeaponBase, public ObjectBase
{
	bool first = true;
	bool hit = false;
	//次の攻撃をするまでのディレイ
	static constexpr int delay = 20;
	int current_delay = 0;
	//音
	Sound hit_sound;
	Sound nohit_sound;
	//プレイヤーからの距離
	static constexpr float distance = 80.0f;
	//コリジョン
	SquareCollider collider;
	Sprite sprite;
	//プレイヤーが右を向いているかどうか
	bool right = true;
protected:
	void RenderProcess(bool)final {}
	void InitProcess()final {}
	void UpdateProcess()final {}
public:
	//コンストラクタ
	Sword();
	/**
	* @brief コピーコンストラクタ
	*/
	Sword(const Sword& s) :collider(this, true)
	{
		this->transform = s.transform;
	}
	/**
	* @brief 代入演算子
	*/
	Sword& operator=(const Sword& other)
	{
		if (this != &other)
		{
			//this->is_attack = other.is_attack;
			this->collider = other.collider;
			ObjectBase::operator=(other);
		}
		return *this;
	}
	void WeaponStart()final;
	void WeaponUpdate(const Vec3&, bool)final;
	void WeaponDestroy()final;
	void Collision(ObjectBase*, Vec2)final;
	bool Attack(bool, const Vec3&)final;
	void WeaponRender(const Transform& = 
		Transform{ saki::vector3_zero<float>,saki::vector3_zero<float>,saki::vector3_zero<float> })final;
	void Destroy() {}
};
