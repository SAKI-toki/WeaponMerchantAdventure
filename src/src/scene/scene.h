/**
* @file scene.h
* @brief �}�l�[�W���[���܂܂Ȃ��V�[���̃X�[�p�[�N���X��錾
* @author �ΎR�@�I
* @date 2018/10/02
*/
#pragma once
#include "base/scene_base.h"
#include <memory>
/**
* @brief �}�l�[�W���[���܂܂Ȃ��V�[���̃X�[�p�[�N���X
* @details �}�l�[�W���[�͂��̃N���X��ێ�����
*/
class Scene :public SceneBase
{
public:
	virtual ~Scene() {}
	virtual std::shared_ptr<Scene> Update(std::shared_ptr<Scene>&) = 0;
	/**
	* @brief �V�[�����ς��Ƃ��̍X�V
	*/
	virtual void ExitFadeUpdate() {};
};