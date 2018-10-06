/**
* @file title_scene.cpp
* @brief タイトルシーンクラスのメンバ関数の定義
* @author 石山　悠
* @date 2018/10/02
*/
#include "title_scene.h"
#include "../../../common/common.h"
/**
* @brief タイトルシーンの初期化
*/
void TitleScene::Init()
{
	my_scene = SCENE::TITLE;
	player.Init(L"resources/texture/sample3.png", 100, 200, { 500,500 });
}

/**
* @brief タイトルシーンの更新
* @return SCENE シーンが変わるなら次のシーンのenum classを返す
*/
SCENE TitleScene::Update()
{
	auto current_scene = my_scene;
	player.Update();
	player.transform.rot += PI<float> * 2 / 100;
	return current_scene;
}

/**
* @brief タイトルシーンの描画
*/
void TitleScene::Render()
{
	player.Render();
}

/**
* @brief タイトルシーンの破棄
*/
void TitleScene::Destroy()
{

}