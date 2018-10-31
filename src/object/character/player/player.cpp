/**
* @file player.cpp
* @brief �v���C���[�N���X�̃����o�֐����`
* @author �ΎR�@�I
* @date 2018/10/29
*/
#include "player.h"
#include "../../../input/gamepad/gamepad_input.h"


/**
* @brief ������
*/
void Player::InitProcess()
{
	gravity.Init(max_speed);
	gravity.ResetGravity();
	status.Init(100, 1, 1);
	collider.SetStatus(transform.pos, transform.size.x, transform.size.y, transform.rot, transform.scale*collider_scale);
	weapon[weapon_num]->WeaponStart();
	anim.Init(transform.size, 6, 8, 0);
	anim.ChangeAnimation(0, 30);
}
/**
* @brief �v���C���[�̍X�V
*/
void Player::UpdateProcess()
{
	if (transform.pos.y > DESTROY_Y)
	{
		Destroy();
		return;
	}
	anim.Update();
	if (!destroy_flg)
	{
		//�W�����v
		if (GamepadInput::GetInstance()->GetTrigger(false))
		{
			//�W�����v�������ɉ���炷
			if (gravity.SetUpPower(jump))
			{
				//TODO:�T�E���h
			}
		}
		//�ړ�
		{
			float x = GamepadInput::GetInstance()->GetStick(false, true);
			if (x > 0)
			{
				//transform.pos.x += speed;
				gravity.SetSidePower(speed);
				dire = DIRE::RIGHT;
				anim.ChangeAnimation(6, 10);
			}
			else if (x < 0)
			{
				//transform.pos.x -= speed;
				gravity.SetSidePower(-speed);
				dire = DIRE::LEFT;
				anim.ChangeAnimation(2, 10);
			}
			else
			{
				if (gravity.ReturnZero(speed * 2.5f))
				{
					anim.ChangeAnimation(0, 30);
				}
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
	}
	//�d��
	transform.pos/*.y*/ += gravity.AddGravity();
	if (!destroy_flg)collider.SetStatus(transform.pos, transform.size.x, transform.size.y, transform.rot, transform.scale*collider_scale);
}
/**
* @brief �v���C���[�̕`��
* @param camera_affected �J�����̈ʒu�ɂ���ĕ`�悷��ʒu��ς��邩�ǂ���
*/
void Player::RenderProcess(bool camera_affected)
{
	sprite.SetRect(anim.GetAnimation());
	sprite.Render(transform, camera_affected, true, transform.sprite_effect);
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
	if (obj == nullptr)return;
	if (obj->object_tag == OBJECT_TAG::ENEMY)
	{
		collider.Destroy();
		destroy_flg = true;
		gravity.ResetGravity();
		gravity.SetUpPower(5);
		weapon[weapon_num]->WeaponDestroy();
		transform.sprite_effect = DirectX::SpriteEffects_FlipVertically;
	}
}


/**
* @brief �U��
*/
void Player::Attack()
{
	weapon[weapon_num]->Attack((dire == DIRE::RIGHT ? true : false), transform.pos);
}
