/**
* @file title_scene.h
* @brief タイトルシーンクラスの宣言
* @author 石山　悠
* @date 2018/10/02
*/
#pragma once
#include "../../scene.h"
#include "../../../object/base/static/static_object.h"
#include "../../../object/map/map.h"
#include "../../../object/character/player/player.h"
#include "../../../object/character/enemy/normal/normal_enemy.h"

/**
* @brief タイトルシーンクラス
*/
class TitleScene :public Scene
{
	NormalEnemy enemy;
	Player player;
	std::vector<StaticObject> backGround;
	std::vector<MapObject> field;
public:
	void Init()final;
	SCENE Update()final;
	void Render()final;
	void Destroy()final;
};