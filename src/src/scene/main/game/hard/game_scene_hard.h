/**
* @file game_scene_hard.h
* @brief �Q�[���V�[��(hard)�̐錾
* @author �ΎR�@�I
* @date 2018/11/20
*/
#pragma once
#include "../base/game_scene_base.h"
/**
* @brief �Q�[���V�[��(hard)�N���X
*/
class GameSceneHard :public Scene,private GameSceneBase
{
public:
	void Init()final;
	std::shared_ptr<Scene> Update(std::shared_ptr<Scene>&)final;
	void Render()final;
	void Destroy()final;
};