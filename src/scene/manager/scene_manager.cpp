/**
* @file scene_manager.cpp
* @brief シーンのマネージャークラスのメンバ関数を定義
* @author 石山　悠
* @date 2018/10/30
*/
#include "scene_manager.h"
#include "../main/title/title_scene.h"
#include "../main/game/game_scene.h"
#include "../../input/gamepad/gamepad_input.h"
#include "../../sound/manager/sound_manager.h"
#include "../../rendering/sprite/manager/sprite_manager.h"
#include "../../collider/manager/collider_manager.h"
#include "../../object/camera/camera.h"
#include "../fade/fade.h"

/**
* @brief シーンマネージャーの初期化
*/
void SceneManager::Init()
{
	SpriteManager::GetInstance()->Init();
	Fade::GetInstance()->Init();
	//タイトルからスタート
	my_scene = SCENE::TITLE;
	scene_ptr = switch_scene(my_scene);
	scene_ptr->Init();
}

/**
* @brief 保持してるシーンの更新
*/
void SceneManager::Update()
{
	//サウンドの更新
	SoundManager::GetInstance()->Update();
	//フェードしていないときはシーンを更新する
	if (!is_current_fade)
	{
		//ゲームパッドの更新
		GamepadInput::GetInstance()->Update();
		//シーンを更新し、ほかのシーンが返ってきたらシーン遷移する/*ここではシーン遷移はしていない*/
		auto next_scene = scene_ptr->Update();
		if (next_scene != my_scene)
		{
			my_scene = next_scene;
			//フェードを開始する
			is_current_fade = true;
			//ゲームパッドのバイブレーションのリセット
			GamepadInput::GetInstance()->Vibration(0, 0);
		}
		//当たり判定のチェック
		ColliderManager::GetInstance()->CheckCollision();
		//カメラの更新
		Camera::GetInstance()->Update();
	}
	//フェードインアウト
	else
	{
		//フェードを更新し、インかアウトが終わったらtrueが返る
		if (Fade::GetInstance()->Update(is_fade_in))
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
				ColliderManager::GetInstance()->Reset();
				//シーンの遷移
				scene_ptr = switch_scene(my_scene);
				//シーンの初期化
				scene_ptr->Init();
				//カメラの更新をここで一回しないと変なところにカメラがいってしまう
				Camera::GetInstance()->Update();
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
	scene_ptr->Render();
	//もしシーン遷移中なら
	if (is_current_fade)Fade::GetInstance()->Render();
}

/**
* @brief 保持してるシーンのマネージャーの破棄
*/
void SceneManager::Destroy()
{
	scene_ptr->Destroy();
	Fade::GetInstance()->Destroy();
	SoundManager::GetInstance()->Destroy();
}

/**
* @brief 引数によってシーンを切り替える
* @param scene 次のシーンのenum class
* @return std::unique_ptr<Scene>
*/
std::unique_ptr<Scene> SceneManager::switch_scene(const SCENE scene)const
{
	switch (scene)
	{
	case SCENE::TITLE:
		return std::make_unique<TitleScene>();
	case SCENE::GAME:
		return std::make_unique<GameScene>();
	}
	Comment(L"登録していないシーンに遷移した", L"error");
	return nullptr;
}