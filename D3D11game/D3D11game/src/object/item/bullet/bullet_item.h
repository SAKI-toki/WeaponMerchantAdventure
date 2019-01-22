#pragma once
#include "../base/item_base.h"
class BulletItem :public ItemBase
{
public:
	/**
	* @brief コンストラクタ
	*/
	BulletItem() :ItemBase()
	{
		object_tag = OBJECT_TAG::BULLET_ITEM;
	}
	/**
	* @brief コピーコンストラクタ
	*/
	BulletItem(const BulletItem& m) :
		ItemBase()
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
	BulletItem(BulletItem&& m)noexcept :
		ItemBase()
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
	BulletItem& operator=(const BulletItem& other)
	{
		if (this != &other)
		{
			ItemBase::operator=(other);
		}
		return *this;
	}

	/**
	* @brief ムーブ代入演算子
	*/
	BulletItem& operator=(BulletItem&& other)noexcept
	{
		if (this != &other)
		{
			ItemBase::operator=(other);
		}
		return *this;
	}
};