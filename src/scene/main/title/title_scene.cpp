/**
* @file title_scene.cpp
* @brief タイトルシーンクラスのメンバ関数の定義
* @author 石山　悠
* @date 2018/10/16
*/
#include "title_scene.h"
#include "../../../common/common.h"
#include "../../../object/camera/camera.h"
#include "../../../input/gamepad/gamepad_input.h"
/**
* @brief タイトルシーンの初期化
*/
void TitleScene::Init()
{
	my_scene = SCENE::TITLE;
	font.Init(L"XとYを同時押しで始まるよ");
}

/**
* @brief タイトルシーンの更新
* @return SCENE シーンが変わるなら次のシーンのenum classを返す
*/
SCENE TitleScene::Update()
{
	auto current_scene = my_scene;
	if (GamepadInput::GetInstance()->GetButton(BUTTON::X) &&
		GamepadInput::GetInstance()->GetButton(BUTTON::Y))
	{
		current_scene = SCENE::GAME;
	}
	font.SetTransform(Transform(VEC2(100, 400), 0, 9));
	return current_scene;
}

/**
* @brief タイトルシーンの描画
*/
void TitleScene::Render()
{
	font.Render();
}

/**
* @brief タイトルシーンの破棄
*/
void TitleScene::Destroy()
{

}