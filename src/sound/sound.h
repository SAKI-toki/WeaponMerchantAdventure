/**
* @file sound.h
* @brief サウンドクラスの宣言
* @author 石山　悠
* @date 2018/10/04
*/
#pragma once
#include <string>
#include <optional>
#include <Audio.h>

/**
* @brief　個々のサウンドクラス
*/
class Sound
{
	std::unique_ptr<DirectX::SoundEffectInstance> instance_sound;
	//ループするかどうか
	bool is_loop;
public:
	void Init(WCHAR*, bool, bool);

	//再生
	void Start() { instance_sound->Play(is_loop); }
	//停止
	void Stop() { instance_sound->Stop(); }
	//一時停止
	void Pause() { instance_sound->Pause(); }
	//ボリューム
	void SetVolume(float vol) { instance_sound->SetVolume(vol); }
	//ピッチ
	void SetPitch(float pit) { instance_sound->SetPitch(pit); }
	//パン
	void SetPan(float pan) { instance_sound->SetPan(pan); }

	~Sound();

	std::unique_ptr<DirectX::SoundEffectInstance>& operator()()
	{
		return instance_sound;
	}
};