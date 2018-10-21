/**
* @file map.h
* @brief マップに配置するオブジェクトのクラスの宣言
* @author 石山　悠
* @date 2018/10/11
*/
#pragma once
#include "../base/static/static_object.h"
#include "../../collider/square/square_collider.h"

/**
* @brief マップに配置するオブジェクトのクラス
*/
class MapObject :public StaticObject
{
	//コライダ
	SquareCollider collider;
protected:
	void InitProcess()final;
	void UpdateProcess()final;
public:
	void Destroy()final;
	/**
	* @brief コンストラクタ
	*/
	MapObject() :collider(this, false, true)
	{
		object_tag = OBJECT_TAG::MAP;
	}
	/**
	* @brief コピーコンストラクタ
	*/
	MapObject(const MapObject& m) :
		collider(this, false,true)
	{
		this->transform = m.transform;
		this->enabled = m.enabled;
		this->object_tag = m.object_tag;
		this->sprite = m.sprite;
		this->use_gravity = m.use_gravity;
	}
	/**
	* @brief コピー代入演算子
	*/
	MapObject& operator=(const MapObject& other)
	{
		if (this != &other)
		{
			this->collider = other.collider;
			StaticObject::operator=(other);
		}
		return *this;
	}

	void Collision(ObjectBase*, VEC2)final;

	/**
	* @brief デストラクタ
	*/
	~MapObject()
	{
		Destroy();
	}
};