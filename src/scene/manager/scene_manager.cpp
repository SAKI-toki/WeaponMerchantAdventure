/**
* @file scene_manager.cpp
* @brief シーンのマネージャークラスのメンバ関数を定義
* @author 石山　悠
* @date 2018/10/02
*/
#include "scene_manager.h"
#include "../main/title/title_scene.h"
#include "../../input/gamepad/gamepad_input.h"
#include "../../sound/manager/sound_manager.h"
#include <Windows.h>

/**
* @brief シーンマネージャーの初期化
*/
void SceneManager::Init()
{
	my_scene = SCENE::TITLE;
	scene_ptr = switch_scene(my_scene);
	scene_ptr->Init();
	sound.Init(L"resources/sample.wav", true,true);
}

/**
* @brief 保持してるシーンの更新
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
		//シーン遷移
		scene_ptr->Destroy();
		scene_ptr = switch_scene(next_scene);
		scene_ptr->Init();
	}
}

/**
* @brief 保持してるシーンの描画
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
* @brief 保持してるシーンのマネージャーの破棄
*/
void SceneManager::Destroy()
{
	scene_ptr->Destroy();
	SoundManager::GetInstance()->Destroy();
}

/**
* @brief 引数によってシーンを切り替える
* @param scene 次のシーンのenum class
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