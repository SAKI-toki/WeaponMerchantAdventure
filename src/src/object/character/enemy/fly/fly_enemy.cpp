/**
* @file fly_enemy.cpp
* @brief ��ԃG�l�~�[�N���X�̃����o�֐����`
* @author �ΎR�@�I
* @date 2018/10/22
*/
#include "fly_enemy.h"

/**
* @brief ������
*/
void FlyEnemy::InitProcess()
{
	effect.Init("effect_normal", L"bullet.png", 32, 32);
	effect.SetParam(10, 30, 10);
	collider.SetStatus(transform.get_pos(), size.x, size.y, transform.get_scale()*0.75f);
	status.Init(100, 10, 1);
}

/**
* @brief �X�V
*/
void FlyEnemy::UpdateProcess()
{
	if (transform.get_pos().y < DESTROY_Y)
	{
		Destroy();
		return;
	}
	if (!destroy_flg)
	{
		transform.move(move);
		auto rot = transform.get_rot();
		if (move.x > 0)
		{
			rot.y = saki::PI<float>;
		}
		else if (move.x < 0)
		{
			rot.y = 0;
		}
		transform.set_rot(rot);
		auto pos = transform.get_pos();
		if ((pos.x >= start_pos.x&&pos.x >= end_pos.x ||
			pos.x <= start_pos.x&&pos.x <= end_pos.x) &&
			(pos.y >= start_pos.y&&pos.y >= end_pos.y ||
				pos.y <= start_pos.y&&pos.y <= end_pos.y))
		{
			move *= -1;
		}
		collider.SetStatus(transform.get_pos(), size.x, size.y, transform.get_scale()*0.75f);
	}
	else
	{
		transform.move(gravity.AddGravity());
	}
}

/**
* @brief ���������Ƃ��Ɏ��s����֐�
* @param obj ������������̃I�u�W�F�N�g
*/
void FlyEnemy::Collision(ObjectBase* obj, Vec2)
{
	if (obj == nullptr)return;
	if (obj->object_tag == OBJECT_TAG::MAP)
	{
		move *= -1;
	}
	if (obj->object_tag == OBJECT_TAG::WEAPON)
	{
		/*if (!status.Damage(obj->status.Attack))
		{
			return;
		}*/
		effect.Start(transform.get_pos());
		collider.Destroy();
		destroy_flg = true;
		gravity.ResetGravity();
		gravity.SetUpPower(5);
		auto rot = transform.get_rot();
		rot.x = saki::PI<float>;
		transform.set_rot(rot);
	}
}

/**
* @brief �j��
*/
void FlyEnemy::Destroy()
{
	if (collider.enabled)collider.Destroy();
	enabled = false;
}

