/**
* @file game_over.cpp
* @brief ゲームオーバークラスのメンバ関数を定義
* @author 石山　悠
* @date 2018/10/29
*/
#include "game_over.h"

/**
* @brief ゲームオーバーシーンの初期化
*/
void GameOverScene::Init()
{
	my_scene = SCENE::OVER;
}

/**
* @brief ゲームオーバーシーンの更新
* @return SCENE シーンが変わるなら次のシーンのenum classを返す
*/
SCENE GameOverScene::Update()
{
	auto current_scene = my_scene;

	return current_scene;
}

/**
* @brief ゲームオーバーシーンの描画
*/
void GameOverScene::Render()
{

}

/**
* @brief ゲームオーバーシーンの破棄
*/
void GameOverScene::Destroy()
{

}