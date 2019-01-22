#pragma once
#include "../../base/static/static_object.h"
#include "../../../collider/square/square_collider.h"

class ItemBase :public StaticObject
{
	//コライダ
	SquareCollider collider;
protected:
	void InitProcess()final
	{
		collider.SetStatus(transform.get_pos(), size.x,
			size.y, transform.get_scale());
	}
	void UpdateProcess()final
	{
		collider.SetStatus(transform.get_pos(), size.x,
			size.y, transform.get_scale());
	}
public:
	void Destroy()final
	{
		if (collider.enabled)collider.Destroy();
		enabled = false;
	}
	/**
	* @brief コンストラクタ
	*/
	ItemBase() :collider(this, true, true)
	{
	}
	/**
	* @brief コピーコンストラクタ
	*/
	ItemBase(const ItemBase& m) :
		collider(this, true, true)
	{
		this->transform = m.transform;
		this->enabled = m.enabled;
		this->object_tag = m.object_tag;
		this->sprite = m.sprite;
		this->use_gravity = m.use_gravity;
	}
	/**
	* @brief ムーブコンストラクタ
	*/
	ItemBase(ItemBase&& m)noexcept :
		collider(this, true, true)
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
	ItemBase& operator=(const ItemBase& other)
	{
		if (this != &other)
		{
			this->collider = other.collider;
			StaticObject::operator=(other);
		}
		return *this;
	}

	/**
	* @brief ムーブ代入演算子
	*/
	ItemBase& operator=(ItemBase&& other)noexcept
	{
		if (this != &other)
		{
			this->collider = other.collider;
			StaticObject::operator=(other);
		}
		return *this;
	}

	/**
	* @brief デストラクタ
	*/
	~ItemBase()
	{
		Destroy();
	}

	void Collision(ObjectBase* obj, Vec2)final
	{
		if (obj->object_tag == OBJECT_TAG::PLAYER)
		{
			Destroy();
		}
	}
};