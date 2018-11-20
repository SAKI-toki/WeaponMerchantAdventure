/**
* @file bullet.h
* @brief ���������킩��o��e�N���X�̐錾
* @author �ΎR�@�I
* @date 2018/10/18
*/
#pragma once
#include "../../../base/dynamic/dynamic_object.h"
#include "../../../../collider/square/square_collider.h"
#include "../arrow.h"

/**
* @brief �e�N���X
*/
class Bullet :public DynamicObject
{
	//bool is_
	//���������Ƃ��Ɏ��s����֐�
	std::function<void()> arrow_func;
	//�e��
	static constexpr float speed = 20.0f;
	//�e�̎����i�t���[�����j
	static constexpr int life_time = 120;
	//�R���C�_
	SquareCollider collider;
	//�ǂ̕����Ɍ������Ĕ�Ԃ�
	VEC2 dire;
	//��������Ă���̎���
	int life = 0;
protected:
	void InitProcess()final;
	void UpdateProcess()final;
public:
	/**
	* @brief �R���X�g���N�^
	*/
	Bullet() :collider(this, true)
	{
		object_tag = OBJECT_TAG::WEAPON;
	}
	/**
	* @brief �R�s�[�R���X�g���N�^
	*/
	Bullet(const Bullet& b) :collider(this, true)
	{
		this->transform = b.transform;
		this->dire = b.dire;
		this->enabled = b.enabled;
		this->object_tag = b.object_tag;
		this->sprite = b.sprite;
		this->use_gravity = b.use_gravity;
		this->life = b.life;
	}

	/**
	* @brief �R�s�[������Z�q
	*/
	Bullet& operator=(const Bullet& other)
	{
		if (this != &other)
		{
			this->transform = other.transform;
			this->dire = other.dire;
			this->enabled = other.enabled;
			this->object_tag = other.object_tag;
			this->sprite = other.sprite;
			this->use_gravity = other.use_gravity;
			this->life = other.life;
		}
		return *this;
	}

	/**
	* @brief ���[�u�R���X�g���N�^
	*/
	Bullet(Bullet&& b) :collider(this, true)
	{
		this->transform = b.transform;
		this->dire = b.dire;
		this->enabled = b.enabled;
		this->object_tag = b.object_tag;
		this->sprite = b.sprite;
		this->use_gravity = b.use_gravity;
		this->life = b.life;
	}

	void BulletInit(const float, const std::function<void()>&);
	void Destroy()final;
	void Collision(ObjectBase*, VEC2)final;

	/**
	* @brief �f�X�g���N�^
	*/
	~Bullet()
	{
		Destroy();
	}
};