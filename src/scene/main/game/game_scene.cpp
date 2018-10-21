/**
* @file game_scene.cpp
* @brief ゲームシーンクラスのメンバ関数の定義
* @author 石山　悠
* @date 2018/10/02
*/
#include "game_scene.h"
#include "../../../common/common.h"
#include "../../../rendering/font/font.h"
#include "../../../object/camera/camera.h"
#include "../../../input/gamepad/gamepad_input.h"
/**
* @brief ゲームシーンの初期化
*/
void GameScene::Init()
{
	my_scene = SCENE::GAME;
	//プレイヤーの初期化
	{
		player.Init(std::string("player"), L"monster2.png", 32, 32, { 100,100 });
	}
	//敵の初期化
	{
		enemy.push_front(NormalEnemy());
		std::begin(enemy)->Init(std::string("normalenemy1"), L"monster.png", 32, 32, { 1000,100 });
		enemy.push_front(NormalEnemy());
		std::begin(enemy)->Init(std::string("normalenemy2"), L"monster1.png", 400, 366, { 2100,-100 }, 0, 0.2f);

		f_enemy.push_front(FlyEnemy());
		std::begin(f_enemy)->Init(std::string("normalenemy1"), L"monster.png", 32, 32, { 2000,-500 });
		f_enemy.push_front(FlyEnemy());
		std::begin(f_enemy)->Init(std::string("normalenemy1"), L"monster.png", 32, 32, { 150,-100 });
		f_enemy.push_front(FlyEnemy());
		std::begin(f_enemy)->Init(std::string("normalenemy1"), L"monster.png", 32, 32, { 400,-200 });
	}
	//背景の初期化
	{
		backGround.push_back(StaticObject());
		backGround[0].Init(std::string("background1"), L"background/sample5.jpg", 1920, 1080,
			{ 1920 / 2,1080 / 2 }, 0, 1);
	}
	//マップの初期化
	{
		constexpr int map_width = 80;
		constexpr int map_height = 10;
		//地面
		for (int i = 0; i < 50; ++i)
		{
			field.push_back(MapObject());
			field[field.size() - 1].Init(std::string("field1"), L"map/map1.png", 32, 32, { i * 32.0f,32.0f * map_height });
		}
		for (int i = 60; i < 80; ++i)
		{
			field.push_back(MapObject());
			field[field.size() - 1].Init(std::string("field1"), L"map/map1.png", 32, 32, { i * 32.0f,32.0f * (map_height - 10) });
		}
		//壁
		for (int i = -5; i < map_height; ++i)
		{
			field.push_back(MapObject());
			field[field.size() - 1].Init(std::string("field1"), L"map/map1.png", 32, 32, { 0 * 32.0f,32.0f * i });
		}
		field.push_back(MapObject());
		field[field.size() - 1].Init(std::string("field1"), L"map/map1.png", 32, 32, { 49 * 32.0f,32.0f * (map_height - 1) });
		field.push_back(MapObject());
		field[field.size() - 1].Init(std::string("field1"), L"map/map1.png", 32, 32, { 60 * 32.0f,32.0f * (map_height - 11) });
		field.push_back(MapObject());
		field[field.size() - 1].Init(std::string("field1"), L"map/map1.png", 32, 32, { 60 * 32.0f,32.0f * (map_height - 12) });
		field.push_back(MapObject());
		field[field.size() - 1].Init(std::string("field1"), L"map/map1.png", 32, 32, { 60 * 32.0f,32.0f * (map_height - 13) });
		field.push_back(MapObject());
		field[field.size() - 1].Init(std::string("field1"), L"map/map1.png", 32, 32, { 79 * 32.0f,32.0f * (map_height - 11) });

		for (int i = 0; i < 3; ++i)
		{
			field.push_back(MapObject());
			field[field.size() - 1].Init(std::string("field1"), L"map/map1.png", 32, 32, { (30 + i) * 32.0f,32.0f * 5 });
			field.push_back(MapObject());
			field[field.size() - 1].Init(std::string("field1"), L"map/map1.png", 32, 32, { (35 + i) * 32.0f,32.0f * 0 });
			field.push_back(MapObject());
			field[field.size() - 1].Init(std::string("field1"), L"map/map1.png", 32, 32, { (40 + i) * 32.0f,32.0f * -5 });
			field.push_back(MapObject());
			field[field.size() - 1].Init(std::string("field1"), L"map/map1.png", 32, 32, { (45 + i) * 32.0f,32.0f * -10 });
		}
	}
	//プレイヤーを追尾する
	Camera::GetInstance()->SetTarget(&player);
}

/**
* @brief ゲームシーンの更新
* @return SCENE シーンが変わるなら次のシーンのenum classを返す
*/
SCENE GameScene::Update()
{
	auto current_scene = my_scene;
	if ((enemy.size() <= 0 && f_enemy.size() <= 0) || player.transform.pos.y >= 500 || !player.enabled)
	{
		current_scene = SCENE::TITLE;
	}
	else
	{
		auto enemy_itr = std::begin(enemy);
		while (enemy_itr != std::end(enemy))
		{
			enemy_itr->Update();
			if (!enemy_itr->enabled)
			{
				enemy_itr = enemy.erase(enemy_itr);
			}
			else
			{
				++enemy_itr;
			}
		}

		auto f_enemy_itr = std::begin(f_enemy);
		while (f_enemy_itr != std::end(f_enemy))
		{
			f_enemy_itr->Update();
			if (!f_enemy_itr->enabled)
			{
				f_enemy_itr = f_enemy.erase(f_enemy_itr);
			}
			else
			{
				++f_enemy_itr;
			}
		}

		player.Update();

		for (auto&& f : field)
		{
			f.Update();
		}
	}
	return current_scene;
}

/**
* @brief ゲームシーンの描画
*/
void GameScene::Render()
{
	for (auto&& back : backGround)
	{
		back.Render(false);
	}
	for (auto&& f : field)
	{
		f.Render();
	}
	for (auto&& e : enemy)
	{
		e.Render();
	}
	for (auto&& f : f_enemy)
	{
		f.Render();
	}
	player.Render();
}

/**
* @brief ゲームシーンの破棄
*/
void GameScene::Destroy()
{
	for (auto&& back : backGround)
	{
		back.Destroy();
	}
	for (auto&& f : field)
	{
		f.Destroy();
	}
	for (auto&& e : enemy)
	{
		e.Destroy();
	}
	for (auto&& f : f_enemy)
	{
		f.Destroy();
	}
	player.Destroy();

}