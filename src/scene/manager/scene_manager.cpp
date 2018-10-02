#include "scene_manager.h"
#include "../main/title/title_scene.h"
#include "../../input/gamepad/gamepad_input.h"
#include <Windows.h>
void SceneManager::Init()
{
	my_scene = SCENE::TITLE;
	scene_ptr = switch_scene(my_scene);
}

void SceneManager::Update()
{
	GamepadInput::GetInstance()->Update();
	auto next_scene = scene_ptr->Update();
	if (next_scene != my_scene)
	{
		//ƒV[ƒ“‘JˆÚ
		scene_ptr->Destroy();
		//scene_ptr=
		scene_ptr->Init();
	}
}

void SceneManager::Render()
{

}

void SceneManager::Destroy()
{

}

std::unique_ptr<Scene> SceneManager::switch_scene(const SCENE scene)const 
{
	//return 
	switch (scene)
	{
	case SCENE::TITLE:
		return std::make_unique<TitleScene>();
	}
	return nullptr;
}