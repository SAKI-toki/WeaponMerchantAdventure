/**
* @file player.cpp
* @brief プレイヤークラスのメンバ関数を定義
* @author 石山　悠
* @date 2018/10/29
*/
#include "player.h"
#include "../../../input/gamepad/gamepad_input.h"


/**
* @brief 初期化
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
* @brief プレイヤーの更新
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
		//ジャンプ
		if (GamepadInput::GetInstance()->GetTrigger(false))
		{
			//ジャンプ成功時に音を鳴らす
			if (gravity.SetUpPower(jump))
			{
				//TODO:サウンド
			}
		}
		//移動
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
		//武器の切り替え
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
		//攻撃
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
	//重力
	transform.pos/*.y*/ += gravity.AddGravity();
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
		collider.Destroy();
		destroy_flg = true;
		gravity.ResetGravity();
		gravity.SetUpPower(5);
		weapon[weapon_num]->WeaponDestroy();
		transform.sprite_effect = DirectX::SpriteEffects_FlipVertically;
	}
}


/**
* @brief 攻撃
*/
void Player::Attack()
{
	weapon[weapon_num]->Attack((dire == DIRE::RIGHT ? true : false), transform.pos);
}
