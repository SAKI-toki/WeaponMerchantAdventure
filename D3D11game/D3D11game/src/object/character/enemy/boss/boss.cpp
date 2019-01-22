#include "boss.h"
#include <saki/random/random.h>
#include "../../../../input/gamepad/gamepad_input.h"

/**
* @brief エネミーの初期化
*/
void Boss::InitProcess()
{
	effect.Init("effect_normal", L"effect_blood.png", 42, 42);
	effect.SetParam(30, 60, 5);
	damage_effect.Init("effect_normal", L"bullet.png", 32, 32);
	damage_effect.SetParam(5, 30, 10);
	gravity.ResetGravity();
	gravity.Init(max_speed);
	collider.SetStatus(transform.get_pos(), WINDOW_WIDTH*2.2f, WINDOW_HEIGHT*2.2f, transform.get_scale());
	delay = saki::random(30, 120);
	constexpr float ui_size = 8.0f;
	constexpr Vec3 ui_pos{ -400.0f,400.0f,0 };
	ui_hp_back.Init("hp_bar_back", L"hp_bar_back.png", 102, 12,
		ui_pos, saki::vector3_zero<float>, { ui_size,ui_size,1 });
	ui_hp.Init("hp_bar", L"hp_bar.png", 100, 10, ui_pos, saki::vector3_zero<float>, { ui_size,ui_size,1 });
	ui_hp_back.SetColor(0.0f, 0.0f, 0.0f, 1.0f);
	ui_hp.SetColor(1.0f, 1.0f, 0.0f, 1.0f);
}
/**
* @brief エネミーの更新
*/
void Boss::UpdateProcess()
{
	if (transform.get_pos().y < DESTROY_Y)
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
	transform.set_pos(gravity.AddGravity() + transform.get_pos());
	if (!boss_scene && !boss_translation_scene)
	{
		collider.SetStatus(transform.get_pos(), WINDOW_WIDTH*2.2f, WINDOW_HEIGHT*2.2f, saki::vector3_one<float>);
	}
	else
	{
		if (!destroy_flg)
		{
			collider.SetStatus(transform.get_pos(), size.x, size.y, transform.get_scale());
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
	sprite.Render(transform, camera_affected);
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
void Boss::Collision(ObjectBase* obj, Vec2)
{
	if (obj == nullptr || !boss_scene)return;
	if (obj->object_tag == OBJECT_TAG::WEAPON)
	{
		if (!status.Damage(obj->status.Attack))
		{
			damage_effect.Start(transform.get_pos());
			return;
		}
		effect.Start(transform.get_pos());
		percentage = 0.0f;
		action_pattern_manager.Destroy();
		collider.Destroy();
		destroy_flg = true;
		gravity.ResetGravity();
		gravity.SetUpPower(5);
		auto rot = transform.get_rot();
		rot.x = saki::PI<float>;
		transform.set_rot(rot);
	}
}
