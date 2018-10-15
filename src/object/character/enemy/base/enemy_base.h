/**
* @file enemy_base.h
* @brief �G�l�~�[�̃X�[�p�[�N���X�̐錾
* @author �ΎR�@�I
* @date 2018/10/11
*/
#pragma once
#include "../../../base/dynamic/dynamic_object.h"
#include "../../../../collider/square/square_collider.h"

/**
* @brief �G�̃^�C�v
*/
enum class ENEMY_TYPE { NORMAL, NONE };

/**
* @brief �G�l�~�[�̃X�[�p�[�N���X
*/
class EnemyBase :public DynamicObject
{
protected:
	//�R���C�_
	SquareCollider collider;
public:
	//�G�̃^�C�v
	ENEMY_TYPE enemy_type;
	/**
	* @brief �R���X�g���N�^
	* @param et �G�̃^�C�v
	*/
	EnemyBase(ENEMY_TYPE et) :enemy_type(et), collider(this)
	{
		object_tag = OBJECT_TAG::ENEMY;
	}

};