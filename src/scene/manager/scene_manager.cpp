/**
* @file scene_manager.cpp
* @brief �V�[���̃}�l�[�W���[�N���X�̃����o�֐����`
* @author �ΎR�@�I
* @date 2018/10/02
*/
#include "scene_manager.h"
#include "../main/title/title_scene.h"
#include "../../input/gamepad/gamepad_input.h"
#include "../../sound/manager/sound_manager.h"
#include <Windows.h>

/**
* @brief �V�[���}�l�[�W���[�̏�����
*/
void SceneManager::Init()
{
	my_scene = SCENE::TITLE;
	scene_ptr = switch_scene(my_scene);
	scene_ptr->Init();
	sound.Init(L"resources/sample.wav", true,true);
}

/**
* @brief �ێ����Ă�V�[���̍X�V
*/
void SceneManager::Update()
{
	SoundManager::GetInstance()->Update();
	if (GamepadInput::GetInstance()->GetButtonDown(BUTTON::A))
	{
		sound()->SetVolume(2);
	}
	if (GamepadInput::GetInstance()->GetButtonDown(BUTTON::B))
	{
		sound()->SetVolume(1);
	}
	if (GamepadInput::GetInstance()->GetButtonDown(BUTTON::X))
	{
		sound()->SetVolume(0.5f);
	}
	GamepadInput::GetInstance()->Update();
	auto next_scene = scene_ptr->Update();
	if (next_scene != my_scene)
	{
		//�V�[���J��
		scene_ptr->Destroy();
		scene_ptr = switch_scene(next_scene);
		scene_ptr->Init();
	}
}

/**
* @brief �ێ����Ă�V�[���̕`��
*/
void SceneManager::Render()
{
	if (GamepadInput::GetInstance()->GetTrigger(true) > 0)
	{
		MessageBox(NULL, L"", L"", MB_OK);
	}
	scene_ptr->Render();
}

/**
* @brief �ێ����Ă�V�[���̃}�l�[�W���[�̔j��
*/
void SceneManager::Destroy()
{
	scene_ptr->Destroy();
	SoundManager::GetInstance()->Destroy();
}

/**
* @brief �����ɂ���ăV�[����؂�ւ���
* @param scene ���̃V�[����enum class
* @return std::unique_ptr<Scene>
*/
std::unique_ptr<Scene> SceneManager::switch_scene(const SCENE scene)const 
{
	switch (scene)
	{
	case SCENE::TITLE:
		return std::make_unique<TitleScene>();
	}
	return nullptr;
}