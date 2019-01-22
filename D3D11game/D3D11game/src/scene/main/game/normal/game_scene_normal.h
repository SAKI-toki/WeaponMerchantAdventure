/**
* @file game_scene_normal.h
* @brief �Q�[���V�[��(normal)�̐錾
* @author �ΎR�@�I
* @date 2018/11/20
*/
#pragma once
#include "../base/game_scene_base.h"
/**
* @brief �Q�[���V�[��(normal)�N���X
*/
class GameSceneNormal :public Scene, private GameSceneBase
{
public:
	void Init()final;
	std::shared_ptr<Scene> Update(std::shared_ptr<Scene>&)final;
	void Render()final;
	void Destroy()final;
};