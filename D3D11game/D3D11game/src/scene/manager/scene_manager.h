/**
* @file scene_manager.h
* @brief �V�[���̃}�l�[�W���[�N���X�̐錾
* @author �ΎR�@�I
* @date 2018/10/02
*/
#pragma once
#include "../base/scene_base.h"
#include "../scene.h"
#include <saki/singleton/singleton.h>
#include <memory>
/**
* @brief �V�[�����}�l�[�W���[����N���X
*/
class SceneManager :public SceneBase, public saki::Singleton<SceneManager>
{
	bool continue_scene = false;
	std::shared_ptr<Scene> next_continue_scene_ptr;
	//�V�[��
	std::shared_ptr<Scene> scene_ptr;
	std::shared_ptr<Scene> next_scene_ptr;
	//�t�F�[�h�����ǂ���
	bool is_current_fade = false;
	//�t�F�[�h�C�����ǂ���
	bool is_fade_in = false;
public:
	bool is_game_scene = false;
	void Init()final;
	void Update();
	void Render()final;
	void Destroy()final;
	
	void ContinueGame(std::shared_ptr<Scene>& p)
	{
		continue_scene = true;
		next_continue_scene_ptr = p;
	}
};