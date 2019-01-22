/**
* @file game_scene_normal.h
* @brief ゲームシーン(normal)の宣言
* @author 石山　悠
* @date 2018/11/20
*/
#pragma once
#include "../base/game_scene_base.h"
/**
* @brief ゲームシーン(normal)クラス
*/
class GameSceneNormal :public Scene, private GameSceneBase
{
public:
	void Init()final;
	std::shared_ptr<Scene> Update(std::shared_ptr<Scene>&)final;
	void Render()final;
	void Destroy()final;
};