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
	collider.SetStatus(transform.get_pos(), size.x,
		size.y, transform.get_scale());
	if (is_mapchip)
	{
		sprite.slice_num = Vec2{ 16,8 };
		sprite.current_slice = Vec2{ 16 ,2 };
		//sprite.SetRect(RECT{ 448 + 32,32,480 + 32,32 + 32 });
	}
}

/**
* @brief マップの更新
*/
void MapObject::UpdateProcess()
{
	collider.SetStatus(transform.get_pos(), size.x,
		size.y, transform.get_scale());
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
void MapObject::Collision(ObjectBase* obj, Vec2)
{
	if (obj == nullptr)return;
}
