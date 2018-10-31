/**
* @file scene_manager.h
* @brief �V�[���̃}�l�[�W���[�N���X�̐錾
* @author �ΎR�@�I
* @date 2018/10/02
*/
#pragma once
#include "../base/scene_base.h"
#include "../scene.h"
#include "../../common/singleton.h"
#include <memory>
/**
* @brief �V�[�����}�l�[�W���[����N���X
*/
class SceneManager :public SceneBase, public Singleton<SceneManager>
{
	//�V�[��
	std::unique_ptr<Scene> scene_ptr;
	//�V�[���J��
	std::unique_ptr<Scene> switch_scene(const SCENE)const;
	//�t�F�[�h�����ǂ���
	bool is_current_fade = false;
	//�t�F�[�h�C�����ǂ���
	bool is_fade_in = false;
public:
	void Init()final;
	void Update();
	void Render()final;
	void Destroy()final;
};