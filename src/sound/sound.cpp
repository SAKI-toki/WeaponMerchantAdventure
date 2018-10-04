/**
* @file sound.cpp
* @brief サウンドのメンバ関数の定義
* @author 石山　悠
* @date 2018/10/04
*/
#include "sound.h"
#include "manager/sound_manager.h"

/**
* @brief サウンドの初期化
* @param path サウンドのパス
* @param loop ループするかどうか
* @param awake 初期化した瞬間から再生するかどうか
*/
void Sound::Init(WCHAR* path, bool loop, bool awake)
{
	instance_sound = SoundManager::GetInstance()->GetSound(path)->CreateInstance();
	is_loop = loop;
	if (awake)Start();
}

/**
* @brief デストラクタ
*/
Sound::~Sound()
{
	instance_sound.reset();
}