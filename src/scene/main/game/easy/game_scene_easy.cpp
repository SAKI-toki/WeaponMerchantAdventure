/**
* @file game_scene.cpp
* @brief ゲームシーンクラスのメンバ関数の定義
* @author 石山　悠
* @date 2018/11/08
*/
#include "game_scene_easy.h"
#include "../../../../common/common.h"
#include "../../../../rendering/font/font.h"
#include "../../../../object/camera/camera.h"
#include "../../../../input/gamepad/gamepad_input.h"
#include "../../../../sound/bgm/bgm.h"
#include "../over/game_over.h"

#include "../../select/select_scene.h"

/**
* @brief ゲームシーンの初期化
*/
void GameSceneEasy::Init()
{
	GameOver::getinstance()->Reset();
	//プレイヤーの初期化
	{
		player = std::make_unique<Player>();
		player->Init(std::string("player"), L"WizardWalkRight.png", 86, 128, { 200,200 }, 0, 0.6f);
	}
	//敵の初期化
	{
		enemy.push_front(NormalEnemy());
		std::begin(enemy)->Init(std::string("normalenemy1"), L"monster1.png", 400, 366, { 1000,200 }, 0, 0.2f);
		enemy.push_front(NormalEnemy());
		std::begin(enemy)->Init(std::string("normalenemy2"), L"monster1.png", 400, 366, { 2100,-100 }, 0, 0.2f);

		f_enemy.push_front(FlyEnemy());
		std::begin(f_enemy)->Init(std::string("fly_enemy"), L"bird.png", 450, 415, { 2000,-500 }, 0, 0.25f);
		std::begin(f_enemy)->SetMove(VEC2(100, 0), 60);
		f_enemy.push_front(FlyEnemy());
		std::begin(f_enemy)->Init(std::string("fly_enemy"), L"bird.png", 450, 415, { 300,-100 }, 0, 0.25f);
		std::begin(f_enemy)->SetMove(VEC2(0, 100), 60);
		f_enemy.push_front(FlyEnemy());
		std::begin(f_enemy)->Init(std::string("fly_enemy"), L"bird.png", 450, 415, { 700,-200 }, 0, 0.25f);
		std::begin(f_enemy)->SetMove(VEC2(100, 100), 30);
	}
	//背景の初期化
	{
		backGround.push_back(StaticObject());
		backGround[0].Init(std::string("background1"), L"background/background1.jpg", 600, 338,
			{ 1920 / 2,1080 / 2 }, 0, 3.5f);
	}
	//マップの初期化
	{
		//地面
		{
			MakeMap(field, { 64.0f * 0,64.0f * 5 }, 120, 4, std::string("field1"), L"map/map2.png", 32, 32, 0, 2);
			MakeMap(field, { 64.0f * 30, 64.0f * 0 }, 20, 3, std::string("field1"), L"map/map2.png", 32, 32, 0, 2);
		}
		//壁
		{
			MakeMap(field, { 64.0f * 0,64.0f * -9 }, 2, 15, std::string("field1"), L"map/map2.png", 32, 32, 0, 2);
			MakeMap(field, { 64.0f * 20,64.0f * 3 }, 2, 2, std::string("field1"), L"map/map2.png", 32, 32, 0, 2);
		}
		//足場
		{
			MakeMap(field, { 64.0f * 10,64.0f * 3 }, 3, 1, std::string("field1"), L"map/map2.png", 32, 32, 0, 2);
			MakeMap(field, { 64.0f * 15,64.0f * 1 }, 3, 1, std::string("field1"), L"map/map2.png", 32, 32, 0, 2);
			/*MakeMap(field, { 32.0f * 35,32.0f * 0 }, 3, 1, std::string("field1"), L"map/map2.png", 32, 32, 0, 2);
			MakeMap(field, { 32.0f * 40,32.0f * -5 }, 3, 1, std::string("field1"), L"map/map2.png", 32, 32, 0, 2);
			MakeMap(field, { 32.0f * 45,32.0f * -10 }, 3, 1, std::string("field1"), L"map/map2.png", 32, 32, 0, 2);*/
		}
	}
	//ボス
	{
		boss = std::make_unique<Boss>();
		boss->Init(std::string("Boss"), L"boss.png", 303, 400, VEC2{ 5000.0f,-100.0f }, 0, 0.5f);
		boss->SetMaxHp(30.0f);
	}
	//プレイヤーを追尾する
	Camera::GetInstance()->SetTarget(player.get());
	BGM::GetInstance()->ChangeBgm(std::string("game_bgm"), L"BGM/game.wav");
}

