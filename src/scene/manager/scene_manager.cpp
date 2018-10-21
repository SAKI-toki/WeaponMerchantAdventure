/**
* @file scene_manager.cpp
* @brief シーンのマネージャークラスのメンバ関数を定義
* @author 石山　悠
* @date 2018/10/02
*/
#include "scene_manager.h"
#include "../main/title/title_scene.h"
#include "../main/game/game_scene.h"
#include "../../input/gamepad/gamepad_input.h"
#include "../../sound/manager/sound_manager.h"
#include "../../rendering/sprite/manager/sprite_manager.h"
#include "../../collider/manager/collider_manager.h"
#include "../../object/camera/camera.h"

/**
* @brief シーンマネージャーの初期化
*/
void SceneManager::Init()
{
	SpriteManager::GetInstance()->Init();
	my_scene = SCENE::TITLE;
	scene_ptr = switch_scene(my_scene);
	scene_ptr->Init();
}

/**
* @brief 保持してるシーンの更新
*/
void SceneManager::Update()
{
	SoundManager::GetInstance()->Update();
	GamepadInput::GetInstance()->Update();
	auto next_scene = scene_ptr->Update();
	if (next_scene != my_scene)
	{
		my_scene = next_scene;
		//シーン遷移
		scene_ptr->Destroy();
		ColliderManager::GetInstance()->Reset();
		scene_ptr = switch_scene(next_scene);
		scene_ptr->Init();
	}
	ColliderManager::GetInstance()->CheckCollision();
	Camera::GetInstance()->Update();
}

/**
* @brief 保持してるシーンの描画
*/
void SceneManager::Render()
{
	SpriteManager::GetInstance()->Start();
	scene_ptr->Render();
	SpriteManager::GetInstance()->End();
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
	case SCENE::GAME:
		return std::make_unique<GameScene>();
	}
	return nullptr;
}