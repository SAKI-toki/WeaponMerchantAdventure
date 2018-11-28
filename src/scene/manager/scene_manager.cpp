/**
* @file scene_manager.cpp
* @brief �V�[���̃}�l�[�W���[�N���X�̃����o�֐����`
* @author �ΎR�@�I
* @date 2018/11/20
*/
#include "scene_manager.h"
#include "../main/title/title_scene.h"
#include "../../input/gamepad/gamepad_input.h"
#include "../../sound/manager/sound_manager.h"
#include "../../rendering/sprite/manager/sprite_manager.h"
#include "../../collider/manager/collider_manager.h"
#include "../../object/camera/camera.h"
#include "../fade/fade.h"
#include "../../object/ui/manager/ui_manager.h"
#include "../main/game/over/game_over.h"
#ifdef _DEBUG
#include "../main/select/select_scene.h"
#include "../main/game/easy/game_scene_easy.h"
#include "../main/game/normal/game_scene_normal.h"
#include "../main/game/hard/game_scene_hard.h"
#endif


/**
* @brief �V�[���}�l�[�W���[�̏�����
*/
void SceneManager::Init()
{
	SpriteManager::GetInstance()->Init();
	Fade::GetInstance()->Init();
	GameOver::getinstance()->Init();
	//�^�C�g������X�^�[�g
#ifndef _DEBUG
	scene_ptr = std::make_shared<TitleScene>();
#else //�f�o�b�O�p�ɂǂ��̃V�[������ł��X�^�[�g�ł���
	scene_ptr = std::make_shared<GameSceneNormal>();
#endif
	scene_ptr->Init();
}

/**
* @brief �ێ����Ă�V�[���̍X�V
*/
void SceneManager::Update()
{
	//�T�E���h�̍X�V
	SoundManager::GetInstance()->Update();
	//�t�F�[�h���Ă��Ȃ��Ƃ��̓V�[�����X�V����
	if (!is_current_fade)
	{
		//�Q�[���p�b�h�̍X�V
		GamepadInput::GetInstance()->Update();
		//�V�[�����X�V���A�ق��̃V�[�����Ԃ��Ă�����V�[���J�ڂ���/*�����ł̓V�[���J�ڂ͂��Ă��Ȃ�*/
		next_scene_ptr = scene_ptr->Update(scene_ptr);
		if (continue_scene || next_scene_ptr != scene_ptr)
		{
			//�t�F�[�h���J�n����
			is_current_fade = true;
			//�Q�[���p�b�h�̃o�C�u���[�V�����̃��Z�b�g
			GamepadInput::GetInstance()->Vibration(0, 0);
		}
		//�����蔻��̃`�F�b�N
		ColliderManager::GetInstance()->CheckCollision();
		//�J�����̍X�V
		Camera::GetInstance()->Update();
	}
	//�t�F�[�h�C���A�E�g
	else
	{
		//�t�F�[�h���X�V���A�C�����A�E�g���I�������true���Ԃ�
		if (Fade::GetInstance()->Update(is_fade_in))
		{
			//�t�F�[�h�C�����I�������t�F�[�h���I��点��
			if (is_fade_in)
			{
				is_current_fade = false;
			}
			else
			{
				//�V�[���̔j��
				scene_ptr->Destroy();
				//�R���C�_�̃��Z�b�g
				ColliderManager::GetInstance()->Reset();
				//UI�̔j��
				UiManager::getinstance()->Destroy();
				//�V�[���̑J��
				if (continue_scene)
				{
					next_scene_ptr = next_continue_scene_ptr;
					continue_scene = false;
				}
				scene_ptr = next_scene_ptr;
				//�V�[���̏�����
				scene_ptr->Init();
				//�J�����̍X�V�������ň�񂵂Ȃ��ƕςȂƂ���ɃJ�����������Ă��܂�
				Camera::GetInstance()->Update();
			}
			//�t�F�[�h�C�����I������玟�̓t�F�[�h�A�E�g�A�t���R��
			is_fade_in = !is_fade_in;
		}
	}
}

/**
* @brief �ێ����Ă�V�[���̕`��
*/
void SceneManager::Render()
{
	//�V�[���̕`��
	scene_ptr->Render();
	//UI�̕`��
	UiManager::getinstance()->Render();
	//�Q�[���I�[�o�[�V�[���̕`��
	GameOver::getinstance()->Render();
	//�����V�[���J�ڒ��Ȃ�
	if (is_current_fade)Fade::GetInstance()->Render();
}

/**
* @brief �ێ����Ă�V�[���̃}�l�[�W���[�̔j��
*/
void SceneManager::Destroy()
{
	scene_ptr->Destroy();
	Fade::GetInstance()->Destroy();
	SoundManager::GetInstance()->Destroy();
}