/**
* @brief ゲームシーンの更新
* @return std::shared_ptr<Scene> シーンが変わるなら次のシーンのstd::shared_ptr<Scene>を返す
*/
std::shared_ptr<Scene> GameSceneEasy::Update(std::shared_ptr<Scene>& scene)
{
	auto current_scene = scene;

	//プレイヤーが死んだらタイトルに戻る
	if (!player->enabled)
	{
		if (GameOver::getinstance()->Update())
		{
			current_scene = std::make_shared<SelectScene>();
		}
		return current_scene;
	}


	//敵の更新
	if (current_game == GAME::MAIN)
	{
		if (player->boss_scene)
		{
			current_game = GAME::TRANSLATION;
			Camera::GetInstance()->SetTarget(nullptr);
			boss->TranslationBossScene();
			player->TranslationBossScene();
		}
		else
		{
			//敵
			auto enemy_itr = std::begin(enemy);
			while (enemy_itr != std::end(enemy))
			{
				enemy_itr->Update();
				if (!enemy_itr->enabled)
				{
					enemy_itr = enemy.erase(enemy_itr);
				}
				else
				{
					++enemy_itr;
				}
			}
			//飛ぶ敵
			auto f_enemy_itr = std::begin(f_enemy);
			while (f_enemy_itr != std::end(f_enemy))
			{
				f_enemy_itr->Update();
				if (!f_enemy_itr->enabled)
				{
					f_enemy_itr = f_enemy.erase(f_enemy_itr);
				}
				else
				{
					++f_enemy_itr;
				}
			}
			//プレイヤーの更新
			player->Update();
		}
	}
	//ボスシーンに遷移
	else if (current_game == GAME::TRANSLATION)
	{
		if (player->transform.pos.x >= boss->transform.pos.x - 500)
		{
			current_game = GAME::BOSS;
			boss_center_x = Camera::GetInstance()->GetPos().x + WINDOW_WIDTH / 2.0f;
			boss->InBossScene(boss_center_x);
			player->InBossScene();
			for (auto&& e : enemy)
			{
				e.Destroy();
			}
			for (auto&& f : f_enemy)
			{
				f.Destroy();
			}
		}
		else
		{
			player->transform.pos.x += 2.5f;
			auto camera_pos = Camera::GetInstance()->GetPos();
			camera_pos += VEC2{ 4.0f,0.0f };
			Camera::GetInstance()->DirectSetPos(camera_pos);
			player->UpdateAnimation();
		}
		boss->Update();
		boss->ResetSpeed();
	}
	//ボスの更新
	else if (current_game == GAME::BOSS)
	{
		if (!boss->enabled)
		{
			boss->DestroyUi();
			player->EnabledWeapon();
			current_game = GAME::CLEAR;
		}

		if (player->transform.pos.x < boss_center_x - WINDOW_WIDTH / 2.0f)
		{
			player->transform.pos.x = boss_center_x - WINDOW_WIDTH / 2.0f;
			player->ResetSpeed();
		}
		else if (player->transform.pos.x > boss_center_x + WINDOW_WIDTH / 2.0f)
		{
			player->transform.pos.x = boss_center_x + WINDOW_WIDTH / 2.0f;
			player->ResetSpeed();
		}
		//プレイヤーの更新
		player->Update();
		boss->Update();
	}
	//クリア時のアニメーション
	else if (current_game == GAME::CLEAR)
	{
		player->ResetSpeed();
		if (player->transform.pos.x > boss_center_x - 10 && player->transform.pos.x < boss_center_x + 10)
		{
			if (!clear_jump&&player->gravity.SetUpPower(10.0f))
			{
				clear_jump = true;
				player->transform.Rotate(PI<float>*0.04f);
			}
			else if (clear_jump)
			{
				if (player->transform.rot != 0.0f)
				{
					player->transform.Rotate(PI<float>*0.04f);
					if (player->transform.rot > PI<float>*2.0f)
					{
						player->transform.rot = 0.0f;
					}
				}
				else if (player->gravity.SetUpPower(0.0f))
				{
					current_scene = std::make_shared<SelectScene>();
				}
			}
		}
		else
		{
			if (player->transform.pos.x < boss_center_x)
			{
				player->transform.Move(VEC2(2.5f, 0));
				player->AnimationWalk(true);
			}
			else
			{
				player->transform.Move(VEC2(-2.5f, 0));
				player->AnimationWalk(false);
			}
		}
		player->ClearUpdate();
		//current_scene = std::make_shared<TitleScene>();
	}
	//マップの更新
	for (auto&& f : field)
	{
		f.Update();
	}
	return current_scene;
}

/**
* @brief ゲームシーンの描画
*/
void GameSceneEasy::Render()
{
	//背景の描画
	for (auto&& back : backGround)
	{
		back.Render(false);
	}
	//マップの描画
	for (auto&& f : field)
	{
		f.Render();
	}
	//飛ばない敵の描画
	for (auto&& e : enemy)
	{
		e.Render();
	}
	//飛ぶ敵の描画
	for (auto&& f : f_enemy)
	{
		f.Render();
	}
	//ボスの描画
	boss->Render();
	//プレイヤーの描画
	player->Render();
	player->UiRender(); 
	if (!player->enabled)
	{
		GameOver::getinstance()->Render();
	}
}

/**
* @brief ゲームシーンの破棄
*/
void GameSceneEasy::Destroy()
{
	for (auto&& back : backGround)
	{
		back.Destroy();
	}
	for (auto&& f : field)
	{
		f.Destroy();
	}
	for (auto&& e : enemy)
	{
		e.Destroy();
	}
	for (auto&& f : f_enemy)
	{
		f.Destroy();
	}
	boss->Destroy();
	player->Destroy();
}