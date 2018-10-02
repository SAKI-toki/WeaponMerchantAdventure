/**
* @file title_scene.cpp
* @brief タイトルシーンクラスのメンバ関数の定義
* @author 石山　悠
* @date 2018/10/02
*/
#include "title_scene.h"

/**
* @brief タイトルシーンの初期化
*/
void TitleScene::Init()
{
	my_scene = SCENE::TITLE;
}

/**
* @brief タイトルシーンの更新
* @return SCENE シーンが変わるなら次のシーンのenum classを返す
*/
SCENE TitleScene::Update()
{
	auto current_scene = my_scene;

	return current_scene;
}

/**
* @brief タイトルシーンの描画
*/
void TitleScene::Render()
{

}

/**
* @brief タイトルシーンの破棄
*/
void TitleScene::Destroy()
{

}