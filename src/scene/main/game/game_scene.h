/**
* @file game_scene.h
* @brief ゲームシーンの宣言
* @author 石山　悠
* @date 2018/10/18
*/
#pragma once
#include "../../scene.h"
#include "../../../object/base/static/static_object.h"
#include "../../../object/map/map.h"
#include "../../../object/character/player/player.h"
#include "../../../object/character/enemy/normal/normal_enemy.h"
#include "../../../object/character/enemy/fly/fly_enemy.h"
#include <list>
/**
* @brief ゲームシーンクラス
*/
class GameScene :public Scene
{
	std::list<NormalEnemy> enemy;
	std::list<FlyEnemy> f_enemy;
	Player player;
	std::vector<StaticObject> backGround;
	std::vector<MapObject> field;
public:
	void Init()final;
	SCENE Update()final;
	void Render()final;
	void Destroy()final;
};