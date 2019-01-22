/**
* @file game_scene_normal.cpp
* @brief �Q�[���V�[��(normal)�N���X�̃����o�֐��̒�`
* @author �ΎR�@�I
* @date 2018/11/20
*/
#include "game_scene_normal.h"
#include "../over/game_over.h"
#include "../../../../load/map/load_map.h"

#include "../../select/select_scene.h"


/**
* @brief �Q�[���V�[��(normal)�̏�����
*/
void GameSceneNormal::Init()
{
	GameInit();
	//�}�b�v�̏�����
	{
		LoadMap::getinstance()->GameLoadingMap(L"normal_map.csv", L"normal_fly_enemy.csv");
		LoadMap::getinstance()->GameMakingMap(field, enemy, f_enemy, boss, player,bullet_item);
	}
	//�w�i
	{
		backGround.push_back(StaticObject());
		backGround[0].Init(std::string("background1"), L"background/background1.jpg", 600, 338,
			{ 0,0,9000 }, saki::vector3_zero<float>, Vec3{ 3.5f,3.5f,1 });
	}
	//�{�X
	{
		boss->SetMaxHp(60.0f);
	}
}

/**
* @brief �Q�[���V�[��(normal)�̍X�V
* @return std::shared_ptr<Scene> �V�[�����ς��Ȃ玟�̃V�[����std::shared_ptr<Scene>��Ԃ�
*/
std::shared_ptr<Scene> GameSceneNormal::Update(std::shared_ptr<Scene>& scene)
{
	auto current_scene = scene;

	//�v���C���[�����񂾂�^�C�g���ɖ߂�
	if (!player->enabled)
	{
		GameOver::getinstance()->Update(current_scene, std::make_shared<GameSceneNormal>());
		return current_scene;
	}
	current_scene = GameUpdate(scene);
	return current_scene;
}

/**
* @brief �Q�[���V�[��(normal)�̕`��
*/
void GameSceneNormal::Render()
{
	GameRender();
}

/**
* @brief �Q�[���V�[��(normal)�̔j��
*/
void GameSceneNormal::Destroy()
{
	GameDestroy();
}