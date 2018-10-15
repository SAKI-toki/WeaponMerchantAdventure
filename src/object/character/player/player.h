/**
* @file player.h
* @brief �v���C���[�N���X��錾
* @author �ΎR�@�I
* @date 2018/10/10
*/
#pragma once
#include "../../base/dynamic/dynamic_object.h"
#include "../../../collider/square/square_collider.h"

/**
* @brief �v���C���[�N���X
*/
class Player :public DynamicObject
{
	//�����蔻��
	SquareCollider collider;
protected:
	void InitProcess()final;
	void UpdateProcess()final;
public:
	void Destroy()final;
	/**
	* @brief �R���X�g���N�^
	*/
	Player() :collider(this)
	{
		object_tag = OBJECT_TAG::PLAYER;
	}

	void Collision(ObjectBase*,VEC2)final;
};