/**
* @file game_scene_easy.cpp
* @brief �Q�[���V�[��(easy)�N���X�̃����o�֐��̒�`
* @author �ΎR�@�I
* @date 2018/11/22
*/
#include "game_scene_easy.h"
#include "../over/game_over.h"
#include "../../../../load/map/load_map.h"

#include "../../select/select_scene.h"

/**
* @brief �Q�[���V�[��(easy)�̏�����
*/
void GameSceneEasy::Init()
{
	GameInit();
	//�}�b�v�̏�����
	{
		LoadMap::getinstance()->GameLoadingMap(L"easy_map.csv", L"easy_fly_enemy.csv");
		LoadMap::getinstance()->GameMakingMap(field, enemy, f_enemy, boss, player, bullet_item);
	}
	//�w�i
	{
		backGround.push_back(StaticObject());
		backGround[0].Init(std::string("background1"), L"background/background1.jpg", 600, 338,
			{ 0,0,9000 }, saki::vector3_zero<float>, Vec3{ 3.5f,3.5f,1 });
	}
	//�{�X
	{
		boss->SetMaxHp(30.0f);
	}
}

/**
* @brief �Q�[���V�[��(easy)�̍X�V
* @return std::shared_ptr<Scene> �V�[�����ς��Ȃ玟�̃V�[����std::shared_ptr<Scene>��Ԃ�
*/
std::shared_ptr<Scene> GameSceneEasy::Update(std::shared_ptr<Scene>& scene)
{
	auto current_scene = scene;

	//�v���C���[�����񂾂�^�C�g���ɖ߂�
	if (!player->enabled)
	{
		GameOver::getinstance()->Update(current_scene, std::make_shared<GameSceneEasy>());
		return current_scene;
	}

	current_scene = GameUpdate(scene);

	return current_scene;
}

/**
* @brief �Q�[���V�[��(easy)�̕`��
*/
void GameSceneEasy::Render()
{
	GameRender();
}

/**
* @brief �Q�[���V�[��(easy)�̔j��
*/
void GameSceneEasy::Destroy()
{
	GameDestroy();
}