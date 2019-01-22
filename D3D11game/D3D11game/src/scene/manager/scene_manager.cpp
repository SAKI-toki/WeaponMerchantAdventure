/**
* @file scene_manager.cpp
* @brief �V�[���̃}�l�[�W���[�N���X�̃����o�֐����`
* @author �ΎR�@�I
* @date 2018/11/20
*/
#include "scene_manager.h"
#include "../main/title/title_scene.h"
#include "../../input/gamepad/gamepad_input.h"
#include "../../input/keyboard/keyboard_input.h"
#include "../../sound/manager/sound_manager.h"
//#include "../../rendering/sprite/manager/sprite_manager.h"
#include "../../collider/manager/collider_manager.h"
#include "../../camera/camera.h"
#include "../fade/fade.h"
#include "../../object/ui/manager/ui_manager.h"
#include "../main/game/over/game_over.h"
#include "../pause/pause_scene.h"
#include "../../effect/manager/effect_manager.h"
#include "../../device/device.h"
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
	//SpriteManager::getinstance()->Init();
	Fade::getinstance()->Init();
	GameOver::getinstance()->Init();
	PauseScene::getinstance()->Init();
	//�^�C�g������X�^�[�g
#ifndef _DEBUG
	scene_ptr = std::make_shared<TitleScene>();
#else //�f�o�b�O�p�ɂǂ��̃V�[������ł��X�^�[�g�ł���
	scene_ptr = std::make_shared<TitleScene>();
#endif
	scene_ptr->Init();
}

/**
* @brief �ێ����Ă�V�[���̍X�V
*/
void SceneManager::Update()
{
	//�T�E���h�̍X�V
	//SoundManager::getinstance()->Update();
	//�G�t�F�N�g�̍X�V
	EffectManager::getinstance()->Update();
	//�t�F�[�h���Ă��Ȃ��Ƃ��̓V�[�����X�V����
	if (!is_current_fade)
	{
		if (is_game_scene && !GameOver::getinstance()->game_over_flg && !PauseScene::getinstance()->is_pause&&
			GamepadInput::getinstance()->GetButtonDown(0,BUTTON::START))
		{
			PauseScene::getinstance()->SwitchPause();
		}
		else
		{
			if (PauseScene::getinstance()->is_pause)
			{
				next_scene_ptr = PauseScene::getinstance()->Update(scene_ptr);
			}
			else
			{
				//�V�[�����X�V���A�ق��̃V�[�����Ԃ��Ă�����V�[���J�ڂ���/*�����ł̓V�[���J�ڂ͂��Ă��Ȃ�*/
				next_scene_ptr = scene_ptr->Update(scene_ptr);
			}
			if (continue_scene || next_scene_ptr != scene_ptr)
			{
				//�t�F�[�h���J�n����
				is_current_fade = true;
				//�Q�[���p�b�h�̃o�C�u���[�V�����̃��Z�b�g
				GamepadInput::getinstance()->Vibration(0, 0, 0);
			}
			//�����蔻��̃`�F�b�N
			ColliderManager::getinstance()->CheckCollision();
			//�J�����̍X�V
			Camera::getinstance()->update();
		}
	}
	//�t�F�[�h�C���A�E�g
	else
	{
		if (!is_fade_in)
		{
			scene_ptr->ExitFadeUpdate();
			//�����蔻��̃`�F�b�N
			ColliderManager::getinstance()->CheckCollision();
			//�J�����̍X�V
			Camera::getinstance()->update();
		}
		//�t�F�[�h���X�V���A�C�����A�E�g���I�������true���Ԃ�
		if (Fade::getinstance()->Update(is_fade_in))
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
				ColliderManager::getinstance()->Reset();
				//�G�t�F�N�g�̔j��
				EffectManager::getinstance()->Clear();
				//UI�̔j��
				UiManager::getinstance()->Destroy();
				//�|�[�Y�̏I��
				PauseScene::getinstance()->EndPause();
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
				Camera::getinstance()->update();
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
	Device::getinstance()->draw_begin();
	Sprite::depth = 9999;
	//�V�[���̕`��
	scene_ptr->Render();
	//�G�t�F�N�g�̕`��
	EffectManager::getinstance()->Render();
	//UI�̕`��
	UiManager::getinstance()->Render();
	if (GameOver::getinstance()->game_over_flg)
	{
		//�Q�[���I�[�o�[�V�[���̕`��
		GameOver::getinstance()->Render();
	}
	else if (PauseScene::getinstance()->is_pause)
	{
		PauseScene::getinstance()->Render();
	}
	//�����V�[���J�ڒ��Ȃ�
	if (is_current_fade)Fade::getinstance()->Render();
	Device::getinstance()->draw_end();
}

/**
* @brief �ێ����Ă�V�[���̃}�l�[�W���[�̔j��
*/
void SceneManager::Destroy()
{
	scene_ptr->Destroy();
	Fade::getinstance()->Destroy();
	SoundManager::getinstance()->destroy();
	PauseScene::getinstance()->Destroy();
}
