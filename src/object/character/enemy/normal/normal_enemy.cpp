/**
* @file normal_enemy.cpp
* @brief エネミークラスのメンバ関数を定義
* @author 石山　悠
* @date 2018/10/18
*/
#include "normal_enemy.h"

/**
* @brief エネミーの初期化
*/
void NormalEnemy::InitProcess()
{
	prev_left = move_left;
	gravity.ResetGravity();
	gravity.Init(max_speed);
	status.Init(100, 10, 1);
	collider.SetStatus(transform.pos, transform.size.x, transform.size.y, transform.rot, transform.scale);
}
/**
* @brief エネミーの更新
*/
void NormalEnemy::UpdateProcess()
{
	if (transform.pos.y > DESTROY_Y)
	{
		Destroy();
		return;
	}
	if (!destroy_flg)
	{
		if (move_left != prev_left)
		{
			move_left = prev_left;
			gravity.DirectSetSidePower(0);
		}
		gravity.SetSidePower(move_left ? -move_speed : move_speed);
	}
	else
	{
		if (transform.pos.y > DESTROY_Y)
		{
			Destroy();
		}
	}
	transform.pos += gravity.AddGravity();
	if (!destroy_flg)collider.SetStatus(transform.pos, transform.size.x, transform.size.y, transform.rot, transform.scale);
}
/**
* @brief エネミーの破棄
*/
void NormalEnemy::Destroy()
{
	if (collider.enabled) { collider.Destroy(); }
	enabled = false;
}

/**
* @brief エネミーの当たったときに実行する関数
* @param obj　当たった相手のオブジェクト
*/
void NormalEnemy::Collision(ObjectBase* obj,VEC2)
{
	if (this->collider.collision_is_static_x)
	{
		prev_left = !move_left;
	}
	if (obj == nullptr)return;
	if (obj->object_tag == OBJECT_TAG::WEAPON)
	{
		/*if (!status.Damage(obj->status.Attack))
		{
			return;
		}*/
		collider.Destroy();
		destroy_flg = true;
		gravity.ResetGravity();
		gravity.SetUpPower(5);
		transform.sprite_effect = DirectX::SpriteEffects_FlipVertically;
	}
}