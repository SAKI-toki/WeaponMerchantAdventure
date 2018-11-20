#pragma once

//�v���g�^�C�v�錾
class Boss;
class ActionPattern;

class ActionPatternManager
{
	std::shared_ptr<ActionPattern> action_pattern;
	Boss& boss;
public:
	ActionPatternManager(Boss&);
	void Update(const float);
	void Render();
	void Destroy();
};