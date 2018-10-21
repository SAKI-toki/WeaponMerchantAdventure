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
	status.Init(100, 1, 1);
	collider.SetStatus(transform.pos, transform.size.x, transform.size.y, transform.rot, transform.scale);
}
/**
* @brief エネミーの更新
*/
void NormalEnemy::UpdateProcess()
{
	move_left = prev_left;
	transform.pos.y += gravity.AddGravity();
	transform.pos.x += move_left ? -move_speed : move_speed;
	collider.SetStatus(transform.pos, transform.size.x, transform.size.y, transform.rot, transform.scale);
}
/**
* @brief エネミーの破棄
*/
void NormalEnemy::Destroy()
{
	if (collider.enabled)collider.Destroy();
	enabled = false;
}

/**
* @brief エネミーの当たったときに実行する関数
*/
void NormalEnemy::Collision(ObjectBase*,VEC2)
{
	if (this->collider.collision_is_static_x)
	{
		prev_left = !move_left;
	}
	//Destroy();
	//enabled = false;
}