/**
* @file player.cpp
* @brief プレイヤークラスのメンバ関数を定義
* @author 石山　悠
* @date 2018/11/19
*/
#include "player.h"
#include "../../../input/gamepad/gamepad_input.h"

/**
* @brief 初期化
*/
void Player::InitProcess()
{
	which_weapon_ui[0].Init("weapon_ui_sword", L"sword_ui.png", 592, 592);
	which_weapon_ui[1].Init("weapon_ui_magic", L"magic_ui.png", 592, 592, 0.5f, 0.5f, 0.5f, 1.0f);
	gravity.Init(max_speed);
	gravity.ResetGravity();
	transform.pos += gravity.AddGravity();
	jump_sound.Init(std::string("jump_sound"), L"jump.wav", false, false);
	status.Init(100, 10, 1);
	collider.SetStatus(transform.pos, transform.size.x, transform.size.y, transform.rot, transform.scale*collider_scale);
	weapon[weapon_num]->WeaponStart();
	anim.Init(transform.size, 6, 8, 0);
	anim.ChangeAnimation(0, 30);
}

/**
* @brief プレイヤーの更新
*/
void Player::UpdateProcess()
{
	if (transform.pos.y > DESTROY_Y)
	{
		Destroy();
		return;
	}
	/*if (is_invincible)
	{
		if (++current_invincible_time >= invincible_time)
		{
			current_invincible_time = 0;
			is_invincible = false;
		}
	}*/
	anim.Update();
	if (!destroy_flg)
	{
		//ジャンプ
		if (GamepadInput::GetInstance()->GetTrigger(false) > 0)
		{
			if (!current_trigger_left)
			{
				current_trigger_left = true;
				//ジャンプ成功時に音を鳴らす
				if (gravity.SetUpPower(jump))
				{
					jump_sound.Stop();
					jump_sound.Start();
				}
			}

		}
		else
		{
			current_trigger_left = false;
		}
		//移動
		{
			float x = GamepadInput::GetInstance()->GetStick(false, true);
			//右に移動
			if (x > 0)
			{
				gravity.SetSidePower(speed);
				dire = DIRE::RIGHT;
				anim.ChangeAnimation(6, 10);
			}
			//左に移動
			else if (x < 0)
			{
				gravity.SetSidePower(-speed);
				dire = DIRE::LEFT;
				anim.ChangeAnimation(2, 10);
			}
			//止まっている
			else
			{
				//完全に止まった
				if (gravity.ReturnZero(speed*1.5f))
				{
					anim.ChangeAnimation(0, 30);
				}
			}
		}
		//武器の切り替え
		{
			auto prev = weapon_num;
			if (weapon_num != 1 && GamepadInput::GetInstance()->GetButtonDown(BUTTON::L1))
			{
				weapon_num = 1;
			}
			if (weapon_num != 0 && GamepadInput::GetInstance()->GetButtonDown(BUTTON::R1))
			{
				weapon_num = 0;
			}
			if (weapon_num != prev)
			{
				which_weapon_ui[prev].ColorChange(0.5f, 0.5f, 0.5f, 1.0f);
				weapon[prev]->WeaponDestroy();
				weapon[weapon_num]->WeaponStart();
				which_weapon_ui[weapon_num].ColorChange(1.0f, 1.0f, 1.0f, 1.0f);
			}
			weapon[weapon_num]->WeaponUpdate(transform.pos, dire == DIRE::RIGHT ? true : false);
		}
		//攻撃
		if (GamepadInput::GetInstance()->GetTrigger(true) > 0)
		{
			if (!current_trigger_right)
			{
				current_trigger_right = true;
				Attack();
			}
		}
		else
		{
			current_trigger_right = false;
		}
	}
	//重力
	transform.pos += gravity.AddGravity();
	if (!destroy_flg)collider.SetStatus(transform.pos, transform.size.x, transform.size.y, transform.rot, transform.scale*collider_scale);
}

/**
* @brief プレイヤーの描画
* @param camera_affected カメラの位置によって描画する位置を変えるかどうか
*/
void Player::RenderProcess(bool camera_affected)
{
	sprite.SetRect(anim.GetAnimation());
	sprite.Render(transform, camera_affected, true, transform.sprite_effect);
	weapon[weapon_num]->WeaponRender(transform);
}

/**
* @brief プレイヤーの破棄
*/
void Player::Destroy()
{
	if (collider.enabled)collider.Destroy();
	enabled = false;
	weapon[weapon_num]->WeaponDestroy();
}

/**
* @brief 当たってるときに実行する関数
*/
void Player::Collision(ObjectBase* obj, VEC2)
{
	if (obj == nullptr)return;
	if (obj->object_tag == OBJECT_TAG::ENEMY)
	{
		/*if (is_invincible) { return; }
		if (!status.Damage(obj->status.Attack)) 
		{
			is_invincible = true;
			return;
		}
		else*/
		{
			collider.Destroy();
			destroy_flg = true;
			gravity.ResetGravity();
			gravity.SetUpPower(5);
			weapon[weapon_num]->WeaponDestroy();
			transform.sprite_effect = DirectX::SpriteEffects_FlipVertically;
		}
	}
	else if (obj->object_tag == OBJECT_TAG::BOSS)
	{
		if (boss_scene)
		{
			collider.Destroy();
			destroy_flg = true;
			gravity.ResetGravity();
			gravity.SetUpPower(5);
			weapon[weapon_num]->WeaponDestroy();
			transform.sprite_effect = DirectX::SpriteEffects_FlipVertically;
		}
		else
		{
			boss_scene = true;
			gravity.ResetGravity();
			gravity.ResetSideGravity();
		}
	}
}


/**
* @brief 攻撃
*/
void Player::Attack()
{
	weapon[weapon_num]->Attack((dire == DIRE::RIGHT ? true : false), transform.pos);
}
