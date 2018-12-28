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
	sprite.Init(std::string("sword"), L"sword.png", Vec2(100, 100));
	sprite.ColorChange(0, 0, 0, 0.3f);
	hit_sound.init(std::string("sword_sound"), L"sword.wav", false, false);
	nohit_sound.init(std::string("sword_nohit_sound"), L"sword_motion.wav", false, false);
	size = Vec2(100, 100);
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
void Sword::WeaponUpdate(const Vec3& p, bool _right)
{
	if (current_delay < delay)
	{
		if (std::exchange(first, false) && !std::exchange(hit, false))
		{
			nohit_sound.stop();
			nohit_sound.play();
		}
		++current_delay;
		sprite.ColorChange(1, 1, 1, 0.8f);
	}
	else
	{
		sprite.ColorChange(0, 0, 0, 0.5f);
		first = true;
	}
	right = _right;
	//is_attack = false;

	collider.enabled = false;
	transform.set_pos(Vec3(p.x + (_right ? 1 : -1)*distance, p.y, -1));
	collider.SetStatus(transform.get_pos(), size.x,
		size.y, transform.get_scale());
}

/**
* @brief ����p�̕`��
* @param t �`��ʒu
*/
void Sword::WeaponRender(const Transform&)
{
	if (!weapon_enabled)return;
	sprite.Render(Transform(transform.get_pos(), saki::vector3_zero<float>, saki::vector3_one<float>));
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
void Sword::Collision(ObjectBase* obj, Vec2)
{
	if (obj == nullptr)return;
	/*if (!is_attack)
	{
		return;
	}*/
	if (obj->object_tag == OBJECT_TAG::ENEMY || obj->object_tag == OBJECT_TAG::BOSS || obj->object_tag == OBJECT_TAG::SELECT)
	{
		hit = true;
		hit_sound.stop();
		hit_sound.play();
	}
}

/**
* @brief �U��
* @param _right �E�������ǂ���
* @param pos �ʒu
*/
bool Sword::Attack(bool _right, const Vec3& pos)
{
	if (current_delay < delay) { return false; }
	current_delay = 0;
	auto p = pos;
	p.x += (_right ? 1 : -1)*distance;
	collider.SetStatus(Vec3{ p.x,p.y,0 }, size.x, size.y, transform.get_scale());
	//is_attack = true;
	collider.enabled = true;
	return true;
}