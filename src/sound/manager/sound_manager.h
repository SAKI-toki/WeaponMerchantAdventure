/**
* @file sound_manager.h
* @brief サウンドマネージャークラスの宣言
* @author 石山　悠
* @date 2018/10/04
*/
#pragma once
#include "../../common/common.h"
#include "../../common/singleton.h"
#include "Audio.h"

/**
* @brief サウンドを管理するクラス
*/
class SoundManager :public Singleton<SoundManager>
{
	//必要なもの
	HDEVNOTIFY hNewAudio;
	std::unique_ptr<DirectX::AudioEngine> m_pAudioEngine;
	bool retry_audio;

	//1度読み込んだものは2回読み込まない
	//パスで管理
	std::unordered_map<WCHAR*, std::unique_ptr<DirectX::SoundEffect>> soundList;
public:
	std::unique_ptr<DirectX::SoundEffect>& GetSound(WCHAR*);

	void Init(HWND);
	void Update();
	void Destroy();

	//AudioEngineを返す
	auto GetEngine() { return m_pAudioEngine.get(); }

	//必要なもの
	void RetryAudio() { retry_audio = true; }
	void Suspend() { if (m_pAudioEngine)m_pAudioEngine->Suspend(); }
	void Resume() { if (m_pAudioEngine)m_pAudioEngine->Resume(); }
};