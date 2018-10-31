/**
* @file select_scene.cpp
* @brief セレクトシーンクラスのメンバ関数を定義
* @author 石山　悠
* @date 2018/10/19
*/
#include "select_scene.h"

/**
* @brief セレクトシーンの初期化
*/
void SelectScene::Init()
{
	my_scene = SCENE::SELECT;
}

/**
* @brief セレクトシーンの更新
* @return SCENE シーンが変わるなら次のシーンのenum classを返す
*/
SCENE SelectScene::Update()
{
	auto current_scene = my_scene;

	return current_scene;
}

/**
* @brief セレクトシーンの描画
*/
void SelectScene::Render()
{

}

/**
* @brief セレクトシーンの破棄
*/
void SelectScene::Destroy()
{

}