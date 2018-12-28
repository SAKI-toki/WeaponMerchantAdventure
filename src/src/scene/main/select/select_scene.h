/**
* @file select_scene.h
* @brief セレクトシーンクラスの宣言
* @author 石山　悠
* @date 2018/11/19
*/
#pragma once
#include "../../scene.h"
#include "../../../object/character/player/player.h"
#include "../../../object/map/map.h"
#include "../../../object/select/select_object.h"
/**
* @brief セレクトシーンクラス
*/
class SelectScene :public Scene
{
	//exit関係
	bool exit_flg = false;
	bool exit_select = false;
	bool exit_select_end = false;
	int exit_num = 0;
	bool upflg = true;
	bool downflg = true;
	Sprite exit_sprite[3];
	std::unique_ptr<Player> player;
	std::vector<MapObject> map;
	std::vector<SelectObj> select_obj;
	StaticObject exit_sign;

	Sprite background;
	bool next_flg = false;

	static constexpr float operation_scale = 0.5f;
	Sprite frame;
	Transform operation_transform;
	Sprite x_button;
	Sprite operation_player;
	Sprite bullet;
	Sprite momentum;
	bool player_right = false;
public:
	void Init()final;
	std::shared_ptr<Scene> Update(std::shared_ptr<Scene>&)final;
	void Render()final;
	void Destroy()final;
	void ExitFadeUpdate()final;
};