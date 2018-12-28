/**
* @file scene_manager.cpp
* @brief シーンのマネージャークラスのメンバ関数を定義
* @author 石山　悠
* @date 2018/11/20
*/
#include "scene_manager.h"
#include "../main/title/title_scene.h"
#include "../../input/gamepad/gamepad_input.h"
#include "../../input/keyboard/keyboard_input.h"
#include "../../sound/manager/sound_manager.h"
//#include "../../rendering/sprite/manager/sprite_manager.h"
#include "../../collider/manager/collider_manager.h"
#include "../../camera/camera.h"
#include "../fade/fade.h"
#include "../../object/ui/manager/ui_manager.h"
#include "../main/game/over/game_over.h"
#include "../pause/pause_scene.h"
#include "../../effect/manager/effect_manager.h"
#include "../../device/device.h"
#ifdef _DEBUG
#include "../main/select/select_scene.h"
#include "../main/game/easy/game_scene_easy.h"
#include "../main/game/normal/game_scene_normal.h"
#include "../main/game/hard/game_scene_hard.h"
#endif


/**
* @brief シーンマネージャーの初期化
*/
void SceneManager::Init()
{
	//SpriteManager::getinstance()->Init();
	Fade::getinstance()->Init();
	GameOver::getinstance()->Init();
	PauseScene::getinstance()->Init();
	//タイトルからスタート
#ifndef _DEBUG
	scene_ptr = std::make_shared<TitleScene>();
#else //デバッグ用にどこのシーンからでもスタートできる
	scene_ptr = std::make_shared<TitleScene>();
#endif
	scene_ptr->Init();
}

/**
* @brief 保持してるシーンの更新
*/
void SceneManager::Update()
{
	//サウンドの更新
	//SoundManager::getinstance()->Update();
	//エフェクトの更新
	EffectManager::getinstance()->Update();
	//フェードしていないときはシーンを更新する
	if (!is_current_fade)
	{
		if (is_game_scene && !GameOver::getinstance()->game_over_flg && !PauseScene::getinstance()->is_pause&&
			GamepadInput::getinstance()->GetButtonDown(0,BUTTON::START))
		{
			PauseScene::getinstance()->SwitchPause();
		}
		else
		{
			if (PauseScene::getinstance()->is_pause)
			{
				next_scene_ptr = PauseScene::getinstance()->Update(scene_ptr);
			}
			else
			{
				//シーンを更新し、ほかのシーンが返ってきたらシーン遷移する/*ここではシーン遷移はしていない*/
				next_scene_ptr = scene_ptr->Update(scene_ptr);
			}
			if (continue_scene || next_scene_ptr != scene_ptr)
			{
				//フェードを開始する
				is_current_fade = true;
				//ゲームパッドのバイブレーションのリセット
				GamepadInput::getinstance()->Vibration(0, 0, 0);
			}
			//当たり判定のチェック
			ColliderManager::getinstance()->CheckCollision();
			//カメラの更新
			Camera::getinstance()->update();
		}
	}
	//フェードインアウト
	else
	{
		if (!is_fade_in)
		{
			scene_ptr->ExitFadeUpdate();
			//当たり判定のチェック
			ColliderManager::getinstance()->CheckCollision();
			//カメラの更新
			Camera::getinstance()->update();
		}
		//フェードを更新し、インかアウトが終わったらtrueが返る
		if (Fade::getinstance()->Update(is_fade_in))
		{
			//フェードインが終わったらフェードを終わらせる
			if (is_fade_in)
			{
				is_current_fade = false;
			}
			else
			{
				//シーンの破棄
				scene_ptr->Destroy();
				//コライダのリセット
				ColliderManager::getinstance()->Reset();
				//エフェクトの破棄
				EffectManager::getinstance()->Clear();
				//UIの破棄
				UiManager::getinstance()->Destroy();
				//ポーズの終了
				PauseScene::getinstance()->EndPause();
				//シーンの遷移
				if (continue_scene)
				{
					next_scene_ptr = next_continue_scene_ptr;
					continue_scene = false;
				}
				scene_ptr = next_scene_ptr;
				//シーンの初期化
				scene_ptr->Init();
				//カメラの更新をここで一回しないと変なところにカメラがいってしまう
				Camera::getinstance()->update();
			}
			//フェードインが終わったら次はフェードアウト、逆も然り
			is_fade_in = !is_fade_in;
		}
	}
}

/**
* @brief 保持してるシーンの描画
*/
void SceneManager::Render()
{
	Device::getinstance()->draw_begin();
	Sprite::depth = 9999;
	//シーンの描画
	scene_ptr->Render();
	//エフェクトの描画
	EffectManager::getinstance()->Render();
	//UIの描画
	UiManager::getinstance()->Render();
	if (GameOver::getinstance()->game_over_flg)
	{
		//ゲームオーバーシーンの描画
		GameOver::getinstance()->Render();
	}
	else if (PauseScene::getinstance()->is_pause)
	{
		PauseScene::getinstance()->Render();
	}
	//もしシーン遷移中なら
	if (is_current_fade)Fade::getinstance()->Render();
	Device::getinstance()->draw_end();
}

/**
* @brief 保持してるシーンのマネージャーの破棄
*/
void SceneManager::Destroy()
{
	scene_ptr->Destroy();
	Fade::getinstance()->Destroy();
	SoundManager::getinstance()->destroy();
	PauseScene::getinstance()->Destroy();
}
