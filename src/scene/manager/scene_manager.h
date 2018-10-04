/**
* @file scene_manager.h
* @brief シーンのマネージャークラスの宣言
* @author 石山　悠
* @date 2018/10/02
*/
#pragma once
#include "../base/scene_base.h"
#include "../scene.h"
#include "../../common/singleton.h"
#include "../../sound/sound.h"	
#include "../../rendering/sprite/sprite.h"
#include <memory>
/**
* @brief シーンをマネージャーするクラス
*/
class SceneManager :public SceneBase, public Singleton<SceneManager>
{
	Sound sound[2];
	Sprite sprite[2];

	std::unique_ptr<Scene> scene_ptr;
	std::unique_ptr<Scene> switch_scene(const SCENE)const;
public:
	void Init()final;
	void Update();
	void Render()final;
	void Destroy()final;
};