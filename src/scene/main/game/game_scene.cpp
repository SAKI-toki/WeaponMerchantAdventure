/**
* @file game_scene.cpp
* @brief �Q�[���V�[���N���X�̃����o�֐��̒�`
* @author �ΎR�@�I
* @date 2018/10/30
*/
#include "game_scene.h"
#include "../../../common/common.h"
#include "../../../rendering/font/font.h"
#include "../../../object/camera/camera.h"
#include "../../../input/gamepad/gamepad_input.h"
#include "../../../sound/bgm/bgm.h"
/**
* @brief �Q�[���V�[���̏�����
*/
void GameScene::Init()
{
	my_scene = SCENE::GAME;
	//�v���C���[�̏�����
	{
		player.Init(std::string("player"), L"WizardWalkRight.png", 86, 128, { 100,270 }, 0, 0.5f);
	}
	//�G�̏�����
	{
		enemy.push_front(NormalEnemy());
		std::begin(enemy)->Init(std::string("normalenemy1"), L"monster1.png", 400, 366, { 1000,100 }, 0, 0.2f);
		enemy.push_front(NormalEnemy());
		std::begin(enemy)->Init(std::string("normalenemy2"), L"monster1.png", 400, 366, { 2100,-100 }, 0, 0.2f);

		f_enemy.push_front(FlyEnemy());
		std::begin(f_enemy)->Init(std::string("fly_enemy"), L"bird.png", 450, 415, { 2000,-500 }, 0, 0.25f);
		std::begin(f_enemy)->SetMove(VEC2(100, 0), 60);
		f_enemy.push_front(FlyEnemy());
		std::begin(f_enemy)->Init(std::string("fly_enemy"), L"bird.png", 450, 415, { 150,-100 }, 0, 0.25f);
		std::begin(f_enemy)->SetMove(VEC2(0, 100), 60);
		f_enemy.push_front(FlyEnemy());
		std::begin(f_enemy)->Init(std::string("fly_enemy"), L"bird.png", 450, 415, { 400,-200 }, 0, 0.25f);
		std::begin(f_enemy)->SetMove(VEC2(100, 100), 30);
	}
	//�w�i�̏�����
	{
		backGround.push_back(StaticObject());
		backGround[0].Init(std::string("background1"), L"background/sample5.jpg", 1920, 1080,
			{ 1920 / 2,1080 / 2 }, 0, 1);
	}
	//�}�b�v�̏�����
	{

		//�n��
		{
			MakeMap(field, { 32.0f * 0,32.0f * 10 }, 50, 3, std::string("field1"), L"map/map2.png", 32, 32);
			MakeMap(field, { 32.0f * 60, 32.0f * 0 }, 20, 3, std::string("field1"), L"map/map2.png", 32, 32);
		}
		//��
		{
			MakeMap(field, { 32.0f * 0,32.0f * -5 }, 2, 15, std::string("field1"), L"map/map2.png", 32, 32);
			MakeMap(field, { 32.0f * 48,32.0f * 8 }, 2, 2, std::string("field1"), L"map/map2.png", 32, 32);
			MakeMap(field, { 32.0f * 60,32.0f * -3 }, 2, 3, std::string("field1"), L"map/map2.png", 32, 32);
			MakeMap(field, { 32.0f * 78,32.0f * -3 }, 2, 3, std::string("field1"), L"map/map2.png", 32, 32);
		}
		//����
		{
			MakeMap(field, { 32.0f * 5,32.0f * 5 }, 3, 1, std::string("field1"), L"map/map2.png", 32, 32);
			MakeMap(field, { 32.0f * 30,32.0f * 5 }, 3, 1, std::string("field1"), L"map/map2.png", 32, 32);
			MakeMap(field, { 32.0f * 35,32.0f * 0 }, 3, 1, std::string("field1"), L"map/map2.png", 32, 32);
			MakeMap(field, { 32.0f * 40,32.0f * -5 }, 3, 1, std::string("field1"), L"map/map2.png", 32, 32);
			MakeMap(field, { 32.0f * 45,32.0f * -10 }, 3, 1, std::string("field1"), L"map/map2.png", 32, 32);
		}
	}
	//�v���C���[��ǔ�����
	Camera::GetInstance()->SetTarget(&player);
	BGM::GetInstance()->ChangeBgm(std::string("game_bgm"), L"BGM/game.wav");
}

/**
* @brief �Q�[���V�[���̍X�V
* @return SCENE �V�[�����ς��Ȃ玟�̃V�[����enum class��Ԃ�
*/
SCENE GameScene::Update()
{
	auto current_scene = my_scene;
	//�G�����Ȃ��Ȃ邩�A�v���C���[������艺�ɗ����邩�A�v���C���[�����񂾂�^�C�g���ɖ߂�
	if ((enemy.size() <= 0 && f_enemy.size() <= 0) || !player.enabled)
	{
		current_scene = SCENE::TITLE;
	}
	else
	{
		//�G�̍X�V
		{
			auto enemy_itr = std::begin(enemy);
			while (enemy_itr != std::end(enemy))
			{
				enemy_itr->Update();
				if (!enemy_itr->enabled)
				{
					enemy_itr = enemy.erase(enemy_itr);
				}
				else
				{
					++enemy_itr;
				}
			}

			auto f_enemy_itr = std::begin(f_enemy);
			while (f_enemy_itr != std::end(f_enemy))
			{
				f_enemy_itr->Update();
				if (!f_enemy_itr->enabled)
				{
					f_enemy_itr = f_enemy.erase(f_enemy_itr);
				}
				else
				{
					++f_enemy_itr;
				}
			}
		}
		//�v���C���[�̍X�V
		player.Update();
		//�}�b�v�̍X�V
		for (auto&& f : field)
		{
			f.Update();
		}
	}
	return current_scene;
}

/**
* @brief �Q�[���V�[���̕`��
*/
void GameScene::Render()
{
	//�w�i�̕`��
	for (auto&& back : backGround)
	{
		back.Render(false);
	}
	//�}�b�v�̕`��
	for (auto&& f : field)
	{
		f.Render();
	}
	//��΂Ȃ��G�̕`��
	for (auto&& e : enemy)
	{
		e.Render();
	}
	//��ԓG�̕`��
	for (auto&& f : f_enemy)
	{
		f.Render();
	}
	//�v���C���[�̕`��
	player.Render();
}

/**
* @brief �Q�[���V�[���̔j��
*/
void GameScene::Destroy()
{
	for (auto&& back : backGround)
	{
		back.Destroy();
	}
	for (auto&& f : field)
	{
		f.Destroy();
	}
	for (auto&& e : enemy)
	{
		e.Destroy();
	}
	for (auto&& f : f_enemy)
	{
		f.Destroy();
	}
	player.Destroy();

}