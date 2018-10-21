/**
* @file map.h
* @brief �}�b�v�ɔz�u����I�u�W�F�N�g�̃N���X�̐錾
* @author �ΎR�@�I
* @date 2018/10/11
*/
#pragma once
#include "../base/static/static_object.h"
#include "../../collider/square/square_collider.h"

/**
* @brief �}�b�v�ɔz�u����I�u�W�F�N�g�̃N���X
*/
class MapObject :public StaticObject
{
	//�R���C�_
	SquareCollider collider;
protected:
	void InitProcess()final;
	void UpdateProcess()final;
public:
	void Destroy()final;
	/**
	* @brief �R���X�g���N�^
	*/
	MapObject() :collider(this, false, true)
	{
		object_tag = OBJECT_TAG::MAP;
	}
	/**
	* @brief �R�s�[�R���X�g���N�^
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
	* @brief �R�s�[������Z�q
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
	* @brief �f�X�g���N�^
	*/
	~MapObject()
	{
		Destroy();
	}
};