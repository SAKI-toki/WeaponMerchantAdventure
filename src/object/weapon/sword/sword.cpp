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
	sprite.Init(std::string("sword"), L"sword.png", true, 100, 100, 0, 0, 0, 0.3f);
	transform.size = VEC2(100, 100);
	transform.scale = 1;
}
/**
* @brief ����p�̏�����
*/
void Sword::WeaponStart()
{
	collider.enabled = true;
}

/**
* @brief ����p�̍X�V
* @param _right �E�������ǂ���
*/
void Sword::WeaponUpdate(const VEC2&, bool _right)
{
	right = _right;
	is_attack = false;
}

/**
* @brief ����p�̕`��
* @param t �`��ʒu
*/
void Sword::WeaponRender(const Transform& t)
{
	sprite.Render(Transform(t.pos.x + (right ? distance : -distance), t.pos.y, 0, 1));
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
*/
void Sword::Collision(ObjectBase* obj, VEC2)
{
	if (!is_attack)
	{
		return;
	}
	if (obj->object_tag == OBJECT_TAG::ENEMY)
	{
		--obj->status.HP;
		obj->Destroy();
	}
}

/**
* @brief �U��
* @param _right �E�������ǂ���
* @param pos �ʒu
*/
void Sword::Attack(bool _right, const VEC2& pos)
{
	auto p = pos;
	p.x += (_right ? 1 : -1)*distance;
	collider.SetStatus(p, transform.size.x, transform.size.y, 0, transform.scale);
	is_attack = true;
}