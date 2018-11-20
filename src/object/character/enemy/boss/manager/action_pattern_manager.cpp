#include "action_pattern_manager.h"
#include "../action_pattern/base/action_pattern_base.h"
#include "../boss.h"
#include "../action_pattern/move/move_action.h"

ActionPatternManager::ActionPatternManager(Boss& _boss) :
	action_pattern(std::make_shared<MoveAction>()), boss(_boss) {}


void ActionPatternManager::Update(const float x)
{
	auto next_action_pattern = action_pattern->Action(action_pattern, boss,x);
	if (next_action_pattern != action_pattern)
	{
		action_pattern->Destroy();
		action_pattern = next_action_pattern;
		action_pattern->Init();
	}

	if (boss.transform.pos.x < x - WINDOW_WIDTH / 2.0f)
	{
		boss.transform.pos.x = x - WINDOW_WIDTH / 2.0f;
		boss.ResetSpeed();
	}
	else if (boss.transform.pos.x > x + WINDOW_WIDTH / 2.0f)
	{
		boss.transform.pos.x = x + WINDOW_WIDTH / 2.0f;
		boss.ResetSpeed();
	}
}

void ActionPatternManager::Render()
{
	action_pattern->Render();
}

void ActionPatternManager::Destroy()
{
	action_pattern->Destroy();
}