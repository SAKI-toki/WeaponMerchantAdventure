/**
* @file game_scene_normal.cpp
* @brief ゲームシーン(normal)クラスのメンバ関数の定義
* @author 石山　悠
* @date 2018/11/20
*/
#include "game_scene_normal.h"
#include "../over/game_over.h"
#include "../../../../load/map/load_map.h"

#include "../../select/select_scene.h"


/**
* @brief ゲームシーン(normal)の初期化
*/
void GameSceneNormal::Init()
{
	GameInit();
	//マップの初期化
	{
		LoadMap::getinstance()->LoadingMap(L"normal_map.csv", L"normal_fly_enemy.csv");
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
}

/**
* @brief ゲームシーン(normal)の更新
* @return std::shared_ptr<Scene> シーンが変わるなら次のシーンのstd::shared_ptr<Scene>を返す
*/
std::shared_ptr<Scene> GameSceneNormal::Update(std::shared_ptr<Scene>& scene)
{
	auto current_scene = scene;

	//プレイヤーが死んだらタイトルに戻る
	if (!player->enabled)
	{
		GameOver::getinstance()->Update(current_scene, std::make_shared<GameSceneNormal>());
		return current_scene;
	}
	current_scene = GameUpdate(scene);
	return current_scene;
}

/**
* @brief ゲームシーン(normal)の描画
*/
void GameSceneNormal::Render()
{
	GameRender();
}

/**
* @brief ゲームシーン(normal)の破棄
*/
void GameSceneNormal::Destroy()
{
	GameDestroy();
}