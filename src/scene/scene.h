/**
* @file scene.h
* @brief �}�l�[�W���[���܂܂Ȃ��V�[���̃X�[�p�[�N���X��錾
* @author �ΎR�@�I
* @date 2018/10/02
*/
#pragma once
#include "base/scene_base.h"
/**
* @brief �}�l�[�W���[���܂܂Ȃ��V�[���̃X�[�p�[�N���X
* @details �}�l�[�W���[�͂��̃N���X��ێ�����
*/
class Scene :public SceneBase
{
public:
	virtual ~Scene() {}
	virtual SCENE Update() = 0;
};