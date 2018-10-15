/**
* @file player.cpp
* @brief �v���C���[�N���X�̃����o�֐����`
* @author �ΎR�@�I
* @date 2018/10/07
*/
#include "player.h"
#include "../../../input/gamepad/gamepad_input.h"


/**
* @brief ������
*/
void Player::InitProcess()
{
	collider.SetStatus(transform.pos, transform.size.x, transform.size.y, transform.rot);
}
/**
* @brief �v���C���[�̍X�V
*/
void Player::UpdateProcess()
{
	transform.pos.y += 0.5f;
	collider.SetStatus(transform.pos, transform.size.x, transform.size.y, transform.rot);
}
/**
* @brief �v���C���[�̔j��
*/
void Player::Destroy()
{
	if (collider.enabled)collider.Destroy();
}

/**
* @brief �������Ă�Ƃ��Ɏ��s����֐�
*/
void Player::Collision(ObjectBase* obj,VEC2 vector)
{
	if (obj->object_tag == OBJECT_TAG::ENEMY)
	{
		//Destroy();
		//enabled = false;
	}
}
