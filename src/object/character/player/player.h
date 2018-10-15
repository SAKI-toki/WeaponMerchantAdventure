/**
* @file player.h
* @brief プレイヤークラスを宣言
* @author 石山　悠
* @date 2018/10/10
*/
#pragma once
#include "../../base/dynamic/dynamic_object.h"
#include "../../../collider/square/square_collider.h"

/**
* @brief プレイヤークラス
*/
class Player :public DynamicObject
{
	//当たり判定
	SquareCollider collider;
protected:
	void InitProcess()final;
	void UpdateProcess()final;
public:
	void Destroy()final;
	/**
	* @brief コンストラクタ
	*/
	Player() :collider(this)
	{
		object_tag = OBJECT_TAG::PLAYER;
	}

	void Collision(ObjectBase*,VEC2)final;
};