/**
* @file game_scene_easy.cpp
* @brief ゲームシーン(easy)クラスのメンバ関数の定義
* @author 石山　悠
* @date 2018/11/22
*/
#include "game_scene_easy.h"
#include "../over/game_over.h"
#include "../../../../load/map/load_map.h"

#include "../../select/select_scene.h"

/**
* @brief ゲームシーン(easy)の初期化
*/
void GameSceneEasy::Init()
{
	GameInit();
	//マップの初期化
	{
		LoadMap::getinstance()->LoadingMap(L"easy_map.csv", L"easy_fly_enemy.csv");
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
	//	player->Init(std::string("player"), L"WizardWalkRight.png", 86, 128,
	//		{ 200,200 }, 0, 0.6f);
	//}
	////敵の初期化
	//{
	//	//飛ばない敵
	//	{
	//		enemy.push_front(NormalEnemy());
	//		std::begin(enemy)->Init(std::string("normalenemy1"), L"monster1.png", 400, 366,
	//			{ BLOCK_SIZE * 16,BLOCK_SIZE * 3 }, 0, 0.2f);
	//		enemy.push_front(NormalEnemy());
	//		std::begin(enemy)->Init(std::string("normalenemy2"), L"monster1.png", 400, 366,
	//			{ BLOCK_SIZE * 27,BLOCK_SIZE * 3 }, 0, 0.2f);
	//		enemy.push_front(NormalEnemy());
	//		std::begin(enemy)->Init(std::string("normalenemy2"), L"monster1.png", 400, 366,
	//			{ BLOCK_SIZE * 33,BLOCK_SIZE * 3 }, 0, 0.2f);
	//	}
	//	//飛ぶ敵
	//	{
	//		f_enemy.push_front(FlyEnemy());
	//		std::begin(f_enemy)->Init(std::string("fly_enemy"), L"bird.png", 450, 415,
	//			{ BLOCK_SIZE * 5,BLOCK_SIZE * -5 }, 0, 0.25f);
	//		std::begin(f_enemy)->SetMove(VEC2(100, 100), 60);
	//		f_enemy.push_front(FlyEnemy());
	//		std::begin(f_enemy)->Init(std::string("fly_enemy"), L"bird.png", 450, 415,
	//			{ BLOCK_SIZE * 25,BLOCK_SIZE * -8 }, 0, 0.25f);
	//		std::begin(f_enemy)->SetMove(VEC2(2000, 0), 2000);
	//		f_enemy.push_front(FlyEnemy());
	//		std::begin(f_enemy)->Init(std::string("fly_enemy"), L"bird.png", 450, 415,
	//			{ BLOCK_SIZE * 43,BLOCK_SIZE * 2 }, 0, 0.25f);
	//		std::begin(f_enemy)->SetMove(VEC2(200, 200), 60);
	//		f_enemy.push_front(FlyEnemy());
	//		std::begin(f_enemy)->Init(std::string("fly_enemy"), L"bird.png", 450, 415,
	//			{ BLOCK_SIZE * 45,BLOCK_SIZE * 2 }, 0, 0.25f);
	//		std::begin(f_enemy)->SetMove(VEC2(0, 0), 1);
	//		f_enemy.push_front(FlyEnemy());
	//		std::begin(f_enemy)->Init(std::string("fly_enemy"), L"bird.png", 450, 415,
	//			{ BLOCK_SIZE * 47,BLOCK_SIZE * 2 }, 0, 0.25f);
	//		std::begin(f_enemy)->SetMove(VEC2(-200, 200), 60);
	//	}
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
	//		MakeMap(field, { BLOCK_SIZE * 0,BLOCK_SIZE * 5 }, 120, 4, std::string("field1"), L"map/map2.png", BLOCK_TEXTURE_SIZE, BLOCK_TEXTURE_SIZE, 0, BLOCK_SCALE);
	//	}
	//	//壁
	//	{
	//		MakeMap(field, { BLOCK_SIZE * 0,BLOCK_SIZE * -10 }, 2, 15, std::string("field1"), L"map/map2.png", BLOCK_TEXTURE_SIZE, BLOCK_TEXTURE_SIZE, 0, BLOCK_SCALE);
	//		MakeMap(field, { BLOCK_SIZE * 10,BLOCK_SIZE * 3 }, 3, 2, std::string("field1"), L"map/map2.png", BLOCK_TEXTURE_SIZE, BLOCK_TEXTURE_SIZE, 0, BLOCK_SCALE);
	//		MakeMap(field, { BLOCK_SIZE * 23,BLOCK_SIZE * 3 }, 3, 2, std::string("field1"), L"map/map2.png", BLOCK_TEXTURE_SIZE, BLOCK_TEXTURE_SIZE, 0, BLOCK_SCALE);
	//		MakeMap(field, { BLOCK_SIZE * 36,BLOCK_SIZE * 3 }, 3, 2, std::string("field1"), L"map/map2.png", BLOCK_TEXTURE_SIZE, BLOCK_TEXTURE_SIZE, 0, BLOCK_SCALE);
	//	}
	//	//足場
	//	{
	//		MakeMap(field, { BLOCK_SIZE * 27,BLOCK_SIZE * 1 }, 8, 1, std::string("field1"), L"map/map2.png", BLOCK_TEXTURE_SIZE, BLOCK_TEXTURE_SIZE, 0, BLOCK_SCALE);
	//		MakeMap(field, { BLOCK_SIZE * 49,BLOCK_SIZE * 4 }, 1, 1, std::string("field1"), L"map/map2.png", BLOCK_TEXTURE_SIZE, BLOCK_TEXTURE_SIZE, 0, BLOCK_SCALE);
	//		MakeMap(field, { BLOCK_SIZE * 50,BLOCK_SIZE * 3 }, 1, 2, std::string("field1"), L"map/map2.png", BLOCK_TEXTURE_SIZE, BLOCK_TEXTURE_SIZE, 0, BLOCK_SCALE);
	//		MakeMap(field, { BLOCK_SIZE * 51,BLOCK_SIZE * 2 }, 1, 3, std::string("field1"), L"map/map2.png", BLOCK_TEXTURE_SIZE, BLOCK_TEXTURE_SIZE, 0, BLOCK_SCALE);
	//		MakeMap(field, { BLOCK_SIZE * 52,BLOCK_SIZE * 1 }, 1, 4, std::string("field1"), L"map/map2.png", BLOCK_TEXTURE_SIZE, BLOCK_TEXTURE_SIZE, 0, BLOCK_SCALE);
	//		MakeMap(field, { BLOCK_SIZE * 53,BLOCK_SIZE * 0 }, 1, 5, std::string("field1"), L"map/map2.png", BLOCK_TEXTURE_SIZE, BLOCK_TEXTURE_SIZE, 0, BLOCK_SCALE);
	//		MakeMap(field, { BLOCK_SIZE * 54,BLOCK_SIZE * -1 }, 1, 6, std::string("field1"), L"map/map2.png", BLOCK_TEXTURE_SIZE, BLOCK_TEXTURE_SIZE, 0, BLOCK_SCALE);

	//	}
	//}
	////ボス
	//{
	//	boss->Init(std::string("Boss"), L"boss.png", 303, 400, 
	//		{ 5000.0f,-200.0f }, 0, 0.5f);
	//	boss->SetMaxHp(30.0f);
	//}
}

/**
* @brief ゲームシーン(easy)の更新
* @return std::shared_ptr<Scene> シーンが変わるなら次のシーンのstd::shared_ptr<Scene>を返す
*/
std::shared_ptr<Scene> GameSceneEasy::Update(std::shared_ptr<Scene>& scene)
{
	auto current_scene = scene;

	//プレイヤーが死んだらタイトルに戻る
	if (!player->enabled)
	{
		GameOver::getinstance()->Update(current_scene, std::make_shared<GameSceneEasy>());
		return current_scene;
	}

	current_scene = GameUpdate(scene);

	return current_scene;
}

/**
* @brief ゲームシーン(easy)の描画
*/
void GameSceneEasy::Render()
{
	GameRender();
}

/**
* @brief ゲームシーン(easy)の破棄
*/
void GameSceneEasy::Destroy()
{
	GameDestroy();
}