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
		LoadMap::getinstance()->LoadingMap(L"easy_map.csv", L"easy_fly_enemy.csv");
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
	//	player->Init(std::string("player"), L"WizardWalkRight.png", 86, 128,
	//		{ 200,200 }, 0, 0.6f);
	//}
	////�G�̏�����
	//{
	//	//��΂Ȃ��G
	//	{
	//		enemy.push_front(NormalEnemy());
	//		std::begin(enemy)->Init(std::string("normalenemy1"), L"monster1.png", 400, 366,
	//			{ BLOCK_SIZE * 16,BLOCK_SIZE * 3 }, 0, 0.2f);
	//		enemy.push_front(NormalEnemy());
	//		std::begin(enemy)->Init(std::string("normalenemy2"), L"monster1.png", 400, 366,
	//			{ BLOCK_SIZE * 27,BLOCK_SIZE * 3 }, 0, 0.2f);
	//		enemy.push_front(NormalEnemy());
	//		std::begin(enemy)->Init(std::string("normalenemy2"), L"monster1.png", 400, 366,
	//			{ BLOCK_SIZE * 33,BLOCK_SIZE * 3 }, 0, 0.2f);
	//	}
	//	//��ԓG
	//	{
	//		f_enemy.push_front(FlyEnemy());
	//		std::begin(f_enemy)->Init(std::string("fly_enemy"), L"bird.png", 450, 415,
	//			{ BLOCK_SIZE * 5,BLOCK_SIZE * -5 }, 0, 0.25f);
	//		std::begin(f_enemy)->SetMove(VEC2(100, 100), 60);
	//		f_enemy.push_front(FlyEnemy());
	//		std::begin(f_enemy)->Init(std::string("fly_enemy"), L"bird.png", 450, 415,
	//			{ BLOCK_SIZE * 25,BLOCK_SIZE * -8 }, 0, 0.25f);
	//		std::begin(f_enemy)->SetMove(VEC2(2000, 0), 2000);
	//		f_enemy.push_front(FlyEnemy());
	//		std::begin(f_enemy)->Init(std::string("fly_enemy"), L"bird.png", 450, 415,
	//			{ BLOCK_SIZE * 43,BLOCK_SIZE * 2 }, 0, 0.25f);
	//		std::begin(f_enemy)->SetMove(VEC2(200, 200), 60);
	//		f_enemy.push_front(FlyEnemy());
	//		std::begin(f_enemy)->Init(std::string("fly_enemy"), L"bird.png", 450, 415,
	//			{ BLOCK_SIZE * 45,BLOCK_SIZE * 2 }, 0, 0.25f);
	//		std::begin(f_enemy)->SetMove(VEC2(0, 0), 1);
	//		f_enemy.push_front(FlyEnemy());
	//		std::begin(f_enemy)->Init(std::string("fly_enemy"), L"bird.png", 450, 415,
	//			{ BLOCK_SIZE * 47,BLOCK_SIZE * 2 }, 0, 0.25f);
	//		std::begin(f_enemy)->SetMove(VEC2(-200, 200), 60);
	//	}
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
	//		MakeMap(field, { BLOCK_SIZE * 0,BLOCK_SIZE * 5 }, 120, 4, std::string("field1"), L"map/map2.png", BLOCK_TEXTURE_SIZE, BLOCK_TEXTURE_SIZE, 0, BLOCK_SCALE);
	//	}
	//	//��
	//	{
	//		MakeMap(field, { BLOCK_SIZE * 0,BLOCK_SIZE * -10 }, 2, 15, std::string("field1"), L"map/map2.png", BLOCK_TEXTURE_SIZE, BLOCK_TEXTURE_SIZE, 0, BLOCK_SCALE);
	//		MakeMap(field, { BLOCK_SIZE * 10,BLOCK_SIZE * 3 }, 3, 2, std::string("field1"), L"map/map2.png", BLOCK_TEXTURE_SIZE, BLOCK_TEXTURE_SIZE, 0, BLOCK_SCALE);
	//		MakeMap(field, { BLOCK_SIZE * 23,BLOCK_SIZE * 3 }, 3, 2, std::string("field1"), L"map/map2.png", BLOCK_TEXTURE_SIZE, BLOCK_TEXTURE_SIZE, 0, BLOCK_SCALE);
	//		MakeMap(field, { BLOCK_SIZE * 36,BLOCK_SIZE * 3 }, 3, 2, std::string("field1"), L"map/map2.png", BLOCK_TEXTURE_SIZE, BLOCK_TEXTURE_SIZE, 0, BLOCK_SCALE);
	//	}
	//	//����
	//	{
	//		MakeMap(field, { BLOCK_SIZE * 27,BLOCK_SIZE * 1 }, 8, 1, std::string("field1"), L"map/map2.png", BLOCK_TEXTURE_SIZE, BLOCK_TEXTURE_SIZE, 0, BLOCK_SCALE);
	//		MakeMap(field, { BLOCK_SIZE * 49,BLOCK_SIZE * 4 }, 1, 1, std::string("field1"), L"map/map2.png", BLOCK_TEXTURE_SIZE, BLOCK_TEXTURE_SIZE, 0, BLOCK_SCALE);
	//		MakeMap(field, { BLOCK_SIZE * 50,BLOCK_SIZE * 3 }, 1, 2, std::string("field1"), L"map/map2.png", BLOCK_TEXTURE_SIZE, BLOCK_TEXTURE_SIZE, 0, BLOCK_SCALE);
	//		MakeMap(field, { BLOCK_SIZE * 51,BLOCK_SIZE * 2 }, 1, 3, std::string("field1"), L"map/map2.png", BLOCK_TEXTURE_SIZE, BLOCK_TEXTURE_SIZE, 0, BLOCK_SCALE);
	//		MakeMap(field, { BLOCK_SIZE * 52,BLOCK_SIZE * 1 }, 1, 4, std::string("field1"), L"map/map2.png", BLOCK_TEXTURE_SIZE, BLOCK_TEXTURE_SIZE, 0, BLOCK_SCALE);
	//		MakeMap(field, { BLOCK_SIZE * 53,BLOCK_SIZE * 0 }, 1, 5, std::string("field1"), L"map/map2.png", BLOCK_TEXTURE_SIZE, BLOCK_TEXTURE_SIZE, 0, BLOCK_SCALE);
	//		MakeMap(field, { BLOCK_SIZE * 54,BLOCK_SIZE * -1 }, 1, 6, std::string("field1"), L"map/map2.png", BLOCK_TEXTURE_SIZE, BLOCK_TEXTURE_SIZE, 0, BLOCK_SCALE);

	//	}
	//}
	////�{�X
	//{
	//	boss->Init(std::string("Boss"), L"boss.png", 303, 400, 
	//		{ 5000.0f,-200.0f }, 0, 0.5f);
	//	boss->SetMaxHp(30.0f);
	//}
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