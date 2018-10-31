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
	collider.SetStatus(transform.pos, transform.size.x, transform.size.y, transform.rot, transform.scale);
}

/**
* @brief �X�V
*/
void FlyEnemy::UpdateProcess()
{
	if (transform.pos.y > DESTROY_Y)
	{
		Destroy();
		return;
	}
	if (!destroy_flg)
	{
		transform.pos += move;
		if ((transform.pos.x >= start_pos.x&&transform.pos.x >= end_pos.x ||
			transform.pos.x <= start_pos.x&&transform.pos.x <= end_pos.x) &&
			(transform.pos.y >= start_pos.y&&transform.pos.y >= end_pos.y ||
				transform.pos.y <= start_pos.y&&transform.pos.y <= end_pos.y))
		{
			move *= -1;
			//transform.pos += move;
		}
		collider.SetStatus(transform.pos, transform.size.x, transform.size.y, transform.rot, transform.scale);
	}
	else
	{
		transform.pos/*.y*/ += gravity.AddGravity();
	}
}

/**
* @brief ���������Ƃ��Ɏ��s����֐�
* @param obj ������������̃I�u�W�F�N�g
*/
void FlyEnemy::Collision(ObjectBase* obj, VEC2)
{
	if (obj == nullptr)return;
	if (obj->object_tag == OBJECT_TAG::WEAPON)
	{
		collider.Destroy();
		destroy_flg = true;
		gravity.ResetGravity();
		gravity.SetUpPower(5);
		transform.sprite_effect = DirectX::SpriteEffects_FlipVertically;
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

