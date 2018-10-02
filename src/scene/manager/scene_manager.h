#pragma once
#include "../base/scene_base.h"
#include "../scene.h"
#include "../../common/singleton.h"
#include <memory>

class SceneManager :public SceneBase, public Singleton<SceneManager>
{
	SCENE my_scene;
	std::unique_ptr<Scene> scene_ptr;
	std::unique_ptr<Scene> switch_scene(const SCENE)const;
public:
	void Init()final;
	void Update();
	void Render()final;
	void Destroy()final;
};