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
		LoadMap::getinstance()->GameLoadingMap(L"easy_map.csv", L"easy_fly_enemy.csv");
		LoadMap::getinstance()->GameMakingMap(field, enemy, f_enemy, boss, player, bullet_item);
	}
	//背景
	{
		backGround.push_back(StaticObject());
		backGround[0].Init(std::string("background1"), L"background/background1.jpg", 600, 338,
			{ 0,0,9000 }, saki::vector3_zero<float>, Vec3{ 3.5f,3.5f,1 });
	}
	//ボス
	{
		boss->SetMaxHp(30.0f);
	}
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