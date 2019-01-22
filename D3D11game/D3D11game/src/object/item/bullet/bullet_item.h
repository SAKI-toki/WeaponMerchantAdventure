#pragma once
#include "../base/item_base.h"
class BulletItem :public ItemBase
{
public:
	/**
	* @brief �R���X�g���N�^
	*/
	BulletItem() :ItemBase()
	{
		object_tag = OBJECT_TAG::BULLET_ITEM;
	}
	/**
	* @brief �R�s�[�R���X�g���N�^
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
	* @brief ���[�u�R���X�g���N�^
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
	* @brief �R�s�[������Z�q
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
	* @brief ���[�u������Z�q
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