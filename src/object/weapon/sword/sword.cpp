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
	sprite.Init(std::string("sword"), L"sword.png", true, 100, 100, 0, 0, 0, 0.3f);
	transform.size = VEC2(100, 100);
	transform.scale = 1;
}
/**
* @brief 武器用の初期化
*/
void Sword::WeaponStart()
{
	collider.enabled = true;
}

/**
* @brief 武器用の更新
* @param _right 右向きかどうか
*/
void Sword::WeaponUpdate(const VEC2&, bool _right)
{
	right = _right;
	is_attack = false;
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
*/
void Sword::Collision(ObjectBase* obj, VEC2)
{
	if (!is_attack)
	{
		return;
	}
	if (obj->object_tag == OBJECT_TAG::ENEMY)
	{
		--obj->status.HP;
		obj->Destroy();
	}
}

/**
* @brief 攻撃
* @param _right 右向きかどうか
* @param pos 位置
*/
void Sword::Attack(bool _right, const VEC2& pos)
{
	auto p = pos;
	p.x += (_right ? 1 : -1)*distance;
	collider.SetStatus(p, transform.size.x, transform.size.y, 0, transform.scale);
	is_attack = true;
}