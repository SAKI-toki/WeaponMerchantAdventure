/**
* @file enemy_base.h
* @brief エネミーのスーパークラスの宣言
* @author 石山　悠
* @date 2018/10/11
*/
#pragma once
#include "../../../base/dynamic/dynamic_object.h"
#include "../../../../collider/square/square_collider.h"

/**
* @brief 敵のタイプ
*/
enum class ENEMY_TYPE { NORMAL, NONE };

/**
* @brief エネミーのスーパークラス
*/
class EnemyBase :public DynamicObject
{
protected:
	//コライダ
	SquareCollider collider;
public:
	//敵のタイプ
	ENEMY_TYPE enemy_type;
	/**
	* @brief コンストラクタ
	* @param et 敵のタイプ
	*/
	EnemyBase(ENEMY_TYPE et) :enemy_type(et), collider(this)
	{
		object_tag = OBJECT_TAG::ENEMY;
	}

};