/**
* @file game_scene.h
* @brief ゲームシーンの宣言
* @author 石山　悠
* @date 2018/10/18
*/
#pragma once
#include "../../../scene.h"
#include "../../../../object/base/static/static_object.h"
#include "../../../../object/map/map.h"
#include "../../../../object/character/player/player.h"
#include "../../../../object/character/enemy/normal/normal_enemy.h"
#include "../../../../object/character/enemy/fly/fly_enemy.h"
#include "../../../../object/character/enemy/boss/boss.h"
#include <list>
#include <vector>
/**
* @brief ゲームシーンクラス
*/
class GameSceneEasy :public Scene
{
	bool clear_jump = false;
	enum class GAME { MAIN, TRANSLATION, BOSS, CLEAR, NONE };
	GAME current_game = GAME::MAIN;
	std::list<NormalEnemy> enemy;
	std::list<FlyEnemy> f_enemy;
	std::unique_ptr<Player> player;
	std::unique_ptr<Boss> boss;
	std::vector<StaticObject> backGround;
	std::vector<MapObject> field;
	float boss_center_x;
public:
	void Init()final;
	std::shared_ptr<Scene> Update(std::shared_ptr<Scene>&)final;
	void Render()final;
	void Destroy()final;
};