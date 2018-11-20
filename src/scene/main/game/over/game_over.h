#pragma once
#include "../../../../common/saki/singleton/singleton.h"
#include "../../../../rendering/font/font.h"
#include "../../../../rendering/sprite/sprite.h"
class GameOver :public saki::singleton<GameOver>
{
	static constexpr float alpha_limit = 0.7f;
	static constexpr int delay = 120;
	Sprite black;
	Sprite next_scene[3];
	int current_select = 0;
	float alpha = 0.0f;
	Font font;
	int time = 0;

public:
	void Init();
	void Reset()
	{
		alpha = 0.0f;
		current_select = 0;
	}
	void SetColor()
	{
		black.ColorChange(1.0f, 1.0f, 1.0f, alpha);
		font.ColorChange(1.0f, 0.0f, 0.0f, alpha);
	}
	bool Update();
	void Render();
};