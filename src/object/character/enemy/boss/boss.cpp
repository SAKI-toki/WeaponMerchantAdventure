#include "boss.h"
#include "../../../../common/saki/random/random.h"

/**
* @brief エネミーの初期化
*/
void Boss::InitProcess()
{
	gravity.ResetGravity();
	gravity.Init(max_speed);
	collider.SetStatus(transform.pos, WINDOW_WIDTH*1.2f, WINDOW_HEIGHT*1.2f, 0, 1);
	delay = saki::random(30, 120);
	constexpr float ui_size = 8.0f;
	constexpr VEC2 ui_pos{ 50.0f,50.0f };
	ui_hp_back.Init("hp_bar_back", L"hp_bar_back.png", 102, 12,
		ui_pos - VEC2{ 2 * ui_size / 2,2 * ui_size / 2 }, 0, ui_size);
	ui_hp.Init("hp_bar", L"hp_bar.png", 100, 10, ui_pos, 0, ui_size);
	ui_hp_back.SetColor(0.0f, 0.0f, 0.0f, 1.0f);
	ui_hp.SetColor(1.0f, 1.0f, 0.0f, 1.0f);
}
/**
* @brief エネミーの更新
*/
void Boss::UpdateProcess()
{
	if (transform.pos.y > DESTROY_Y)
	{
		Destroy();
		return;
	}
	if (!destroy_flg)
	{
		if (boss_scene)
		{
			ui_hp.enabled = true;
			ui_hp_back.enabled = true;
			object_tag = OBJECT_TAG::BOSS;
			action_pattern_manager.Update(boss_scene_center_pos_x);
		}
	}
	transform.pos += gravity.AddGravity();
	if (!boss_scene && !boss_translation_scene)
	{
		collider.SetStatus(transform.pos, WINDOW_WIDTH*1.2f, WINDOW_HEIGHT*1.2f, 0, 1);
	}
	else
	{
		if (!destroy_flg)
		{
			collider.SetStatus(transform.pos, transform.size.x, transform.size.y, transform.rot, transform.scale);
		}
	}
}
/**
* @brief 描画
* @param camera_affected カメラの位置によって位置を変えるかどうか
*/
void Boss::RenderProcess(bool camera_affected)
{
	ui_hp.SetPercent(percentage);
	if (percentage >= 0.2f && percentage <= 0.4f)
	{
		ui_hp.SetColor(1.0f, (percentage - 0.2f) * 5, 0.0f, 1.0f);
	}
	auto percent = status.HP / MAX_HP;
	if (percent < percentage - 0.01f)
	{
		percentage -= 0.01f;
	}
	else
	{
		percentage = percent;
	}
	sprite.Render(transform, camera_affected, true, transform.sprite_effect);
	action_pattern_manager.Render();
}

/**
* @brief エネミーの破棄
*/
void Boss::Destroy()
{
	if (collider.enabled) { collider.Destroy(); }
	enabled = false;
	action_pattern_manager.Destroy();
}

/**
* @brief エネミーの当たったときに実行する関数
* @param obj　当たった相手のオブジェクト
*/
void Boss::Collision(ObjectBase* obj, VEC2)
{
	if (obj == nullptr || !boss_scene)return;
	if (obj->object_tag == OBJECT_TAG::WEAPON)
	{
		if (!status.Damage(obj->status.Attack))
		{
			return;
		}
		percentage = 0.0f;
		action_pattern_manager.Destroy();
		collider.Destroy();
		destroy_flg = true;
		gravity.ResetGravity();
		gravity.SetUpPower(5);
		transform.sprite_effect = DirectX::SpriteEffects_FlipVertically;
	}
}