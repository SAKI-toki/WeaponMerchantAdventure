/**
* @file game_scene_easy.h
* @brief �Q�[���V�[��(easy)�̐錾
* @author �ΎR�@�I
* @date 2018/11/22
*/
#pragma once
#include "../base/game_scene_base.h"
/**
* @brief �Q�[���V�[��(easy)�N���X
*/
class GameSceneEasy :public Scene, private GameSceneBase
{
public:
	void Init()final;
	std::shared_ptr<Scene> Update(std::shared_ptr<Scene>&)final;
	void Render()final;
	void Destroy()final;
};