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
#include <memory>
/**
* @brief シーンをマネージャーするクラス
*/
class SceneManager :public SceneBase, public Singleton<SceneManager>
{
	//シーン
	std::shared_ptr<Scene> scene_ptr;
	std::shared_ptr<Scene> next_scene_ptr;
	//フェード中かどうか
	bool is_current_fade = false;
	//フェードインかどうか
	bool is_fade_in = false;
public:
	void Init()final;
	void Update();
	void Render()final;
	void Destroy()final;
};