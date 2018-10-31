/**
* @file sound.h
* @brief �T�E���h�N���X�̐錾
* @author �ΎR�@�I
* @date 2018/10/04
*/
#pragma once
#include <string>
#include <optional>
#include <Audio.h>

/**
* @brief �X�̃T�E���h�N���X
*/
class Sound
{
	std::unique_ptr<DirectX::SoundEffectInstance> instance_sound;
	//���[�v���邩�ǂ���
	bool is_loop;
public:
	/**
	* @brief �R���X�g���N�^
	*/
	Sound() {}
	/**
	* @brief �R�s�[�R���X�g���N�^
	*/
	Sound(const Sound& s)
	{
		//this->instance_sound = s.instance_sound;
		this->is_loop = s.is_loop;
	}
	/**
	* @brief �R�s�[������Z�q
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
	* @brief ���[�u�R���X�g���N�^
	*/
	Sound(Sound&& s)noexcept
	{
		this->instance_sound = std::move(s.instance_sound);
		this->is_loop = s.is_loop;
	}
	/**
	* @brief ���[�u������Z�q
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
	//�Đ�
	void Start() { if (instance_sound)instance_sound->Play(is_loop); }
	//��~
	void Stop() { if (instance_sound)instance_sound->Stop(); }
	//�ꎞ��~
	void Pause() { if (instance_sound)instance_sound->Pause(); }
	//�Đ�����Ă��邩�ǂ���
	bool Is_Play()const { return instance_sound && instance_sound->GetState() != DirectX::SoundState::STOPPED; }
	//�{�����[��
	void SetVolume(float vol) { if (instance_sound)instance_sound->SetVolume(vol); }
	//�s�b�`
	void SetPitch(float pit) { if (instance_sound)instance_sound->SetPitch(pit); }
	//�p��
	void SetPan(float pan) { if (instance_sound)instance_sound->SetPan(pan); }

	~Sound();

	std::unique_ptr<DirectX::SoundEffectInstance>& operator()()
	{
		return instance_sound;
	}
};