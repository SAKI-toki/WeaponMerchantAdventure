/**
* @file sword.cpp
* @brief ���N���X�̃����o�֐����`
* @author �ΎR�@�I
* @date 2018/10/18
*/
#include "sword.h"

/**
* @brief �R���X�g���N�^
*/
Sword::Sword() :collider(this, true)
{
	object_tag = OBJECT_TAG::WEAPON;
	status.Init(1, 20, 1);
	sprite.Init(std::string("sword"), L"sword.png", 100, 100, 0, 0, 0, 0.3f);
	hit_sound.Init(std::string("sword_sound"), L"sword.wav", false, false);
	nohit_sound.Init(std::string("sword_nohit_sound"), L"sword_motion.wav", false, false);
	transform.size = VEC2(100, 100);
	transform.scale = 1;
}

/**
* @brief ����p�̏�����
*/
void Sword::WeaponStart()
{
	//collider.enabled = true;
	collider.enabled = false;
	current_delay = delay;
}

/**
* @brief ����p�̍X�V
* @param p �ʒu
* @param _right �E�������ǂ���
*/
void Sword::WeaponUpdate(const VEC2& p, bool _right)
{
	if (current_delay < delay)
	{
		if (std::exchange(first, false) && !std::exchange(hit, false))
		{
			nohit_sound.Stop();
			nohit_sound.Start();
		}
		++current_delay;
		sprite.ColorChange(1, 0, 0, 0.3f);
	}
	else
	{
		sprite.ColorChange(0, 0, 0, 0.3f);
		first = true;
	}
	right = _right;
	//is_attack = false;

	collider.enabled = false;
	transform.pos = VEC2(p.x + (_right ? 1 : -1)*distance, p.y);
	collider.SetStatus(VEC2(p.x + (_right ? 1 : -1)*distance, p.y), transform.size.x, transform.size.y, 0, transform.scale);
}

/**
* @brief ����p�̕`��
* @param t �`��ʒu
*/
void Sword::WeaponRender(const Transform& t)
{
	if (!weapon_enabled)return;
	sprite.Render(Transform(transform.pos, 0, 1));
}

/**
* @brief ����p�̔j��
*/
void Sword::WeaponDestroy()
{
	collider.enabled = false;
}

/**
* @brief ���������Ƃ��̔���
* @param obj ������������̃I�u�W�F�N�g
*/
void Sword::Collision(ObjectBase* obj, VEC2)
{
	if (obj == nullptr)return;
	/*if (!is_attack)
	{
		return;
	}*/
	if (obj->object_tag == OBJECT_TAG::ENEMY || obj->object_tag == OBJECT_TAG::BOSS || obj->object_tag == OBJECT_TAG::SELECT)
	{
		hit = true;
		hit_sound.Stop();
		hit_sound.Start();
	}
}

/**
* @brief �U��
* @param _right �E�������ǂ���
* @param pos �ʒu
*/
void Sword::Attack(bool _right, const VEC2& pos)
{
	if (current_delay < delay) { return; }
	current_delay = 0;
	auto p = pos;
	p.x += (_right ? 1 : -1)*distance;
	collider.SetStatus(p, transform.size.x, transform.size.y, 0, transform.scale);
	//is_attack = true;
	collider.enabled = true;
}