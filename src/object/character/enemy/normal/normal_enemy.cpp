#include "normal_enemy.h"

/**
* @brief 初期化
*/
void NormalEnemy::InitProcess()
{
	collider.SetStatus(transform.pos, transform.size.x, transform.size.y, transform.rot);
}
/**
* @brief エネミーの更新
*/
void NormalEnemy::UpdateProcess()
{
	transform.pos.y += 1.0f;
	collider.SetStatus(transform.pos, transform.size.x, transform.size.y, transform.rot);
}
/**
* @brief エネミーの破棄
*/
void NormalEnemy::Destroy()
{
	if (collider.enabled)collider.Destroy();
}

/**
* @brief エネミーの当たったときに実行する関数
*/
void NormalEnemy::Collision(ObjectBase*,VEC2)
{
	//Destroy();
	//enabled = false;
}