/**
* @file bullet.cpp
* @brief ���������킩��o��e�N���X�̃����o�֐����`
* @author �ΎR�@�I
* @date 2018/10/18
*/
#include "bullet.h"
/**
* @brief �e�̏�����
* @param angle ���ˊp�x
* @param func ���������Ƃ��Ɏ��s����֐�
*/
void Bullet::BulletInit(const float angle, const std::function<void()>& func)
{
	dire = Vec3(std::cos(-angle + saki::PI<float>*0.5f), -std::sin(-angle + saki::PI<float>*0.5f), 0);
	arrow_func = func;
	status.Init(1, 5, 1);
}
/**
* @brief ������
*/
void Bullet::InitProcess()
{
	collider.SetStatus(transform.get_pos(), size.x,
		size.y, transform.get_scale());
}

/**
* @brief �X�V
*/
void Bullet::UpdateProcess()
{
	//�����������������
	if (life++ > life_time)
	{
		this->Destroy();
		return;
	}
	transform.move(dire * speed);
	collider.SetStatus(transform.get_pos(), size.x,
		size.y, transform.get_scale());
}

/**
* @brief �j��
*/
void Bullet::Destroy()
{
	if (collider.enabled)collider.Destroy();
	enabled = false;
}

/**
* @brief ���������Ƃ��Ɏ��s����֐�
* @param obj ������������̃I�u�W�F�N�g
*/
void Bullet::Collision(ObjectBase* obj, Vec2)
{
	if (obj == nullptr)return;
	//�G�ɓ���������
	if (obj->object_tag == OBJECT_TAG::ENEMY)
	{
		arrow_func();
	}
	//�G���Ŕ̏ꍇ�̓f�X�g���C����
	else if (obj->object_tag == OBJECT_TAG::BOSS || obj->object_tag == OBJECT_TAG::SELECT)
	{
		arrow_func();
		this->Destroy();
	}
	//�}�b�v�ɓ���������
	else if (obj->object_tag == OBJECT_TAG::MAP)
	{
		this->Destroy();
	}
	else if (obj->object_tag == OBJECT_TAG::BOSS_BULLET)
	{
		arrow_func();
		this->Destroy();
	}
}