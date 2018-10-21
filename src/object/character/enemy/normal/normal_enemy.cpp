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
	prev_left = move_left;
	gravity.ResetGravity();
	status.Init(100, 1, 1);
	collider.SetStatus(transform.pos, transform.size.x, transform.size.y, transform.rot, transform.scale);
}
/**
* @brief �G�l�~�[�̍X�V
*/
void NormalEnemy::UpdateProcess()
{
	move_left = prev_left;
	transform.pos.y += gravity.AddGravity();
	transform.pos.x += move_left ? -move_speed : move_speed;
	collider.SetStatus(transform.pos, transform.size.x, transform.size.y, transform.rot, transform.scale);
}
/**
* @brief �G�l�~�[�̔j��
*/
void NormalEnemy::Destroy()
{
	if (collider.enabled)collider.Destroy();
	enabled = false;
}

/**
* @brief �G�l�~�[�̓��������Ƃ��Ɏ��s����֐�
*/
void NormalEnemy::Collision(ObjectBase*,VEC2)
{
	if (this->collider.collision_is_static_x)
	{
		prev_left = !move_left;
	}
	//Destroy();
	//enabled = false;
}