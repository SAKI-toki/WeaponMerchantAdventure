/**
* @file game_scene_base.cpp
* @brief ゲームシーンのスーパークラスの宣言
* @author 石山　悠
* @date 2018/11/26
*/
#include "game_scene_base.h"
#include "../../../../common/common.h"
#include "../../../../camera/camera.h"
#include "../../../../input/gamepad/gamepad_input.h"
#include "../../../../sound/bgm/bgm.h"
#include "../over/game_over.h"
#include "../../../../collider/manager/collider_manager.h"
#include "../../../manager/scene_manager.h"
#include <saki/pi.h>
#include "../../select/select_scene.h"

#ifdef _DEBUG
#include "../easy/game_scene_easy.h"
#include "../normal/game_scene_normal.h"
#include "../hard/game_scene_hard.h"
#include "../../title/title_scene.h"
#endif 

/**
* @brief ゲームシーンの初期化
*/
void GameSceneBase::GameInit()
{
	SceneManager::getinstance()->is_game_scene = true;
	player = std::make_unique<Player>();
	boss = std::make_unique<Boss>();
	//プレイヤーを追尾する
	Camera::getinstance()->SetTarget(player.get());
	Sprite::has_target = true;
	Camera::getinstance()->SetPos(player->transform.get_pos());
	ColliderManager::getinstance()->SetTarget(player.get());
	BGM::getinstance()->ChangeBgm(std::string("game_bgm"), L"BGM/game.wav");
}

