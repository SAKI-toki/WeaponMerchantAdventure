/**
* @file title_scene.cpp
* @brief タイトルシーンクラスのメンバ関数の定義
* @author 石山　悠
* @date 2018/11/30
*/
#include "title_scene.h"
#include "../../../common/common.h"
#include "../../../camera/camera.h"
#include "../../../input/gamepad/gamepad_input.h"
#include "../../../sound/bgm/bgm.h"
#include "../../../collider/manager/collider_manager.h"
#include "../../../load/map/load_map.h"
#include "../select/select_scene.h"
#include <saki/pi.h>
#include "../../../object/select/select_object.h"
/**
* @brief タイトルシーンの初期化
*/
void TitleScene::Init()
{
	std::vector<SelectObj> temp;
	StaticObject temp_m;
	ColliderManager::getinstance()->SetTarget(nullptr);
	Camera::getinstance()->SetTarget(nullptr);
	Sprite::has_target = false;
	Camera::getinstance()->SetPos(Vec3{ WINDOW_WIDTH/2,0,0 });
	BGM::getinstance()->ChangeBgm(std::string("title_bgm"), L"BGM/title.wav");
	//解説
	{
		down_stick.Init("down_stick", L"operation/stick.png", Vec2(139, 152));
		frame.Init("frame", L"operation/frame.png", Vec2(599, 442));
		frame_transform.set_pos({ 300,0,799 });
		frame_transform.set_scale({ operation_scale,operation_scale,1 });
		stick_transform.set_pos({ 300.0f + 140.0f * operation_scale * 0.5f,100.0f * operation_scale * 0.5f ,798 });
		stick_transform.set_scale({ operation_scale,operation_scale,1 });
		operation_player.Init(("player"), L"WizardWalkRight.png", Vec2(86, 128));
		operation_player_transform.set_pos({ 300.0f - 400.0f * operation_scale * 0.5f,-250.0f * operation_scale * 0.5f ,797 });
		operation_player_transform.set_scale({ operation_scale,operation_scale,1 });
		operation_size = { 86,128 };
		operation_anim.Init(operation_size, 6, 8, 0);
		operation_anim.ChangeAnimation(7, 10);
		operation_player.slice_num = Vec2(6, 8);
	}
	//プレイヤー
	{
		player = std::make_unique<Player>();
	}
	//テクスチャ
	{
		background.Init("title_background", L"background/title_background.jpg", Vec2(1280, 640));
		finger_arrow.Init("finger_arrow", L"finger_arrow.png", Vec2(300, 237));
	}
	LoadMap::getinstance()->TitleSelectLoadingMap(L"title_map.csv");
	LoadMap::getinstance()->TitleSelectMakingMap(map, player, temp, temp_m);
}

/**
* @brief タイトルシーンの更新
* @return std::shared_ptr<Scene> シーンが変わるなら次のシーンのstd::shared_ptr<Scene>を返す
*/
std::shared_ptr<Scene> TitleScene::Update(std::shared_ptr<Scene>& scene)
{
	auto current_scene = scene;
	if (!player->enabled)
	{
		current_scene = std::make_shared<SelectScene>();
	}
	player->Update();
	//マップの更新
	for (auto&& m : map)
	{
		m.Update();
	}
	//指の更新
	if (++finger_time > 60)
	{
		finger_time = 0;
	}
	//スティックの更新
	if (++stick_time > 300)
	{
		stick_time = 0;
		auto rot = stick_transform.get_rot();
		auto pos = stick_transform.get_pos();
		if (rot.y == 0)
		{
			rot.y = saki::PI<float>;
			pos.x -= 140.0f * operation_scale;
			operation_anim.ChangeAnimation(3, 10);
			player_right = true;
		}
		else
		{
			rot.y = 0;
			pos.x += 140.0f * operation_scale;
			operation_anim.ChangeAnimation(7, 10);
			player_right = false;
		}
		stick_transform.set_rot(rot);
		stick_transform.set_pos(pos);
	}
	operation_player_transform.move({ (player_right) ? -0.7f : 0.7f , 0, 0 });
	operation_anim.Update();
	return current_scene;
}

/**
* @brief タイトルシーンの描画
*/
void TitleScene::Render()
{
	background.Render(Transform({ WINDOW_WIDTH / 2, 0,9000 },
		{ 0,0,0 }, { 1.8f,1.8f,1 }));
	for (auto&& m : map)
	{
		m.Render();
	}
	finger_arrow.Render(Transform({ WINDOW_WIDTH / 2, -finger_time * 1.5f,800 }
	, { 0,0,-saki::PI<float> / 2.0f }, saki::vector3_one<float>));
	frame.Render(frame_transform);
	down_stick.Render(stick_transform, true);
	operation_player.current_slice = operation_anim.GetAnimation();
		operation_player.Render(operation_player_transform, true);
	player->Render();
	player->UiRender();
}

/**
* @brief タイトルシーンの破棄
*/
void TitleScene::Destroy()
{
	for (auto&& m : map)
	{
		m.Destroy();
	}
	player->Destroy();
}