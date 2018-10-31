/**
* @file fly_enemy.cpp
* @brief 飛ぶエネミークラスのメンバ関数を定義
* @author 石山　悠
* @date 2018/10/22
*/
#include "fly_enemy.h"

/**
* @brief 初期化
*/
void FlyEnemy::InitProcess()
{
	collider.SetStatus(transform.pos, transform.size.x, transform.size.y, transform.rot, transform.scale);
}

/**
* @brief 更新
*/
void FlyEnemy::UpdateProcess()
{
	if (transform.pos.y > DESTROY_Y)
	{
		Destroy();
		return;
	}
	if (!destroy_flg)
	{
		transform.pos += move;
		if ((transform.pos.x >= start_pos.x&&transform.pos.x >= end_pos.x ||
			transform.pos.x <= start_pos.x&&transform.pos.x <= end_pos.x) &&
			(transform.pos.y >= start_pos.y&&transform.pos.y >= end_pos.y ||
				transform.pos.y <= start_pos.y&&transform.pos.y <= end_pos.y))
		{
			move *= -1;
			//transform.pos += move;
		}
		collider.SetStatus(transform.pos, transform.size.x, transform.size.y, transform.rot, transform.scale);
	}
	else
	{
		transform.pos/*.y*/ += gravity.AddGravity();
	}
}

/**
* @brief 当たったときに実行する関数
* @param obj 当たった相手のオブジェクト
*/
void FlyEnemy::Collision(ObjectBase* obj, VEC2)
{
	if (obj == nullptr)return;
	if (obj->object_tag == OBJECT_TAG::WEAPON)
	{
		collider.Destroy();
		destroy_flg = true;
		gravity.ResetGravity();
		gravity.SetUpPower(5);
		transform.sprite_effect = DirectX::SpriteEffects_FlipVertically;
	}
}

/**
* @brief 破棄
*/
void FlyEnemy::Destroy()
{
	if (collider.enabled)collider.Destroy();
	enabled = false;
}

