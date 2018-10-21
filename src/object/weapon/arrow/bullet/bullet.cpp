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
*/
void Bullet::BulletInit(const float angle)
{
	dire = VEC2(std::cos(-angle + PI<float>*0.5f), -std::sin(-angle + PI<float>*0.5f));
}
/**
* @brief ������
*/
void Bullet::InitProcess()
{
	collider.SetStatus(transform.pos, transform.size.x, transform.size.y, transform.rot, transform.scale);
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
	transform.pos += dire * speed;
	collider.SetStatus(transform.pos, transform.size.x, transform.size.y, transform.rot, transform.scale);
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
*/
void Bullet::Collision(ObjectBase* obj, VEC2)
{
	//�G�ɓ���������
	if (obj->object_tag == OBJECT_TAG::ENEMY)
	{
		obj->Destroy();
		this->Destroy();
	}
	//�}�b�v�ɓ���������
	else if (obj->object_tag == OBJECT_TAG::MAP)
	{
		this->Destroy();
	}
}