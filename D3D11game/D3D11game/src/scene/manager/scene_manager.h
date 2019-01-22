/**
* @file scene_manager.h
* @brief シーンのマネージャークラスの宣言
* @author 石山　悠
* @date 2018/10/02
*/
#pragma once
#include "../base/scene_base.h"
#include "../scene.h"
#include <saki/singleton/singleton.h>
#include <memory>
/**
* @brief シーンをマネージャーするクラス
*/
class SceneManager :public SceneBase, public saki::Singleton<SceneManager>
{
	bool continue_scene = false;
	std::shared_ptr<Scene> next_continue_scene_ptr;
	//シーン
	std::shared_ptr<Scene> scene_ptr;
	std::shared_ptr<Scene> next_scene_ptr;
	//フェード中かどうか
	bool is_current_fade = false;
	//フェードインかどうか
	bool is_fade_in = false;
public:
	bool is_game_scene = false;
	void Init()final;
	void Update();
	void Render()final;
	void Destroy()final;
	
	void ContinueGame(std::shared_ptr<Scene>& p)
	{
		continue_scene = true;
		next_continue_scene_ptr = p;
	}
};