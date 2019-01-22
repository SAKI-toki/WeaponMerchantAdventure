/**
* @file normal_enemy.cpp
* @brief �G�l�~�[�N���X�̃����o�֐����`
* @author �ΎR�@�I
* @date 2018/10/18
*/
#include "normal_enemy.h"

/**
* @brief �G�l�~�[�̏�����
*/
void NormalEnemy::InitProcess()
{
	effect.Init("effect_normal", L"effect_blood.png", 42, 42);
	effect.SetScale(Vec3{ 0.4f,0.4f,0.4f });
	effect.SetParam(20, 30, 10);
	prev_left = move_left;
	gravity.ResetGravity();
	gravity.Init(max_speed);
	status.Init(100, 10, 1);
	collider.SetStatus(transform.get_pos(), size.x, size.y, transform.get_scale()*0.75f);
}
/**
* @brief �G�l�~�[�̍X�V
*/
void NormalEnemy::UpdateProcess()
{
	if (transform.get_pos().y < DESTROY_Y)
	{
		Destroy();
		return;
	}
	if (!destroy_flg)
	{
		if (move_left != prev_left)
		{
			move_left = prev_left;
			gravity.DirectSetSidePower(0);
		}
		gravity.SetSidePower(move_left ? -move_speed : move_speed);
		auto rot = transform.get_rot();
		rot.y = (move_left) ? 0 : saki::PI<float>;
		transform.set_rot(rot);
	}
	else
	{
		if (transform.get_pos().y < DESTROY_Y)
		{
			Destroy();
		}
	}
	transform.set_pos(gravity.AddGravity() + transform.get_pos());
	if (!destroy_flg)
		collider.SetStatus(transform.get_pos(), size.x, size.y, transform.get_scale()*0.75f);
}
/**
* @brief �G�l�~�[�̔j��
*/
void NormalEnemy::Destroy()
{
	if (collider.enabled) { collider.Destroy(); }
	enabled = false;
}

/**
* @brief �G�l�~�[�̓��������Ƃ��Ɏ��s����֐�
* @param obj�@������������̃I�u�W�F�N�g
*/
void NormalEnemy::Collision(ObjectBase* obj,Vec2)
{
	if (this->collider.collision_is_static_x)
	{
		ChangeDire();
	}
	if (obj == nullptr)return;
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