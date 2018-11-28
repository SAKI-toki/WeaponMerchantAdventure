/**
* @file game_scene_base.cpp
* @brief ゲームシーンのスーパークラスの宣言
* @author 石山　悠
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
* @brief ゲームシーンの初期化
*/
void GameSceneBase::GameInit()
{
	player = std::make_unique<Player>();
	boss = std::make_unique<Boss>();
	//プレイヤーを追尾する
	Camera::GetInstance()->SetTarget(player.get());
	ColliderManager::GetInstance()->SetTarget(player.get());
	BGM::GetInstance()->ChangeBgm(std::string("game_bgm"), L"BGM/game.wav");
}

/**
* @brief ゲームシーンの更新
* @return std::shared_ptr<Scene> シーンが変わるなら次のシーンのstd::shared_ptr<Scene>を返す
*/
std::shared_ptr<Scene> GameSceneBase::GameUpdate(std::shared_ptr<Scene>& scene)
{
	auto current_scene = scene;


	//プレイヤーが死んだらタイトルに戻る
	/*if (!player->enabled)
	{
		GameOver::getinstance()->Update(current_scene, std::make_shared<GameSceneEasy>());
		return current_scene;
	}*/


	//敵の更新
	if (current_game == GAME::MAIN)
	{
		//プレイヤーがボスゾーンに入ったらボスシーンに移行する場面に変更
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
			//敵
			auto enemy_itr = std::begin(enemy);
			while (enemy_itr != std::end(enemy))
			{
				//プレイヤーと一定範囲離れると更新しない
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
			//飛ぶ敵
			auto f_enemy_itr = std::begin(f_enemy);
			while (f_enemy_itr != std::end(f_enemy))
			{
				//プレイヤーと一定範囲離れると更新しない
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
			//プレイヤーの更新
			player->Update();
		}
	}
	//ボスシーンに遷移
	else if (current_game == GAME::TRANSLATION)
	{
		//プレイヤーとボスが近くなったらボスシーンに移行する
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
	//ボスの更新
	else if (current_game == GAME::BOSS)
	{
		//ボスを倒したらクリアに移行する
		if (!boss->enabled)
		{
			boss->DestroyUi();
			player->EnabledWeapon();
			current_game = GAME::CLEAR;
			BGM::GetInstance()->OneShotBGM(std::string("clear_bgm"), L"BGM/clear.wav");
		}
		//画面の外に出ないようにする（これは横のみの判定のためここで判定する）
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
		//プレイヤーの更新
		player->Update();
		boss->Update();
	}
	//クリア時のアニメーション
	else if (current_game == GAME::CLEAR)
	{
		player->ResetSpeed();
		//画面の中央付近に来たらアニメーション開始
		if (player->transform.pos.x > boss_center_x - 10 && player->transform.pos.x < boss_center_x + 10)
		{
			//ジャンプする
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
			//画面中央に近づく
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
	//マップの更新
	for (auto&& f : field)
	{
		f.Update();
	}
	return current_scene;
}

/**
* @brief ゲームシーンの描画
*/
void GameSceneBase::GameRender()
{

	//背景の描画
	for (auto&& back : backGround)
	{
		back.Render(false);
	}
	//マップの描画
	for (auto&& f : field)
	{
		f.Render();
	}
	//飛ばない敵の描画
	for (auto&& e : enemy)
	{
		e.Render();
	}
	//飛ぶ敵の描画
	for (auto&& f : f_enemy)
	{
		f.Render();
	}
	//ボスの描画
	boss->Render();
	//プレイヤーの描画
	player->Render();
	player->UiRender();
	if (!player->enabled)
	{
		GameOver::getinstance()->Render();
	}
}

/**
* @brief ゲームシーンの破棄
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