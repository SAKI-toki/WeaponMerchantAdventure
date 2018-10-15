/**
* @file player.cpp
* @brief プレイヤークラスのメンバ関数を定義
* @author 石山　悠
* @date 2018/10/07
*/
#include "player.h"
#include "../../../input/gamepad/gamepad_input.h"


/**
* @brief 初期化
*/
void Player::InitProcess()
{
	collider.SetStatus(transform.pos, transform.size.x, transform.size.y, transform.rot);
}
/**
* @brief プレイヤーの更新
*/
void Player::UpdateProcess()
{
	transform.pos.y += 0.5f;
	collider.SetStatus(transform.pos, transform.size.x, transform.size.y, transform.rot);
}
/**
* @brief プレイヤーの破棄
*/
void Player::Destroy()
{
	if (collider.enabled)collider.Destroy();
}

/**
* @brief 当たってるときに実行する関数
*/
void Player::Collision(ObjectBase* obj,VEC2 vector)
{
	if (obj->object_tag == OBJECT_TAG::ENEMY)
	{
		//Destroy();
		//enabled = false;
	}
}
