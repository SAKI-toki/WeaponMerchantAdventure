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
* @brief 個々のサウンドクラス
*/
class Sound
{
	std::unique_ptr<DirectX::SoundEffectInstance> instance_sound;
	//ループするかどうか
	bool is_loop;
public:
	/**
	* @brief コンストラクタ
	*/
	Sound() {}
	/**
	* @brief コピーコンストラクタ
	*/
	Sound(const Sound& s)
	{
		//this->instance_sound = s.instance_sound;
		this->is_loop = s.is_loop;
	}
	/**
	* @brief コピー代入演算子
	*/
	Sound& operator=(const Sound& s)
	{
		if (this != &s)
		{
			//this->instance_sound = s.instance_sound;
			this->is_loop = s.is_loop;
		}
		return *this;
	}
	/**
	* @brief ムーブコンストラクタ
	*/
	Sound(Sound&& s)noexcept
	{
		this->instance_sound = std::move(s.instance_sound);
		this->is_loop = s.is_loop;
	}
	/**
	* @brief ムーブ代入演算子
	*/
	Sound& operator=(Sound&& s)noexcept
	{
		if (this != &s)
		{
			this->instance_sound = std::move(s.instance_sound);
			this->is_loop = s.is_loop;
		}
		return *this;
	}

	void Init(const std::string, WCHAR*, bool, bool);
	void Destroy();
	/**
	* @brief 再生
	*/
	void Start() { if (instance_sound)instance_sound->Play(is_loop); }

	/**
	* @brief 停止
	*/
	void Stop() { if (instance_sound)instance_sound->Stop(); }

	/**
	* @brief 一時停止
	*/
	void Pause() { if (instance_sound)instance_sound->Pause(); }

	/**
	* @brief 再生されているかどうか
	* @return bool 再生されていたらtrue
	*/
	bool Is_Play()const { return instance_sound && instance_sound->GetState() != DirectX::SoundState::STOPPED; }

	/**
	* @brief ボリュームのセッタ
	* @param vol ボリューム
	*/
	void SetVolume(float vol) { if (instance_sound)instance_sound->SetVolume(vol); }

	/**
	* @brief ピッチのセッタ
	* @param pit ピッチ
	*/
	void SetPitch(float pit) { if (instance_sound)instance_sound->SetPitch(pit); }

	/**
	* @brief パンのセッタ
	* @param pan パン
	*/
	void SetPan(float pan) { if (instance_sound)instance_sound->SetPan(pan); }


	~Sound();
	/*
	std::unique_ptr<DirectX::SoundEffectInstance>& operator()()
	{
		return instance_sound;
	}
	*/
};