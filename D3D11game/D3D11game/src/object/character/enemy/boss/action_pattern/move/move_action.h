#pragma once
#include "../base/action_pattern_base.h"

class MoveAction :public ActionPattern
{
	int current_jump_count = 0;
	int jump_count = 3;
public:
	void Init()final;
	std::shared_ptr<ActionPattern> Action(std::shared_ptr<ActionPattern>&, Boss&, const float)final;
	void Render()final;
	void Destroy()final;
};