#pragma once
#include "../base/static/static_object.h"
#include "../../collider/square/square_collider.h"
#include <array>

class SelectObj :public StaticObject
{
	//�R���C�_
	SquareCollider collider;
protected:
	void InitProcess()final;
	void UpdateProcess()final;
public:
	bool collision_weapon = false;
	bool another_obj_collision = false;
	void Destroy()final;
	/**
	* @brief �R���X�g���N�^
	*/
	SelectObj() :collider(this, true, true)
	{
		object_tag = OBJECT_TAG::MAP;
	}
	/**
	* @brief �R�s�[�R���X�g���N�^
	*/
	SelectObj(const SelectObj& m) :
		collider(this, true, true)
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
	SelectObj(SelectObj&& m)noexcept :
		collider(this, true, true)
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
	SelectObj& operator=(const SelectObj& other)
	{
		if (this != &other)
		{
			this->collider = other.collider;
			StaticObject::operator=(other);
		}
		return *this;
	}

	/**
	* @brief ���[�u������Z�q
	*/
	SelectObj& operator=(SelectObj&& other)noexcept
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
	* @brief �f�X�g���N�^
	*/
	~SelectObj()
	{
		Destroy();
	}
};