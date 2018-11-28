/**
* @file game_scene_hard.cpp
* @brief �Q�[���V�[��(hard)�N���X�̃����o�֐��̒�`
* @author �ΎR�@�I
* @date 2018/11/20
*/
#include "game_scene_hard.h"
#include "../over/game_over.h"
#include "../../../../load/map/load_map.h"

#include "../../select/select_scene.h"

/**
* @brief �Q�[���V�[��(hard)�̏�����
*/
void GameSceneHard::Init()
{
	GameInit();
	//�}�b�v�̏�����
	{
		LoadMap::getinstance()->LoadingMap(L"hard_map.csv", L"hard_fly_enemy.csv");
		LoadMap::getinstance()->MakingMap(field, enemy, f_enemy, boss, player);
	}
	//�w�i
	{
		backGround.push_back(StaticObject());
		backGround[0].Init(std::string("background1"), L"background/background1.jpg", 600, 338,
			{ 1920 / 2,1080 / 2 }, 0, 3.5f);
	}
	//�{�X
	{
		boss->SetMaxHp(30.0f);
	}
	//GameInit();
	////�v���C���[�̏�����
	//{
	//	player->Init(std::string("player"), L"WizardWalkRight.png", 86, 128, { 200,200 }, 0, 0.6f);
	//}
	////�G�̏�����
	//{
	//	enemy.push_front(NormalEnemy());
	//	std::begin(enemy)->Init(std::string("normalenemy1"), L"monster1.png", 400, 366, { 1000,200 }, 0, 0.2f);
	//	enemy.push_front(NormalEnemy());
	//	std::begin(enemy)->Init(std::string("normalenemy1"), L"monster1.png", 400, 366, { 800,50 }, 0, 0.2f);
	//	enemy.push_front(NormalEnemy());
	//	std::begin(enemy)->Init(std::string("normalenemy2"), L"monster1.png", 400, 366, { 2100,-100 }, 0, 0.2f);

	//	f_enemy.push_front(FlyEnemy());
	//	std::begin(f_enemy)->Init(std::string("fly_enemy"), L"bird.png", 450, 415, { 2000,-500 }, 0, 0.25f);
	//	std::begin(f_enemy)->SetMove(VEC2(100, 0), 60);
	//	f_enemy.push_front(FlyEnemy());
	//	std::begin(f_enemy)->Init(std::string("fly_enemy"), L"bird.png", 450, 415, { 300,-100 }, 0, 0.25f);
	//	std::begin(f_enemy)->SetMove(VEC2(0, 100), 60);
	//	f_enemy.push_front(FlyEnemy());
	//	std::begin(f_enemy)->Init(std::string("fly_enemy"), L"bird.png", 450, 415, { 700,-200 }, 0, 0.25f);
	//	std::begin(f_enemy)->SetMove(VEC2(100, 100), 30);
	//}
	////�w�i�̏�����
	//{
	//	backGround.push_back(StaticObject());
	//	backGround[0].Init(std::string("background1"), L"background/background1.jpg", 600, 338,
	//		{ 1920 / 2,1080 / 2 }, 0, 3.5f);
	//}
	////�}�b�v�̏�����
	//{
	//	//�n��
	//	{
	//		MakeMap(field, { 64.0f * 0,64.0f * 5 }, 120, 4, std::string("field1"), L"map/map2.png", 32, 32, 0, 2);
	//		MakeMap(field, { 64.0f * 30, 64.0f * 0 }, 20, 3, std::string("field1"), L"map/map2.png", 32, 32, 0, 2);
	//	}
	//	//��
	//	{
	//		MakeMap(field, { 64.0f * 0,64.0f * -9 }, 2, 15, std::string("field1"), L"map/map2.png", 32, 32, 0, 2);
	//		MakeMap(field, { 64.0f * 20,64.0f * 3 }, 2, 2, std::string("field1"), L"map/map2.png", 32, 32, 0, 2);
	//	}
	//	//����
	//	{
	//		MakeMap(field, { 64.0f * 10,64.0f * 3 }, 3, 1, std::string("field1"), L"map/map2.png", 32, 32, 0, 2);
	//		MakeMap(field, { 64.0f * 15,64.0f * 1 }, 3, 1, std::string("field1"), L"map/map2.png", 32, 32, 0, 2);
	//		/*MakeMap(field, { 32.0f * 35,32.0f * 0 }, 3, 1, std::string("field1"), L"map/map2.png", 32, 32, 0, 2);
	//		MakeMap(field, { 32.0f * 40,32.0f * -5 }, 3, 1, std::string("field1"), L"map/map2.png", 32, 32, 0, 2);
	//		MakeMap(field, { 32.0f * 45,32.0f * -10 }, 3, 1, std::string("field1"), L"map/map2.png", 32, 32, 0, 2);*/
	//	}
	//}
	////�{�X
	//{
	//	boss->Init(std::string("Boss"), L"boss.png", 303, 400, VEC2{ 5000.0f,-100.0f }, 0, 0.5f);
	//	boss->SetMaxHp(100.0f);
	//}
}

/**
* @brief �Q�[���V�[��(hard)�̍X�V
* @return std::shared_ptr<Scene> �V�[�����ς��Ȃ玟�̃V�[����std::shared_ptr<Scene>��Ԃ�
*/
std::shared_ptr<Scene> GameSceneHard::Update(std::shared_ptr<Scene>& scene)
{
	auto current_scene = scene;

	//�v���C���[�����񂾂�^�C�g���ɖ߂�
	if (!player->enabled)
	{
		GameOver::getinstance()->Update(current_scene, std::make_shared<GameSceneHard>());
		return current_scene;
	}

	current_scene = GameUpdate(scene);

	return current_scene;
}

/**
* @brief �Q�[���V�[��(hard)�̕`��
*/
void GameSceneHard::Render()
{
	GameRender();
}

/**
* @brief �Q�[���V�[��(hard)�̔j��
*/
void GameSceneHard::Destroy()
{
	GameDestroy();
}