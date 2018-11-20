#include "move_action.h"
#include "../attack/attack_action.h"

void MoveAction::Init()
{

}

std::shared_ptr<ActionPattern> MoveAction::Action(std::shared_ptr<ActionPattern>& action_ptr, Boss& boss, const float center_x)
{
	auto next_action_ptr = action_ptr;
	boss.gravity.DirectSetSidePower(4.0f*((current_jump_count % 2 == 0) ? 1.0f : -1.0f));
	if (current_jump_count > jump_count)
	{
		next_action_ptr = std::make_shared<AttackAction>();
	}
	//ƒWƒƒƒ“ƒv¬Œ÷‚É‰¹‚ğ–Â‚ç‚·
	else if (boss.gravity.SetUpPower(20.0f))
	{
		++current_jump_count;
	}

	return next_action_ptr;
}

void MoveAction::Render()
{

}

void MoveAction::Destroy()
{

}