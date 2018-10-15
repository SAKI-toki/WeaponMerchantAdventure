/**
* @file collider_base.h
* @brief コライダのスーパークラスの宣言、定義
* @author 石山　悠
* @date 2018/10/11
*/
#pragma once
#include "../../object/base/object_base.h"

/**
* @brief コライダのスーパークラス
*/
class ColliderBase
{
public:
	//押し出しするかどうか
	const bool is_trigger;
	//x方向に対して押し出ししないものぶつかったかどうか
	bool collision_is_trigger_x;
	//y方向に対して押し出ししないものぶつかったかどうか
	bool collision_is_trigger_y;
	//このコライダを持つオブジェクト
	ObjectBase* object;
	//当たっているときに実行する関数
	std::function<void(ObjectBase*,VEC2)> collision_func;
	//判定するかどうか
	bool enabled;

	/**
	* @brief コンストラクタ
	* @param obj オブジェクト
	* @param _is_trigger 押し出しするかどうか
	*/
	ColliderBase(ObjectBase* obj, bool _is_trigger = false) :
		enabled(true), object(obj), is_trigger(_is_trigger), collision_is_trigger_x(false), collision_is_trigger_y(false)
	{
		//当たったときに実行する関数を格納
		collision_func = std::bind(&ObjectBase::Collision, obj, std::placeholders::_1, std::placeholders::_2);
	}

	virtual ~ColliderBase() {}
};