/**
* @file select_scene.cpp
* @brief セレクトシーンクラスのメンバ関数を定義
* @author 石山　悠
* @date 2018/11/19
*/
#include "select_scene.h"
#include "../../../object/camera/camera.h"
#include "../../../sound/bgm/bgm.h"
#include "../../../input/gamepad/gamepad_input.h"
#include "../../../rendering/font/font.h"

#include "../game/easy/game_scene_easy.h"
#include "../game/normal/game_scene_normal.h"
#include "../game/hard/game_scene_hard.h"

/**
* @brief セレクトシーンの初期化
*/
void SelectScene::Init()
{
	//プレイヤー
	{
		player = std::make_unique<Player>();
		player->Init(std::string("player"), L"WizardWalkRight.png", 86, 128, { 120,250 }, 0, 0.6f);
	}
	//マップ
	{
		MakeMap(map, { 64.0f * 0,64.0f * 5 }, 40, 4, std::string("field1"), L"map/map2.png", 32, 32, 0, 2);
		MakeMap(map, { 64.0f * 0,64.0f * -10 }, 2, 15, std::string("field1"), L"map/map2.png", 32, 32, 0, 2);
		MakeMap(map, { 64.0f * 29,64.0f * -10 }, 2, 15, std::string("field1"), L"map/map2.png", 32, 32, 0, 2);
		MakeMap(map, { 64.0f * 4 ,64.0 * 4 }, 3, 1, std::string("field1"), L"map/map2.png", 32, 32, 0, 2);
		MakeMap(map, { 64.0f * 14 ,64.0 * 4 }, 3, 1, std::string("field1"), L"map/map2.png", 32, 32, 0, 2);
		MakeMap(map, { 64.0f * 24 ,64.0 * 4 }, 3, 1, std::string("field1"), L"map/map2.png", 32, 32, 0, 2);
	}
	//セレクトオブジェクト
	{
		select_obj.push_back(SelectObj());
		select_obj[0].Init("select_obj_easy", L"select_easy.png", 599, 550, { 64.0f * 5,220.0f - 64.0f }, 0, 0.25f);
		select_obj.push_back(SelectObj());
		select_obj[1].Init("select_obj_normal", L"select_normal.png", 599, 550, { 64.0f * 15,220.0f - 64.0f }, 0, 0.25f);
		select_obj.push_back(SelectObj());
		select_obj[2].Init("select_obj_hard", L"select_hard.png", 599, 550, { 64.0f * 25,220.0f - 64.0f }, 0, 0.25f);
	}
	//背景
	{
		background.Init("select_background", L"background/select_background.png", 1220, 620);
		font.Init(L"選んだ難易度を攻撃しよう！");
		font.SetTransform(Transform({ 350,300 }, 0, 6));
	}
	Camera::GetInstance()->SetTarget(nullptr);
	Camera::GetInstance()->SetPos({ 0.0f, 0.0f });
	BGM::GetInstance()->ChangeBgm(std::string("select_bgm"), L"BGM/select.wav");
}

/**
* @brief セレクトシーンの更新
* @return std::shared_ptr<Scene> シーンが変わるなら次のシーンのstd::shared_ptr<Scene>を返す
*/
std::shared_ptr<Scene> SelectScene::Update(std::shared_ptr<Scene>& scene)
{
	auto current_scene = scene;

	player->Update();
	for (auto&& m : map)
	{
		m.Update();
	}
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

	return current_scene;
}

/**
* @brief セレクトシーンの描画
*/
void SelectScene::Render()
{
	background.Render(Transform({ WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f }, 0, 1.8f), false);
	font.Render();
	for (auto&& m : map)
	{
		m.Render();
	}
	for (auto&& s_obj : select_obj)
	{
		s_obj.Render();
	}
	player->Render();
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
	for (auto&& s_obj : select_obj)
	{
		s_obj.Destroy();
	}
}