#include "game_over.h"
#include "../../../../input/gamepad/gamepad_input.h"

void GameOver::Init()
{
	//黒のテクスチャの読み込み
	black.Init(std::string("black"), L"black.png", 1920, 1080, 1.0f, 1.0f, 1.0f, 0.0f);
	font.SetText(L"Game Over");
	font.SetTransform(Transform({ 700,300 }, 0.0f, 8.0f));
	next_scene[0].Init("one_more", L"one_more.png", 481, 133);
	next_scene[1].Init("return_select", L"return_select.png", 481, 133);
	next_scene[2].Init("return_title", L"return_title.png", 481, 133);
}

bool GameOver::Update()
{
	if (alpha < alpha_limit)
	{
		alpha += 0.01f;
	}
	else
	{
		if (time >= delay)
		{
			return true;
			auto prev_select = current_select;
			/*if (current_select != 0 && GamepadInput::GetInstance()->GetStick(false, false) < 0)
			{
				--current_select;
			}
			else if (current_select != 2 && GamepadInput::GetInstance()->GetStick(false, false) > 0)
			{
				++current_select;
			}
			else if (GamepadInput::GetInstance()->GetButton(BUTTON::A))
			{

			}
			if (prev_select != current_select)
			{
				next_scene[prev_select].ColorChange(0.4f, 0.4f, 0.4f, 1.0f);
				next_scene[current_select].ColorChange(1.0f, 1.0f, 1.0f, 1.0f);
			}*/
		}
		else
		{
			++time;
		}
	}
	return false;
}

void GameOver::Render()
{
	SetColor();
	black.Render(Transform({ 0,0 }, 0, 1), false, false);
	font.Render();
	/*for (int i = 0; i < 3; ++i)
	{
		next_scene[i].Render(Transform({ WINDOW_WIDTH / 2.0f,(600 + 150 * i) + (delay - time) * 10 }));
	}*/
}