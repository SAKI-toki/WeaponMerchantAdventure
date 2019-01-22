#include "move_action.h"
#include "../attack/attack_action.h"
#include <saki/random/random.h>
#include "../../../../../../input/gamepad/gamepad_input.h"

void MoveAction::Init()
{
	jump_count = saki::random(2, 6);
}

std::shared_ptr<ActionPattern> MoveAction::Action(std::shared_ptr<ActionPattern>& action_ptr, Boss& boss, const float)
{
	auto next_action_ptr = action_ptr;
	boss.gravity.DirectSetSidePower(4.0f*((current_jump_count % 2 == 0) ? 1.0f : -1.0f));
	if (current_jump_count > jump_count)
	{
		next_action_ptr = std::make_shared<AttackAction>();
	}
	//ƒWƒƒƒ“ƒv¬Œ÷Žž‚É‰¹‚ð–Â‚ç‚·
	else if (boss.gravity.SetUpPower(20.0f))
	{
		++current_jump_count;
		Camera::getinstance()->SetVibration(10.0f);
		GamepadInput::getinstance()->Vibration(0, 0.6f, 0.6f);
	}

	return next_action_ptr;
}

void MoveAction::Render()
{

}

void MoveAction::Destroy()
{

}