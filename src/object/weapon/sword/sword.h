/**
* @file sword.h
* @brief ���N���X�̐錾
* @author �ΎR�@�I
* @date 2018/10/15
*/
#pragma once
#include "../base/weapon_base.h"
#include "../../base/object_base.h"
#include "../../../collider/square/square_collider.h"
#include "../../../rendering/sprite/sprite.h"
#include "../../../sound/sound.h"

/**
* @brief ���N���X
*/
class Sword :public WeaponBase, public ObjectBase
{
	//���̍U��������܂ł̃f�B���C
	static constexpr int delay = 30;
	int current_delay = 0;
	//��
	Sound sound;
	//�v���C���[����̋���
	static constexpr float distance = 80.0f;
	//�A�^�b�N���Ă��邩�ǂ����̃t���O
	//bool is_attack = false;
	//�R���W����
	SquareCollider collider;
	Sprite sprite;
	//�v���C���[���E�������Ă��邩�ǂ���
	bool right = true;
protected:
	void RenderProcess(bool)final {}
	void InitProcess()final {}
	void UpdateProcess()final {}
public:
	//�R���X�g���N�^
	Sword();
	/**
	* @brief �R�s�[�R���X�g���N�^
	*/
	Sword(const Sword& s) :collider(this, true)
	{
		this->transform = s.transform;
	}
	/**
	* @brief ������Z�q
	*/
	Sword& operator=(const Sword& other)
	{
		if (this != &other)
		{
			//this->is_attack = other.is_attack;
			this->collider = other.collider;
			ObjectBase::operator=(other);
		}
		return *this;
	}
	void WeaponStart();
	void WeaponUpdate(const VEC2&,bool);
	void WeaponDestroy()final;
	void Collision(ObjectBase*, VEC2)final;
	void Attack(bool, const VEC2&)final;
	void WeaponRender(const Transform& = NULL);
	void Destroy() {}
};
