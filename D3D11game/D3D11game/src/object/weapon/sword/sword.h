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
#include "../../../sprite/sprite.h"
#include "../../../sound/sound.h"

/**
* @brief ���N���X
*/
class Sword :public WeaponBase, public ObjectBase
{
	bool first = true;
	bool hit = false;
	//���̍U��������܂ł̃f�B���C
	static constexpr int delay = 20;
	int current_delay = 0;
	//��
	Sound hit_sound;
	Sound nohit_sound;
	//�v���C���[����̋���
	static constexpr float distance = 80.0f;
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
	void WeaponStart()final;
	void WeaponUpdate(const Vec3&, bool)final;
	void WeaponDestroy()final;
	void Collision(ObjectBase*, Vec2)final;
	bool Attack(bool, const Vec3&)final;
	void WeaponRender(const Transform& = 
		Transform{ saki::vector3_zero<float>,saki::vector3_zero<float>,saki::vector3_zero<float> })final;
	void Destroy() {}
};
