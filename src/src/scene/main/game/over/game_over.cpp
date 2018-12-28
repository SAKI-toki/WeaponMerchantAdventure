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
#include <saki/random/random.h>

/**
* @brief ゲームオーバーシーンの初期化
*/
void GameOver::Init()
{
	//黒のテクスチャの読み込み
	black.Init(std::string("black"), L"black.png", Vec2(1920, 1080));
	black.ColorChange(1, 1, 1, 0);
	game_over.Init("game_over", L"game_over.png", Vec2(238, 80));
	game_over.ColorChange(1.0f, 0.0f, 0.0f, 1.0f);
	blood.Init("blood", L"blood.png", Vec2(125, 203));
	next_scene[0].Init("one_more", L"one_more.png", Vec2(481, 133));
	next_scene[0].ColorChange(brightness, brightness, brightness, 1.0f);
	next_scene[1].Init("return_select", L"return_select.png", Vec2(481, 133));
	next_scene[1].ColorChange(0.4f, 0.4f, 0.4f, 1.0f);
	next_scene[2].Init("return_title", L"return_title.png", Vec2(481, 133));
	next_scene[2].ColorChange(0.4f, 0.4f, 0.4f, 1.0f);
	move_sound.init(std::string("menu_move_sound"), L"menu_move.wav", false, false);
	accept_sound.init(std::string("menu_accept_sound"), L"menu_accept.wav", false, false);
}

/**
* @brief ゲームオーバーシーンの更新
* @param scene_ptr 現在のシーン情報を格納し、シーン遷移時にも利用する
* @param continue_next ゲームシーンがどの難易度かわかるようにする
*/
void GameOver::Update(std::shared_ptr<Scene>& scene_ptr, std::shared_ptr<Scene>&& continue_next)
{
	game_over_flg = true;
	//血が落ちるアニメーション
	if (++current_blood_time > blood_time)
	{
		current_blood_time = 0;
		blood_time = saki::random(10, 30);
		blood_pos.push_back(blood_status());
		(std::end(blood_pos) - 1)->pos = { saki::random<float>(0.0f,WINDOW_WIDTH),WINDOW_HEIGHT / 2 + 100,0 };
		(std::end(blood_pos) - 1)->scale = saki::random(0.1f, 0.5f);
	}
	//フェイドイン
	if (alpha < alpha_limit)
	{
		//最初だけBGMを変える処理を行う
		if (std::exchange(first, false))
		{
			BGM::getinstance()->ChangeBgm("over", L"BGM/over.wav");
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
				(GamepadInput::getinstance()->GetStick(0, false, false) > 0 ||
					GamepadInput::getinstance()->GetButton(0, BUTTON::DPAD_UP)))
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
				(GamepadInput::getinstance()->GetStick(0, false, false) < 0 ||
					GamepadInput::getinstance()->GetButton(0, BUTTON::DPAD_DOWN)))
			{
				if (!downflg)
				{
					++current_select;
					downflg = true;
					upflg = false;
				}
			}
			//決定
			else if (GamepadInput::getinstance()->GetButtonDown(0, BUTTON::A))
			{
				accept_sound.stop();
				accept_sound.play();
				switch (current_select)
				{
				case 0:
					SceneManager::getinstance()->ContinueGame(continue_next);
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
				move_sound.stop();
				move_sound.play();
				next_scene[prev_select].ColorChange(0.4f, 0.4f, 0.4f, 1.0f);
			}
			next_scene[current_select].ColorChange(brightness, brightness, brightness, 1.0f);
		}
		else
		{
			if (GamepadInput::getinstance()->GetButtonDown(0, BUTTON::A))
			{
				time = delay;
			}
			else
			{
				++time;
			}
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
	black.Render(Transform({ 0,0,0 }, { 0,0,0 }, { 1,1,1 }), false);
	game_over.Render(Transform({ 0,300.0f,0 }, { 0,0,0 }, { 3,3,3 }), false);
	//血の描画
	auto itr = std::begin(blood_pos);
	while (itr != std::end(blood_pos))
	{
		blood.Render(Transform(itr->pos, { 0,0,0 }, { itr->scale,itr->scale,1 }), false);
		itr->pos.y -= 10;
		if (itr->pos.y > WINDOW_HEIGHT / 2 - 300)
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
		next_scene[i].Render(Transform({ 0,
			(-200.0f * i) - (delay - time) * 10.0f,0 }, { 0,0,0 },
			Vec3((current_select == i) ? 1.2f : 0.8f, (current_select == i) ? 1.2f : 0.8f, 1)),
			false);
	}
}