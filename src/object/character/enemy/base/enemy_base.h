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
* @brief �G�̃^�C�v�̗񋓌^
*/
enum class ENEMY_TYPE { NORMAL, FLY, NONE };

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
	/**
	* @brief �R�s�[������Z�q
	*/
	EnemyBase& operator=(const EnemyBase& other)
	{
		if (this != &other)
		{
			this->collider = other.collider;
			this->enemy_type = other.enemy_type;
			DynamicObject::operator=(other);
		}
		return *this;
	}

};