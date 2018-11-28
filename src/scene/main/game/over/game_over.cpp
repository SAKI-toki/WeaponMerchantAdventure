/**
* @file game_over.cpp
* @brief ゲームオーバーシーンの定義
* @author 石山　悠
* @date 2018/11/26
*/
#include "game_over.h"
#include "../../../../input/gamepad/gamepad_input.h"
#include "../../../manager/scene_manager.h"
#include "../../select/select_scene.h"
#include "../../title/title_scene.h"
#include "../../../../sound/bgm/bgm.h"
#include "../../../../common/saki/random/random.h"

/**
* @brief ゲームオーバーシーンの初期化
*/
void GameOver::Init()
{
	//黒のテクスチャの読み込み
	black.Init(std::string("black"), L"black.png", 1920, 1080, 1.0f, 1.0f, 1.0f, 0.0f);
	game_over.Init("game_over", L"game_over.png", 238, 80);
	game_over.ColorChange(1.0f, 0.0f, 0.0f, 1.0f);
	blood.Init("blood", L"blood.png", 125, 203);
	next_scene[0].Init("one_more", L"one_more.png", 481, 133);
	next_scene[0].ColorChange(brightness, brightness, brightness, 1.0f);
	next_scene[1].Init("return_select", L"return_select.png", 481, 133);
	next_scene[1].ColorChange(0.4f, 0.4f, 0.4f, 1.0f);
	next_scene[2].Init("return_title", L"return_title.png", 481, 133);
	next_scene[2].ColorChange(0.4f, 0.4f, 0.4f, 1.0f);
}

/**
* @brief ゲームオーバーシーンの更新
* @param scene_ptr 現在のシーン情報を格納し、シーン遷移時にも利用する
* @param continue_next ゲームシーンがどの難易度かわかるようにする
*/
void GameOver::Update(std::shared_ptr<Scene>& scene_ptr, std::shared_ptr<Scene>&& continue_next)
{
	//血が落ちるアニメーション
	if (++current_blood_time > blood_time)
	{
		current_blood_time = 0;
		blood_time = saki::random(10, 30);
		blood_pos.push_back(blood_status());
		(std::end(blood_pos) - 1)->pos = { saki::random<float>(0.0f,WINDOW_WIDTH),-100 };
		(std::end(blood_pos) - 1)->scale = saki::random(0.1f, 0.5f);
	}
	//フェイドイン
	if (alpha < alpha_limit)
	{
		//最初だけBGMを変える処理を行う
		if (std::exchange(first, false))
		{
			BGM::GetInstance()->ChangeBgm("over", L"BGM/over.wav");
			rendering_flg = true;
		}
		alpha += 0.01f;
	}
	//フェイドイン終了
	else
	{
		if (time >= delay)
		{
			auto prev_select = current_select;
			//明るさ変更
			{
				if (bright_down)
				{
					brightness -= 0.003f;
					if (brightness <= brightness_downlimit)
						bright_down = !bright_down;
				}
				else
				{
					brightness += 0.003f;
					if (brightness >= brightness_uplimit)
						bright_down = !bright_down;
				}
			}
			//選択（上）
			if (current_select != 0 &&
				(GamepadInput::GetInstance()->GetStick(false, false) > 0 ||
					GamepadInput::GetInstance()->GetButton(BUTTON::DPAD_UP)))
			{
				if (!upflg)
				{
					--current_select;
					upflg = true;
					downflg = false;
				}
			}
			//選択（下）
			else if (current_select != 2 &&
				(GamepadInput::GetInstance()->GetStick(false, false) < 0 ||
					GamepadInput::GetInstance()->GetButton(BUTTON::DPAD_DOWN)))
			{
				if (!downflg)
				{
					++current_select;
					downflg = true;
					upflg = false;
				}
			}
			//決定
			else if (GamepadInput::GetInstance()->GetButton(BUTTON::A))
			{
				switch (current_select)
				{
				case 0:
					SceneManager::GetInstance()->ContinueGame(continue_next);
					return;
				case 1:
					scene_ptr = std::make_shared<SelectScene>();
					return;
				case 2:
					scene_ptr = std::make_shared<TitleScene>();
					return;
				}
			}
			else
			{
				upflg = false;
				downflg = false;
			}
			//色の変更
			if (prev_select != current_select)
			{
				next_scene[prev_select].ColorChange(0.4f, 0.4f, 0.4f, 1.0f);
			}
			next_scene[current_select].ColorChange(brightness, brightness, brightness, 1.0f);
		}
		else
		{
			++time;
		}
	}
}

/**
* @brief ゲームオーバーシーンの描画
*/
void GameOver::Render()
{
	if (!rendering_flg)return;
	//色をセット
	SetColor();
	black.Render(Transform({ 0,0 }, 0, 1), false, false);
	game_over.Render(Transform({ WINDOW_WIDTH / 2.0f,300.0f },0,3.0f), false);
	//血の描画
	auto itr = std::begin(blood_pos);
	while (itr != std::end(blood_pos))
	{
		blood.Render(Transform(itr->pos, 0.0f, itr->scale), false);
		itr->pos.y += 10;
		if (itr->pos.y > WINDOW_HEIGHT + 300)
		{
			itr = blood_pos.erase(itr);
		}
		else
		{
			++itr;
		}
	}
	//選択肢の描画
	for (int i = 0; i < 3; ++i)
	{
		next_scene[i].Render(Transform({ WINDOW_WIDTH / 2.0f,(500.0f + 200.0f * i) + (delay - time) * 10.0f }, 0, ((current_select == i) ? 1.2f : 0.8f)), false);
	}
}