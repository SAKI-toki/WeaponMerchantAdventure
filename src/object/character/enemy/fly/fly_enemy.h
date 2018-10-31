/**
* @file fly_enemy.h
* @brief ��ԃG�l�~�[�N���X�̐錾
* @author �ΎR�@�I
* @date 2018/10/22
*/
#pragma once
#include "../base/enemy_base.h"
/**
* @brief ��ԃG�l�~�[�N���X
*/
class FlyEnemy :public EnemyBase
{
	//�X�^�[�g�ƏI���̊Ԃ��ړ�����
	VEC2 start_pos, end_pos, move;
protected:
	void InitProcess()final;
	void UpdateProcess()final;
public:
	/**
	* @brief �R���X�g���N�^
	*/
	FlyEnemy() :EnemyBase(ENEMY_TYPE::FLY) {}
	/**
	* @brief �R�s�[�R���X�g���N�^
	*/
	FlyEnemy(const FlyEnemy& ne) :EnemyBase(ENEMY_TYPE::FLY)
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
	FlyEnemy(FlyEnemy&& ne) :EnemyBase(ENEMY_TYPE::FLY)
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
	FlyEnemy& operator=(const FlyEnemy& other)
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
	void Collision(ObjectBase*, VEC2)final;
	void Destroy()final;

	/**
	* @brief �f�X�g���N�^
	*/
	~FlyEnemy()
	{
		Destroy();
	}

	/**
	* @brief �ړ��͈͂����߂�
	* @param range ���݂̈ʒu����ǂ̂��炢�ړ����邩
	* @param time �ǂ̂��炢�̎��Ԃ������čs�������邩
	*/
	void SetMove(const VEC2& range, float time)
	{
		VEC2 _range = range / 2;
		start_pos = VEC2(transform.pos.x - _range.x, transform.pos.y - _range.y);
		end_pos = VEC2(transform.pos.x + _range.x, transform.pos.y + _range.y);
		move = (start_pos - end_pos) / time;
	}
};