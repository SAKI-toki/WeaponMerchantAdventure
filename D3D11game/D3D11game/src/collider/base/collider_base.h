/**
* @file collider_base.h
* @brief コライダのスーパークラスの宣言、定義
* @author 石山　悠
* @date 2018/10/11
*/
#pragma once
#include "../../common/common.h"
#include "../../object/base/object_base.h"
#include <functional>
/**
* @brief コライダのスーパークラス
*/
class ColliderBase
{
public:
	//当たったときに消えるフラグ
	bool collision_destroy = false;
	//押し出しするかどうか
	bool is_trigger;
	//x方向に対して押し出ししないものぶつかったかどうか
	bool collision_is_static_x = false;
	//y方向に対して押し出ししないものぶつかったかどうか
	bool collision_is_static_y = false;
	//このコライダを持つオブジェクト
	ObjectBase* object;
	//当たっているときに実行する関数
	std::function<void(ObjectBase*,Vec2)> collision_func;
	//判定するかどうか
	bool enabled = true;

	/**
	* @brief コンストラクタ
	* @param obj オブジェクト
	* @param _is_trigger 押し出しするかどうか
	*/
	ColliderBase(ObjectBase* obj, bool _is_trigger = false) :
		object(obj), is_trigger(_is_trigger)
	{
		//当たったときに実行する関数を格納
		collision_func = std::bind(&ObjectBase::Collision, obj, std::placeholders::_1, std::placeholders::_2);
	}

	/**
	* @brief コピー代入演算子
	*/
	ColliderBase& operator=(const ColliderBase& other)
	{
		if (this != &other)
		{
			this->collision_func = other.collision_func;
			this->collision_is_static_x = other.collision_is_static_x;
			this->collision_is_static_y = other.collision_is_static_y;
			this->enabled = other.enabled;
			this->is_trigger = other.is_trigger;
			this->object = other.object;
		}
		return *this;
	}

	virtual ~ColliderBase() {}
};