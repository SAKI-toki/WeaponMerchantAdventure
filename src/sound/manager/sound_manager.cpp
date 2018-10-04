/**
* @file sound.h
* @brief サウンドマネージャークラスのメンバ関数を定義
* @author 石山　悠
* @date 2018/10/04
*/
#include "sound_manager.h"
#include <Dbt.h>
/**
* @brief サウンドマネージャークラスの初期化
* @param hWnd ウィンドウハンドラ
*/
void SoundManager::Init(HWND hWnd)
{
	DirectX::AUDIO_ENGINE_FLAGS eflags = DirectX::AudioEngine_Default;
#ifdef _DEBUG
	eflags = eflags | DirectX::AudioEngine_Debug;
#endif
	m_pAudioEngine = std::make_unique<DirectX::AudioEngine>(eflags);

	retry_audio = false;

	hNewAudio = nullptr;

	DEV_BROADCAST_DEVICEINTERFACE filter = {};
	filter.dbcc_size = sizeof(filter);
	filter.dbcc_devicetype = DBT_DEVTYP_DEVICEINTERFACE;
	filter.dbcc_classguid = KSCATEGORY_AUDIO;

	hNewAudio = RegisterDeviceNotification(hWnd, &filter, DEVICE_NOTIFY_WINDOW_HANDLE);
}

/**
* @brief サウンドマネージャーの更新
*/
void SoundManager::Update()
{
	if (retry_audio)
	{
		retry_audio = false;
		if (m_pAudioEngine->Reset())
		{

		}
	}
	else if (!m_pAudioEngine->Update())
	{
		if (m_pAudioEngine->IsCriticalError())
		{
			retry_audio = true;
		}
	}
}

/**
* @brief サウンドマネージャーの破棄
*/
void SoundManager::Destroy()
{
	Suspend();
	if (hNewAudio)UnregisterDeviceNotification(hNewAudio);
}

/**
* @brief サウンドを返す
* @param path wavファイルのパス
* @details 同じファイルを2度読み込まないようにする
*/
std::unique_ptr<DirectX::SoundEffect>& SoundManager::GetSound(WCHAR* path)
{
	auto itr = soundList.find(path);
	if (itr == soundList.end())
	{
		soundList.insert(std::make_pair(path, std::make_unique<DirectX::SoundEffect>(SoundManager::GetInstance()->GetEngine(), path)));
	}
	return soundList.at(path);

}
