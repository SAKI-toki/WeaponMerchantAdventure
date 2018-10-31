/**
* @file game_clear.cpp
* @brief ゲームクリアクラスのメンバ関数を定義
* @author 石山　悠
* @date 2018/10/29
*/
#include "game_clear.h"

/**
* @brief ゲームクリアシーンの初期化
*/
void GameClearScene::Init()
{
	my_scene = SCENE::CLEAR;
}

/**
* @brief ゲームクリアシーンの更新
* @return SCENE シーンが変わるなら次のシーンのenum classを返す
*/
SCENE GameClearScene::Update()
{
	auto current_scene = my_scene;

	return current_scene;
}

/**
* @brief ゲームクリアシーンの描画
*/
void GameClearScene::Render()
{

}

/**
* @brief ゲームクリアシーンの破棄
*/
void GameClearScene::Destroy()
{

}