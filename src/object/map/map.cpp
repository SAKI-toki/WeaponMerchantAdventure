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
	sprite.SetRect(RECT{ 448 + 32,32,480 + 32,32 + 32 });
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
	enabled = false;
}

/**
* @brief マップが当たってるときに実行する関数
*/
void MapObject::Collision(ObjectBase* obj, VEC2)
{
	if (obj == nullptr)return;
}
