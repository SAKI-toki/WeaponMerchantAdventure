#pragma once
#include "../scene.h"
#include <saki/singleton/singleton.h>
#include "../../sprite/sprite.h"
#include "../../sound/bgm/bgm.h"
class PauseScene :public saki::Singleton<PauseScene>,public Scene
{
	Sound move_sound;
	Sound accept_sound;
	//テクスチャ
	Sprite black;
	Sprite next_scene[2];
	int current_select = 0;
	bool upflg = true;
	bool downflg = true;
public:
	void Init();
	std::shared_ptr<Scene> Update(std::shared_ptr<Scene>&);
	void Render();
	void Destroy();
	bool is_pause = false;
	void Reset()
	{
		current_select = 0;
		next_scene[0].ColorChange(1.0f, 1.0f, 1.0f, 1.0f);
		next_scene[1].ColorChange(0.4f, 0.4f, 0.4f, 1.0f);
		upflg = true;
		downflg = true;
	}
	void EndPause()
	{
		is_pause = false;
		Reset();
	}
	void SwitchPause()
	{
		is_pause = true;
		move_sound.stop();
		accept_sound.stop();
		BGM::getinstance()->SetVolume(0.55f);
	}
};