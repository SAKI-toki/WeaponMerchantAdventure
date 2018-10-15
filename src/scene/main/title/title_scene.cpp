/**
* @file title_scene.cpp
* @brief タイトルシーンクラスのメンバ関数の定義
* @author 石山　悠
* @date 2018/10/02
*/
#include "title_scene.h"
#include "../../../common/common.h"
#include "../../../rendering/font/font.h"
#include "../../../object/camera/camera.h"
#include "../../../input/gamepad/gamepad_input.h"
/**
* @brief タイトルシーンの初期化
*/
void TitleScene::Init()
{
	my_scene = SCENE::TITLE;
	enemy.Init(std::string("normalenemy"), L"sample1.png", 100, 100, { 500,0 });
	player.Init(std::string("player"), L"sample3.png", 100, 200, { 100,-50 });
	backGround.push_back(StaticObject());
	backGround[0].Init(std::string("background1"), L"background/sample3.png", 1920, 1080,
		{ 1920 / 2,1080 / 2 }, 0, 1);
	field.emplace_back(MapObject());
	field[0].Init(std::string("field1"), L"background/sample3.png", 1920, 1080,{ 0,1000 });
	Camera::GetInstance()->SetTarget(&player);
}

/**
* @brief タイトルシーンの更新
* @return SCENE シーンが変わるなら次のシーンのenum classを返す
*/
SCENE TitleScene::Update()
{
	auto current_scene = my_scene;
	static constexpr float speed = 3;
	if (GamepadInput::GetInstance()->GetStick(false, true) > 0)
	{
		player.transform.pos += VEC2(speed, 0);
	}
	if (GamepadInput::GetInstance()->GetStick(false, true) < 0)
	{
		player.transform.pos += VEC2(-speed, 0);
	}
	if (GamepadInput::GetInstance()->GetStick(false, false) > 0)
	{
		player.transform.pos += VEC2(0, -speed);
	}
	if (GamepadInput::GetInstance()->GetStick(false, false) < 0)
	{
		player.transform.pos += VEC2(0, speed);
	}
	enemy.Update();
	player.Update();
	for (auto&& f : field)
	{
		f.Update();
	}
	return current_scene;
}

/**
* @brief タイトルシーンの描画
*/
void TitleScene::Render()
{
	for (auto&& back : backGround)
	{
		back.Render();
	}
	for (auto&& f : field)
	{
		f.Render();
	}
	enemy.Render();
	player.Render();
}

/**
* @brief タイトルシーンの破棄
*/
void TitleScene::Destroy()
{
	for (auto&& back : backGround)
	{
		back.Destroy();
	}
	for (auto&& f : field)
	{
		f.Destroy();
	}
	enemy.Destroy();
	player.Destroy();
}