/**
* @brief ゲームシーンの更新
* @return std::shared_ptr<Scene> シーンが変わるなら次のシーンのstd::shared_ptr<Scene>を返す
*/
std::shared_ptr<Scene> GameSceneBase::GameUpdate(std::shared_ptr<Scene>& scene)
{
	auto current_scene = scene;

#ifdef _DEBUG
	//デバッグ用に難易度を変えるものを作成
	/*
	STARTボタンを押しながら
	DPADの左ならEasy
	DPADの下ならNormal
	DPADの右ならHard
	DPADの上ならTitle
	*/
	if (GamepadInput::getinstance()->GetButton(0, BUTTON::BACK))
	{
		//Easy
		if (GamepadInput::getinstance()->GetButton(0, BUTTON::DPAD_LEFT))
		{
			current_scene = std::make_shared<GameSceneEasy>();
		}
		//Normal
		else if (GamepadInput::getinstance()->GetButton(0, BUTTON::DPAD_DOWN))
		{
			current_scene = std::make_shared<GameSceneNormal>();
		}
		//Easy
		else if (GamepadInput::getinstance()->GetButton(0, BUTTON::DPAD_RIGHT))
		{
			current_scene = std::make_shared<GameSceneHard>();
		}
		//Title
		else if (GamepadInput::getinstance()->GetButton(0, BUTTON::DPAD_UP))
		{
			current_scene = std::make_shared<TitleScene>();
		}
	}
#endif

	//敵の更新
	if (current_game == GAME::MAIN)
	{
		//プレイヤーがボスゾーンに入ったらボスシーンに移行する場面に変更
		if (player->boss_scene)
		{
			current_game = GAME::TRANSLATION;
			Camera::getinstance()->SetTarget(nullptr);
			boss->TranslationBossScene();
			player->TranslationBossScene();
			BGM::getinstance()->ChangeBgm(std::string("boss_bgm"), L"BGM/boss.wav");
			camera_prev_x = Camera::getinstance()->GetPos().x + WINDOW_WIDTH / 2.0f;
		}
		else
		{
			//敵
			auto enemy_itr = std::begin(enemy);
			while (enemy_itr != std::end(enemy))
			{
				//プレイヤーと一定範囲離れると更新しない
				if (std::abs(player->transform.get_pos().x - enemy_itr->transform.get_pos().x) < WINDOW_WIDTH)
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
				if (std::abs(player->transform.get_pos().x - f_enemy_itr->transform.get_pos().x) < WINDOW_WIDTH)
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
		auto camera_pos = Camera::getinstance()->GetPos();
		if (boss->transform.get_pos().x - 250 - camera_prev_x != 0)
		{
			float color = (camera_pos.x - camera_prev_x) / (boss->transform.get_pos().x - 250 - camera_prev_x);
			if (color < 0.8f)
			{
				backGround[0].SetColor(1.0f, 1.0f - color * 0.8f, 1.0f - color, 1.0f);
			}
		}
		//プレイヤーとボスが近くなったらボスシーンに移行する
		if (player->transform.get_pos().x >= boss->transform.get_pos().x - 500 &&
			camera_pos.x > boss->transform.get_pos().x - 250)
		{
			current_game = GAME::BOSS;
			boss_center_x = Camera::getinstance()->GetPos().x;
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
			if (player->transform.get_pos().x < boss->transform.get_pos().x - 500)
			{
				player->transform.move({ 2.8f*1.2f,0,0 });
			}
			if (camera_pos.x < boss->transform.get_pos().x - 250)
			{
				camera_pos += Vec3{ 4.0f * 1.2f,0.0f,0 };
				Camera::getinstance()->/*Direct*/SetPos(camera_pos);
			}
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
			BGM::getinstance()->OneShotBGM(std::string("clear_bgm"), L"BGM/clear.wav");
			SceneManager::getinstance()->is_game_scene = false;
		}
		auto pos = player->transform.get_pos();
		//画面の外に出ないようにする（これは横のみの判定のためここで判定する）
		if (player->transform.get_pos().x < boss_center_x - WINDOW_WIDTH / 2.0f)
		{
			pos.x = boss_center_x - WINDOW_WIDTH / 2.0f;
			player->ResetSpeed();
		}
		else if (player->transform.get_pos().x > boss_center_x + WINDOW_WIDTH / 2.0f)
		{
			pos.x = boss_center_x + WINDOW_WIDTH / 2.0f;
			player->ResetSpeed();
		}
		player->transform.set_pos(pos);
		//プレイヤーの更新
		player->Update();
		boss->Update();
	}
	//クリア時のアニメーション
	else if (current_game == GAME::CLEAR)
	{
		player->ResetSpeed();
		//画面の中央付近に来たらアニメーション開始
		if (player->transform.get_pos().x > boss_center_x - 10 && player->transform.get_pos().x < boss_center_x + 10)
		{
			//ジャンプする
			if (!clear_jump&&player->gravity.SetUpPower(10.0f))
			{
				clear_jump = true;
				player->transform.rotate(Vec3(0, 0, saki::PI<float>*0.04f));
			}
			else if (clear_jump)
			{
				if (player->transform.get_rot().z != 0.0f)
				{
					player->transform.rotate(Vec3(0, 0, saki::PI<float>*0.04f));
					if (player->transform.get_rot().z > saki::PI<float>*2.0f)
					{
						player->transform.set_rot(Vec3(0, 0, 0));
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
			if (player->transform.get_pos().x < boss_center_x)
			{
				player->transform.move(Vec3(2.8f*1.2f, 0, 0));
				player->AnimationWalk(true);
			}
			else
			{
				player->transform.move(Vec3(-2.8f*1.2f, 0, 0));
				player->AnimationWalk(false);
			}
		}
		player->ClearUpdate();
		//current_scene = std::make_shared<TitleScene>();
	}
	//たまにアイテムの更新
	for (auto&& bi : bullet_item)
	{
		bi.Update();
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
	Sprite::target_x = player->transform.get_pos().x;
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
	//たまにアイテムの描画
	for (auto&& bi : bullet_item)
	{
		bi.Render();
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
	for (auto&& bi : bullet_item)
	{
		bi.Destroy();
	}
	bullet_item.clear();
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
	SceneManager::getinstance()->is_game_scene = false;
}