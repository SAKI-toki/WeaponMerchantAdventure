/**
* @file enemy_base.h
* @brief エネミーのスーパークラスの宣言
* @author 石山　悠
* @date 2018/10/23
*/
#pragma once
#include "../../../base/dynamic/dynamic_object.h"
#include "../../../../collider/square/square_collider.h"

/**
* @brief 敵のタイプの列挙型
*/
enum class ENEMY_TYPE { NORMAL, FLY, NONE };

/**
* @brief エネミーのスーパークラス
*/
class EnemyBase :public DynamicObject
{
protected:
	//コライダ
	SquareCollider collider;
	//削除するかどうか
	bool destroy_flg = false;
	void RenderProcess(bool)final;
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
	/**
	* @brief コピー代入演算子
	*/
	EnemyBase& operator=(const EnemyBase& other)
	{
		if (this != &other)
		{
			this->collider = other.collider;
			this->enemy_type = other.enemy_type;
			DynamicObject::operator=(other);
		}
		return *this;
	}

};