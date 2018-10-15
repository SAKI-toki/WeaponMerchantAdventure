#include "map.h"



/**
* @brief 初期化
*/
void MapObject::InitProcess()
{
	collider.SetStatus(transform.pos, transform.size.x, transform.size.y, transform.rot);
}
/**
* @brief マップの更新
*/
void MapObject::UpdateProcess()
{
	collider.SetStatus(transform.pos, transform.size.x, transform.size.y, transform.rot);
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
void MapObject::Collision(ObjectBase* obj, VEC2 vector)
{
	if (obj->object_tag == OBJECT_TAG::ENEMY)
	{
		//Destroy();
		//enabled = false;
	}
}
