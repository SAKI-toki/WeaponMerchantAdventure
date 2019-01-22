/**
* @file game_scene_easy.h
* @brief ゲームシーン(easy)の宣言
* @author 石山　悠
* @date 2018/11/22
*/
#pragma once
#include "../base/game_scene_base.h"
/**
* @brief ゲームシーン(easy)クラス
*/
class GameSceneEasy :public Scene, private GameSceneBase
{
public:
	void Init()final;
	std::shared_ptr<Scene> Update(std::shared_ptr<Scene>&)final;
	void Render()final;
	void Destroy()final;
};