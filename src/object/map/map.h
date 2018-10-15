#pragma once
#include "../base/static/static_object.h"
#include "../../collider/square/square_collider.h"

class MapObject :public StaticObject
{
	SquareCollider collider;
protected:
	void InitProcess()final;
	void UpdateProcess()final;
public:
	void Destroy()final;
	/**
	* @brief �R���X�g���N�^
	*/
	MapObject() :collider(this, true, true)
	{
		object_tag = OBJECT_TAG::PLAYER;
	}
	/**
	* @brief ���[�u�R���X�g���N�^
	*/
	MapObject(MapObject&& m) :
		collider(this, true,true)
	{
		m.collider.Destroy();
	}

	void Collision(ObjectBase*, VEC2)final;

};