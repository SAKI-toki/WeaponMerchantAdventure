/**
* @file sword.cpp
* @brief 剣クラスのメンバ関数を定義
* @author 石山　悠
* @date 2018/10/18
*/
#include "sword.h"

/**
* @brief コンストラクタ
*/
Sword::Sword() :collider(this, true)
{
	object_tag = OBJECT_TAG::WEAPON;
	
	sprite.Init(std::string("sword"), L"sword.png", 100, 100, 0, 0, 0, 0.3f);
	sound.Init(std::string("sword_sound"), L"sword.wav", false, false);
	transform.size = VEC2(100, 100);
	transform.scale = 1;
}

/**
* @brief 武器用の初期化
*/
void Sword::WeaponStart()
{
	//collider.enabled = true;
	collider.enabled = false;
	current_delay = delay;
}

/**
* @brief 武器用の更新
* @param p 位置
* @param _right 右向きかどうか
*/
void Sword::WeaponUpdate(const VEC2& p, bool _right)
{
	if (current_delay < delay) { ++current_delay; }
	right = _right;
	//is_attack = false;

	collider.enabled = false;
	collider.SetStatus(VEC2(p.x + (_right ? 1 : -1)*distance, p.y), transform.size.x, transform.size.y, 0, transform.scale);
}

/**
* @brief 武器用の描画
* @param t 描画位置
*/
void Sword::WeaponRender(const Transform& t)
{
	sprite.Render(Transform(t.pos.x + (right ? distance : -distance), t.pos.y, 0, 1));
}

/**
* @brief 武器用の破棄
*/
void Sword::WeaponDestroy()
{
	collider.enabled = false;
}

/**
* @brief 当たったときの反応
* @param obj 当たった相手のオブジェクト
*/
void Sword::Collision(ObjectBase* obj, VEC2)
{
	if (obj == nullptr)return;
	/*if (!is_attack)
	{
		return;
	}*/
	if (obj->object_tag == OBJECT_TAG::ENEMY)
	{
		sound.Stop();
		sound.Start();
	}
}

/**
* @brief 攻撃
* @param _right 右向きかどうか
* @param pos 位置
*/
void Sword::Attack(bool _right, const VEC2& pos)
{
	if (current_delay < delay) { return; }
	current_delay = 0;
	auto p = pos;
	p.x += (_right ? 1 : -1)*distance;
	collider.SetStatus(p, transform.size.x, transform.size.y, 0, transform.scale);
	//is_attack = true;
	collider.enabled = true;
}