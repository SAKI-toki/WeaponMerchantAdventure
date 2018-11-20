/**
* @file select_scene.h
* @brief �Z���N�g�V�[���N���X�̐錾
* @author �ΎR�@�I
* @date 2018/11/19
*/
#pragma once
#include "../../scene.h"
#include "../../../object/character/player/player.h"
#include "../../../object/map/map.h"
#include "../../../object/select/select_object.h"
#include "../../../rendering/font/font.h"
/**
* @brief �Z���N�g�V�[���N���X
*/
class SelectScene :public Scene
{
	std::unique_ptr<Player> player;
	std::vector<MapObject> map;
	std::vector<SelectObj> select_obj;
	Sprite background;
	Font font;
	bool next_flg = false;
public:
	void Init()final;
	std::shared_ptr<Scene> Update(std::shared_ptr<Scene>&)final;
	void Render()final;
	void Destroy()final;
};