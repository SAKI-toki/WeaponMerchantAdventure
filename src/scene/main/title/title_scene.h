/**
* @file title_scene.h
* @brief タイトルシーンクラスの宣言
* @author 石山　悠
* @date 2018/11/19
*/
#pragma once
#include "../../scene.h"
#include "../../../rendering/font/font.h"
#include "../../../rendering/sprite/sprite.h"
#include "../../../object/character/player/player.h"
#include "../../../object/map/map.h"
#include <vector>

/**
* @brief タイトルシーンクラス
*/
class TitleScene :public Scene
{
	int finger_time = 0;
	std::vector<Font> font;
	Sprite background;
	Sprite finger_arrow;
	std::unique_ptr<Player> player;
	std::vector<MapObject> map;
public:
	void Init()final;
	std::shared_ptr<Scene> Update(std::shared_ptr<Scene>&)final;
	void Render()final;
	void Destroy()final;
};