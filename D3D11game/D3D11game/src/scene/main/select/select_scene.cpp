/**
* @file select_scene.cpp
* @brief セレクトシーンクラスのメンバ関数を定義
* @author 石山　悠
* @date 2018/11/19
*/
#include "select_scene.h"
#include "../../../camera/camera.h"
#include "../../../sound/bgm/bgm.h"
#include "../../../input/gamepad/gamepad_input.h"
#include "../../../collider/manager/collider_manager.h"
#include "../../../load/map/load_map.h"
#include "../game/easy/game_scene_easy.h"
#include "../game/normal/game_scene_normal.h"
#include "../game/hard/game_scene_hard.h"
#include "../title/title_scene.h"
#include "../../exit_scene.h"

/**
* @brief セレクトシーンの初期化
*/
void SelectScene::Init()
{
	constexpr Vec4 v1(10, 20, 5, 2);
	constexpr Vec4 v2(-2, 6, 2, 7);
	auto v = saki::dot(v1, v2);
	auto vv = v1.x*v2.x + v1.y*v2.y +
		v1.z*v2.z + v1.w*v2.w;


	ColliderManager::getinstance()->SetTarget(nullptr);
	Camera::getinstance()->SetTarget(nullptr);
	Sprite::has_target = false;
	Camera::getinstance()->SetPos(Vec3{ WINDOW_WIDTH / 2,0,0 });
	BGM::getinstance()->ChangeBgm(std::string("select_bgm"), L"BGM/select.wav");
	//解説
	{
		operation_transform.set_pos({ 300,100,4 });
		operation_transform.set_scale(Vec3{ operation_scale,operation_scale,1 });
		x_button.Init("x_button", L"operation/x_button.png", Vec2(186, 211));
		frame.Init("frame", L"operation/frame.png", Vec2(599, 442));
		operation_player.Init(("player"), L"WizardWalkRight.png", Vec2(86, 128));
		Animation anim;
		anim.Init(Vec2{ 86,128 }, 6, 8, 0);
		anim.ChangeAnimation(7, 10);
		operation_player.slice_num = Vec2(6, 8);
		operation_player.current_slice = Vec2(0, 7);
		//operation_player.SetRect(anim.GetAnimation());
		bullet.Init(("bullet"), L"bullet.png", Vec2(32, 32));
		momentum.Init("momentum", L"operation/momentum.png", Vec2(168, 22));
	}
	//exit
	{
		exit_sprite[0].Init("really_end", L"really_end.png", Vec2(593, 315));
		exit_sprite[1].Init("not_end", L"not_end.png", Vec2(159, 80));
		exit_sprite[2].Init("yes_end", L"yes_end.png", Vec2(153, 80));
	}
	//プレイヤー
	{
		player = std::make_unique<Player>();
		player->Init(std::string("player"), L"WizardWalkRight.png", 86, 128, { 120,250,0 },
			saki::vector3_zero<float>, { 0.6f,0.6f,1 });
	}
	//背景
	{
		background.Init("select_background", L"background/select_background.png", Vec2(1220, 620));
	}
	LoadMap::getinstance()->TitleSelectLoadingMap(L"select_map.csv");
	LoadMap::getinstance()->TitleSelectMakingMap(map, player, select_obj, exit_sign);
}

/**
* @brief セレクトシーンの更新
* @return std::shared_ptr<Scene> シーンが変わるなら次のシーンのstd::shared_ptr<Scene>を返す
*/
std::shared_ptr<Scene> SelectScene::Update(std::shared_ptr<Scene>& scene)
{
	auto current_scene = scene;
	if (exit_select)
	{
		if (exit_select_end)
		{
			player->ResetSpeed();
			player->transform.move({ -3.0f,0,0 });
			player->UpdateAnimation(false);
			if (player->transform.get_pos().x <= WINDOW_WIDTH - 100.0f)
			{
				exit_select_end = false;
				exit_select = false;
			}
		}
		//選択（左）
		else if (exit_num != 0 &&
			(GamepadInput::getinstance()->GetStick(0, false, true) < 0 ||
				GamepadInput::getinstance()->GetButton(0, BUTTON::DPAD_LEFT)))
		{
			if (!upflg)
			{
				--exit_num;
				upflg = true;
				downflg = false;
			}
		}
		//選択（右）
		else if (exit_num != 1 &&
			(GamepadInput::getinstance()->GetStick(0, false, true) > 0 ||
				GamepadInput::getinstance()->GetButton(0, BUTTON::DPAD_RIGHT)))
		{
			if (!downflg)
			{
				++exit_num;
				downflg = true;
				upflg = false;
			}
		}
		//決定
		else if (GamepadInput::getinstance()->GetButtonDown(0, BUTTON::A))
		{
			switch (exit_num)
			{
			case 0:
				exit_select_end = true;
				break;
			case 1:
				exit_flg = true;
				return std::make_shared<ExitScene>();
			}
		}
		else
		{
			upflg = false;
			downflg = false;
		}
	}
	else if (!player->enabled)
	{
		current_scene = std::make_shared<TitleScene>();
	}
	//Exit
	else if (player->transform.get_pos().x > WINDOW_WIDTH - 50.0f)
	{
		//ExitGame();
		exit_select = true;
		exit_num = 0;
		upflg = true;
		downflg = true;
	}
	else
	{
		player->Update();
		for (auto&& m : map)
		{
			m.Update();
		}
		exit_sign.Update();
		for (auto&& s_obj : select_obj)
		{
			s_obj.Update();
		}
		for (unsigned int i = 0; i < select_obj.size(); ++i)
		{
			if (select_obj[i].collision_weapon)
			{
				switch (i)
				{
				case 0:
					current_scene = std::make_shared<GameSceneEasy>();
					break;
				case 1:
					current_scene = std::make_shared<GameSceneNormal>();
					break;
				case 2:
					current_scene = std::make_shared<GameSceneHard>();
					break;
				}
				select_obj[i].Destroy();
				for (auto&& _s_obj : select_obj)
				{
					_s_obj.another_obj_collision = true;
				}
				break;
			}
		}
	}

	return current_scene;
}

