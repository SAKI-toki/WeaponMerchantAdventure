/**
* @file player.cpp
* @brief �v���C���[�N���X�̃����o�֐����`
* @author �ΎR�@�I
* @date 2018/10/18
*/
#include "player.h"
#include "../../../input/gamepad/gamepad_input.h"


/**
* @brief ������
*/
void Player::InitProcess()
{
	gravity.ResetGravity();
	status.Init(100, 1, 1);
	collider.SetStatus(transform.pos, transform.size.x, transform.size.y, transform.rot,transform.scale);
	weapon[weapon_num]->WeaponStart();
}
/**
* @brief �v���C���[�̍X�V
*/
void Player::UpdateProcess()
{
	//�W�����v
	if (GamepadInput::GetInstance()->GetTrigger(false))
	{
		gravity.SetPower(jump);
	}
	//�ړ�
	{
		float x = GamepadInput::GetInstance()->GetStick(false, true);
		if (x > 0)
		{
			transform.pos.x += speed;
			dire = DIRE::RIGHT;
		}
		else if (x < 0)
		{
			transform.pos.x -= speed;
			dire = DIRE::LEFT;
		}
	}
	//����̐؂�ւ�
	{
		auto prev = weapon_num;
		if (weapon_num != 1 && GamepadInput::GetInstance()->GetButtonDown(BUTTON::DPAD_UP))
		{
			weapon_num = 1;
		}
		if (weapon_num != 0 && GamepadInput::GetInstance()->GetButtonDown(BUTTON::DPAD_DOWN))
		{
			weapon_num = 0;
		}
		if (weapon_num != prev)
		{
			weapon[prev]->WeaponDestroy();
			weapon[weapon_num]->WeaponStart();
		}
		weapon[weapon_num]->WeaponUpdate(transform.pos, dire == DIRE::RIGHT ? true : false);
	}
	//�U��
	if (GamepadInput::GetInstance()->GetTrigger(true) > 0)
	{
		if (!current_trigger)
		{
			current_trigger = true;
			Attack();
		}
	}
	else
	{
		current_trigger = false;
	}
	//�d��
	transform.pos.y += gravity.AddGravity();
	collider.SetStatus(transform.pos, transform.size.x, transform.size.y, transform.rot, transform.scale);
}
/**
* @brief �v���C���[�̕`��
* @param camera_affected �J�����̈ʒu�ɂ���ĕ`�悷��ʒu��ς��邩�ǂ���
*/
void Player::RenderProcess(bool camera_affected)
{
	sprite.Render(transform, camera_affected);
	weapon[weapon_num]->WeaponRender(transform);
}
/**
* @brief �v���C���[�̔j��
*/
void Player::Destroy()
{
	if (collider.enabled)collider.Destroy();
	enabled = false;
	weapon[weapon_num]->WeaponDestroy();
}

/**
* @brief �������Ă�Ƃ��Ɏ��s����֐�
*/
void Player::Collision(ObjectBase* obj, VEC2)
{
	if (obj->object_tag == OBJECT_TAG::ENEMY)
	{
		Destroy();
		enabled = false;
	}
}
