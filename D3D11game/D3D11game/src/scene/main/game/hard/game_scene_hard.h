/**
* @file game_scene_hard.h
* @brief ゲームシーン(hard)の宣言
* @author 石山　悠
* @date 2018/11/20
*/
#pragma once
#include "../base/game_scene_base.h"
/**
* @brief ゲームシーン(hard)クラス
*/
class GameSceneHard :public Scene,private GameSceneBase
{
public:
	void Init()final;
	std::shared_ptr<Scene> Update(std::shared_ptr<Scene>&)final;
	void Render()final;
	void Destroy()final;
};