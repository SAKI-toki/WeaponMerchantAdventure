/**
* @file game_scene_base.h
* @brief ゲームシーンのスーパークラスの宣言
* @author 石山　悠
* @date 2018/11/26
*/
#pragma once
#include "../../../scene.h"
#include "../../../../object/base/static/static_object.h"
#include "../../../../object/map/map.h"
#include "../../../../object/character/player/player.h"
#include "../../../../object/character/enemy/normal/normal_enemy.h"
#include "../../../../object/character/enemy/fly/fly_enemy.h"
#include "../../../../object/character/enemy/boss/boss.h"
#include "../../../../object/item/bullet/bullet_item.h"
#include <list>
#include <vector>

/**
* @brief ゲームシーンのスーパークラス
*/
class GameSceneBase
{
private:
	float camera_prev_x = 0.0f;
public:
	//クリアのジャンプが終わったかどうか
	bool clear_jump = false;
	//ゲームの場面の列挙（ステートマシンにしようとしたが、共通のリソースを使用するためswitchに）
	enum class GAME { MAIN, TRANSLATION, BOSS, CLEAR, NONE };
	//今どの場面か格納する
	GAME current_game = GAME::MAIN;
	//飛ばない敵
	std::list<NormalEnemy> enemy;
	//飛ぶ敵
	std::list<FlyEnemy> f_enemy;
	//プレイヤー
	std::unique_ptr<Player> player;
	//ボス
	std::unique_ptr<Boss> boss;
	//背景
	std::vector<StaticObject> backGround;
	//マップ
	std::vector<MapObject> field;
	//アイテム
	std::list<BulletItem> bullet_item;
	//ボスと戦闘するときの中央位置＆カメラ位置
	float boss_center_x;
	//ゲームの初期化
	void GameInit();
	//ゲームの更新
	std::shared_ptr<Scene> GameUpdate(std::shared_ptr<Scene>&);
	//ゲームの描画
	void GameRender();
	//ゲームの破棄
	void GameDestroy();
};