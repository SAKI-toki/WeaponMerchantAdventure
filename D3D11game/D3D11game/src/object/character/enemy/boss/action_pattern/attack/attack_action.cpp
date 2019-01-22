#include "attack_action.h"
#include "../move/move_action.h"
#include <saki/random/random.h>
#include "../../../../../../input/gamepad/gamepad_input.h"

void AttackAction::Init()
{
	bullet_num = saki::random(10, 20);
}

std::shared_ptr<ActionPattern> AttackAction::Action(std::shared_ptr<ActionPattern>& action_ptr, Boss& boss, const float center_pos_x)
{
	auto next_action_ptr = action_ptr;
	if (num > bullet_num)
	{
		if (bullet.empty())
		{
			next_action_ptr = std::make_shared<MoveAction>();
		}
	}
	else if (++time > interval)
	{
		++num;
		time = 0;
		bullet.push_front(BossBullet());
		std::begin(bullet)->Init("buss_bullet", L"sample5.png", 32, 32, boss.transform.get_pos());
		auto angle = saki::random(0.0f, saki::PI<float>*2.0f);
		std::begin(bullet)->SetVector({ std::cos(angle), std::sin(angle) });
	}

	//弾の更新
	auto itr = std::begin(bullet);
	while (itr != std::end(bullet))
	{
		itr->Update();
		if (!itr->enabled)
		{
			itr = bullet.erase(itr);
		}
		else
		{
			++itr;
		}
	}

	//ジャンプ成功時に音を鳴らす
	if (boss.gravity.SetUpPower(saki::random(5.0f, 10.0f)))
	{
		boss.gravity.DirectSetSidePower(saki::random(1.0f, 3.0f)*((boss.transform.get_pos().x < center_pos_x) ? 1.0f : -1.0f));
		Camera::getinstance()->SetVibration(5.0f);
		GamepadInput::getinstance()->Vibration(0, 0.4f, 0.4f);
	}
	return next_action_ptr;
}

void AttackAction::Render()
{
	for (auto&& b : bullet)
	{
		b.Render();
	}
}

void AttackAction::Destroy()
{
	for (auto&& b : bullet)
	{
		b.Destroy();
	}
	bullet.clear();
}