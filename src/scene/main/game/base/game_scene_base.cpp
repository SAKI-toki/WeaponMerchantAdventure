/**
* @file game_scene_base.cpp
* @brief �Q�[���V�[���̃X�[�p�[�N���X�̐錾
* @author �ΎR�@�I
* @date 2018/11/26
*/
#include "game_scene_base.h"
#include "../../../../common/common.h"
#include "../../../../rendering/font/font.h"
#include "../../../../object/camera/camera.h"
#include "../../../../input/gamepad/gamepad_input.h"
#include "../../../../sound/bgm/bgm.h"
#include "../over/game_over.h"
#include "../../../../collider/manager/collider_manager.h"

#include "../../select/select_scene.h"

/**
* @brief �Q�[���V�[���̏�����
*/
void GameSceneBase::GameInit()
{
	player = std::make_unique<Player>();
	boss = std::make_unique<Boss>();
	//�v���C���[��ǔ�����
	Camera::GetInstance()->SetTarget(player.get());
	ColliderManager::GetInstance()->SetTarget(player.get());
	BGM::GetInstance()->ChangeBgm(std::string("game_bgm"), L"BGM/game.wav");
}

/**
* @brief �Q�[���V�[���̍X�V
* @return std::shared_ptr<Scene> �V�[�����ς��Ȃ玟�̃V�[����std::shared_ptr<Scene>��Ԃ�
*/
std::shared_ptr<Scene> GameSceneBase::GameUpdate(std::shared_ptr<Scene>& scene)
{
	auto current_scene = scene;


	//�v���C���[�����񂾂�^�C�g���ɖ߂�
	/*if (!player->enabled)
	{
		GameOver::getinstance()->Update(current_scene, std::make_shared<GameSceneEasy>());
		return current_scene;
	}*/


	//�G�̍X�V
	if (current_game == GAME::MAIN)
	{
		//�v���C���[���{�X�]�[���ɓ�������{�X�V�[���Ɉڍs�����ʂɕύX
		if (player->boss_scene)
		{
			current_game = GAME::TRANSLATION;
			Camera::GetInstance()->SetTarget(nullptr);
			boss->TranslationBossScene();
			player->TranslationBossScene();
			BGM::GetInstance()->ChangeBgm(std::string("boss_bgm"), L"BGM/boss.wav");
		}
		else
		{
			//�G
			auto enemy_itr = std::begin(enemy);
			while (enemy_itr != std::end(enemy))
			{
				//�v���C���[�ƈ��͈͗����ƍX�V���Ȃ�
				if (std::abs(player->transform.pos.x - enemy_itr->transform.pos.x) < WINDOW_WIDTH)
				{
					enemy_itr->Update();
				}
				if (!enemy_itr->enabled)
				{
					enemy_itr = enemy.erase(enemy_itr);
				}
				else
				{
					++enemy_itr;
				}
			}
			//��ԓG
			auto f_enemy_itr = std::begin(f_enemy);
			while (f_enemy_itr != std::end(f_enemy))
			{
				//�v���C���[�ƈ��͈͗����ƍX�V���Ȃ�
				if (std::abs(player->transform.pos.x - f_enemy_itr->transform.pos.x) < WINDOW_WIDTH)
				{
					f_enemy_itr->Update();
				}
				if (!f_enemy_itr->enabled)
				{
					f_enemy_itr = f_enemy.erase(f_enemy_itr);
				}
				else
				{
					++f_enemy_itr;
				}
			}
			//�v���C���[�̍X�V
			player->Update();
		}
	}
	//�{�X�V�[���ɑJ��
	else if (current_game == GAME::TRANSLATION)
	{
		//�v���C���[�ƃ{�X���߂��Ȃ�����{�X�V�[���Ɉڍs����
		if (player->transform.pos.x >= boss->transform.pos.x - 500)
		{
			current_game = GAME::BOSS;
			boss_center_x = Camera::GetInstance()->GetPos().x + WINDOW_WIDTH / 2.0f;
			boss->InBossScene(boss_center_x);
			player->InBossScene();
			for (auto&& e : enemy)
			{
				e.Destroy();
			}
			for (auto&& f : f_enemy)
			{
				f.Destroy();
			}
		}
		else
		{
			player->transform.pos.x += 2.8f * 1.2f;
			auto camera_pos = Camera::GetInstance()->GetPos();
			camera_pos += VEC2{ 4.0f * 1.2f,0.0f };
			Camera::GetInstance()->DirectSetPos(camera_pos);
			player->UpdateAnimation();
		}
		boss->Update();
		boss->ResetSpeed();
	}
	//�{�X�̍X�V
	else if (current_game == GAME::BOSS)
	{
		//�{�X��|������N���A�Ɉڍs����
		if (!boss->enabled)
		{
			boss->DestroyUi();
			player->EnabledWeapon();
			current_game = GAME::CLEAR;
			BGM::GetInstance()->OneShotBGM(std::string("clear_bgm"), L"BGM/clear.wav");
		}
		//��ʂ̊O�ɏo�Ȃ��悤�ɂ���i����͉��݂̂̔���̂��߂����Ŕ��肷��j
		if (player->transform.pos.x < boss_center_x - WINDOW_WIDTH / 2.0f)
		{
			player->transform.pos.x = boss_center_x - WINDOW_WIDTH / 2.0f;
			player->ResetSpeed();
		}
		else if (player->transform.pos.x > boss_center_x + WINDOW_WIDTH / 2.0f)
		{
			player->transform.pos.x = boss_center_x + WINDOW_WIDTH / 2.0f;
			player->ResetSpeed();
		}
		//�v���C���[�̍X�V
		player->Update();
		boss->Update();
	}
	//�N���A���̃A�j���[�V����
	else if (current_game == GAME::CLEAR)
	{
		player->ResetSpeed();
		//��ʂ̒����t�߂ɗ�����A�j���[�V�����J�n
		if (player->transform.pos.x > boss_center_x - 10 && player->transform.pos.x < boss_center_x + 10)
		{
			//�W�����v����
			if (!clear_jump&&player->gravity.SetUpPower(10.0f))
			{
				clear_jump = true;
				player->transform.Rotate(PI<float>*0.04f);
			}
			else if (clear_jump)
			{
				if (player->transform.rot != 0.0f)
				{
					player->transform.Rotate(PI<float>*0.04f);
					if (player->transform.rot > PI<float>*2.0f)
					{
						player->transform.rot = 0.0f;
					}
				}
				else if (player->gravity.SetUpPower(0.0f))
				{
					current_scene = std::make_shared<SelectScene>();
				}
			}
		}
		else
		{
			//��ʒ����ɋ߂Â�
			if (player->transform.pos.x < boss_center_x)
			{
				player->transform.Move(VEC2(2.8f*1.2f, 0));
				player->AnimationWalk(true);
			}
			else
			{
				player->transform.Move(VEC2(-2.8f*1.2f, 0));
				player->AnimationWalk(false);
			}
		}
		player->ClearUpdate();
		//current_scene = std::make_shared<TitleScene>();
	}
	//�}�b�v�̍X�V
	for (auto&& f : field)
	{
		f.Update();
	}
	return current_scene;
}

/**
* @brief �Q�[���V�[���̕`��
*/
void GameSceneBase::GameRender()
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
	//�{�X�̕`��
	boss->Render();
	//�v���C���[�̕`��
	player->Render();
	player->UiRender();
	if (!player->enabled)
	{
		GameOver::getinstance()->Render();
	}
}

/**
* @brief �Q�[���V�[���̔j��
*/
void GameSceneBase::GameDestroy()
{
	for (auto&& back : backGround)
	{
		back.Destroy();
	}
	backGround.clear();
	for (auto&& f : field)
	{
		f.Destroy();
	}
	field.clear();
	for (auto&& e : enemy)
	{
		e.Destroy();
	}
	enemy.clear();
	for (auto&& f : f_enemy)
	{
		f.Destroy();
	}
	f_enemy.clear();
	boss->Destroy();
	player->Destroy();
	GameOver::getinstance()->Reset();
}