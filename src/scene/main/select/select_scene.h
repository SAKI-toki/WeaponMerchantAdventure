/**
* @file select_scene.h
* @brief �Z���N�g�V�[���N���X�̐錾
* @author �ΎR�@�I
* @date 2018/10/19
*/
#pragma once
#include "../../scene.h"
/**
* @brief �Z���N�g�V�[���N���X
*/
class SelectScene :public Scene
{
public:
	void Init()final;
	SCENE Update()final;
	void Render()final;
	void Destroy()final;
};