#pragma once
#include "../base/action_pattern_base.h"
#include "bullet/boss_bullet.h"
#include <list>

class AttackAction :public ActionPattern
{
	static constexpr float speed = 0.3f;
	std::list<BossBullet> bullet;
	static constexpr int interval = 10;
	int bullet_num = 0;
	int num = 0;
	int time = 0;
public:
	void Init()final;
	std::shared_ptr<ActionPattern> Action(std::shared_ptr<ActionPattern>&, Boss&, const float)final;
	void Render()final;
	void Destroy()final;
};