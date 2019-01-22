/**
* @file fade.h
* @brief �t�F�[�h�N���X�̐錾
* @author �ΎR�@�I
* @date 2018/10/30
*/
#pragma once
#include "../../common/common.h"
#include "../../sprite/sprite.h"
#include <saki/singleton/singleton.h>



/**
* @brief �t�F�[�h�N���X
*/
class Fade :public saki::Singleton<Fade>
{
	//�A���t�@�l
	float alpha = 0.0f;
	//���̃e�N�X�`��
	Sprite black;
	Transform transform;
public:
	void Init();
	bool Update(const bool);
	void Render();
	void Destroy();
};