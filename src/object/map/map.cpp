/**
* @file map.cpp
* @brief マップに配置するオブジェクトのクラスのメンバ関数を定義
* @author 石山　悠
* @date 2018/10/11
*/
#include "map.h"

/**
* @brief 初期化
*/
void MapObject::InitProcess()
{
	collider.SetStatus(transform.pos, transform.size.x, transform.size.y, transform.rot, transform.scale);
}
/**
* @brief マップの更新
*/
void MapObject::UpdateProcess()
{
	collider.SetStatus(transform.pos, transform.size.x, transform.size.y, transform.rot, transform.scale);
}
/**
* @brief マップの破棄
*/
void MapObject::Destroy()
{
	if (collider.enabled)collider.Destroy();
}

/**
* @brief マップが当たってるときに実行する関数
*/
void MapObject::Collision(ObjectBase* obj, VEC2)
{
}
