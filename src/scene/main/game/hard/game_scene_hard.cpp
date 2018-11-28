/**
* @file game_scene_hard.cpp
* @brief ゲームシーン(hard)クラスのメンバ関数の定義
* @author 石山　悠
* @date 2018/11/20
*/
#include "game_scene_hard.h"
#include "../over/game_over.h"
#include "../../../../load/map/load_map.h"

#include "../../select/select_scene.h"

/**
* @brief ゲームシーン(hard)の初期化
*/
void GameSceneHard::Init()
{
	GameInit();
	//マップの初期化
	{
		LoadMap::getinstance()->LoadingMap(L"hard_map.csv", L"hard_fly_enemy.csv");
		LoadMap::getinstance()->MakingMap(field, enemy, f_enemy, boss, player);
	}
	//背景
	{
		backGround.push_back(StaticObject());
		backGround[0].Init(std::string("background1"), L"background/background1.jpg", 600, 338,
			{ 1920 / 2,1080 / 2 }, 0, 3.5f);
	}
	//ボス
	{
		boss->SetMaxHp(30.0f);
	}
	//GameInit();
	////プレイヤーの初期化
	//{
	//	player->Init(std::string("player"), L"WizardWalkRight.png", 86, 128, { 200,200 }, 0, 0.6f);
	//}
	////敵の初期化
	//{
	//	enemy.push_front(NormalEnemy());
	//	std::begin(enemy)->Init(std::string("normalenemy1"), L"monster1.png", 400, 366, { 1000,200 }, 0, 0.2f);
	//	enemy.push_front(NormalEnemy());
	//	std::begin(enemy)->Init(std::string("normalenemy1"), L"monster1.png", 400, 366, { 800,50 }, 0, 0.2f);
	//	enemy.push_front(NormalEnemy());
	//	std::begin(enemy)->Init(std::string("normalenemy2"), L"monster1.png", 400, 366, { 2100,-100 }, 0, 0.2f);

	//	f_enemy.push_front(FlyEnemy());
	//	std::begin(f_enemy)->Init(std::string("fly_enemy"), L"bird.png", 450, 415, { 2000,-500 }, 0, 0.25f);
	//	std::begin(f_enemy)->SetMove(VEC2(100, 0), 60);
	//	f_enemy.push_front(FlyEnemy());
	//	std::begin(f_enemy)->Init(std::string("fly_enemy"), L"bird.png", 450, 415, { 300,-100 }, 0, 0.25f);
	//	std::begin(f_enemy)->SetMove(VEC2(0, 100), 60);
	//	f_enemy.push_front(FlyEnemy());
	//	std::begin(f_enemy)->Init(std::string("fly_enemy"), L"bird.png", 450, 415, { 700,-200 }, 0, 0.25f);
	//	std::begin(f_enemy)->SetMove(VEC2(100, 100), 30);
	//}
	////背景の初期化
	//{
	//	backGround.push_back(StaticObject());
	//	backGround[0].Init(std::string("background1"), L"background/background1.jpg", 600, 338,
	//		{ 1920 / 2,1080 / 2 }, 0, 3.5f);
	//}
	////マップの初期化
	//{
	//	//地面
	//	{
	//		MakeMap(field, { 64.0f * 0,64.0f * 5 }, 120, 4, std::string("field1"), L"map/map2.png", 32, 32, 0, 2);
	//		MakeMap(field, { 64.0f * 30, 64.0f * 0 }, 20, 3, std::string("field1"), L"map/map2.png", 32, 32, 0, 2);
	//	}
	//	//壁
	//	{
	//		MakeMap(field, { 64.0f * 0,64.0f * -9 }, 2, 15, std::string("field1"), L"map/map2.png", 32, 32, 0, 2);
	//		MakeMap(field, { 64.0f * 20,64.0f * 3 }, 2, 2, std::string("field1"), L"map/map2.png", 32, 32, 0, 2);
	//	}
	//	//足場
	//	{
	//		MakeMap(field, { 64.0f * 10,64.0f * 3 }, 3, 1, std::string("field1"), L"map/map2.png", 32, 32, 0, 2);
	//		MakeMap(field, { 64.0f * 15,64.0f * 1 }, 3, 1, std::string("field1"), L"map/map2.png", 32, 32, 0, 2);
	//		/*MakeMap(field, { 32.0f * 35,32.0f * 0 }, 3, 1, std::string("field1"), L"map/map2.png", 32, 32, 0, 2);
	//		MakeMap(field, { 32.0f * 40,32.0f * -5 }, 3, 1, std::string("field1"), L"map/map2.png", 32, 32, 0, 2);
	//		MakeMap(field, { 32.0f * 45,32.0f * -10 }, 3, 1, std::string("field1"), L"map/map2.png", 32, 32, 0, 2);*/
	//	}
	//}
	////ボス
	//{
	//	boss->Init(std::string("Boss"), L"boss.png", 303, 400, VEC2{ 5000.0f,-100.0f }, 0, 0.5f);
	//	boss->SetMaxHp(100.0f);
	//}
}

/**
* @brief ゲームシーン(hard)の更新
* @return std::shared_ptr<Scene> シーンが変わるなら次のシーンのstd::shared_ptr<Scene>を返す
*/
std::shared_ptr<Scene> GameSceneHard::Update(std::shared_ptr<Scene>& scene)
{
	auto current_scene = scene;

	//プレイヤーが死んだらタイトルに戻る
	if (!player->enabled)
	{
		GameOver::getinstance()->Update(current_scene, std::make_shared<GameSceneHard>());
		return current_scene;
	}

	current_scene = GameUpdate(scene);

	return current_scene;
}

/**
* @brief ゲームシーン(hard)の描画
*/
void GameSceneHard::Render()
{
	GameRender();
}

/**
* @brief ゲームシーン(hard)の破棄
*/
void GameSceneHard::Destroy()
{
	GameDestroy();
}