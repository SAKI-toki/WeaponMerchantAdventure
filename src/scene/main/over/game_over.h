/**
* @file game_over.h
* @brief �Q�[���I�[�o�[�N���X�̐錾
* @author �ΎR�@�I
* @date 2018/10/29
*/
#pragma once
#include "../../scene.h"
class GameOverScene :public Scene
{
public:
	void Init()final;
	SCENE Update()final;
	void Render()final;
	void Destroy()final;
};