/**
* @brief セレクトシーンの描画
*/
void SelectScene::Render()
{
	background.Render(Transform({ 0,0,9000 },
		saki::vector3_zero<float>, { 1.8f,1.8f,1 }), false);
	for (auto&& m : map)
	{
		m.Render();
	}
	//解説
	{
		frame.Render(operation_transform);
		x_button.Render(operation_transform +
			Transform({ 0.0f, 50.0f,-1 }, saki::vector3_zero<float>, saki::vector3_zero<float>));
		momentum.Render(operation_transform +
			Transform({ 0.0f, -150.0f * operation_scale * 0.5f,-2 }, saki::vector3_zero<float>, { 0.3f,0.3f,0 }));
		operation_player.Render(operation_transform +
			Transform({ -300.0f * operation_scale * 0.5f, -150.0f * operation_scale * 0.5f,-3 },
				saki::vector3_zero<float>, { 0.3f,0.3f,0 }));
		bullet.Render(operation_transform +
			Transform({ +300.0f * operation_scale * 0.5f, -150.0f * operation_scale * 0.5f,-3 },
				saki::vector3_zero<float>, { 0.3f,0.3f,0 }));
	}
	for (auto&& s_obj : select_obj)
	{
		s_obj.Render();
	}
	exit_sign.Render();
	player->Render();
	//exitの「はい」「いいえ」
	if (exit_select && !exit_select_end && !exit_flg)
	{
		exit_sprite[0].Render(Transform{ {0,0,-1},
			saki::vector3_zero<float>,saki::vector3_one<float> }, false);

		exit_sprite[(exit_num == 0) ? 1 : 2].ColorChange(1.0f, 1.0f, 1.0f, 1.0f);
		exit_sprite[(exit_num == 0) ? 2 : 1].ColorChange(0.4f, 0.4f, 0.4f, 1.0f);
		static float scale = 0.9f;
		static constexpr float increment_n = 0.005f;
		static float increment = increment_n;
		scale += increment;
		if (scale > 1.1f)
		{
			increment = -increment_n;
		}
		if (scale < 0.9f)
		{
			increment = increment_n;
		}
		exit_sprite[1].Render(Transform{ {-100.0f,-60.0f,-2},
			saki::vector3_zero<float>,{(exit_num == 0) ? 1.3f*scale : 1.0f,(exit_num == 0) ? 1.3f*scale : 1.0f,1} },
			false);
		exit_sprite[2].Render(Transform{ {100.0f,-60.0f,-2},
			saki::vector3_zero<float>,{(exit_num != 0) ? 1.3f*scale : 1.0f,(exit_num != 0) ? 1.3f*scale : 1.0f,1} }
		, false);
	}
	player->UiRender();
}

/**
* @brief セレクトシーンの破棄
*/
void SelectScene::Destroy()
{

	player->Destroy();
	for (auto&& m : map)
	{
		m.Destroy();
	}
	exit_sign.Destroy();
	for (auto&& s_obj : select_obj)
	{
		s_obj.Destroy();
	}
}

/**
* @brief フェード中の更新
*/
void SelectScene::ExitFadeUpdate()
{
	if (exit_flg)
	{
		player->ResetSpeed();
		player->transform.move({ 0.5f,0,0 });
		player->UpdateAnimation(true);
	}
}