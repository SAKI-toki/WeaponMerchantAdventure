/**
* @file title_scene.h
* @brief �^�C�g���V�[���N���X�̐錾
* @author �ΎR�@�I
* @date 2018/10/02
*/
#pragma once
#include "../../scene.h"
/**
* @brief �^�C�g���V�[���N���X
*/
class TitleScene :public Scene
{
public:
	void Init()final;
	SCENE Update()final;
	void Render()final;
	void Destroy()final;
};