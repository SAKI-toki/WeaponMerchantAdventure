/**
* @file normal_enemy.h
* @brief �m�[�}���ȓG�N���X�̐錾
* @author �ΎR�@�I
* @date 2018/10/18
*/
#pragma once
#include "../base/enemy_base.h"

/**
* @brief �m�[�}���ȓG�N���X
*/
class NormalEnemy :public EnemyBase
{
	//���Ɉړ����Ă��邩�ǂ���
	bool move_left = true;
	//���������Ƃ��ɕ����]�����邽�߂̈ꎞ�I�Ɋi�[����ϐ�
	bool prev_left = true;
	//�ړ����x
	static constexpr float move_speed = 0.1f;
	static constexpr float max_speed = 2.0f;
protected:
	void InitProcess()final;
	void UpdateProcess()final;
public:
	/**
	* @brief �R���X�g���N�^
	*/
	NormalEnemy() :EnemyBase(ENEMY_TYPE::NORMAL) {}
	/**
	* @brief �R�s�[�R���X�g���N�^
	*/
	NormalEnemy(const NormalEnemy& ne) :EnemyBase(ENEMY_TYPE::NORMAL)
	{
		this->transform = ne.transform;
		this->enabled = ne.enabled;
		this->object_tag = ne.object_tag;
		this->sprite = ne.sprite;
		this->use_gravity = ne.use_gravity;
	}
	/**
	* @brief ���[�u�R���X�g���N�^
	*/
	NormalEnemy(NormalEnemy&& ne)noexcept :EnemyBase(ENEMY_TYPE::NORMAL)
	{
		this->transform = ne.transform;
		this->enabled = ne.enabled;
		this->object_tag = ne.object_tag;
		this->sprite = ne.sprite;
		this->use_gravity = ne.use_gravity;
	}
	/**
	* @brief �R�s�[������Z�q
	*/
	NormalEnemy& operator=(const NormalEnemy& other) 
	{
		if (this != &other)
		{
			this->transform = other.transform;
			this->enabled = other.enabled;
			this->object_tag = other.object_tag;
			this->sprite = other.sprite;
			this->use_gravity = other.use_gravity;
			this->collider = other.collider;
			EnemyBase::operator=(other);
		}
		return *this;
	}
	
	void Collision(ObjectBase*,VEC2)final;
	void Destroy()final;

	/**
	* @brief �f�X�g���N�^
	*/
	~NormalEnemy()
	{
		Destroy();
	}
};