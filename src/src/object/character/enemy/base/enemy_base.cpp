/**
* @file enemy_base.cpp
* @brief エネミーのスーパークラスのメンバ関数を定義
* @author 石山　悠
* @date 2018/10/23
*/
#include "enemy_base.h"

/**
* @brief 描画
* @param camera_affected カメラの位置によって描画する位置を変えるかどうか
*/
void EnemyBase::RenderProcess(bool camera_affected)
{
	sprite.Render(transform, camera_affected);
}