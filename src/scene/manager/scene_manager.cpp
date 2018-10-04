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
#include "../../rendering/sprite/manager/sprite_manager.h"

#include "../../transform/transform.h"

#include <tchar.h>
/**
* @brief �V�[���}�l�[�W���[�̏�����
*/
void SceneManager::Init()
{
	SpriteManager::GetInstance()->Init();
	my_scene = SCENE::TITLE;
	scene_ptr = switch_scene(my_scene);
	scene_ptr->Init();
	sound[0].Init(L"resources/audio/sample1.wav", true, true);
	sound[1].Init(L"resources/audio/sample2.wav", true, true);
	sprite[0].Init(L"resources/texture/sample1.png", 100, 100);
	sprite[1].Init(L"resources/texture/sample2.png", 32, 32);
}

/**
* @brief �ێ����Ă�V�[���̍X�V
*/
void SceneManager::Update()
{
	SoundManager::GetInstance()->Update();
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
	SpriteManager::GetInstance()->Start();
	scene_ptr->Render();
	Transform tt;
	sprite[0].Render(tt);
	sprite[1].Render(tt);
	SpriteManager::GetInstance()->End();
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