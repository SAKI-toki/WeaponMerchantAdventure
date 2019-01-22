/**
* @file title_scene.h
* @brief �^�C�g���V�[���N���X�̐錾
* @author �ΎR�@�I
* @date 2018/11/19
*/
#pragma once
#include "../../scene.h"
#include "../../../sprite/sprite.h"
#include "../../../object/character/player/player.h"
#include "../../../object/map/map.h"
#include <vector>
/**
* @brief �^�C�g���V�[���N���X
*/
class TitleScene :public Scene
{
	int finger_time = 0;
	std::unique_ptr<Player> player;
	std::vector<MapObject> map;
	//�w�i
	Sprite background;
	//�w�̉摜
	Sprite finger_arrow;
	static constexpr float operation_scale = 0.5f;
	Sprite frame;
	Transform frame_transform;
	//�X�e�B�b�N��|�����摜
	Sprite down_stick;
	Transform stick_transform;
	int stick_time = 0;
	Sprite operation_player;
	Animation operation_anim;
	Transform operation_player_transform;
	Vec2 operation_size;
	bool player_right = false;
public:
	void Init()final;
	std::shared_ptr<Scene> Update(std::shared_ptr<Scene>&)final;
	void Render()final;
	void Destroy()final;
};