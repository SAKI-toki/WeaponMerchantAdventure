/**
* @file game_clear.h
* @brief �Q�[���N���A�N���X�̐錾
* @author �ΎR�@�I
* @date 2018/10/29
*/
#pragma once
#include "../../scene.h"
/**
* @brief �Q�[���N���A�N���X
*/
class GameClearScene :public Scene
{
public:
	void Init()final;
	SCENE Update()final;
	void Render()final;
	void Destroy()final;
};